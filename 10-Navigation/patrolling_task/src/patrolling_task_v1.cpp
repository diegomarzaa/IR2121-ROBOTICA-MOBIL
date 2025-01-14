// Version 1: send one goal

#include "rclcpp/rclcpp.hpp"          // Main ROS2
#include "geometry_msgs/msg/pose_stamped.hpp"

using namespace std::chrono_literals;

std::map<std::string, double> objectiu = {{"x", -1.0}, {"y", 3.0}, {"yaw", 0.0}};

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    auto node = rclcpp::Node::make_shared("goal_publisher");
    auto publisher = node->create_publisher<geometry_msgs::msg::PoseStamped>("goal_pose", 10);

    rclcpp::WallRate loop_rate(1s);

    while (rclcpp::ok()) {
        /********* PUBLICAR OBJECTIU *********/
        geometry_msgs::msg::PoseStamped goal_msg;
        goal_msg.header.stamp = node->get_clock()->now();
        goal_msg.header.frame_id = "map";
        goal_msg.pose.position.x = objectiu["x"];
        goal_msg.pose.position.y = objectiu["y"];
        goal_msg.pose.position.z = 0.0;

        // Yaw -> Quaternion
        // On yaw és l'angle de gir respecte l'eix Z, sentit antihorari
        tf2::Quaternion q;
        q.setRPY(0, 0, objectiu["yaw"]);
        goal_msg.pose.orientation.x = q.x();
        goal_msg.pose.orientation.y = q.y();
        goal_msg.pose.orientation.z = q.z();
        goal_msg.pose.orientation.w = q.w();

        publisher->publish(goal_msg);
        RCLCPP_INFO(node->get_logger(), "Publicant objectiu a /goal_pose");

        // Sleep for the defined loop rate
        loop_rate.sleep();
    }

    rclcpp::shutdown();
    return 0;
}
