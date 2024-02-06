#include "Mainframe.h"
#include <wx/wx.h>
#include <wx/simplebook.h>
#include <wx/generic/statbmpg.h>
#include <string>
#include <fstream>
#include <thread>
#include "Account.h"
#include "Player.h"
#include "Dealer.h"
#include "Deck.h"

Mainframe::Mainframe(const wxString& title) : wxFrame(nullptr, wxID_ANY, title)
{
    SetMinSize(wxSize(400, 400));

    LoadImages();
    notebook = new wxSimplebook(this, wxID_ANY);

    firstPanel = new wxPanel(notebook);
    firstPanel->SetBackgroundColour(wxColour(128, 128, 128));

    playButton = new wxButton(firstPanel, wxID_ANY, "Play BlackJack", wxDefaultPosition, wxSize(100, 50));
    quitButton = new wxButton(firstPanel, wxID_ANY, "Quit", wxDefaultPosition, wxSize(100, 50));

    playButton->Bind(wxEVT_BUTTON, &Mainframe::OnPlayPressed, this);
    quitButton->Bind(wxEVT_BUTTON, &Mainframe::OnQuitPressed, this);
    
    AddSizerToPanel(firstPanel, {playButton, quitButton});

    notebook->AddPage(firstPanel, "Main Menu");
}

void Mainframe::AddSizerToPanel(wxPanel* frame, std::vector<wxControl*> controls)
{
    wxBoxSizer* s1 = new wxBoxSizer(wxVERTICAL);

    s1->AddStretchSpacer(1);
    for (auto control : controls)
    {
        s1->Add(control, 0, wxALIGN_CENTER | wxALL, 5);
    }
    s1->AddStretchSpacer(1);

    frame->SetSizerAndFit(s1);
}

void Mainframe::OnQuitPressed(wxCommandEvent& evt)
{
    wxMessageDialog dialog(this, "Are you sure you want to quit?", "Quit", wxYES_NO | wxICON_QUESTION);
    int result = dialog.ShowModal();
    if (result == wxID_YES) {
        Close();
    }
}

void Mainframe::OnPlayPressed(wxCommandEvent& evt)
{
    loginPanel = new wxPanel(notebook);
    loginPanel->SetBackgroundColour(wxColour(128, 128, 128));

    loginButton = new wxButton(loginPanel, wxID_ANY, "Log in", wxPoint(350, 200), wxSize(100, 50));
    createAccount = new wxButton(loginPanel, wxID_ANY, "Create an account", wxPoint(350, 275), wxSize(100, 50));
    backButton = new wxButton(loginPanel, wxID_ANY, "Back", wxPoint(350, 350), wxSize(100, 50));

    loginButton->Bind(wxEVT_BUTTON, &Mainframe::OnLoginPressed, this);
    createAccount->Bind(wxEVT_BUTTON, &Mainframe::OnCreateAccountPressed, this);
    backButton->Bind(wxEVT_BUTTON, &Mainframe::OnBackPressed, this);

    AddSizerToPanel(loginPanel, { loginButton, createAccount, backButton });

    notebook->AddPage(loginPanel, "Login");
    notebook->ShowNewPage(loginPanel);
}

void Mainframe::OnLoginPressed(wxCommandEvent& evt)
{
    CreateAccountDetailsPanel();
}

void Mainframe::CreateAccountDetailsPanel()
{
    credentialsPanel = new wxPanel(notebook);
    credentialsPanel->SetBackgroundColour(wxColour(128, 128, 128));

    wxStaticText* enterUsername = new wxStaticText(credentialsPanel, wxID_ANY, "Username:", wxPoint(350, 180));
    usernameBox = new wxTextCtrl(credentialsPanel, wxID_ANY, "", wxPoint(350, 195));

    wxStaticText* enterPassword = new wxStaticText(credentialsPanel, wxID_ANY, "Password:", wxPoint(350, 230));
    passwordBox = new wxTextCtrl(credentialsPanel, wxID_ANY, "", wxPoint(350, 245), wxDefaultSize, wxTE_PASSWORD);

    enterCredentials = new wxButton(credentialsPanel, wxID_ANY, "Enter", wxPoint(380, 275), wxSize(50, -1));

    enterCredentials->Bind(wxEVT_BUTTON, &Mainframe::OnCredentialsEntered, this);

    AddSizerToPanel(credentialsPanel, { enterUsername, usernameBox, enterPassword,  passwordBox, enterCredentials });

    notebook->AddPage(credentialsPanel, "Credentials");
    notebook->ShowNewPage(credentialsPanel);
}

void Mainframe::OnCreateAccountPressed(wxCommandEvent& evt)
{
    createAccountPanel = new wxPanel(notebook);
    createAccountPanel->SetBackgroundColour(wxColour(128, 128, 128));

    wxStaticText* enterFirstName = new wxStaticText(createAccountPanel, wxID_ANY, "First name:", wxPoint(350, 180));
    firstNameBox = new wxTextCtrl(createAccountPanel, wxID_ANY, "", wxPoint(350, 195));

    wxStaticText* enterUsername = new wxStaticText(createAccountPanel, wxID_ANY, "Username:", wxPoint(350, 230));
    usernameBox = new wxTextCtrl(createAccountPanel, wxID_ANY, "", wxPoint(350, 245));

    wxStaticText* enterEmail = new wxStaticText(createAccountPanel, wxID_ANY, "eMail:", wxPoint(350, 280));
    emailBox = new wxTextCtrl(createAccountPanel, wxID_ANY, "", wxPoint(350, 295));

    wxStaticText* enterPassword = new wxStaticText(createAccountPanel, wxID_ANY, "Password:", wxPoint(350, 330));
    passwordBox = new wxTextCtrl(createAccountPanel, wxID_ANY, "", wxPoint(350, 345), wxDefaultSize, wxTE_PASSWORD);

    newAccountButton = new wxButton(createAccountPanel, wxID_ANY, "Enter", wxPoint(380, 395), wxSize(50, -1));

    newAccountButton->Bind(wxEVT_BUTTON, &Mainframe::VerifyExistingAccount, this);

    notebook->AddPage(createAccountPanel, "Create Account");
    notebook->ShowNewPage(createAccountPanel);
}

void Mainframe::OnBackPressed(wxCommandEvent& evt)
{
    notebook->ShowNewPage(firstPanel);
}

void Mainframe::OnCredentialsEntered(wxCommandEvent& evt)
{
    if (!VerifyAccountDetails()) 
    {
        wxMessageBox(wxT("User not found or invalid credentials! Please try again."), wxT("Invalid Credentials"), wxICON_INFORMATION);
        return;
    }
    ShowBeginGamePanel();
}

void Mainframe::VerifyExistingAccount(wxCommandEvent& evt) {
    std::string  existing_name{}, existing_username{}, existing_email{}, existing_balance{}, existing_won{}, existing_played{}, existing_password{};

    firstName = firstNameBox->GetValue().ToStdString();
    username = usernameBox->GetValue().ToStdString();
    email = emailBox->GetValue().ToStdString();
    password = passwordBox->GetValue().ToStdString();

    if (firstName.empty() || username.empty() || email.empty() || password.empty())
    {
        wxMessageBox(wxT("No filed can be left empty, plase fill all the fields and try again!"), wxT("No empty fields"), wxICON_INFORMATION);
        return;
    }
    if (username.size() < 3) {
        wxMessageBox(wxT("Username must have be at least 3 characters long, please try again"), wxT("Username too short"), wxICON_INFORMATION);
        return;
    }

    std::ifstream in;
    in.open("accounts.txt");

    if (!in) {
        wxMessageBox(wxT("Failled to open the accounts database."), wxT("Database fail"), wxICON_INFORMATION);
        Close();
    }

    while (!in.eof()) {
        std::getline(in, existing_name, ' ');
        std::getline(in, existing_username, ' ');
        std::getline(in, existing_email, ' ');
        std::getline(in, existing_balance, ' ');
        std::getline(in, existing_won, ' ');
        std::getline(in, existing_played, ' ');
        std::getline(in, existing_password);

        if (existing_username == username) {
            wxMessageBox(wxT("Username already taken, please try another one"), wxT("Username taken"), wxICON_INFORMATION);
            return;
        }
        if (existing_email == email) {
            wxMessageBox(wxT("eMail already taken, please try another one"), wxT("eMail taken"), wxICON_INFORMATION);
            return;
        }
    }

    in.close();

    CreateAccount();

    ShowBeginGamePanel();
}

void Mainframe::CreateAccount() {
    loggedInAccount = new Account(firstName, username, email, password, 100);
    player = new Player(*loggedInAccount);

}

void Mainframe::ShowBeginGamePanel()
{
    gameOptionsPanel = new wxPanel(notebook);
    gameOptionsPanel->SetBackgroundColour(wxColour(128, 128, 128));

    UpdateAcoountInfo();

    accountDetailsText = new wxStaticText(gameOptionsPanel, wxID_ANY, GetAccountDetails(), wxPoint(10, 10));

    wxButton* beginButton = new wxButton(gameOptionsPanel, wxID_ANY, "Begin a match", wxPoint(350, 200), wxSize(100, 50));
    wxButton* depositButton = new wxButton(gameOptionsPanel, wxID_ANY, "Deposit money", wxPoint(350, 275), wxSize(100, 50));
    wxButton* withdrawButton = new wxButton(gameOptionsPanel, wxID_ANY, "Withdraw money", wxPoint(350, 350), wxSize(100, 50));

    beginButton->Bind(wxEVT_BUTTON, &Mainframe::OnBeginGame, this);
    depositButton->Bind(wxEVT_BUTTON, &Mainframe::DepositMoney, this);
    withdrawButton->Bind(wxEVT_BUTTON, &Mainframe::WithdrawMoney, this);

    AddSizerToPanel(gameOptionsPanel, { beginButton, depositButton, withdrawButton });

    notebook->AddPage(gameOptionsPanel, "GameOptions");
    notebook->ShowNewPage(gameOptionsPanel);
}

void Mainframe::OnBeginGame(wxCommandEvent& evt)
{
    wholeGamePanel = new wxPanel(notebook);
    wholeGamePanel->SetBackgroundColour(wxColour(128, 128, 128));


    topGamePanel = new wxPanel(wholeGamePanel, wxID_ANY, wxDefaultPosition, wxSize(-1, 150));
    topGamePanel->SetBackgroundColour(wxColour(100, 100, 200));
    middleGamePanel = new wxPanel(wholeGamePanel, wxID_ANY, wxDefaultPosition, wxSize(-1, 300));
    middleGamePanel->SetBackgroundColour(wxColour(100, 200, 100));
    bottomGamePanel = new wxPanel(wholeGamePanel, wxID_ANY, wxDefaultPosition, wxSize(-1, 150));
    bottomGamePanel->SetBackgroundColour(wxColour(200, 100, 100));

    gameSizer = new wxBoxSizer(wxVERTICAL);
    topSizer = new wxBoxSizer(wxHORIZONTAL);
    middleSizer = new wxBoxSizer(wxHORIZONTAL);
    bottomSizer = new wxBoxSizer(wxHORIZONTAL);
    gameSizer->Add(topGamePanel, 1, wxEXPAND);
    gameSizer->Add(middleGamePanel, 2, wxEXPAND);
    gameSizer->Add(bottomGamePanel, 1, wxEXPAND);

    dealer = new Dealer();

    gameResult = new wxStaticText(middleGamePanel, wxID_ANY, "");
    dealerPoints = new wxStaticText(middleGamePanel, wxID_ANY, "", wxPoint(350, 160));
    playerPoints = new wxStaticText(middleGamePanel, wxID_ANY, "", wxPoint(350, 425));
    drawButton = new wxButton(middleGamePanel, wxID_ANY, "Draw", wxPoint(310, 280), wxSize(50, -1));
    stopButton = new wxButton(middleGamePanel, wxID_ANY, "Stop", wxPoint(365, 280), wxSize(50, -1));
    backToStartGame = new wxButton(middleGamePanel, wxID_ANY, "Return", wxPoint(350, 280), wxSize(50, -1));

    drawButton->Show(true);
    stopButton->Show(true);
    backToStartGame->Show(false);
    InitGame();

    std::string dealerPointsString = "Dealer: " + std::to_string(dealer->get_total_points(true));
    std::string playerPointsString = "You: " + std::to_string(player->get_points());
    dealerPoints->SetLabel(dealerPointsString);
    playerPoints->SetLabel(playerPointsString);

    drawButton->Bind(wxEVT_BUTTON, &Mainframe::OnDrawCard, this);
    stopButton->Bind(wxEVT_BUTTON, &Mainframe::OnStopEntered, this);

    DrawDealerCards(true);

    middleSizer = new wxBoxSizer(wxVERTICAL);
    middleSizer->AddStretchSpacer(1);
    middleSizer->Add(gameResult, 0, wxALIGN_CENTER);
    middleSizer->Add(dealerPoints, 0, wxALIGN_CENTER);
    middleSizer->Add(drawButton, 0, wxALIGN_CENTER);
    middleSizer->Add(stopButton, 0, wxALIGN_CENTER);
    middleSizer->Add(backToStartGame, 0, wxALIGN_CENTER);
    middleSizer->Add(playerPoints, 0, wxALIGN_CENTER);
    middleSizer->AddStretchSpacer(1);
    middleGamePanel->SetSizerAndFit(middleSizer);

    DrawPlayerCards();

    wholeGamePanel->SetSizerAndFit(gameSizer);

    notebook->AddPage(wholeGamePanel, "Gameplay");
    notebook->ShowNewPage(wholeGamePanel);
}

void Mainframe::LoadImages()
{
    wxPNGHandler* handler = new wxPNGHandler;
    wxImage::AddHandler(handler);

    ::wxInitAllImageHandlers();

    wxImage image("classic-cards.png", wxBITMAP_TYPE_PNG);

    wxBitmap b(image);
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 13; j++) {
            cards.push_back(b.GetSubBitmap(wxRect(5 + j * 225, 5 + i * 310, 215, 300)));
        }
    }
    for (auto& card : cards)
    {
        wxBitmap::Rescale(card, wxSize(107, 150));
    }

    wxImage backImage("Card-Back-03.png", wxBITMAP_TYPE_PNG);
    wxBitmap b2(backImage);
    cards.push_back(b2.GetSubBitmap(wxRect(1, 1, 107, 150)));
}

void Mainframe::OnStopEntered(wxCommandEvent& evt)
{
    RemoveBackCardAndEnterDealersTurn();
}

void Mainframe::RemoveBackCardAndEnterDealersTurn()
{

    topSizer->Hide(2);
    topSizer->Detach(2);
    DealersTurn();
}

void Mainframe::PrintDealerPointsAndCards()
{
    std::string dealerPointsString = "Dealer: " + std::to_string(dealer->get_points());
    dealerPoints->SetLabel(dealerPointsString);
    dealerPoints->Update(); 


    wxBitmap cardBitmap = cards.at(dealer->get_hand().back());
    wxStaticBitmap* cardImage = new wxStaticBitmap(topGamePanel, wxID_ANY, cardBitmap);
    topSizer->Insert(dealer->get_hand().size(), cardImage, 0, wxALIGN_CENTER | wxALL, 5);
}

void Mainframe::DealersTurn()
{
    wxStaticText* gameCurrentState = new wxStaticText(middleGamePanel, wxID_ANY, "", wxPoint(340, 240));

    drawButton->Show(false);
    stopButton->Show(false);

    int cardValue{};

    for (int i=0; i< dealer->get_hand().size(); i++)
    {
        if (dealer->get_hand().at(i) % 13 == 0)
        {
            cardValue = 11;
        }
        else
        {
            cardValue = std::min(((dealer->get_hand().at(i) % 13) + 1), 10);
        }
        dealer->add_points(cardValue);
    }
    
    PrintDealerPointsAndCards();
    gameSizer->Layout();
    notebook->Update();

    if (dealer->get_points() == 21) {
        gameResult->SetLabel("Dealer has a natural Blackjack!");
        if (dealer->get_points() == player->get_points()) {
            gameResult->SetLabel("It's a Blackjack draw");
            player->add_match(0);
        }
        else {
            gameResult->SetLabel("You lost...");
            player->add_match(0);
        }
        PlayAgainOrReturn();
        return;
    }

    if (dealer->get_points() < 17) {
        std::this_thread::sleep_for(std::chrono::seconds(2));

        do {
            dealer->set_card(deck.draw_card());

            if (dealer->get_hand().back() % 13 == 0)
            {
                cardValue = 11;
            }
            else
            {
                cardValue = std::min(((dealer->get_hand().back() % 13) + 1), 10);
            }

            dealer->add_points(cardValue);

            if (dealer->get_points() > 21)
            {
                dealer->get_total_points(false);
            }

            PrintDealerPointsAndCards();
            gameSizer->Layout();
            notebook->Update();

            std::this_thread::sleep_for(std::chrono::seconds(2));
        } while (dealer->get_points() <= 16);
    }

    if (dealer->get_points() > player->get_points() && dealer->get_points() <= 21) {
        gameResult->SetLabel("You lost...");
        player->add_match(0);
    }
    else if (dealer->get_points() == player->get_points()) {
        gameResult->SetLabel("It's a draw...");
        player->add_match(0);
        //player->deposit_to_acc(amount);
    }
    else {
        gameResult->SetLabel("You Won!!!");
        player->add_match(1);
        //player->deposit_to_acc(amount * 2);
    }

    PlayAgainOrReturn();
}

void Mainframe::InitGame()
{
    player->reset_hand();
    dealer->reset_hand();

    player->set_card(deck.draw_card());
    player->set_card(deck.draw_card());
    //player->set_card(1);
    //player->set_card(8);
    dealer->set_card(deck.draw_card());
    dealer->set_card(deck.draw_card());
    //dealer->set_card(0);
    //dealer->set_card(13);

    int cardValue{};

    for (size_t i = 0; i < player->get_hand().size(); i++)
    { 
        if(player->get_hand().at(i) % 13 == 0)
        {
            cardValue = 11;
        }
        else
        {
            cardValue = std::min(((player->get_hand().at(i) % 13) + 1), 10);
        }

        player->add_points(cardValue);
    }
       
    if (player->get_points() == 21)
    {
        gameResult->SetLabel("Natural Blackjack!\nCongratulations!");
        player->add_match(1);
        PlayAgainOrReturn();
    }
}

void Mainframe::OnDrawCard(wxCommandEvent& evt)
{
    int cardValue{};
    if(player->get_points() != 21)
    { 
        player->set_card(deck.draw_card());
    }
    else
    {
        player->get_total_points();
        if (player->get_points() > 21)
        {
            DealersTurn();
        }
    }
    
    if (player->get_hand().back() % 13 == 0)
    {
        cardValue = 11;
    }
    else
    {
        cardValue = std::min(((player->get_hand().back() % 13) + 1), 10);
    }

    if (player->get_points() < 21)
    {
        player->add_points(cardValue);
    }
    else if (player->get_total_points() < 21) {
        player->get_total_points();
    }

    wxBitmap cardBitmap = cards.at(player->get_hand().back());
    wxStaticBitmap* cardImage = new wxStaticBitmap(bottomGamePanel, wxID_ANY, cardBitmap);
    bottomSizer->Insert(player->get_hand().size(), cardImage, 0, wxALIGN_CENTER | wxALL, 5);
    bottomGamePanel->SetSizerAndFit(bottomSizer);

    std::string playerPointsString = "You: " + std::to_string(player->get_points());
    playerPoints->SetLabel(playerPointsString);

    gameSizer->Layout();
    notebook->Update();
    if (player->get_points() > 21) {
        player->get_total_points();
        if (player->get_points() > 21)
        {
            gameResult->SetLabel("You lost...");
            player->add_match(0);
            PlayAgainOrReturn();
        }
        else
        {
            std::string playerPointsString = "You: " + std::to_string(player->get_points());
            playerPoints->SetLabel(playerPointsString);
        }
    }
    else if (player->get_points() == 21) 
    {
        RemoveBackCardAndEnterDealersTurn();
    }
}

void Mainframe::PlayAgainOrReturn()
{
    backToStartGame->Show(true);
    backToStartGame->Bind(wxEVT_BUTTON, &Mainframe::ReloadGame, this);

    drawButton->Show(false);
    stopButton->Show(false);

    gameSizer->Layout();
    notebook->Update();
}

void Mainframe::ReloadGame(wxCommandEvent& evt)
{
    ShowBeginGamePanel();
}

void Mainframe::DrawPlayerCards()
{
    bottomSizer->AddStretchSpacer(1);
    int i{ 0 };
    for (const auto& card : player->get_hand())
    {
        wxBitmap cardBitmap = cards.at(card);
        wxStaticBitmap* cardImage = new wxStaticBitmap(bottomGamePanel, wxID_ANY, cardBitmap);

        bottomSizer->Add(cardImage, 0, wxALIGN_CENTER | wxALL, 5);
        i++;
    }
    bottomSizer->AddStretchSpacer(1);
    bottomGamePanel->SetSizerAndFit(bottomSizer);
}

void Mainframe::DrawDealerCards(bool showOneCardOnly)
{
    topSizer->AddStretchSpacer(1);

    if (showOneCardOnly)
    {
        wxBitmap dealerCardBitmap = cards.at(dealer->get_hand().at(0));
        wxBitmap holeCardBitmap = cards.at(52);

        wxStaticBitmap* dealerCardImage = new wxStaticBitmap(topGamePanel, wxID_ANY, dealerCardBitmap);
        wxStaticBitmap* holeCardImage = new wxStaticBitmap(topGamePanel, wxID_ANY, holeCardBitmap);

        topSizer->Add(dealerCardImage, 0, wxALIGN_CENTRE | wxALL, 5);
        topSizer->Add(holeCardImage, 0, wxALIGN_CENTER | wxALL, 5);
        topSizer->AddStretchSpacer(1);
        topGamePanel->SetSizerAndFit(topSizer);

        return;
    }

    for (const auto& card : dealer->get_hand())
    {
        wxBitmap cardBitmap = cards.at(card);
        wxStaticBitmap* cardImage = new wxStaticBitmap(topGamePanel, wxID_ANY, cardBitmap);

        topSizer->Add(cardImage, 0, wxALIGN_CENTER | wxALL, 5);
        topGamePanel->SetSizerAndFit(topSizer);
    }
}

std::string Mainframe::GetAccountDetails()
{
    std::string accountDetails = "Account Details\nUsername: " + username + "\nBalance: " + std::to_string(loggedInAccount->check_balance())
        + "\nWin percentage: " + std::to_string(loggedInAccount->get_win_percentage());
    return accountDetails;
}

void Mainframe::DepositMoney(wxCommandEvent& evt)
{
    depositSlider = new wxSlider(gameOptionsPanel, wxID_ANY, 100, 100, 10000, wxPoint(500, 275), wxSize(200, -1), wxSL_VALUE_LABEL);

    depositEnterButton = new wxButton(gameOptionsPanel, wxID_ANY, "OK", wxPoint(570, 315));

    depositEnterButton->Bind(wxEVT_BUTTON, &Mainframe::OnDepositEntered, this);
}

void Mainframe::OnDepositEntered(wxCommandEvent& evt)
{
    long value = depositSlider->GetValue();
    loggedInAccount->deposit(value);

    depositEnterButton->Destroy();
    depositSlider->Destroy();

    UpdateAcoountInfo();
    accountDetailsText->SetLabel(GetAccountDetails());
}

void Mainframe::WithdrawMoney(wxCommandEvent& evt)
{
    if (loggedInAccount->check_balance() == 0) {
        wxMessageBox("You don't have any money to make a withdrawal", "Insufficient funds");
        return;
    }

    withdrawSlider = new wxSlider(gameOptionsPanel, wxID_ANY, 0, 0, loggedInAccount->check_balance(), wxPoint(500, 350), wxSize(200, -1), wxSL_VALUE_LABEL);

    withdrawEnterButton = new wxButton(gameOptionsPanel, wxID_ANY, "OK", wxPoint(570, 390));

    withdrawEnterButton->Bind(wxEVT_BUTTON, &Mainframe::OnWithdrawEntered, this);
}

void Mainframe::OnWithdrawEntered(wxCommandEvent& evt)
{
    long value = withdrawSlider->GetValue();
    loggedInAccount->withdraw(value);

    withdrawEnterButton->Destroy();
    withdrawSlider->Destroy();

    UpdateAcoountInfo();
    accountDetailsText->SetLabel(GetAccountDetails());
}

bool Mainframe::VerifyAccountDetails()
{
    std::ifstream in;
    in.open("accounts.txt");

    if (!in) {
        wxMessageBox(wxT("Failled to open the accounts database."), wxT("Database fail"), wxICON_INFORMATION);
    }

    username = usernameBox->GetValue().ToStdString();
    password = passwordBox->GetValue().ToStdString();

    std::string  existing_name{}, existing_username{}, existing_email{}, existing_balance{}, existing_won{}, existing_played{}, existing_password{};

    int no_attempts{ 3 };

    while (!in.eof()) {
        std::getline(in, existing_name, ' ');
        std::getline(in, existing_username, ' ');
        std::getline(in, existing_email, ' ');
        std::getline(in, existing_balance, ' ');
        std::getline(in, existing_won, ' ');
        std::getline(in, existing_played, ' ');
        std::getline(in, existing_password);

        while (username == existing_username && password != existing_password && no_attempts != 0) {
            in.close();
            return false;
        }

        if (username == existing_username && password == existing_password) {
            wxMessageBox(wxT("Logged in successfully!"), wxT("Success"), wxICON_INFORMATION);
            in.close();
            loggedInAccount = new Account(existing_name, existing_username, existing_email, existing_password,
                std::stoi(existing_balance), std::stoi(existing_won), std::stoi(existing_played));
            player = new Player(*loggedInAccount);
            return true;
        }
    }

    in.close();
    return false;
}

void Mainframe::UpdateAcoountInfo()
{
    loggedInAccount->delete_from_database();
    loggedInAccount->add_to_database();
}