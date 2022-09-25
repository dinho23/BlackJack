#ifndef _ACCOUNT_H_
#define _ACCOUNT_H_
#include <string>
#include "I_Printable.h"

class Account : public I_Printable 
{
private:
    static constexpr const char *def_name = "No Name";
    static constexpr const char *def_username = "guest";
    static constexpr const char *def_password = "1234";
    static constexpr const char *def_email = "no_email@noemail.com";
    static constexpr int zero = 0;
protected:
    std::string name;
    std::string username;
    std::string email;
    std::string password;
    unsigned long balance;
    unsigned int matches_played;
    unsigned int matches_won;
    double win_percentage;
public:
    Account(std::string name = def_name, std::string username = def_username, std::string email = def_email, std::string password = def_password, unsigned long balance = zero);
    ~Account() = default;
    
    void add_to_database();
    bool deposit(long amount);
    void update_win_percentage();
    unsigned long check_balance();
    virtual void print(std::ostream &os) const override;

};

#endif // _ACCOUNT_H_
