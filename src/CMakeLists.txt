add_executable(ice main.cpp)

add_subdirectory(entities)
add_subdirectory(domain)
add_subdirectory(infra)
add_subdirectory(use_case)
add_subdirectory(factory)

target_link_libraries(ice PRIVATE entities domain models options factory use_case randGen )