#include <ros/ros.h>
#include <visualization_msgs/Marker.h>
  
//17.09.22  >>>
#include <move_base_msgs/MoveBaseAction.h>  
#include <nav_msgs/Odometry.h>

//  <<<

bool goal_reached = false; 
float pick_up = 2.0;
float drop_off = - 2.0;
int goal = pick_up;
float odom_y = 0;

int count = 0;

void goal_status (const move_base_msgs::MoveBaseActionResult goal_update)
    {
    int status = goal_update.status.status;
    ROS_INFO ("Reached goal = , \%d", status);
    goal_reached = true; 
    }


void pose_status (const nav_msgs::Odometry pose_update)
    {
    float odom_x = pose_update.pose.pose.position.x ;
     odom_y = pose_update.pose.pose.position.y ;
     //ROS_INFO ("pose_status = , \%f ,\%f" , odom_x, odom_y);
   
    }



int main( int argc, char** argv )
   {
     ros::init(argc, argv, "add_markers");
     ros::NodeHandle n;
     ros::Rate r(1);
     ros::Publisher marker_pub = n.advertise<visualization_msgs::Marker>("visualization_marker", 1, true);
   
     ros::Subscriber goal_sub = n.subscribe("/move_base/result",1,goal_status);
     
     ros::Subscriber pose_sub = n.subscribe("/odom",1,pose_status);
   
     // Set our initial shape type to be a cube
     uint32_t shape = visualization_msgs::Marker::CUBE;

     while (ros::ok())
     {
       visualization_msgs::Marker marker;
       // Set the frame ID and timestamp.  See the TF tutorials for information on these.
       //marker.header.frame_id = "/my_frame";
       marker.header.frame_id = "/map";
       marker.header.stamp = ros::Time::now();
   
       // Set the namespace and id for this marker.  This serves to create a unique ID
       // Any marker sent with the same namespace and id will overwrite the old one
       marker.ns = "add_markers";
       marker.id = 0;
       
       // Set the marker type.  Initially this is CUBE, and cycles between that and SPHERE, ARROW, and CYLINDER
       marker.type = shape;
     
       // Set the pose of the marker.  This is a full 6DOF pose relative to the frame/time specified in the header
       marker.pose.position.x = goal;
       marker.pose.position.y = goal;
       marker.pose.position.z = 0.0;
       
       marker.pose.orientation.x = 0.0;
       marker.pose.orientation.y = 0.0;
       marker.pose.orientation.z = 0.0;
       marker.pose.orientation.w = 1.0;
   
       // Set the scale of the marker -- 1x1x1 here means 1m on a side
       marker.scale.x = 0.3;
       marker.scale.y = 0.3;
       marker.scale.z = 0.3;
   
       // Set the color -- be sure to set alpha to something non-zero!
       marker.color.r = 0.0f;
       marker.color.g = 1.0f;
       marker.color.b = 0.0f;
       marker.color.a = 1.0;
   
       marker.lifetime = ros::Duration();
   
     // Publish the marker
     /*  while (marker_pub.getNumSubscribers() < 1)
       {
         if (!ros::ok())
         {
           return 0;
         }
         ROS_WARN_ONCE("Please create a subscriber to the marker");
         sleep(1);
       }
       */
       
       
       if (goal_reached)
       {
            goal_reached = false;
            if ( (odom_y > 1.8) && (goal == pick_up) )
            {
            
            goal = drop_off;
            marker.action = visualization_msgs::Marker::DELETE;
            marker_pub.publish(marker);
            ROS_INFO ( "first goal reached ");
            ros::Duration(5).sleep();
            count = 3;

            }
            else if ((odom_y < -1.8 ) && (goal== drop_off))
            {
            count = 1;
            marker.action = visualization_msgs::Marker::ADD;
            ROS_INFO ("second goal reached");
            marker_pub.publish(marker);
            
            }
            
        }
      else if (count < 1) 
      {
      count = 2;
     
       marker.action = visualization_msgs::Marker::ADD;
       marker_pub.publish(marker);
      }
      else if (count > 2)
      { 
      // marker.action = visualization_msgs::Marker::ADD;
       marker.action = visualization_msgs::Marker::DELETE;
       marker_pub.publish(marker);
      } 
       // Cycle between different shapes
       
       ros::spinOnce();
       //ros::spin();
  
      r.sleep();
    }
  }
