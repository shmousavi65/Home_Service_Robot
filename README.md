# Home_Service_Robot

This project navigates a turtlebot to pick up an object and drop it off at desired locations.

## Execution
Create the required directories for the workspace:
```
mkdir -p catkin_ws/src
```
Initialize the workspace and clone this repository:
```
cd catkin_ws/src
catkin_init_worksapce
git clone https://github.com/shmousavi65/Home_Service_Robot.git
```
Build the project:
```
cd ..
catkin_make
```
Change the directory:
```
cd src/scripts
```
Run the bash file:
```
./home_service.sh
```
