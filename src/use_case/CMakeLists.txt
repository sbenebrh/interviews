add_library(use_case STATIC
        MonteCarloPricer.h
        MonteCarloPricer.cpp)

target_include_directories(use_case PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(use_case PUBLIC domain entities randGen)
