#include "Deck.h"
#include <random>

Deck::Deck()
{
    for (int i = 0; i < 52; i++)
    {
        cards.push_back(i);
    }
}

#include <random>

int Deck::draw_card() {
    // Use a random number engine and a distribution
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 51); // Distribution for numbers between 0 and 51 (inclusive)

    return cards.at(dis(gen)); // Generate a random index for cards vector
}