/* ---------------------------------------------------------------------------- */
//! CyWxGeneralUserPreferencesPanel.cpp
/* ---------------------------------------------------------------------------- */
//!
//! \file CyWxGeneralUserPreferencesPanel.cpp
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

#include "UserInterfaceLayer/CyWxGeneralUserPreferencesPanel.h"
#include "DataLayer/CyUserPreferences.h"
#include "UtilitiesLayer/CyFilesService.h"
#include "UtilitiesLayer/CyGetText.h"
#include "UtilitiesLayer/CyEnum.h"

/* ---------------------------------------------------------------------------- */

CyWxGeneralUserPreferencesPanel::CyWxGeneralUserPreferencesPanel ( wxWindow* pParent, int id, const wxPoint& pos, const wxSize& size, long style, const wxString& name) :
	wxPanel ( pParent, id, pos, size, style, name )
{
	// The main sizer is created
	wxBoxSizer* pMainSizer = new wxBoxSizer ( wxVERTICAL );

	wxBoxSizer* pMainLanguageSizer = new wxStaticBoxSizer (
		wxVERTICAL,
		this,
		CyGetText::getInstance ( ).getText ( "CyWxGeneralUserPreferencesPanel.CyWxGeneralUserPreferencesPanel.MainLanguage" ) );

	// a gridbag sizer is created...
	wxGridBagSizer* pUserLanguageSizer = new wxGridBagSizer ( CyEnum::kMarginSize, CyEnum::kMarginSize );

	this->m_strUserLanguage = CyUserPreferences::getInstance ( ).getUserLanguage ( );
	wxArrayString strLanguageFilesArray = CyFilesService::getInstance ( ).getMessagesFiles ( );

	wxStaticText* pUserLanguageText = new wxStaticText (
		this,
		wxID_ANY,
		CyGetText::getInstance ( ).getText ( "CyWxGeneralUserPreferencesPanel.CyWxGeneralUserPreferencesPanel.UserLanguage" ),
		wxDefaultPosition,
		wxSize ( kTextGridWidth, kTextGridHeight ),
		wxALIGN_BOTTOM | wxALIGN_RIGHT );
	pUserLanguageSizer->Add ( pUserLanguageText ,  wxGBPosition ( 0, 0 ) );

	this->m_pUserLanguageComboBox = new wxComboBox ( 
		this, 
		CyWxGeneralUserPreferencesPanel::kUserLanguage,
		m_strUserLanguage,
		wxDefaultPosition,
		wxSize ( kControlGridWidth, kControlGridHeight ),
		strLanguageFilesArray,
		wxCB_READONLY );
	pUserLanguageSizer->Add ( this->m_pUserLanguageComboBox, wxGBPosition ( 0, 1 ) );

	pMainLanguageSizer->Add ( pUserLanguageSizer, 0, wxEXPAND | wxALL, CyEnum::kMarginSize );

	pMainSizer->Add ( pMainLanguageSizer, 0, wxEXPAND | wxALL, CyEnum::kMarginSize );

	wxBoxSizer* pCheckBoxesSizer = new wxStaticBoxSizer (
		wxVERTICAL,
		this,
		CyGetText::getInstance ( ).getText ( "CyWxGeneralUserPreferencesPanel.CyWxGeneralUserPreferencesPanel.Others" ) );

	this->m_pReuseLastOpenedFileCheckbox = new wxCheckBox (
		this,
		CyWxGeneralUserPreferencesPanel::kReuseLastOpenedFile,
		CyGetText::getInstance ( ).getText ( "CyWxGeneralUserPreferencesPanel.CyWxGeneralUserPreferencesPanel.ReuseLastOpenedfile" ) );
	pCheckBoxesSizer->Add ( this->m_pReuseLastOpenedFileCheckbox );

	this->m_pReuseLastOpenedFileCheckbox->SetValue ( CyUserPreferences::getInstance ( ).getReuseLastFile ( ) );

	pCheckBoxesSizer->AddSpacer ( CyEnum::kMarginSize );

	this->m_pDeleteImportFileCheckBox = new wxCheckBox (
		this,
		CyWxGeneralUserPreferencesPanel::kDeleteImportFile,
		CyGetText::getInstance ( ).getText ( "CyWxGeneralUserPreferencesPanel.CyWxGeneralUserPreferencesPanel.DeleteImportFile" ) );

	this->m_pDeleteImportFileCheckBox->SetValue ( CyUserPreferences::getInstance ( ).getDeleteImportFile ( ) );

	pCheckBoxesSizer->Add ( this->m_pDeleteImportFileCheckBox );

	pCheckBoxesSizer->AddSpacer ( CyEnum::kMarginSize );

	pMainSizer->Add ( pCheckBoxesSizer, 0, wxEXPAND | wxALL, CyEnum::kMarginSize );

	// the sizer is added to the dialog
	this->SetSizer ( pMainSizer );
	this->Layout ( );
}

/* ---------------------------------------------------------------------------- */

CyWxGeneralUserPreferencesPanel::~CyWxGeneralUserPreferencesPanel ( )
{
}

/* ---------------------------------------------------------------------------- */
