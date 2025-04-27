add_library(strategy Strategy.cpp Strategy.h)
add_library(ordered_strategy OrderedStrategy.cpp OrderedStrategy.h)
add_library(custom_strategy CustomStrategy.cpp CustomStrategy.h)

target_link_libraries(strategy PRIVATE my_field field ship)
target_link_libraries(ordered_strategy PRIVATE strategy my_field field ship)
target_link_libraries(custom_strategy PRIVATE strategy my_field field ship)