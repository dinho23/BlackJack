#include "Deck.h"

Deck::Deck()
{
    std::vector<char> simbol;
    std::pair<int,char> c;
    
    simbol.push_back('D');
    simbol.push_back('H');
    simbol.push_back('S');
    simbol.push_back('C');
    
    for(size_t i=1; i<14; i++) {
        for(size_t j=0; j<4; j++) {
           c = std::make_pair(i,simbol[j]);
           cards.push_back(c);
        }
    }
    
    simbol.clear();
}

void Deck::print(std::ostream &os) const {
    os << std::fixed;
    os << "There are: " << cards.size() << " left in the deck, they are:\n";
    for(size_t i=0; i<cards.size(); i++) 
        os << cards.at(i).first << " " << cards.at(i).second << "\t";
    
}

std::pair<int, char> Deck::draw_card() {
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);

    /* using nano-seconds instead of seconds */
    srand((time_t)ts.tv_nsec);
    return cards.at(rand() % 52 + 1);
}