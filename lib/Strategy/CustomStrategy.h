#include "Strategy.h"

class CustomStrategy : public Strategy {
   public:
    CustomStrategy(uint64_t width, uint64_t height, uint64_t decks[]);
    ~CustomStrategy() = default;

    void SetResult(ShotResult result) override;
    Coordinates GetShot() override;

   private:
    Coordinates CreateShot();
    uint8_t size = 0;
    Coordinates RandomShot();

    uint64_t x_order = 0;
    uint64_t y_order = 0;
    bool is_first = true;

    Coordinates missed;
    Coordinates first_part;
    std::vector<Coordinates> next_shots;

    bool is_vertical = true;
    bool InKilledOreol(Coordinates coordinates);

    void UpdateNextShot();

};