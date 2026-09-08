#include <iostream>
#include <vector>
#include <string>
#include <cmath>

#include "asciize/render.hpp"
#include "asciize/AsciiRampLength.hpp"

char ASCII_RAMP_LONG[71] = "$@B%8&WM#*oahkbdpqwmZO0QLCJUYXzcvunxrjft/\\|()1{}[]?-_+~<>i!lI;:,\"^`'. ";
char ASCII_RAMP_STANDARD[29] = "@#W$9876543210?!abc;:+=-,._ ";
char ASCII_RAMP_SHORT[11] = "@%#*+=-:. ";


struct ColourMap {
    std::string esc_code;
    unsigned char r;
    unsigned char g;
    unsigned char b;
};

std::vector<ColourMap> esc_codes = {
    {"\033[0;30m", 0, 0, 0}, // Black
    {"\033[0;31m", 255, 0, 0}, // Red
    {"\033[0;32m", 0, 255, 0}, // Green
    {"\033[0;33m", 255, 255, 0}, // Yellow
    {"\033[0;34m", 0, 0, 255}, // Blue
    {"\033[0;35m", 128, 0, 128}, // Purple
    {"\033[0;36m", 0, 255, 255}, // Cyan
    {"\033[0;37m", 255, 255, 255} // White
};


char get_char(int luminance, AsciiRampLength ramp_length_enum) {
    const char* ascii_ramp = nullptr;
    int ramp_len = 0;

    switch (ramp_length_enum) {
        case AsciiRampLength::SHORT:
            ascii_ramp = ASCII_RAMP_SHORT;
            break;
        case AsciiRampLength::STANDARD:
            ascii_ramp = ASCII_RAMP_STANDARD;
            break;
        case AsciiRampLength::LONG:
            ascii_ramp = ASCII_RAMP_LONG;
            break;
    }

    // Exclude the null terminator (\0) from character count
    int ramp_length = sizeof(ascii_ramp) - 1; // char is 1 byte, Exclude '\0'

    int scaled_luminance = (int) ((float) luminance / 255.0 * ramp_length + 0.5);
    int luminance_index = ramp_length - scaled_luminance;

    return ascii_ramp[scaled_luminance];
}

void output_colour(char output_char, int r, int g, int b) {
    ColourMap selected_esc_code = esc_codes[0];

    int min_rgb_diff = std::abs(r - esc_codes[0].r) + std::abs(g - esc_codes[0].g) + std::abs(b - esc_codes[0].b);

    // Loop through vector elements
    for (size_t i = 1; i < esc_codes.size(); ++i) {
        int rgb_diff = std::abs(r - esc_codes[i].r) + std::abs(g - esc_codes[i].g) + std::abs(b - esc_codes[i].b);

        if (rgb_diff < min_rgb_diff) {
            selected_esc_code = esc_codes[i];
            min_rgb_diff = rgb_diff;
        }
    }

    // Print color escape code, character, and reset escape code (\033[0m)
    std::cout << selected_esc_code.esc_code << output_char << "\033[0m";
}

void output_colour_24bit(char output_char, int r, int g, int b) {
    // \033[38;2;R;G;Bm sets fg color directly to RGB values
    std::cout << "\033[38;2;" << r << ";" << g << ";" << b << "m" 
              << output_char 
              << "\033[0m";
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

void render_colour(std::vector<std::vector<std::vector<unsigned char>>> chrominance_matrix) {
    for (int row = 0; row < chrominance_matrix.size(); row++) {
        for (int col = 0; col < chrominance_matrix[row].size(); col++) {
            std::vector<unsigned char> pixel_chrominance = chrominance_matrix[row][col];

            int luminance = (pixel_chrominance[0] + pixel_chrominance[1] + pixel_chrominance[2]) / 3;
            char ascii_char = '@';

            // Double output to get aspect ratio correct
            output_colour_24bit(ascii_char, pixel_chrominance[0], pixel_chrominance[1], pixel_chrominance[2]);
            output_colour_24bit(ascii_char, pixel_chrominance[0], pixel_chrominance[1], pixel_chrominance[2]);
        }
        std::cout << '\n';
    }
}