/* ---------------------------------------------------------------------------- */
//! CyWxEditAccountDialog.cpp
/* ---------------------------------------------------------------------------- */
//!
//! \file CyWxEditAccountDialog.cpp
//! \brief definition file for class CyWxEditAccountDialog
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

#include "UserInterfaceLayer/CyWxEditAccountDialog.h"
#include "CoreLayer/CyCurrencyConverter.h"
#include "CoreLayer/CyAccountsSqlBuilder.h"
#include "DataLayer/CyLongValue.h"
#include "DataLayer/CyStringValue.h"
#include "DataLayer/CyUserPreferences.h"
#include "UtilitiesLayer/CyGetText.h"

/* ---------------------------------------------------------------------------- */


CyWxEditAccountDialog::CyWxEditAccountDialog ( CyQueryResult::CyQueryResultValuesRow& currentRow, wxWindow* pParent, const wxString& strTitle ) :
	wxDialog  (
		pParent,
		wxID_ANY,
		strTitle,
		::wxGetMousePosition ( ),
		wxSize ( kDialogWidth, kDialogHeight ),
		wxRESIZE_BORDER | wxCAPTION | wxMAXIMIZE_BOX | wxCLOSE_BOX | wxCAPTION  ),
		m_lAccountObjId ( CyEnum::kInvalidObjId ),
		m_lAccountCanBeImported ( CyEnum::kNo ),
		m_dAccountInitialAmount ( 0.0 ),
		m_currentRow ( currentRow )
{
	// The values to be displayed are searched in the currentRow variable
	this->m_lAccountObjId = m_currentRow.at ( CyAccountsSqlBuilder::kAccountObjId )->get ( CyLongValue::m_lDummyValue );
	this->m_strAccountNumber = m_currentRow.at ( CyAccountsSqlBuilder::kAccountNumber )->getAsString ( );
	this->m_strAccountOwner = m_currentRow.at ( CyAccountsSqlBuilder::kAccountOwner )->getAsString ( );
	this->m_lAccountCanBeImported = m_currentRow.at ( CyAccountsSqlBuilder::kAccountImported )->get ( CyLongValue::m_lDummyValue );
	wxString strAccountValidSinceDate = m_currentRow.at ( CyAccountsSqlBuilder::kAccountValidSinceDate )->getAsString ( );
	this->m_dAccountInitialAmount = CyCurrencyConverter::toDouble ( m_currentRow.at ( CyAccountsSqlBuilder::kAccountInitialAmount )->get ( CyLongValue::m_lDummyValue ) );

	// The main sizer is created
	wxBoxSizer* pMainSizer = new wxBoxSizer ( wxVERTICAL );

	// a secondary sizer is added for the data
	wxBoxSizer* pStaticBoxSizer = new wxStaticBoxSizer (
		wxVERTICAL,
		this,
		wxEmptyString );

	// a gridbag sizer is created...
	wxGridBagSizer* pAccountSizer = new wxGridBagSizer ( CyEnum::kMarginSize, CyEnum::kMarginSize );

	// and texts and control added....
	// ... for account number...
	wxStaticText* pAccountNumberText = new wxStaticText (
		this,
		wxID_ANY,
		CyGetText::getInstance ( ).getText ( "CyWxEditAccountDialog.CyWxEditAccountDialog.AccountNumber" ),
		wxDefaultPosition,
		wxSize ( kTextGridWidth, kTextGridHeight ),
		wxALIGN_BOTTOM | wxALIGN_RIGHT );
	pAccountSizer->Add ( pAccountNumberText ,  wxGBPosition ( 0, 0 ) );

	this->m_pAccountNumberCtrl = new wxTextCtrl ( 
		this, 
		CyWxEditAccountDialog::kAccountNumber,
		m_strAccountNumber,
		wxDefaultPosition,
		wxSize ( kControlGridWidth, kControlGridHeight ) );
	pAccountSizer->Add ( this->m_pAccountNumberCtrl, wxGBPosition ( 0, 1 ) );

	// ... account description....
	wxStaticText* pAccountOwnerText = new wxStaticText (
		this,
		wxID_ANY,
		CyGetText::getInstance ( ).getText ( "CyWxEditAccountDialog.CyWxEditAccountDialog.AccountOwner" ),
		wxDefaultPosition,
		wxSize ( kTextGridWidth, kTextGridHeight ),
		wxALIGN_BOTTOM | wxALIGN_RIGHT );
	pAccountSizer->Add ( pAccountOwnerText ,  wxGBPosition ( 1, 0 ) );

	this->m_pAccountOwnerCtrl = new wxTextCtrl ( 
		this, 
		CyWxEditAccountDialog::kAccountOwner,
		m_strAccountOwner,
		wxDefaultPosition,
		wxSize ( kControlGridWidth, kControlGridHeight ) );
	pAccountSizer->Add ( this->m_pAccountOwnerCtrl, wxGBPosition ( 1, 1 ) );

	// ... account import
	wxStaticText* pAccountCanBeImportedText = new wxStaticText (
		this,
		wxID_ANY,
		CyGetText::getInstance ( ).getText ( "CyWxEditAccountDialog.CyWxEditAccountDialog.AccountCanBeImported" ),
		wxDefaultPosition,
		wxSize ( kTextGridWidth, kTextGridHeight ),
		wxALIGN_BOTTOM | wxALIGN_RIGHT );
	pAccountSizer->Add ( pAccountCanBeImportedText ,  wxGBPosition ( 2, 0 ) );

	wxArrayString strAccountCanBeImported;
	strAccountCanBeImported.Add ( CyGetText::getInstance ( ).getText ( "CyWxEditAccountDialog.CyWxEditAccountDialog.Yes" ) );
	strAccountCanBeImported.Add ( CyGetText::getInstance ( ).getText ( "CyWxEditAccountDialog.CyWxEditAccountDialog.No" ) );

	this->m_pAccountCanBeImportedComboBox = new wxComboBox (
		this, 
		CyWxEditAccountDialog::kAccountCanBeImported,
		CyGetText::getInstance ( ).getText ( "CyWxEditAccountDialog.CyWxEditAccountDialog.Yes" ),
		wxDefaultPosition,
		wxSize ( kControlGridWidth, kControlGridHeight ),
		strAccountCanBeImported,
		wxCB_READONLY );

	pAccountSizer->Add ( this->m_pAccountCanBeImportedComboBox, wxGBPosition ( 2, 1 ) );

	// selection of the correct value in the import combo box
	this->m_pAccountCanBeImportedComboBox->Select ( ( CyEnum::kYes == this->m_lAccountCanBeImported ) ? 0 : 1 );

	// account valid since date
	wxStaticText* pAccountValidSinceText = new wxStaticText (
		this,
		wxID_ANY,
		CyGetText::getInstance ( ).getText ( "CyWxEditAccountDialog.CyWxEditAccountDialog.AccountValidSince" ),
		wxDefaultPosition,
		wxSize ( kTextGridWidth, kTextGridHeight ),
		wxALIGN_BOTTOM | wxALIGN_RIGHT );
	pAccountSizer->Add ( pAccountValidSinceText ,  wxGBPosition ( 3, 0 ) );

	this->m_pAccountValidSinceDateCtrl = new wxDatePickerCtrl ( 
		this,
		CyWxEditAccountDialog::kAccountValidSinceDate,
		wxDefaultDateTime,
		wxDefaultPosition ,
		wxSize ( kControlGridWidth, kControlGridHeight ),
		wxDP_DROPDOWN );

	wxDateTime accountValidSinceDate;
	if ( accountValidSinceDate.ParseISODate ( strAccountValidSinceDate ) )
	{
		this->m_pAccountValidSinceDateCtrl->SetValue ( accountValidSinceDate );
	}

	pAccountSizer->Add ( this->m_pAccountValidSinceDateCtrl ,  wxGBPosition ( 3, 1 ) );

	// initial amount of the account
	wxStaticText* pAccountInitialAmountText = new wxStaticText (
		this,
		wxID_ANY,
		CyGetText::getInstance ( ).getText ( "CyWxEditAccountDialog.CyWxEditAccountDialog.AccountInitialAmount" ),
		wxDefaultPosition,
		wxSize ( kTextGridWidth, kTextGridHeight ),
		wxALIGN_BOTTOM | wxALIGN_RIGHT );
	pAccountSizer->Add ( pAccountInitialAmountText ,  wxGBPosition ( 4, 0 ) );

	wxFloatingPointValidator <  double > initialAmountValidator(
		static_cast < int > ( CyUserPreferences::getInstance ( ).getCurrencyDecimalPrecision ( ) ), &m_dAccountInitialAmount, wxNUM_VAL_DEFAULT);

	this->m_pAccountInitialAmountCtrl = new wxTextCtrl ( 
		this, 
		CyWxEditAccountDialog::kAccountInitialAmount,
		wxEmptyString,
		wxDefaultPosition,
		wxSize ( kControlGridWidth, kControlGridHeight ),
		0,
		initialAmountValidator );

	*( this->m_pAccountInitialAmountCtrl ) << this->m_dAccountInitialAmount;
	pAccountSizer->Add ( m_pAccountInitialAmountCtrl ,  wxGBPosition ( 4, 1 ) );

	// and the gridbag is added to the secondary sizer...
	pStaticBoxSizer->Add ( pAccountSizer, 0, wxEXPAND | wxALL, CyEnum::kMarginSize );

	// and the secondary sizer added to the main sizer
	pMainSizer->Add ( pStaticBoxSizer, 0, wxEXPAND | wxALL, CyEnum::kMarginSize );

	pMainSizer->AddSpacer ( CyEnum::kMarginSize );

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

CyWxEditAccountDialog::~CyWxEditAccountDialog ( )
{
}

/* ---------------------------------------------------------------------------- */

const wxString CyWxEditAccountDialog::getAccountNumber ( ) const
{
	return this->m_pAccountNumberCtrl->GetValue ( );
}

/* ---------------------------------------------------------------------------- */

const wxString CyWxEditAccountDialog::getAccountOwner ( ) const
{
	return this->m_pAccountOwnerCtrl->GetValue ( );
}

/* ---------------------------------------------------------------------------- */

const long long& CyWxEditAccountDialog::getAccountObjId ( ) const
{
	return this->m_lAccountObjId;
}

/* ---------------------------------------------------------------------------- */

const CyEnum::AccountCanBeImported CyWxEditAccountDialog::getAccountCanBeImported ( ) const
{
	return ( CyGetText::getInstance ( ).getText ( "CyWxEditAccountDialog.CyWxEditAccountDialog.Yes" ) == this->m_pAccountCanBeImportedComboBox->GetStringSelection (  ) ) ? CyEnum::kYes : CyEnum::kNo;
}

/* ---------------------------------------------------------------------------- */

const wxString CyWxEditAccountDialog::getAccountValidSinceDate ( ) const
{
	return this->m_pAccountValidSinceDateCtrl->GetValue ( ).Format ( wxString ( "%Y-%m-%d" ) );
}

/* ---------------------------------------------------------------------------- */

const long long CyWxEditAccountDialog::getAccountInitialAmount ( ) const
{
	return CyCurrencyConverter::toLongLong ( this->m_dAccountInitialAmount );
}

/* ---------------------------------------------------------------------------- */

int CyWxEditAccountDialog::ShowModal ( )
{
	int iReturnCode =  wxDialog::ShowModal ( );

	if ( wxID_OK == iReturnCode )
	{
		this->m_currentRow.at ( CyAccountsSqlBuilder::kAccountNumber )->set ( this->getAccountNumber ( ) );
		this->m_currentRow.at ( CyAccountsSqlBuilder::kAccountOwner )->set ( this->getAccountOwner ( ) );
		this->m_currentRow.at ( CyAccountsSqlBuilder::kAccountImported )->set ( this->getAccountCanBeImported ( ) );
		this->m_currentRow.at ( CyAccountsSqlBuilder::kAccountValidSinceDate )->set ( this->getAccountValidSinceDate ( ) );
		this->m_currentRow.at ( CyAccountsSqlBuilder::kAccountInitialAmount )->set ( this->getAccountInitialAmount ( ) );
	}

	return iReturnCode;
}

/* ---------------------------------------------------------------------------- */
