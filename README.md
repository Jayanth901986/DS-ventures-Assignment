creating the workspace 
   -mkdir -p ~/ros2_mock_ws/src
package name - ros2 pkg create--build-type ament_cmake mock_serial_robot

Folder structure -
mock_serial_robot/
├── launch/
│   └── mock_robot.launch.py
├── urdf/
│   └── mock_robot.urdf.xacro
├── config/
│   └── controllers.yaml
├── include/
│   └── mock_serial_robot/
│       ├── mock_driver.hpp
│       └── mock_system.hpp
├── src/
│   └── mock_system.cpp
   mock_system_plugin.xml
├── CMakeLists.txt
└── package.xml

Build -
  colcon build --packages-select mock_serial_robot
  source install/setup.bash
Run
  ros2 launch mock_serial_robot mock_robot.launch.py
  ros2 topic list
  ros2 run rqt_plot rqt_plot /joint_states/position[0]
  ros2 topic pub /joint_group_position_controller/commands std_msgs/msg/Float64MultiArray "data: [1.0]"
[open new terminal after exceuting one command and start same process by source and command]
