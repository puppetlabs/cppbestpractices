cmake_minimum_required(VERSION 3.4)
project(cpp-ral-example)

find_package(Boost 1.57.0 COMPONENTS system filesystem REQUIRED)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

set(SOURCE_FILES main.cc resource.cc file.cc package.cc service.cc)
add_executable(cpp-ral-example ${SOURCE_FILES})
target_link_libraries(cpp-ral-example ${Boost_LIBRARIES})
