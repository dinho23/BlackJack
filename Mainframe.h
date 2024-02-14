#pragma once
#include <wx/wx.h>
#include <wx/simplebook.h>
#include <string>
#include <thread>
#include "Account.h"
#include "Player.h"
#include "Dealer.h"
#include "Deck.h"
#include "DatabaseManager.h"

class Mainframe : public wxFrame
{
public:
	Mainframe(const wxString& title);

private:
	Account* loggedInAccount;
	Player* player;
	Dealer* dealer;
	Deck deck;
	DatabaseManager* db;

	wxSimplebook* notebook;

	wxBoxSizer* gameSizer;
	wxSizer* topSizer;
	wxSizer* middleSizer;
	wxSizer* bottomSizer;

	std::vector<wxBitmap> cards;

	wxPanel* dealerPanel;
	wxPanel* playerPanel;

	wxPanel* firstPanel;
	wxPanel* loginPanel;
	wxPanel* createAccountPanel;
	wxPanel* credentialsPanel;
	wxPanel* gameOptionsPanel;

	wxPanel* wholeGamePanel;
	wxPanel* topGamePanel;
	wxPanel* middleGamePanel;
	wxPanel* bottomGamePanel;

	wxButton* playButton;
	wxButton* quitButton;
	wxButton* loginButton;
	wxButton* backButton;
	wxButton* enterCredentials;
	wxButton* createAccount;
	wxButton* newAccountButton;
	wxButton* drawButton;
	wxButton* stopButton;
	wxButton* backToStartGame;

	wxTextCtrl* usernameBox;
	wxTextCtrl* passwordBox;
	wxTextCtrl* firstNameBox;
	wxTextCtrl* emailBox;

	wxSlider* betSlider;
	wxSlider* depositSlider;
	wxSlider* withdrawSlider;
	wxButton* betButton;
	wxButton* withdrawEnterButton;
	wxButton* depositEnterButton;

	wxStaticText* accountDetailsText;
	wxStaticText* playerPoints;
	wxStaticText* dealerPoints;
	wxStaticText* gameResult;

	std::string username;
	std::string firstName;
	std::string email;
	std::string password;
	int ammountBet;

	void AddSizerToPanel(wxPanel* frame, std::vector<wxControl*> controls);

	void OnQuitPressed(wxCommandEvent& evt);
	void OnPlayPressed(wxCommandEvent& evt);
	void OnLoginPressed(wxCommandEvent& evt);
	void OnCreateAccountPressed(wxCommandEvent& evt);
	void OnBackPressed(wxCommandEvent& evt);
	void OnCredentialsEntered(wxCommandEvent& evt);
	void OnDrawCard(wxCommandEvent& evt);

	void DepositMoney(wxCommandEvent& evt);
	void OnDepositEntered(wxCommandEvent& evt);
	void WithdrawMoney(wxCommandEvent& evt);
	void OnWithdrawEntered(wxCommandEvent& evt);
	void ShowBettingOptions(wxCommandEvent& evt);
	void OnBeginGame(wxCommandEvent& evt);
	void OnStopEntered(wxCommandEvent& evt);

	void VerifyExistingAccount(wxCommandEvent& evt);
	void CreateAccount();

	bool ValidateEmail(const std::string& email);

	void CreateAccountDetailsPanel();
	bool VerifyAccountDetails();

	void ShowBeginGamePanel();

	std::string GetAccountDetails();

	void LoadImages();
	void PrintDealerPointsAndCards();

	void InitGame();
	void DrawPlayerCards();
	void DrawDealerCards(bool showOneCardOnly);
	void ReloadGame(wxCommandEvent& evt);
	void DealersTurn();
	void PlayAgainOrReturn();
	void RemoveBackCardAndEnterDealersTurn();
};