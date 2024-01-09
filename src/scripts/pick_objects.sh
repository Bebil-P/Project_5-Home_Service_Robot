#!/bin/sh


export 
TURTLEBOT_GAZEBO_WORLD_FILE=$(rospack find my_robot)/maps/myworld2.world

xterm  -e  "roslaunch turtlebot_gazebo turtlebot_world.launch" &

sleep 5
xterm  -e  "roslaunch turtlebot_gazebo amcl_demo.launch map_file:=$(rospack find my_robot)/maps/myworld2.yaml" &

sleep 5
xterm  -e  " roslaunch turtlebot_rviz_launchers view_navigation.launch" &
sleep 5
xterm  -e  " roslaunch pick_objects pick_object1.launch" 

