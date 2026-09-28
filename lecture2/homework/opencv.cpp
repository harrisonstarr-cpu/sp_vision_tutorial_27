#include "io/camera.hpp"
#include "tasks/apriltag_detector.hpp"
#include "opencv2/opencv.hpp"
#include "tools/img_tools.hpp"

#include <iostream>
#include <string>

int main()
{
    try {
        Camera camera;
        auto_charge::AprilTagDetector detector("./configs/yolo.yaml");

        while (true) {
            cv::Mat img = camera.read();
            if (img.empty()) {
                std::cerr << "Failed to read camera frame.\n";
                continue;
            }

            auto detections = detector.detect(img);

            for (const auto & detection : detections) {
                // AprilTag 的四个角点按左上、左下、右下、右上的顺序给出。
                tools::draw_points(img, detection.corners, {0, 255, 255}, 2);
                tools::draw_text(
                    img, "AprilTag " + std::to_string(detection.id),
                    cv::Point(static_cast<int>(detection.center.x),
                              static_cast<int>(detection.center.y) - 10),
                    {0, 255, 255}, 0.7, 2);
            }

            cv::Mat display;
            cv::resize(img, display, cv::Size(640, 480));
            cv::imshow("AprilTag Detection", display);

            const int key = cv::waitKey(1) & 0xff;
            if (key == 'q' || key == 27) break;
        }

        cv::destroyAllWindows();
    } catch (const std::exception & e) {
        std::cerr << "Error: " << e.what() << '\n';
        return 1;
    }

    return 0;
}
