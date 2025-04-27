#pragma once
#include <fstream>

#include "Field.h"

class MyField : public Field {
   public:
    MyField();
    MyField(const uint64_t height, const uint64_t width);
    MyField(const MyField& other);
    ~MyField() = default;

    void SetShot(Coordinates shot);
    ShotResult GetResult();
    void LoadShips(std::ifstream& in);
    void DumpShips(std::ofstream& out);
    bool IsLose();
    bool GenerateField();

   private:
    static const std::string v_;
    static const std::string h_;
    bool lose_ = false;
    ShotResult last_result_ = ShotResult::Missed;
    bool IsEmpty(std::map<uint64_t, std::set<Ship>>& map);
    bool FillOneOrientation(std::map<uint64_t, std::set<Ship>>& ships, uint8_t* decks, uint64_t width);

    ShotResult SetShipShot(Coordinates& shot);
};