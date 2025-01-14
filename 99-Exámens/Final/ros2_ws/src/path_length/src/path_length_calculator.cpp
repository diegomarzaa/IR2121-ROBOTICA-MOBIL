#include "rclcpp/rclcpp.hpp"
#include "geometry_msgs/msg/pose_stamped.hpp"
#include <vector>

using namespace std::chrono_literals;

void on_new_path(std::vector<geometry_msgs::msg::PoseStamped::SharedPtr> path)
{
  int size = path.size();
  double length = 0;

  for (int i=1; i<size; i++) {
    double x_act = path[i]->pose.pose.position.x;
    double x_ant = path[i-1]->pose.pose.position.x;
    
    double y_act = path[i]->pose.pose.position.y;
    double y_ant = path[i-1]->pose.pose.position.y;

    length += sqrt(pow(x_act-x_ant, 2) + pow(y_act-y_ant, 2));
  }

  RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "El tamany del path és: %f",
              length);
}


int main(int argc, char ** argv)
{
  rclcpp::init(argc, argv);
  auto node = rclcpp::Node::make_shared("path_length_calculator");
  auto subscriber = node->create_subscription<geometry_msgs::msg::PoseStamped>(
      "plan", 10, on_new_path);

  rclcpp::WallRate loop_rate(1s);

  while (rclcpp::ok()) {
    rclcpp::spin_some(node);
    loop_rate.sleep();
  } 

  rclcpp::shutdown();
  return 0;
}
