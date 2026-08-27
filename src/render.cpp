#include <iostream>
#include <vector>

#include "asciize/render.hpp"
#include "asciize/AsciiRampLength.hpp"

char ASCII_RAMP_LONG[71] = "$@B%8&WM#*oahkbdpqwmZO0QLCJUYXzcvunxrjft/\\|()1{}[]?-_+~<>i!lI;:,\"^`'. ";
char ASCII_RAMP_STANDARD[29] = "@#W$9876543210?!abc;:+=-,._ ";
char ASCII_RAMP_SHORT[11] = "@%#*+=-:. ";


char get_char(int luminance, AsciiRampLength ramp_length_enum) {
    const char* ascii_ramp = nullptr;
    int ramp_len = 0;

    switch (ramp_length_enum) {
        case SHORT:
            ascii_ramp = ASCII_RAMP_SHORT;
            ramp_len = sizeof(ASCII_RAMP_SHORT) - 1; // Exclude '\0'
            break;
        case STANDARD:
            ascii_ramp = ASCII_RAMP_STANDARD;
            ramp_len = sizeof(ASCII_RAMP_STANDARD) - 1; // Exclude '\0'
            break;
        case LONG:
            ascii_ramp = ASCII_RAMP_LONG;
            ramp_len = sizeof(ASCII_RAMP_LONG) - 1; // Exclude '\0'
            break;
    }

    // Exclude the null terminator (\0) from character count
    int ramp_length = sizeof(ascii_ramp) - 1; // char is 1 byte

    int scaled_luminance = (int) ((float) luminance / 255.0 * ramp_length + 0.5);
    int luminance_index = ramp_length - scaled_luminance;

    return ascii_ramp[scaled_luminance];
}


void render(std::vector<std::vector<unsigned char>> luminance_matrix, AsciiRampLength ramp_length) {
    for (int row = 0; row < luminance_matrix.size(); row++) {
        for (int col = 0; col < luminance_matrix[row].size(); col++) {
            char ascii_char = get_char(luminance_matrix[row][col], ramp_length);

            // Double output to get aspect ratio correct
            std::cout << ascii_char;
            std::cout << ascii_char;
        }
        std::cout << '\n';
    }
}