// Dice.cpp
// Mara Kim
//
// An object that simulates a dice roll

#include "Dice.h"

int Dice::roll(const unsigned int& die, const unsigned int& times) {
    int result = 0;
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine generator(seed);
    std::uniform_int_distribution<int> distribution(1,die);
    for(int i = 0; i < times; i++)
        result += distribution(generator);
    return result;
}

int Dice::roll(const Dice::roll_type& roll) {
    return Dice::roll(roll.die,roll.times);
}

Dice::result_type Dice::roll_str(const unsigned int& die, const unsigned int& times) {
    int result = 0;
    std::stringstream report;
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine generator(seed);
    std::uniform_int_distribution<int> distribution(1,die);
    bool first = true;
    for(int i = 0; i < times; i++) {
        if(first)
            first = false;
        else
            report << " + ";
        int roll = distribution(generator);
        result += roll;
        report << roll;
    }
    Dice::result_type r;
    r.result = result;
    r.report = report.str();
    return r;
}

Dice::result_type Dice::roll_str(const Dice::roll_type& roll) {
    return Dice::roll_str(roll.die,roll.times);
}