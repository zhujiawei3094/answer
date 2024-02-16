//
// Created by zhu on 24-2-15.
//
#include"imageSubscriper.h"
void imageSubscriber::callback(sensor_msgs::msg::Image msg){

    cv_bridge::CvImagePtr cvImage;
    cvImage = cv_bridge::toCvCopy(msg,msg.encoding);
    cv::Mat image = cvImage->image;
    std::string outputFilename = "output.png";
    cv::imwrite(outputFilename, image);

    //RCLCPP_INFO_STREAM(this->get_logger(),"Mat:"<<image<<std::endl);
    //std::cout<<image<<std::endl;
    //cv::randu(image, cv::Scalar(0), cv::Scalar(255));


    //RCLCPP_INFO(this->get_logger(),"[x:%d,y:%d,ch:%d]",msg.height,msg.width,image.channels());
    //RCLCPP_INFO_STREAM(this->get_logger(),"Encoding:"<<msg.encoding);
}

