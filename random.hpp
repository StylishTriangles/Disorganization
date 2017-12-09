#pragma once
#include <random>
#include <climits>

std::mt19937 rng32((std::random_device())());
std::mt19937_64 rng64((std::random_device())());

int randInt(int min = INT_MIN, int max = INT_MAX) {
    std::uniform_int_distribution<int> kek(min, max);
    return kek(rng32);
}
