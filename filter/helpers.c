#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            int average = round((image[i][j].rgbtRed + image[i][j].rgbtBlue + image[i][j].rgbtGreen) / 3);
            image[i][j].rgbtBlue = average;
            image[i][j].rgbtGreen = average;
            image[i][j].rgbtRed = average;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for(int i = 0; i < height; i++){
        for(int j = 0; j < width; j++){
            int sepiaRed = round(0.393 * image[i][j].rgbtRed + 0.769 * image[i][j].rgbtGreen + 0.189 * image[i][j].rgbtBlue);
            int sepiaGreen = round(0.349 * image[i][j].rgbtRed + 0.686 * image[i][j].rgbtGreen + 0.168 * image[i][j].rgbtBlue);
            int sepiaBlue = round(0.272 * image[i][j].rgbtRed + 0.534 * image[i][j].rgbtGreen + 0.131 * image[i][j].rgbtBlue);

            if (sepiaRed > 255) {
                sepiaRed = 255;
            }
            if (sepiaGreen > 255) {
                sepiaGreen = 255;
            }
            if (sepiaBlue > 255) {
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
    for(int i = 0; i < height; i++) {
        for (int j = 0; j < width/2; j++) {
            RGBTRIPLE temp = image[i][j];
            image[i][j] = image[i][width - 1- j];
            image[i][width - 1- j] = temp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    for(int i = 0; i < height; i++){
        for(int j = 0; j < width; j++){
            int blurRed;
            int blurGreen;
            int blurBlue;
            if( i == 0 && j == 0) {
                blurRed = round((image[i+1][j].rgbtRed + image[i][j+1].rgbtRed + image[i+1][j+1].rgbtRed)/3);
                blurGreen = round((image[i+1][j].rgbtGreen + image[i][j+1].rgbtGreen + image[i+1][j+1].rgbtGreen)/3);
                blurBlue = round((image[i+1][j].rgbtBlue + image[i][j+1].rgbtBlue + image[i+1][j+1].rgbtBlue)/3);
            }
            else if(i == 0) {
                blurRed = round((image[i+1][j].rgbtRed + image[i][j+1].rgbtRed + image[i][j-1].rgbtRed + image[i+1][j+1].rgbtRed + image[i+1][j-1].rgbtRed)/5);
                blurGreen = round((image[i+1][j].rgbtGreen + image[i][j+1].rgbtGreen + image[i][j-1].rgbtGreen + image[i+1][j+1].rgbtGreen + image[i+1][j-1].rgbtGreen)/5);
                blurBlue = round((image[i+1][j].rgbtBlue + image[i][j+1].rgbtBlue + image[i][j-1].rgbtBlue + image[i+1][j+1].rgbtBlue + image[i+1][j-1].rgbtBlue)/5);
            }
            else if (j == 0) {
                blurRed = round((image[i+1][j].rgbtRed + image[i-1][j].rgbtRed + image[i][j+1].rgbtRed + image[i+1][j+1].rgbtRed + image[i-1][j+1].rgbtRed)/5);
                blurGreen = round((image[i+1][j].rgbtGreen + image[i-1][j].rgbtGreen + image[i][j+1].rgbtGreen + image[i+1][j+1].rgbtGreen + image[i-1][j+1].rgbtGreen)/5);
                blurBlue = round((image[i+1][j].rgbtBlue + image[i-1][j].rgbtBlue + image[i][j+1].rgbtBlue + image[i+1][j+1].rgbtBlue + image[i-1][j+1].rgbtBlue)/5);
            } else {
                blurRed = round((image[i+1][j].rgbtRed + image[i-1][j].rgbtRed + image[i][j+1].rgbtRed + image[i][j-1].rgbtRed + image[i+1][j+1].rgbtRed + image[i-1][j-1].rgbtRed + image[i+1][j-1].rgbtRed + image[i-1][j+1].rgbtRed)/8);
                blurGreen = round((image[i+1][j].rgbtGreen + image[i-1][j].rgbtGreen + image[i][j+1].rgbtGreen + image[i][j-1].rgbtGreen + image[i+1][j+1].rgbtGreen + image[i-1][j-1].rgbtGreen + image[i+1][j-1].rgbtGreen + image[i-1][j+1].rgbtGreen)/8);
                blurBlue = round((image[i+1][j].rgbtBlue + image[i-1][j].rgbtBlue + image[i][j+1].rgbtBlue + image[i][j-1].rgbtBlue + image[i+1][j+1].rgbtBlue + image[i-1][j-1].rgbtBlue + image[i+1][j-1].rgbtBlue + image[i-1][j+1].rgbtBlue)/8);
            }
            image[i][j].rgbtRed = blurRed;
            image[i][j].rgbtGreen = blurGreen;
            image[i][j].rgbtBlue = blurBlue;
        }
    }
    return;
}
