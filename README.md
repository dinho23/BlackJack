# Cross-Platform Blackjack Game with GUI, User Management and Data Encryption

This project is an implementation of the popular card game Blackjack written in C++17. It features a graphical user interface (GUI) created using wxWidgets, a C++ library for building cross-platform applications. MySQL is utilized for data storage and update, while OpenSSL handles data encryption.

Features

    Play Blackjack against a computer dealer.
    Graphical user interface (GUI) built with wxWidgets for an interactive gaming experience.
    Storing user information such as login credentials, account balance, and win percentage into a MySQL Database.
    Supports common Blackjack rules, including hitting, standing, and busting.
    Tracks player's balance, wins, and win percentage.
    Ability to create and log in with a user account.

Requirements

To build and run the Blackjack project, you will need the following:

    Visual Studio 2022 (recommended)
    C++17 compiler for game logic
    wxWidgets library for GUI Interface
    MySQL libraries and MySQL connector for C++ for storing/updating the data
    OpenSSL library for password encryption

Usage

    Upon launching the application, you will be presented with a main menu where you can choose to play Blackjack or quit the game.
    If you choose to play, you will have the option to log in with an existing account or create a new one.
    Once logged in, the account information is displayed on the upper left of the screen, showing your name, account balance, and win percentage.
    Available options once logged in: begin a match, with a custom amount to bet; deposit money into the account; withdraw money from the account.
    Once any change is done to the account balance, the account information will update instantly.
    Follow the on-screen instructions to hit, stand, or perform other actions during the game.
    After the game concludes, you will have the option to return to the main menu (still logged in).