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
    std::vector<cv::Vec2f> lines;
    cv::Canny(image,dst,50,200,3);
    cv::cvtColor(dst,cdst,CV_GRAY2BGR);
    cv::HoughLines(dst,lines,1,CV_PI/180,100,0,0);
    for(size_t i=0;i<lines.size();i++){
        float rho=lines[i][0],theta=lines[i][0];
        cv::Point pt1,pt2;
        double a=cos(theta),b=sin(theta);
        double x0=a*rho,y0=b*rho;
        pt1.x=cvRound(x0+1000*(-b));
        pt1.y=cvRound(y0+1000*(a));
        pt2.x=cvRound(x0-1000*(-b));
        pt2.y=cvRound(y0-1000*(a));
        cv::line(cdst,pt1,pt2,cv::Scalar(0,0,255),3,0);

    }
    cv::imshow("i",image);
    cv::imshow("p",dst);
    cv::imshow("j",cdst);
    cv::waitKey(100);


}

