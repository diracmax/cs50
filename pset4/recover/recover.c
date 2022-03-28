#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint8_t BYTE;

const int BLOCK_SIZE = 512;
const int JPEG_SIGNATURE_SIZE = 4;

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        return 1;
    }

    FILE *file = fopen(argv[1], "r");
    if (!file)
    {
        return 1;
    }

    /*int count = 0;

    char filename[20];

    while (count <= 50)
    {
        BYTE block[BLOCK_SIZE - JPEG_SIGNATURE_SIZE];
        BYTE is_jpeg_signature[JPEG_SIGNATURE_SIZE];
        fread(is_jpeg_signature, sizeof(uint8_t), JPEG_SIGNATURE_SIZE, file);
        fread(block, sizeof(uint8_t), BLOCK_SIZE - JPEG_SIGNATURE_SIZE, file);
        if (is_jpeg_signature[0] == 0xff && is_jpeg_signature[1] == 0xd8 && is_jpeg_signature[2] == 0xff && is_jpeg_signature[3] & 0xf0 == 0xe0)
        {
            if (count != 0)
            {
                fclose(output);
            }
            count++;
            sprintf(filename, "%03i.jpg", count - 1);
            FILE *img = fopen(filename, 'w');
            output = fopen(filename, "w");
            fwrite(block, sizeof(uint8_t), BLOCK_SIZE - JPEG_SIGNATURE_SIZE, output);
        }
        else
        {
            if (fopen(output))
            {
                fwrite(is_jpeg_signature, sizeof(uint8_t), JPEG_SIGNATURE_SIZE, output);
                fwrite(block, sizeof(uint8_t), BLOCK_SIZE - JPEG_SIGNATURE_SIZE, output);
            }
        }
    }
    */

    int count = 0;
    char filename[20];
    BYTE buffer[BLOCK_SIZE];
    FILE *img;

    while (1)
    {
        if (fread(buffer, sizeof(BYTE), BLOCK_SIZE, file) != BLOCK_SIZE)
        {
            fclose(img);
            break;
        }
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            if (count != 0)
            {
                fclose(img);
            }
            sprintf(filename, "%03i.jpg", count);
            img = fopen(filename, "w");
            fwrite(buffer, sizeof(BYTE), BLOCK_SIZE, img);
            count++;
        }
        else
        {
            if (count != 0)
            {
                fwrite(buffer, sizeof(BYTE), BLOCK_SIZE, img);
            }
        }
    }


    fclose(file);
}