cmake_minimum_required(VERSION 3.10)
project(bgtotesim_psp)
add_definitions(-DPROGRAM_NAME="bgtotesim_psp")
set(CMAKE_CXX_STANDARD 17)


set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
find_package(catkin REQUIRED)
find_package(OpenCV REQUIRED)

include_directories(${OpenCV_INCLUDE_DIRS})
link_directories(${OpenCV_LIBRARIES})


# Find Boost
find_package(Boost REQUIRED COMPONENTS program_options)
include_directories(${Boost_INCLUDE_DIRS})



## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
find_package(catkin REQUIRED COMPONENTS
  roscpp
  rospy
)

###################################
## catkin specific configuration ##
###################################

catkin_package(
  INCLUDE_DIRS include
)


## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
find_package(catkin REQUIRED COMPONENTS
  roscpp
  rospy
  std_msgs
  sensor_msgs
  tf
  tf_conversions
  message_generation
  std_msgs
  common_msgs
  perception_msgs
  bg_rpc
)

###########
## Build ##
###########

## Specify additional locations of header files
## Your package locations should be listed before other locations
# include_directories(include)
include_directories(
  include/
  ${catkin_INCLUDE_DIRS}
)

# psp nde
add_executable(bgtotesim_psp src/bgtotesim_psp.cpp)
target_link_libraries(bgtotesim_psp ${catkin_LIBRARIES} )
add_dependencies(bgtotesim_psp ${catkin_EXPORTED_TARGETS})




###
# Tests and examples
###
