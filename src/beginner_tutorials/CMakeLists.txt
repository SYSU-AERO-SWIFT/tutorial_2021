cmake_minimum_required(VERSION 3.0.2)
project(beginner_tutorials)



find_package(catkin REQUIRED COMPONENTS
  roscpp  
  rospy
  std_msgs
  geometry_msgs
  akira_msgs
   message_generation
)



add_message_files(
   FILES
   Akiramsg.msg
 )




generate_messages(
  DEPENDENCIES
  std_msgs
   )


catkin_package(
#  INCLUDE_DIRS include
#  LIBRARIES beginner_tutorials
CATKIN_DEPENDS roscpp rospy std_msgs akira_msgs
#  DEPENDS system_lib
)


include_directories(
# include
  ${catkin_INCLUDE_DIRS}
)


add_executable(pub src/pub.cpp)
target_link_libraries(pub ${catkin_LIBRARIES})
add_dependencies(pub beginner_tutorials_generate_messages_cpp)

add_executable(sub src/sub.cpp)
target_link_libraries(sub ${catkin_LIBRARIES})
add_dependencies(sub beginner_tutorials_generate_messages_cpp)


