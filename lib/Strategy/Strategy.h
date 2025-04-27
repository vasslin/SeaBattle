#pragma once
#include <iostream>
#include <queue>
#include <set>

#include "../Field/MyField.h"

class Strategy {
   public:
    Strategy(uint64_t width, uint64_t height, uint64_t decks[]);
    Strategy(const Strategy& other);
    ~Strategy() = default;

    virtual Coordinates GetShot() = 0;
    virtual void SetResult(ShotResult result) = 0;
    bool IsWin();

   protected:
    Field field_;  // use field to add killed ships
    Coordinates last_shot;
};
