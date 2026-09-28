#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <opencv2/opencv.hpp>

class Camera
{
public:
    Camera();
    ~Camera();
    cv::Mat read();

private:
    void * handle_;
    bool opened_;
    bool grabbing_;
};

#endif
