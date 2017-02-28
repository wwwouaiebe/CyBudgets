/* ---------------------------------------------------------------------------- */
//! CyWxUserPreferencesDialog.cpp
/* ---------------------------------------------------------------------------- */
//!
//! \file CyWxUserPreferencesDialog.cpp
//! \brief definition file for class CyWxUserPreferencesDialog
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

#include "UserInterfaceLayer/CyWxUserPreferencesDialog.h"
#include "DataLayer/CySqliteDb.h"
#include "DataLayer/CyUserPreferences.h"
#include "UtilitiesLayer/CyEnum.h"
#include "UtilitiesLayer/CyGetText.h"

/* ---------------------------------------------------------------------------- */

CyWxUserPreferencesDialog::CyWxUserPreferencesDialog ( wxWindow* pParent, const wxString& strTitle ) :
	wxDialog  (
		pParent,
		wxID_ANY,
		strTitle,
		::wxGetMousePosition ( ),
		wxSize ( kDialogWidth, kDialogHeight ),
		wxRESIZE_BORDER | wxCAPTION | wxMAXIMIZE_BOX | wxCLOSE_BOX | wxCAPTION  )
{
	// The main sizer is created
	wxBoxSizer* pMainSizer = new wxBoxSizer ( wxVERTICAL );

	// The notebook is created
	wxBoxSizer* pNotebookSizer = new wxBoxSizer ( wxVERTICAL );
	this->m_pNotebook = new wxNotebook ( this, CyWxUserPreferencesDialog::kNotebook );

	// The General panel is created
	this->m_pGeneralUserPreferencesPanel = new CyWxGeneralUserPreferencesPanel (
		this->m_pNotebook, 
		CyWxUserPreferencesDialog::kGeneralUserPreferencesPanel,
		wxDefaultPosition,
		wxSize ( CyWxUserPreferencesDialog::kPanelWidth, CyWxUserPreferencesDialog::kPanelHeight ),
		wxTAB_TRAVERSAL,
		"GeneralUserPreference");

	this->m_pNotebook->AddPage ( this->m_pGeneralUserPreferencesPanel, CyGetText::getInstance ( ).getText ( "CyWxUserPreferencesDialog.CyWxUserPreferencesDialog.GeneralUserPreferenceTitle" ) );

	//The Display panel is created
	this->m_pDisplayUserPreferencesPanel = new CyWxDisplayUserPreferencesPanel (
		this->m_pNotebook, 
		CyWxUserPreferencesDialog::kDisplayUserPreferencesPanel,
		wxDefaultPosition,
		wxSize ( CyWxUserPreferencesDialog::kPanelWidth, CyWxUserPreferencesDialog::kPanelHeight ),
		wxTAB_TRAVERSAL,
		"DisplayUserPreference");

	this->m_pNotebook->AddPage ( this->m_pDisplayUserPreferencesPanel, CyGetText::getInstance ( ).getText ( "CyWxUserPreferencesDialog.CyWxUserPreferencesDialog.DisplayUserPreferenceTitle" ) );

	// The database panel is created
	this->m_pDatabaseUserPreferencesPanel = new CyWxDatabaseUserPreferencesPanel (
		this->m_pNotebook, 
		CyWxUserPreferencesDialog::kDatabaseUserPreferencesPanel,
		wxDefaultPosition,
		wxSize ( CyWxUserPreferencesDialog::kPanelWidth, CyWxUserPreferencesDialog::kPanelHeight ),
		wxTAB_TRAVERSAL,
		"DatabaseUserPreference");

	this->m_pNotebook->AddPage ( this->m_pDatabaseUserPreferencesPanel, CyGetText::getInstance ( ).getText ( "CyWxUserPreferencesDialog.CyWxUserPreferencesDialog.DatabaseUserPreferenceTitle" ) );

	pMainSizer->Add ( pNotebookSizer, 0, wxEXPAND | wxALL, CyEnum::kMarginSize );
	pMainSizer->AddSpacer ( CyEnum::kMarginSize );

	pNotebookSizer->Add ( this->m_pNotebook );

	// and a button sizer is added
	wxBoxSizer* pButtonSizer = new wxStaticBoxSizer ( wxHORIZONTAL, this, wxEmptyString );
	pButtonSizer->Add ( this->CreateButtonSizer ( wxOK | wxCANCEL ) );
	pMainSizer->Add ( pButtonSizer, 0, wxEXPAND | wxALL, CyEnum::kMarginSize );

	// the sizer is added to the dialog
	this->SetSizer ( pMainSizer );

	// and the dialog is reorganized and centered
	this->Fit ( );
	this->Centre ( );
}

/* ---------------------------------------------------------------------------- */

CyWxUserPreferencesDialog::~CyWxUserPreferencesDialog ( )
{
}

/* ---------------------------------------------------------------------------- */

int CyWxUserPreferencesDialog::ShowModal ( )
{
	int iReturnCode =  wxDialog::ShowModal ( );

	if ( wxID_OK == iReturnCode )
	{
		// the database is updated with values from the database panel
		if ( CySqliteDb::getInstance ( ).IsInitialized ( ) )
		{
			CyUserPreferences::m_objUserPreferences.m_lCurrencyDecimalPrecision = this->m_pDatabaseUserPreferencesPanel->m_pDbCurrencyDecimalPrecisionSpinCtrl->GetValue ( );
			CyUserPreferences::m_objUserPreferences.m_strCurrencySymbol = this->m_pDatabaseUserPreferencesPanel->m_pDbCurrencySymbolCtrl->GetValue ( );
		}

		CyUserPreferences::m_objUserPreferences.m_strCurrencyPositiveSymbol = this->m_pDisplayUserPreferencesPanel->m_pCurrencyPositiveSymbolCtrl->GetValue ( );

		CyUserPreferences::m_objUserPreferences.m_strCurrencyNegativeSymbol = this->m_pDisplayUserPreferencesPanel->m_pCurrencyNegativeSymbolCtrl->GetValue ( );

		CyUserPreferences::m_objUserPreferences.m_strCurrencyPositiveColor =
			static_cast < wchar_t > ( CyForegroundBlue + this->m_pDisplayUserPreferencesPanel->m_pCurrencyPositiveColorComboBox->GetCurrentSelection ( ) );

		CyUserPreferences::m_objUserPreferences.m_strCurrencyNegativeColor =
			static_cast < wchar_t > ( CyForegroundBlue + this->m_pDisplayUserPreferencesPanel->m_pCurrencyNegativeColorComboBox->GetCurrentSelection ( ) );

		CyUserPreferences::m_objUserPreferences.m_strDecimalSeparator = this->m_pDisplayUserPreferencesPanel->m_pDecimalSeparatorCtrl->GetValue ( );

		CyUserPreferences::m_objUserPreferences.m_strThousandSeparator = this->m_pDisplayUserPreferencesPanel->m_pThousandSeparatorCtrl->GetValue ( );

		CyUserPreferences::m_objUserPreferences.m_lGrouping = this->m_pDisplayUserPreferencesPanel->m_pGroupingSpinCtrl->GetValue ( );

		CyUserPreferences::m_objUserPreferences.m_bCurrencySymbolBefore =
			CyEnum::kYes == this->m_pDisplayUserPreferencesPanel->m_pCurrencySymbolPositionComboBox->GetCurrentSelection ( );

		CyUserPreferences::m_objUserPreferences.m_strBooleanTrueSymbol = this->m_pDisplayUserPreferencesPanel->m_pBooleanTrueSymbolCtrl->GetValue ( );

		CyUserPreferences::m_objUserPreferences.m_strBooleanFalseSymbol = this->m_pDisplayUserPreferencesPanel->m_pBooleanFalseSymbolCtrl->GetValue ( );

		CyUserPreferences::m_objUserPreferences.m_strUserLanguage = this->m_pGeneralUserPreferencesPanel->m_pUserLanguageComboBox->GetValue ( );

		CyUserPreferences::m_objUserPreferences.save ( );
	}

	return iReturnCode;
}

/* ---------------------------------------------------------------------------- */