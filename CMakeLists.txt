cmake_minimum_required(VERSION 3.0)
project(lc)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_CXX_FLAGS "-Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

###############################################################################
## file globbing ##############################################################
###############################################################################
file(GLOB_RECURSE sources src/count_lines.cpp src/main.cpp)

###############################################################################
## target definitions #########################################################
###############################################################################

add_executable(lc ${sources})
target_compile_options(lc PUBLIC -std=c++17 -Wall)
target_include_directories(lc PUBLIC include)

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
