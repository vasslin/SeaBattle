#include "OrderedStrategy.h"

OrderedStrategy::OrderedStrategy(const OrderedStrategy& other) : Strategy(other), x(other.x), y(other.y) {}

Coordinates OrderedStrategy::GetShot() {
    if (x < field_.GetWith()) {
        std::cout << "x < field_.GetWith() координаты: " << Coordinates{x, y} << std::endl;
        return Coordinates{x++, y};
    }
    x = 0;
    std::cout << "else координаты: " << Coordinates{x, y + 1} << std::endl;
    return Coordinates{x++, ++y};
}

void OrderedStrategy::SetResult(ShotResult result) {
    if (result == Kill) {
        for (uint8_t i = 0; i < Constants::count_of_types; ++i) {
            if (field_.GetDeck(i) != 0) {
                field_.MinusDecks(i);
                return;
            }
        }
    }
}