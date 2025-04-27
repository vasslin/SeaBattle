#pragma once
#include <iostream>
#include <limits>
#include <map>
#include <set>
#include <vector>

#include "Ship.h"

class Field {
   public:
    Field() = default;
    Field(const uint64_t height, const uint64_t width);
    Field(const Field& other);
    ~Field();
    void AddShip(Coordinates first, uint8_t size, bool is_vertical);
    void MinusDecks(uint8_t i);
    uint64_t GetDeck(uint8_t i);

    uint64_t GetWith();
    uint64_t GetHeight();
    bool Contains(Coordinates& coordinates);

    bool IsDeckEmpty();
    void SetDecks(uint64_t decks[]);

   protected:
    std::map<uint64_t, std::set<Ship>> vertical_ships_;
    std::map<uint64_t, std::set<Ship>> horizontal_ships_;
    uint64_t width_ = 1;
    uint64_t height_ = 1;
    uint64_t decks_[Constants::count_of_types]{};
};
