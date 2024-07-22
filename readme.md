ImageUnwrapper Library Usage Documentation
Overview
The ImageUnwrapper library provides functionality to unwrap circular images into rectangular images based on a given configuration. This document details how to use the ImageUnwrapper class, including its main functions, inputs, and outputs.

Installation
To use the ImageUnwrapper library, ensure that you have the following files:

ImageUnwrapper.h
ImageUnwrapper.lib (for static library) or ImageUnwrapper.dll and ImageUnwrapper.lib (for dynamic library)
Usage
Including the Library
To use the ImageUnwrapper class, include the ImageUnwrapper.h header file in your project.

cpp
Copy code
#include "ImageUnwrapper.h"
Constructor
ImageUnwrapper(const std::string& filename)
Initializes the ImageUnwrapper object with the configuration file specified by filename.

Parameters:
filename: A std::string specifying the path to the configuration file.
Functions
std::vector<uint8_t> unwarp(const std::vector<uint8_t> &inputImg, int inputWidth, int inputHeight, int channels)
Unwarps the given image data.

Parameters:

inputImg: A std::vector<uint8_t> containing the input image data.
inputWidth: An int specifying the width of the input image.
inputHeight: An int specifying the height of the input image.
channels: An int specifying the number of channels in the input image.
Returns:

A std::vector<uint8_t> containing the unwrapped image data.
Public Member Variables
int Wd
The width of the unwrapped image.

int Hd
The height of the unwrapped image.

Example Usage
Below is an example of how to use the ImageUnwrapper class in a project.

Example Code
cpp
Copy code
#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/videoio.hpp>
#include "ImageUnwrapper.h"
#define _USE_MATH_DEFINES
#include <math.h>

int main() {
    // Create a window to display the results
    cv::namedWindow("Display", cv::WINDOW_GUI_NORMAL | cv::WINDOW_NORMAL);
    cv::setWindowProperty("Display", cv::WND_PROP_FULLSCREEN, cv::WINDOW_GUI_EXPANDED);

    // Open the default camera
    cv::VideoCapture camera(0);
    camera.set(cv::CAP_PROP_FRAME_WIDTH, 3264);
    camera.set(cv::CAP_PROP_FRAME_HEIGHT, 2448);

    // Initialize the ImageUnwrapper with the configuration file
    ImageUnwrapper unwrapper("config.txt");

    cv::Mat frame;
    while (true) {
        // Capture a frame from the camera
        camera.read(frame);
        if (!frame.empty()) {
            int width = frame.cols;
            int height = frame.rows;
            int channels = frame.channels();

            // Convert the frame to a vector of uint8_t
            std::vector<uint8_t> inputImg(frame.data, frame.data + width * height * channels);

            // Unwrap the image using the ImageUnwrapper
            std::vector<uint8_t> outputImg = unwrapper.unwarp(inputImg, width, height, channels);
            cv::Mat output(unwrapper.Hd, unwrapper.Wd, frame.type(), outputImg.data());

            // Resize the output image to 1920xHd
            cv::resize(output, output, cv::Size(1920, unwrapper.Hd));

            // Display the unwrapped image
            cv::imshow("Unwarped Image", output);

            // Exit the loop if 'esc' key is pressed
            if (cv::waitKey(1) == 27) {
                break;
            }
        }
    }

    return 0;
}
Explanation
Initialization:

Include the necessary headers.
Create a window using OpenCV to display the results.
Open the default camera and set its resolution.
Initialize the ImageUnwrapper object with a configuration file.
Main Loop:

Capture frames from the camera.
Convert the captured frame to a std::vector<uint8_t>.
Use the unwarp function to unwrap the image.
Convert the unwrapped image data back to a cv::Mat.
Resize the unwrapped image to a width of 1920 pixels while maintaining the height.
Display the unwrapped image.
Exit the loop if the 'esc' key is pressed.