// Version 5: wait for completion based on tf2

#include "rclcpp/rclcpp.hpp"
#include "geometry_msgs/msg/pose_stamped.hpp"
#include "geometry_msgs/msg/pose_with_covariance_stamped.hpp"
#include <vector>
#include <map>

#include "tf2_ros/transform_listener.h"
#include "tf2_ros/buffer.h"
#include "geometry_msgs/msg/transform_stamped.hpp"
#include "tf2/LinearMath/Quaternion.h"

using namespace std::chrono_literals;

std::map<std::string, double> posicio_actual = {{"x", -2}, {"y", -0.5}};    // 1
std::vector<std::map<std::string, double>> objectius = {
    {{"x", 6.34}, {"y", -1.25}, {"yaw", 0.0}},      // 2
    {{"x", 1.0}, {"y", 3.88}, {"yaw", 1.57}},        // 3
    {{"x", -6.48}, {"y", -0.58}, {"yaw", 3.14}},     // 4
    {{"x", -2.7}, {"y", 3.75}, {"yaw", -1.57}}       // 5
};

size_t objectiu_i = 0;

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    auto node = rclcpp::Node::make_shared("patrolling_task");
    auto publisher = node->create_publisher<geometry_msgs::msg::PoseStamped>("goal_pose", 10);
    
    // Guardar transformacions
    // Es podrà accedir a elles en qualsevol moment
    tf2_ros::Buffer tf_buffer(node->get_clock());
    tf2_ros::TransformListener tf_listener(tf_buffer);

    // rclcpp::WallRate pose_send(1ms);
    rclcpp::WallRate loop_rate(1s);

    while (rclcpp::ok() && objectiu_i < objectius.size()) {
        auto objectiu = objectius[objectiu_i];
    
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

        RCLCPP_INFO(node->get_logger(), "Publicant objectiu %ld: (%f, %f, yaw: %f)", objectiu_i+2, objectiu["x"], objectiu["y"], objectiu["yaw"]);


        /********* (v5) COMPROVAR OBJECTIU ALCANÇAT *********/
        // Si  no es troba la transformació, es llença un warning, per a aixó en try-catch
        // S'obté la distància entre el robot i l'objectiu i es comprova si és prou a prop

        try {
            geometry_msgs::msg::TransformStamped transform_stamped = tf_buffer.lookupTransform(
                "map",                  // Destí, global
                "base_footprint",       // Origen, robot
                tf2::TimePointZero,     // Última transformació
                1s);                    // Temps d'expiració si no es troba

            // Obtindre diferència de distàncies
            double posicio_robot_x = transform_stamped.transform.translation.x;
            double posicio_robot_y = transform_stamped.transform.translation.y;
            double posicio_objectiu_x = objectiu["x"];
            double posicio_objectiu_y = objectiu["y"];

            double distancia_diferencia = sqrt(pow(posicio_robot_x - posicio_objectiu_x, 2) +
                                                pow(posicio_robot_y - posicio_objectiu_y, 2));
            RCLCPP_INFO(node->get_logger(), "Distancia robot a 'map': %f, Distancia objectiu a 'map': %f", posicio_robot, posicio_objectiu);

            // Veure si és suficientment a prop
            if (distancia_diferencia < 0.3) {
                objectiu_i++;
                RCLCPP_INFO(node->get_logger(), "\033[32mObjectiu %ld alcançat\033[0m", objectiu_i+1);
                continue;
            }
        }

        catch (tf2::TransformException &ex) {
            RCLCPP_WARN(node->get_logger(), "No es pot obtenir la transformació: %s", ex.what());
        }

        /************ SPIN AND SLEEP ************/
        /* (all versions) */
        rclcpp::spin_some(node);
        loop_rate.sleep();
    }

    rclcpp::shutdown();
    return 0;
}
