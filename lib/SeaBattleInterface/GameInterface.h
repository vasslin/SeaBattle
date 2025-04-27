#include "SeaBattle.h"

void AddCommand(SeaBattle& game, std::stringstream& ss, uint64_t& x, uint64_t& y, std::string& cmd,
                       std::string& str, bool& game_has_value);

void Get(std::string& cmd, SeaBattle& game, std::stringstream& ss);

void Set(std::string& cmd, SeaBattle& game, std::stringstream& ss);

void StartGame();