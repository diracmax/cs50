import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions, HTTPException, InternalServerError
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True


# Ensure responses aren't cached
@app.after_request
def after_request(response):
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    own_stocks = db.execute("SELECT symbol, SUM(number) AS number FROM history WHERE id = ? GROUP BY symbol;", session["user_id"])
    money = db.execute("SELECT cash FROM users WHERE id = ?;", session["user_id"])
    return render_template("index.html", own_stocks=own_stocks, lookup=lookup, money=money[0]["cash"])


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "POST":
        # Ensure Symbol was submitted
        if not request.form.get("symbol") or lookup(request.form.get("symbol")) == None:
            return apology("The symbol does not exist.", 400)

        # Accept only positive numbers
        if not request.form.get("shares").isnumeric() or request.form.get("shares") == 0:
            return apology("invalid shares", 400)

        stock_price = lookup(request.form.get("symbol"))["price"]
        user_information = db.execute("SELECT * FROM users WHERE id = ?;", session["user_id"])
        money = user_information[0]["cash"]
        balance = int(money) - int(stock_price) * int(request.form.get("shares"))

        if balance >= 0:
            # When you can buy

            # Refresh the user's cache
            db.execute("UPDATE users SET cash = ? WHERE id = ?;", balance, session["user_id"])

            # Add purchase history
            db.execute("INSERT INTO history (id, symbol, price, number) VALUES (?, ?, ?, ?)",
                       session["user_id"], request.form.get("symbol"), stock_price, request.form.get("shares"))

            return redirect("/")
        else:
            # When you cannot buy
            return apology("I don't have enough money.", 400)

    else:
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    transaction_history = db.execute("SELECT * FROM history WHERE id = ?;", session["user_id"])
    return render_template("history.html", transaction_history=transaction_history)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 400)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 400)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 400)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    if request.method == "POST":
        # Ensure symbol was submitted
        if not request.form.get("symbol"):
            return apology("must provide symbol", 400)

        if lookup(request.form.get("symbol")) != None:
            # When the symbol exists
            name = lookup(request.form.get("symbol"))["name"]
            price = usd(lookup(request.form.get("symbol"))["price"])
            symbol = lookup(request.form.get("symbol"))["symbol"]

            return render_template("quoted.html", name=name, price=price, symbol=symbol)

        else:
            # When the symbol doesn't exist
            return apology("The symbol does not exist", 400)

    else:
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    if request.method == "POST":
        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 400)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 400)

        # Ensure confirmation was submitted
        elif not request.form.get("confirmation"):
            return apology("must provide confirmation", 400)

        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        # When the user already exists
        if len(rows) != 0:
            return apology("The user name is already in use.", 400)

        # When the password does not match
        if request.form.get("password") != request.form.get("confirmation"):
            return apology("The two passwords are different.", 400)

        # Add a user's information to the database
        db.execute("INSERT INTO users (username, hash) VALUES(?, ?);", request.form.get("username"),
                   generate_password_hash(request.form.get("password"), method='pbkdf2:sha256', salt_length=8))

        return render_template("login.html")

    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    if request.method == "POST":
        # When the symbol does not exist
        if not request.form.get("symbol") or lookup(request.form.get("symbol")) == None:
            return apology("The symbol does not exist.", 400)

        stock_price = int(lookup(request.form.get("symbol"))["price"])
        user_information = db.execute("SELECT * FROM users WHERE id = ?;", session["user_id"])

        # User's money
        money = int(user_information[0]["cash"])

        # The amount of money the user has after the sale
        money += stock_price * int(request.form.get("shares"))

        # Current shares which the user has
        shares = db.execute("SELECT SUM(number) AS total FROM history WHERE id = ? AND symbol = ?;",
                            session["user_id"], request.form.get("symbol"))

        if int(shares[0]["total"]) >= int(request.form.get("shares")):
            # When you can sell
            db.execute("UPDATE users SET cash = ? WHERE id = ?;", money, session["user_id"])

            # Update the user's information to the database
            db.execute("INSERT INTO history (id, symbol, price, number) VALUES (?, ?, ?, ?)",
                       session["user_id"], request.form.get("symbol"), stock_price, -int(request.form.get("shares")))
            return redirect("/")
        else:
            # When you cannot sell
            return apology("I don't have enough shares.", 400)
    else:
        share_symbols = db.execute("SELECT DISTINCT symbol FROM history WHERE id = ?;", session["user_id"])
        return render_template("sell.html", share_symbols=share_symbols)


@app.route("/password_change", methods=["GET", "POST"])
def password_change():
    if request.method == "POST":
        # Ensure password was submitted
        if not request.form.get("password"):
            return apology("must provide new password", 400)

        # Ensure confirmation was submitted
        elif not request.form.get("confirmation"):
            return apology("must provide confirmation", 400)

        if request.form.get("password") != request.form.get("confirmation"):
            return apology("The two passwords are different.", 400)

        # Update the user's password
        db.execute("UPDATE users SET hash = ? WHERE id = ?;", generate_password_hash(
            request.form.get("password"), method='pbkdf2:sha256', salt_length=8), session["user_id"])

        return render_template("success.html")

    else:
        return render_template("change.html")


def errorhandler(e):
    """Handle error"""
    if not isinstance(e, HTTPException):
        e = InternalServerError()
    return apology(e.name, e.code)


# Listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)
