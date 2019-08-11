#include <ros/ros.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>
#include <std_msgs/UInt8.h>


// Define a client for to send goal requests to the move_base server through a SimpleActionClient
typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;


int main(int argc, char** argv){
  // Initialize the simple_navigation_goals node
  ros::init(argc, argv, "pick_objects");

  //tell the action client that we want to spin a thread by default
  MoveBaseClient ac("move_base", true);



  // Wait 5 sec for move_base action server to come up
  while(!ac.waitForServer(ros::Duration(5.0))){
    ROS_INFO("Waiting for the move_base action server to come up");
  }

  ros::NodeHandle n;
  // Define a publisher for the state of the robot
  ros::Publisher pub_state = n.advertise<std_msgs::UInt8>("/robot_state_topic",1); 

  move_base_msgs::MoveBaseGoal goal;
  std_msgs::UInt8 robot_state;


  // set up the frame parameters
  goal.target_pose.header.frame_id = "map";
  goal.target_pose.header.stamp = ros::Time::now();



  // Define a position and orientation for the robot to reach
//First Goal
  goal.target_pose.pose.position.y = 1.0;
  goal.target_pose.pose.orientation.w = .5;

   // Send the goal position and orientation for the robot to reach
  ROS_INFO("Sending goal");
  ac.sendGoal(goal);

  // Wait an infinite time for the results
  ac.waitForResult();

  // Check if the robot reached its goal
  if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED){
    ROS_INFO("Hooray, the robot reached the pick up zone!");
    robot_state.data = 1;
    pub_state.publish(robot_state);
  }
  else
    ROS_INFO("The base failed to move for some reason");


//Second Goal
  goal.target_pose.pose.position.x = -5.0;
  goal.target_pose.pose.position.y = 1;
  goal.target_pose.pose.orientation.w = .5;



  // Wait 5 sec for
  ros::Duration(5).sleep();
   // Send the goal position and orientation for the robot to reach
  ROS_INFO("Sending goal 2");
  ac.sendGoal(goal);

  // Wait an infinite time for the results
  ac.waitForResult();

  // Check if the robot reached its goal
  if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED){
    ROS_INFO("Hooray, the reached the drop-off zone!");
    robot_state.data = 2;
    pub_state.publish(robot_state);
  }
  else
    ROS_INFO("The base failed to move some reason");

  ros::Duration(2).sleep();

  return 0;
}
