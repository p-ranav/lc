cmake_minimum_required(VERSION 3.0)
project(lc)

# Use ccache to speed up our build
find_program(CCACHE_PROGRAM ccache)
if(CCACHE_PROGRAM)
  set(CMAKE_CXX_COMPILER_LAUNCHER ${CCACHE_PROGRAM})
endif()

# Configure compiler options
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(ENABLE_ALL_WARNINGS OFF)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

###############################################################################
## file globbing ##############################################################
###############################################################################
file(GLOB_RECURSE sources src/count_lines.cpp src/main.cpp)

###############################################################################
## target definitions #########################################################
###############################################################################

add_executable(lc ${sources})
target_include_directories(lc PRIVATE include)

###############################################################################
## dependencies ###############################################################
###############################################################################

find_package(Threads REQUIRED)
target_link_libraries(lc PRIVATE Threads::Threads)

###############################################################################
## packaging ##################################################################
###############################################################################

install(TARGETS lc)

# now comes everything we need, to create a package
# there are a lot more variables you can set, and some
# you need to set for some package types, but we want to
# be minimal here
set(CPACK_PACKAGE_NAME "lc")
set(CPACK_PACKAGE_VERSION "1.0.0")

# we don't want to split our program up into several things
set(CPACK_MONOLITHIC_INSTALL 1)

# This must be last
include(CPack)
