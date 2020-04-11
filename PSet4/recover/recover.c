#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Flow: open memory card, read JPEG file until the next and read everything

int main(int argc, char *argv[])
{
    // Check whether there are two or more conditions
    if (argc != 2)
    {
        printf("./recover key\n");
        return 1;
    }

    // Get user to key in file name and read file.
    FILE *file = fopen(argv[1], "r");
    if (!file)
    {
        printf("Unable to read raw file.\n");
        return 1;
    }

    // Assign variables
    int counter = 0;
    bool isjpeg = false;
    unsigned char *buffer = malloc(512);
    FILE *filepointer;
    char filename[8];

    // Read card and Loop through card
    while ((fread(buffer, 512, 1, file)) == 1)
    {
        // check whether new jpeg by checking first four bytes
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && ((buffer[3] & 0xf0) ==  0xe0))
        {
            // if first JPEG
            if (counter == 0)
            {
                isjpeg = true;
            }

            // If not first JPEG
            else
            {
                fclose(filepointer);
            }

            sprintf(filename, "%03i.jpg", counter);
            filepointer = fopen(filename, "w");
            fwrite(buffer, 512, 1, filepointer);
            counter++;

        }
        else
        {
            if (isjpeg)
            {
                fwrite(buffer, 512, 1, filepointer);
            }
        }
    }
    free(buffer);
    fclose(filepointer);
    fclose(file);
    return 0;
}
