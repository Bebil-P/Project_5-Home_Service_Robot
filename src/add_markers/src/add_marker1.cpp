#include <ros/ros.h>
#include <visualization_msgs/Marker.h>

//4HSR 
//#include "geometry_msgs/Twist.h"

  
int main( int argc, char** argv )
   {
     ros::init(argc, argv, "add_marker1");
     ros::NodeHandle n;
     ros::Rate r(1);
     ros::Publisher marker_pub = n.advertise<visualization_msgs::Marker>("visualization_marker", 1);
     
     //4HSR 
    // ros::Publisher pick_drop_pub = n.advertise<geometry_msgs::Twist>("pick_drop_loc", 10);
   
   
   
     // Set our initial shape type to be a cube
     uint32_t shape = visualization_msgs::Marker::CUBE;
     int option = 1;  
     float dest = 0.0;
     while (ros::ok())
     {
       visualization_msgs::Marker marker;
       // Set the frame ID and timestamp.  See the TF tutorials for information on these.
       //marker.header.frame_id = "/my_frame";
       marker.header.frame_id = "/map";
       marker.header.stamp = ros::Time::now();
   
       // Set the namespace and id for this marker.  This serves to create a unique ID
       // Any marker sent with the same namespace and id will overwrite the old one
       marker.ns = "add_marker1";
       marker.id = 0;
   
       // Set the marker type.  Initially this is CUBE, and cycles between that and SPHERE, ARROW, and CYLINDER
       marker.type = shape;
   
       // Set the marker action.  Options are ADD, DELETE, and new in ROS Indigo: 3 (DELETEALL)
      // marker.action = visualization_msgs::Marker::ADD;
     switch (option)
     {
       case 1: 
       marker.action = visualization_msgs::Marker::ADD;
       option = 2;
       dest = 0.0;
       ROS_INFO("at case 1");
       break;
       
       case 2:
       marker.action = visualization_msgs::Marker::DELETE;
       option = 3;
       ROS_INFO("at case 2");
       break;
       
       case 3:
       marker.action = visualization_msgs::Marker::ADD;
       option = 4;
       dest = 4.0;
       ROS_INFO("at case 3");
       break;
       
       case 4:
       marker.action = visualization_msgs::Marker::DELETE;
       option = 1;
       ROS_INFO("at case 4");
       break;
      
      }
   
   
   
   
       // Set the pose of the marker.  This is a full 6DOF pose relative to the frame/time specified in the header
       marker.pose.position.x = 2.0-dest;
       marker.pose.position.y = 2.0-dest;
       marker.pose.position.z = 0.0;
       marker.pose.orientation.x = 0.0;
       marker.pose.orientation.y = 0.0;
       marker.pose.orientation.z = 0.0;
       marker.pose.orientation.w = 1.0;
   
       // Set the scale of the marker -- 1x1x1 here means 1m on a side
       marker.scale.x = 0.5;
       marker.scale.y = 0.5;
       marker.scale.z = 0.5;
   
       // Set the color -- be sure to set alpha to something non-zero!
       marker.color.r = 0.0f;
       marker.color.g = 1.0f;
       marker.color.b = 0.0f;
       marker.color.a = 1.0;
   
       marker.lifetime = ros::Duration();
   
     // Publish the marker
       while (marker_pub.getNumSubscribers() < 1)
       {
         if (!ros::ok())
         {
           return 0;
         }
         ROS_WARN_ONCE("Please create a subscriber to the marker");
         sleep(1);
       }
       marker_pub.publish(marker);
        ros::Duration(5).sleep();
       // Cycle between different shapes
     
  
      r.sleep();
    }
  }
