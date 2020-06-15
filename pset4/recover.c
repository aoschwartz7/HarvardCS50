#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


// Create block size and byte instances
// Check that user entered one command-line argument only
// Open file to be recovered
// Using while loop, read block on memory card (file)
// Break loop when we reach end of file
// Check for JPEG start sequence
// Write block to file
// Repeat until end of file
// Close new file and name it "###.jpg"





#define BLOCK_SIZE 512
typedef uint8_t BYTE;




int main(int argc, char *argv[])
{
	// Check for single command-line argument
	if (argc != 2)
	{
		printf("Usage: recover [filename]\n");
		return 1;
	}

	// Remember file name
	char *infile = argv[1];

	// Open file
	FILE *inptr = fopen(infile, "r");

	if (!inptr)
	{
		printf("Could not open %s.\n", infile);
		return 2;
	}

	// Initialize 512 byte block size for buffering
	BYTE buffer[512];

	// Initialize imageCount for file naming
	int imageCount = 0;

	// Create fileName instance for output file
	char fileName[8];

	// Set outfile to null
	FILE *outptr = NULL;

// Create while loop to find and store JPEGs from memory card file
    while (1)
    {
        // Read a 512 byte block of the memory card image
        size_t bytesRead = fread(buffer, sizeof(BYTE), BLOCK_SIZE, inptr);

        // Break out of the loop when we reach the end of the card image
        if (bytesRead == 0 && feof(inptr))
        {
            break;
        }

        // Check if we found a JPEG by looking for signature header sequence
        bool containsJpegHeader = buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0;

        // If we found another JPEG, we must close the previous file
        if (containsJpegHeader && outptr != NULL)
        {
            fclose(outptr);
            imageCount++;
        }

        // If we found a JPEG, we need to open a new file for writing
        if (containsJpegHeader)
        {
            sprintf(fileName, "%03i.jpg", imageCount);
            outptr = fopen(fileName, "w");
        }

        // Write to file anytime we have an open file
        if (outptr != NULL)
        {
            fwrite(buffer, sizeof(BYTE), bytesRead, outptr);
        }
    }

    // Close last jpeg file
    fclose(outptr);

    // Close infile
    fclose(inptr);

    // Success
    return 0;
}
