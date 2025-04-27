#include "Ship.h"

Ship::Ship(uint8_t size, uint64_t start) : start_(start) {
    // 0000 0000 (big endian)
    // size parts (0 - no/killed, 1 - live)
    for (uint8_t i = 0; i < size; ++i) {
        data_ = (data_ << 1) & 0xFF;
        data_ |= 1;
    }
    data_ |= ((size << 4) & 0xFF);
};

ShotResult Ship::StatusOfShip() {
    if (((data_ << 4) & 0xFF) == 0) {
        return ShotResult::Kill;
    }
    return ShotResult::Hit;
}

bool Ship::IsKilled() {
    return (data_ << 4) & 0xFF == 0;
}

uint8_t Ship::GetSize() const {
    return (data_ >> 4) & 0xFF;
}

uint64_t Ship::GetStart() const {
    return start_;
}

void Ship::ChangeBit(uint8_t bit) {
    data_ &= ((One << bit) & 0xFF) ^ (std::numeric_limits<uint8_t>::max());  // 00000010 ^ 11111111 == 11111101
}

bool Ship::operator<(const Ship& other) const {
    return start_ < other.GetStart();
}

std::ostream& operator<<(std::ostream& stream, const ShotResult& result) {
    if (result == ShotResult::Hit) {
        stream << "hit";
    } else if (result == ShotResult::Kill) {
        stream << "kill";
    } else if (result == ShotResult::Missed) {
        stream << "miss";
    }
    return stream;
}


bool operator==(const Coordinates& lhs, const Coordinates& rhs) {
    return lhs.x == rhs.x && lhs.y == rhs.y;
}

bool operator!=(const Coordinates& lhs, const Coordinates& rhs) {
    return !(lhs == rhs);
}

bool operator<=(const Coordinates& lhs, const Coordinates& rhs) {
    return lhs.x <= rhs.x && lhs.y <= rhs.y;
}

std::ostream& operator<<(std::ostream& stream, const Coordinates& value) {
    stream << value.x << " " << value.y;
    return stream;
}