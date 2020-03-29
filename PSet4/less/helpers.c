#include "helpers.h"
#include <math.h>
#include <stdio.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int avg = round(((float)image[i][j].rgbtRed + (float)image[i][j].rgbtGreen + (float)image[i][j].rgbtBlue) / 3);

            image[i][j].rgbtRed = avg;
            image[i][j].rgbtGreen = avg;
            image[i][j].rgbtBlue = avg;
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
            // Get sepia RGB color adjustments per pixel per color.
            int sepiaRed = round(.393 * image[i][j].rgbtRed + .769 * image[i][j].rgbtGreen + .189 * image[i][j].rgbtBlue);
            int sepiaGreen = round(.349 * image[i][j].rgbtRed + .686 * image[i][j].rgbtGreen + .168 * image[i][j].rgbtBlue);
            int sepiaBlue = round(.272 * image[i][j].rgbtRed + .534 * image[i][j].rgbtGreen + .131 * image[i][j].rgbtBlue);

            // Ensure that 8-bit color value for sepia RBG is 0 to 255 inclusive, ensure that conditions are non mutually exclusive
            if (sepiaRed > 255)
            {
                sepiaRed = 255;
            }
            if (sepiaGreen > 255)
            {
                sepiaGreen = 255;
            }
            if (sepiaBlue > 255)
            {
                sepiaBlue = 255;
            }

            image[i][j].rgbtRed = sepiaRed;
            image[i][j].rgbtGreen = sepiaGreen;
            image[i][j].rgbtBlue = sepiaBlue;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        // Only loop half of the image to avoid excess jobs. if width is odd, pixels in the middle row are unaffected by the swap.
        for (int j = 0; j < (width / 2); j++)
        {
            // store pixles in temp location
            RGBTRIPLE temp = image[i][j];
            image[i][j] = image[i][width - 1 - j];
            image[i][width - 1 - j] = temp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // Create a copy to retain RGB pixels at its original location.
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
