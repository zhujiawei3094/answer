//
// Created by zhu on 24-2-15.
//

#ifndef HOMEWORK_IMAGESUBSCRIPER_H
#define HOMEWORK_IMAGESUBSCRIPER_H
#include "websocketpp/config/asio_no_tls.hpp"

#include "websocketpp/server.hpp"

#include <iostream>
#include <thread>

#include <rclcpp/rclcpp.hpp>
#include <geometry_msgs/msg/point32.hpp>
#include <sensor_msgs/msg/image.hpp>
#include <opencv2/opencv.hpp>

#include <cv_bridge/cv_bridge.h>

using Server = websocketpp::server<websocketpp::config::asio>;
using message_ptr = Server::message_ptr;
using namespace std::chrono_literals;
using std::placeholders::_1;

class imageSubscriber : public rclcpp::Node{
private:
    rclcpp::Subscription<sensor_msgs::msg::Image>::SharedPtr  clickPointSubscriber;
    void callback(sensor_msgs::msg::Image msg);
public:
    imageSubscriber():Node("Subscriber"){
        clickPointSubscriber = this->create_subscription<sensor_msgs::msg::Image>(
                "/raw_image",10,std::bind(&imageSubscriber::callback,this,_1));
    }

};
#endif //HOMEWORK_IMAGESUBSCRIPER_H
