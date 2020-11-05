#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define BLOCKSIZE 512

int usage(void);

int card_check(void);

int main(int argc, char *argv[])
{

    //proper input
    if (argc != 2)
    {
        return usage();
    }

    if (argv[1] == NULL)
    {
        return usage();
    }

    //open file inputed
    FILE *SDcard = fopen(argv[1], "r");

    if (SDcard == NULL)
    {
        return card_check();
    }

    unsigned char buffer[BLOCKSIZE];
    int jpeg_counter = 0;
    //creating a filename string of 8 characters xxx.jpeg\0
    char filename[8];
    //creating file to input jpeg
    FILE *new_jpeg;

    //reading each block of 512 bytes from SDcard
    while (fread(buffer, BLOCKSIZE, 1, SDcard) == 1)
    {
        //if start of jpeg
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && ((buffer[3] & 0xf0) == 0xe0))
        {
            //if first jpeg in SDcard
            if (jpeg_counter == 0)
            {
                jpeg_counter = 1;
            }

            //not first jpeg found
            else
            {
                fclose(new_jpeg);
                jpeg_counter += 1;

            }

            //writing to a string called "filename" the new jpeg name
            sprintf(filename, "%03i.jpg", jpeg_counter - 1);

            //creating new jpeg file by opening it with the string name we just created and wanting to write to it
            new_jpeg = fopen(filename, "w");

            //writing first block to new jpeg image from the SDcard
            fwrite(buffer, BLOCKSIZE, 1, new_jpeg);
        }

        //only runs after first jpeg detected
        else if (jpeg_counter > 0)
        {
            //keep writing to new jpeg
            fwrite(buffer, BLOCKSIZE, 1, new_jpeg);
        }

    }

    //close files
    fclose(new_jpeg);
    fclose(SDcard);

    return 0;
}

int usage(void)
{
    printf("Usage: ./recover image\n");
    return 1;
}

int card_check(void)
{
    printf("Nothing in file\n");
    return 1;
}