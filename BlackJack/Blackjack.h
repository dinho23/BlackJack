#ifndef _BLACKJACK_H_
#define _BLACKJACK_H_
#include "Player.h"
#include "Deck.h"
#include "Dealer.h"
#include <stdlib.h>
#include <time.h>

class Blackjack
{
protected:
    Deck deck;
    Dealer dealer;
    Player player;
    
public:
    Blackjack(Deck deck, Dealer dealer, Player player);
    ~Blackjack() = default;
    
    std::pair<int, char> draw();
    void bet();
    void play();
};

#endif // _BLACKJACK_H_
