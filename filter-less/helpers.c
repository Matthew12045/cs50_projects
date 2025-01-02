#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int rgbAvg = round(
                (float) (image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / 3);
            image[i][j].rgbtRed = rgbAvg;
            image[i][j].rgbtGreen = rgbAvg;
            image[i][j].rgbtBlue = rgbAvg;
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
            int sepiaRed = round(0.393 * image[i][j].rgbtRed + 0.769 * image[i][j].rgbtGreen +
                                 0.189 * image[i][j].rgbtBlue);
            int sepiaGreen = round(0.349 * image[i][j].rgbtRed + 0.686 * image[i][j].rgbtGreen +
                                   0.168 * image[i][j].rgbtBlue);
            int sepiaBlue = round(0.272 * image[i][j].rgbtRed + 0.534 * image[i][j].rgbtGreen +
                                  0.131 * image[i][j].rgbtBlue);
            image[i][j].rgbtRed = fmin(sepiaRed, 255);
            image[i][j].rgbtGreen = fmin(sepiaGreen, 255);
            image[i][j].rgbtBlue = fmin(sepiaBlue, 255);
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        int last = width - 1;
        for (int j = 0; j < width / 2; j++)
        {
            int tmpRed = image[i][last].rgbtRed;
            int tmpGreen = image[i][last].rgbtGreen;
            int tmpBlue = image[i][last].rgbtBlue;
            image[i][last].rgbtRed = image[i][j].rgbtRed;
            image[i][last].rgbtGreen = image[i][j].rgbtGreen;
            image[i][last].rgbtBlue = image[i][j].rgbtBlue;
            image[i][j].rgbtRed = tmpRed;
            image[i][j].rgbtGreen = tmpGreen;
            image[i][j].rgbtBlue = tmpBlue;
            last--;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE virgin[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            virgin[i][j] = image[i][j];
        }
    }

    // Iterate over each pixel in the original image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int sumRed = 0, sumGreen = 0, sumBlue = 0;
            int count = 0;

            // Iterate over the neighboring pixels within the 3x3 grid
            for (int di = -1; di <= 1; di++)
            {
                for (int dj = -1; dj <= 1; dj++)
                {
                    // Calculate the neighboring pixel's row index
                    int ni = i + di;
                    // Calculate the neighboring pixel's column index
                    int nj = j + dj;

                    // Check if the neighboring pixel is within the image boundaries
                    // This ensures we don't access pixels outside the image
                    if (ni >= 0 && ni < height && nj >= 0 && nj < width)
                    {
                        sumRed += virgin[ni][nj].rgbtRed;
                        sumGreen += virgin[ni][nj].rgbtGreen;
                        sumBlue += virgin[ni][nj].rgbtBlue;
                        count++;
                    }
                }
            }

            // Calculate the average color values
            image[i][j].rgbtRed = fmin(round((float) sumRed / count), 255);
            image[i][j].rgbtGreen = fmin(round((float) sumGreen / count), 255);
            image[i][j].rgbtBlue = fmin(round((float) sumBlue / count), 255);
        }
    }
    return;
}
