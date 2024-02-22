from launch import LaunchDescription
from launch_ros.actions import Node

def generate_launch_description():
    return LaunchDescription([
        Node(
            package='homework',
            namespace='homework',
            executable='homework_node',
            name='homework'
        ),
        Node(
            package='answer',
            namespace='answer',
            executable='answer_node',
            name='answer'
        )
    ])