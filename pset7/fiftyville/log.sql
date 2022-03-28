-- Keep a log of any SQL queries you execute as you solve the mystery.

-- $ sqlite3 fiftyville.db
-- SQLite version 3.34.0 2020-12-01 16:14:00
-- Enter ".help" for usage hints.
-- sqlite> .tables
-- airports                  crime_scene_reports       people
-- atm_transactions          flights                   phone_calls
-- bank_accounts             interviews
-- courthouse_security_logs  passengers

-- .schema crime_scene_reports
-- CREATE TABLE crime_scene_reports (
--     id INTEGER,
--     year INTEGER,
--     month INTEGER,
--     day INTEGER,
--     street TEXT,
--     description TEXT,
--     PRIMARY KEY(id)
-- );

--About the crime scene
SELECT description FROM crime_scene_reports WHERE month = 7 AND day = 28 AND street = "Chamberlin Street";
-- descriptionTheft of the CS50 duck took place at 10:15am at the Chamberlin Street courthouse. Interviews were conducted today with three witnesses who were present at the time — each of their interview transcripts mentions the courthouse.

--Informed consent
SELECT transcript FROM interviews WHERE year = 2020 AND month = 7 AND day = 28;

-- transcript
-- “Ah,” said he, “I forgot that I had not seen you for some weeks. It is a little souvenir from the King of Bohemia in return for my assistance in the case of the Irene Adler papers.”
-- “I suppose,” said Holmes, “that when Mr. Windibank came back from France he was very annoyed at your having gone to the ball.”
-- “You had my note?” he asked with a deep harsh voice and a strongly marked German accent. “I told you that I would call.” He looked from one to the other of us, as if uncertain which to address.
-- Sometime within ten minutes of the theft, I saw the thief get into a car in the courthouse parking lot and drive away. If you have security footage from the courthouse parking lot, you might want to look for cars that left the parking lot in that time frame.
-- I don't know the thief's name, but it was someone I recognized. Earlier this morning, before I arrived at the courthouse, I was walking by the ATM on Fifer Street and saw the thief there withdrawing some money.
-- As the thief was leaving the courthouse, they called someone who talked to them for less than a minute. In the call, I heard the thief say that they were planning to take the earliest flight out of Fiftyville tomorrow. The thief then asked the person on the other end of the phone to purchase the flight ticket.

--Parking records within 10 minutes of the incident
SELECT activity, license_plate FROM courthouse_security_logs WHERE year = 2020 AND month = 7 AND day = 28 AND hour = 10 AND minute >= 15 AND minute <= 25;
-- activity | license_plate
-- exit | 5P2BI95
-- exit | 94KL13X
-- exit | 6P58WS2
-- exit | 4328GD8
-- exit | G412CB7
-- exit | L93JTIZ
-- exit | 322W7JE
-- exit | 0NTHK55

--Number plates of cars entering and leaving the car park within 10 minutes of the incident
SELECT name, phone_number, passport_number FROM people WHERE license_plate IN (SELECT license_plate FROM courthouse_security_logs WHERE year = 2020 AND month = 7 AND day = 28 AND hour = 10 AND minute >= 15 AND minute <= 25);
-- name | phone_number | passport_number
-- Patrick | (725) 555-4692 | 2963008352
-- Amber | (301) 555-4174 | 7526138472
-- Elizabeth | (829) 555-5269 | 7049073643
-- Roger | (130) 555-0289 | 1695452385
-- Danielle | (389) 555-5198 | 8496433585
-- Russell | (770) 555-1861 | 3592750733
-- Evelyn | (499) 555-9472 | 8294398571
-- Ernest | (367) 555-5533 | 5773159633

--The name of the person who leaves the car park within 10 minutes of the incident, makes a call of 60 seconds or less, and is the fastest to leave Fiftyville the next day.
SELECT name FROM people WHERE license_plate IN (SELECT license_plate FROM courthouse_security_logs WHERE year = 2020 AND month = 7 AND day = 28 AND hour = 10 AND minute >= 15 AND minute <= 25) INTERSECT SELECT name FROM people WHERE phone_number IN (SELECT caller FROM phone_calls WHERE year = 2020 AND month = 7 AND day = 28 AND duration <= 60) INTERSECT SELECT name FROM people WHERE passport_number IN (SELECT passport_number FROM passengers WHERE flight_id IN (SELECT id FROM flights WHERE year = 2020 AND month = 7 AND day = 29 AND origin_airport_id IN (SELECT id FROM airports WHERE city = "Fiftyville") ORDER BY hour ASC, minute ASC LIMIT 1));

-- name
-- Ernest
-- Evelyn
-- Roger

--The name of person who withdrew money from a bank near Fifty Street on the day of the incident
SELECT people.name FROM people JOIN bank_accounts ON people.id = bank_accounts.person_id WHERE bank_accounts.account_number IN (SELECT bank_accounts.account_number FROM bank_accounts JOIN atm_transactions ON bank_accounts.account_number = atm_transactions.account_number WHERE atm_transactions.year = 2020 AND atm_transactions.month = 7 AND atm_transactions.day = 28 AND atm_transactions.atm_location = "Fifer Street" AND atm_transactions.transaction_type = "withdraw");

--The name of the person who withdrew money from a bank near Fifty Street on the day of the incident, left the car park within 10 minutes of the incident, made a call of 60 seconds or less, and left Fiftyville the fastest the next day
SELECT name FROM people WHERE license_plate IN (SELECT license_plate FROM courthouse_security_logs WHERE year = 2020 AND month = 7 AND day = 28 AND hour = 10 AND minute >= 15 AND minute <= 25) INTERSECT SELECT name FROM people WHERE phone_number IN (SELECT caller FROM phone_calls WHERE year = 2020 AND month = 7 AND day = 28 AND duration <= 60) INTERSECT SELECT name FROM people WHERE passport_number IN (SELECT passport_number FROM passengers WHERE flight_id IN (SELECT id FROM flights WHERE year = 2020 AND month = 7 AND day = 29 AND origin_airport_id IN (SELECT id FROM airports WHERE city = "Fiftyville") ORDER BY hour ASC, minute ASC LIMIT 1)) INTERSECT SELECT people.name FROM people JOIN bank_accounts ON people.id = bank_accounts.person_id WHERE bank_accounts.account_number IN (SELECT bank_accounts.account_number FROM bank_accounts JOIN atm_transactions ON bank_accounts.account_number = atm_transactions.account_number WHERE atm_transactions.year = 2020 AND atm_transactions.month = 7 AND atm_transactions.day = 28 AND atm_transactions.atm_location = "Fifer Street" AND atm_transactions.transaction_type = "withdraw");

--The THIEF is Ernest

--Ernest's callers
SELECT name FROM people WHERE phone_number IN (SELECT receiver FROM phone_calls WHERE year = 2020 AND month = 7 AND day = 28 AND duration <= 60 AND caller = (SELECT phone_number FROM people WHERE name = "Ernest"));
-- name
-- Berthold

--The ACCOMPLICE is Berthold

--The name of the city of the airport you are fleeing to
SELECT city FROM airports WHERE id IN (SELECT destination_airport_id FROM flights WHERE id IN (SELECT id FROM flights WHERE year = 2020 AND month = 7 AND day = 29 AND origin_airport_id IN (SELECT id FROM airports WHERE city = "Fiftyville") ORDER BY hour ASC, minute ASC LIMIT 1));

-- city
-- London

--The thief ESCAPED TO London