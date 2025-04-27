#include "Field.h"

Field::Field(const uint64_t height, const uint64_t width) : height_(height), width_(width) {}

Field::Field(const Field& other)
    : height_(other.height_),
      width_(other.width_),
      vertical_ships_(other.vertical_ships_),
      horizontal_ships_(other.horizontal_ships_) {
    for (uint8_t i = 0; i < Constants::count_of_types; ++i) {
        decks_[i] = other.decks_[i];
    }
}

Field::~Field() {}

void Field::AddShip(Coordinates first, uint8_t size, bool is_vertical) {
    if (is_vertical) {
        vertical_ships_[first.x].insert(Ship{size, first.y});
    } else {
        horizontal_ships_[first.y].insert(Ship{size, first.x});
    }
    return;
}

void Field::SetDecks(uint64_t decks[]) {
    for (uint8_t i = 0; i < Constants::count_of_types; ++i) {
        decks_[i] = decks[i];
    }
}

uint64_t Field::GetDeck(uint8_t i) { return decks_[i]; }

void Field::MinusDecks(uint8_t i) {
    if (decks_[i] != 0) {
        --decks_[i];
    }
}

uint64_t Field::GetWith() { return width_; }

uint64_t Field::GetHeight() { return height_; }

bool Field::IsDeckEmpty() {
    for (uint8_t i = 0; i < Constants::count_of_types; ++i) {
        if (decks_[i] != 0) {
            return false;
        }
    }
    return true;
}

bool Field::Contains(Coordinates& coordinates) {
    uint64_t x = coordinates.x;
    uint64_t y = coordinates.y;
    if (horizontal_ships_.find(y) != horizontal_ships_.end()) {
        for (Ship ship : horizontal_ships_[y]) {
            if (x >= ship.GetStart() && (x < ship.GetStart() + ship.GetSize())) {
                return true;
            }
        }
    }
    if (vertical_ships_.find(x) != vertical_ships_.end()) {
        for (Ship ship : vertical_ships_[x]) {
            if (y >= ship.GetStart() && (y < ship.GetStart() + ship.GetSize())) {
                return true;
            }
        }
    }
    return false;
}
