#pragma once
#include <fstream>
#include <iostream>
#include <optional>
#include <string>

#include "../Strategy/CustomStrategy.h"
#include "../Strategy/OrderedStrategy.h"
#include "../Strategy/Strategy.h"

enum Mode { Master, Slave };
enum StrategyType { Ordered, Custom };


class SeaBattle {
   public:
    SeaBattle();
    SeaBattle(const SeaBattle& other);
    ~SeaBattle();

    bool SetWidth(uint64_t width);
    bool SetHeight(uint64_t height);
    uint64_t GetWigth();
    uint64_t GetHeight();
    bool Start();
    void Stop();
    bool SetCount(uint8_t type, uint64_t count);
    uint64_t GetCount(uint8_t type);
    void SetStrategy(StrategyType strategy_type);
    ShotResult SetShot(Coordinates coord);
    Coordinates MakeShot();
    void SetResult(ShotResult result);
    bool Finished();
    bool Win();
    bool Lose();
    void Dump(std::string& path);
    void Load(std::string& path);
    void SetMode(Mode mode);
    Mode GetMode();
    bool Started();

   private:
    std::optional<uint64_t> width_;
    std::optional<uint64_t> height_;
    std::optional<Mode> mode_;
    std::optional<StrategyType> strategy_type_;
    Strategy* strategy = nullptr;
    bool is_started_ = false;
    bool is_stopped_ = false;
    MyField my_field_;
    static const std::string v_;
    uint64_t decks_[Constants::count_of_types]{};
    bool is_loaded_ = false;

    // default values
    const uint64_t w_default = 6;
    const uint64_t h_default = 6;
    const uint64_t decks_default[4]{1, 1, 1, 1};
    void SetDefaultValue();
    bool AllDecksEntered();
};