#include "Account.h"
#include <fstream>

Account::Account(std::string name, std::string username, std::string password, std::string email, unsigned long balance)
    : name{name}, username{username}, email{email}, password{password}, balance{balance}, matches_played{0}, matches_won{0}, win_percentage{100} {
        add_to_database();
    }
    
void Account::update_win_percentage() {
    if (matches_played!=0)
        win_percentage = matches_played / matches_won;
}

void Account::print(std::ostream &os) const {
    os.precision(2);
    os << std::fixed;
    os << "Account details:\nName: " << name << "\nUsername: " << username << "\nBallance: " << balance << "\nMatches won: " << matches_won << "\nMatches played: " << matches_played <<
        "\nWin Percentage: " << win_percentage <<"%\n";
}


bool Account::deposit(long amount) {
    if(amount < 0) 
        return false;
    else {
        balance += amount;
        return true;
    }
}

unsigned long Account::check_balance() {
    return balance;
}

void Account::add_to_database() {
    std::ofstream of;
    of.open("accounts.txt", std::ios::app);
    of << '\n' << name << " " << username << " " << email << " " << balance << " " << matches_won << " " << matches_played << " " << password;
    of.close();
    
    of.open("login_info.txt", std::ios::app);
    of << "\n" << username << " " << password << " " << email;
    of.close();
}