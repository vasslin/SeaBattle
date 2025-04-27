add_executable(${PROJECT_NAME} main.cpp)

# target_link_libraries(${PROJECT_NAME} PRIVATE tools)
# target_link_libraries(${PROJECT_NAME} PRIVATE ship)
# target_link_libraries(${PROJECT_NAME} PRIVATE field)
# target_link_libraries(${PROJECT_NAME} PRIVATE my_field)
# target_link_libraries(${PROJECT_NAME} PRIVATE strategy)
# target_link_libraries(${PROJECT_NAME} PRIVATE custom_strategy)
# target_link_libraries(${PROJECT_NAME} PRIVATE ordered_strategy)
target_link_libraries(${PROJECT_NAME} PRIVATE sea_battle)
target_link_libraries(${PROJECT_NAME} PRIVATE game_interface)

target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR})

include_directories(${CMAKE_SOURCE_DIR}/lib)