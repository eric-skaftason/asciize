#include <iostream>
#include <vector>
#include <string>
#include <cstring>

#include "asciize/ImageLoader.hpp"
#include "asciize/ImageProcessor.hpp"
#include "asciize/render.hpp"

int main() {
    std::cout << "--- ASCIIZE: An CLI image viewer that renders in ASCII ---" << '\n';
    std::cout << "Enter 'q' to quit program at any time.\n";

    while (true) {
        std::string file_path;
        std::cout << "Input abbsolute path to desired image: ";

        std::cin >> file_path;

        std::vector<std::vector<unsigned char>> og_luminance_matrix = ImageLoader::get_luminance(file_path.c_str());

        std::vector<std::vector<unsigned char>> luminance_matrix = ImageProcessor::downscale(og_luminance_matrix, 40, 60);

        render(luminance_matrix);
    }

    
    
    return 0;
}
