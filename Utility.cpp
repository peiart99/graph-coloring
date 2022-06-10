//
// Created by Artur on 08.06.2022.
//

#include "Utility.h"

int util::generateRandomNumber(int min_value, int max_value)
{
    std::default_random_engine eng;
    unsigned long int t = std::chrono::high_resolution_clock::now().time_since_epoch().count();
    eng.seed(t);
    static std::mt19937 gen(eng());
    std::uniform_int_distribution<> dist(min_value,max_value);
    return dist(gen);
}

double util::generateRandomFloat(float min_value, float max_value)
{
    std::default_random_engine eng;
    unsigned long int t = std::chrono::high_resolution_clock::now().time_since_epoch().count();
    eng.seed(t);
    static std::mt19937 gen(eng());
    std::uniform_real_distribution<> dist(min_value,max_value);
    return dist(gen);
}
