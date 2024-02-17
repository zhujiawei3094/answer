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

    //RCLCPP_INFO(this->get_logger(),"[x:%d,y:%d,ch:%d]",msg.height,msg.width,image.channels());
    //RCLCPP_INFO_STREAM(this->get_logger(),"Encoding:"<<msg.encoding);
}
void imageSubscriber::image_deal() {
    cv::Mat image=cv::imread("output.png",0);
    cv::Mat dst,cdst;
    std::vector<cv::Vec4i> lines;
    std::vector<float> b_line;
    cv::Vec4i judge_line;
    cv::Canny(image,dst,50,200,3);
    cv::cvtColor(dst,cdst,CV_GRAY2BGR);
    //获取判定线
    cv::HoughLinesP(dst,lines,1,CV_PI/180,50,1000,10);
    judge_line=lines[0];
    lines.pop_back();
    cv::HoughLinesP(dst,lines,1,CV_PI/180,50,50,10);
    //计算距离
    float k=(judge_line[1]-judge_line[3])/(judge_line[0]-judge_line[2]);
    float divid= sqrt(k*k+1);
    b_line.push_back(judge_line[1]-k*judge_line[0]);
    for(size_t i=0;i<lines.size();i++){
        cv::Vec4i l=lines[i];
        b_line.push_back(l[1]-k*l[0]);
        cv::line(cdst,cv::Point(l[0],l[1]),cv::Point (l[2],l[3]),cv::Scalar(0,0,255),3,cv::LINE_AA);
    }
    for(size_t i=1;i<b_line.size();i++){
        int distance =(b_line[0]-b_line[i])/divid;
        if(distance>10&&distance<=30)
        {
            int click_point[2]={{(lines[i][0]+lines[i][2])/2},{(lines[i][1]+lines[i][3])/2}};
            RCLCPP_INFO(this->get_logger(),"[x:%d y:%d]",click_point[0],click_point[1]);
        }
    }

    cv::imshow("p",dst);
    cv::imshow("j",cdst);
    cv::waitKey(100);


}

