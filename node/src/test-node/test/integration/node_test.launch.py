# import os

from launch import LaunchDescription
from launch.actions import ExecuteProcess
import launch_testing.actions


def generate_test_description():

    # testExecutable = os.getenv('TEST_EXECUTABLE')
    f = '/home/michael/Github/devops-test/build/test_node/test/integration/node_tester'
    testExecutable = f

    return LaunchDescription([

        ExecuteProcess(
          cmd=[testExecutable],
        ),

        # Start tests right away - no need to wait for anything in this example
        launch_testing.actions.ReadyToTest()
    ])
