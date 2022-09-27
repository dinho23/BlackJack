#ifndef _DEALER_H_
#define _DEALER_H_
#include <iostream>
#include <vector>

class Dealer
{
protected:
    std::vector<std::pair<int, char>> hand;
    unsigned int no_points;
public:
    Dealer();
    ~Dealer() = default;

};

#endif // _DEALER_H_
