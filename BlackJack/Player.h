#ifndef _PLAYER_H_
#define _PLAYER_H_
#include "Account.h"

class Player
{
private:
    static constexpr std::pair<int, char> def_hand = std::make_pair(0,' ');
    static constexpr unsigned int zero = 0;
protected:
    Account player;
    std::pair<int, char> hand;
    unsigned int no_points;
public:
    Player(Account player = Account());
    ~Player() = default;

};

#endif // _PLAYER_H_
