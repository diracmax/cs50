/*long allBlue = image[i][j].rgbtBlue;
            if ((i > 0) && (i < height - 1) && (j > 0) && (j < width - 1))
            {
                allBlue += image[i][j - 1].rgbtBlue + image[i][j + 1].rgbtBlue + image[i - 1][j - 1].rgbtBlue + image[i - 1][j].rgbtBlue + image[i - 1][j + 1].rgbtBlue + image[i + 1][j - 1].rgbtBlue + image[i + 1][j].rgbtBlue + image[i + 1][j + 1].rgbtBlue;
                allBlue /= 9;
            }

            if (i == 0)
            {
                if (j == 0)
                {
                    allBlue += image[i][j + 1].rgbtBlue  + image[i + 1][j].rgbtBlue + image[i + 1][j + 1].rgbtBlue;
                    allBlue /= 4;
                }
                else if (j == width - 1)
                {
                    allBlue += image[i][j - 1].rgbtBlue + image[i + 1][j - 1].rgbtBlue + image[i + 1][j].rgbtBlue;
                    allBlue /= 4;
                }
                else
                {
                    allBlue += image[i][j - 1].rgbtBlue + image[i][j + 1].rgbtBlue + image[i + 1][j - 1].rgbtBlue + image[i + 1][j].rgbtBlue + image[i + 1][j + 1].rgbtBlue;
                    allBlue /= 6;
                }
            }

            if (i == height - 1)
            {
                if (j == 0)
                {
                    allBlue += image[i][j + 1].rgbtBlue + image[i - 1][j].rgbtBlue + image[i - 1][j + 1].rgbtBlue;
                    allBlue /= 4;
                }
                else if (j == width - 1)
                {
                    allBlue += image[i][j - 1].rgbtBlue + image[i - 1][j - 1].rgbtBlue + image[i - 1][j].rgbtBlue;
                    allBlue /= 4;
                }
                else
                {
                    allBlue += image[i][j - 1].rgbtBlue + image[i][j + 1].rgbtBlue + image[i - 1][j - 1].rgbtBlue + image[i - 1][j].rgbtBlue + image[i - 1][j + 1].rgbtBlue;
                    allBlue /= 6;
                }
            }

            if ((j == 0) && (i != 0) && (i != height - 1))
            {
                allBlue += image[i][j + 1].rgbtBlue + image[i - 1][j].rgbtBlue + image[i - 1][j + 1].rgbtBlue + image[i + 1][j].rgbtBlue + image[i + 1][j + 1].rgbtBlue;
                allBlue /= 6;
            }

            if ((j == width - 1) && (i != 0) && (i != height - 1))
            {
                allBlue += image[i][j - 1].rgbtBlue + image[i - 1][j - 1].rgbtBlue + image[i - 1][j].rgbtBlue + image[i + 1][j - 1].rgbtBlue + image[i + 1][j].rgbtBlue;
                allBlue /= 6;
            }

            image[i][j].rgbtBlue = allBlue;
            */

 /*float allGreen = image[i][j].rgbtGreen;
            count = 1;

            if (!((i == 0) || (j == 0)))
            {
                allGreen += image[i - 1][j - 1].rgbtGreen;
                count++;
            }

            if (!(i == 0))
            {
                allGreen += image[i - 1][j].rgbtGreen;
                count++;
            }

            if (!((i == 0) || (j == (width - 1))))
            {
                allGreen += image[i - 1][j + 1].rgbtGreen;
                count++;
            }

            if (!(j == 0))
            {
                allGreen += image[i][j - 1].rgbtGreen;
                count++;
            }

            if (!(j == (width - 1)))
            {
                allGreen += image[i][j + 1].rgbtGreen;
                count++;
            }

            if (!((i == height - 1) || (j == 0)))
            {
                allGreen += image[i + 1][j - 1].rgbtGreen;
                count++;
            }

            if (!(i == (height - 1)))
            {
                allGreen += image[i + 1][j].rgbtGreen;
                count++;
            }

            if (!((i == (height - 1)) || (j == (width - 1))))
            {
                allGreen += image[i + 1][j + 1].rgbtGreen;
                count++;
            }

            image[i][j].rgbtGreen = round(allGreen / count);

            float allRed = image[i][j].rgbtRed;
            count = 1;

            if (!((i == 0) || (j == 0)))
            {
                allRed += image[i - 1][j - 1].rgbtRed;
                count++;
            }

            if (!(i == 0))
            {
                allRed += image[i - 1][j].rgbtRed;
                count++;
            }

            if (!((i == 0) || (j == (width - 1))))
            {
                allRed += image[i - 1][j + 1].rgbtRed;
                count++;
            }

            if (!(j == 0))
            {
                allRed += image[i][j - 1].rgbtRed;
                count++;
            }

            if (!(j == (width - 1)))
            {
                allRed += image[i][j + 1].rgbtRed;
                count++;
            }

            if (!((i == height - 1) || (j == 0)))
            {
                allRed += image[i + 1][j - 1].rgbtRed;
                count++;
            }

            if (!(i == (height - 1)))
            {
                allRed += image[i + 1][j].rgbtRed;
                count++;
            }

            if (!((i == (height - 1)) || (j == (width - 1))))
            {
                allRed += image[i + 1][j + 1].rgbtRed;
                count++;
            }

            image[i][j].rgbtRed = round(allRed / count);
            */