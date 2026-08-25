#pragma once
#include <vector>

class ImageProcessor{
    public:
        static std::vector<std::vector<unsigned char>> scale(std::vector<std::vector<unsigned char>> luminance_matrix, double scale_factor);

        static std::vector<std::vector<unsigned char>> downscale(std::vector<std::vector<unsigned char>> og_luminance_matrix, int max_rows, int max_cols);
};
