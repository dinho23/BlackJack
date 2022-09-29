#include "Dealer.h"

Dealer::Dealer(std::pair<int, char> hand, int no_points)
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

void Dealer::set_points(int points_to_set) {
    no_points = points_to_set;
}

void Dealer::add_points(int points_to_add) {
    if (points_to_add <= 10)
        no_points += points_to_add;
    
    if (points_to_add > 11)
        no_points += 10;
        
    if (points_to_add == 11) {
        if (no_points + points_to_add > 21)
            no_points += 1;
        else
            no_points += points_to_add;
    }
}

int Dealer::get_points() {
    return no_points;
}

int Dealer::get_total_points() {
    if (hand.size() == 0)
        return 0;
        
    int sum{}, temp{};
    
    for(size_t i = 0; i < hand.size(); i++) {
        if (hand.at(i).first <= 11)
            temp = hand.at(i).first;
        else
            temp = 10;
        
        if(i == hand.size() - 1 && sum + temp <= 21) {
            sum += temp;
            break;
        }
        
        if(temp == 11 && no_points + 11 <= 21) 
            sum += temp;
        
        if (temp == 11 && no_points + 11 > 21) 
            sum += 1;
        
        if (temp != 11) 
            sum += temp;
    }
    
    return sum;
}

int Dealer::get_first_card_points() {
    if(hand.at(0).first > 11)
        return 10;
    else
        return hand.at(0).first;
}

void Dealer::reset_hand() {
    hand.clear();
    no_points = 0;
}
