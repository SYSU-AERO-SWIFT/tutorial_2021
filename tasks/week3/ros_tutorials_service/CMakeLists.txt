cmake_minimum_required(VERSION 3.0.2)
project(ros_tutorials_service)

## 这是进行catkin构建时所需的组件包。
## 依赖包是message_generation、 std_msgs和roscpp。如果这些包不存在，在构建过程中会发生错误。
find_package(catkin REQUIRED COMPONENTS message_generation std_msgs roscpp)
## 服务声明： SrvTutorial.srv
add_service_files(FILES SrvTutorial.srv)
## 这是一个设置依赖消息的选项。
## 如果未安装std_msgs，则在构建过程中会发生错误。
generate_messages(DEPENDENCIES std_msgs)
## 这是catkin功能包选项，它描述了库、 catkin构建依赖和依赖系统的功能包。
catkin_package(
LIBRARIES ros_tutorials_service
CATKIN_DEPENDS std_msgs
roscpp
)
## 设置包含目录。
include_directories(${catkin_INCLUDE_DIRS})
## 这是service_server节点的构建选项。
## 设置可执行文件、目标链接库和附加依赖项。
add_executable(service_server src/service_server.cpp)
add_dependencies(service_server ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
target_link_libraries(service_server ${catkin_LIBRARIES})
## 这是节点的构建选项。
add_executable(service_client src/service_client.cpp)
add_dependencies(service_client ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
target_link_libraries(service_client ${catkin_LIBRARIES})