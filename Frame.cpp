#include "Frame.h" // Frame declaration

#include <iostream>     /* string, stoi, exception */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

#include <wx/wx.h>      /* wxWidgets */

#if defined(_WIN32) || defined(_WIN64)
static bool CAN_COPY = true;
#else
static bool CAN_COPY = false;
#endif


// --- Handle on close event ---
BEGIN_EVENT_TABLE(Frame, wxFrame)
EVT_CLOSE(Frame::OnClose)
END_EVENT_TABLE()

void Frame::OnClose(wxCloseEvent& evt)
{
    popup->Destroy();
    Destroy();
}

// --- GUI ---
Frame::Frame()
    : wxFrame(nullptr, wxID_ANY, "Hello World", wxDefaultPosition, wxSize(200, 100))
{

    if (CAN_COPY)
        popup->copyBtn->Bind(wxEVT_BUTTON, &Frame::CopyPassword, this); // Copy button binding

    // --- Padding and sizer ---
    const int P = 20;
    wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);


    // --- Length Input ---
    wxSizer* inputSizer = new wxBoxSizer(wxHORIZONTAL);

    wxStaticText* lengthText = new wxStaticText(this, wxID_ANY, wxString("Uzunluk:  ")); // Text
    inputSizer->Add(lengthText, 0);

    lengthInput = new wxTextCtrl(this, wxID_ANY); // Field
    inputSizer->Add(lengthInput, 1);

    sizer->Add(inputSizer, 1, wxEXPAND | wxLEFT | wxRIGHT | wxTOP, P);


    // --- Check boxes ---
    wxBoxSizer* cBoxSizer = new wxBoxSizer(wxHORIZONTAL);

    // Create boxes
    cBoxes[0] = new wxCheckBox(this, wxID_ANY, wxString("Harflerden çek"));
    cBoxes[1] = new wxCheckBox(this, wxID_ANY, wxString("Rakamlardan çek"));
    cBoxes[2] = new wxCheckBox(this, wxID_ANY, wxString("Özel karakterlerden çek"));

    // Add to sizers
    for (int i = 0; i < 3; i++)
        cBoxSizer->Add(cBoxes[i], 1);
    sizer->Add(cBoxSizer, 1, wxEXPAND | wxLEFT | wxRIGHT | wxTOP, P);


    // --- Button ---
    wxButton* submitBtn = new wxButton(this, wxID_ANY, wxString("Þifre Oluþtur"));
    submitBtn->Bind(wxEVT_BUTTON, &Frame::GeneratePassword, this);
    sizer->Add(submitBtn, 1, wxEXPAND | wxLEFT | wxRIGHT | wxTOP | wxBOTTOM, P);

    this->SetSizerAndFit(sizer);
}


// --- Generate password/contro the strength of it ---
void Frame::GeneratePassword(wxCommandEvent& evt)
{
    // Get length with error control
    try
    {
        passwordLength = std::stoi(lengthInput->GetValue().ToStdString());

        
        if (passwordLength < 1)
            throw std::exception();
    }
    catch(std::exception e)
    {
        wxMessageBox("Geçerli bir uzunluk giriniz.", "Hata", wxOK | wxICON_ERROR );
        return;
    }
    
    // Set characters to generate password with
    std::string chars;

    if (cBoxes[0]->GetValue())
        chars += CHARS.UPPERCASE + CHARS.LOWERCASE;

    if (cBoxes[1]->GetValue())
        chars += CHARS.DIGITS;

    if (cBoxes[2]->GetValue())
        chars += CHARS.SYMBOLS;

    // Control if there are no chars to pick randomly
    if (chars == "")
    {
        wxMessageBox("En az bir seçenek iþaretlenmelidir.", "Hata", wxOK | wxICON_ERROR);
        return;
    }

    
    // Generate the password
    password = ""; 
    srand(time(NULL)); // initiliaze a random seed to get unique numbers

    for (int i = 0; i < passwordLength; i++)
        password += chars[rand() % chars.length()];

    // Show the password
    std::string strength = std::to_string(PasswordStrength());

    popup->passwordPowerText->SetLabel(wxString("Þifre gücü: " + strength));
    popup->popupField->SetValue(wxString(password));
    popup->Show(true);
}
  
    
// --- Copying ---

void Frame::CopyError()
{
    wxMessageBox("Kopyalama iþlemi baþarýsýz,\n lütfen manuel olarak kopyalamayý deneyin.", "Hata", wxOK | wxICON_ERROR);
}

void Frame::CopyPassword(wxCommandEvent& evt)
{
    CopyText(password);
}


void Frame::CopyText(std::string text)
{
    if (!CAN_COPY)
    {
        wxMessageBox("Kopyalama iþlemi sadece Windows iþletim sistemlerinde yapýlabilir.", "Hata", wxOK | wxICON_ERROR);
        return;
    }
    

    if (!OpenClipboard(0))
        CopyError();
    else if (!EmptyClipboard())
        CopyError();
    else
    {
        HGLOBAL hg = GlobalAlloc(GMEM_MOVEABLE, text.size() + 1);
        if (!hg) {
            CopyError();
            return;
        }

        memcpy(GlobalLock(hg), text.c_str(), text.size() + 1);
        GlobalUnlock(hg);
        SetClipboardData(CF_TEXT, hg);
        CloseClipboard();
        GlobalFree(hg);

        wxMessageBox("Metin kopyalandý.", "Kopyalandý", wxOK | wxICON_INFORMATION);
    }
}