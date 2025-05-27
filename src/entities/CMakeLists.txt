add_library(entities INTERFACE
        SpotPrice.h
        TimeToMaturity.h
        Strike.h)
target_include_directories(entities INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})