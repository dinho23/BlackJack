#ifndef _DEALER_H_
#define _DEALER_H_
#include <iostream>
#include <vector>

class Dealer
{
private:
    static constexpr std::pair<int, char> def_hand = std::make_pair(0,' ');
    static constexpr  int zero = 0;
protected:
    std::vector<std::pair<int, char>> hand;
    int no_points;
public:
    Dealer(std::pair<int, char> hand = def_hand, int no_points = zero);
    ~Dealer() = default;
    
    std::pair<int, char> get_card(size_t pos);
    std::vector<std::pair<int, char>> get_hand();
    void set_card(std::pair<int, char> card);
    int get_total_points();
    void add_points(int points_to_add);
    int get_first_card_points();
    void reset_hand();
    int get_points();
    void set_points(int points_to_set);

};

#endif // _DEALER_H_
