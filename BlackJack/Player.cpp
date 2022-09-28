#include "Player.h"

Player::Player(Account account, std::pair<int, char> hand, int no_points)
    : account{account}, hand {def_hand}, no_points {zero}
{
    std::cout << account << " " << "Player succesfully logged in!\n";
}

Account Player::account_info() {
    return account;
}

void Player::withdraw_from_acc(int amount) {
    account.withdraw(amount);
}
void Player::deposit_to_acc(int amount) {
    account.deposit(amount);
}

void Player::set_card(std::pair<int, char> card) {
    hand.push_back(card);
}

std::pair<int, char> Player::get_card(size_t pos) {
    return hand.at(pos);
}

std::vector<std::pair<int, char>> Player::get_hand() {
    return hand;
}

int Player::get_total_points() {
    int sum{};
    
    if (hand.size() == 0)
        return 0;
    
    for(size_t i = 0; i < hand.size(); i++)
        sum += hand.at(i).first;
        
    return sum;
}

int Player::get_points() {
    return no_points;
}

void Player::add_points(int points_to_add) {
    no_points += points_to_add;
}

void Player::reset_hand() {
    hand.clear();
}