#include <iostream>
#include <vector>

#include "asciize/ImageProcessor.hpp"

std::vector<std::vector<unsigned char>> ImageProcessor::scale(std::vector<std::vector<unsigned char>> og_luminance_matrix, double scale_factor) {
    if (scale_factor <= 0) {
        std::cout << "Invalid scale_factor.\n";
        return og_luminance_matrix;
    }

    // Use nearest neighbour scaling to preserve harsh edges
    int og_rows = og_luminance_matrix.size();
    int og_cols = og_luminance_matrix[0].size();

    int rows = (int) (og_rows * scale_factor + 0.5);
    int cols = (int) (og_cols * scale_factor + 0.5);

    std::vector<std::vector<unsigned char>> luminance_matrix(rows, std::vector<unsigned char>(cols));

    for (int row = 0; row < rows; row++) {
        for (int col = 0; col < cols; col++) {
            int mapped_og_row = (int) (row / scale_factor + 0.5);
            int mapped_og_col = (int) (col / scale_factor + 0.5);
            luminance_matrix[row][col] = og_luminance_matrix[mapped_og_row][mapped_og_col];
        }   
    }

    return luminance_matrix;

}

std::vector<std::vector<unsigned char>> ImageProcessor::downscale(std::vector<std::vector<unsigned char>> og_luminance_matrix, int max_rows, int max_cols) {
    int og_rows = og_luminance_matrix.size();
    int og_cols = og_luminance_matrix[0].size();

    double v_scale = 1.0;
    if (og_rows > max_rows) {
        v_scale = (double) max_rows / (double) og_rows;
    }

    double h_scale = 1.0;
    if (og_cols > max_cols) {
        h_scale = (double) max_cols / (double) max_cols;
    }
    
    
    double scale_factor;
    if (v_scale < h_scale) scale_factor = v_scale;
    else scale_factor = h_scale;

    return scale(og_luminance_matrix, scale_factor);
}