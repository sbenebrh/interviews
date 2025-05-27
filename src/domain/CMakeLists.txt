add_library(domain INTERFACE
        Option.h
        Model.h)
target_include_directories(domain INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})