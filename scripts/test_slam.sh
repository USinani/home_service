#!/bin/sh
xterm  -e  "cd ~/workspace/catkin_ws/; roslaunch home_service_robot world.launch" & 
sleep 5
xterm  -e  "cd ~/workspace/catkin_ws/; roslaunch home_service_robot mapping.launch" &
sleep 5
xterm  -e  "cd ~/workspace/catkin_ws/; rosrun rviz rviz -d \`rospack find rvizConfig\`/home_service.rviz" &
sleep 2
xterm  -e  "cd ~/workspace/catkin_ws/; rosrun teleop_twist_keyboard teleop_twist_keyboard.py"
