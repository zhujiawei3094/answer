//
// Created by zhu on 24-2-15.
//

#ifndef HOMEWORK_IMAGESUBSCRIPER_H
#define HOMEWORK_IMAGESUBSCRIPER_H

#include <iostream>
#include <thread>

#include <rclcpp/rclcpp.hpp>
#include <geometry_msgs/msg/point32.hpp>
#include <sensor_msgs/msg/image.hpp>
#include <opencv2/opencv.hpp>

#include <cv_bridge/cv_bridge.h>

using namespace std::chrono_literals;
using std::placeholders::_1;

class imageSubscriber : public rclcpp::Node{
private:
    int count;
    rclcpp::Publisher<geometry_msgs::msg::Point32>::SharedPtr clickPoint;
    rclcpp::Subscription<sensor_msgs::msg::Image>::SharedPtr  imageSubscription;
    std::queue<geometry_msgs::msg::Point32>msg;
    void image_callback(sensor_msgs::msg::Image::SharedPtr msg);
    void click_callback();
    void image_deal(cv::Mat image);
    rclcpp::TimerBase::SharedPtr timer_;
public:
    imageSubscriber():Node("Subscriber"){
        imageSubscription = this->create_subscription<sensor_msgs::msg::Image>(
                "/raw_image",10,std::bind(&imageSubscriber::image_callback,this,_1));

        clickPoint=this->create_publisher<geometry_msgs::msg::Point32>(
                "/click_position",10);
        if(msg.empty()) click_callback();
        timer_ = this->create_wall_timer(
                10ms, std::bind(&imageSubscriber::click_callback, this));

    }
};
#endif //HOMEWORK_IMAGESUBSCRIPER_H
