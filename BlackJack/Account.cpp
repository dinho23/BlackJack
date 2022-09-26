#include "Account.h"
#include <fstream>

Account::Account(std::string name, std::string username, std::string email, std::string password, unsigned long balance, unsigned int matches_won, unsigned int matches_played,
                double win_percentage)
    : name{name}, username{username}, email{email}, password{password}, balance{balance}, matches_won{matches_won}, matches_played{matches_played}, win_percentage{win_percentage} {
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
}