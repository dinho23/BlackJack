#ifndef _DECK_H_
#define _DECK_H_
#include <utility>
#include <vector>
#include <stdlib.h>
#include <time.h>
#include "I_Printable.h"

class Deck : public I_Printable
{
protected:
    std::vector <std::pair<int, char>> cards;
public:
    Deck();
    ~Deck() = default;
    
    virtual void print(std::ostream &os) const override;
    std::pair<int, char> draw_card();

};

#endif // _DECK_H_
