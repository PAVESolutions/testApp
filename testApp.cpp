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
    cv::namedWindow("Display", cv::WINDOW_GUI_NORMAL | cv::WINDOW_NORMAL);
    cv::setWindowProperty("Display", cv::WND_PROP_FULLSCREEN, cv::WINDOW_GUI_EXPANDED);
    cv::VideoCapture camera(0);
    camera.set(cv::CAP_PROP_FRAME_WIDTH, 3264);
    camera.set(cv::CAP_PROP_FRAME_HEIGHT, 2448);
    ImageUnwrapper unwrapper("config.txt");
    cv::Mat frame;
    while (true) {
        camera.read(frame);
        if (!frame.empty()) {
            int width = frame.cols;
            int height = frame.rows;
            int channels = frame.channels();

            std::vector<uint8_t> inputImg(frame.data, frame.data + width * height * channels);

            std::vector<uint8_t> outputImg = unwrapper.unwarp(inputImg, width, height, channels);
            cv::Mat output(unwrapper.Hd, unwrapper.Wd, frame.type(), outputImg.data());

            cv::resize(output, output, cv::Size(1920, unwrapper.Hd));
            cv::imshow("Unwarped Image", output);

            if (cv::waitKey(1) == 27) {  // Wait for 'esc' key press for 30ms
                break; // Stop capturing

            }
        }
    }
    return 0;
}
