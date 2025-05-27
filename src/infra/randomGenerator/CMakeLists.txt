add_library(randGen STATIC
        StdNormalGenerator.cpp
        StdNormalGenerator.h
        RandomGeneratorType.h)

target_link_libraries(randGen entities domain)

target_include_directories(randGen
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR})
