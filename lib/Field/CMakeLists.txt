
add_library(ship Ship.cpp Ship.h)
add_library(field Field.cpp Field.h)
add_library(my_field MyField.cpp MyField.h)


target_link_libraries(field PRIVATE ship)
target_link_libraries(my_field PRIVATE field ship)