#pragma once
#include <string>

class Account
{
private:
    static constexpr const char* def_name = "No-Name";
    static constexpr const char* def_username = "guest";
    static constexpr const char* def_password = "1234";
    static constexpr const char* def_email = "no_email@noemail.com";
    static constexpr int zero = 0;
    static constexpr int hundred = 100;
protected:
    std::string name;
    std::string username;
    std::string email;
    std::string password;
    long balance;
    int matches_won;
    int matches_played;
    double win_percentage;
public:
    Account(std::string name = def_name, std::string username = def_username, std::string email = def_email, std::string password = def_password, long balance = zero,
        int matches_won = zero, int matches_played = zero, double win_percentage = hundred);
    ~Account() = default;

    void add_to_database();
    bool deposit(long amount);
    void update_win_percentage();
    long check_balance();
    bool withdraw(long amount);
    void add_match(bool won);
    double get_win_percentage();
    void delete_from_database();

};