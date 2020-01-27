#!/bin/sh
xterm  -e  "cd ~/workspace/catkin_ws/; source devel/setup.bash; roslaunch home_service_robot world.launch" & 
sleep 5
xterm  -e  "cd ~/workspace/catkin_ws/; source devel/setup.bash; roslaunch home_service_robot amcl.launch" &
sleep 5
xterm  -e  "cd ~/workspace/catkin_ws/; source devel/setup.bash;rosrun rviz rviz -d \`rospack find rvizConfig\`/home_service.rviz" &
sleep 5
xterm  -e  "cd ~/workspace/catkin_ws/; source devel/setup.bash; roslaunch pick_objects pick_objects.launch"

