/* ---------------------------------------------------------------------------- */
//! CyWxEditOperationDialog.cpp
/* ---------------------------------------------------------------------------- */
//!
//! \file CyWxEditOperationDialog.cpp
//! \brief definition file for class CyWxEditOperationDialog
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
#include "UserInterfaceLayer/CyWxEditOperationDialog.h"
#include "CoreLayer/CyCurrencyConverter.h"
#include "CoreLayer/CyOperationsAttributionsSqlBuilder.h"
#include "CoreLayer/CyOperationsDetailsSqlBuilder.h"
#include "CoreLayer/CyOperationsSqlBuilder.h"
#include "CoreLayer/CyOperationsSqlManager.h"
#include "DataLayer/CyLongValue.h"
#include "DataLayer/CySqliteDb.h"
#include "DataLayer/CyStringValue.h"
#include "DataLayer/CyUserPreferences.h"
#include "UtilitiesLayer/CyEnum.h"
#include "UtilitiesLayer/CyGetText.h"

/* ---------------------------------------------------------------------------- */

CyWxEditOperationDialog::CyWxEditOperationDialog ( 
	CyOperationsSqlManager* pOperationsSqlManager,
	wxWindow* pParent, 
	const wxString& strTitle ) :
	wxDialog  (
		pParent,
		wxID_ANY,
		strTitle,
		wxDefaultPosition,
		wxSize ( kDialogWidth, kDialogHeight ),
		wxRESIZE_BORDER | wxCAPTION | wxMAXIMIZE_BOX | wxCLOSE_BOX | wxCAPTION  ),
		m_bAccountCanBeImported ( true ),
		m_dAmount ( 0.0 ),
		m_lOperationObjId ( CyEnum::kInvalidObjId ),
		m_bAttributionModified ( false ),
		m_pOperationsSqlManager ( pOperationsSqlManager )
{
	// The needed informations are extracted from the currentRow parameter.
	this->m_bAccountCanBeImported =
		( CyEnum::kYes == m_pOperationsSqlManager->getRow ( )->at ( CyOperationsSqlBuilder::kOperationAccountCanBeImported )->get ( CyLongValue::m_lDummyValue ) );
	this->m_strAccountNumber = m_pOperationsSqlManager->getRow ( )->at ( CyOperationsSqlBuilder::kOperationAccountNumber )->getAsString ( );

	// The main sizer is created.
	wxBoxSizer* pMainSizer = new wxBoxSizer ( wxVERTICAL );

	// A sizer for the account and operation number is created...
	wxBoxSizer* pInfoSizer = new wxStaticBoxSizer (
		wxVERTICAL,
		this,
		wxEmptyString );

	// and texts added....
	// ... for accountnumber ...
	wxString strAccountText;
	strAccountText
		<< CyGetText::getInstance ( ).getText ( "CyWxEditOperationDialog.CyWxEditOperationDialog.Account" )
		<< this->m_pOperationsSqlManager->getRow ( )->at ( CyOperationsSqlBuilder::kOperationAccountNumber )->getAsString ( );
	wxStaticText* pAccountText = new wxStaticText (
		this,
		wxID_ANY,
		strAccountText,
		wxDefaultPosition,
		wxSize ( kSingleControlWidth, kTextHeight ),
		wxALIGN_BOTTOM | wxALIGN_LEFT );
	pInfoSizer->Add ( pAccountText );

	// ... and operation number...
	wxString strOperationNumberText;
	strOperationNumberText
		<< CyGetText::getInstance ( ).getText ( "CyWxEditOperationDialog.CyWxEditOperationDialog.OperationNumber" )
		<< m_pOperationsSqlManager->getRow ( )->at ( CyOperationsSqlBuilder::kOperationNumber )->getAsString ( ); 

	wxStaticText* pOperationNumberText = new wxStaticText (
		this,
		wxID_ANY,
		strOperationNumberText,
		wxDefaultPosition,
		wxSize ( kSingleControlWidth, kTextHeight ),
		wxALIGN_BOTTOM | wxALIGN_LEFT );
	pInfoSizer->Add ( pOperationNumberText );

	// ...and the sizer is added to the main sizer.
	pMainSizer->Add ( pInfoSizer, 0, wxEXPAND | wxALL, CyEnum::kMarginSize );

	pMainSizer->AddSpacer ( CyEnum::kMarginSize );

	// A gridbag sizer is created...
	wxGridBagSizer* pDateSizer = new wxGridBagSizer ( CyEnum::kMarginSize, CyEnum::kMarginSize );

	// and texts and controls added....
	// ... for operation date ...
	wxStaticText* pOperationDateText = new wxStaticText (
		this,
		wxID_ANY,
		CyGetText::getInstance ( ).getText ( "CyWxEditOperationDialog.CyWxEditOperationDialog.OperationDate" ),
		wxDefaultPosition,
		wxSize ( kTextGridWidth, kTextHeight ),
		wxALIGN_BOTTOM | wxALIGN_RIGHT );
	pDateSizer->Add ( pOperationDateText ,  wxGBPosition ( 0, 0 ) );

	this->m_pOperationDateCtrl = new wxDatePickerCtrl ( 
		this,
		this->kOperationDate,
		wxDefaultDateTime,
		wxDefaultPosition ,
		wxSize ( kControlGridWidth, kControlGridHeight ),
		wxDP_DROPDOWN );
	pDateSizer->Add ( this->m_pOperationDateCtrl ,  wxGBPosition ( 0, 1 ) );

	wxDateTime operationDate;
	if ( operationDate.ParseISODate ( m_pOperationsSqlManager->getRow ( )->at ( CyOperationsSqlBuilder::kOperationDate )->getAsString ( ) ) )
	{
		this->m_pOperationDateCtrl->SetValue ( operationDate );
	}

	// ... and the control disabled when the operation is imported ...
	if ( this->m_bAccountCanBeImported )
	{
		this->m_pOperationDateCtrl->Disable ( );
	}
	
	// ...for value date...
	wxStaticText* pValueDateText = new wxStaticText (
		this,
		wxID_ANY,
		CyGetText::getInstance ( ).getText ( "CyWxEditOperationDialog.CyWxEditOperationDialog.ValueDate" ),
		wxDefaultPosition,
		wxSize ( kTextGridWidth, kTextHeight ),
		wxALIGN_BOTTOM | wxALIGN_RIGHT );
	pDateSizer->Add ( pValueDateText ,  wxGBPosition ( 1, 0 ) );

	this->m_pValueDateCtrl = new wxDatePickerCtrl ( 
		this,
		this->kValueDate,
		wxDefaultDateTime,wxDefaultPosition ,
		wxSize ( kControlGridWidth, kControlGridHeight ),
		wxDP_DROPDOWN );
	pDateSizer->Add ( this->m_pValueDateCtrl ,  wxGBPosition ( 1, 1 ) );

	wxDateTime valueDate;
	if ( valueDate.ParseISODate ( m_pOperationsSqlManager->getRow ( )->at ( CyOperationsSqlBuilder::kOperationValueDate )->getAsString ( ) ) )
	{
		this->m_pValueDateCtrl->SetValue ( valueDate );
	}

	// ... and the control disabled when the operation is imported ....
	if ( this->m_bAccountCanBeImported )
	{
		this->m_pValueDateCtrl->Disable ( );
	}
	
	// ...and for budget date.
	wxStaticText* pBudgetDateText = new wxStaticText (
		this,
		wxID_ANY,
		CyGetText::getInstance ( ).getText ( "CyWxEditOperationDialog.CyWxEditOperationDialog.BudgetDate" ),
		wxDefaultPosition,
		wxSize ( kTextGridWidth, kTextHeight ),
		wxALIGN_BOTTOM | wxALIGN_RIGHT );
	pDateSizer->Add ( pBudgetDateText ,  wxGBPosition ( 2, 0 ) );

	this->m_pBudgetDateCtrl = new wxDatePickerCtrl ( 
		this, 
		this->kBudgetDate, 
		wxDefaultDateTime,
		wxDefaultPosition , 
		wxSize ( kControlGridWidth, kControlGridHeight ), 
		wxDP_DROPDOWN );
	pDateSizer->Add ( this->m_pBudgetDateCtrl ,  wxGBPosition ( 2, 1 ) );

	// The budget date is set to ...
	wxDateTime budgetDate;
	if ( budgetDate.ParseISODate ( m_pOperationsSqlManager->getRow ( )->at ( CyOperationsSqlBuilder::kOperationAttributionDate )->getAsString ( ) ) )
	{
		// ... the budget date found in the currentRow parameter...
		this->m_pBudgetDateCtrl->SetValue ( budgetDate );
	}
	else
	{
		// ... or to the operation date if not found.
		this->m_pBudgetDateCtrl->SetValue ( operationDate );
	}

	// A control is added for the amount...
	long long lAmount = m_pOperationsSqlManager->getRow ( )->at ( CyOperationsSqlBuilder::kOperationAmount )->get ( CyLongValue::m_lDummyValue );

	this->m_dAmount = CyCurrencyConverter::toDouble ( lAmount );
	wxStaticText* pAmountText = new wxStaticText (
		this,
		wxID_ANY,
		CyGetText::getInstance ( ).getText ( "CyWxEditOperationDialog.CyWxEditOperationDialog.Amount" ),
		wxDefaultPosition,
		wxSize ( kTextGridWidth, kTextHeight ),
		wxALIGN_BOTTOM | wxALIGN_RIGHT );
	pDateSizer->Add ( pAmountText ,  wxGBPosition ( 3, 0 ) );

	wxFloatingPointValidator <  double > amountValidator( static_cast < int > ( CyUserPreferences::getInstance ( ).getCurrencyDecimalPrecision ( ) ), &m_dAmount, wxNUM_VAL_DEFAULT);

	this->m_pAmountCtrl = new wxTextCtrl ( 
		this, 
		CyWxEditOperationDialog::kAmount,
		wxEmptyString,
		wxDefaultPosition,
		wxSize ( kControlGridWidth, kControlGridHeight ),
		0,
		amountValidator );
	*( this->m_pAmountCtrl ) << this->m_dAmount;
	pDateSizer->Add ( m_pAmountCtrl ,  wxGBPosition ( 3, 1 ) );

	// ... and the control disabled when the operation is imported.
	if ( this->m_bAccountCanBeImported )
	{
		this->m_pAmountCtrl->Disable ( );
	}

	// a main sizer for the dates and amount is created...
	wxBoxSizer* pMainDateSizer = new wxStaticBoxSizer (
		wxVERTICAL,
		this,
		wxEmptyString );

	// the gridbag sizer is added to the main date sizer
	pMainDateSizer->Add ( pDateSizer, 0, wxEXPAND | wxALL, CyEnum::kMarginSize );
	// and the main date sizer added to the main sizer
	pMainSizer->Add ( pMainDateSizer, 0, wxEXPAND | wxALL, CyEnum::kMarginSize );

	pMainSizer->AddSpacer ( CyEnum::kMarginSize );

	// a sizer is created for the attributions, the details and the note
	wxBoxSizer* pDetailSizer = new wxStaticBoxSizer (
		wxVERTICAL,
		this,
		wxEmptyString );

	// and texts and controls added...
	// ... for the attributions
	wxStaticText* pAttributionsText = new wxStaticText (
		this,
		wxID_ANY,
		CyGetText::getInstance ( ).getText ( "CyWxEditOperationDialog.CyWxEditOperationDialog.Attributions" ),
		wxDefaultPosition,
		wxSize ( kSingleControlWidth, kTextHeight ) );
	pDetailSizer->Add ( pAttributionsText );

	// ... creation of the attributions grid...
	this->m_pAttributionsGrid = new wxGrid ( this, -1,wxDefaultPosition,wxSize ( kSingleControlWidth, kAttributionsHeigth ) );
	this->m_pAttributionsGrid->CreateGrid ( 0, 3 );

	// ... adding labels to the grid....
	this->m_pAttributionsGrid->SetColLabelValue ( 0, CyGetText::getInstance ( ).getText ( "CyWxEditOperationDialog.CyWxEditOperationDialog.MainDescription" ) );
	this->m_pAttributionsGrid->SetColLabelValue ( 1, CyGetText::getInstance ( ).getText ( "CyWxEditOperationDialog.CyWxEditOperationDialog.Description" ) );
	this->m_pAttributionsGrid->SetColLabelValue ( 2, CyGetText::getInstance ( ).getText ( "CyWxEditOperationDialog.CyWxEditOperationDialog.AttributionAmount" ) );

	// ... and values to the grid
	int iRow = 0;
	CyQueryResult::const_iterator iterator;
	for ( iterator = this->m_pOperationsSqlManager->getOperationsAttributionsQueryResult ( ).begin ( );
		  iterator != this->m_pOperationsSqlManager->getOperationsAttributionsQueryResult ( ).end ( );
		  ++ iterator ) 
	{
		this->m_pAttributionsGrid->AppendRows ( 1 );
		this->m_pAttributionsGrid->SetCellValue ( 
			iRow, 
			0, 
			iterator->at ( CyOperationsAttributionsSqlBuilder::kAttributionGroupDescription )->getAsString ( ) );
		this->m_pAttributionsGrid->SetCellValue ( 
			iRow, 
			1, 
			iterator->at ( CyOperationsAttributionsSqlBuilder::kAttributionDescription )->getAsString ( ) );
		this->m_pAttributionsGrid->SetCellValue ( 
			iRow,
			2,
			iterator->at ( CyOperationsAttributionsSqlBuilder::kAttributionOperationAmount )->getAsString ( ) );

		++ iRow;
	}
	this->m_pAttributionsGrid->AutoSize ( );
	this->m_pAttributionsGrid->EnableEditing ( false );
	pDetailSizer->Add ( this->m_pAttributionsGrid );
	pDetailSizer->AddSpacer ( CyEnum::kMarginSize );

	// Acontrol is added for the operation's details...
	wxStaticText* pDetailText = new wxStaticText (
		this,
		wxID_ANY,
		CyGetText::getInstance ( ).getText ( "CyWxEditOperationDialog.CyWxEditOperationDialog.Details" ),
		wxDefaultPosition,
		wxSize ( kSingleControlWidth, kTextHeight ) );
	pDetailSizer->Add ( pDetailText );

	this->m_pDetailsCtrl = new wxTextCtrl ( 
		this, 
		CyWxEditOperationDialog::kDetails,
		wxEmptyString,
		wxDefaultPosition,
		wxSize ( kSingleControlWidth, kDetailsHeight ),
		this->m_bAccountCanBeImported ? wxTE_MULTILINE | wxTE_READONLY : wxTE_MULTILINE );

	// ...and details added to the control.
	for ( iterator = this->m_pOperationsSqlManager->getOperationsDetailsQueryResult ( ).begin ( );
		  iterator != this->m_pOperationsSqlManager->getOperationsDetailsQueryResult ( ).end ( );
		  ++ iterator )
	{
		*( this->m_pDetailsCtrl ) << iterator->at ( CyOperationsDetailsSqlBuilder::kDetail )->getAsString ( ) << char (13);
	}
	pDetailSizer->Add ( this->m_pDetailsCtrl );
	pDetailSizer->AddSpacer ( CyEnum::kMarginSize );

	// A control is created for the description...
	wxStaticText* pDescriptionText = new wxStaticText (
		this,
		wxID_ANY,
		CyGetText::getInstance ( ).getText ( "CyWxEditOperationDialog.CyWxEditOperationDialog.Note" ),
		wxDefaultPosition,
		wxSize ( kSingleControlWidth, kTextHeight ) );
	pDetailSizer->Add ( pDescriptionText );

	this->m_pDescriptionCtrl = new wxTextCtrl ( 
		this, 
		CyWxEditOperationDialog::kDescription,
		m_pOperationsSqlManager->getRow ( )->at ( CyOperationsSqlBuilder::kOperationDescription )->getAsString ( ),
		wxDefaultPosition,
		wxSize ( kSingleControlWidth, kDescriptionHeight ) );

	// ... and added to the sizer...
	pDetailSizer->Add ( this->m_pDescriptionCtrl );

	// ...and th sizer is added to the main sizer...
	pMainSizer->Add ( pDetailSizer, 0, wxEXPAND | wxALL, CyEnum::kMarginSize );

	pMainSizer->AddSpacer ( CyEnum::kMarginSize );

	// the button sizer is created
	wxBoxSizer* pButtonSizer = new wxStaticBoxSizer ( wxHORIZONTAL, this, wxEmptyString );
	pButtonSizer->Add ( this->CreateButtonSizer ( wxOK | wxCANCEL ) );

	pMainSizer->Add ( pButtonSizer, 0, wxEXPAND | wxALL, 5 );

	// the main sizer is added to the dialog
	this->SetSizer ( pMainSizer );

	// and the dialog is reorganized and centered
	this->Fit ( );
	this->Centre ( );

	// creation of events
	this->Connect (
		this->m_pAttributionsGrid->GetId ( ),
		wxEVT_GRID_CELL_RIGHT_CLICK,
		wxGridEventHandler ( CyWxEditOperationDialog::onRightClickGrid ) );
	this->Connect (
		this->m_pAttributionsGrid->GetId ( ),
		wxEVT_GRID_CELL_LEFT_DCLICK,
		wxGridEventHandler ( CyWxEditOperationDialog::onDoubleLeftClickGrid ) );
	this->Connect (
		this->m_pAttributionsGrid->GetId ( ),
		wxEVT_GRID_LABEL_RIGHT_CLICK,
		wxGridEventHandler ( CyWxEditOperationDialog::onRightClickLabel ) );
	this->Connect (
		this->m_pAttributionsGrid->GetId ( ),
		wxEVT_GRID_LABEL_LEFT_DCLICK,
		wxGridEventHandler ( CyWxEditOperationDialog::onDoubleLeftClickLabel ) );

}

/* ---------------------------------------------------------------------------- */

CyWxEditOperationDialog::~CyWxEditOperationDialog ( )
{
	this->Disconnect (
		this->m_pAttributionsGrid->GetId ( ),
		wxEVT_GRID_CELL_RIGHT_CLICK,
		wxGridEventHandler ( CyWxEditOperationDialog::onRightClickGrid ) );
	this->Disconnect (
		this->m_pAttributionsGrid->GetId ( ),
		wxEVT_GRID_CELL_LEFT_DCLICK,
		wxGridEventHandler ( CyWxEditOperationDialog::onDoubleLeftClickGrid ) );
	this->Disconnect (
		this->m_pAttributionsGrid->GetId ( ),
		wxEVT_GRID_LABEL_RIGHT_CLICK,
		wxGridEventHandler ( CyWxEditOperationDialog::onRightClickGrid ) );
	this->Disconnect (
		this->m_pAttributionsGrid->GetId ( ),
		wxEVT_GRID_LABEL_LEFT_DCLICK,
		wxGridEventHandler ( CyWxEditOperationDialog::onDoubleLeftClickLabel ) );
}

/* ---------------------------------------------------------------------------- */

void CyWxEditOperationDialog::onDoubleLeftClickLabel ( wxGridEvent& )
{
	this->addAttribution ( );
}

/* ---------------------------------------------------------------------------- */

void CyWxEditOperationDialog::onDoubleLeftClickGrid ( wxGridEvent& event )
{
	m_iCurrentAttributionRow = event.GetRow ( );
	this->editAttribution ( );
}

/* ---------------------------------------------------------------------------- */

void CyWxEditOperationDialog::onRightClickGrid ( wxGridEvent& event )
{
	m_iCurrentAttributionRow = event.GetRow ( );
	wxMenu objMenu;

	objMenu.Append ( CyWxEditOperationDialog::kEditAttribution,
					 CyGetText::getInstance ( ).getText ( "CyWxEditOperationDialog.onRightClickGrid.EditAttribution" ) );
	objMenu.Append ( CyWxEditOperationDialog::kAddAttribution,
					 CyGetText::getInstance ( ).getText ( "CyWxEditOperationDialog.onRightClickGrid.AddAttribution" ) );
	objMenu.Append ( CyWxEditOperationDialog::kDeleteAttribution,
					 CyGetText::getInstance ( ).getText ( "CyWxEditOperationDialog.onRightClickGrid.DeleteAttribution" ) );
	objMenu.Connect (
		wxEVT_COMMAND_MENU_SELECTED,
		( wxObjectEventFunction ) &CyWxEditOperationDialog::onPopupRightClickGrid,
		NULL,
		this );

	this->PopupMenu ( &objMenu );

	objMenu.Disconnect (
		wxEVT_COMMAND_MENU_SELECTED,
		( wxObjectEventFunction ) &CyWxEditOperationDialog::onPopupRightClickGrid,
		NULL,
		this );
}

/* ---------------------------------------------------------------------------- */

void CyWxEditOperationDialog::onRightClickLabel ( wxGridEvent& event )
{
	m_iCurrentAttributionRow = event.GetRow ( );
	wxMenu objMenu;

	objMenu.Append ( CyWxEditOperationDialog::kAddAttribution,
					 CyGetText::getInstance ( ).getText ( "CyWxEditOperationDialog.onRightClickLabel.AddAttribution" ) );
	objMenu.Connect (
		wxEVT_COMMAND_MENU_SELECTED,
		( wxObjectEventFunction ) &CyWxEditOperationDialog::onPopupRightClickLabel,
		NULL,
		this );

	this->PopupMenu ( &objMenu );

	objMenu.Disconnect (
		wxEVT_COMMAND_MENU_SELECTED,
		( wxObjectEventFunction ) &CyWxEditOperationDialog::onPopupRightClickLabel,
		NULL,
		this );
}

/* ---------------------------------------------------------------------------- */

void CyWxEditOperationDialog::onPopupRightClickGrid ( wxCommandEvent& event )
{
	switch ( event.GetId ( ) )
	{
	case CyWxEditOperationDialog::kEditAttribution:
		this->editAttribution ( );
		break;
	case CyWxEditOperationDialog::kAddAttribution:
		this->addAttribution ( );
		break;
	case CyWxEditOperationDialog::kDeleteAttribution:
		this->deleteAttribution ( );
		break;
	default:
		break;
	}
}

/* ---------------------------------------------------------------------------- */

void CyWxEditOperationDialog::onPopupRightClickLabel ( wxCommandEvent& event )
{
	switch ( event.GetId ( ) )
	{
	case CyWxEditOperationDialog::kAddAttribution:
		this->addAttribution ( );
		break;
	default:
		break;
	}
}

/* ---------------------------------------------------------------------------- */

void CyWxEditOperationDialog::addAttribution ( )
{
	// a vector with empty values except for the amount is created
	CyQueryResult::CyQueryResultValuesRow newRow;
	this->m_pOperationsSqlManager->createNewAttributionRow ( newRow );

	// the amount is extracted from the control...
	double dOperationAttributionAmount = this->m_dAmount;
	this->m_pAmountCtrl->GetValue ( ).ToCDouble ( &dOperationAttributionAmount );
	long long lOperationAttributionAmount = CyCurrencyConverter::toLongLong ( dOperationAttributionAmount );

	// ... and the amount of the existing attributions removed from the operation amount
	CyQueryResult::const_iterator OperationsAttributionsIterator;
	for ( OperationsAttributionsIterator = this->m_pOperationsSqlManager->getOperationsAttributionsQueryResult ( ).begin ( );
		  OperationsAttributionsIterator != this->m_pOperationsSqlManager->getOperationsAttributionsQueryResult ( ).end ( );
		  ++ OperationsAttributionsIterator )
	{
		lOperationAttributionAmount -=  
			OperationsAttributionsIterator->at ( CyOperationsAttributionsSqlBuilder::kAttributionOperationAmount )->get ( CyLongValue::m_lDummyValue );		
	}

	newRow.at ( CyOperationsAttributionsSqlBuilder::kAttributionOperationAmount )->set ( lOperationAttributionAmount );

	// a dialog for editing the attribution is show
	CyWxEditOperationAttributionDialog* pEditOperationAttributionDialog = new CyWxEditOperationAttributionDialog (
		newRow,
		this,
		CyGetText::getInstance ( ).getText ( "CyWxEditOperationDialog.AddAttribution.Add" ) );
	if ( wxID_OK == pEditOperationAttributionDialog->ShowModal ( ) )
	{
		// the user have clicked on the ok button. A new row is added to the operation attributions query result with the values given by the user
		this->m_bAttributionModified = true;
		this->m_pOperationsSqlManager->getOperationsAttributionsQueryResult ( ).push_back ( newRow );
		// and a new row is added to the attribution grid
		this->m_pAttributionsGrid->AppendRows ( 1 );
		int iAddedRowNumber = this->m_pAttributionsGrid->GetNumberRows ( ) - 1;
		this->m_pAttributionsGrid->SetCellValue ( 
			iAddedRowNumber,
			0, 
			newRow.at ( CyOperationsAttributionsSqlBuilder::kAttributionGroupDescription )->getAsString ( ) );
		this->m_pAttributionsGrid->SetCellValue ( 
			iAddedRowNumber, 
			1, 
			newRow.at ( CyOperationsAttributionsSqlBuilder::kAttributionDescription )->getAsString ( ) );
		this->m_pAttributionsGrid->SetCellValue ( 
			iAddedRowNumber, 
			2, 
			newRow.at ( CyOperationsAttributionsSqlBuilder::kAttributionOperationAmount )->getAsString ( ) );
	}
	else
	{
		// the user have clicked on the cancel button. Memory cleaning
		newRow.clear ( );
	}

	pEditOperationAttributionDialog->Destroy ( );
}

/* ---------------------------------------------------------------------------- */

void CyWxEditOperationDialog::editAttribution ( )
{
	CyWxEditOperationAttributionDialog* pEditOperationAttributionDialog = new CyWxEditOperationAttributionDialog (
		this->m_pOperationsSqlManager->getOperationsAttributionsQueryResult ( ).at ( static_cast < size_t > ( m_iCurrentAttributionRow ) ),
		this,
		CyGetText::getInstance ( ).getText ( "CyWxEditOperationDialog.onPopupRightClickGrid.Edit" ) );
	if ( wxID_OK == pEditOperationAttributionDialog->ShowModal ( ) )
	{
		this->m_pAttributionsGrid->SetCellValue ( 
			m_iCurrentAttributionRow,
			0, 
			this->m_pOperationsSqlManager->getOperationsAttributionsQueryResult ( ).at ( 
				static_cast < size_t > ( m_iCurrentAttributionRow ) ).at ( CyOperationsAttributionsSqlBuilder::kAttributionGroupDescription )->getAsString ( ) );
		this->m_pAttributionsGrid->SetCellValue ( 
			m_iCurrentAttributionRow,
			1, 
			this->m_pOperationsSqlManager->getOperationsAttributionsQueryResult ( ).at ( 
				static_cast < size_t > ( m_iCurrentAttributionRow ) ).at ( CyOperationsAttributionsSqlBuilder::kAttributionDescription )->getAsString ( ) );
		this->m_pAttributionsGrid->SetCellValue ( 
			m_iCurrentAttributionRow, 
			2, 
			this->m_pOperationsSqlManager->getOperationsAttributionsQueryResult ( ).at ( 
				static_cast < size_t > ( m_iCurrentAttributionRow ) ).at ( CyOperationsAttributionsSqlBuilder::kAttributionOperationAmount )->getAsString ( ) );
	}
	pEditOperationAttributionDialog->Destroy ( );
}

/* ---------------------------------------------------------------------------- */

void CyWxEditOperationDialog::deleteAttribution ( )
{
	wxMessageDialog* pConfirmDialog = new wxMessageDialog (
		this,
		CyGetText::getInstance ( ).getText ( "CyWxEditOperationDialog.deleteAttribution.ComfirmText" ),
		CyGetText::getInstance ( ).getText ( "CyWxEditOperationDialog.deleteAttribution.ComfirmCaption" ),
		wxOK | wxCANCEL | wxCANCEL_DEFAULT | wxICON_EXCLAMATION | wxCENTRE );

	if ( wxID_OK == pConfirmDialog->ShowModal ( ) )
	{
		this->m_bAttributionModified = true;
		this->m_pOperationsSqlManager->getOperationsAttributionsQueryResult ( ).erase ( this->m_pOperationsSqlManager->getOperationsAttributionsQueryResult ( ).begin ( ) + this->m_iCurrentAttributionRow );
		this->m_pAttributionsGrid->DeleteRows ( this->m_iCurrentAttributionRow , 1 );
	}

	pConfirmDialog->Destroy ( );
}

/* ---------------------------------------------------------------------------- */

const wxString CyWxEditOperationDialog::getOperationDate ( ) const
{
	return this->m_pOperationDateCtrl->GetValue ( ).Format ( wxString ( "%Y-%m-%d" ) );
}

/* ---------------------------------------------------------------------------- */

const wxString CyWxEditOperationDialog::getValueDate ( ) const
{
	return this->m_pValueDateCtrl->GetValue ( ).Format ( wxString ( "%Y-%m-%d" ) );
}

/* ---------------------------------------------------------------------------- */

const wxString CyWxEditOperationDialog::getBudgetDate ( ) const
{
	return this->m_pBudgetDateCtrl->GetValue ( ).Format ( wxString ( "%Y-%m-%d" ) );
}

/* ---------------------------------------------------------------------------- */

long long CyWxEditOperationDialog::getAmount ( ) const
{
	return CyCurrencyConverter::toLongLong ( this->m_dAmount );
}

/* ---------------------------------------------------------------------------- */

bool CyWxEditOperationDialog::hasOperationAttributions ( ) const
{
	return ( 0 != this->m_pOperationsSqlManager->getOperationsAttributionsQueryResult ( ).size ( ) );
}

/* ---------------------------------------------------------------------------- */

bool CyWxEditOperationDialog::hasOperationDetails ( ) const
{
	return ! this->m_pDetailsCtrl->GetValue ( ).empty ( );
}

/* ---------------------------------------------------------------------------- */

bool CyWxEditOperationDialog::hasDescription ( ) const
{
	return ! this->m_pDescriptionCtrl->GetValue ( ).empty ( );
}

/* ---------------------------------------------------------------------------- */

bool CyWxEditOperationDialog::canAccountBeImported ( ) const
{
	return this->m_bAccountCanBeImported;
}

/* ---------------------------------------------------------------------------- */

const wxString CyWxEditOperationDialog:: getAccountNumber ( ) const
{
	return this->m_strAccountNumber;
}

/* ---------------------------------------------------------------------------- */

const wxString CyWxEditOperationDialog::getDescription ( ) const
{
	return this->m_pDescriptionCtrl->GetValue ( );
}

/* ---------------------------------------------------------------------------- */

bool CyWxEditOperationDialog::isAttributionModified ( )const
{
	return this->m_bAttributionModified;
}

/* ---------------------------------------------------------------------------- */

int CyWxEditOperationDialog::ShowModal ( )
{
	int iReturnCode =  wxDialog::ShowModal ( );

	if ( wxID_OK == iReturnCode )
	{
		this->m_pOperationsSqlManager->getRow ( )->at ( CyOperationsSqlBuilder::kOperationDescription )->set ( this->getDescription ( ) );
		this->m_pOperationsSqlManager->getRow ( )->at ( CyOperationsSqlBuilder::kOperationDate )->set ( this->getOperationDate ( ) );
		this->m_pOperationsSqlManager->getRow ( )->at ( CyOperationsSqlBuilder::kOperationValueDate )->set ( this->getValueDate ( ) );
		this->m_pOperationsSqlManager->getRow ( )->at ( CyOperationsSqlBuilder::kOperationAttributionDate )->set ( this->getBudgetDate ( ) );
		this->m_pOperationsSqlManager->getRow ( )->at ( CyOperationsSqlBuilder::kOperationAmount )->set ( this->getAmount ( ) );
		this->m_pOperationsSqlManager->getRow ( )->at ( CyOperationsSqlBuilder::kOperationHaveNote )->set ( this->getDescription ( ).empty ( ) ? CyEnum::kNo : CyEnum::kYes );
		this->m_pOperationsSqlManager->getRow ( )->at ( CyOperationsSqlBuilder::kOperationHaveDetails )->set ( this->hasOperationDetails ( ) ? CyEnum::kYes : CyEnum::kNo );
		this->m_pOperationsSqlManager->getRow ( )->at ( CyOperationsSqlBuilder::kOperationHaveAttribution )->set ( this->hasOperationAttributions ( ) ? CyEnum::kYes : CyEnum::kNo );
	}

	return iReturnCode;
}

/* ---------------------------------------------------------------------------- */

