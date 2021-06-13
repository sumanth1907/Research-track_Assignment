# first_assignments

Research_Track_first assignment   (Pakanati Sumanth)(matricola s5058417)
The assignment requires controlling a holonomic robot in a 2d space with a simple 2d simulator

### A brief description of the used Algorithm
1. The robot asks for a random target, with both coordinates in the interval (-6.0, 6.0).
2. The robot reaches the target.
3. it will go to step 1.


### content of package
First node: (assignment1)
ROS publisher: publishing the robot speed
ROS subscriber: subscribe for robot position
ROS client: receiving a random target

Second node: (node1)
ROS server: Service Server replies to the client with a random target



##Run the simulator

To start rosmaster

 'roscore'
 
 To launch the simulator
 
 'rosrun stage_ros stageros $(rospack find assignment1)/world/exercise.world'

Run the service node
'rosrun node1 node1'

Run the First node
'rosrun assignment1 assignment1'

## Software architecture
![rosgraph](https://user-images.githubusercontent.com/73032093/115158081-febaab00-a07b-11eb-855d-b8fdd51d1f2f.png)

