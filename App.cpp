#include "App.h"
#include "Frame.h"
#include <wx/wx.h>

wxIMPLEMENT_APP(App);

bool App::OnInit()
{
    Frame* frame = new Frame();
    frame->Show(true);
    return true;
}