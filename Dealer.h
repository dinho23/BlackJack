#pragma once
#include <iostream>
#include <vector>

class Dealer
{
private:
    static constexpr  int minusOne = -1;
    static constexpr  int zero = 0;
protected:
    std::vector<int> hand;
    int no_points;
public:
    Dealer(int hand = minusOne, int no_points = zero);
    ~Dealer() = default;

    int get_card(size_t pos);
    std::vector<int> get_hand();
    void set_card(int card);
    int get_total_points(bool firstCardOnly);
    void add_points(int points_to_add);
    int get_first_card_points();
    void reset_hand();
    int get_points();
    void set_points(int points_to_set);
    int getCardValue(int card);
};