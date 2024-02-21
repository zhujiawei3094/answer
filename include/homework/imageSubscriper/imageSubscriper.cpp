//
// Created by zhu on 24-2-15.
//
#include"imageSubscriper.h"
void imageSubscriber::image_callback(sensor_msgs::msg::Image::SharedPtr msg){
if(count%3==0){
    cv_bridge::CvImagePtr cvImage;
    cvImage = cv_bridge::toCvCopy(msg,msg->encoding);
    cv::Mat image = cvImage->image;
    image_deal(image);
}
count++;
}
void imageSubscriber::image_deal(cv::Mat image) {
    double min;
    int min_position[2];
    cv::Mat dst,cdst,mask,red_image,clear_image;
    std::vector<cv::Vec4i> lines;
    std::vector<cv::Mat>split_image;
    cv::split(image,split_image);
    red_image=split_image[2];
    mask=cv::Mat::zeros(red_image.size(),CV_8UC1);
    cv::Canny(image,dst,50,200,3);

    cv::HoughLinesP(dst,lines,1,CV_PI/180,10,1000);
    if(!lines.empty()){
        cv::Rect r1(0,lines[0][1]-25,1150,40);
        mask(r1).setTo(255);
        /*cv::bitwise_and(red_image,mask,cdst);
        cv::Canny(cdst,clear_image,50,200,3);
        cv::imshow("a",cdst);
        cv::imshow("b",clear_image);
        cv::waitKey(5);*/

        cv::minMaxIdx(red_image,&min,0,min_position,0,mask);
         if(min==0){
             geometry_msgs::msg::Point32 point;
             point.set__x(min_position[1]);
             point.set__y(min_position[0]);
             RCLCPP_INFO_STREAM(this->get_logger(),
                                "Send click: (" <<point.x<<","<<point.y <<")");
             msg.push(point);
         }
    }
}
void imageSubscriber::click_callback() {
    if(!msg.empty()){
        cv::waitKey(5);
        clickPoint->publish(msg.front());
        msg.pop();
        cv::waitKey(5);

    }
}