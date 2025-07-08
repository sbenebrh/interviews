cmake_minimum_required(VERSION 3.25)
project(strategy_pattern_lib LANGUAGES CXX)

add_library(strategy_lib INTERFACE
include/strategy_lib.hpp)
target_include_directories(strategy_lib
        PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include> )
target_compile_features(strategy_lib PUBLIC cxx_std_23)


add_subdirectory(examples)


# (optional) install
install(TARGETS strategy_lib EXPORT strategy_libTargets)
install(DIRECTORY include/ DESTINATION include)