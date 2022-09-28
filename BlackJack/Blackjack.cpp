#include "Blackjack.h"

Blackjack::Blackjack(Deck deck, Dealer dealer, Player player)
    : deck{deck}, dealer{dealer}, player{player}
{
}


std::pair<int, char> Blackjack::draw_cards() {
    Deck deck;
    return deck.draw_card();
}

void Blackjack::show_table(Player &player, Dealer &dealer) {
    player.reset_hand();
    dealer.reset_hand();
    
    player.set_card(deck.draw_card());
    dealer.set_card(deck.draw_card());
    player.set_card(deck.draw_card());
    dealer.set_card(deck.draw_card());
    
    std::cout << "Dealer:\n";
    std::cout << dealer.get_card(0).first << "-" << dealer.get_card(0).second << " and a faced down card\n";
    std::cout << "You:\n";
    for (size_t i = 0; i < player.get_hand().size(); i++)
        std::cout << player.get_card(i).first << "-" << player.get_card(i).second << ";";
    std::cout << '\n';
    std::cout << "Dealer's points: " << dealer.get_first_card_points() << "\n";
    std::cout << "Your total points: " << player.get_total_points() << "\n";
}

void Blackjack::bet(Player &player, Dealer &dealer) {
    int amount{};
    
    std::cout << "How much would you like to bet?\n";
    
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
    
    player.withdraw_from_acc(amount);
    
    std::cout << "\nDealing the cards...\n";
    show_table(player, dealer);
    
}

void Blackjack::deposit(Player &player) {
    int amount{};
    
    std::cout << "How much would you like to deposit?\n";
    
    std::cin >> amount;
    
    do {
        if(amount <= 0) {
            std::cout << "Plase enter a valid amount!\n";
            std::cin >> amount;
        }
        else 
            player.deposit_to_acc(amount);
    } while (amount <=0);
}

void Blackjack::withdraw(Player &player) {
    int amount{};
    
    std::cout << "How much would you like to withdraw?\n";
    
    std::cin >> amount;
    
    do {
        if(amount <= 0) {
            std::cout << "Plase enter a valid amount!\n";
            std::cin >> amount;
        }
        else if (player.account_info().check_balance() < amount) {
            std::cout << "Insufficinet funds!\nPlase enter a valid amount!\n";
            std::cin >> amount;
        }
        else 
            player.withdraw_from_acc(amount);
    } while (amount <=0);
}

void Blackjack::play(Player &player) {
    char in{};
    do {
        std::cout << "1. Begin a match\n";
        std::cout << "2. Deposit money on your account\n";
        std::cout << "3. Withdraw money from your account\n\n";
        std::cout << "0. Exit\n";
        
        std::cin >> in;
        
        if(in == '1')
            bet(player, dealer);
        else if (in == '2')
            deposit(player);
        else if (in == '3')
            withdraw(player);
    } while (in != '0');
}
