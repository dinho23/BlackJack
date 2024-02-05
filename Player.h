#pragma once
#include "Account.h"
#include <vector>

class Player
{
private:
    static constexpr  int zero = 0;
    static constexpr  int minusOne = -1;
protected:
    Account account;
    std::vector<int> hand;
    int no_points;
public:
    Player(Account account = Account(), int hand = minusOne, int no_points = zero);
    ~Player() = default;

    Account account_info();
    std::vector<int> get_hand();
    int get_card(size_t pos);
    void set_card(int card);
    void withdraw_from_acc(int amount);
    void deposit_to_acc(int amount);
    int get_total_points();
    int get_points();
    void add_points(int points_to_add);
    void reset_hand();
    void set_points(int points_to_set);
    void add_match(bool won);
};