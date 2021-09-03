#pragma once
#include "Popup.h"
#include "Characters.h"
#include <iostream>
#include <wx/wx.h>


class Frame : public wxFrame
{
public:
    // Inputs
    wxCheckBox* cBoxes[3];
    wxTextCtrl* lengthInput;

    // For password
    Popup* popup = new Popup(); // Display
    std::string password; // Generate

    Frame();

    CHARACTERS CHARS;
    void GeneratePassword(wxCommandEvent&);

    void CopyPassword(wxCommandEvent&);
    void CopyText(std::string);
    void CopyError();

    // For password control
    int passwordLength = 0;
    int points[6] = { 0 };
    std::string uniques;

    int PasswordStrength();
    void FillPoints(int);
    int PointsLength();
    void AddPoint(int);
    void AddIfHaveOne(std::string, int);

protected:
    DECLARE_EVENT_TABLE();
    void OnClose(wxCloseEvent& evt);
};
