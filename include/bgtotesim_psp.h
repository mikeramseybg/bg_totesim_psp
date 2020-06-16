/** @file
 * @author @berkshiregrey.com
 * @copyright Copyright (c) 2018-, Berkshire Grey, Inc. All rights reserved.
 * @license Berkshire Grey, Inc., CONFIDENTIAL
 */

#ifndef BGTOTESIM_PSP_H
#define BGTOTESIM_PSP_H


#include <cmath>
#include <mutex>
#include <condition_variable>
#include <memory>
#include <thread>
#include <map>
#include <chrono>
#include <sstream>
#include <vector>
#include <atomic>
#include <ctime>   // localtime
#include <sstream> // stringstream
#include <iomanip> // put_time

// Ros
#include <ros/ros.h>

// Topic Synchronization
#include <message_filters/subscriber.h>
#include <message_filters/synchronizer.h>
#include <message_filters/sync_policies/exact_time.h>


#include <ros/ros.h>
#include <sensor_msgs/Image.h>
#include <actionlib/server/simple_action_server.h>
#include <actionlib/client/simple_action_client.h>

#include <common_msgs/SoftwareTriggerAction.h>

#include <actionlib/client/simple_action_client.h>
#include <actionlib/client/terminal_state.h>

#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <cv_bridge/cv_bridge.h>


#include <boost/program_options.hpp>
#include <grpcpp/grpcpp.h>

#include "bgtotesim_psp_orchestrator_settings.h"

using namespace std;
// =============================================================================
// The nexus is simply an object that tracks the state of the psp
// The nexus tracks the current image folder (where image and camera info is saved)
//
// Typical nexus state flow:
//
//  awaiting software trigger -> awaiting image set (repeat until totesim finishes)
//    -> enters into a Ready state for further operations (waiting for trigger)   
class PSPNexus final
{
public:

    // Accessor for the nexus state
    const PSPState& getState() const
    {
        return m_state;
    }

    // Accessor for the current folders name
    const string& getFolderName() const
    {
        return m_folderName;
    }

    // Setter for the nexus state
    void setState(PSPState state)
    {
        m_state = state;
    }
    
    // Update target folder name for image serialization
    void setFolderName()
    {
        // Sample format: (Date_Time) 2020-06-10 15:56:37
        m_folderName = currentDateTime();
        printf(" ImageFolder : %s \n", m_folderName.c_str());
    }
    
private:

    // Build date and time string used for folder naming
    string currentDateTime()
    {
        auto now = chrono::system_clock::now();
        auto time_t = chrono::system_clock::to_time_t(now);

        stringstream ss;
        ss << put_time(std::localtime(&time_t), "%Y-%m-%d %X");
        return ss.str();
    }

private:

    PSPState m_state = PSPState::PSPS_Ready;
    string m_folderName = std::string("None");
};
// =============================================================================
 
class PSPNode final
{
public:
    PSPNode() {}
    ~PSPNode() {}

    // Initialize node
    bool initialize();
    bool ok() const { return m_ok; }

    void setNexusState(const PSPState& state)
    {
        m_nexus.setState(state);
    }

    const PSPState& getState() const
    {
        return m_nexus.getState();
    }

private:
    // Callback for  server
    void triggerCallback(const common_msgs::SoftwareTriggerGoalConstPtr& /*goal*/);

private:
    // Action server 
    using TriggerActionServerT = actionlib::SimpleActionServer<common_msgs::SoftwareTriggerAction>;
    unique_ptr<TriggerActionServerT> m_triggerServer;

    bool m_ok = true;

    PSPNexus m_nexus;

};

// =============================================================================


#endif // BGTOTESIM_PSP_H