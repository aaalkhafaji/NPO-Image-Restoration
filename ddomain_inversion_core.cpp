%%writefile domain_inversion_core.cpp
#include <iostream>
#include <iomanip>

struct PixelState {
    float r, g, b;
};

PixelState CVDE_DivisionFreeInverse(const PixelState& v, float time_t) {
    PixelState recovered;
    const float alpha = 0.03f;
    const float beta  = 0.01f;
    const float gamma = 0.04f;
    const float k_t   = 0.005f * time_t;

    recovered.b = v.b - k_t;
    
    float h_val = gamma * (recovered.b * recovered.b);
    recovered.g = v.g - h_val;

    float f_val = (alpha * (recovered.g * recovered.g)) + (beta * recovered.b);
    recovered.r = v.r - f_val;

    return recovered;
}

int main() {
    PixelState input_vector = {120.5f / 255.0f, 85.2f / 255.0f, 45.0f / 255.0f};
    PixelState clean_pixel = CVDE_DivisionFreeInverse(input_vector, 1.0f);
    
    std::cout << "--- CVDE Hardware Execution Trace ---" << std::endl;
    std::cout << std::fixed << std::setprecision(4);
    std::cout << "Input Corrupted State (Normalized) -> R: " << input_vector.r 
              << ", G: " << input_vector.g 
              << ", B: " << input_vector.b << std::endl;
    std::cout << "Recovered Clean State (Normalized) -> R: " << clean_pixel.r 
              << ", G: " << clean_pixel.g 
              << ", B: " << clean_pixel.b << std::endl;
    std::cout << "Recovered Clean State (8-bit scale)  -> R: " << (int)(clean_pixel.r * 255) 
              << ", G: " << (int)(clean_pixel.g * 255) 
              << ", B: " << (int)(clean_pixel.b * 255) << std::endl;
    std::cout << "Total Divisions Computed: 0" << std::endl;
    return 0;
}
