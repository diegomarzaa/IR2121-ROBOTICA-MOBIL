#include "rclcpp/rclcpp.hpp"          // Main ROS2
#include "geometry_msgs/msg/pose_stamped.hpp"
#include "nav_msgs/msg/odometry.hpp"
#include <vector>

using namespace std::chrono_literals;

std::map<std::string, double> posicio_actual = {{"x", 0.0}, {"y", 0.0}};
std::vector<std::map<std::string, double>> objectius = {
    {{"x", 1.0}, {"y", 1.0}},
    {{"x", 2.0}, {"y", 2.0}},
    {{"x", 3.0}, {"y", 3.0}},
    {{"x", 4.0}, {"y", 4.0}}
};

size_t objectiu_i = 0;

void actualitzar_odom(const nav_msgs::msg::Odometry::SharedPtr msg)
{
    posicio_actual["x"] = msg->pose.pose.position.x;
    posicio_actual["y"] = msg->pose.pose.position.y;

    RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "\033[34mPosició actual: (%f, %f)\033[0m",    // \033[34m és per posar el text en blau
                posicio_actual["x"], posicio_actual["y"]);
}

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    auto node = rclcpp::Node::make_shared("patrolling_task");
    auto publisher = node->create_publisher<geometry_msgs::msg::PoseStamped>("goal_pose", 10);
    auto subscriber = node->create_subscription<nav_msgs::msg::Odometry>("odom", 10, actualitzar_odom);

    // rclcpp::WallRate pose_send(1ms);
    rclcpp::WallRate loop_rate(1s);

    while (rclcpp::ok() && objectiu_i < objectius.size()) {
        auto objectiu = objectius[objectiu_i];
    
        // Publicar objectiu
        geometry_msgs::msg::PoseStamped goal_msg;
        goal_msg.header.stamp = node->get_clock()->now();
        goal_msg.header.frame_id = "map";
        goal_msg.pose.position.x = objectiu["x"];
        goal_msg.pose.position.y = objectiu["y"];
        goal_msg.pose.position.z = 0.0;
        goal_msg.pose.orientation.x = 0.0;
        goal_msg.pose.orientation.y = 0.0;
        goal_msg.pose.orientation.z = 0.0;
        goal_msg.pose.orientation.w = 1.0;
        publisher->publish(goal_msg);
        RCLCPP_INFO(node->get_logger(), "Publicant objectiu %ld: (%f, %f)", objectiu_i+1, objectiu["x"], objectiu["y"]);

        // Objectiu alcançat?
        double distancia_a_objectiu = sqrt(pow(posicio_actual["x"] - objectiu["x"], 2) + 
                                           pow(posicio_actual["y"] - objectiu["y"], 2));
        if (distancia_a_objectiu < 0.3) {
            objectiu_i++;
            RCLCPP_INFO(node->get_logger(), "\033[32mObjectiu %ld alcançat\033[0m", objectiu_i+1);
            continue;
        } else {
            RCLCPP_INFO(node->get_logger(), "Distància a l'objectiu %ld: %f", objectiu_i+1, distancia_a_objectiu);
        }

        // Sleep for the defined loop rate
        rclcpp::spin_some(node);
        loop_rate.sleep();
    }

    rclcpp::shutdown();
    return 0;
}
