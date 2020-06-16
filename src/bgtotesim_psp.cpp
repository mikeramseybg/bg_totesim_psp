/** @file
 * @author @berkshiregrey.com
 * @copyright Copyright (c) 2018-, Berkshire Grey, Inc. All rights reserved.
 * @license Berkshire Grey, Inc., CONFIDENTIAL
 */

#include "bgtotesim_psp.h"


#include <bg_rpc/bind.hpp>
#include <bg_rpc/grpc/sync_stub.hpp>
#include <bg_rpc/sync_client_method.hpp>
#include <bg_rpc/server_interface.hpp>
#include <bg_rpc/sync_server.hpp>
//#include <hyper_scanner/proto/parcel_event.grpc.pb.h>

using namespace bg::comms::rpc;



// =============================================================================
bool PSPNode::initialize()
{
    printf("PSPNode::initialize \n");

    // Local nodehandle
    ros::NodeHandle nh;

    // create simple action server to use for "software trigger"
    m_triggerServer.reset(new TriggerActionServerT(
        nh, TRIGGER_NAME,
        boost::bind(&PSPNode::triggerCallback, this, _1),
        false));
    m_triggerServer->start();
    ros::spin();
  
}
// =============================================================================
void PSPNode::triggerCallback(const common_msgs::SoftwareTriggerGoalConstPtr& /*goal*/)
{
      
    printf(" --- triggerCallback\n");
    printf("dog\n");
    m_ok = false;
}
// =============================================================================
int main(int argc, char **argv) 
{
    printf("====================================================================\n");
    printf("                 BGToteSim Primary Scanner Proxy (PSP)\n");
    printf("====================================================================\n");

    ros::init(argc, argv, "psp");
    // PSPnode goes into it's own thread
    PSPNode psp_node;
    psp_node.initialize();

    printf("==");

    // ros::Rate spin_rate(30.0f);
    while(psp_node.ok())
    {
        // ros::spinOnce();
        // spin_rate.sleep();
        printf(".");
    }

    printf("hi");
}

// =============================================================================
