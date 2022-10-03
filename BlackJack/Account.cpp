#include "Account.h"
#include <fstream>
#include <iostream>
#include <cstring>

Account::Account(std::string name, std::string username, std::string email, std::string password, long balance, int matches_won, int matches_played, double win_percentage)
    : name{name}, username{username}, email{email}, password{password}, balance{balance}, matches_won{matches_won}, matches_played{matches_played}, win_percentage{win_percentage} {
        if(matches_played > 0)
            update_win_percentage();
    }
    
void Account::update_win_percentage() {
    if (matches_played!=0)
        win_percentage = (double)matches_won * 100 / matches_played;
}

void Account::print(std::ostream &os) const {
    os.precision(2);
    os << std::fixed;
    os << "\nAccount details:\nName: " << name << "\nUsername: " << username << "\nBallance: " << balance << "\nMatches won: " << matches_won << "\nMatches played: " << matches_played <<
        "\nWin Percentage: " << win_percentage <<"%\n\n";
}


bool Account::deposit(long amount) {
    if(amount < 0) 
        return false;
    else {
        balance += amount;
        return true;
    }
}

bool Account::withdraw(long amount) {
    std:: cout << balance << " " << amount << "\n";
    if(amount < 0 || balance < amount) 
        return false;
    else {
        balance -= amount;
        return true;
    }
}

long Account::check_balance() {
    return balance;
}

void Account::add_to_database() {
    std::ofstream of;
    of.open("accounts.txt", std::ios::app);
    of << name << " " << username << " " << email << " " << balance << " " << matches_won << " " << matches_played << " " << password;
    of.close();
}

void Account::add_match(bool won) {
    matches_played++;
    if (won)
        matches_won++;
}

double Account::get_win_percentage() {
    return win_percentage;
}

void Account::delete_from_database() {
    std::string line{}, eraseLine{};
    std::ifstream in;
    
    
    std::string path = "accounts.txt";
    
    eraseLine = name + " " + username + " " + email + " " + std::to_string(balance) + " " + std::to_string(matches_won) + " " + std::to_string(matches_played) + " " + password;
    
    in.open(path);
    // contents of path must be copied to a temp file then
    // renamed back to the path file
    std::ofstream temp;
    temp.open("temp.txt");

    while (getline(in, line)) {
    char *cstr = new char[line.length()+1];
    std::strcpy(cstr, line.c_str());
    
    char *token = std::strtok(cstr, " ");

    token = std::strtok(NULL, " ");
    char *char_username;
    char_username = token;
    
    token = std::strtok(NULL, " ");
    char *char_email;
    char_email = token;

    if (char_username != username && char_email != email  && line != "\n") 
        temp << line << std::endl;
    }

    temp.close();
    in.close();
    
    // required conversion for remove and rename functions
    const char * p = path.c_str();
    remove(p);
    rename("temp.txt", p);
}