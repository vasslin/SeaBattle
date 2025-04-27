#include "MyField.h"

const std::string MyField::v_ = "v";
const std::string MyField::h_ = "h";

MyField::MyField() : Field() {};

MyField::MyField(const uint64_t height, const uint64_t width) : Field(height, width) {}

MyField::MyField(const MyField& other) : Field(other), lose_(other.lose_), last_result_(other.last_result_) {}

void MyField::SetShot(Coordinates shot) {
    last_result_ = SetShipShot(shot);
}

bool MyField::IsLose() {
    return IsDeckEmpty();
}

ShotResult MyField::GetResult() {
    return last_result_;
}

void MyField::LoadShips(std::ifstream& in) {
    uint8_t size;
    uint64_t x;
    uint64_t y;
    std::string orientation;
    while (in >> size >> orientation >> x >> y) {
        size -= '0';
        if (orientation == v_) {
            vertical_ships_[x].insert(Ship{size, y});
        }
        if (orientation == h_) {
            horizontal_ships_[y].insert(Ship{size, x});
        }
    }
}

void MyField::DumpShips(std::ofstream& out) {
    for (std::map<uint64_t, std::set<Ship>>::iterator it_map = horizontal_ships_.begin();
         it_map != horizontal_ships_.end(); ++it_map) {
        for (std::set<Ship>::iterator it_set = it_map->second.begin(); it_set != it_map->second.end(); ++it_set) {
            out << +it_set->GetSize() << " " << h_ << " " << it_set->GetStart() << " " << it_map->first << "\n";
        }
    }

    for (std::map<uint64_t, std::set<Ship>>::iterator it_map = vertical_ships_.begin(); it_map != vertical_ships_.end();
         ++it_map) {
        for (std::set<Ship>::iterator it_set = it_map->second.begin(); it_set != it_map->second.end(); ++it_set) {
            out << +it_set->GetSize() << " " << v_ << " " << it_map->first << " " << it_set->GetStart() << "\n";
        }
    }
}

ShotResult MyField::SetShipShot(Coordinates& shot) {
    Ship ship{};
    ShotResult status_of_ship;
    std::map<uint64_t, std::set<Ship>>::iterator it_map = horizontal_ships_.find(shot.y);
    if (it_map != horizontal_ships_.end()) {
        for (std::set<Ship>::iterator it_set = it_map->second.begin(); it_set != it_map->second.end(); ++it_set) {
            if (it_set->GetStart() <= shot.x && (it_set->GetStart() + it_set->GetSize() > shot.x)) {
                it_map->second.erase(it_set);
                ship = *it_set;
                ship.ChangeBit(shot.y - ship.GetStart());
                it_map->second.insert(ship);
                status_of_ship = ship.StatusOfShip();
                if (status_of_ship == ShotResult::Kill) {
                    --decks_[ship.GetSize() - 1];
                }

                return status_of_ship;
            }
        }
    }
    it_map = vertical_ships_.find(shot.x);
    if (it_map != vertical_ships_.end()) {
        for (std::set<Ship>::iterator it_set = it_map->second.begin(); it_set != it_map->second.end(); ++it_set) {
            if (it_set->GetStart() <= shot.y && (it_set->GetSize() + it_set->GetStart() > shot.y)) {
                it_map->second.erase(it_set);
                ship = *it_set;
                ship.ChangeBit(shot.y - ship.GetStart());
                it_map->second.insert(ship);
                status_of_ship = ship.StatusOfShip();
                if (status_of_ship == ShotResult::Kill) {
                    --decks_[ship.GetSize() - 1];
                }
                return status_of_ship;
            }
        }
    }
    return ShotResult::Missed;
}

bool MyField::IsEmpty(std::map<uint64_t, std::set<Ship>>& map) {
    for (std::map<uint64_t, std::set<Ship>>::iterator it_map = map.begin(); it_map != map.end(); ++it_map) {
        if (!it_map->second.empty()) {
            return false;
        }
    }
    return true;
}

bool MyField::GenerateField() {
    uint8_t decks_tmp[Constants::count_of_types];
    for (uint8_t i = 0; i < Constants::count_of_types; ++i) {
        decks_tmp[i] = decks_[i];
    }

    if (width_ > height_) {
        return FillOneOrientation(horizontal_ships_, decks_tmp, width_);
    } else {
        return FillOneOrientation(vertical_ships_, decks_tmp, height_);
    }
}

bool MyField::FillOneOrientation(std::map<uint64_t, std::set<Ship>>& ships, uint8_t* decks, uint64_t width) {
    uint64_t x = 0;
    uint8_t size = Constants::count_of_types;
    uint64_t i;
    for (uint64_t j = width; j > 0; j -= 2) {
        i = j - 1;
        std::set<Ship>& ship_set = ships[i];
        size = Constants::count_of_types;
        x = 0;
        while (size > 0 && decks[size - 1] == 0) {
            --size;
        }
        while (size > 0) {
            if (width - x >= size) {
                ship_set.insert({size, x});
                x += size;
                if (width - x >= 1) {
                    ++x;
                }
                --decks[size - 1];
            } else {
                --size;
            }
            while (size > 0 && decks[size - 1] == 0) {
                --size;
            }
        }
    }
    for (uint8_t i = 0; i < Constants::count_of_types; ++i) {
        if (decks[i] != 0) {
            return false;
        }
    }
    return true;
}