#include "Deck.h"

Deck::Deck()
{
    for (int i = 0; i < 52; i++)
    {
        cards.push_back(i);
    }
}

int Deck::draw_card() {
    auto seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
    srand(seed);

    return cards.at(rand() % 51);
}