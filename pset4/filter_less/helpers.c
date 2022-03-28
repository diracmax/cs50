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

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            float originalBlue = image[i][j].rgbtBlue;
            float originalGreen = image[i][j].rgbtGreen;
            float originalRed = image[i][j].rgbtRed;
            int red = round(.393 * originalRed + .769 * originalGreen + .189 * originalBlue);
            int green = round(.349 * originalRed + .686 * originalGreen + .168 * originalBlue);
            int blue = round(.272 * originalRed + .534 * originalGreen + .131 * originalBlue);

            if (blue > 255)
            {
                image[i][j].rgbtBlue = 255;
            }
            else
            {
                image[i][j].rgbtBlue = blue;
            }
            if (green > 255)
            {
                image[i][j].rgbtGreen = 255;
            }
            else
            {
                image[i][j].rgbtGreen = green;
            }
            if (red > 255)
            {
                image[i][j].rgbtRed = 255;
            }
            else
            {
                image[i][j].rgbtRed = red;
            }
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
