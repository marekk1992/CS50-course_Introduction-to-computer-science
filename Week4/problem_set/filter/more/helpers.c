#include "helpers.h"
#include <math.h>

//Prototype
int check_limit(int pixel_value);

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    int shade_of_grey;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            shade_of_grey = round((image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3.0);
            image[i][j].rgbtBlue = shade_of_grey;
            image[i][j].rgbtGreen = shade_of_grey;
            image[i][j].rgbtRed = shade_of_grey;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        int index_of_last_pixel_in_row = width - 1;
        for (int j = 0; j <= index_of_last_pixel_in_row; j++)
        {
            RGBTRIPLE temporary = image[i][j];
            image[i][j] = image[i][index_of_last_pixel_in_row];
            image[i][index_of_last_pixel_in_row] = temporary;
            index_of_last_pixel_in_row--;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    int new_Red[height][width];
    int new_Green[height][width];
    int new_Blue[height][width];

    for (int column_index = 0; column_index < height; column_index++)
    {
        for (int row_index = 0; row_index < width; row_index++)
        {
            int divider = 0;
            float Red_sum = 0;
            float Green_sum = 0;
            float Blue_sum = 0;

            for (int i = -1; i <= 1 && column_index + i < height; i++)
            {
                for (int j = -1; j <= 1 && row_index + j < width; j++)
                {
                    if (column_index + i >= 0 && row_index + j >= 0)
                    {
                        Red_sum = Red_sum + image[column_index + i][row_index + j].rgbtRed;
                        Green_sum = Green_sum + image[column_index + i][row_index + j].rgbtGreen;
                        Blue_sum = Blue_sum + image[column_index + i][row_index + j].rgbtBlue;
                        divider++;
                    }
                }
            }
            new_Red[column_index][row_index] = round(Red_sum / divider);
            new_Green[column_index][row_index] = round(Green_sum / divider);
            new_Blue[column_index][row_index] = round(Blue_sum / divider);
        }
    }
    for (int n = 0; n < height; n++)
    {
        for (int m = 0; m < width; m++)
        {
            image[n][m].rgbtRed = new_Red[n][m];
            image[n][m].rgbtGreen = new_Green[n][m];
            image[n][m].rgbtBlue = new_Blue[n][m];
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    int new_Red[height][width];
    int new_Green[height][width];
    int new_Blue[height][width];
    
    //Create two dimensional array Gx & Gy
    int Gx_kernel[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int Gy_kernel[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};

    for (int column_index = 0; column_index < height; column_index++)
    {
        for (int row_index = 0; row_index < width; row_index++)
        {
            // Calculate Gx & Gy values for all pixels
            float Red_Gx = 0;
            float Green_Gx = 0;
            float Blue_Gx = 0;
            float Red_Gy = 0;
            float Green_Gy = 0;
            float Blue_Gy = 0;
            
            for (int i = -1; i <= 1 && column_index + i < height; i++)
            {
                for (int j = -1; j <= 1 && row_index + j < width; j++)
                {
                    if (column_index + i >= 0 && row_index + j >= 0)
                    {
                        Red_Gx = Red_Gx + Gx_kernel[i + 1][j + 1] * image[column_index + i][row_index + j].rgbtRed;
                        Green_Gx = Green_Gx + Gx_kernel[i + 1][j + 1] * image[column_index + i][row_index + j].rgbtGreen;
                        Blue_Gx = Blue_Gx + Gx_kernel[i + 1][j + 1] * image[column_index + i][row_index + j].rgbtBlue;
                        Red_Gy = Red_Gy + Gy_kernel[i + 1][j + 1] * image[column_index + i][row_index + j].rgbtRed;
                        Green_Gy = Green_Gy + Gy_kernel[i + 1][j + 1] * image[column_index + i][row_index + j].rgbtGreen;
                        Blue_Gy = Blue_Gy + Gy_kernel[i + 1][j + 1] * image[column_index + i][row_index + j].rgbtBlue;
                    }
                }
            }
            new_Red[column_index][row_index] = check_limit(round(sqrt(Red_Gx * Red_Gx + Red_Gy * Red_Gy)));
            new_Green[column_index][row_index] = check_limit(round(sqrt(Green_Gx * Green_Gx + Green_Gy * Green_Gy)));
            new_Blue[column_index][row_index] = check_limit(round(sqrt(Blue_Gx * Blue_Gx + Blue_Gy * Blue_Gy)));
        }
    }
    for (int column_index = 0; column_index < height; column_index++)
    {
        for (int row_index = 0; row_index < width; row_index++)
        {
            image[column_index][row_index].rgbtRed = new_Red[column_index][row_index];
            image[column_index][row_index].rgbtGreen = new_Green[column_index][row_index];
            image[column_index][row_index].rgbtBlue = new_Blue[column_index][row_index];
        }
    }
    return;
}

int check_limit(int pixel_value)
{
    if (pixel_value > 255)
    {
        return 255;
    }
    return pixel_value;
}
