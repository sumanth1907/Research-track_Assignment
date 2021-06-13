#include "ros/ros.h"
#include "geometry_msgs/Twist.h"
#include "nav_msgs/Odometry.h"
#include "geometry_msgs/PoseWithCovariance.h"
#include "geometry_msgs/Pose.h"
#include "geometry_msgs/Point.h"
#include "node1/random_target.h"
#include <sstream>
#include <iostream>
#include <math.h>

ros::Publisher chat_pub; 

ros::ServiceClient client; 

node1::random_target target; 
geometry_msgs::Point T_vel; 

void positionCallback(const nav_msgs::Odometry::ConstPtr& od)
{
  int k = 2; 
  geometry_msgs::Point p_vel;
  geometry_msgs::Twist vel;

  // read robot postion (x,y)
  p_vel.x = od->pose.pose.position.x; 
  p_vel.y = od->pose.pose.position.y;
	


if( fabs(T_vel.x - p_vel.x) < 0.1 && fabs(T_vel.y - p_vel.y) < 0.1 )
 {	
	
	client.call(target); 

	
	T_vel.x = target.response.pos_x;
  	T_vel.y = target.response.pos_y;

	
	ROS_INFO("Target position [%lf, %lf]", T_vel.x , T_vel.y);
 }
  

  vel.linear.x = k*(T_vel.x - p_vel.x);
  vel.linear.y = k*(T_vel.y - p_vel.y);
  

  chat_pub.publish(vel);

}


int main(int argc, char **argv)
{
 
  ros::init(argc, argv, "assignment1");
  ros::NodeHandle n; 


  client = n.serviceClient<node1::random_target>("/target");
  client.call(target);

  T_vel.x = target.response.pos_x; 
  T_vel.y = target.response.pos_y; 

 
  ROS_INFO("Target position [%lf, %lf]", T_vel.x , T_vel.y); 

  ros::Subscriber pose_sub = n.subscribe("/odom", 1000, positionCallback);


  chat_pub = n.advertise<geometry_msgs::Twist>("/cmd_vel", 1000);
  
  ros::spin();

  return 0;
}
