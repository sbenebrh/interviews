
include_directories(/opt/homebrew/opt/googletest/include)
link_directories(/opt/homebrew/opt/googletest/lib)

add_executable(ice_tests test.cpp
        MonteCarloPricerTest.cpp)

target_include_directories(ice_tests PRIVATE
        ${CMAKE_SOURCE_DIR}/src/entities
        ${CMAKE_SOURCE_DIR}/src/domain
        ${CMAKE_SOURCE_DIR}/src/infra)

target_link_libraries(ice_tests PRIVATE gtest gmock gtest_main domain options models entities randGen use_case)

