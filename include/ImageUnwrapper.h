#pragma once
#ifndef IMAGE_UNWRAPPER_H
#define IMAGE_UNWRAPPER_H

#include <string>
#include <vector>

class ImageUnwrapper {
public:
    ImageUnwrapper(const std::string& filename);

    // Method to unwarp the image
    std::vector<uint8_t> unwarp(const std::vector<uint8_t>& inputImg, int inputWidth, int inputHeight, int channels);
    int Wd, Hd;

    // Getters for R1 and R2 to be used in the test application
    int getR1() const { return R1; }
    int getR2() const { return R2; }

private:
    // Methods to read configuration, build the map, and convert values
    bool readConfig(const std::string& filename);
    void buildMap();
    void convertVals();

    // Member variables for the parameters
    double Cx_r, Cy_r;
    double R1_r, R2_r;
    int Cx, Cy;
    int R1, R2;
    int Ws, Hs;

    // Vectors to hold the mapping values
    std::vector<float> map_x, map_y;
};

#endif // IMAGE_UNWRAPPER_H
