#!/bin/sh


xterm  -e  "roslaunch my_robot world.launch" &

sleep 5
xterm  -e  "roslaunch my_robot amcl.launch map_file:=/home/robond/ROS/catkin_ws/src/maps/myworld2.yaml" &

sleep 5
xterm  -e  "roslaunch turtlebot_rviz_launchers view_navigation.launch" &

sleep 5
xterm  -e  "roslaunch add_markers add_markers.launch" &

sleep 5
xterm  -e  "roslaunch pick_objects pick_objects.launch" 


