/* ---------------------------------------------------------------------------- */
//! CyWxEditAttributionDialog.cpp
/* ---------------------------------------------------------------------------- */
//!
//! \file CyWxEditAttributionDialog.cpp
//! \brief definition file for class CyWxEditAttributionDialog
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

#include "UserInterfaceLayer/CyWxEditAttributionDialog.h"
#include "UserInterfaceLayer/CyWxLongLongItemData.h"
#include "CoreLayer/CyBudgetsSqlBuilder.h"
#include "CoreLayer/CyAttributionsGroupsSqlBuilder.h"
#include "CoreLayer/CyAttributionsSqlBuilder.h"
#include "DataLayer/CyLongValue.h"
#include "DataLayer/CySqliteDb.h"
#include "DataLayer/CyStringValue.h"
#include "UtilitiesLayer/CyEnum.h"
#include "UtilitiesLayer/CyGetText.h"

/* ---------------------------------------------------------------------------- */


CyWxEditAttributionDialog::CyWxEditAttributionDialog ( CyQueryResult::CyQueryResultValuesRow& currentRow, wxWindow* pParent, const wxString& strTitle ) :
	wxDialog  (
		pParent,
		wxID_ANY,
		strTitle,
		::wxGetMousePosition ( ),
		wxSize ( kDialogWidth, kDialogHeight ),
		wxRESIZE_BORDER | wxCAPTION | wxMAXIMIZE_BOX | wxCLOSE_BOX | wxCAPTION  ),
	m_currentRow ( currentRow )

{
	// The main sizer is created
	wxBoxSizer* pMainSizer = new wxBoxSizer ( wxVERTICAL );

	// a secondary sizer is added for the data
	wxBoxSizer* pStaticBoxSizer = new wxStaticBoxSizer (
		wxVERTICAL,
		this,
		wxEmptyString );

	// a gridbag sizer is created...
	wxGridBagSizer* pAttributionSizer = new wxGridBagSizer ( CyEnum::kMarginSize, CyEnum::kMarginSize );

	// and texts and control added....
	// ... for group definiton ...
	wxStaticText* pGroupDefinitionText = new wxStaticText (
		this,
		wxID_ANY,
		CyGetText::getInstance ( ).getText ( "CyWxEditAttributionDialog.CyWxEditAttributionDialog.GroupDescription" ),
		wxDefaultPosition,
		wxSize ( kTextGridWidth, kTextGridHeight ),
		wxALIGN_BOTTOM | wxALIGN_RIGHT );
	pAttributionSizer->Add ( pGroupDefinitionText ,  wxGBPosition ( 0, 0 ) );

	// Groups combo box creation
	wxArrayString strDummyArray;
	this->m_pAttributionGroupDescriptionComboBox = new wxComboBox (
		this, 
		CyWxEditAttributionDialog::kAttributionGroupDescription,
		m_currentRow.at ( CyAttributionsSqlBuilder::kAttributionGroupDescription )->getAsString ( ),
		wxDefaultPosition,
		wxSize ( kControlGridWidth, kControlGridHeight ),
		strDummyArray,
		wxCB_READONLY );
	pAttributionSizer->Add ( this->m_pAttributionGroupDescriptionComboBox, wxGBPosition ( 0, 1 ) );

	// ... groups values are searched in the db...
	CyQueryResult objAttributionsGroupsQueryResult;
	CyAttributionsGroupsSqlBuilder objAttributionsGroupsSqlBuilder;
	objAttributionsGroupsSqlBuilder.doSelect ( objAttributionsGroupsQueryResult );
	CyQueryResult::const_iterator iterator;

	// ... and added to the control
	for ( iterator = objAttributionsGroupsQueryResult.begin (); iterator != objAttributionsGroupsQueryResult.end ( ); ++ iterator )
	{
		this->m_pAttributionGroupDescriptionComboBox->Append ( 
			iterator->at ( CyAttributionsGroupsSqlBuilder::kGroupDescription )->getAsString ( ), 
			new CyWxLongLongItemData ( iterator->at ( CyAttributionsGroupsSqlBuilder::kGroupObjId )->get ( CyLongValue::m_lDummyValue ) ) );
	}

	// and the first group selected ( for the add dialog ) or the value from the currentRow ( for the edit dialog )
	this->m_pAttributionGroupDescriptionComboBox->SetValue ( 
		( CyEnum::kInvalidObjId == m_currentRow.at ( CyAttributionsSqlBuilder::kAttributionGroupObjId )->get ( CyLongValue::m_lDummyValue ) ) ?
			objAttributionsGroupsQueryResult.at ( 0 ).at ( CyAttributionsGroupsSqlBuilder::kGroupDescription )->getAsString ( ):
			m_currentRow.at ( CyAttributionsSqlBuilder::kAttributionGroupDescription )->getAsString ( ) );

	// For definition
	wxStaticText* pDefinitionText = new wxStaticText (
		this,
		wxID_ANY,
		CyGetText::getInstance ( ).getText ( "CyWxEditAttributionDialog.CyWxEditAttributionDialog.Description" ),
		wxDefaultPosition,
		wxSize ( kTextGridWidth, kTextGridHeight ),
		wxALIGN_BOTTOM | wxALIGN_RIGHT );
	pAttributionSizer->Add ( pDefinitionText ,  wxGBPosition ( 1, 0 ) );

	this->m_pAttributionDescriptionCtrl = new wxTextCtrl ( 
		this, 
		CyWxEditAttributionDialog::kAttributionDescription,
		m_currentRow.at ( CyAttributionsSqlBuilder::kAttributionDescription )->getAsString ( ),
		wxDefaultPosition,
		wxSize ( kControlGridWidth, kControlGridHeight ) );
	pAttributionSizer->Add ( this->m_pAttributionDescriptionCtrl, wxGBPosition ( 1, 1 ) );

	// For budgets
	wxStaticText* pBudgetText = new wxStaticText (
		this,
		wxID_ANY,
		CyGetText::getInstance ( ).getText ( "CyWxEditAttributionDialog.CyWxEditAttributionDialog.Budget" ),
		wxDefaultPosition,
		wxSize ( kTextGridWidth, kTextGridHeight ),
		wxALIGN_BOTTOM | wxALIGN_RIGHT );
	pAttributionSizer->Add ( pBudgetText ,  wxGBPosition ( 2, 0 ) );

	// ...budget combo box creation
	this->m_pBudgetComboBox = new wxComboBox ( 
		this, 
		CyWxEditAttributionDialog::kBudgetDescription,
		m_currentRow.at ( CyAttributionsSqlBuilder::kBudgetDescription )->getAsString ( ),
		wxDefaultPosition,
		wxSize ( kControlGridWidth, kControlGridHeight ),
		strDummyArray, 
		wxCB_READONLY );
	pAttributionSizer->Add ( this->m_pBudgetComboBox, wxGBPosition ( 2, 1 ));

	// ... budgets values are searched in the db...
	CyQueryResult objBudgetsQueryResult;
	CyBudgetsSqlBuilder objBudgetsSqlBuilder;
	objBudgetsSqlBuilder.doSelect ( objBudgetsQueryResult );

	// ...and added to the control
	for ( iterator = objBudgetsQueryResult.begin (); iterator != objBudgetsQueryResult.end ( ); ++ iterator )
	{
		this->m_pBudgetComboBox->Append ( 
			iterator->at ( CyBudgetsSqlBuilder::kBudgetDescription )->getAsString ( ), 
			new CyWxLongLongItemData ( iterator->at ( CyBudgetsSqlBuilder::kBudgetObjId )->get ( CyLongValue::m_lDummyValue ) ) );
	}

	// and the first budget selected ( for the add dialog ) or the edited attribution's budget selected ( for the edit dialog ) 
	this->m_pBudgetComboBox->SetValue ( 
		( CyEnum::kInvalidObjId == m_currentRow.at ( CyAttributionsSqlBuilder::kBudgetObjId )->get ( CyLongValue::m_lDummyValue ) ) ?
			objBudgetsQueryResult.at ( 0 ).at ( CyBudgetsSqlBuilder::kBudgetDescription )->getAsString ( ):
			m_currentRow.at ( CyAttributionsSqlBuilder::kBudgetDescription )->getAsString ( ) );

	// attribution valid to date
	wxStaticText* pAttributionValidToDateText = new wxStaticText (
		this,
		wxID_ANY,
		CyGetText::getInstance ( ).getText ( "CyWxEditAttributionDialog.CyWxEditAttributionDialog.AttributionValidTo" ),
		wxDefaultPosition,
		wxSize ( kTextGridWidth, kTextGridHeight ),
		wxALIGN_BOTTOM | wxALIGN_RIGHT );
	pAttributionSizer->Add ( pAttributionValidToDateText, wxGBPosition ( 3, 0 ) );

	this->m_pAttributionValidToDateCtrl = new wxDatePickerCtrl (
		this,
		CyWxEditAttributionDialog::kAttributionValidToDate,
		wxDefaultDateTime,
		wxDefaultPosition,
		wxSize ( kControlGridWidth, kControlGridHeight ),
		wxDP_DROPDOWN );
	pAttributionSizer->Add ( this->m_pAttributionValidToDateCtrl, wxGBPosition ( 3, 1 ) );

	wxString strAttributionValidSinceDate = m_currentRow.at ( CyAttributionsSqlBuilder::kAttributionValidToDate )->getAsString ( );

	wxDateTime attributionValidToDate;
	if ( attributionValidToDate.ParseISODate ( strAttributionValidSinceDate ) )
	{
		this->m_pAttributionValidToDateCtrl->SetValue ( attributionValidToDate );
	}

	// and the gridbag is added to the secondary sizer...
	pStaticBoxSizer->Add ( pAttributionSizer, 0, wxEXPAND | wxALL, CyEnum::kMarginSize );

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

CyWxEditAttributionDialog::~CyWxEditAttributionDialog ( )
{
}

/* ---------------------------------------------------------------------------- */

const wxString CyWxEditAttributionDialog::getAttributionGroupDescription ( ) const
{
	return this->m_pAttributionGroupDescriptionComboBox->GetValue ( );
}

/* ---------------------------------------------------------------------------- */

const long long CyWxEditAttributionDialog::getAttributionGroupObjId ( ) const
{
	CyWxLongLongItemData* pLongLongItemData =  dynamic_cast < CyWxLongLongItemData* > ( this->m_pAttributionGroupDescriptionComboBox->GetClientObject ( 
		static_cast < unsigned int > ( this->m_pAttributionGroupDescriptionComboBox->GetSelection ( ) ) ) );
	if ( NULL != pLongLongItemData )
	{
		return pLongLongItemData->getValue ( );
	}
	else
	{
		return CyEnum::kInvalidObjId;
	}
}

/* ---------------------------------------------------------------------------- */

const wxString CyWxEditAttributionDialog::getAttributionDescription ( ) const
{
	return this->m_pAttributionDescriptionCtrl->GetValue ( );
}

/* ---------------------------------------------------------------------------- */

const wxString CyWxEditAttributionDialog::getAttributionBudgetDescription ( ) const
{
	return this->m_pBudgetComboBox->GetValue ( );
}

/* ---------------------------------------------------------------------------- */

const long long CyWxEditAttributionDialog::getAttributionBudgetObjId ( ) const
{
	CyWxLongLongItemData* pLongLongItemData =  dynamic_cast < CyWxLongLongItemData* > ( this->m_pBudgetComboBox->GetClientObject (
		static_cast < unsigned int > ( this->m_pBudgetComboBox->GetSelection ( ) ) ) );
	if ( NULL != pLongLongItemData )
	{
		return pLongLongItemData->getValue ( );
	}
	else
	{
		return CyEnum::kInvalidObjId;
	}
}

/* ---------------------------------------------------------------------------- */

const wxString CyWxEditAttributionDialog::getAttributionValidToDate ( ) const
{
	return this->m_pAttributionValidToDateCtrl->GetValue ( ).Format ( wxString ( "%Y-%m-%d" ) );
}

/* ---------------------------------------------------------------------------- */

int CyWxEditAttributionDialog::ShowModal ( )
{
	int iReturnCode =  wxDialog::ShowModal ( );

	if ( wxID_OK == iReturnCode )
	{
		this->m_currentRow.at ( CyAttributionsSqlBuilder::kAttributionGroupObjId )->set ( this->getAttributionGroupObjId ( ) );
		this->m_currentRow.at ( CyAttributionsSqlBuilder::kBudgetObjId )->set ( this->getAttributionBudgetObjId ( ) );
		this->m_currentRow.at ( CyAttributionsSqlBuilder::kAttributionGroupDescription )->set ( this->getAttributionGroupDescription ( ) );
		this->m_currentRow.at ( CyAttributionsSqlBuilder::kAttributionDescription )->set ( this->getAttributionDescription ( ) );
		this->m_currentRow.at ( CyAttributionsSqlBuilder::kBudgetDescription )->set ( this->getAttributionBudgetDescription ( ) );
		this->m_currentRow.at ( CyAttributionsSqlBuilder::kAttributionValidToDate )->set ( this->getAttributionValidToDate ( ) );
	}

	return iReturnCode;
}

/* ---------------------------------------------------------------------------- */
