#include "homework/imageSubscriper/imageSubscriper.h"
int main(int argc, char **argv) {
    rclcpp::init(argc,argv);
    std::thread SubscriberThread([=](){
        rclcpp::spin(std::make_shared<imageSubscriber>());
        rclcpp::shutdown();
    });
    SubscriberThread.detach();
    std::thread PublisherThread([=](){
        rclcpp::spin(std::make_shared<imageSubscriber>());
        rclcpp::shutdown();
    });
    PublisherThread.detach();

    rclcpp::spin(std::make_shared<imageSubscriber>());
    rclcpp::shutdown();
}
