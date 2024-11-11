#include "rclcpp/rclcpp.hpp"          // Main ROS2
#include "geometry_msgs/msg/pose_stamped.hpp"

using namespace std::chrono_literals;

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    auto node = rclcpp::Node::make_shared("goal_publisher");
    auto publisher = node->create_publisher<geometry_msgs::msg::PoseStamped>("goal_pose", 10);

    rclcpp::WallRate loop_rate(1s);

    while (rclcpp::ok()) {
        // Missatge a publicar
        geometry_msgs::msg::PoseStamped goal_msg;
        goal_msg.header.stamp = node->get_clock()->now();
        goal_msg.header.frame_id = "map";
        goal_msg.pose.position.x = -1.0;
        goal_msg.pose.position.y = 3.0;
        goal_msg.pose.position.z = 0.0;
        goal_msg.pose.orientation.x = 0.0;
        goal_msg.pose.orientation.y = 0.0;
        goal_msg.pose.orientation.z = 0.0;
        goal_msg.pose.orientation.w = 1.0;

        // Publicar
        RCLCPP_INFO(node->get_logger(), "Publicant objectiu a /goal_pose");
        publisher->publish(goal_msg);

        // Sleep for the defined loop rate
        loop_rate.sleep();
    }

    rclcpp::shutdown();
    return 0;
}
