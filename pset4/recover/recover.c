#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define B 512

int main(int argc, char *argv[])
{
    typedef uint8_t BYTE;
    int image_counter = 0;

    char *filename = malloc(8);

    FILE *temp_image;

    // Initial arguments check
    if (argc != 2)
    {
        printf("Usage: ./recover image");
        return 1;
    }

    // Open File
    FILE *file = fopen(argv[1], "r");
    if (file == NULL)
    {
        printf("Cannot open forensic image");
        return 1;
    }

    // main loop that iterates the bytes of the .raw
    while (!feof(file))
    {
        BYTE buffer[B]; // Defining our buffer of 512 bytes
        int bytes_read = fread(buffer, 1, B,
                               file); // Storing that 512 bytes temporarily on the buffer and assigning the bytes read to a variable

        // Detecting when the last block is read
        if (bytes_read == 0)
        {
            break;
        }

        printf("%i", bytes_read);
        // Find a new JPG
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            if (image_counter == 0)
            {
                // Formatting the filename
                sprintf(filename, "%03i.jpg", image_counter);

                // Opening our temp_image for write mode
                temp_image = fopen(filename, "w");

                fwrite(buffer, 512, 1, temp_image);
                image_counter++;
            }
            else
            {
                // Same process as before, but closing the temp_image
                fclose(temp_image);

                // Formatting the filename
                sprintf(filename, "%03i.jpg", image_counter);

                // Opening our temp_image for write mode
                temp_image = fopen(filename, "w");

                fwrite(buffer, 512, 1, temp_image);
                image_counter++;
            }
        }
        else
        {
            if (temp_image)
            {
                fwrite(buffer, 512, 1, temp_image);
            }
        }

    }
    fclose(temp_image);
    free(filename);
    return 0;
}
