#include <iostream>
#include <vector>

#include "asciize/render.hpp"

char ascii_ramp[71] = "$@B%8&WM#*oahkbdpqwmZO0QLCJUYXzcvunxrjft/\\|()1{}[]?-_+~<>i!lI;:,\"^`'. ";

char get_char(int luminance) {
    // Exclude the null terminator (\0) from character count
    int ramp_length = sizeof(ascii_ramp) - 1; // char is 1 byte

    int scaled_luminance = (int) ((float) luminance / 255.0 * ramp_length - 0.5);
    int luminance_index = ramp_length - scaled_luminance;

    return ascii_ramp[scaled_luminance];
}


void render(std::vector<std::vector<unsigned char>> luminance_matrix) {
    for (int row = 0; row < luminance_matrix.size(); row++) {
        for (int col = 0; col < luminance_matrix[row].size(); col++) {
            char ascii_char = get_char(luminance_matrix[row][col]);

            // Double output to get aspect ratio correct
            std::cout << ascii_char;
            std::cout << ascii_char;
        }
        std::cout << '\n';
    }
}