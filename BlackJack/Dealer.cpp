#include "Dealer.h"

Dealer::Dealer()
    : hand {std::make_pair(0, ' ')}, no_points {0}
{
}

std::pair<int, char> Dealer::get_card(size_t pos) {
    return hand.at(pos);
}

std::vector<std::pair<int, char>> Dealer::get_hand() {
    return hand;
}

void Dealer::set_card(std::pair<int, char> card) {
    hand.push_back(card);
}

void Dealer::add_points(int points_to_add) {
    no_points += points_to_add;
}

int Dealer::get_total_points() {
    if (hand.size() == 0)
        return 0;
    
    for(size_t i = 0; i < hand.size(); i++) {
        if(hand.at(i).first <= 10)
            add_points(hand.at(i).first);
        else
            add_points(10);
    }
        
    return no_points;
}

int Dealer::get_first_card_points() {
    return hand.at(0).first;
}

void Dealer::reset_hand() {
    hand.clear();
}
