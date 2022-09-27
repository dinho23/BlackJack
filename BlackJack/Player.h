#ifndef _PLAYER_H_
#define _PLAYER_H_
#include "Account.h"
#include <vector>

class Player
{
private:
    static constexpr std::pair<int, char> def_hand = std::make_pair(0,' ');
    static constexpr unsigned int zero = 0;
protected:
    Account account;
    std::vector<std::pair<int, char>> hand;
    unsigned int no_points;
public:
    Player(Account account = Account(), std::pair<int, char> hand = def_hand, unsigned int no_points = zero);
    ~Player() = default;
    
    Account account_info();

};

#endif // _PLAYER_H_
