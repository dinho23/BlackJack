#pragma once
#include <vector>
#include <cstdlib>
#include <ctime>
#include <random>

class Deck
{
protected:
    std::vector <int> cards;
public:
    Deck();
    ~Deck() = default;

    int draw_card();
};