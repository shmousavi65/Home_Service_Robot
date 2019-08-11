# Home_Service_Robot

The goal of this project is to navigate a home service turtlebot in order to pick up an object and drop it off in desired locations.
Towards this goal, a 2-D occupancy grid map is created for the home environment, using a laser-based SLAM algorithm (gmapping package).

In order to do the pick-up and drop-off tasks at desired locations, ROS Navigation stack is used which runs a version of Uiform Cost Search Algortihm , called Dijkstra's, to perform path-planning between the locations, while avoiding the obstacles in the mapped environment. A node called pick_objects has been created which communicates the desired locations to the Navigator. Note that during the task the adaptive Monte-Carlo algorithm (amcl package) is launched to determine the location of robot in the environment.


## Execution
Create the required directories for the workspace:
```
mkdir -p catkin_ws/src
```
Initialize the workspace and clone this repository:
```
cd catkin_ws/src
git clone https://github.com/shmousavi65/Home_Service_Robot.git
```
Build the project:
```
cd ..
catkin_make
```
Change the directory:
```
cd src/Home_Service_Robot/scripts
```
Run the bash file:
```
./home_service.sh
```
