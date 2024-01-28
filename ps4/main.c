#include <stdio.h>
#include <stdlib.h>
#include "bmp.h"
#include "transformations.h"
#include <math.h>

int main()
{

    FILE * file = fopen("file.bmp", "rb");
    if (file == NULL) return 1;

    FILE * output = fopen("output.bmp", "wb");
    if (output == NULL) {
        fclose(file);
        return 1;
    }


    struct bmp_image* image = read_bmp(file);

    struct bmp_image* rotated_right = rotate_right(image);
    struct bmp_image* rotated_left = rotate_left(image);
    struct bmp_image* fpliiped_v = flip_vertically(image);
    struct bmp_image* flipped_h = flip_horizontally(image);

    write_bmp(output, fpliiped_v);


    free_bmp_image(image);
    free_bmp_image(rotated_right);
    free_bmp_image(rotated_left);
    free_bmp_image(fpliiped_v);
    free_bmp_image(flipped_h);


    fclose(file);
    fclose(output);

    return 0;
}