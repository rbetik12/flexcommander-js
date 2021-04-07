cmake_minimum_required(VERSION 3.16)
project(flexcommander-native)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(flexcommander-lib)

include_directories(${CMAKE_JS_INC})
include_directories(flexcommander-lib/include)
include_directories(include)
include_directories(../node_modules/node-addon-api)
include_directories(/usr/include/node)

add_library(${CMAKE_PROJECT_NAME} SHARED src/Lib.cpp include/Lib.h)
set_target_properties(${CMAKE_PROJECT_NAME} PROPERTIES PREFIX "" SUFFIX ".node")
target_link_libraries(${CMAKE_PROJECT_NAME} flexcommander-lib)