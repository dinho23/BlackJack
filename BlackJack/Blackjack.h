#ifndef _BLACKJACK_H_
#define _BLACKJACK_H_
#include "Player.h"
#include "Deck.h"
#include "Dealer.h"

class Blackjack
{
protected:
    Deck deck;
    Dealer dealer;
    Player player;
    
public:
    Blackjack(Deck deck, Dealer dealer, Player player);
    ~Blackjack() = default;
    
    void bet(Player &player, Dealer &dealer);
    void play(Player &player);
    void deposit(Player &player);
    void withdraw(Player &player);
    void show_table(Player &player, Dealer &dealer);
    std::pair<int, char> draw_cards();
    void reset_hand();
};

#endif // _BLACKJACK_H_
