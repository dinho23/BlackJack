#include "Player.h"

Player::Player(Account player)
    : player {player}, hand {std::make_pair(0,' ')}, no_points {0}
{
    std::cout << "Player succesfully logged in!\n";
}


