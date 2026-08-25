#include <iostream>
#include <vector>
#include <string>
#include <cstring>

#include "asciize/get_luminance.hpp"
#include "asciize/render.hpp"

int main() {
    std::cout << "--- ASCIIZE: An CLI image viewer that renders in ASCII ---" << '\n';
    std::cout << "Enter 'q' to quit program at any time.\n";

    while (true) {
        std::string file_path;
        std::cout << "Input abbsolute path to desired image: ";

        std::cin >> file_path;

        std::vector<std::vector<unsigned char>> luminance_matrix = get_luminance(file_path.c_str());

        render(luminance_matrix);
    }

    
    
    return 0;
}
