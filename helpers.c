#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    int i, j;
    float average;
    int assign;
    for (i = 0; i < height; i++)
    {
        for (j = 0; j < width; j++)
        {
            average = ((float)(image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed)) / 3;
            //image are integers hence need to typecast them before division otherwise result would be integer division
            assign = round(average);                               //assigning assign the value of average that is the grayscale value
            image[i][j].rgbtBlue = assign;                         //blue changed to grayscale
            image[i][j].rgbtGreen = assign;                        //green changed to grayscale
            image[i][j].rgbtRed = assign;                          //red changed to grayscale
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    int sepiaRed, sepiaGreen, sepiaBlue;
    float originalRed, originalGreen, originalBlue;
    int i, j;
    for (i = 0; i < height; i++)
    {
        for (j = 0; j < width; j++)
        {

            originalBlue = image[i][j].rgbtBlue;
            originalGreen = image[i][j].rgbtGreen;
            originalRed = image[i][j].rgbtRed;
            sepiaRed = round(.393 * originalRed + .769 * originalGreen + .189 * originalBlue);
            sepiaGreen = round(.349 * originalRed + .686 * originalGreen + .168 * originalBlue);
            sepiaBlue = round(.272 * originalRed + .534 * originalGreen + .131 * originalBlue);
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
            image[i][j].rgbtBlue = sepiaBlue;                                 //blue changed to sepia value
            image[i][j].rgbtGreen = sepiaGreen;                               //green changed to sepia value
            image[i][j].rgbtRed = sepiaRed;                                   //red changed to sepia value
        }
    }

    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    int i, j;
    int temp;
    for (i = 0; i < height; i++)
    {

        for (j = 0; j < (width /  2); j++)
        {
            temp = image[i][j].rgbtBlue;
            image[i][j].rgbtBlue = image[i][width - j - 1].rgbtBlue;
            image[i][width - j - 1].rgbtBlue = temp;
            temp = image[i][j].rgbtGreen;
            image[i][j].rgbtGreen = image[i][width - j - 1].rgbtGreen;
            image[i][width - j - 1].rgbtGreen = temp;
            temp = image[i][j].rgbtRed;
            image[i][j].rgbtRed = image[i][width - j - 1].rgbtRed;
            image[i][width - j - 1].rgbtRed = temp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    int i, j, k, l, counter;
    double averageB, averageG, averageR;
    long int sumB, sumG, sumR;
    RGBTRIPLE array[height][width];
    for (i = 0; i < height; i++)
    {
        for (j = 0; j < width; j++)
        {
            array[i][j].rgbtBlue = image[i][j].rgbtBlue;
            array[i][j].rgbtGreen = image[i][j].rgbtGreen;
            array[i][j].rgbtRed = image[i][j].rgbtRed;
        }
    }
    for (i = 0; i < height; i++)
    {
        for (j = 0; j < width; j++)
        {
            sumB = 0;
            sumG = 0;
            sumR = 0;
            if ((i > 0) && (j > 0) && (i < height - 1) && (j < width - 1))
            {
                for (k = -1; k <= 1; k++)
                {
                    for (l = -1; l <= 1; l++)
                    {
                        sumB += array[i + k][j + l].rgbtBlue;
                        sumG += array[i + k][j + l].rgbtGreen;
                        sumR += array[i + k][j + l].rgbtRed;
                    }
                }
                averageB = ((float)sumB / 9);
                averageG = ((float)sumG / 9);
                averageR = ((float)sumR / 9);
                image[i][j].rgbtBlue = round(averageB);
                image[i][j].rgbtGreen = round(averageG);
                image[i][j].rgbtRed = round(averageR);
            }
            else                                                       // ((i = 0) || (j = 0) || (i = height - 1) || (j = width - 1))
            {
                counter = 0;
                for (k = -1; k <= 1; k++)
                {
                    for (l = -1; l <= 1; l++)
                    {
                        if (((i + k) >= 0) && ((j + l) >= 0) && ((i + k) < height) && ((j + l) < width))
                        {
                            counter++;
                            sumB += array[i + k][j + l].rgbtBlue;
                            sumG += array[i + k][j + l].rgbtGreen;
                            sumR += array[i + k][j + l].rgbtRed;
                        }
                    }
                }
                averageB = ((float)sumB / counter);
                averageG = ((float)sumG / counter);
                averageR = ((float)sumR / counter);
                image[i][j].rgbtBlue = round(averageB);
                image[i][j].rgbtGreen = round(averageG);
                image[i][j].rgbtRed = round(averageR);
            }
        }
    }
    return;
}



























