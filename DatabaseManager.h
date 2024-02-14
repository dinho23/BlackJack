#pragma once
#include "mysql_connection.h"

#include <iostream>
#include <string>
#include <list>
#include <mysql_connection.h>
#include <cppconn/driver.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>
#include <cppconn/metadata.h>
#include <openssl/evp.h>


class DatabaseManager {
private:
    sql::Connection* con;

    const std::string server = "tcp://127.0.0.1:3306";
    const std::string username;
    const std::string password;

    std::string hashPassword(const std::string& password);

public:
    DatabaseManager();

    void connectDB();
    void createTables();
    void ensureTableExist(const std::string& tableName);
    void insertLoginInfo(const std::string& username, const std::string& password);
    void insertAccountDetails(const int& userId, const std::string& firstName, const std::string& email, const double& balance, const int& gamesWon, const int& gamesPlayed);
    void closeDB();

    bool isEmailInUse(const std::string& email);
    bool isUsernameInUse(const std::string& username);

    bool login(const std::string& username, const std::string& password);
    int getUserIdByUsername(const std::string& username);
    double getBalance(const std::string& username);
    std::string getFirstName(const std::string& username);
    std::string getEmail(const std::string& username);
    int getGamesPlayed(const std::string& username);
    int getGamesWon(const std::string& username);
    bool withdrawFromBalance(const std::string& username, double amount);
    bool depositToBalance(const std::string& username, double amount);
    bool increaseGamesPlayed(const std::string& username, bool won);
    bool increaseGamesWon(const std::string& username);

    std::string getEnvVar(const char* envVarName);
};