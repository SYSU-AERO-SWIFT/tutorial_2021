cmake_minimum_required(VERSION 3.0.2)
project(akira_msgs)


find_package(catkin REQUIRED)

find_package(catkin REQUIRED COMPONENTS roscpp rospy message_generation std_msgs geometry_msgs)
add_message_files(
  FILES
  Akiramsg.msg
  # Message2.msg
)




generate_messages(
 DEPENDENCIES
 geometry_msgs
)
catkin_package(

CATKIN_DEPENDS message_runtime

)



catkin_package(
#  INCLUDE_DIRS include
#  LIBRARIES akira_msgs
#  CATKIN_DEPENDS other_catkin_pkg
#  DEPENDS system_lib
)


