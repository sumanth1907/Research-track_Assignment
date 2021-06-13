#include "ros/ros.h"
#include "nav_msgs/Odometry.h"
#include "geometry_msgs/Twist.h"
#include "move_base_msgs/MoveBaseActionGoal.h"
#include "final_assignment/robot_target.h"
#include "std_srvs/SetBool.h"



ros::Publisher pub;
ros::Subscriber sub;
move_base_msgs::MoveBaseActionGoal des_pos;
float x_position;   
float y_position;
final_assignment::robot_target Rand_Pos;
std_srvs::SetBool wall_follower;



void positionCallback(const nav_msgs::Odometry::ConstPtr& msg) 
{
	x_position = msg->pose.pose.position.x;
	y_position = msg->pose.pose.position.y;
}

int main(int argc, char **argv)
{
  	ros::init(argc,argv,"robot_interface");		
   	ros::NodeHandle n;
   			
	ros::Rate r(0.5);  

   	pub = n.advertise<move_base_msgs::MoveBaseActionGoal>("move_base/goal",1000);  
   	sub = n.subscribe("/odom", 1000, positionCallback);

   	float option;      
   	float des_x;   
   	float des_y;  
   	float x_coord[]={-4,-4,-4, 5, 5,5};   
   	float y_coord[]={-3, 2, 7,-7,-3,1};  
	bool istrue = false;      


	ros::ServiceClient client1 = n.serviceClient<final_assignment::robot_target>("random_target");  
	ros::ServiceClient client2 = n.serviceClient<std_srvs::SetBool>("/wall_follower_switch");        
   	
        while(option!=-1)
 	{
                ROS_INFO("final_project");
		ROS_INFO("1. Robot moves in the environment randomly");
		ROS_INFO("2. Robot moves to the user's desired position");
		ROS_INFO("3. Robot follows the walls");
		ROS_INFO("4. Robot stops in the last position");
		ROS_INFO("-1 to terminate the program");
                ROS_INFO("Please chose your desired option");
   		scanf("%f",&option);
		
		ros::spinOnce();
		r.sleep();     
		
		if(option==1){
	                       
		
				client1.call(Rand_Pos);
				des_pos.goal.target_pose.header.frame_id="map";
				des_pos.goal.target_pose.pose.orientation.w=1;
				des_pos.goal.target_pose.pose.position.x=Rand_Pos.response.pos_x;
				des_pos.goal.target_pose.pose.position.y=Rand_Pos.response.pos_y;
				ROS_INFO("Random Coordintes: [%f,%f]",Rand_Pos.response.pos_x,Rand_Pos.response.pos_y);
				r.sleep();
				pub.publish(des_pos);
				
				while((abs(Rand_Pos.response.pos_x - x_position)>=1)||(abs(Rand_Pos.response.pos_y- y_position)>=1))
				{
				ROS_INFO("Current position of Robot: [%f,%f]",x_position, y_position);					
				ros::spinOnce();
				r.sleep();
				}

				

		}
   		
   		
		if(option==2){		
				ROS_INFO("given X coordinates (-4,-4,-4, 5, 5, 5)");
				ROS_INFO("given Y coordinates (-3, 2, 7,-7,-3,1)");
				ROS_INFO("insert the given X coordinates");
				scanf("%f",&des_x);
				ROS_INFO("insert the given Y coordinates");
				scanf("%f",&des_y);

			        for (int i = 0; i <= 5; i++)   
				{
				   if((des_x==x_coord[i])&&(des_y==y_coord[i])){
				   istrue = true;
					}
                                }

				if(istrue==true)    
				{
				des_pos.goal.target_pose.header.frame_id="map";
				des_pos.goal.target_pose.pose.orientation.w=1;
				des_pos.goal.target_pose.pose.position.x=des_x;
				des_pos.goal.target_pose.pose.position.y=des_y;
				pub.publish(des_pos);
				while((abs(des_x - x_position)>=1)||(abs(des_y - y_position)>=1))
				{
				ROS_INFO("current position of robot: [%f,%f]",x_position, y_position);					
				ros::spinOnce();
				r.sleep();
				}
				}

				else      
				{	
				ROS_INFO("incorrect coordinates entered,sorry please try again.");
				}
				istrue = false;
			    }
		
			if(option==3){    
		
				ROS_INFO("Robot starts following the walls!");
				wall_follower.request.data=true;
				client2.call(wall_follower); 
			}
			
		
			if(option==4){  
		
				wall_follower.request.data=false;
				client2.call(wall_follower);
				des_pos.goal.target_pose.header.frame_id="map";
				des_pos.goal.target_pose.pose.orientation.w=1;
				des_pos.goal.target_pose.pose.position.x=x_position;
				des_pos.goal.target_pose.pose.position.y=y_position;
				pub.publish(des_pos);
				ROS_INFO("Robot stops");
 			}
          
		
    	}

	ros::spin();
    	return 0;
} 
