import os
import unittest

import ament_index_python

import launch
import launch.actions

import launch_testing
import launch_testing.actions
from launch_testing.asserts import assertSequentialStdout

import pytest


@pytest.mark.launch_test
def generate_test_description():

    cmd = os.path.join(ament_index_python.get_package_prefix('test_node'),
                       'lib/test_node/node')

    # This is necessary to get unbuffered output from the process under test
    proc_env = os.environ.copy()
    proc_env['RCUTILS_LOGGING_USE_STDOUT'] = '1'
    proc_env['RCUTILS_LOGGING_BUFFERED_STREAM'] = '0'

    dut_process = launch.actions.ExecuteProcess(
        cmd=[cmd],
        env=proc_env, output='screen'
    )

    return launch.LaunchDescription([
        dut_process,

        # Start tests right away - no need to wait for anything in this example.
        # In a more complicated launch description, we might want this action happen
        # once some process starts or once some other event happens
        launch_testing.actions.ReadyToTest()
    ]), {'dut_process': dut_process}


# These tests will run concurrently with the dut process.  After all these tests are done,
# the launch system will shut down the processes that it started up
class TestGoodProcess(unittest.TestCase):

    def test_count_to_four(self, proc_output):
        # This will match stdout from any process.  In this example there is only one process
        # running
        proc_output.assertWaitFor('Hello, world!! 2', timeout=10, stream='stdout')
        proc_output.assertWaitFor('Hello, world!! 3', timeout=10, stream='stdout')
        proc_output.assertWaitFor('Hello, world!! 4', timeout=10, stream='stdout')
        proc_output.assertWaitFor('Hello, world!! 5', timeout=10, stream='stdout')


@launch_testing.post_shutdown_test()
class TestProcessOutput(unittest.TestCase):

    def test_exit_code(self, proc_info):
        # Check that all processes in the launch (in this case, there's just one) exit
        # with code 0
        launch_testing.asserts.assertExitCodes(proc_info)

    def test_full_output(self, proc_output, dut_process):
        # Using the SequentialStdout context manager asserts that the following stdout
        # happened in the same order that it's checked
        with assertSequentialStdout(proc_output, dut_process) as cm:
            cm.assertInStdout('Starting Up')
            for n in range(1, 4):
                cm.assertInStdout('Hello, world!! {}'.format(n))
