cmake_minimum_required(VERSION 3.16)
project(flexcommander-native)

add_subdirectory(flexcommander-lib)

include_directories(${CMAKE_JS_INC})
include_directories(flexcommander-lib/include)
include_directories(include)
include_directories(../node_modules/node-addon-api)
set(CMAKE_CXX_STANDARD 17)

add_library(${PROJECT_NAME} SHARED ${CMAKE_JS_SRC} src/Lib.cpp include/Lib.h src/Index.cpp)
set_target_properties(${PROJECT_NAME} PROPERTIES PREFIX "" SUFFIX ".node")
target_link_libraries(${PROJECT_NAME} ${CMAKE_JS_LIB} flexcommander-lib)
