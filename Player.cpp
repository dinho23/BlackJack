#include "Player.h"

Player::Player(Account account, int hand, int no_points)
    : account{ account }, hand{ minusOne }, no_points{ zero }
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

void Player::set_card(int card) {
    hand.push_back(card);
}

int Player::get_card(size_t pos) {
    return hand.at(pos);
}

std::vector<int> Player::get_hand() {
    return hand;
}

int Player::get_total_points() {
    if (hand.size() == 0)
        return 0;

    int sum{};

    int cardValue{};

    for (size_t i = 0; i < hand.size(); i++) {
        if (hand.at(i) % 13 == 0)
        {
            cardValue = 11;
        }
        else
        {
            cardValue = std::min(hand.at(i) % 13 + 1, 10);
        }

        if (i == hand.size() - 1 && sum + cardValue <= 21) {
            sum += cardValue;
            break;
        }

        if (i == hand.size() - 1 && sum + cardValue <= 21) {
            sum += cardValue;
            break;
        }

        if (cardValue == 11 && no_points + 11 <= 21)
            sum += cardValue;
        else if (cardValue == 11 && no_points + 11 > 21) {
            sum += 1;
        }
        else if (cardValue <= 10)
            sum += cardValue;
        else
            sum += 10;
    }

    if (sum < no_points)
    {
        set_points(sum);
    }

    return sum;
}

int Player::get_points() {
    return no_points;
}

void Player::add_points(int points_to_add) {
    if (points_to_add <= 10)
    { 
        no_points += points_to_add;
    }
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