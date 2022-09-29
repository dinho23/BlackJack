#include "Player.h"

Player::Player(Account account, std::pair<int, char> hand, int no_points)
    : account{account}, hand {def_hand}, no_points {zero}
{
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
    if (hand.size() == 0)
        return 0;
        
    int sum{};
    
    for(size_t i = 0; i < hand.size(); i++) {
        if(i == hand.size() - 1 && sum + hand.at(i).first <= 21) {
            sum += hand.at(i).first;
            break;
        }
        
        if(hand.at(i).first == 11 && no_points + 11 <= 21)
            sum += hand.at(i).first;
        else if (hand.at(i).first == 11 && no_points + 11 > 21) {
            sum += 1;
        }
        else if (hand.at(i).first <= 10)
            sum += hand.at(i).first;
        else 
            sum += 10;
    }
        
    return sum;
}

int Player::get_points() {
    return no_points;
}

void Player::add_points(int points_to_add) {
    if (points_to_add <= 10)
        no_points += points_to_add;
    else if (points_to_add > 11)
        no_points += 10;
    else {
        if (no_points + points_to_add > 21)
            no_points += 1;
        else
            no_points += points_to_add;
    }
}

void Player::reset_hand() {
    hand.clear();
    no_points = 0;
}

void Player::set_points(int points_to_set) {
    no_points = points_to_set;
}

void Player::add_match(bool won) {
    account.add_match(won);
    account.update_win_percentage();
}