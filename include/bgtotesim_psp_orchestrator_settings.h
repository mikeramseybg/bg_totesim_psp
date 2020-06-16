/** @file
 * @author @berkshiregrey.com
 * @copyright Copyright (c) 2018-, Berkshire Grey, Inc. All rights reserved.
 * @license Berkshire Grey, Inc., CONFIDENTIAL
 */

#ifndef BGTOTESIM_PSP_ORCHESTRATOR_SETTINGS_H
#define BGTOTESIM_PSP_ORCHESTRATOR_SETTINGS_H

#include <string>

// =============================================================================
std::string TOTESIM_IP = std::string("10.0.0.7:50051");
std::string PSP_PORT = std::string("50053");
std::string TRIGGER_NAME = std::string("psp");
const int INITIAL_PSP2TOTESIM_TIMOUT = 2; // length of time out in seconds for totesim ping
const int MAX_THREAD_WORKERS = 10;
std::string current_folder = std::string ("BGInvalid"); // worker thread mgr creates/maintains
std::string IMAGE_TOPIC = std::string("psp");
const int MAX_MESSAGE_LENGTH = 50 * 1024 * 1024; // should match bgtotesim
std::string PSP_CONFIGURATION_FILE = std::string ("psp_feature_config.yaml");
std::string ORCHESTRATOR_CONFIGURATION_FILE = std::string ("orchestrator_feature_config.yaml");

// =============================================================================

enum class PSPState : unsigned int
{
    PSPS_EmptyState = 0, //  totesim
    PSPS_AwaitingSoftwareTrigger = 1, // awaiting a software trigger to invoke totesim
    PSPS_AwaitingImageSet = 2, // in the image transfer loop
    PSPS_Ready = 3, // generic catch-all, psp is fully stood-up
    PSPS_Error = 4 // rpc failure
};

// =============================================================================

#endif // BGTOTESIM_PSP_ORCHESTRATOR_SETTINGS_H