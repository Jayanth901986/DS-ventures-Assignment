from launch import LaunchDescription
from launch_ros.actions import Node
from launch.substitutions import Command
from launch_ros.parameter_descriptions import ParameterFile
from ament_index_python.packages import get_package_share_directory
import os

def generate_launch_description():
    pkg_share = get_package_share_directory('mock_serial_robot')

    robot_description_content = Command([
        "xacro ",
        os.path.join(pkg_share, "urdf", "mock_robot.urdf.xacro")
    ])

    robot_description = {"robot_description": robot_description_content}

    controllers_yaml = ParameterFile(
        os.path.join(pkg_share, "config", "controllers.yaml"),
        allow_substs=True
    )

    return LaunchDescription([
        Node(
            package="controller_manager",
            executable="ros2_control_node",
            parameters=[robot_description, controllers_yaml],
            output="screen"
        ),

        Node(
            package="controller_manager",
            executable="spawner",
            arguments=["joint_state_broadcaster"],
            output="screen"
        ),

        Node(
            package="controller_manager",
            executable="spawner",
            arguments=["joint_group_position_controller"],
            output="screen"
        )
    ])
