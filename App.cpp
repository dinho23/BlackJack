#include "App.h"
#include "Mainframe.h"

wxIMPLEMENT_APP(App);

bool App::OnInit()
{
    Mainframe* mainFrame = new Mainframe("BlackJack");
    mainFrame->SetClientSize(800, 600);
    mainFrame->Center();
    mainFrame->Show();

    return true;
}
