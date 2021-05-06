#include "helpers.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    // height loop
    for (int i = 0; i < height; i++)
    {
        // width loop
        for (int j = 0; j < width; j++)
        {
            float avrg = (image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / 3.0;

            int average = round(avrg);


            // Assigning the average between all RGB on the pixel
            image[i][j].rgbtBlue = average;
            image[i][j].rgbtRed = average;
            image[i][j].rgbtGreen = average;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    // height loop
    for (int i = 0; i < height; i++)
    {
        // width loop
        for (int j = 0; j < width; j++)
        {
            float sepiaRed = (0.393 * image[i][j].rgbtRed) + (0.769 * image[i][j].rgbtGreen) + (0.189 * image[i][j].rgbtBlue);
            float sepiaGreen = (0.349 * image[i][j].rgbtRed) + (0.686 * image[i][j].rgbtGreen) + (0.168 * image[i][j].rgbtBlue);
            float sepiaBlue = (0.272 * image[i][j].rgbtRed) + (0.534 * image[i][j].rgbtGreen) + (0.131 * image[i][j].rgbtBlue);

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

            image[i][j].rgbtRed = round(sepiaRed);
            image[i][j].rgbtGreen = round(sepiaGreen);
            image[i][j].rgbtBlue = round(sepiaBlue);
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp;
    // height loop
    for (int i = 0; i < height; i++)
    {
        // half width loop
        for (int j = 0; j < floor(width / 2); j++)
        {
            int reflected_index = (width - 1) - j;

            temp = image[i][reflected_index];
            image[i][reflected_index] = image[i][j];
            image[i][j] = temp;
        }
    }
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE tmp_image[height][width];
    int avrgRed = 0;
    int avrgGreen = 0;
    int avrgBlue = 0;

    int x_offset_array[10] = {-1, -1, -1, 0, 0, 0, 1, 1, 1};
    int y_offset_array[10] = {-1, 0, 1, -1, 0, 1, -1, 0, 1,};

    float neighbor_count = 0;

    // heigth loop
    for (int y = 0; y < height; y++)
    {
        // width loop
        for (int x = 0; x < width; x++)
        {
            float tmp_avrgRed = 0;
            float tmp_avrgGreen = 0;
            float tmp_avrgBlue = 0;
            neighbor_count = 0;

            // Neighbors sum
            for (int o = 0; o < 9; o++)
            {
                int x_offset = x + x_offset_array[o];
                int y_offset = y + y_offset_array[o];

                if (x_offset < 0 || x_offset >= width || y_offset < 0 || y_offset >= height)
                {
                    continue;
                }
                else
                {
                    tmp_avrgRed += image[y_offset][x_offset].rgbtRed;
                    tmp_avrgGreen += image[y_offset][x_offset].rgbtGreen;
                    tmp_avrgBlue += image[y_offset][x_offset].rgbtBlue;
                    neighbor_count++;
                }
            }
            tmp_image[y][x].rgbtRed = round(tmp_avrgRed / neighbor_count);
            tmp_image[y][x].rgbtGreen = round(tmp_avrgGreen / neighbor_count);
            tmp_image[y][x].rgbtBlue = round(tmp_avrgBlue / neighbor_count);
        }
    }
    // copying pixels into original image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = tmp_image[i][j];
        }
    }
}
