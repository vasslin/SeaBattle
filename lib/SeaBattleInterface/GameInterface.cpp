#include "GameInterface.h"

#include <sstream>

void StartGame() {
    uint64_t x;
    uint64_t y;
    std::string cmd;
    std::string str;
    bool game_has_value = false;
    std::stringstream ss{};
    SeaBattle game{};

    while (true) {
        ss.str("");
        ss.clear();
        std::getline(std::cin, str);
        ss << str;
        ss >> cmd;

        if (cmd == "exit") {
            return;
        } else {
            AddCommand(game, ss, x, y, cmd, str, game_has_value);
        }
    }
}

void Set(std::string& cmd, SeaBattle& game, std::stringstream& ss) {
    bool success = true;
    std::string str;
    if (cmd == "strategy") {
        ss >> cmd;
        if (cmd == "ordered") {
            game.SetStrategy(StrategyType::Ordered);
        } else if (cmd == "custom") {
            game.SetStrategy(StrategyType::Custom);
        } else {
            success = false;
        }
    } else if (cmd == "result") {
        if (!game.Started()) {
            success = false;
        }
        ss >> cmd;
        if (cmd == "hit") {
            game.SetResult(ShotResult::Hit);
        } else if (cmd == "miss") {
            game.SetResult(ShotResult::Missed);
        } else if (cmd == "kill") {
            game.SetResult(ShotResult::Kill);
        } else {
            success = false;
        }
    }

    else if (game.GetMode() != Mode::Master) {
        if (cmd == "width") {
            ss >> cmd;
            if (!game.SetWidth(std::stoull(cmd))) {
                success = false;
            }
        } else if (cmd == "height") {
            ss >> cmd;
            if (!game.SetHeight(std::stoull(cmd))) {
                success = false;
            }
        } else if (cmd == "count") {
            ss >> str;
            ss >> cmd;
            if (!game.SetCount(str[0] - '0', std::stoull(cmd))) {
                success = false;
            }
        }
    } else {
        success = false;
    }
    if (success) {
        std::cout << "ok" << std::endl;
        return;
    }
    std::cout << "failed1" << std::endl;
}

void Get(std::string& cmd, SeaBattle& game, std::stringstream& ss) {
    if (cmd == "width") {
        std::cout << game.GetWigth() << std::endl;
    } else if (cmd == "height") {
        std::cout << game.GetHeight() << std::endl;
    } else if (cmd == "count") {
        ss >> cmd;
        std::cout << +game.GetCount(cmd[0] - '0') << std::endl;
    }
}

void AddCommand(SeaBattle& game, std::stringstream& ss, uint64_t& x, uint64_t& y, std::string& cmd, std::string& str,
                bool& game_has_value) {
    // общие команды
    if (cmd == "ping") {
        std::cout << "pong" << std::endl;
    }

    else if (cmd == "create") {
        ss >> cmd;
        if (!game_has_value) {
            game_has_value = true;
            if (cmd == "master") {
                game.SetMode(Mode::Master);
            } else if (cmd == "slave") {
                game.SetMode(Mode::Slave);
            }
            std::cout << "ok" << std::endl;
        }
        // else {
        // std::cout << "failed" << std::endl;
        // }
    }

    else {
        // команды для объекта SeaBattle
        if (!game_has_value) {
            // std::cout << "failed" << std::endl;
            return;
        }
        if (cmd == "start") {
            if (game_has_value && game.Start()) {
                std::cout << "ok" << std::endl;
            } else {
                std::cout << "failed: data is incompatible or missing" << std::endl;
            }
        } else if (cmd == "stop") {
            if (game_has_value) {
                game.Stop();
                std::cout << "ok" << std::endl;
            }
            // std::cout << "failed" << std::endl;

        } else if (cmd == "set") {
            if (!game_has_value) {
                std::cout << "failed" << std::endl;
                return;
            }
            ss >> cmd;
            Set(cmd, game, ss);
        } else if (cmd == "get") {
            ss >> cmd;
            Get(cmd, game, ss);
        } else if (cmd == "load") {
            ss >> cmd;
            game.Load(cmd);
            std::cout << "ok" << std::endl;
        } else if (cmd == "dump") {
            ss >> cmd;
            game.Dump(cmd);
            std::cout << "ok" << std::endl;
        }

        else {  // for started game
            // if (!game.Started()) {
            //     std::cout << "failed" << std::endl;
            //     return;
            // }
            if (cmd == "finished") {
                std::cout << (game.Finished() ? "yes" : "no") << std::endl;
            } else if (cmd == "win") {
                std::cout << (game.Win() ? "yes" : "no") << std::endl;
            } else if (cmd == "lose") {
                std::cout << (game.Lose() ? "yes" : "no") << std::endl;
            } else {
                if (game.Finished()) {
                    return;
                }
                if (cmd == "shot") {
                    if (ss >> x >> y) {
                        std::cout << game.SetShot({x, y}) << std::endl;
                    } else {
                        std::cout << game.MakeShot() << std::endl;
                    }
                }
            }
        }
    }
}