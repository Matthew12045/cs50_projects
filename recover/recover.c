#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define BLOCK 512

typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    // Accept a single command-line argument

    if (argc != 2)
    {
        printf("Usage: ./recover FILE\n");
        return 1;
    }

    // Open the memory card

    FILE *card = fopen(argv[1], "r");
    if (card == NULL)
    {
        printf("Could not open file\n");
        return 1;
    }

    // Create a buffer for a block of data

    BYTE buffer[BLOCK];

    // While there's still data left to read from the memory card
    // Set img pointer to NULL
    char filename[8];
    FILE *img = NULL;
    int jpgName = 0;

    while (fread(buffer, 1, BLOCK, card) == BLOCK)
    {
        // Create JPEGs from the data
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff &&
            (buffer[3] & 0xf0) == 0xe0)
        {
            // Close the previous JPEG file if it exists
            if (img != NULL)
            {
                fclose(img);
            }
            // Create a new filename for the JPEG
            sprintf(filename, "%03i.jpg", jpgName);

            // Open a new JPEG file
            img = fopen(filename, "w");
            if (img == NULL)
            {
                printf("Could not create output JPEG file\n");
                return 1;
            }
            // increment the jpeg name
            jpgName++;
        }

        // Keep writing if new jpeg file is not found
        if (img != NULL)
        {
            fwrite(buffer, BLOCK, 1, img);
        }
    }

    // Close any remaining open files
    if (img != NULL)
    {
        fclose(img);
    }

    // Close the memory card file
    fclose(card);

    return 0;
}
