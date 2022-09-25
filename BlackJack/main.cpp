#include <iostream>
#include <fstream>
#include <vector>
#include "Account.h"
#include "Deck.h"
#include "Blackjack.h"
#include "Player.h"

void login();


void display_menu() {
    char in{};
    
    std::cout << "Welcome!\n\nWhat would you like to do:\n";
    
    while(in != '3') {
        std::cout << "1. Log in\n";
        std::cout << "2. Create an account\n";
        std::cout << "3. Exit\n";
    
        std::cin >> in;
    
        if(in == '1')
            login();
        else if (in == '2')
            std::cout << "Redirecting you to create an account.\n";
        else if (in == '3')
            std::cout << "Exiting...\n";
        else
            std::cout << "Invalid choice, please try again.\n";
    }
    
}

void login() {
    std::ifstream in;
    in.open("login_info.txt");
    
    if (!in) {
        std::cout << "Failled to open the accounts database.\n";
        exit(0);
    }
    
    std::string username{}, password{}, existing_username{}, existing_email{}, existing_password{};
    std::cout << "Enter your username:\n";
    std::cin >> username;
    std::cout << "Enter your password:\n";
    std::cin >> password;
    
    size_t no_attempts{3};
    
    while(!in.eof()) {
        std::getline(in, existing_username, ' ');
        std::getline(in, existing_email, ' ');
        std::getline(in, existing_password);
        std::cout << existing_username << " " << existing_password << "\n";
        if(username == existing_username && password == existing_password) {
            std::cout << "You have successfully logged in!\n";
            break;
        }
        while(username == existing_username && password != existing_password && no_attempts!=0) {
            std::cout << "Wrong password! Please try again.\n";
            std::cout << "Attempts left " << no_attempts << "\n";
            no_attempts--;
            std::cin >> password;
        }
    }
    
    in.close();
}


int main()
{
    display_menu();
    
    Account user1("Andrei","dinho23","test@gmail.com","pass",100);
    std::cout << user1;
    
    
    Deck deck;
    std::cout << deck;
    
    return 0;
}