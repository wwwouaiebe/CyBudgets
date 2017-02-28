/* ---------------------------------------------------------------------------- */
//! CyWxDatabaseUserPreferencesPanel.cpp
/* ---------------------------------------------------------------------------- */
//!
//! \file CyWxDatabaseUserPreferencesPanel.cpp
//! \brief definition file for class CyWxDatabaseUserPreferencesPanel
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

#include "UserInterfaceLayer/CyWxDatabaseUserPreferencesPanel.h"
#include "DataLayer/CyUserPreferences.h"
#include "DataLayer/CySqliteDb.h"
#include "UtilitiesLayer/CyGetText.h"
#include "UtilitiesLayer/CyEnum.h"

/* ---------------------------------------------------------------------------- */

CyWxDatabaseUserPreferencesPanel::CyWxDatabaseUserPreferencesPanel ( wxWindow* pParent, int id, const wxPoint& pos, const wxSize& size, long style, const wxString& name) :
	wxPanel ( pParent, id, pos, size, style, name )
{
	// The main sizer is created
	wxBoxSizer* pMainSizer = new wxBoxSizer ( wxVERTICAL );

	// Currency...

	if ( CySqliteDb::getInstance ( ).IsInitialized ( ) )
	{
		wxBoxSizer* pMainMoneySizer = new wxStaticBoxSizer (
			wxVERTICAL,
			this,
			CyGetText::getInstance ( ).getText ( "CyWxDatabaseUserPreferencesPanel.CyWxDatabaseUserPreferencesPanel.MoneyValues" ) );

		wxGridBagSizer* pGridBagMoneySizer = new wxGridBagSizer ( CyEnum::kMarginSize, CyEnum::kMarginSize );

		// Currency symbol
		this->m_strDbCurrencySymbol = CyUserPreferences::getInstance ( ).getCurrencySymbol ( );

		wxStaticText* pCurrencySymbolText = new wxStaticText (
			this,
			wxID_ANY,
			CyGetText::getInstance ( ).getText ( "CyWxDatabaseUserPreferencesPanel.CyWxDatabaseUserPreferencesPanel.CurrencySymbol" ),
			wxDefaultPosition,
			wxSize ( kTextGridWidth, kTextGridHeight ),
			wxALIGN_BOTTOM | wxALIGN_RIGHT );
		pGridBagMoneySizer->Add ( pCurrencySymbolText, wxGBPosition ( 0, 0 ) );

		this->m_pDbCurrencySymbolCtrl = new wxTextCtrl (
			this,
			CyWxDatabaseUserPreferencesPanel::kCurrencySymbol,
			this->m_strDbCurrencySymbol,
			wxDefaultPosition,
			wxSize ( kControlGridWidth, kControlGridHeight ) );
		pGridBagMoneySizer->Add ( this->m_pDbCurrencySymbolCtrl, wxGBPosition ( 0, 1 ) );

		// Decimal precision
		this->m_lDbCurrencyDecimalPrecision = CyUserPreferences::getInstance ( ).getCurrencyDecimalPrecision ( );

		wxStaticText* pCurrencyDecimalPrecisionText = new wxStaticText (
			this,
			wxID_ANY,
			CyGetText::getInstance ( ).getText ( "CyWxDatabaseUserPreferencesPanel.CyWxDatabaseUserPreferencesPanel.CurrencyDecimalPrecision" ),
			wxDefaultPosition,
			wxSize ( kTextGridWidth, kTextGridHeight ),
			wxALIGN_BOTTOM | wxALIGN_RIGHT );
		pGridBagMoneySizer->Add ( pCurrencyDecimalPrecisionText, wxGBPosition ( 1, 0 ) );

		this->m_pDbCurrencyDecimalPrecisionSpinCtrl = new wxSpinCtrl (
			this,
			CyWxDatabaseUserPreferencesPanel::kDbDecimalPrecistion,
			wxEmptyString,
			wxDefaultPosition,
			wxSize ( kSpinControlGridWidth, kControlGridHeight ),
			wxSP_ARROW_KEYS,
			0,
			6,
			static_cast <int> ( this->m_lDbCurrencyDecimalPrecision ) );
		pGridBagMoneySizer->Add ( this->m_pDbCurrencyDecimalPrecisionSpinCtrl, wxGBPosition ( 1, 1 ) );
		pMainMoneySizer->Add ( pGridBagMoneySizer, 0, wxEXPAND | wxALL, CyEnum::kMarginSize );
		pMainSizer->Add ( pMainMoneySizer, 0, wxEXPAND | wxALL, CyEnum::kMarginSize );
	}
	// Numbers...

	this->SetSizer ( pMainSizer );
	this->Layout ( );
}

/* ---------------------------------------------------------------------------- */

CyWxDatabaseUserPreferencesPanel::~CyWxDatabaseUserPreferencesPanel ( )
{
}

/* ---------------------------------------------------------------------------- */
