source /opt/ros/humble/setup.bash
export ROS_LOCALHOST_ONLY=1
export TURTLEBOT3_MODEL=waffle_pi
source /usr/share/gazebo/setup.bash
source install/setup.bash


--------------------------------------------------

- [ ] ma

SLAM

- `ros2 launch warehouse_exercise turtlebot3_warehouse.launch.py`

- [ ] add map topic to rviz -> slam.rviz

- `ros2 bag record /clock /map /map_updates /odom /robot_description /scan /scan_matched_points2 /submap_list /tf /tf_static`

- recorrer tot
- parar rosbag

- comprobar: `rviz2 -d /opt/ros/humble/share/turtlebot3_cartographer/rviz/tb3_cartographer.rviz`

- [ ] Mapa per a cada algorisme

ros2 launch warehouse_exercise cartographer.launch.py
ros2 run nav2_map_server map_saver_cli -f ./cartographer_map

ros2 launch warehouse_exercise rtabmap.launch.py
ros2 run nav2_map_server map_saver_cli -f ./rtabmap_map

ros2 launch warehouse_exercise slam_toolbox.launch.py
ros2 run nav2_map_server map_saver_cli -f ./slam_toolbox_map

- [ ] Pasar a carpeta els mapes y comprimir


millor: rtabmap

--------------------------------------------------

NAVIGATION:

`ros2 launch warehouse_exercise turtlebot3_warehouse.launch.py`

`ros2 launch warehouse_exercise navigation2.launch.py map:=maps/rtabmap_map.yaml`

- [ ] nav2_view.rviz add image

- `ros2 bag record /clock /tf /tf_static /map /robot_description /scan /particle_cloud /plan /local_plan /waypoints /mobile_base/sensors/bumper_pointcloud /global_costmap/costmap /global_costmap/costmap_updates /global_costmap/voxel_marked_cloud /downsampled_costmap /downsampled_costmap_updates /local_costmap/costmap /local_costmap/costmap_updates /local_costmap/published_footprint /local_costmap/voxel_marked_cloud`

- 5 goals

- cancel rosbag and save
















colcon build --symlink-install --packages-select ...

ros2 run turtlebot3_teleop teleop_keyboard
rqt