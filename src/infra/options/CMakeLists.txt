add_library(options STATIC
        Call.cpp
        Call.h
        Put.cpp
        Put.h
        Straddle.cpp
        Straddle.h
        Square.h
        Square.cpp
)

target_link_libraries(options entities domain)

target_include_directories(options
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR})
