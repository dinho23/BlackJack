#include "Account.h"
#include <fstream>
#include <iostream>
#include <cstring>

Account::Account(std::string name, std::string username, std::string email, std::string password, long balance, int matches_won, int matches_played, double win_percentage)
    : name{ name }, username{ username }, email{ email }, password{ password }, balance{ balance }, matches_won{ matches_won }, matches_played{ matches_played }, win_percentage{ win_percentage } {
    if (matches_played > 0)
        update_win_percentage();
}

void Account::update_win_percentage() {
    if (matches_played != 0)
        win_percentage = (double)matches_won * 100 / matches_played;
}

bool Account::deposit(long amount) {
    if (amount < 0)
        return false;
    else {
        balance += amount;
        return true;
    }
}

bool Account::withdraw(long amount) {
    std::cout << balance << " " << amount << "\n";
    if (amount < 0 || balance < amount)
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
    //of << '\n';
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

    while (std::getline(in, line)) {
        char* cstr = new char[line.length() + 1];
        strcpy_s(cstr, line.length() + 1, line.c_str());

        char* token = nullptr;
        char* next_token = nullptr; // Declare next_token variable

        token = strtok_s(cstr, " ", &next_token);

        token = strtok_s(NULL, " ", &next_token);
        char* char_username;
        char_username = token;

        token = strtok_s(NULL, " ", &next_token);
        char* char_email;
        char_email = token;

        if (!line.empty()) {
            std::string temp_username = char_username;
            std::string temp_email = char_email;
            if (temp_username != username && temp_email != email) {
                temp << line << '\n';
            }
        }

        delete[] cstr; // Free memory allocated by new[]
    }

    temp.close();
    in.close();

    // required conversion for remove and rename functions
    const char* p = path.c_str();
    remove(p);
    rename("temp.txt", p);
}
