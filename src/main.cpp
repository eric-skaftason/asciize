#include <iostream>
#include <vector>
#include <string>
#include <cstring>

#include "asciize/ImageLoader.hpp"
#include "asciize/ImageProcessor.hpp"
#include "asciize/render.hpp"
#include "asciize/AsciiRampLength.hpp"

int main() {
    std::cout << "--- ASCIIZE: An CLI image viewer that renders in ASCII ---" << '\n';
    std::cout << "Enter 'q' to quit program at any time.\n";

    while (true) {
        std::string file_path;
        std::cout << "Input absolute path to desired image: ";

        std::cin >> file_path;

        // std::vector<std::vector<unsigned char>> og_luminance_matrix = ImageLoader::get_luminance(file_path.c_str());
        // std::vector<std::vector<unsigned char>> luminance_matrix = ImageProcessor::downscale(og_luminance_matrix, 400, 600);


        std::vector<std::vector<std::vector<unsigned char>>> og_chrominance_matrix = ImageLoader::get_chrominance(file_path.c_str());
        std::vector<std::vector<std::vector<unsigned char>>> chrominance_matrix = ImageProcessor::downscale(og_chrominance_matrix, 400, 600);

        AsciiRampLength ramp_len = STANDARD;
        std::cout << "Enter ASCII ramp length (1. short, 2. standard [default], 3. long) - Choice [1-3]: ";
        
        int ramp_choice = 2;
        std::cin >> ramp_choice;

        switch (ramp_choice) {
            case 1:
                ramp_len = SHORT;
                break;
            case 2:
                ramp_len = STANDARD;
                break;
            case 3:
                ramp_len = LONG;
                break;
            default:
                std::cout << "Invalid ASCII ramp length. Default value to be used.\n";
                ramp_len = SHORT;
                break;
        }


        render(chrominance_matrix, ramp_len);
    }

    
    
    return 0;
}
