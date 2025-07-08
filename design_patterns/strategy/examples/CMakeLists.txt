add_executable(strategy_demo main.cpp)
target_link_libraries(strategy_demo INTERFACE strategy_lib)
target_compile_features(strategy_demo PUBLIC cxx_std_23)

if (CMAKE_CXX_COMPILER_ID MATCHES "Clang|GNU")
    target_compile_options(strategy_demo PRIVATE -fdiagnostics-color=always)
endif()


