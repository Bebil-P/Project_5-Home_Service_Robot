#!/bin/sh

#export 
#TURTLEBOT_GAZEBO_WORLD_FILE=/home/robond/ROS/catkin_ws/src/maps/myworld2.world

xterm  -e  "roslaunch my_robot world.launch" &
sleep 5
xterm  -e  "roslaunch my_robot amcl.launch" & 
sleep 5
xterm  -e  "roslaunch turtlebot_rviz_launchers view_navigation.launch" &
sleep 5
xterm  -e  "roslaunch pick_objects pick_objects.launch" 

