#include "io/camera.hpp"
#include "tasks/yolo.hpp"
#include "opencv2/opencv.hpp"
#include "tools/img_tools.hpp"

#include <algorithm>
#include <iostream>
#include <string>

int main()
{
    try {
        Camera camera;
        auto_aim::YOLO yolo("./configs/yolo.yaml", false);

        int frame_count = 0;

        while (true) {
            cv::Mat img = camera.read();
            if (img.empty()) {
                std::cerr << "Failed to read camera frame.\n";
                continue;
            }

            auto armors = yolo.detect(img, frame_count++);

            for (const auto & armor : armors) {
                // 题目要求：连接四个关键点形成闭合绿色矩形。
                tools::draw_points(img, armor.points, {0, 255, 0}, 2);

                // 在绿色装甲板框的正上方显示识别结果，例如：bluefour。
                std::string text = auto_aim::COLORS[armor.color] +
                                   auto_aim::ARMOR_NAMES[armor.name];

                float min_y = armor.points[0].y;
                float center_x = 0.0f;

                for (const auto & point : armor.points) {
                    min_y = std::min(min_y, point.y);
                    center_x += point.x;
                }

                center_x /= static_cast<float>(armor.points.size());

                // 根据文字宽度向左偏移，使文字大致居中于装甲板。
                int baseline = 0;
                const double font_scale = 0.7;
                const int thickness = 2;
                const int font_face = cv::FONT_HERSHEY_SIMPLEX;
                const cv::Size text_size = cv::getTextSize(
                    text, font_face, font_scale, thickness, &baseline);

                const int text_x = static_cast<int>(center_x) - text_size.width / 2;
                const int text_y = std::max(
                    text_size.height + 2,
                    static_cast<int>(min_y) - 10);

                tools::draw_text(
                    img,
                    text,
                    cv::Point(text_x, text_y),
                    {0, 255, 0},
                    font_scale,
                    thickness);
            }

            cv::Mat display;
            cv::resize(img, display, cv::Size(640, 480));
            cv::imshow("YOLO Armor Detection", display);

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

