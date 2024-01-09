#include <ros/ros.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>

// Define a client for to send goal requests to the move_base server through a SimpleActionClient
typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;

int main(int argc, char** argv){
  // Initialize the simple_navigation_goals node
  ros::init(argc, argv, "simple_navigation_goals");

  //tell the action client that we want to spin a thread by default
  MoveBaseClient ac("move_base", true);

  // Wait 5 sec for move_base action server to come up
  while(!ac.waitForServer(ros::Duration(5.0))){
    ROS_INFO("Waiting for the move_base action server to come up");
  }

  move_base_msgs::MoveBaseGoal goal;

  // set up the frame parameters
  goal.target_pose.header.frame_id = "map";
  goal.target_pose.header.stamp = ros::Time::now();

  // Define a position and orientation for the robot to reach
  goal.target_pose.pose.position.x = 2.0;
  goal.target_pose.pose.position.y = 2.0;
  goal.target_pose.pose.orientation.w = 1.0;

   // Send the goal position and orientation for the robot to reach
  ROS_INFO("Sending goal, x\%f, y\%f",goal.target_pose.pose.position.x, goal.target_pose.pose.position.y );
  ac.sendGoal(goal);

  // Wait an infinite time for the results
  ac.waitForResult();

  // Check if the robot reached its goal
  if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED)
    ROS_INFO("Hooray, reached pick up locaiton");
  else
    ROS_INFO("The base failed to reach pick up location");
    
  ros::Duration(5).sleep();
  //drop off 
  

  goal.target_pose.pose.position.x = -2.0;
  goal.target_pose.pose.position.y = -2.0;
  goal.target_pose.pose.orientation.w = 1.0;

   // Send the goal position and orientation for the robot to reach
  ROS_INFO("Sending goal, x\%f, y\%f",goal.target_pose.pose.position.x, goal.target_pose.pose.position.y );
  ac.sendGoal(goal);

  // Wait an infinite time for the results
  ac.waitForResult();

  // Check if the robot reached its goal
  if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED)
    ROS_INFO("Hooray, reached dropoff location");
  else
    ROS_INFO("The base failed to reach dropoff location");
    

  return 0;
}



/*









#include <ros/ros.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>
#include <std_msgs/String.h>

#include <visualization_msgs/Marker.h>

// Define a client for to send goal requests to the move_base server through a SimpleActionClient
typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;

float check_loc_x = 0.0;
float check_loc_y = 0.0;

void received_location (const visualization_msgs::Marker location)
    {
     
    float x = location.pose.position.x;
    float y = location.pose.position.y; 
    
   // ROS_INFO(" x axis=\%f & y axis=\%f ", x,y );

 //tell the action client that we want to spin a thread by default. It also tells the action client
  //to start a thread to call ros::spin().
  MoveBaseClient ac("move_base", true);

  // Wait 5 sec for move_base action server to come up
  while(!ac.waitForServer(ros::Duration(5.0))){
    ROS_INFO("Waiting for the move_base action server to come up");
  }
  

// Pick up 

  // Create a new goal to send to move_base
  move_base_msgs::MoveBaseGoal goal;
  

  // set up the frame parameters
  goal.target_pose.header.frame_id = "map";
  goal.target_pose.header.stamp = ros::Time::now();

if ((check_loc_x != x) || (check_loc_y!=y  )){
  // Define a position and orientation for the robot to reach
  ROS_INFO ("New goal targets received");
  check_loc_x = x;
  check_loc_y = y;
  goal.target_pose.pose.position.x = x;
  goal.target_pose.pose.position.y = y;
  goal.target_pose.pose.orientation.w = 1.0;
  
  }
  
  else 
  {
  goal.target_pose.pose.position.x = x;
  goal.target_pose.pose.position.y = y;
  goal.target_pose.pose.orientation.w = 1.0;
  }

  // Send the goal position and orientation for the robot to reach
  ROS_INFO("Sending to pick up location");
  ac.sendGoal(goal);  

  // Wait an infinite time for the results
  ac.waitForResult();

  // Check if the robot reached its pick up goal
  if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED)
    {
      ROS_INFO("Father I have reached the Pick up Location");
      //ros::Duration(5).sleep();
    }
  else
    {
      ROS_INFO("Father you have failed me to reach Pick up");
      ros::Duration(5).sleep();
    }
  

    }


int main(int argc, char** argv){
  // Initialize the simple_navigation_goals node i.e. connect to ros 
  ros::init(argc, argv, "pick_objects");

//15.09.22 >>>
    ros::NodeHandle n;
    ros::Subscriber subscribe_location = n.subscribe("/visualization_marker",1,received_location);

//<<<



 
    
//}
 
  //  ros::spinOnce();
    ros::spin();
 
  return 0;
}

*/
