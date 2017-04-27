cmake_minimum_required(VERSION 2.8.8)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set_property(GLOBAL PROPERTY PREDEFINED_TARGETS_FOLDER "CMake")

project(ncframe)

if(NOT ${CMAKE_VERSION} LESS 3.2)
    set(CMAKE_CXX_STANDARD 14)
    set(CMAKE_CXX_STANDARD_REQUIRED ON)
else()
    message(STATUS "Checking compiler flags for C++14 support.")
    # Set C++11 support flags for various compilers
    include(CheckCXXCompilerFlag)
    check_cxx_compiler_flag("-std=c++14" COMPILER_SUPPORTS_CXX14)
    check_cxx_compiler_flag("-std=c++1y" COMPILER_SUPPORTS_CXX1Y)
    if(COMPILER_SUPPORTS_CXX14)
        message(STATUS "C++11 is supported.")
        if(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
            set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -stdlib=libc++")
        else()
            set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")
        endif()
    elseif(COMPILER_SUPPORTS_CXX0X)
        message(STATUS "C++0x is supported.")
        if(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
            set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1y -stdlib=libc++")
        else()
            set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1y")
        endif()
    else()
        message(STATUS "The compiler ${CMAKE_CXX_COMPILER} has no C++14 support. Please use a different C++ compiler.")
    endif()
endif()


set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/lib)

set(NCF_LIBRARIES ncf CACHE INTERNAL "")
set(NCF_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/ncf/inc CACHE INTERNAL "")

include_directories(${NCF_INCLUDE_DIR})
add_subdirectory(ncf/ncf)
