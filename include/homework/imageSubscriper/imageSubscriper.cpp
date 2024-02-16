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
    image_deal();
    //cv::imshow("output.png",image);
    //cv::waitKey(0);

    //RCLCPP_INFO_STREAM(this->get_logger(),"Mat:"<<image<<std::endl);
    //std::cout<<image<<std::endl;
    //cv::randu(image, cv::Scalar(0), cv::Scalar(255));

    RCLCPP_INFO(this->get_logger(),"[x:%d,y:%d,ch:%d]",msg.height,msg.width,image.channels());
    //RCLCPP_INFO_STREAM(this->get_logger(),"Encoding:"<<msg.encoding);
}
void imageSubscriber::image_deal() {
    cv::Mat image=cv::imread("output.png",0);
    cv::Mat dst,cdst;
    std::vector<cv::Vec4i> lines;
    cv::Canny(image,dst,50,200,3);
    cv::cvtColor(dst,cdst,CV_GRAY2BGR);
    cv::HoughLinesP(dst,lines,1,CV_PI/180,50,400,10);
    for(size_t i=0;i<lines.size();i++){
        cv::Vec4i l=lines[i];
        cv::line(cdst,cv::Point(l[0],l[1]),cv::Point (l[2],l[3]),cv::Scalar(0,0,255),3,cv::LINE_AA);

    }

    cv::imshow("p",dst);
    cv::imshow("j",cdst);
    cv::waitKey(100);


}

