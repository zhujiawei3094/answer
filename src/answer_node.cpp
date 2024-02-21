#include "homework/imageSubscriper/imageSubscriper.h"
int main(int argc, char **argv) {
    rclcpp::init(argc,argv);
    rclcpp::spin(std::make_shared<imageSubscriber>());
    rclcpp::shutdown();

}
