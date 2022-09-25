#ifndef _PLAYER_H_
#define _PLAYER_H_
#include "Account.h"

class Player
{
private:
    Account player;
    std::pair<int, char> hand;
    int no_points;
public:
    Player();
    ~Player();

};

#endif // _PLAYER_H_
