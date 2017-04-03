/* ---------------------------------------------------------------------------- */
//! CyWxEditOperationAttributionDialog.cpp
/* ---------------------------------------------------------------------------- */
//!
//! \file CyWxEditOperationAttributionDialog.cpp
//! \brief definition file for class CyWxEditOperationAttributionDialog
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

#include "UserInterfaceLayer/CyWxEditOperationAttributionDialog.h"
#include "CoreLayer/CyAttributionsSqlBuilder.h"
#include "CoreLayer/CyCurrencyConverter.h"
#include "CoreLayer/CyOperationsAttributionsSqlBuilder.h"
#include "DataLayer/CyLongValue.h"
#include "DataLayer/CyStringValue.h"
#include "DataLayer/CyUserPreferences.h"
#include "UtilitiesLayer/CyEnum.h"
#include "UtilitiesLayer/CyGetText.h"

/* ---------------------------------------------------------------------------- */

CyWxEditOperationAttributionDialog::CyWxEditOperationAttributionDialog ( CyQueryResult::CyQueryResultValuesRow& currentRow, wxWindow* pParent, const wxString& strTitle ) :
	wxDialog  (
		pParent,
		wxID_ANY,
		strTitle,
		wxDefaultPosition,
		wxSize ( kDialogWidth, kDialogHeight ),
		wxRESIZE_BORDER | wxCAPTION | wxMAXIMIZE_BOX | wxCLOSE_BOX | wxCAPTION  ),
		m_currentRow ( currentRow ),
		m_dAmount ( 0.0 ),
		m_pSelectedItemData ( NULL )
{
	// The main sizer is created
	wxBoxSizer* pMainSizer = new wxBoxSizer ( wxVERTICAL );

	// a sizer for the controls is created
	wxBoxSizer* pAttributionSizer = new wxStaticBoxSizer (
		wxVERTICAL,
		this,
		wxEmptyString );

	// and texts and control added....
	// ... for the attributions
	wxStaticText* pAttributionText = new wxStaticText (
		this,
		wxID_ANY,
		CyGetText::getInstance ( ).getText ( "CyWxEditOperationAttributionDialog.CyWxEditOperationAttributionDialog.Attribution" ),
		wxDefaultPosition,
		wxSize ( kTextWidth, kTextHeight ),
		wxALIGN_BOTTOM | wxALIGN_LEFT );
	pAttributionSizer->Add ( pAttributionText );

	this->m_pAttributionCtrl = new wxTreeCtrl (
		this,
		this->kAttribution,
		wxDefaultPosition,
		wxSize ( kControlWidth, kTreeControlHeight ),
		wxTR_DEFAULT_STYLE);

	// The attributions are searched in the db
	wxDateTime objToday;
	objToday.SetToCurrent ( );
	CyAttributionsSqlBuilder objAttributionsSqlBuilder ( objToday );
	objAttributionsSqlBuilder.doSelect ( this->m_objAttributionsQueryResult );

	// An empty root item is created
	// For each item in the tree, item data are added. The item data contains:
	// - the ObjId of the attribution in the table Attributions for item corresponding to the Description field.
	// - for the root item and item corresponding to the MainDescription field a CyEnum::kInvalidObjId value is added
	wxTreeItemId rootItem = this->m_pAttributionCtrl->AddRoot ( 
		wxEmptyString,
		CyEnum::kNoImage,
		CyEnum::kNoSelectedImage,
		new CyWxTreeItemData ( static_cast <size_t > ( CyEnum::kInvalidObjId ) ) );

	// Preparing the loop on the attributions to add the items to the tree control
	CyQueryResult::const_iterator AttributionsQueryIterator;
	long long lCurrentGroupObjId = CyEnum::kInvalidObjId;
	wxTreeItemId currentGroupItem;
	wxTreeItemId currentItem;
	wxTreeItemId selectedItem;
	bool bSelectedItemFound = false;
	size_t position = 0;
	long long lEditedAttributionObjId = this->m_currentRow.at ( CyOperationsAttributionsSqlBuilder::kAtributionObjId )->get ( CyLongValue::m_lDummyValue );

	// loop on the attributions
	for ( AttributionsQueryIterator = this->m_objAttributionsQueryResult.begin ( ); AttributionsQueryIterator != this->m_objAttributionsQueryResult.end ( ); ++ AttributionsQueryIterator )
	{
		if ( lCurrentGroupObjId != AttributionsQueryIterator->at ( CyAttributionsSqlBuilder::kAttributionGroupObjId )->get ( CyLongValue::m_lDummyValue ) )
		{
			// The group is changed... adding a new main item under the root item...
			currentGroupItem = this->m_pAttributionCtrl->AppendItem ( 
				rootItem,
				AttributionsQueryIterator->at ( CyAttributionsSqlBuilder::kAttributionGroupDescription )->getAsString ( ),
				CyEnum::kNoImage,
				CyEnum::kNoSelectedImage,
				new CyWxTreeItemData ( static_cast < size_t > ( CyEnum::kInvalidObjId ) ) );
			lCurrentGroupObjId = AttributionsQueryIterator->at ( CyAttributionsSqlBuilder::kAttributionGroupObjId )->get ( CyLongValue::m_lDummyValue );
		}
		// ...and adding a new item under the main item...
		currentItem = this->m_pAttributionCtrl->AppendItem ( 
			currentGroupItem, 
			AttributionsQueryIterator->at ( CyAttributionsSqlBuilder::kAttributionDescription )->getAsString ( ),
			CyEnum::kNoImage,
			CyEnum::kNoSelectedImage,
			new CyWxTreeItemData ( position ) );

		++ position;

		// ...and comparing the new item with the edited item.
		if ( lEditedAttributionObjId == AttributionsQueryIterator->at ( CyAttributionsSqlBuilder::kAttributionObjId )->get ( CyLongValue::m_lDummyValue ) )
		{
			selectedItem = currentItem;
			bSelectedItemFound = true;
		}
	} // end of loop on attributions

	if ( bSelectedItemFound )
	{
		// a selected item was found. The item is show, selected and set in bold
		this->m_pAttributionCtrl->EnsureVisible ( selectedItem );
		this->m_pAttributionCtrl->SelectItem ( selectedItem );
		this->m_pAttributionCtrl->SetItemBold ( selectedItem );
		// and saved in the >m_pSelectedItemData member variable
		this->m_pSelectedItemData = dynamic_cast < CyWxTreeItemData* > ( this->m_pAttributionCtrl->GetItemData ( selectedItem ) );
	}

	// and finally the tree control is added to the sizer
	pAttributionSizer->Add ( this->m_pAttributionCtrl );
	pAttributionSizer->AddSpacer ( CyEnum::kMarginSize );

	// now text and control for the amount are created
	wxStaticText* pAmountText = new wxStaticText (
		this,
		wxID_ANY,
		CyGetText::getInstance ( ).getText ( "CyWxEditOperationAttributionDialog.CyWxEditOperationAttributionDialog.Amount" ),
		wxDefaultPosition,
		wxSize ( kTextWidth, kTextHeight ),
		wxALIGN_BOTTOM | wxALIGN_LEFT );
	pAttributionSizer->Add ( pAmountText );

	// the amount available is searched in the currentRow
	this->m_dAmount = CyCurrencyConverter::toDouble ( this->m_currentRow.at ( CyOperationsAttributionsSqlBuilder::kAttributionOperationAmount )->get ( CyLongValue::m_lDummyValue ) );

	wxFloatingPointValidator < double > amountValidator( 
		static_cast < int > ( CyUserPreferences::getInstance ( ).getCurrencyDecimalPrecision ( ) ), &m_dAmount, wxNUM_VAL_DEFAULT);

	this->m_pAmountCtrl = new wxTextCtrl ( 
		this, 
		CyWxEditOperationAttributionDialog::kAmount,
		wxEmptyString,
		wxDefaultPosition,
		wxSize ( kControlWidth, kControlHeight ),
		0,
		amountValidator );

	*( this->m_pAmountCtrl ) << this->m_dAmount;

	pAttributionSizer->Add ( m_pAmountCtrl );

	// and the control's sizer is added to the main sizer
	pMainSizer->Add ( pAttributionSizer, 0, wxEXPAND | wxALL, CyEnum::kMarginSize );

	// and a OK / Cancel buttons sizer is added
	wxBoxSizer* pButtonSizer = new wxStaticBoxSizer ( wxHORIZONTAL, this, wxEmptyString );
	pButtonSizer->Add ( this->CreateButtonSizer ( wxOK | wxCANCEL ) );
	pMainSizer->Add ( pButtonSizer, 0, wxEXPAND | wxALL, CyEnum::kMarginSize );

	// the main sizer is added to the dialog
	this->SetSizer ( pMainSizer );

	if ( ! bSelectedItemFound )
	{
		// An item was not found. The ok button is disabled and the tree control expanded
		this->FindWindow ( this->GetAffirmativeId ( ) )->Disable ( );
		this->m_pAttributionCtrl->Expand ( rootItem );
	}
	// and the dialog is reorganized and centered
	this->Fit ( );
	this->Centre ( );

	// events are added
	this->Connect (
		this->m_pAttributionCtrl->GetId ( ),
		wxEVT_TREE_SEL_CHANGED,
		wxTreeEventHandler ( CyWxEditOperationAttributionDialog::onAttributionSelected ) );
}

/* ---------------------------------------------------------------------------- */

CyWxEditOperationAttributionDialog::~CyWxEditOperationAttributionDialog ( )
{
	this->Disconnect (
		m_pAttributionCtrl->GetId ( ),
		wxEVT_TREE_SEL_CHANGED,
		wxTreeEventHandler ( CyWxEditOperationAttributionDialog::onAttributionSelected ) );
}

/* ---------------------------------------------------------------------------- */

void CyWxEditOperationAttributionDialog::onAttributionSelected ( wxTreeEvent& event  )
{
	this->m_pSelectedItemData = dynamic_cast < CyWxTreeItemData* > ( this->m_pAttributionCtrl->GetItemData ( event.GetItem ( ) ) );
	
	// when the user select a MainDescription item or the root item the ok button is disabled
	if ( CyEnum::kInvalidObjId ==  static_cast < int > ( this->m_pSelectedItemData->getPosition ( ) ) )
	{
		this->FindWindow ( this->GetAffirmativeId ( ) )->Disable ( );
	}
	else
	{
		this->FindWindow ( this->GetAffirmativeId ( ) )->Enable ( );
	}	
}

/* ---------------------------------------------------------------------------- */

const long long CyWxEditOperationAttributionDialog::getAttributionObjId ( ) const
{
	long long lReturnValue = CyEnum::kInvalidObjId;
	if ( ( NULL != this->m_pSelectedItemData ) && ( CyEnum::kInvalidObjId != static_cast < int > ( this->m_pSelectedItemData->getPosition ( ) ) ) )
	{
		lReturnValue = this->m_objAttributionsQueryResult.at ( 
			this->m_pSelectedItemData->getPosition ( ) ).at ( CyAttributionsSqlBuilder::kAttributionObjId )->get ( CyLongValue::m_lDummyValue );
	}

	return lReturnValue;
}

/* ---------------------------------------------------------------------------- */

const long long CyWxEditOperationAttributionDialog::getAmount ( ) const
{
	return  CyCurrencyConverter::toLongLong ( this->m_dAmount );
}

/* ---------------------------------------------------------------------------- */

const wxString CyWxEditOperationAttributionDialog::getGroupDescription ( ) const
{
	if ( ( NULL != this->m_pSelectedItemData ) && ( CyEnum::kInvalidObjId != static_cast < int > ( this->m_pSelectedItemData->getPosition ( ) ) ) )
	{
		return this->m_objAttributionsQueryResult.at ( 
			this->m_pSelectedItemData->getPosition ( ) ).at ( CyAttributionsSqlBuilder::kAttributionGroupDescription )->getAsString ( );
	}

	return wxEmptyString;
}

/* ---------------------------------------------------------------------------- */

const wxString CyWxEditOperationAttributionDialog::getDescription ( ) const
{
	if ( ( NULL != this->m_pSelectedItemData ) && ( CyEnum::kInvalidObjId != static_cast < int > ( this->m_pSelectedItemData->getPosition ( ) ) ) )
	{
		return this->m_objAttributionsQueryResult.at ( 
			this->m_pSelectedItemData->getPosition ( ) ).at ( CyAttributionsSqlBuilder::kAttributionDescription )->getAsString ( );
	}

	return wxEmptyString;
}

/* ---------------------------------------------------------------------------- */

int CyWxEditOperationAttributionDialog::ShowModal ( )
{
	int iReturnCode =  wxDialog::ShowModal ( );

	if ( wxID_OK == iReturnCode )
	{
		m_currentRow.at ( CyOperationsAttributionsSqlBuilder::kAtributionObjId )->set ( this->getAttributionObjId ( ) );
		m_currentRow.at ( CyOperationsAttributionsSqlBuilder::kAttributionGroupDescription )->set ( this->getGroupDescription ( ) );
		m_currentRow.at ( CyOperationsAttributionsSqlBuilder::kAttributionDescription )->set ( this->getDescription ( ) );
		m_currentRow.at ( CyOperationsAttributionsSqlBuilder::kAttributionOperationAmount )->set ( this->getAmount ( ) );
	}

	return iReturnCode;
}

/* ---------------------------------------------------------------------------- */

