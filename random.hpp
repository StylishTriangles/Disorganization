#pragma once
#include <random>
#include <climits>

int* rseed = new int;

std::mt19937 rng32((long long int)rseed);
std::mt19937_64 rng64((long long int)rseed+1000000009LL);

int randInt(int min = INT_MIN, int max = INT_MAX) {
    std::uniform_int_distribution<int> kek(min, max);
    return kek(rng32);
}
