#pragma once
#include <wx/wx.h>


// Popup to display a copyable password
class Popup : public wxFrame
{
public:
     wxTextCtrl* popupField;
     wxStaticText* passwordPowerText;
     wxButton* copyBtn;


    Popup()
        : wxFrame(nullptr, wxID_ANY, wxString("�ifreniz Olu�turuldu"), wxDefaultPosition, wxSize(300, 200))
    {
        int PADDING = 20;
        wxBoxSizer* popupSizer = new wxBoxSizer(wxVERTICAL);


        wxBoxSizer* textSizer  = new wxBoxSizer(wxHORIZONTAL);

        wxStaticText* popupText = new wxStaticText(this, wxID_ANY, wxString("�ifreniz:   "));
        textSizer->Add(popupText, 1, wxEXPAND | wxLEFT, PADDING);

        popupField = new wxTextCtrl(this, wxID_ANY);
        textSizer->Add(popupField, 1, wxRIGHT, PADDING);

        popupSizer->Add(textSizer, 1, wxEXPAND | wxTOP | wxLEFT | wxRIGHT, PADDING);


        // Text to show password power
        wxBoxSizer* passwordPowerSizer = new wxBoxSizer(wxHORIZONTAL);
        passwordPowerText = new wxStaticText(this, wxID_ANY, wxEmptyString);

        passwordPowerSizer->Add(passwordPowerText, 1, wxALL, PADDING);
        popupSizer->Add(passwordPowerSizer, 1, wxEXPAND | wxLEFT | wxRIGHT, PADDING);


        // Button to copy
        copyBtn = new wxButton(this, wxID_ANY, wxString("Kopyala"));
        popupSizer->Add(copyBtn, 1, wxEXPAND | wxBOTTOM | wxLEFT | wxRIGHT , PADDING);

        this->SetSizer(popupSizer);
    };

protected:
    DECLARE_EVENT_TABLE();
    void OnClose(wxCloseEvent& evt);
};
