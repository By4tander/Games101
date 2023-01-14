#include "Triangle.hpp"
#include "rasterizer.hpp"
#include <eigen3/Eigen/Eigen>
#include <iostream>
#include <opencv2/opencv.hpp>

constexpr double MY_PI = 3.1415926;

Eigen::Matrix4f get_view_matrix(Eigen::Vector3f eye_pos)
{
    Eigen::Matrix4f view = Eigen::Matrix4f::Identity();

    Eigen::Matrix4f translate;
    translate << 1, 0, 0, -eye_pos[0], 0, 1, 0, -eye_pos[1], 0, 0, 1,
        -eye_pos[2], 0, 0, 0, 1;

    view = translate * view;

    return view;
}

//构建变换矩阵,绕z旋转
Eigen::Matrix4f get_model_matrix(float rotation_angle)
{
    Eigen::Matrix4f model = Eigen::Matrix4f::Identity();

    // TODO: Implement this function
    // Create the model matrix for rotating the triangle around the Z axis.
    // Then return it.
    rotation_angle= rotation_angle/180.0*MY_PI;
    Eigen::Matrix4f rotate_z;
    rotate_z << cos(rotation_angle),-sin(rotation_angle),0,0,
                 sin(rotation_angle),cos(rotation_angle),0,0,
                 0  ,0  ,1  ,0,
                 0  ,0  ,0  ,1;
    model=rotate_z *model;
    return model;
}

//构建透视矩阵
Eigen::Matrix4f get_projection_matrix(float eye_fov, float aspect_ratio,
                                      float zNear, float zFar)
{
    Eigen::Matrix4f projection = Eigen::Matrix4f::Identity();
    //perspective projection
    //eye_fov 可视范围
    //aspect_ratio 宽高比
    Eigen::Matrix4f toOrthoMatrix; // 透视投影的核心，先压成一个立方体，然后进行ortho的操作
    toOrthoMatrix << zNear, 0,     0,            0,
                  0,     zNear, 0,            0,
                  0,     0,     zNear + zFar, (-1) * zNear * zFar,
                  0,     0,     1,            0;

    //正交投影。记住角度都要化
    float angle_in_use=eye_fov/2.0/180.0*MY_PI;
    float t = zNear * tan(angle_in_use); // y轴的最大范围
    float r = t * aspect_ratio;                // x轴的最小范围
    float l = -1*r; // x轴最小
    float b = -1*t; // y轴最小

    Eigen::Matrix4f moveMatrix; // 平移矩阵，操作第一步将图形中心先放到原点
    moveMatrix <<   1, 0, 0, -(l + r) / 2,
                    0, 1, 0, -(b + t) / 2,
                    0, 0, 1, -(zNear + zFar) / 2,
                    0, 0, 0, 1;

    Eigen::Matrix4f scaleMatirx2; // 缩放到[-1,1]范围内
    scaleMatirx2 << 2/(r - l),   0,    		  0,                  0,
                    0,           2/(t - b),   0,                  0,
                    0,           0,           2/(zFar - zNear) ,  0,
                    0,           0,           0,                  1;

    projection = scaleMatirx2 * moveMatrix * toOrthoMatrix * projection;

    return projection;
}

int main(int argc, const char** argv)//argc：argument count；argv：argument value
{
    float angle = 0;
    bool command_line = false;
    std::string filename = "output.png";

    if (argc >= 3) {
        command_line = true;
        angle = std::stof(argv[2]); // -r by default
        if (argc == 4) {
            filename = std::string(argv[3]);
        }
        else
            return 0;
    }

    rst::rasterizer r(700, 700);

    Eigen::Vector3f eye_pos = {0, 0, 5};

    std::vector<Eigen::Vector3f> pos{{2, 0, -2}, {0, 2, -2}, {-2, 0, -2}};

    std::vector<Eigen::Vector3i> ind{{0, 1, 2}};

    auto pos_id = r.load_positions(pos);
    auto ind_id = r.load_indices(ind);

    int key = 0;
    int frame_count = 0;


    while (key != 27) {
        r.clear(rst::Buffers::Color | rst::Buffers::Depth);

        r.set_model(get_model_matrix(angle));
        r.set_view(get_view_matrix(eye_pos));
        r.set_projection(get_projection_matrix(45, 1, 0.1, 50));

        r.draw(pos_id, ind_id, rst::Primitive::Triangle);

        cv::Mat image(700, 700, CV_32FC3, r.frame_buffer().data());
        image.convertTo(image, CV_8UC3, 1.0f);
        cv::imshow("image", image);
        key = cv::waitKey(10);

        std::cout << "frame count: " << frame_count++ << '\n';

        if (key == 'a') {
            angle += 10;
        }
        else if (key == 'd') {
            angle -= 10;
        }
    }

    return 0;
}
