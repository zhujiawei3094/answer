//
// Created by zhu on 24-2-15.
//
#include"imageSubscriper.h"
void imageSubscriber::image_callback(sensor_msgs::msg::Image::SharedPtr msg){

    cv_bridge::CvImagePtr cvImage;
    cvImage = cv_bridge::toCvCopy(msg,msg->encoding);
    cv::Mat image = cvImage->image;
    image_deal(image);

}
void imageSubscriber::image_deal(cv::Mat image) {
    cv::Mat dst,cdst;
    std::vector<cv::Vec4i> lines;
    std::vector<float> b_line;
    cv::Vec4i judge_line;
    cv::Canny(image,dst,50,200,3);
    cv::cvtColor(dst,cdst,CV_GRAY2BGR);
    //获取判定线
    cv::HoughLinesP(dst,lines,1,CV_PI/180,10,1000);
    if(!lines.empty()) {
        judge_line = lines[0];
        lines.pop_back();
        cv::HoughLinesP(dst, lines, 1, CV_PI / 180, 50, 50);
        //计算距离
        float k = (judge_line[1] - judge_line[3]) / (judge_line[0] - judge_line[2]);
        float divid = sqrt(k * k + 1);
        float b=(judge_line[1] - k * judge_line[0]);

        RCLCPP_INFO_STREAM(this->get_logger(),
                          "Send line: (" << judge_line[0] <<","<<judge_line[1]<< ")("<<judge_line[2]<<"," <<judge_line[3]<< ")");
        for(size_t i=1;i<lines.size();i++){
            cv::Vec4i  l=lines[i];
            cv::line(cdst,cv::Point(l[0],l[1]),cv::Point (l[2],l[3]),cv::Scalar(0,0,255),3,cv::LINE_AA);
            int distance=(2*b-l[1]-l[3] +k *(l[0]+l[2] ))/(2*divid);
            RCLCPP_INFO_STREAM(this->get_logger(),"Send dis:"<<distance);
            if (distance>=6&&distance <= 10) {
                geometry_msgs::msg::Point32 point;
                point.set__x((l[0] + l[2]) / 2);
                //point.set__y((l[1] + l[3]) / 2);
                point.set__y(324);
                RCLCPP_INFO_STREAM(this->get_logger(),
                                  "Send click: (" <<point.x<<","<<point.y <<")");
                msg.push(point);
            }
        }
    }

        //cv::imshow("j",cdst);
        //cv::waitKey(100);
}
void imageSubscriber::click_callback() {
    if(!msg.empty()){
        geometry_msgs::msg::Point32 p;
        clickPoint->publish(msg.front());
        msg.pop();
    }
}
