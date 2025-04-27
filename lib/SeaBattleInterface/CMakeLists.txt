add_library(sea_battle SeaBattle.cpp SeaBattle.h)
add_library(game_interface GameInterface.cpp GameInterface.h)

target_link_libraries(sea_battle PRIVATE ship field my_field strategy custom_strategy ordered_strategy)
target_link_libraries(game_interface PRIVATE sea_battle)