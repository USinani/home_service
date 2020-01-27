# Home service robot simulation using ROS

## Author

* **Tui Alexandre Ono Baraniuk** - *Initial work* - [tuialexandre](https://github.com/tuialexandre)


### Packages description

For this project 4 packages are used: add_markers, home_service_robot, pick_objects and teleop_twist_keyboard.

The add_markers start a service that can add or remove markers in rviz;
home_service_robot contains the world and robot models, and the launch files for mapping, localization and slam;
pick_objects create a simple_action_client and also a add_markers_client. It has a routine that create a marker/object; send the robot to pick it; deliver the object to another location;
teleop_twist_keyboard is used to directly control the robot using the keyboard

The rvizConfig contains the rviz configuration file used during the project.

### Exporting the RTAB_Map
To Export the rtab map (generated with slam) to the 2D .pgm and .yaml used for localization and navigation, the following commands can be used:

roscore
rosrun rtabmap_ros rtabmap _database_path:=<your_map_name>.db
rosrun map_server map_saver <exported_map_name>:=proj_map
rosservice call /publish_map 1 1 0

### Scripts description
There are 4 scripts available:
add_marker.sh -> launch a world and robot on gazebo, runs rviz, starts add_markers service, send calls to the service to simulate a object being created, picked and delivered
test_navigation.sh -> -> launch a world and robot on gazebo, runs rviz, launch amcl, to localize and navigate the robot
test_slam.sh -> launch a world and robot on gazebo, runs rviz, launch mapping node, start keyboard teleop node. This can be used to generate a <map_name>.db that can be used in localization and navigation
home_service.sh -> launch a world and robot on gazebo, runs rviz, starts pick_objects.launch, which create the add_markers node and the pick_objects node. The pick objects node will first create an object/marker, then move the robot to its location, pick it, and finally deliver it in a new location.

## License

This project is licensed under the MIT License - see the [LICENSE.md](LICENSE.md) file for details
