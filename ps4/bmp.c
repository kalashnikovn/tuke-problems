#include "bmp.h"
#include <stdio.h>
#include <stdlib.h>


struct bmp_header* read_bmp_header(FILE* stream) {
    if (stream == NULL) {
        return NULL;
    }

    struct bmp_header* header = calloc(1, sizeof(struct bmp_header));
    if (header == NULL) {
        return NULL;
    }

    if (fread(header, sizeof(struct bmp_header), 1, stream) != 1) {
        free(header);
        return NULL;
    }

    if (header->type != 0x4D42) {
        free(header);
        return NULL;
    }

    if (header->offset != sizeof(struct bmp_header)) {
        free(header);
        return NULL;
    }

    if (header->dib_size != 40) {
        free(header);
        return NULL;
    }

    if (header->bpp != 24) {
        free(header);
        return NULL;
    }

    if (header->compression != 0) {
        free(header);
        return NULL;
    }

    if (header->height <= 0 || header->width <= 0) {
        free(header);
        return NULL;
    }

    return header;
}



struct pixel* read_data(FILE* stream, const struct bmp_header* header) {
    if (stream == NULL || header == NULL) {
        return NULL;
    }

    struct pixel* imagePixels = malloc(header->height * header->width * sizeof(struct pixel));
    if (imagePixels == NULL) {
        return NULL;
    }

    fseek(stream, header->offset, SEEK_SET);

    uint32_t padding = (4 - ((header->width * sizeof(struct pixel)) % 4)) % 4;

    for (uint32_t row = 0; row < header->height; row++) {
        for (uint32_t col = 0; col < header->width; col++) {
            fread(&imagePixels[(row * header->width) + col], sizeof(struct pixel), 1, stream);
        }

        fseek(stream, padding, SEEK_CUR);
    }

    return imagePixels;
}



struct bmp_image* read_bmp(FILE* stream) {
    if (stream == NULL) {
        fprintf(stderr, "Error: Null stream.\n");
        return NULL;
    }

    struct bmp_image* image = calloc(1, sizeof(struct bmp_image));
    if (image == NULL) {
        fprintf(stderr, "Error: Memory allocation failed.\n");
        return NULL;
    }

    image->header = read_bmp_header(stream);
    if (image->header == NULL) {
        fprintf(stderr, "Error: This is not a BMP file.\n");
        free_bmp_image(image);
        return NULL;
    }

    image->data = read_data(stream, image->header);
    if (image->data == NULL) {
        fprintf(stderr, "Error: Failed to read image data.\n");
        free_bmp_image(image);
        return NULL;
    }

    return image;
}


bool write_bmp (FILE* stream, const struct bmp_image* image) {
    if (stream == NULL || image == NULL || image->data == NULL) return false;

    fwrite(image->header, sizeof(struct bmp_header), 1, stream);

    uint32_t padding_size = (4 - (image->header->width * sizeof(struct pixel)) % 4) % 4;

    for (uint32_t row = 0; row < image->header->height; row++) {
        fwrite(&image->data[row * image->header->width], sizeof(struct pixel), image->header->width, stream);
        if (padding_size > 0) {
            uint8_t padding[3] = {0};
            fwrite(padding, padding_size, 1, stream);
        }
    }

    return true;
}



void free_bmp_image(struct bmp_image* image) {
    if (image == NULL) {
        return;
    }
    if (image->header != NULL) {
        free(image->header);
        image->header = NULL;
    }
    if (image->data != NULL) {
        free(image->data);
        image->data = NULL;
    }
    free(image);
    image = NULL;
}

