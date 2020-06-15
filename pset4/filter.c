#include "helpers.h"
#include <math.h>
#include <stdio.h>

// Convert image to grayscale

// 1) Find individual red, blue, green values for pixel
// 2) Calculate average pixel value from these three values
// 3) Set each RGB value to average value

void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
	// Iterate through rows of 2d pixel array
	for (int i = 0; i < height; i++)
	{
		// Iterate columns
		for (int j = 0; j < width; j++)
		{
			// Find int values for RGB values
			float red = image[i][j].rgbtRed;
			float green = image[i][j].rgbtGreen;
			float blue = image[i][j].rgbtBlue;
			
			// Calculate average color value
			float average = (blue + green + red) / 3;
			average = round(average);

			// Reassign RGB values to average value
			image[i][j].rgbtRed = average;
			image[i][j].rgbtGreen = average;
			image[i][j].rgbtBlue = average;
		}
	}
    return;
}

// Convert image to sepia

// 1) Find individual red, blue, green values for pixel
// 2) Calculate sepia pixel values from these three values
// 3) Set each RGB value to sepia values

void sepia(int height, int width, RGBTRIPLE image[height][width])
{
	// Iterate through rows of 2d pixel array
	for (int i = 0; i < height; i++)
	{
		// Iterate through columns
		for (int j = 0; j < width; j++)
		{
			// Find int values for RGB values
			float red = image[i][j].rgbtRed;
			float green = image[i][j].rgbtGreen;
			float blue = image[i][j].rgbtBlue;

			// Calculate Sepia values
			int sepiaRed = round(.393 * red + .769 * green + .189 * blue);
  			int sepiaGreen = round(.349 * red + .686 * green + .168 * blue);
  			int sepiaBlue = round(.272 * red + .534 * green + .131 * blue);

  			// If Sepia value exceeds 255, cap it at 255
  			// Assign pixel to Sepia value
  			if (sepiaRed < 256)
  			{
  				image[i][j].rgbtRed = sepiaRed;
  			}
  			else
  			{
  				image[i][j].rgbtRed = 255;
  			}
  			if (sepiaGreen < 256)
  			{
  				image[i][j].rgbtGreen = sepiaGreen;
  			}
  			else
  			{
  				image[i][j].rgbtGreen = 255;
  			}
  			if (sepiaBlue < 256)
  			{
  				image[i][j].rgbtBlue = sepiaBlue;
  			}
  			else
  			{
  				image[i][j].rgbtBlue= 255;
  			}
		}
	}
    return;
}

// Reflect image horizontally

// 1) Iterate through rows of pixels
// 2) Swap elements by taking current element and popping it to end of array minus iterator
//    to produce this:
// 		[1,2,3,4,5,6]
// 		[6,5,4,3,2,1]
// 

void reflect(int height, int width, RGBTRIPLE image[height][width])
{
	// Iterate through rows of 2d pixel array
	for (int i = 0; i < height; i++)
	{
		// Iterate through columns
		for (int j = 0; j < width/2; j++)
		{
			// Use variable temp as a placeholder for swapping elements
			RGBTRIPLE temp;

			temp = image[i][j];
			image[i][j] = image[i][width-j];
			image[i][width-j] = temp;
		}
	}
    return;
}

// Blur image

// 1. Identify neighboring pixel pattern
// 2. Calculate average RGB value of pattern
// 3. Set each neighboring pixel value to average

void blur(int height, int width, RGBTRIPLE image[height][width])
{  
	// Iterate through rows of 2d pixel array
    for (int i = 0; i < height; i++) // goes over entire image i for rows (height), j for columns (width)
    {
    	// Iterate through columns
        for (int j = 0; j < width; j++)
        {
        	// Initialize sum values for rgbt values per byte
            float sumRed = 0;
            float sumGreen = 0;
            float sumBlue = 0;

            // Initialize variable for counting how many pixels are adjacent to current pixel
            int pixelCount = 0;
           
           	// In the example below (Figure 1), x is surrounded by neighboring pixels 1-9
           	// Refer to this map for help visualizing the conditional statements below
            // [1][2][3]
            // [4][x][6]
            // [7][8][9] 

            // First check each pixel within -1 and +1 of each [i] (ie left to right)
            for (int k = -1; k < 2; k++)
            {

            	// Secondly check each pixel within -1 to +1 of each [j] (ie up to down)
                for (int l = -1; l < 2; l++)
                {
                	// Find neighboring pixels and eliminate edge cases:
                	// (ie, pixels that don't exist if selected pixel is in topmost/bottom rows, leftmost/right columns)
                	// In order from left to right of conditional statement:
                	// 1) Does pixel [4] (Fig. 1) exist? 
                	// 2) Does [2] exist?
                	// 3) Does [8] exist?
                	// 4) Does [6] exist?

                    if (i + k >= 0  && j + l >= 0 && i + k <= height - 1 && j + l <= width - 1) // if statement to check
                    {                                       
                        // If pixel is within bounds, calculate surrounding pixels' rgbt values and add to sum
                        sumRed = image[i+k][j+l].rgbtRed + sumRed;                           
                        sumGreen = image[i+k][j+l].rgbtGreen + sumGreen;
                        sumBlue = image[i+k][j+l].rgbtBlue + sumBlue;
                        // Adds +1 to the pixel count to divide by within each [i][j] loop
                        pixelCount++; 
                    }
                }
            }
            // Assign pixel the average rgbt values
            image[i][j].rgbtRed = round(sumRed / pixelCount);
            image[i][j].rgbtGreen = round(sumGreen / pixelCount);
            image[i][j].rgbtBlue = round(sumBlue / pixelCount);
        }
    }
    return;
}
