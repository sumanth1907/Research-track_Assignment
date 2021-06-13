# Research Track I - Final_Assignment (pakanti sumanth s5058417 )
## Overview

**Robot exhibits the following behaviour based on the user's input:** 
1. Move randomly in the environment and reach the random coordinates.
2. Directly asks the user for the target coordinates and reaches it.
3. Start following the external walls.
4. Stop in the last position


## Contents of the Package
- **Rand_Server.cpp:** Node used for generating random coordinates out of the 6 coordinates, [(-4,-3);(-4,2);(-4,7);(5,-7);(5,-3);(5,1)]
- **robot_interface.cpp:** Node used for getting input from user to control the robot in different modes
- **robot_target.srv:** Custom service file for x and y coordinates
- **wall_follow_service_m.py:** This service file makes the robot follow the walls
- **simulation_gmapping.launch:** Launch file for executing the simulator 
- **move_base.launch:** Launch file for executing move_base
- **robot_launch.launch:** Launch file for executing the main user interface
## How to run the code
First go the ROS workspace and type this command:
```
catkin_make
```
Launch the simulator using the following command:
```
roslaunch final_assignment simulation_gmapping.launch
```
Next, type the following command to move_base:
```
roslaunch final_assignment move_base.launch
```
Finally, type the following command to execute the User Interface:
```
roslaunch final_assignment robot_launch.launch
```
