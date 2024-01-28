#include "bmp.h"
#include <stdlib.h>
#include <math.h>
#include <string.h>



struct bmp_header* copy_header(const struct bmp_header* toCopy)
{
    if (toCopy == NULL) {
        return NULL;
    }

    struct bmp_header* header = malloc(sizeof(struct bmp_header));
    if (header == NULL) {
        return NULL;
    }

    memcpy(header, toCopy, sizeof(struct bmp_header));

    return header;
}


struct pixel* copy_pixels(const struct pixel* to_copy, const long num_pixels)
{
    struct pixel* copied_pixels = malloc(num_pixels * sizeof(struct pixel));

    for (int i = 0; i < num_pixels; ++i)
    {
        copied_pixels[i].red   = to_copy[i].red;
        copied_pixels[i].green = to_copy[i].green;
        copied_pixels[i].blue  = to_copy[i].blue;
    }

    return copied_pixels;
}


struct bmp_image* flip_horizontally(const struct bmp_image* image) {
    if (!image || !image->data || !image->header) {
        return NULL;
    }

    struct bmp_image* result = malloc(sizeof(struct bmp_image));
    if (!result) {
        return NULL;
    }

    result->header = copy_header(image->header);
    result->data = copy_pixels(image->data, image->header->height * image->header->width);
    if (!result->data) {
        free(result->header);
        free(result);
        return NULL;
    }

    size_t image_width = image->header->width;
    size_t image_height = image->header->height;

    for (size_t row = 0; row < image_height; row++) {
        for (size_t col = 0; col < image_width; col++) {
            result->data[row * image_width + col] = image->data[row * image_width + image_width - col - 1];
        }
    }

    return result;
}




struct bmp_image* flip_vertically(const struct bmp_image* img) {
    if (!img || !img->data || !img->header) {
        return NULL;
    }

    struct bmp_image* res = malloc(sizeof(*res));
    if (!res) {
        return NULL;
    }

    res->header = copy_header(img->header);
    res->data = copy_pixels(img->data, img->header->height * img->header->width);
    if (!res->data) {
        free(res->header);
        free(res);
        return NULL;
    }

    size_t width = img->header->width;
    size_t height = img->header->height;

    for (size_t i = 0; i < height; i++) {
        for (size_t j = 0; j < width; j++) {
            res->data[i * width + j] = img->data[(height - 1 - i) * width + j];
        }
    }

    return res;
}




struct bmp_image* rotate_right(const struct bmp_image* img) {
    if (img == NULL || img->data == NULL || img->header == NULL) {
        return NULL;
    }

    struct bmp_image* result = malloc(sizeof(struct bmp_image));
    if (result == NULL) return NULL;

    result->header = copy_header(img->header);
    result->header->width = img->header->height;
    result->header->height = img->header->width;

    int paddedWidth = (result->header->width * result->header->bpp + 31) / 32 * 4;
    int imageSize = paddedWidth * result->header->height;

    result->header->image_size = imageSize;
    result->header->size = imageSize + result->header->offset;

    result->data = malloc(imageSize);
    if (result->data == NULL) {
        free(result);
        return NULL;
    }

    int rowSize = result->header->width * result->header->bpp / 8;
    int paddedRowSize = paddedWidth * result->header->bpp / 8;

    for (int y = 0; y < result->header->height; y++) {
        for (int x = 0; x < result->header->width; x++) {
            int srcIndex = (img->header->height - x - 1) * rowSize + y * paddedWidth;
            int dstIndex = y * paddedRowSize + x * result->header->bpp / 8;
            memcpy(result->data + dstIndex, img->data + srcIndex, result->header->bpp / 8);
        }
    }

    return result;
}






struct bmp_image* rotate_left(const struct bmp_image* input_image)
{
    if (input_image == NULL || input_image->data == NULL || input_image->header == NULL) {
        return NULL;
    }

    struct bmp_image* output_image = malloc(sizeof(struct bmp_image));
    if (output_image == NULL) {
        return NULL;
    }

    output_image->header = copy_header(input_image->header);
    output_image->header->width = input_image->header->height;
    output_image->header->height = input_image->header->width;
    output_image->header->image_size = ((output_image->header->width * input_image->header->bpp + 31) / 32) * 4 * output_image->header->height;
    output_image->header->size = output_image->header->image_size + output_image->header->offset;

    output_image->data = calloc(output_image->header->height * output_image->header->width, sizeof(struct pixel));
    if (output_image->data == NULL) {
        free(output_image);
        return NULL;
    }

    for (int i = 0; i < input_image->header->width; ++i) {
        for (int j = 0; j < input_image->header->height; ++j) {
            output_image->data[((output_image->header->width - i - 1) * output_image->header->height) + j] = input_image->data[(j * input_image->header->width) + i];
        }
    }

    return output_image;
}






