#pragma once
#include <iostream>
#include <limits>

enum ShotResult { Missed, Hit, Kill };

std::ostream& operator<<(std::ostream& stream, const ShotResult& result);

class Ship {
   public:
    Ship(uint8_t size, uint64_t start);
    Ship() = default;
    ~Ship() = default;
    bool operator<(const Ship& other) const;
    uint8_t GetSize() const;
    uint64_t GetStart() const;
    void ChangeBit(uint8_t num);
    ShotResult StatusOfShip();

   private:
    static const uint8_t One = 1;
    uint8_t data_ = 0;
    uint64_t start_ = 0;

    bool IsKilled();
};

namespace Constants {
const uint8_t count_of_types = 4;
}

struct Coordinates {
    uint64_t x = 0;
    uint64_t y = 0;
    Coordinates(uint64_t x_coord, uint64_t y_coord) : x(x_coord), y(y_coord) {};
    Coordinates() = default;
};

bool operator==(const Coordinates& lhs, const Coordinates& rhs);

bool operator!=(const Coordinates& lhs, const Coordinates& rhs);

bool operator<=(const Coordinates& lhs, const Coordinates& rhs);

std::ostream& operator<<(std::ostream& stream, const Coordinates& value);