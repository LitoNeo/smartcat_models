cmake_minimum_required(VERSION 2.8.3)
project(convert_map4costmap_to_gridmap)

add_compile_options(-std=c++11)

find_package(PCL 1.7 REQUIRED)
find_package(OpenCV REQUIRED)


find_package(catkin REQUIRED COMPONENTS
  nav_msgs
  pcl_ros
  roscpp
  rospy
  sensor_msgs
  dynamic_reconfigure
)
generate_dynamic_reconfigure_options(
  config/Points2Costmap.cfg
)


catkin_package(
  # INCLUDE_DIRS include
  LIBRARIES convert_map4costmap_to_gridmap
  CATKIN_DEPENDS nav_msgs pcl_ros roscpp rospy sensor_msgs
  #  DEPENDS system_lib
)

include_directories(
  include
  ${catkin_INCLUDE_DIRS}
)


add_executable(convert_map4costmap_to_gridmap_node 
        src/main.cpp )
add_dependencies(convert_map4costmap_to_gridmap_node
        ${PROJECT_NAME}_gencfg
)
target_link_libraries(convert_map4costmap_to_gridmap_node
        ${catkin_LIBRARIES}
        )

add_executable(load_pcd_file src/load_pcd.cpp)

target_link_libraries(load_pcd_file
        ${catkin_LIBRARIES}
        )