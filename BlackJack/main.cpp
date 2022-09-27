#include <iostream>
#include <fstream>
#include <vector>
#include "Account.h"
#include "Deck.h"
#include "Blackjack.h"
#include "Player.h"

void login(Player &player, size_t &logged_in);
void create_acc(Player &player, size_t &logged_in);
bool verify_acc(std::string username, std::string email);


void display_menu() {
    char in{};
    size_t logged_in {0};
    Player player;
    
    std::cout << in;
    
    std::cout << "Welcome!\n\nWhat would you like to do:\n";
    
    do {
        if (logged_in == 0) {
            std::cout << "1. Log in\n";
            std::cout << "2. Create an account\n";
        }
        else {
            std::cout << "1. Play blackjack\n";
        }
        std::cout << "0. Exit\n";
    
        std::cin >> in;
    
        if(in == '1' && logged_in == 0)
            login(player, logged_in);
        else if (in == '2' && logged_in == 0)
            create_acc(player, logged_in);
        else if (in == '1' && logged_in == 1) {
            Deck deck;
            Dealer dealer;
            Blackjack game = Blackjack(deck, dealer, player);
            game.play();
        }
        else if (in == '0')
            std::cout << "Exiting...\n";
        else {
            std::cout << "Invalid choice, please try again.\n";
        }
    } while (in != '0');
    
}

bool verify_acc(std::string username, std::string email) {
    std::string  existing_name{}, existing_username{}, existing_email{}, existing_balance{}, existing_won{}, existing_played{}, existing_password{};
            
    std::ifstream in;
    in.open("accounts.txt");
    
    if (!in) {
        std::cout << "Failled to open the accounts database.\n";
        exit(0);
    }
    
    while(!in.eof()) {
        std::getline(in, existing_name, ' ');
        std::getline(in, existing_username, ' ');
        std::getline(in, existing_email, ' ');
        std::getline(in, existing_balance, ' ');
        std::getline(in, existing_won, ' ');
        std::getline(in, existing_played, ' ');
        std::getline(in, existing_password);
        
        if(existing_username == username) {
            std::cout << "Username already taken, please try another one:\n";
            return 0;
        }
        if(username.size() < 3) {
            std::cout << "Username must have be at least 3 characters long, please try again:\n";
            return 0;
        }
        if(existing_email == email) {
            std::cout << "eMail already taken, please try another one:\n";
            return 0;
        }
    }
    
    in.close();
    
    return 1;
}

void create_acc(Player &player, size_t &logged_in) {
    std::string name{}, username{}, email{}, password{};
    
    do {
        std::cout << "Enter your first name:\n";
        std::cin >> name;
        std::cout << "Enter your username:\n";
        std::cin >> username;
        std::cout << "Enter your eMail:\n";
        std::cin >> email;
        std::cout << "Enter your password:\n";
        std::cin >> password;
        
    } while (verify_acc(username, email) != 1);
    
    for(size_t i = 0; i < name.size(); i++)
        if(name[i] == ' ')
            name[i] = '_';
    
    Account new_acc = Account(name, username, email, password, 100);
    new_acc.add_to_database();
    player = Player(new_acc);
    logged_in = 1;

}

void login(Player &player, size_t &logged_in) {
    std::ifstream in;
    in.open("accounts.txt");
    
    if (!in) {
        std::cout << "Failled to open the accounts database.\n";
        exit(0);
    }
    
    std::string  existing_name{}, existing_username{}, existing_email{}, existing_balance{}, existing_won{}, existing_played{}, existing_password{};
    std::string  username{}, password{};
    
    std::cout << "Enter your username:\n";
    std::cin >> username;
    std::cout << "Enter your password:\n";
    std::cin >> password;
    
    size_t no_attempts{3};
    
    while(!in.eof()) {
        std::getline(in, existing_name, ' ');
        std::getline(in, existing_username, ' ');
        std::getline(in, existing_email, ' ');
        std::getline(in, existing_balance, ' ');
        std::getline(in, existing_won, ' ');
        std::getline(in, existing_played, ' ');
        std::getline(in, existing_password);
        
        while(username == existing_username && password != existing_password && no_attempts!=0) {
            std::cout << "Wrong password! Please enter the password again.\n";
            std::cout << "Attempts left " << no_attempts << "\n";
            no_attempts--;
            std::cin >> password;
        }
        
        if(username == existing_username && password == existing_password) {
            player = Player(Account(existing_name, existing_username, existing_email, existing_password, std::stoi(existing_balance), std::stoi(existing_won), std::stoi(existing_played)));
            logged_in = 1;
            break;
        }
    }
    
    in.close();
}


int main()
{
    
    display_menu();
    
    return 0;
}