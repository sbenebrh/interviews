add_library(factory STATIC
        OptionFactory.cpp
        OptionFactory.h
        ModelFactory.cpp
        ModelFactory.h
        AbstractFactory.h)

target_link_libraries(factory entities models options)
target_include_directories(factory PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})