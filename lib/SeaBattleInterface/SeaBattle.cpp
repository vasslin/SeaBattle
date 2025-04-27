#include "SeaBattle.h"

const std::string SeaBattle::v_ = "v";

SeaBattle::SeaBattle() {}

SeaBattle::SeaBattle(const SeaBattle& other)
    : width_(other.width_),
      height_(other.height_),
      mode_(other.mode_),
      strategy_type_(other.strategy_type_),
      is_started_(other.is_started_),
      is_stopped_(other.is_stopped_),
      my_field_(other.my_field_),
      is_loaded_(other.is_loaded_),
      w_default(other.w_default),
      h_default(other.h_default) {
    for (uint8_t i = 0; i < Constants::count_of_types; ++i) {
        decks_[i] = other.decks_[i];
    }
    if (other.strategy == nullptr) {
        strategy = nullptr;
    } else if (typeid(*other.strategy) == typeid(CustomStrategy)) {
        strategy = new CustomStrategy(*dynamic_cast<CustomStrategy*>(other.strategy));
    } else if (typeid(*other.strategy) == typeid(OrderedStrategy)) {
        strategy = new OrderedStrategy(*dynamic_cast<OrderedStrategy*>(other.strategy));
    }
}

SeaBattle::~SeaBattle() {
    delete strategy;
}

bool SeaBattle::SetWidth(uint64_t width) {
    if (width_.has_value()) {
        return false;
    }
    width_ = width;
    return true;
}
bool SeaBattle::SetHeight(uint64_t height) {
    if (height_.has_value()) {
        return false;
    }
    height_ = height;
    return true;
}

void SeaBattle::SetMode(Mode mode) {
    mode_ = mode;
    if (mode == Mode::Master) {
        SetDefaultValue();
    }
}

void SeaBattle::SetDefaultValue() {
    width_ = w_default;
    height_ = h_default;
    for (uint8_t i = 0; i < Constants::count_of_types; ++i) {
        decks_[i] = decks_default[i];
    }
}

Mode SeaBattle::GetMode() {
    return mode_.value();
}

uint64_t SeaBattle::GetWigth() {
    return width_.has_value() ? width_.value() : 0;
}

uint64_t SeaBattle::GetHeight() {
    return height_.has_value() ? height_.value() : 0; 
}

bool SeaBattle::SetCount(uint8_t type, uint64_t count) {
    std::cout << +type << std::endl;
    if (type <= Constants::count_of_types && type > 0) {
        if (decks_[type - 1] != 0) {
            return false;
        }
        decks_[type - 1] = count;
        std::cout << decks_[type - 1] << std::endl;
        return true;
    }
    return false;
}
uint64_t SeaBattle::GetCount(uint8_t type) {
    if (type <= Constants::count_of_types && type > 0) {
        return decks_[type - 1];
    }
    return 0;
}
void SeaBattle::SetStrategy(StrategyType strategy_type) {
    if (is_started_ && (strategy != nullptr) &&
        (strategy_type_ != strategy_type)) {  // смена стратегии в течение игры (на другую стратегию)
        delete strategy;
        if (strategy_type_ == StrategyType::Custom) {
            strategy = new CustomStrategy(width_.value(), height_.value(), decks_);
        }
        if (strategy_type_ == StrategyType::Ordered) {
            strategy = new OrderedStrategy(width_.value(), height_.value(), decks_);
        }
    }

    strategy_type_ = strategy_type;
}

void SeaBattle::Load(std::string& path) {
    std::ifstream in;
    in.open(path);
    if (!in.is_open()) {
        std::cerr << "Unable to open a file" << std::endl;
        return;
    }
    std::string line;
    in >> line;
    width_ = std::stoull(line);
    in >> line;
    height_ = std::stoull(line);
    my_field_ = MyField(height_.value(), width_.value());

    // loading
    uint8_t size;
    uint64_t x;
    uint64_t y;
    std::string orientation;
    for (uint8_t i = 0; i < Constants::count_of_types; ++i) {
        decks_[i] = 0;
    }
    while (in >> size >> orientation >> x >> y) {
        size -= '0';
        my_field_.AddShip({x, y}, size, orientation == v_);
        ++decks_[size - 1];
    }
    my_field_.SetDecks(decks_);
    is_loaded_ = true;
}

bool SeaBattle::Win() {
    return strategy->IsWin();
}

bool SeaBattle::Lose() {
    return my_field_.IsLose();
}

void SeaBattle::Dump(std::string& path) {
    std::ofstream out;
    out.open(path);
    out << width_.value() << " " << height_.value() << "\n";
    my_field_.DumpShips(out);
    out.close();
}

bool SeaBattle::Start() {
    if (is_started_) {
        return true;
    }
    if (AllDecksEntered() && width_.has_value() && height_.has_value() && strategy_type_.has_value()) {
        if (!is_loaded_) {
            my_field_ = MyField(height_.value(), width_.value());
            my_field_.SetDecks(decks_);
        }
        if (is_loaded_ || !is_loaded_ && my_field_.GenerateField()) {
            if (strategy_type_ == StrategyType::Custom) {
                strategy = new CustomStrategy(width_.value(), height_.value(), decks_);
            }
            if (strategy_type_ == StrategyType::Ordered) {
                strategy = new OrderedStrategy(width_.value(), height_.value(), decks_);
            }
            is_started_ = true;
            is_stopped_ = false;
            return true;
        }
    }
    return false;
}

void SeaBattle::Stop() {
    is_stopped_ = true;
    is_started_ = false;
}

bool SeaBattle::Finished() {
    return is_stopped_ || my_field_.IsLose() || strategy->IsWin();
}

bool SeaBattle::AllDecksEntered() {
    for (uint8_t i = 0; i < Constants::count_of_types; ++i) {
        if (decks_[i] != 0) {
            return true;
        }
    }
    return false;
}

Coordinates SeaBattle::MakeShot() {
    return strategy->GetShot();
}

void SeaBattle::SetResult(ShotResult result) {
    strategy->SetResult(result);
}

ShotResult SeaBattle::SetShot(Coordinates coord) {
    my_field_.SetShot(coord);
    return my_field_.GetResult();
}

bool SeaBattle::Started() {
    return is_started_;
}

