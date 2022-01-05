#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    // Check usage
    if (argc != 2)
    {
        printf("Usage: ./recover image\n");
        return 1;
    }

    FILE *file = fopen(argv[1], "r");
    if (file == NULL)
    {
        return 1;
    }

    BYTE buffer[512];
    char image_name[8];
    FILE *img = NULL;
    int number = 0;
    while (fread(buffer, 512, 1, file))
    {
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            //check if img is already open
            if (img != NULL)
            {
                fclose(img);
                number++;
            }
            sprintf(image_name, "%03i.jpg", number);
            img = fopen(image_name, "w");
            fwrite(&buffer, 512, 1, img);
        }
        else if (img != NULL)
        {
            fwrite(&buffer, 512, 1, img);
        }
    }
    fclose(img);
    fclose(file);
}
