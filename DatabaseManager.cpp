#include "DatabaseManager.h"

DatabaseManager::DatabaseManager() : username(getEnvVar("MYSQL_USER")), password(getEnvVar("MYSQL_PASSWORD"))
{
    try {
        connectDB();
    }
    catch (const std::exception& e) {
        std::cerr << "An error occurred: " << e.what() << '\n';
        throw;
    }
}

std::string DatabaseManager::getEnvVar(const char* envVarName) {
    char* envVarValue = nullptr;
    size_t requiredSize;

    errno_t err = _dupenv_s(&envVarValue, &requiredSize, envVarName);

    if (err != 0 || envVarValue == nullptr) {
        std::cerr << "Error: Environment variable " << envVarName << " not set or retrieval failed.\n";
        exit(1);
    }

    std::string result(envVarValue);
    free(envVarValue);

    return result;
}

void DatabaseManager::connectDB() {
    sql::Driver* driver;

    try {
        driver = get_driver_instance();
        con = driver->connect(server, username, password);
        ensureTableExist("LoginInfo");
        ensureTableExist("AccountDetails");
    }
    catch (const sql::SQLException& e) {
        std::cerr << "Could not connect to server. Error message: " << e.what() << '\n';
        throw;
    }
}

void DatabaseManager::ensureTableExist(const std::string& tableName) {
    try {
        sql::Statement* stmt = con->createStatement();

        stmt->execute("USE BlackjackDB");

        sql::ResultSet* res = stmt->executeQuery("SHOW TABLES LIKE '" + tableName + "'");
        if (res->next()) {
            std::cout << "Table " << tableName << " exists." << '\n';
        }
        else {
            createTables();
        }

        delete res;
        delete stmt;
    }
    catch (const sql::SQLException& e) {
        std::cerr << "SQL Exception: " << e.what() << '\n';
    }
}

void DatabaseManager::createTables() {
    sql::Statement* stmt;
    stmt = con->createStatement();

    stmt->execute("CREATE DATABASE IF NOT EXISTS BlackjackDB");
    stmt->execute("USE BlackjackDB");
    stmt->execute("DROP TABLE IF EXISTS LoginInfo");
    stmt->execute("DROP TABLE IF EXISTS AccountDetails");
    std::cout << "Finished dropping tables (if existed)\n";
    stmt->execute("CREATE TABLE LoginInfo (id INT AUTO_INCREMENT PRIMARY KEY, username VARCHAR(50) UNIQUE, password VARCHAR(500))");
    std::cout << "Finished creating LoginInfo table\n";
    stmt->execute("CREATE TABLE AccountDetails ( id INT AUTO_INCREMENT PRIMARY KEY, first_name VARCHAR(50), email VARCHAR(100) UNIQUE, balance DECIMAL(10, 2), games_won INT, games_played INT, user_id INT UNIQUE, FOREIGN KEY(user_id) REFERENCES LoginInfo(id))");
    std::cout << "Finished creating AccountDetails table\n";

    delete stmt;
}

void DatabaseManager::insertLoginInfo(const std::string& username, const std::string& password) {
    if (username.length() < 3) {
        std::cerr << "Username is too short.\n";
        return;
    }
    if (password.length() < 3) {
        std::cerr << "Password is too short.\n";
        return;
    }

    std::string hashedPassword = hashPassword(password);

    try {
        sql::PreparedStatement* pstmt;
        pstmt = con->prepareStatement("INSERT INTO LoginInfo (username, password) VALUES (?, ?)");
        pstmt->setString(1, username);
        pstmt->setString(2, hashedPassword);
        pstmt->execute();
        std::cout << "Inserted LoginInfo successfully\n";
        delete pstmt;
    }
    catch (const sql::SQLException& e) {
        std::cerr << "SQL Exception: " << e.what() << '\n';
    }

}

void DatabaseManager::insertAccountDetails(const int& userId, const std::string& firstName, const std::string& email, const double& balance, const int& gamesWon, const int& gamesPlayed) {
    try {
        sql::PreparedStatement* pstmt;

        pstmt = con->prepareStatement("INSERT INTO AccountDetails(user_id, first_name, email, balance, games_won, games_played) VALUES (?, ?, ?, ?, ?, ?)");
        pstmt->setInt(1, userId);
        pstmt->setString(2, firstName);
        pstmt->setString(3, email);
        pstmt->setDouble(4, balance);
        pstmt->setInt(5, gamesWon);
        pstmt->setInt(6, gamesPlayed);
        pstmt->execute();
        std::cout << "Inserted account details successfully\n";

        delete pstmt;
    }
    catch (sql::SQLException& e) {
        std::cout << "SQL Exception: " << e.what() << '\n';
    }
}

std::string DatabaseManager::hashPassword(const std::string& password) {
    EVP_MD_CTX* ctx = EVP_MD_CTX_new();

    EVP_DigestInit_ex(ctx, EVP_sha256(), NULL);
    EVP_DigestUpdate(ctx, password.c_str(), password.size());

    unsigned char hashedPassword[EVP_MAX_MD_SIZE];
    unsigned int hashedPasswordLen;

    EVP_DigestFinal_ex(ctx, hashedPassword, &hashedPasswordLen);
    EVP_MD_CTX_free(ctx);

    char hexHashedPassword[EVP_MAX_MD_SIZE * 2 + 1];

    for (unsigned int i = 0; i < hashedPasswordLen; ++i) {
        sprintf_s(hexHashedPassword + i * 2, 3, "%02x", hashedPassword[i]);
    }
    hexHashedPassword[hashedPasswordLen * 2] = '\0';

    return std::string(hexHashedPassword);
}

void DatabaseManager::closeDB()
{
    delete con;
    std::cout << "Closed connection successfully.\n";
}

bool DatabaseManager::isUsernameInUse(const std::string& username) {
    try {
        sql::PreparedStatement* pstmt;
        sql::ResultSet* res;

        pstmt = con->prepareStatement("SELECT COUNT(*) AS count FROM LoginInfo WHERE username = ?");
        pstmt->setString(1, username);

        res = pstmt->executeQuery();

        int count = 0;
        if (res->next()) {
            count = res->getInt("count");
        }

        delete pstmt;
        delete res;

        return count > 0;
    }
    catch (const sql::SQLException& e) {
        std::cerr << "SQL Exception: " << e.what() << '\n';
        return true;
    }
}

bool DatabaseManager::isEmailInUse(const std::string& email) {
    try {
        sql::PreparedStatement* pstmt;
        sql::ResultSet* res;

        pstmt = con->prepareStatement("SELECT COUNT(*) AS count FROM AccountDetails WHERE email = ?");
        pstmt->setString(1, email);

        res = pstmt->executeQuery();

        int count = 0;
        if (res->next()) {
            count = res->getInt("count");
        }

        delete pstmt;
        delete res;

        return count > 0;
    }
    catch (const sql::SQLException& e) {
        std::cerr << "SQL Exception: " << e.what() << '\n';
        return true;
    }
}

bool DatabaseManager::login(const std::string& username, const std::string& password) {
    try {
        sql::PreparedStatement* pstmt;
        sql::ResultSet* res;
        bool loginSuccessful = false;

        pstmt = con->prepareStatement("SELECT password FROM LoginInfo WHERE username = ?");
        pstmt->setString(1, username);

        res = pstmt->executeQuery();

        if (res->next()) {
            std::string hashedPasswordFromDB = res->getString("password");
            std::string hashedPasswordInput = hashPassword(password);

            if (hashedPasswordInput == hashedPasswordFromDB) {
                std::cout << "Login successful.\n";
                loginSuccessful = true;
            }
            else {
                std::cout << "Incorrect password.\n";
            }
        }
        else {
            std::cout << "Username not found.\n";
        }

        delete pstmt;
        delete res;

        return loginSuccessful;
    }
    catch (const sql::SQLException& e) {
        std::cerr << "SQL Exception: " << e.what() << '\n';
        return false;
    }
}

int DatabaseManager::getUserIdByUsername(const std::string& username) {
    try {
        sql::PreparedStatement* pstmt;
        sql::ResultSet* res;
        int userId = -1;

        pstmt = con->prepareStatement("SELECT id FROM LoginInfo WHERE username = ?");
        pstmt->setString(1, username);

        res = pstmt->executeQuery();

        if (res->next()) {
            userId = res->getInt("id");
        }
        else {
            std::cout << "Username not found.\n";
        }

        delete pstmt;
        delete res;

        return userId;
    }
    catch (const sql::SQLException& e) {
        std::cerr << "SQL Exception: " << e.what() << '\n';
        return -1;
    }
}

double DatabaseManager::getBalance(const std::string& username) {
    try {
        sql::PreparedStatement* pstmt;
        sql::ResultSet* res;
        double balance = 0.0;

        pstmt = con->prepareStatement("SELECT balance FROM AccountDetails WHERE user_id = (SELECT id FROM LoginInfo WHERE username = ?)");
        pstmt->setString(1, username);

        res = pstmt->executeQuery();

        if (res->next()) {
            balance = res->getDouble("balance");
        }
        else {
            std::cout << "User not found.\n";
        }

        delete pstmt;
        delete res;

        return balance;
    }
    catch (const sql::SQLException& e) {
        std::cerr << "SQL Exception: " << e.what() << '\n';
        return -1;
    }
}

std::string DatabaseManager::getFirstName(const std::string& username)
{
    try {
        sql::PreparedStatement* pstmt;
        sql::ResultSet* res;
        std::string firstName;

        pstmt = con->prepareStatement("SELECT first_name FROM AccountDetails WHERE user_id = (SELECT id FROM LoginInfo WHERE username = ?)");
        pstmt->setString(1, username);

        res = pstmt->executeQuery();

        if (res->next()) {
            firstName = res->getString("first_name");
        }
        else {
            std::cout << "User not found.\n";
        }

        delete pstmt;
        delete res;

        return firstName;
    }
    catch (const sql::SQLException& e) {
        std::cerr << "SQL Exception: " << e.what() << '\n';
        return "";
    }
}

std::string DatabaseManager::getEmail(const std::string& username)
{
    try {
        sql::PreparedStatement* pstmt;
        sql::ResultSet* res;
        std::string firstName;

        pstmt = con->prepareStatement("SELECT email FROM AccountDetails WHERE user_id = (SELECT id FROM LoginInfo WHERE username = ?)");
        pstmt->setString(1, username);

        res = pstmt->executeQuery();

        if (res->next()) {
            firstName = res->getString("email");
        }
        else {
            std::cout << "User not found.\n";
        }

        delete pstmt;
        delete res;

        return firstName;
    }
    catch (const sql::SQLException& e) {
        std::cerr << "SQL Exception: " << e.what() << '\n';
        return "";
    }
}

int DatabaseManager::getGamesPlayed(const std::string& username)
{
    try {
        sql::PreparedStatement* pstmt;
        sql::ResultSet* res;
        int matchesPlayed{};

        pstmt = con->prepareStatement("SELECT games_played FROM AccountDetails WHERE user_id = (SELECT id FROM LoginInfo WHERE username = ?)");
        pstmt->setString(1, username);

        res = pstmt->executeQuery();

        if (res->next()) {
            matchesPlayed = res->getInt("games_played");
        }
        else {
            std::cout << "User not found.\n";
        }

        delete pstmt;
        delete res;

        return matchesPlayed;
    }
    catch (const sql::SQLException& e) {
        std::cerr << "SQL Exception: " << e.what() << '\n';
        return -1;
    }
}

int DatabaseManager::getGamesWon(const std::string& username)
{
    try {
        sql::PreparedStatement* pstmt;
        sql::ResultSet* res;
        int matchesWon{};

        pstmt = con->prepareStatement("SELECT games_won FROM AccountDetails WHERE user_id = (SELECT id FROM LoginInfo WHERE username = ?)");
        pstmt->setString(1, username);

        res = pstmt->executeQuery();

        if (res->next()) {
            matchesWon = res->getInt("games_won");
        }
        else {
            std::cout << "User not found.\n";
        }

        delete pstmt;
        delete res;

        return matchesWon;
    }
    catch (const sql::SQLException& e) {
        std::cerr << "SQL Exception: " << e.what() << '\n';
        return -1;
    }
}

bool DatabaseManager::withdrawFromBalance(const std::string& username, double amount) {
    try {
        double currentBalance = getBalance(username);
        if (currentBalance < amount) {
            std::cout << "Insufficient balance. Withdrawal canceled.\n";
            return false;
        }

        double newBalance = currentBalance - amount;

        sql::PreparedStatement* pstmt;
        pstmt = con->prepareStatement("UPDATE AccountDetails SET balance = ? WHERE user_id = (SELECT id FROM LoginInfo WHERE username = ?)");
        pstmt->setDouble(1, newBalance);
        pstmt->setString(2, username);
        pstmt->execute();

        delete pstmt;

        std::cout << "Withdrawal successful. New balance: " << newBalance << '\n';
        return true;
    }
    catch (const sql::SQLException& e) {
        std::cerr << "SQL Exception: " << e.what() << '\n';
        return false;
    }
}

bool DatabaseManager::depositToBalance(const std::string& username, double amount) {
    try {
        double currentBalance = getBalance(username);
        if (currentBalance + amount < 0.0) {
            std::cout << "Error while trying to deposit.\n";
            return false;
        }

        double newBalance = currentBalance + amount;

        sql::PreparedStatement* pstmt;
        pstmt = con->prepareStatement("UPDATE AccountDetails SET balance = ? WHERE user_id = (SELECT id FROM LoginInfo WHERE username = ?)");
        pstmt->setDouble(1, newBalance);
        pstmt->setString(2, username);
        pstmt->execute();

        delete pstmt;

        std::cout << "Deposit successful. New balance: " << newBalance << '\n';
        return true;
    }
    catch (const sql::SQLException& e) {
        std::cerr << "SQL Exception: " << e.what() << 'n';
        return false;
    }
}

bool DatabaseManager::increaseGamesPlayed(const std::string& username, bool won)
{
    try {
        int gamesPlayed = getGamesPlayed(username) + 1;

        if (won) {
            increaseGamesWon(username);
        }

        sql::PreparedStatement* pstmt;
        pstmt = con->prepareStatement("UPDATE AccountDetails SET games_played = ? WHERE user_id = (SELECT id FROM LoginInfo WHERE username = ?)");
        pstmt->setInt(1, gamesPlayed);
        pstmt->setString(2, username);
        pstmt->execute();

        delete pstmt;

        return true;
    }
    catch (const sql::SQLException& e) {
        std::cerr << "SQL Exception: " << e.what() << 'n';
        return false;
    }
}

bool DatabaseManager::increaseGamesWon(const std::string& username)
{
    try {
        int gamesWon = getGamesWon(username) + 1;

        sql::PreparedStatement* pstmt;
        pstmt = con->prepareStatement("UPDATE AccountDetails SET games_won = ? WHERE user_id = (SELECT id FROM LoginInfo WHERE username = ?)");
        pstmt->setInt(1, gamesWon);
        pstmt->setString(2, username);
        pstmt->execute();

        delete pstmt;

        return true;
    }
    catch (const sql::SQLException& e) {
        std::cerr << "SQL Exception: " << e.what() << 'n';
        return false;
    }
}
