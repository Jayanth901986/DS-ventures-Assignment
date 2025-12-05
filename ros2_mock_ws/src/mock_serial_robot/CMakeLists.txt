cmake_minimum_required(VERSION 3.8)
project(mock_serial_robot)

# -------------------------------------------------------------
# Dependencies
# -------------------------------------------------------------
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(hardware_interface REQUIRED)
find_package(pluginlib REQUIRED)
find_package(ros2_control REQUIRED)

# -------------------------------------------------------------
# Include directories
# -------------------------------------------------------------
include_directories(
  include
)

# -------------------------------------------------------------
# Build the hardware interface plugin
# -------------------------------------------------------------
add_library(mock_system SHARED
  src/mock_system.cpp
)

ament_target_dependencies(mock_system
  rclcpp
  hardware_interface
  pluginlib
  ros2_control
)

# Export plugin description file
pluginlib_export_plugin_description_file(hardware_interface mock_system_plugin.xml)

# -------------------------------------------------------------
# Install library target
# -------------------------------------------------------------
install(
  TARGETS mock_system
  LIBRARY DESTINATION lib
)

# -------------------------------------------------------------
# Install headers
# -------------------------------------------------------------
install(
  DIRECTORY include/
  DESTINATION include
)

# -------------------------------------------------------------
# Install plugin XML
# -------------------------------------------------------------
install(
  FILES mock_system_plugin.xml
  DESTINATION share/${PROJECT_NAME}
)

# -------------------------------------------------------------
# Install launch files
# -------------------------------------------------------------
install(
  DIRECTORY launch/
  DESTINATION share/${PROJECT_NAME}/launch
)

# -------------------------------------------------------------
# Install URDF/Xacro files
# -------------------------------------------------------------
install(
  DIRECTORY urdf/
  DESTINATION share/${PROJECT_NAME}/urdf
)

# -------------------------------------------------------------
# Install config files
# -------------------------------------------------------------
install(
  DIRECTORY config/
  DESTINATION share/${PROJECT_NAME}/config
)

# -------------------------------------------------------------
# Package export
# -------------------------------------------------------------
ament_package()

