#define STB_IMAGE_IMPLEMENTATION
#include <iostream>

#include <vector>
#include <string>

#include "stb/stb_image.h"
#include "asciize/get_luminance.hpp"

std::vector<std::vector<unsigned char>> get_luminance(const char *file_path) {
    int x, y, n;
    // x - width
    // y - height
    // n - channels (e.g. n=3 -> rgb)

    // set last arg (desired_channels) to 0 -> n will remain as-is and not be altered
    // if set to pos int, data will contain the number of channels specified
    unsigned char* data = stbi_load(file_path, &x, &y, &n, 3);
    // data is a pointer to the first element of an array of unsigned chars

    std::vector<std::vector<unsigned char>> luminance_matrix(y, std::vector<unsigned char>(x, 0));

    for (int row = 0; row < y; row++) {
        for (int col = 0; col < x; col++) {
            int index = (row * x + col) * 3;
            
            unsigned char pixel_luminance = (data[index] + data[index + 1] + data[index + 2]) / 3;

            luminance_matrix[row][col] = pixel_luminance;
        }   
    }


    stbi_image_free(data);

    return luminance_matrix;
}
