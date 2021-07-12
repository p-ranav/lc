find_package(Threads REQUIRED)

add_executable(lc main.cpp count_lines.cpp)
target_include_directories(lc PRIVATE ${PROJECT_SOURCE_DIR}/include)
target_link_libraries(lc PRIVATE Threads::Threads)

install(TARGETS lc)
