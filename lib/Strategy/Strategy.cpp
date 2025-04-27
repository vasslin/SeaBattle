#include "Strategy.h"

#include <random>

Strategy::Strategy(uint64_t width, uint64_t height, uint64_t decks[]) : field_(height, width) {
    field_.SetDecks(decks);
}

Strategy::Strategy(const Strategy& other) : field_(other.field_), last_shot(other.last_shot) {}

bool Strategy::IsWin() {
    return field_.IsDeckEmpty();
}
