/* ---------------------------------------------------------------------------- */
//! CyWxGeneralUserPreferencesPanel.cpp
/* ---------------------------------------------------------------------------- */
//!
//! \file CyWxDisplayUserPreferencesPanel.cpp
//! \brief definition file for class CyWxGeneralUserPreferencesPanel
//!
/* ----------------------------------------------------------------------------

	contact: http://www.ouaie.be/

    This file is a part of the CyBudgets program

    Copyright ( C ) 2014 - Christian Guyette

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program. If not, see <http://www.gnu.org/licenses/>.

     ---------------------------------------------------------------------------- */

// Line added to force Visual Studio to save as UTF-8 ŉŋ

/* ---------------------------------------------------------------------------- */

#include "UserInterfaceLayer/CyWxDisplayUserPreferencesPanel.h"
#include "DataLayer/CyUserPreferences.h"
#include "UtilitiesLayer/CyGetText.h"
#include "UtilitiesLayer/CyEnum.h"

/* ---------------------------------------------------------------------------- */

CyWxDisplayUserPreferencesPanel::CyWxDisplayUserPreferencesPanel ( wxWindow* pParent, int id, const wxPoint& pos, const wxSize& size, long style, const wxString& name) :
	wxPanel ( pParent, id, pos, size, style, name )
{
	// The main sizer is created
	wxBoxSizer* pMainSizer = new wxBoxSizer ( wxVERTICAL );

	// Boolean...

	wxBoxSizer* pMainBooleanSizer = new wxStaticBoxSizer (
		wxVERTICAL,
		this,
		CyGetText::getInstance ( ).getText ( "CyWxDisplayUserPreferencesPanel.CyWxDisplayUserPreferencesPanel.BooleanValues" ) );

	wxGridBagSizer* pGridBagBooleanSizer = new wxGridBagSizer ( CyEnum::kMarginSize, CyEnum::kMarginSize );

	// True symbol
	this->m_strBooleanTrueSymbol = CyUserPreferences::getInstance ( ).getBooleanTrueSymbol ( );

	wxStaticText* pBooleanTrueSymbolText = new wxStaticText (
		this,
		wxID_ANY,
		CyGetText::getInstance ( ).getText ( "CyWxDisplayUserPreferencesPanel.CyWxDisplayUserPreferencesPanel.BooleanTrueSymbol" ),
		wxDefaultPosition,
		wxSize ( kTextGridWidth, kTextGridHeight ),
		wxALIGN_BOTTOM | wxALIGN_RIGHT );
	pGridBagBooleanSizer->Add ( pBooleanTrueSymbolText ,  wxGBPosition ( 0, 0 ) );

	this->m_pBooleanTrueSymbolCtrl = new wxTextCtrl ( 
		this,
		CyWxDisplayUserPreferencesPanel::kBooleanTrue,
		this->m_strBooleanTrueSymbol,
		wxDefaultPosition,
		wxSize ( kControlGridWidth, kControlGridHeight ) );
	pGridBagBooleanSizer->Add ( this->m_pBooleanTrueSymbolCtrl, wxGBPosition ( 0, 1 ) );

	// False symbol
	this->m_strBooleanFalseSymbol = CyUserPreferences::getInstance ( ).getBooleanFalseSymbol ( );

	wxStaticText* pBooleanFalseSymbolText = new wxStaticText (
		this,
		wxID_ANY,
		CyGetText::getInstance ( ).getText ( "CyWxDisplayUserPreferencesPanel.CyWxDisplayUserPreferencesPanel.BooleanFalseSymbol" ),
		wxDefaultPosition,
		wxSize ( kTextGridWidth, kTextGridHeight ),
		wxALIGN_BOTTOM | wxALIGN_RIGHT );
	pGridBagBooleanSizer->Add ( pBooleanFalseSymbolText ,  wxGBPosition ( 1, 0 ) );

	this->m_pBooleanFalseSymbolCtrl = new wxTextCtrl ( 
		this,
		CyWxDisplayUserPreferencesPanel::kBooleanFalse,
		this->m_strBooleanFalseSymbol,
		wxDefaultPosition,
		wxSize ( kControlGridWidth, kControlGridHeight ) );
	pGridBagBooleanSizer->Add ( this->m_pBooleanFalseSymbolCtrl, wxGBPosition ( 1, 1 ) );

	pMainBooleanSizer->Add ( pGridBagBooleanSizer, 0, wxEXPAND | wxALL, CyEnum::kMarginSize );

	pMainSizer->Add ( pMainBooleanSizer, 0, wxEXPAND | wxALL, CyEnum::kMarginSize );

	// Currency...

	wxBoxSizer* pMainMoneySizer = new wxStaticBoxSizer (
		wxVERTICAL,
		this,
		CyGetText::getInstance ( ).getText ( "CyWxDisplayUserPreferencesPanel.CyWxDisplayUserPreferencesPanel.MoneyValues" ) );

	wxGridBagSizer* pGridBagMoneySizer = new wxGridBagSizer ( CyEnum::kMarginSize, CyEnum::kMarginSize );

	// Currency positive symbol
	this->m_strCurrencyPositiveSymbol = CyUserPreferences::getInstance ( ).getCurrencyPositiveSymbol ( );

	wxStaticText* pCurrencyPositiveText = new wxStaticText (
		this,
		wxID_ANY,
		CyGetText::getInstance ( ).getText ( "CyWxDisplayUserPreferencesPanel.CyWxDisplayUserPreferencesPanel.CurrencyPositiveSymbol" ),
		wxDefaultPosition,
		wxSize ( kTextGridWidth, kTextGridHeight ),
		wxALIGN_BOTTOM | wxALIGN_RIGHT );
	pGridBagMoneySizer->Add ( pCurrencyPositiveText ,  wxGBPosition ( 0, 0 ) );

	this->m_pCurrencyPositiveSymbolCtrl = new wxTextCtrl ( 
		this,
		CyWxDisplayUserPreferencesPanel::kCurrencyPositiveSymbol,
		this->m_strCurrencyPositiveSymbol,
		wxDefaultPosition,
		wxSize ( kControlGridWidth, kControlGridHeight ) );
	pGridBagMoneySizer->Add ( this->m_pCurrencyPositiveSymbolCtrl, wxGBPosition ( 0, 1 ) );

	// Currency positive color
	this->m_strCurrencyPositiveColor = CyUserPreferences::getInstance ( ).getCurrencyPositiveColor ( );
	wxArrayString strCurrencyColorsArray;
	strCurrencyColorsArray.Add ( CyGetText::getInstance ( ).getText ( "CyWxDisplayUserPreferencesPanel.CyWxDisplayUserPreferencesPanel.ForegroundBlue" ) );
	strCurrencyColorsArray.Add ( CyGetText::getInstance ( ).getText ( "CyWxDisplayUserPreferencesPanel.CyWxDisplayUserPreferencesPanel.ForegroundCyan" ) );
	strCurrencyColorsArray.Add ( CyGetText::getInstance ( ).getText ( "CyWxDisplayUserPreferencesPanel.CyWxDisplayUserPreferencesPanel.ForegroundGreen" ) );
	strCurrencyColorsArray.Add ( CyGetText::getInstance ( ).getText ( "CyWxDisplayUserPreferencesPanel.CyWxDisplayUserPreferencesPanel.ForegroundYellow" ) );
	strCurrencyColorsArray.Add ( CyGetText::getInstance ( ).getText ( "CyWxDisplayUserPreferencesPanel.CyWxDisplayUserPreferencesPanel.ForegroundRed" ) );
	strCurrencyColorsArray.Add ( CyGetText::getInstance ( ).getText ( "CyWxDisplayUserPreferencesPanel.CyWxDisplayUserPreferencesPanel.ForegroundBlack" ) );
	strCurrencyColorsArray.Add ( CyGetText::getInstance ( ).getText ( "CyWxDisplayUserPreferencesPanel.CyWxDisplayUserPreferencesPanel.ForegroundGrey" ) );
	strCurrencyColorsArray.Add ( CyGetText::getInstance ( ).getText ( "CyWxDisplayUserPreferencesPanel.CyWxDisplayUserPreferencesPanel.ForegroundWhite" ) );

	wxStaticText* pCurrencyPositiveColorText = new wxStaticText (
		this,
		wxID_ANY,
		CyGetText::getInstance ( ).getText ( "CyWxDisplayUserPreferencesPanel.CyWxDisplayUserPreferencesPanel.CurrencyPositiveColor" ),
		wxDefaultPosition,
		wxSize ( kTextGridWidth, kTextGridHeight ),
		wxALIGN_BOTTOM | wxALIGN_RIGHT );
	pGridBagMoneySizer->Add ( pCurrencyPositiveColorText ,  wxGBPosition ( 1, 0 ) );

	this->m_pCurrencyPositiveColorComboBox = new wxComboBox ( 
		this, 
		CyWxDisplayUserPreferencesPanel::kCurrencyPositiveColor,
		strCurrencyColorsArray [ static_cast < size_t > ( this->m_strCurrencyPositiveColor - CyForegroundBlue ) ],
		wxDefaultPosition,
		wxSize ( kControlGridWidth, kControlGridHeight ),
		strCurrencyColorsArray,
		wxCB_READONLY );
	pGridBagMoneySizer->Add ( this->m_pCurrencyPositiveColorComboBox, wxGBPosition ( 1, 1 ) );

	// Currency negative symbol
	this->m_strCurrencyNegativeSymbol = CyUserPreferences::getInstance ( ).getCurrencyNegativeSymbol ( );
	
	wxStaticText* pCurrencyNegativeSymbolText = new wxStaticText (
		this,
		wxID_ANY,
		CyGetText::getInstance ( ).getText ( "CyWxDisplayUserPreferencesPanel.CyWxDisplayUserPreferencesPanel.CurrencyNegativeSymbol" ),
		wxDefaultPosition,
		wxSize ( kTextGridWidth, kTextGridHeight ),
		wxALIGN_BOTTOM | wxALIGN_RIGHT );
	pGridBagMoneySizer->Add ( pCurrencyNegativeSymbolText ,  wxGBPosition ( 2, 0 ) );

	this->m_pCurrencyNegativeSymbolCtrl = new wxTextCtrl ( 
		this,
		CyWxDisplayUserPreferencesPanel::kCurrencyNegativeSymbol,
		this->m_strCurrencyNegativeSymbol,
		wxDefaultPosition,
		wxSize ( kControlGridWidth, kControlGridHeight ) );
	pGridBagMoneySizer->Add ( this->m_pCurrencyNegativeSymbolCtrl, wxGBPosition ( 2, 1 ) );

	// Currency negative color
	this->m_strCurrencyNegativeColor = CyUserPreferences::getInstance ( ).getCurrencyNegativeColor ( );

	wxStaticText* pCurrencyNegativeColorText = new wxStaticText (
		this,
		wxID_ANY,
		CyGetText::getInstance ( ).getText ( "CyWxDisplayUserPreferencesPanel.CyWxDisplayUserPreferencesPanel.CurrencyNegativeColor" ),
		wxDefaultPosition,
		wxSize ( kTextGridWidth, kTextGridHeight ),
		wxALIGN_BOTTOM | wxALIGN_RIGHT );
	pGridBagMoneySizer->Add ( pCurrencyNegativeColorText ,  wxGBPosition ( 3, 0 ) );

	this->m_pCurrencyNegativeColorComboBox = new wxComboBox ( 
		this, 
		CyWxDisplayUserPreferencesPanel::kCurrencyNegativeColor,
		strCurrencyColorsArray [ static_cast < size_t > ( this->m_strCurrencyNegativeColor - CyForegroundBlue ) ],
		wxDefaultPosition,
		wxSize ( kControlGridWidth, kControlGridHeight ),
		strCurrencyColorsArray,
		wxCB_READONLY );
	pGridBagMoneySizer->Add ( this->m_pCurrencyNegativeColorComboBox, wxGBPosition ( 3, 1 ) );

	// Currency symbol position
	this->m_bCurrencySymbolBefore = CyUserPreferences::getInstance ( ).isCurrencySymbolBefore ( );

	wxArrayString strCurrencySymbolPositionArray;
	strCurrencySymbolPositionArray.Add ( CyGetText::getInstance ( ).getText ( "CyWxDatabaseUserPreferencesPanel.CyWxDatabaseUserPreferencesPanel.CurrencySymbolAfter" ) );
	strCurrencySymbolPositionArray.Add ( CyGetText::getInstance ( ).getText ( "CyWxDatabaseUserPreferencesPanel.CyWxDatabaseUserPreferencesPanel.CurrencySymbolBefore" ) );

	wxStaticText* pCurrencySymbolPositionText = new wxStaticText (
		this,
		wxID_ANY,
		CyGetText::getInstance ( ).getText ( "CyWxDatabaseUserPreferencesPanel.CyWxDatabaseUserPreferencesPanel.CurrencySymbolPosition" ),
		wxDefaultPosition,
		wxSize ( kTextGridWidth, kTextGridHeight ),
		wxALIGN_BOTTOM | wxALIGN_RIGHT );
	pGridBagMoneySizer->Add ( pCurrencySymbolPositionText, wxGBPosition ( 4, 0 ) );

	this->m_pCurrencySymbolPositionComboBox = new wxComboBox (
		this,
		CyWxDisplayUserPreferencesPanel::kCurrencySymbolPosition,
		this->m_bCurrencySymbolBefore ? strCurrencySymbolPositionArray [ 1 ] : strCurrencySymbolPositionArray [ 0 ],
		wxDefaultPosition,
		wxSize ( kControlGridWidth, kControlGridHeight ),
		strCurrencySymbolPositionArray,
		wxCB_READONLY );
	pGridBagMoneySizer->Add ( this->m_pCurrencySymbolPositionComboBox, wxGBPosition ( 4, 1 ) );

	pMainMoneySizer->Add ( pGridBagMoneySizer, 0, wxEXPAND | wxALL, CyEnum::kMarginSize );

	pMainSizer->Add ( pMainMoneySizer, 0, wxEXPAND | wxALL, CyEnum::kMarginSize );

	// Numbers...

	wxBoxSizer* pMainNumberSizer = new wxStaticBoxSizer (
		wxVERTICAL,
		this,
		CyGetText::getInstance ( ).getText ( "CyWxDisplayUserPreferencesPanel.CyWxDisplayUserPreferencesPanel.NumberValues" ) );

	wxGridBagSizer* pGridBagNumberSizer = new wxGridBagSizer ( CyEnum::kMarginSize, CyEnum::kMarginSize );

	// Decimal separator
	this->m_strDecimalSeparator = CyUserPreferences::getInstance ( ).getDecimalSeparator ( );

	wxStaticText* pDecimalSeparatorText = new wxStaticText (
		this,
		wxID_ANY,
		CyGetText::getInstance ( ).getText ( "CyWxDisplayUserPreferencesPanel.CyWxDisplayUserPreferencesPanel.DecimalSeparator" ),
		wxDefaultPosition,
		wxSize ( kTextGridWidth, kTextGridHeight ),
		wxALIGN_BOTTOM | wxALIGN_RIGHT );
	pGridBagNumberSizer->Add ( pDecimalSeparatorText ,  wxGBPosition ( 0, 0 ) );

	this->m_pDecimalSeparatorCtrl = new wxTextCtrl ( 
		this,
		CyWxDisplayUserPreferencesPanel::kDecimalSeparator,
		this->m_strDecimalSeparator,
		wxDefaultPosition,
		wxSize ( kControlGridWidth, kControlGridHeight ) );
	pGridBagNumberSizer->Add ( this->m_pDecimalSeparatorCtrl, wxGBPosition ( 0, 1 ) );

	// Thousand separator
	this->m_strThousandSeparator = CyUserPreferences::getInstance ( ).getThousandSeparator ( );

	wxStaticText* pThousandSeparatorText = new wxStaticText (
		this,
		wxID_ANY,
		CyGetText::getInstance ( ).getText ( "CyWxDisplayUserPreferencesPanel.CyWxDisplayUserPreferencesPanel.ThousandSeparator" ),
		wxDefaultPosition,
		wxSize ( kTextGridWidth, kTextGridHeight ),
		wxALIGN_BOTTOM | wxALIGN_RIGHT );
	pGridBagNumberSizer->Add ( pThousandSeparatorText ,  wxGBPosition ( 1, 0 ) );

	this->m_pThousandSeparatorCtrl = new wxTextCtrl ( 
		this,
		CyWxDisplayUserPreferencesPanel::kThousandSeparator,
		this->m_strThousandSeparator,
		wxDefaultPosition,
		wxSize ( kControlGridWidth, kControlGridHeight ) );
	pGridBagNumberSizer->Add ( this->m_pThousandSeparatorCtrl, wxGBPosition ( 1, 1 ) );

	// Grouping
	this->m_lGrouping = CyUserPreferences::getInstance ( ).getGrouping ( );

	wxStaticText* pGroupingText = new wxStaticText (
		this,
		wxID_ANY,
		CyGetText::getInstance ( ).getText ( "CyWxDisplayUserPreferencesPanel.CyWxDisplayUserPreferencesPanel.Grouping" ),
		wxDefaultPosition,
		wxSize ( kTextGridWidth, kTextGridHeight ),
		wxALIGN_BOTTOM | wxALIGN_RIGHT );
	pGridBagNumberSizer->Add ( pGroupingText ,  wxGBPosition ( 2, 0 ) );

	this->m_pGroupingSpinCtrl = new wxSpinCtrl (
		this,
		CyWxDisplayUserPreferencesPanel::kGrouping,
		wxEmptyString,
		wxDefaultPosition,
		wxSize ( kSpinControlGridWidth, kControlGridHeight ),
		wxSP_ARROW_KEYS,
		0,
		6,
		static_cast < int > ( this->m_lGrouping ) );
	pGridBagNumberSizer->Add ( this->m_pGroupingSpinCtrl, wxGBPosition ( 2, 1 ) );

	pMainNumberSizer->Add ( pGridBagNumberSizer, 0, wxEXPAND | wxALL, CyEnum::kMarginSize );

	pMainSizer->Add ( pMainNumberSizer, 0, wxEXPAND | wxALL, CyEnum::kMarginSize );

	this->SetSizer ( pMainSizer );
	this->Layout ( );
}

/* ---------------------------------------------------------------------------- */

CyWxDisplayUserPreferencesPanel::~CyWxDisplayUserPreferencesPanel ( )
{
}

/* ---------------------------------------------------------------------------- */
