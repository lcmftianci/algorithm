cmake_minimum_required(VERSION 3.5 )
#${PROJECT_SOURCE_DIR}/
include(windows.toolchain.cmake) 

project(demo_ninja)

#find_package(Clang REQUIRED CONFIG)
 
set(SOURCE_FILES demo_ninja_main.cpp)
 
#message(STATUS "This is BINARY dir " ${PROJECT_BINARY_DIR})
#message(STATUS "This is SOURCE dir " ${PROJECT_SOURCE_DIR})
#message(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")
#message(STATUS "Using LLVMConfig.cmake in: ${LLVM_DIR}")
 
# Set your project compile flags.
# E.g. if using the C++ header files
# you will need to enable C++11 support
# for your compiler.

#set(LLVM_INCLUDE_DIRS "D:/Program\ Files/LLVM/lib/clang/9.0.0/include")
#set(LLVM_DEFINITIONS "D:/Program\ Files/LLVM/lib/clang/9.0.0/lib/windows")
 
#include_directories(${LLVM_INCLUDE_DIRS})
#add_definitions(${LLVM_DEFINITIONS})
 
# Now build our tools
add_executable(demo_ninja ${SOURCE_FILES})
 
 
# Find the libraries that correspond to the LLVM components
# that we wish to use
#llvm_map_components_to_libnames(llvm_libs support core irreader)
 
# Link against LLVM libraries
target_link_libraries(demo_ninja ${llvm_libs})