/** @file
 * @author @berkshiregrey.com
 * @copyright Copyright (c) 2018-, Berkshire Grey, Inc. All rights reserved.
 * @license Berkshire Grey, Inc., CONFIDENTIAL
 */

#include "bgtotesim_psp.h"

#include <actionlib/client/simple_action_client.h>
#include <actionlib/client/terminal_state.h>
#include <chrono>
#include <condition_variable>
#include <mutex>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <ros/ros.h>
#include <sstream>
#include <vector>

#include <cv_bridge/cv_bridge.h>

#include <common_msgs/SoftwareTriggerAction.h>



int main(int argc, char **argv) 
{
  ros::init(argc, argv, "psp");
  ros::NodeHandle nh("");
  ros::NodeHandle nh_local("~");
}