execute_process(COMMAND "/home/linhuangnan/Desktop/tutorial_2021/tutorial_2021/tasks/week3/catkin_simulate_ws/build_isolated/arbotix_python/catkin_generated/python_distutils_install.sh" RESULT_VARIABLE res)

if(NOT res EQUAL 0)
  message(FATAL_ERROR "execute_process(/home/linhuangnan/Desktop/tutorial_2021/tutorial_2021/tasks/week3/catkin_simulate_ws/build_isolated/arbotix_python/catkin_generated/python_distutils_install.sh) returned error code ")
endif()
