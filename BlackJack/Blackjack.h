#ifndef _BLACKJACK_H_
#define _BLACKJACK_H_
#include "Player.h"
#include "Deck.h"

class Blackjack
{
protected:
    Deck deck;
    
    Player player;
    
public:
    Blackjack();
    ~Blackjack();

};

#endif // _BLACKJACK_H_
