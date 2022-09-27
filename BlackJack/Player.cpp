#include "Player.h"

Player::Player(Account account, std::pair<int, char> hand, unsigned int no_points)
    : account {account}, hand {def_hand}, no_points {zero}
{
    std::cout << account << " " << hand.first << " " << hand.second << " " << no_points << " " << "Player succesfully logged in!\n";
}

Account Player::account_info() {
    return account;
}