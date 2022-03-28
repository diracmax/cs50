#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            BYTE mean = round((image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / (double) 3);
            image[i][j].rgbtBlue = mean;
            image[i][j].rgbtGreen = mean;
            image[i][j].rgbtRed = mean;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0, n = width / 2; j < n; j++)
        {
            RGBTRIPLE tmp = image[i][j];
            image[i][j] = image[i][width - j - 1];
            image[i][width - j - 1] = tmp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE tmp[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            tmp[i][j].rgbtBlue = image[i][j].rgbtBlue;
            tmp[i][j].rgbtGreen = image[i][j].rgbtGreen;
            tmp[i][j].rgbtRed = image[i][j].rgbtRed;
        }
    }
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {

            float allBlue = tmp[i][j].rgbtBlue;
            float allGreen = tmp[i][j].rgbtGreen;
            float allRed = tmp[i][j].rgbtRed;
            int count = 1;

            if (!((i == 0) || (j == 0)))
            {
                allBlue += tmp[i - 1][j - 1].rgbtBlue;
                allGreen += tmp[i - 1][j - 1].rgbtGreen;
                allRed += tmp[i - 1][j - 1].rgbtRed;
                count++;
            }

            if (!(i == 0))
            {
                allBlue += tmp[i - 1][j].rgbtBlue;
                allGreen += tmp[i - 1][j].rgbtGreen;
                allRed += tmp[i - 1][j].rgbtRed;
                count++;
            }

            if (!((i == 0) || (j == (width - 1))))
            {
                allBlue += tmp[i - 1][j + 1].rgbtBlue;
                allGreen += tmp[i - 1][j + 1].rgbtGreen;
                allRed += tmp[i - 1][j + 1].rgbtRed;
                count++;
            }

            if (!(j == 0))
            {
                allBlue += tmp[i][j - 1].rgbtBlue;
                allGreen += tmp[i][j - 1].rgbtGreen;
                allRed += tmp[i][j - 1].rgbtRed;
                count++;
            }

            if (!(j == (width - 1)))
            {
                allBlue += tmp[i][j + 1].rgbtBlue;
                allGreen += tmp[i][j + 1].rgbtGreen;
                allRed += tmp[i][j + 1].rgbtRed;
                count++;
            }

            if (!((i == (height - 1)) || (j == 0)))
            {
                allBlue += tmp[i + 1][j - 1].rgbtBlue;
                allGreen += tmp[i + 1][j - 1].rgbtGreen;
                allRed += tmp[i + 1][j - 1].rgbtRed;
                count++;
            }

            if (!(i == (height - 1)))
            {
                allBlue += tmp[i + 1][j].rgbtBlue;
                allGreen += tmp[i + 1][j].rgbtGreen;
                allRed += tmp[i + 1][j].rgbtRed;
                count++;
            }

            if (!((i == (height - 1)) || (j == (width - 1))))
            {
                allBlue += tmp[i + 1][j + 1].rgbtBlue;
                allGreen += tmp[i + 1][j + 1].rgbtGreen;
                allRed += tmp[i + 1][j + 1].rgbtRed;
                count++;
            }

            image[i][j].rgbtBlue = round(allBlue / count);
            image[i][j].rgbtGreen = round(allGreen / count);
            image[i][j].rgbtRed = round(allRed / count);
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE tmp[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            tmp[i][j].rgbtBlue = image[i][j].rgbtBlue;
            tmp[i][j].rgbtGreen = image[i][j].rgbtGreen;
            tmp[i][j].rgbtRed = image[i][j].rgbtRed;
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int gx[3][3] =
            {
                {-1, 0, 1},
                {-2, 0, 2},
                {-1, 0, 1}
            };
            int gy[3][3] =
            {
                {-1, -2, -1},
                {0, 0, 0},
                {1, 2, 1}
            };

            if ((i == 0) || (j == 0))
            {
                gx[0][0] = 0;
                gy[0][0] = 0;
            }

            if (i == 0)
            {
                gx[0][1] = 0;
                gy[0][1] = 0;
            }

            if ((i == 0) || (j == (width - 1)))
            {
                gx[0][2] = 0;
                gy[0][2] = 0;
            }

            if (j == 0)
            {
                gx[1][0] = 0;
                gy[1][0] = 0;
            }

            if (j == (width - 1))
            {
                gx[1][2] = 0;
                gy[1][2] = 0;
            }

            if ((i == (height - 1)) || (j == 0))
            {
                gx[2][0] = 0;
                gy[2][0] = 0;
            }

            if (i == (height - 1))
            {
                gx[2][1] = 0;
                gy[2][1] = 0;
            }

            if ((i == (height - 1)) || (j == (width - 1)))
            {
                gx[2][2] = 0;
                gy[2][2] = 0;
            }

            int sum_red_gx = 0;
            int sum_green_gx = 0;
            int sum_blue_gx = 0;
            int sum_red_gy = 0;
            int sum_green_gy = 0;
            int sum_blue_gy = 0;

            for (int k = -1; k < 2; k++)
            {
                for (int l = -1; l < 2; l++)
                {
                    sum_red_gx += tmp[i + k][j + l].rgbtRed * gx[1 + k][1 + l];
                    sum_green_gx += tmp[i + k][j + l].rgbtGreen * gx[1 + k][1 + l];
                    sum_blue_gx += tmp[i + k][j + l].rgbtBlue * gx[1 + k][1 + l];
                    sum_red_gy += tmp[i + k][j + l].rgbtRed * gy[1 + k][1 + l];
                    sum_green_gy += tmp[i + k][j + l].rgbtGreen * gy[1 + k][1 + l];
                    sum_blue_gy += tmp[i + k][j + l].rgbtBlue * gy[1 + k][1 + l];
                }
            }

            int sum_red = round(sqrt(sum_red_gx * sum_red_gx + sum_red_gy * sum_red_gy));
            int sum_green = round(sqrt(sum_green_gx * sum_green_gx + sum_green_gy * sum_green_gy));
            int sum_blue = round(sqrt(sum_blue_gx * sum_blue_gx + sum_blue_gy * sum_blue_gy));
            if (sum_red > 255)
            {
                sum_red = 255;
            }
            if (sum_green > 255)
            {
                sum_green = 255;
            }
            if (sum_blue > 255)
            {
                sum_blue = 255;
            }
            image[i][j].rgbtRed = sum_red;
            image[i][j].rgbtGreen = sum_green;
            image[i][j].rgbtBlue = sum_blue;

        }
    }

    return;
}
