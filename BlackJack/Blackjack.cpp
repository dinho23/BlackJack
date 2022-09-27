#include "Blackjack.h"

Blackjack::Blackjack(Deck deck, Dealer dealer, Player player)
    : deck{deck}, dealer{dealer}, player{player}
{
}

std::pair<int, char> Blackjack::draw() {
    size_t card_no{};
    srand(time(NULL));
    card_no = rand() % 52;
    return deck.draw_card(card_no);
}

void Blackjack::bet() {
    int amount{};
    std::cout << "How many $ would you like to bet?\n";
    std::cin >> amount;
    while (true) {
        if(amount <= 0) {
            std::cout << "Plase enter a valid amount!\n";
            std::cin >> amount;
        }
        else if (player.account_info().check_balance() < amount) {
            std::cout << "Insufficinet funds!\nPlase enter a valid amount!\n";
            std::cin >> amount;
        }
        else 
            break;
    }
    std::cout << player.account_info().withdraw(amount);
}

void Blackjack::play() {
    std::cout << "Balance: " << player.account_info().check_balance() << "\n";
    std::cout << "aici: " << player.account_info().withdraw(5) << "aici\n";
    bet();
}
