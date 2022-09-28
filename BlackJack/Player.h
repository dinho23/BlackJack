#ifndef _PLAYER_H_
#define _PLAYER_H_
#include "Account.h"
#include <vector>

class Player
{
private:
    static constexpr std::pair<int, char> def_hand = std::make_pair(0,' ');
    static constexpr  int zero = 0;
protected:
    Account account;
    std::vector<std::pair<int, char>> hand;
     int no_points;
public:
    Player(Account account = Account(), std::pair<int, char> hand = def_hand, int no_points = zero);
    ~Player() = default;
    
    Account account_info();
    std::vector<std::pair<int, char>> get_hand();
    std::pair<int, char> get_card(size_t pos);
    void set_card(std::pair<int, char> card);
    void withdraw_from_acc(int amount);
    void deposit_to_acc(int amount);
    int get_total_points();
    int get_points();
    void add_points(int points_to_add);
    void reset_hand();

};

#endif // _PLAYER_H_
