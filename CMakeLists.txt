cmake_minimum_required(VERSION 2.6)
project(ncframe)

include_directories("${PROJECT_SOURCE_DIR}/inc")

add_subdirectory(src/ncf)
add_subdirectory(samples)
