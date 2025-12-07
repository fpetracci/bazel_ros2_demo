#! /usr/bin/env python3

import rclpy
from rclpy.node import Node
from std_msgs.msg import Float32


class PyListener(Node):
    def __init__(self):
        super().__init__("py_listener")

        self.pose_sub = self.create_subscription(
            Float32, "car_pose", self.pose_callback, 10
        )

    def pose_callback(self, msg):
        self.get_logger().info(f"Received x: {msg.data}")


def main(args=None):
    rclpy.init(args=args)
    node = PyListener()

    try:
        rclpy.spin(node)
    except KeyboardInterrupt:
        pass
    finally:
        node.destroy_node()
        rclpy.shutdown()


if __name__ == "__main__":
    main()
