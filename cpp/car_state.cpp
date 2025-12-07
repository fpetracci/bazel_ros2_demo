#include <chrono>
#include <memory>

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/float32.hpp"

class CarStatePublisher : public rclcpp::Node {
public:
  CarStatePublisher() : Node("minimal_publisher"), count_(0) {
    declare_parameter("callback_period_ms", 500);
    auto callback_period_ms = get_parameter("callback_period_ms").as_int();

    publisher_ = create_publisher<std_msgs::msg::Float32>("car_pose", 500);
    auto timer_callback = [this]() -> void {
      auto message = std_msgs::msg::Float32();
      message.data = static_cast<float>(count_++);
      publisher_->publish(message);
    };
    timer_ = create_wall_timer(std::chrono::milliseconds(callback_period_ms),
                               timer_callback);
  }

private:
  rclcpp::TimerBase::SharedPtr timer_;
  rclcpp::Publisher<std_msgs::msg::Float32>::SharedPtr publisher_;
  size_t count_;
};

int main(int argc, char *argv[]) {
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<CarStatePublisher>());
  rclcpp::shutdown();
  return 0;
}