#ifndef _DEALER_H_
#define _DEALER_H_
#include <iostream>
#include <vector>

class Dealer
{
protected:
    std::vector<std::pair<int, char>> hand;
    int no_points;
public:
    Dealer();
    ~Dealer() = default;
    
    std::pair<int, char> get_card(size_t pos);
    std::vector<std::pair<int, char>> get_hand();
    void set_card(std::pair<int, char> card);
    int get_total_points();
    void add_points(int points_to_add);
    int get_first_card_points();
    void reset_hand();

};

#endif // _DEALER_H_
