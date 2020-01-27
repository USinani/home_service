#!/bin/sh
xterm  -e  "cd ~/workspace/catkin_ws/; source devel/setup.bash; roslaunch home_service_robot world.launch" & 
sleep 5
xterm  -e  "cd ~/workspace/catkin_ws/; source devel/setup.bash; roslaunch home_service_robot amcl.launch" &
sleep 5
xterm  -e  "cd ~/workspace/catkin_ws/; source devel/setup.bash; rosrun rviz rviz -d \`rospack find rvizConfig\`/home_service.rviz" &
sleep 5
xterm  -e  "cd ~/workspace/catkin_ws/; source devel/setup.bash; rosrun add_markers add_markers_node;" &
sleep 2
xterm  -e  "cd ~/workspace/catkin_ws/; source devel/setup.bash; 
echo \"Creating marker at the pickup zone\";
rosservice call /add_markers/draw_marker -- 4.8 -2.7 0; sleep 5;
echo \"Picking object\"; sleep 2;
echo \"Picked object\";rosservice call /add_markers/delete_marker 0; sleep 2;
echo \"Delivering object\"; sleep 2; 
echo \"Object delivered\";
rosservice call /add_markers/draw_marker -- 6.5 -1.2 0; sleep 10;
"


