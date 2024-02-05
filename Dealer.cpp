#include "Dealer.h"

Dealer::Dealer(int hand, int no_points)
    : hand{ minusOne }, no_points{ 0 }
{
}

int Dealer::get_card(size_t pos) {
    return hand.at(pos);
}

std::vector<int> Dealer::get_hand() {
    return hand;
}

void Dealer::set_card(int card) {
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

int Dealer::get_total_points(bool firstCardOnly) {
    if (hand.size() == 0)
        return 0;
    
    int cardValue{};

    if (hand.at(0) % 13 == 0)
    {
        cardValue = 11;
    }
    else
    {
        cardValue = std::min(hand.at(0) % 13 + 1, 10);
    }

    if (firstCardOnly)
    {
        return cardValue;
    }

    int sum{}, temp{};

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

        if (i == hand.size() - 1 && sum + temp <= 21) {
            sum += cardValue;
            break;
        }

        if (cardValue == 11 && no_points + 11 <= 21)
            sum += cardValue;

        if (cardValue == 11 && no_points + 11 > 21)
            sum += 1;

        if (cardValue != 11)
            sum += cardValue;
    }

    if (sum < no_points)
    {
        set_points(sum);
    }

    return sum;
}

int Dealer::getCardValue(int card)
{
    int cardValue{};

    if (card == 0 || card == 13 || card == 26 || card == 39)
    {
        cardValue = 11;
    }
    else
    {
        cardValue = std::min(card % 13 + 1, 10);
    }

    return cardValue;
}

int Dealer::get_first_card_points() {
    return getCardValue(hand.at(0));
}

void Dealer::reset_hand() {
    hand.clear();
    no_points = 0;
}
