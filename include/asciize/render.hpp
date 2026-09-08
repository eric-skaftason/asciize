#pragma once
#include <vector>

#include "asciize/AsciiRampLength.hpp"

void render(std::vector<std::vector<unsigned char>> luminance_matrix, AsciiRampLength ramp_length);
void render_colour(std::vector<std::vector<std::vector<unsigned char>>> chrominance_matrix);