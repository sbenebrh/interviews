add_library(models STATIC
        LogNormal.cpp
        LogNormal.h
        Normal.cpp
        Normal.h)
target_link_libraries(models PRIVATE domain)
target_include_directories(models INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})