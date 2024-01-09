# Project_5-Home_Service_Robot


    Goal of the project:
    The goal of this project was to build a robot that could map, localize and navigate the environment so that the robot can pick an object (marker) from a provided location and deliver the objects at the desired location. 


Packages used in this project: 

    slam_gmapping:
    For ROS kinetic 
    $ git clone -b hydro-devel https://github.com/ros-perception/slam_gmapping.git

    turtlebot_gazebo:
    $ git clone https://github.com/turtlebot/turtlebot_simulator.git
    
    turtlebot_rviz_launchers:
    $ git clone https://github.com/turtlebot/turtlebot_interactions.git   
  
    turtlebot_teleop:
    $ git clone https://github.com/turtlebot/turtlebot.git
    my_robot (own robot with amcl)

Packages explained: 

    add_Marker: 
    The Add marker packages adds a marker on the map indicating the robot the pickup location. Once the robot has reached the pickup location the marker disappears indicating that the parcel has been picked up. Then it waits for the robot to reach a predefined drop off location where the marker will reappear, indicating that the robot has delivered the parcel. 
    
    pick_objects:
    In this package the robot is autonomously navigated in its environment. The robot receives its pick up location from the add_marker package and it navigates to the location. Once the robot has reached the pickup location it sends information to the add marker packing saying the package has been picked up. The robot then receives new instruction about the drop off location from the add_marker package. The task is complete if the robot reaches the drop off location.     
    
    
    gmapping: 
    This package helps to map unknown environments using the occupancy grid-based fastSLAM mapping algorithm. This package solves the SLAM problem by feeding its nodes with the robots laser and odometry measurement values. This generates a 2D occupancy grid map of the environment which is contentiously updated as the robot moves in its environment.  
    
    
    amcl: 
    This package is used to navigate and localize our robot in its environment. For navigation it uses the ROS Navigation stack which is based on Dijkstra's variant of the Uniform Cost Search algorithm, to plan the robot path from the pick-up location to drop off location. To achieve this it uses a cost map to identify which part of the map is occupied and which part is unoccupied. As the robot moves around the cost map keeps getting updated which helps the robot to avoid any obstacle and generate new trajectory to destination. 
     For localization the package uses Adaptive Monte Carlo Localization algorithm. It uses particle filter to track the pose of a robot against a known map. Initially the particles are spread randomly and uniformly throughout the entire map. Each of these particles represents the hypothesis of where the robot might be. As the robot moves the algorithm dynamically adjusts the number of particles over a period of time and finally converges, estimating the robots position.  
    
    
    
    turtlebot_teleop: 
    The teleop package is used to manually control our robot for testing various packages and mapping our environment.

    turtlebot_rviz_launchers: 
    This is a preconfigured rviz workspace (saved at catkin_ws/src/rvizConfig) that will load the robot model, trajectories, and map.

    turtlebot_gazebo: 
    With the turtlebot_world.launch we can deploy a turtlebot in a gazebo environment by linking the world file to it. 




Directory tree structre :

    ├── add_markers
    │   ├── ...
    │   └── src
    │       ├── add_markers.cpp
    │       └── add_markerstest.cpp
    ├── ...
    ├── maps
    │   ├── myworld2.pgm
    │   ├── myworld2.world
    │   └── myworld2.yaml
    ├── my_robot
    │   ├──
    │   ├── launch
    │   │   ├── amcl.launch
    │   │   ├── robot_description.launch
    │   │   └── world.launch
    │   ├── maps
    │   │   ├── myworld2.pgm
    │   │   └── myworld2.yaml
    │   ├──...
    │   └── worlds
    │       └── myworld2.world
    ├── pick_objects
    │   ├── ...
    │   └── src
    │       └── pick_objects.cpp
    ├── rvizConfig
    │   └── rvizConfig.rviz
    ├── scripts
    │   ├── add_marker.sh
    │   ├── home_service_my_robot.sh
    │   ├── home_service.sh
    │   ├── pick_objects_my_robot.sh
    │   ├── pick_objects.sh
    │   ├── test_navigation.sh
    │   └── test_slam.sh
    ├── slam_gmapping
    │   └── gmapping
    │       └── ...
    ├── turtlebot
    │   ├── ...
    │   └── turtlebot_teleop
    │       
    ├── turtlebot_interactions
    │   └── ...
    │   └── turtlebot_rviz_launchers
    │       
    └── turtlebot_simulator
        ├── ...
        └── turtlebot_gazebo

Running the project:  
    To see the robot perform autonomous navigation run:
    $ catkin_make
    or 
    $ catkin_make --only-pkg-with-deps pick_objects
    $ catkin_make --only-pkg-with-deps add_marker

    Autonomously navigate to pick and drop objects (markers).     
    to use turtlebot:
    $ /src/scripts/home_service.sh
    
    to use my_robot: 
    $ /src/scripts/home_service_my_robot.sh

    Virtual Objects/markers:
    $ /src/scripts/add_markers.sh

    To perform mapping of the environment use:
    $ /src/scripts/test_slam.sh
    $ rosrun map_server map_saver





