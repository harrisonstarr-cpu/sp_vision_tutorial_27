#include "camera.hpp"

#include <stdexcept>
#include <vector>

#include "io/hikrobot/include/MvCameraControl.h"

namespace
{
cv::Mat convert_frame(void * handle, MV_FRAME_OUT & raw)
{
    const auto width = static_cast<int>(raw.stFrameInfo.nWidth);
    const auto height = static_cast<int>(raw.stFrameInfo.nHeight);
    const auto pixel_type = raw.stFrameInfo.enPixelType;

    // 常见的海康 Bayer8 图像直接用 OpenCV 转成 BGR。
    switch (pixel_type) {
        case PixelType_Gvsp_BayerGR8:
        case PixelType_Gvsp_BayerRG8:
        case PixelType_Gvsp_BayerGB8:
        case PixelType_Gvsp_BayerBG8: {
            cv::Mat raw_img(height, width, CV_8UC1, raw.pBufAddr);
            cv::Mat bgr;
            int code = cv::COLOR_BayerBG2BGR;
            if (pixel_type == PixelType_Gvsp_BayerGR8) code = cv::COLOR_BayerGR2BGR;
            if (pixel_type == PixelType_Gvsp_BayerRG8) code = cv::COLOR_BayerRG2BGR;
            if (pixel_type == PixelType_Gvsp_BayerGB8) code = cv::COLOR_BayerGB2BGR;
            if (pixel_type == PixelType_Gvsp_BayerBG8) code = cv::COLOR_BayerBG2BGR;
            cv::cvtColor(raw_img, bgr, code);
            return bgr;
        }
        case PixelType_Gvsp_Mono8:
            return cv::Mat(height, width, CV_8UC1, raw.pBufAddr).clone();
        case PixelType_Gvsp_BGR8_Packed:
            return cv::Mat(height, width, CV_8UC3, raw.pBufAddr).clone();
        case PixelType_Gvsp_RGB8_Packed: {
            cv::Mat rgb(height, width, CV_8UC3, raw.pBufAddr);
            cv::Mat bgr;
            cv::cvtColor(rgb, bgr, cv::COLOR_RGB2BGR);
            return bgr;
        }
        default:
            break;
    }

    // 对其它像素格式交给 MVS SDK 转换成 BGR8。
    cv::Mat bgr(height, width, CV_8UC3);
    MV_CC_PIXEL_CONVERT_PARAM convert_param{};
    convert_param.nWidth = raw.stFrameInfo.nWidth;
    convert_param.nHeight = raw.stFrameInfo.nHeight;
    convert_param.pSrcData = raw.pBufAddr;
    convert_param.nSrcDataLen = raw.stFrameInfo.nFrameLen;
    convert_param.enSrcPixelType = raw.stFrameInfo.enPixelType;
    convert_param.pDstBuffer = bgr.data;
    convert_param.nDstBufferSize = static_cast<unsigned int>(bgr.total() * bgr.elemSize());
    convert_param.enDstPixelType = PixelType_Gvsp_BGR8_Packed;

    if (MV_CC_ConvertPixelType(handle, &convert_param) != MV_OK) {
        return {};
    }
    return bgr;
}
}

Camera::Camera()
    : handle_(nullptr), opened_(false), grabbing_(false)
{
    MV_CC_DEVICE_INFO_LIST device_list{};
    unsigned int ret = MV_CC_EnumDevices(MV_USB_DEVICE, &device_list);
    if (ret != MV_OK || device_list.nDeviceNum == 0) {
        throw std::runtime_error("No HikRobot USB camera found.");
    }

    ret = MV_CC_CreateHandle(&handle_, device_list.pDeviceInfo[0]);
    if (ret != MV_OK) {
        handle_ = nullptr;
        throw std::runtime_error("MV_CC_CreateHandle failed.");
    }

    ret = MV_CC_OpenDevice(handle_);
    if (ret != MV_OK) {
        MV_CC_DestroyHandle(handle_);
        handle_ = nullptr;
        throw std::runtime_error("MV_CC_OpenDevice failed.");
    }
    opened_ = true;

    // 与题目给出的 example.cpp 保持一致的基础相机参数。
    MV_CC_SetEnumValue(handle_, "BalanceWhiteAuto", MV_BALANCEWHITE_AUTO_CONTINUOUS);
    MV_CC_SetEnumValue(handle_, "ExposureAuto", MV_EXPOSURE_AUTO_MODE_OFF);
    MV_CC_SetEnumValue(handle_, "GainAuto", MV_GAIN_MODE_OFF);
    MV_CC_SetFloatValue(handle_, "ExposureTime", 10000.0);
    MV_CC_SetFloatValue(handle_, "Gain", 20.0);
    MV_CC_SetFrameRate(handle_, 60.0);

    ret = MV_CC_StartGrabbing(handle_);
    if (ret != MV_OK) {
        MV_CC_CloseDevice(handle_);
        MV_CC_DestroyHandle(handle_);
        handle_ = nullptr;
        opened_ = false;
        throw std::runtime_error("MV_CC_StartGrabbing failed.");
    }
    grabbing_ = true;
}

Camera::~Camera()
{
    if (handle_ == nullptr) return;

    if (grabbing_) {
        MV_CC_StopGrabbing(handle_);
        grabbing_ = false;
    }
    if (opened_) {
        MV_CC_CloseDevice(handle_);
        opened_ = false;
    }
    MV_CC_DestroyHandle(handle_);
    handle_ = nullptr;
}

cv::Mat Camera::read()
{
    if (handle_ == nullptr || !grabbing_) return {};

    MV_FRAME_OUT raw{};
    unsigned int ret = MV_CC_GetImageBuffer(handle_, &raw, 100);
    if (ret != MV_OK) return {};

    cv::Mat img = convert_frame(handle_, raw);
    MV_CC_FreeImageBuffer(handle_, &raw);
    return img;
}
