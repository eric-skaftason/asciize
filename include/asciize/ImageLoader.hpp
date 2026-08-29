#pragma once
#include <vector>

class ImageLoader {
    public:
        static std::vector<std::vector<unsigned char>> get_luminance(const char *file_path);

        static std::vector<std::vector<std::vector<unsigned char>>> get_chrominance(const char *file_path);
};
