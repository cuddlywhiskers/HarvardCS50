#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int avg = round(((float) image[i][j].rgbtRed + (float) image[i][j].rgbtGreen + (float) image[i][j].rgbtBlue) / 3);

            image[i][j].rgbtRed = avg;
            image[i][j].rgbtGreen = avg;
            image[i][j].rgbtBlue = avg;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < (width / 2); j++)
        {
            RGBTRIPLE tmp = image[i][j];

            image[i][j] = image[i][width - 1 - j];
            image[i][width - 1 - j] = tmp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE image_copy[height][width];
    for (int x = 0; x < height; x++)
    {
        for (int y = 0; y < width; y++)
        {
            image_copy[x][y] = image[x][y];
        }
    }

    // Loop through each pixel
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // For each pixel create a counter to cal new average
            float red = 0;
            float green = 0;
            float blue = 0;
            float counter = 0;

            // Create a loop & identify neighbouring pixels.
            for (int m = -1; m < 2; m++)
            {
                if ((i + m) >= 0 && (i + m) < height)
                {
                    for (int n = -1; n < 2; n++)
                    {
                        if ((j + n) >= 0 && (j + n) < width)
                        {
                            red += image_copy[i + m][j + n].rgbtRed;
                            green += image_copy[i + m][j + n].rgbtGreen;
                            blue += image_copy[i + m][j + n].rgbtBlue;
                            counter++;
                        }
                    }
                }
            }

            // Replace pixel with average pixel values of neighbouring pixels
            image[i][j].rgbtRed = round(red / counter);
            image[i][j].rgbtGreen = round(green / counter);
            image[i][j].rgbtBlue = round(blue / counter);
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    // Create 2x3 array templates that can be referencce to later
    int gxTemplate[3][3] = { {-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1} };
    int gyTemplate[3][3] = { {-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};

    RGBTRIPLE image_copy[height][width];
    for (int x = 0; x < height; x++)
    {
        for (int y = 0; y < width; y++)
        {
            image_copy[x][y] = image[x][y];
        }
    }

    // Loop through each pixel
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // For each pixel create a counter to cal new average
            int gxRed = 0;
            int gxGreen = 0;
            int gxBlue = 0;

            int gyRed = 0;
            int gyGreen = 0;
            int gyBlue = 0;

            // Create a loop & identify neighbouring pixels.
            for (int m = -1; m < 2; m++)
            {
                if ((i + m) >= 0 && (i + m) < height)
                {
                    for (int n = -1; n < 2; n++)
                    {
                        if ((j + n) >= 0 && (j + n) < width)
                        {
                            gxRed += image_copy[i + m][j + n].rgbtRed * gxTemplate[m + 1][n + 1];
                            gxGreen += image_copy[i + m][j + n].rgbtGreen * gxTemplate[m + 1][n + 1];
                            gxBlue += image_copy[i + m][j + n].rgbtBlue * gxTemplate[m + 1][n + 1];

                            gyRed += image_copy[i + m][j + n].rgbtRed * gyTemplate[m + 1][n + 1];
                            gyGreen += image_copy[i + m][j + n].rgbtGreen * gyTemplate[m + 1][n + 1];
                            gyBlue += image_copy[i + m][j + n].rgbtBlue * gyTemplate[m + 1][n + 1];
                        }
                    }
                }
            }

            // Replace pixel with average pixel values of neighbouring pixels
            float newRed = pow((pow(gxRed, 2) + pow(gyRed, 2)), 0.5);
            float newGreen = pow((pow(gxGreen, 2) + pow(gyGreen, 2)), 0.5);
            float newBlue = pow((pow(gxBlue, 2) + pow(gyBlue, 2)), 0.5);

            // Check whether value exceeds max pixel value of 225
            if (newRed > 255)
            {
                newRed = 255;
            }
            if (newGreen > 255)
            {
                newGreen = 255;
            }
            if (newBlue > 255)
            {
                newBlue = 255;
            }

            // Adjust pixels to new values
            image[i][j].rgbtRed =  round(newRed);
            image[i][j].rgbtGreen = round(newGreen);
            image[i][j].rgbtBlue = round(newBlue);
        }
    }
    return;
}
