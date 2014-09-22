cmake_minimum_required(VERSION 2.8)
PROJECT(BinaryThinning3D)

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})

find_package(VTK REQUIRED)
include(${VTK_USE_FILE})

 
add_executable(ThinImage3D BinaryThinning3D.cxx itkBinaryThinningImageFilter3D.txx)
target_link_libraries(ThinImage3D ${ITK_LIBRARIES} ${VTK_LIBRARIES})
