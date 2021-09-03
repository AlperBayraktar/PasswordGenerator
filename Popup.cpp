#include "Popup.h"
#include <wx/wx.h>

// Close event
BEGIN_EVENT_TABLE(Popup, wxFrame)
EVT_CLOSE(Popup::OnClose)
END_EVENT_TABLE()

void Popup::OnClose(wxCloseEvent& event)
{
    popupField->SetValue(wxEmptyString);
    Show(false);
}
