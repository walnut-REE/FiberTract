cmake_minimum_required(VERSION 2.8)
project(RecordVoxelPosition)
 
find_package(ITK REQUIRED)
include(${ITK_USE_FILE})

find_package(VTK REQUIRED)
include(${VTK_USE_FILE})

 
add_executable(RecordVoxelPosition recordVoxelPosition.cpp)
target_link_libraries(RecordVoxelPosition ${ITK_LIBRARIES} ${VTK_LIBRARIES})