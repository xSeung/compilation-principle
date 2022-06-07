cmake_minimum_required(VERSION 3.0.0)

project(E1)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/data/bin)
# set(Boost_NO_WARN_NEW_VERSIONS ON)
include_directories(${PROJECT_SOURCE_DIR}/inc)
# set(CMAKE_GENERATOR "Visual Studio 17 2022")
aux_source_directory(${PROJECT_SOURCE_DIR}/src SRC_LIST)
# add_library(${PROJECT_NAME} ${SRC_LIST})
add_executable(${PROJECT_NAME} ${PROJECT_SOURCE_DIR}/main.cpp ${SRC_LIST})
# find_package(Boost REQUIRED program_options)
# target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES})
