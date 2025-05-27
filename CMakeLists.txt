cmake_minimum_required(VERSION 3.31)
project(ice)

set(CMAKE_CXX_STANDARD 20)

# Add source executable
add_subdirectory(src)

# Add subdirectory for tests
enable_testing()
add_subdirectory(tests)