#include <iostream>
#include <vector>

#include "asciize/get_luminance.hpp"

int main() {
    std::cout << "--- ASCIIZE: An CLI image viewer that renders in ASCII ---" << '\n';
    std::cout << "Enter 'q' to quit program at any time.\n";

    char file_path[57] = "C:\\Users\\skaft\\Desktop\\dev\\asciize\\test_images\\vista.jpg";
    std::vector<std::vector<unsigned char>> data = get_luminance(file_path);

    
    
    return 0;
}
