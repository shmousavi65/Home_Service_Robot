#include <ros/ros.h>
#include <visualization_msgs/Marker.h>
#include <nav_msgs/Odometry.h>
#include <std_msgs/UInt8.h>


unsigned int state_value;



void sub_state_callback(const std_msgs::UInt8 ste)
{
    state_value = ste.data;
    
    if ( (state_value == 1) || (state_value == 2) ){
       ROS_INFO_STREAM("The received data on /robot_state_topic is:"<< state_value);
    }
}




int main( int argc, char** argv )
{


  ros::init(argc, argv, "add_markers");
  ros::NodeHandle n;
  ros::Publisher marker_pub = n.advertise<visualization_msgs::Marker>("visualization_marker", 1);
//  ros::Subscriber sub1 = n.subscribe("/odom", 10, odom_data_callback);
  ros::Subscriber sub_state = n.subscribe<std_msgs::UInt8>("/robot_state_topic",1, sub_state_callback);


  ros::Rate r(20);

/////////// Marker Information //////////////

  // Set our initial shape type to be a cube
  uint32_t shape = visualization_msgs::Marker::CUBE;

  visualization_msgs::Marker marker;
  // Set the frame ID and timestamp.  See the TF tutorials for information on these.
  marker.header.frame_id = "map";
  marker.header.stamp = ros::Time::now();

  // Set the namespace and id for this marker.  This serves to create a unique ID
  // Any marker sent with the same namespace and id will overwrite the old one
  marker.ns = "add_marker";
  marker.id = 0;

  // Set the marker type.  Initially this is CUBE, and cycles between that and SPHERE, ARROW, and CYLINDER
  marker.type = shape;

  // Set the marker action.  Options are ADD, DELETE, and new in ROS Indigo: 3 (DELETEALL)
  marker.action = visualization_msgs::Marker::ADD;

  // Set the scale of the marker -- 1x1x1 here means 1m on a side
  marker.scale.x = .5;
  marker.scale.y = .5;
  marker.scale.z = .5;

  // Set the color -- be sure to set alpha to something non-zero!
  marker.color.r = 0.0f;
  marker.color.g = 1.0f;
  marker.color.b = 0.0f;
  marker.color.a = 1.0;

///////////////////////


  marker.pose.position.x = 0;
  marker.pose.position.y = 1;
  marker.pose.position.z = 0;
  marker.pose.orientation.x = 0.0;
  marker.pose.orientation.y = 0.0;
  marker.pose.orientation.z = 0.0;
  marker.pose.orientation.w = .5;

  marker.lifetime = ros::Duration();
 

while (ros::ok())
  {
    
    if (state_value==1){
       marker.action = visualization_msgs::Marker::DELETE;
    }

    if (state_value==2){

       marker.pose.position.x = -5;
       marker.pose.position.y = 1;
       marker.pose.position.z = 0;
       marker.pose.orientation.x = 0.0;
       marker.pose.orientation.y = 0.0;
       marker.pose.orientation.z = 0.0;
       marker.pose.orientation.w = .5;       
       marker.action = visualization_msgs::Marker::ADD;
    }
   

    marker_pub.publish(marker);
 // Set the pose of the marker.  This is a full 6DOF pose relative to the frame/time specified in the header



  





    // Publish the marker
//    while (marker_pub.getNumSubscribers() < 1)
//    {
//      if (!ros::ok())
//      {
//        return 0;
//      }
//      ROS_WARN_ONCE("Please create a subscriber to the marker");
//      sleep(1);
//    }



    
//  marker.lifetime = ros::Duration();


//    ros::spinOnce();
//    ROS_INFO_STREAM("The x value is"<<robo_y);
//    r.sleep();

    //ros::Duration(10).sleep();

    //marker.action = visualization_msgs::Marker::DELETE;



//    marker.pose.position.x = -5;
//    marker.pose.position.y = 0;
//    marker.pose.position.z = 0;
//    marker.pose.orientation.x = 0.0;
//    marker.pose.orientation.y = 0.0;
//    marker.pose.orientation.z = 0.0;
//    marker.pose.orientation.w = .5;



//   marker.lifetime = ros::Duration();
//   marker_pub.publish(marker);

    //ros::Duration(5).sleep();
    
    //marker.action = visualization_msgs::Marker::ADD;  

    //marker_pub.publish(marker);

       
   ros::spinOnce();
    

    // Cycle between different shapes
   r.sleep();
  }

return 0;
}
