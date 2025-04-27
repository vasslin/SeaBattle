#include "CustomStrategy.h"

CustomStrategy::CustomStrategy(uint64_t width, uint64_t height, uint64_t decks[]) : Strategy(width, height, decks) {}

Coordinates CustomStrategy::GetShot() {
    if (next_shots.empty()) {
        last_shot = CreateShot();
        while (InKilledOreol(last_shot)) {
            last_shot = CreateShot();
            // if last element
            if ((last_shot.y == field_.GetWith() - 1) && (last_shot.x > field_.GetHeight() - 2) &&
                (last_shot.x % 2 == 1)) {
                return RandomShot();
            }
        }
    } else {
        last_shot = next_shots.back();
        std::cout << "next shots: " << std::endl;
        for (Coordinates c : next_shots) {
            std::cout << c << std::endl;
        }
        std::cout << "---" << std::endl;
        next_shots.pop_back();
    }
    return last_shot;
}

Coordinates CustomStrategy::RandomShot() {
    uint64_t x = rand() % field_.GetWith();
    uint64_t y = rand() % field_.GetHeight();
    return Coordinates{x, y};
}

void CustomStrategy::SetResult(ShotResult result) {
    // std::cout << "ЭЩКЕРЕ" << std::endl;
    if (result == ShotResult::Missed) {
        missed = last_shot;
        return;
    }
    ++size;
    if (size == 1) {
        first_part = last_shot;
    }
    is_vertical = last_shot.x == first_part.x;
    if (last_shot <= first_part) {
        first_part = last_shot;
    }

    if (result == ShotResult::Kill) {
        field_.AddShip(first_part, size, is_vertical);
        // std::cout << "Add ship: first_part = " << first_part << " , size = " << size << ", is_vertical = " <<
        // is_vertical << std::endl;
        field_.MinusDecks(size - 1);
        size = 0;
        next_shots.clear();
    } else {
        // std::cout << "Update next shot" << std::endl;
        UpdateNextShot();
    }
    return;
}

Coordinates CustomStrategy::CreateShot() {
    if (is_first) {
        is_first = false;
    } else if (x_order + 2 < field_.GetWith()) {
        x_order += 2;
    } else if (x_order % 2 == 0) {
        x_order = 1;
    } else {
        ++y_order;
        x_order = 0;
    }
    return {x_order, y_order};
}

void CustomStrategy::UpdateNextShot() {
    next_shots.clear();
    if (size == 1) {
        if (first_part.x % 2 == 0) {
            if (first_part.x > 0 && !(InKilledOreol({first_part.x - 1, first_part.y}))) {
                next_shots.push_back({first_part.x - 1, first_part.y});
            }
            if (first_part.x + size < field_.GetWith()) {
                next_shots.push_back({first_part.x + size, first_part.y});
            }
        }
        if (first_part.y + 1 < field_.GetHeight()) {
            next_shots.push_back({first_part.x, first_part.y + 1});
        }
    } else if (is_vertical) {
        next_shots.push_back({first_part.x, first_part.y + size});
    } else {
        // criterions for adding left part:
        // hasn't been shotted yet; != missed; not in killed oreol
        Coordinates tmp = first_part;
        if (tmp.x > 0) {
            --tmp.x;
            if ((tmp.x % 2 == 0) && (tmp != missed) && !(InKilledOreol(tmp))) {
                next_shots.push_back(tmp);
            }
            ++tmp.x;
        }
        // criterions for adding right part:
        // != missed; not in killed oreol
        if (tmp.x < field_.GetWith() - size) {
            tmp.x += size;
            if ((tmp != missed) && !(InKilledOreol(tmp))) {
                next_shots.push_back(tmp);
            }
        }
    }
}

bool CustomStrategy::InKilledOreol(Coordinates coordinates) {
    Coordinates tmp{coordinates};
    if (tmp.x > 0) {
        --tmp.x;
        if (field_.Contains(tmp)) {
            return true;
        }
        ++tmp.x;
    }
    if (tmp.y > 0) {
        --tmp.y;
        if (field_.Contains(tmp)) {
            return true;
        }
        ++tmp.y;
    }

    if (tmp.x < field_.GetWith() - 1) {
        ++tmp.x;
        if (field_.Contains(tmp)) {
            return true;
        }
        --tmp.x;
    }
    if (tmp.y < field_.GetHeight() - 1) {
        ++tmp.y;
        if (field_.Contains(tmp)) {
            return true;
        }
        --tmp.y;
    }
    return false;
}