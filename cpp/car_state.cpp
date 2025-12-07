#include <chrono>
#include <memory>

#include "rclcpp/rclcpp.hpp"
//#include "std_msgs/msg/float32.hpp"
#include "car_msgs/msg/car_state.hpp"

class CarStatePublisher : public rclcpp::Node {
public:
  CarStatePublisher() 
  : Node("car_state_publisher"), count_(0) {
    declare_parameter("callback_period_ms", 500);
    auto callback_period_ms = get_parameter("callback_period_ms").as_int();

    //publisher_ = create_publisher<std_msgs::msg::Float32>("car_pose", 500);
    publisher_ = create_publisher<car_msgs::msg::CarState>("car_pose", 500);
    auto timer_callback = [this]() -> void {
      msg_.x = 2.3;
      msg_.y = 3.5;
      publisher_->publish(msg_);
    };
    timer_ = create_wall_timer(std::chrono::milliseconds(callback_period_ms),
                               timer_callback);
  }

private:
  rclcpp::TimerBase::SharedPtr timer_;
  rclcpp::Publisher<car_msgs::msg::CarState>::SharedPtr publisher_;
  size_t count_;
  //
  car_msgs::msg::CarState msg_;
};

int main(int argc, char *argv[]) {
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<CarStatePublisher>());
  rclcpp::shutdown();
  return 0;
}