// Version 2: send one goal and wait for completion (odom pose does not change)

#include "rclcpp/rclcpp.hpp"          // Main ROS2
#include "geometry_msgs/msg/pose_stamped.hpp"
#include "nav_msgs/msg/odometry.hpp"

using namespace std::chrono_literals;

std::map<std::string, double> posicio_actual = {{"x", 0.0}, {"y", 0.0}};
std::map<std::string, double> objectiu = {{"x", -1.0}, {"y", 3.0}, {"yaw", 0.0}};

void actualitzar_odom(const nav_msgs::msg::Odometry::SharedPtr msg)
{
    posicio_actual["x"] = msg->pose.pose.position.x;
    posicio_actual["y"] = msg->pose.pose.position.y;

    RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "Posició actual: (%f, %f)",
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
    bool goal_reached = false;


    while (rclcpp::ok() && !goal_reached) {
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

        /********* COMPROVAR OBJECTIU ALCANÇAT *********/
        double distancia_a_objectiu = sqrt(pow(posicio_actual["x"] - objectiu["x"], 2) + 
                                           pow(posicio_actual["y"] - objectiu["y"], 2));
        if (distancia_a_objectiu < 0.3) {
            goal_reached = true;
            RCLCPP_INFO(node->get_logger(), "Objectiu alcançat!");
            continue;
        } else {
            RCLCPP_INFO(node->get_logger(), "Distància a l'objectiu: %f", distancia_a_objectiu);
        }

        // Sleep for the defined loop rate
        rclcpp::spin_some(node);
        loop_rate.sleep();
    }

    rclcpp::shutdown();
    return 0;
}
