#include "Strategy.h"

class OrderedStrategy : public Strategy {
   public:
    OrderedStrategy(uint64_t width, uint64_t height, uint64_t decks[]) : Strategy(width, height, decks) {};
    OrderedStrategy(const OrderedStrategy& other);
    ~OrderedStrategy() = default;
    void SetResult(ShotResult result) override;
    Coordinates GetShot() override;

   private:
    uint64_t x = 0;
    uint64_t y = 0;
};