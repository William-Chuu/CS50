#include "helpers.h"
#include <math.h>
//need this for boolean data type
#include <stdbool.h>


// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int j = 0; j < height; j++)
    {
        for (int i = 0; i < width; i++)
        {
            //average of 3 colour bytes (for integers, will round down if get decimal)
            int avg = round(((float)image[j][i].rgbtBlue + (float)image[j][i].rgbtRed + (float)image[j][i].rgbtGreen) / 3);
            //set every colour in each pixel to the average
            image[j][i].rgbtBlue = avg;
            image[j][i].rgbtRed = avg;
            image[j][i].rgbtGreen = avg;
        }
    }

    return;
}

//given 2 empty pointers, swap inputs
void swap(RGBTRIPLE *pixel1, RGBTRIPLE *pixel2)
{
    //make temp equal to whatever pixel1 is point to (first input of function)
    RGBTRIPLE temp = *pixel1;
    //make box that pixel1 is pointing to equal to what pixel2 is pointing to (second input of function)
    *pixel1 = *pixel2;
    //make what pixel2 is pointing to equal to temp
    *pixel2 = temp;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int j = 0; j < height; j++)
    {
        //dividing integer by 2 will always round down SO will already take into account odd or even
        for (int i = 0; i < width / 2; i++)
        {
            //minus 1 since start at 0 and minus i to change to corrent value every loop
            //remember need the ampersand since inputting an address
            swap(&image[j][i], &image[j][width - 1 - i]);
        }
    }
    return;
}

//check to see if valid pixel (not outside of frame)
bool valid_pixel(int new_i, int new_j, int width, int height)
{
    //valid pixel is greater than 0 and within boundaries (height and width)
    if (new_i >= 0 && new_i < height && new_j >= 0 && new_j < width)
    {
        return true;
    }
    return false;
}

RGBTRIPLE get_blur(int i, int j, int width, int height, RGBTRIPLE image[height][width])
{
    //returns a data-type RGBTRIPLE (1 blurred pixel)
    RGBTRIPLE blurred_pixel;
    //to figure out what to divide by to get avg
    int valid_pixel_counter = 0;
    //total red values, blue values, green values
    int red_value, green_value, blue_value;
    red_value = green_value = blue_value = 0;

    //these 2 for loops used to go through grid of 3x3 (what we use to blur)
    for (int di = -1; di <= 1; di++)
    {
        for (int dj = -1; dj <= 1; dj++)
        {
            //new spot in array just add the difference
            int new_j = j + dj;
            int new_i = i + di;
            //see if pixel is in the picture
            if (valid_pixel(new_i, new_j, width, height))
            {
                valid_pixel_counter++;
                red_value += image[new_i][new_j].rgbtRed;
                green_value += image[new_i][new_j].rgbtGreen;
                blue_value += image[new_i][new_j].rgbtBlue;
            }
        }
    }

    blurred_pixel.rgbtRed = round((float)red_value / valid_pixel_counter);
    blurred_pixel.rgbtGreen = round((float)green_value / valid_pixel_counter);
    blurred_pixel.rgbtBlue = round((float)blue_value / valid_pixel_counter);

    return blurred_pixel;

}

// "box" Blur image - average of pixels around original pixel
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    //creating a copy of the image since we need to find average of original pixels
    RGBTRIPLE new_image[height][width];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            //input image into function to slowly input blurred pixels into empty new_image array
            new_image[i][j] = get_blur(i, j, width, height, image);
        }
    }

    //copy this newly blurred image to the main image
    for (int w = 0; w < height; w++)
    {
        for (int c = 0; c < width; c++)
        {
            image[w][c] = new_image[w][c];
        }
    }

    return;
}

//see if out of border
bool inbounds(int new_i, int new_j, int height, int width)
{
    if (new_i >= 0 && new_i < height && new_j >= 0 && new_j < width)
    {
        return true;
    }

    return false;
}

//return SobelPixel
RGBTRIPLE get_SobelPixel(int i, int j, int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE SobelPixel;
    int Gx, Gy, inc_x, inc_y, sumGx_Red, sumGx_Blue, sumGx_Green, sumGy_Red, sumGy_Blue, sumGy_Green;
    Gx = Gy = inc_x = inc_y = sumGx_Red = sumGx_Blue = sumGx_Green = sumGy_Red = sumGy_Blue = sumGy_Green = 0;

    //represents the rows
    for (int di = -1; di <= 1; di++)
    {
        //sets the value of Gx depending on which row it is in
        if (di == 0)
        {
            Gx = -2;
            inc_x = 2;
            Gy = 0;
            inc_y = 0;
        }
        else if (di == -1)
        {
            Gx = -1;
            inc_x = 1;
            Gy = -1;
            inc_y = 1;
        }
        else
        {
            Gx = -1;
            inc_x = 1;
            Gy = 1;
            inc_y = -1;
        }
        //represents the columns
        for (int dj = -1; dj <= 1; dj++)
        {
            int new_i = i + di;
            int new_j = j + dj;

            if (inbounds(new_i, new_j, height, width))
            {
                sumGx_Red += (image[new_i][new_j].rgbtRed * Gx);
                sumGx_Green += (image[new_i][new_j].rgbtGreen * Gx);
                sumGx_Blue += (image[new_i][new_j].rgbtBlue * Gx);

                sumGy_Red += (image[new_i][new_j].rgbtRed * Gy);
                sumGy_Green += (image[new_i][new_j].rgbtGreen * Gy);
                sumGy_Blue += (image[new_i][new_j].rgbtBlue * Gy);
            }

            //adjusts Gx & Gy to next value
            Gx += inc_x;
            inc_y = (inc_y * -1);
            Gy += inc_y;
        }

    }

    int RedPixel  = round((float)sqrt(pow(sumGx_Red, 2) + pow(sumGy_Red, 2)));
    int BluePixel = round((float)sqrt(pow(sumGx_Blue, 2) + pow(sumGy_Blue, 2)));
    int GreenPixel = round((float)sqrt(pow(sumGx_Green, 2) + pow(sumGy_Green, 2)));

    //make sure channel value not greater than 255
    if (RedPixel > 255)
    {
        RedPixel = 255;
    }
    else if (BluePixel > 255)
    {
        BluePixel = 255;
    }
    else if (GreenPixel > 255)
    {
        GreenPixel = 255;
    }

    SobelPixel.rgbtRed = RedPixel;
    SobelPixel.rgbtBlue = BluePixel;
    SobelPixel.rgbtGreen = GreenPixel;

    return SobelPixel;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    //copy of image since we need to find Gx, Gy of orginal pixels
    RGBTRIPLE new_image[height][width];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            //input image pixel into function to get each pixels edge
            new_image[i][j] = get_SobelPixel(i, j, height, width, image);
        }
    }

    //copy this newly edged image to the main image
    for (int w = 0; w < height; w++)
    {
        for (int c = 0; c < width; c++)
        {
            image[w][c] = new_image[w][c];
        }
    }

    return;
}
