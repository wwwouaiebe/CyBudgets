/* ---------------------------------------------------------------------------- */
//! CyWxShowRequestBudgetsMediator.cpp
/* ---------------------------------------------------------------------------- */
//!
//! \file CyWxShowRequestBudgetsMediator.cpp
//! \brief definition file for class CyWxShowRequestBudgetsMediator
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

#include "UserInterfaceLayer/CyWxBudgetsApp.h"
#include "UserInterfaceLayer/CyWxBudgetsFrame.h"
#include "UserInterfaceLayer/CyWxShowRequestDialog.h"
#include "UserInterfaceLayer/CyWxShowRequestBudgetsMediator.h"
#include "CoreLayer/CyBudgetsSqlBuilder.h"
#include "DataLayer/CyLongValue.h"
#include "DataLayer/CyStringValue.h"
#include "UtilitiesLayer/CyGetText.h"

/* ---------------------------------------------------------------------------- */

CyWxShowRequestBudgetsMediator::CyWxShowRequestBudgetsMediator ( CySqlBuilder* pSqlBuilder ):
CyWxShowRequestMediator ( pSqlBuilder )
{
}

/* ---------------------------------------------------------------------------- */

CyWxShowRequestBudgetsMediator::~CyWxShowRequestBudgetsMediator ( )
{
}

/* ---------------------------------------------------------------------------- */

void CyWxShowRequestBudgetsMediator::onDoubleLeftClickGrid ( )
{
	this->onEdit ( );
}

/* ---------------------------------------------------------------------------- */

void CyWxShowRequestBudgetsMediator::onDoubleLeftClickLabel ( )
{
	this->onAdd ( );
}

/* ---------------------------------------------------------------------------- */

bool CyWxShowRequestBudgetsMediator::addPopupItems ( wxMenu& objMenu)
{
	objMenu.Append ( CyWxShowRequestBudgetsMediator::kEdit,
					 CyGetText::getInstance ( ).getText ( "CyWxShowRequestBudgetsMediator.addPopupItems.Edit" ) );
	objMenu.Append ( CyWxShowRequestBudgetsMediator::kAdd,
					 CyGetText::getInstance ( ).getText ( "CyWxShowRequestBudgetsMediator.addPopupItems.Add" ) );
	objMenu.Append ( CyWxShowRequestBudgetsMediator::kDelete,
					 CyGetText::getInstance ( ).getText ( "CyWxShowRequestBudgetsMediator.addPopupItems.Delete" ) );

	return true;
}

/* ---------------------------------------------------------------------------- */

void CyWxShowRequestBudgetsMediator::onPopupRightClickGrid ( wxCommandEvent& event)
{
	switch ( event.GetId ( ) )
	{
	case CyWxShowRequestBudgetsMediator::kAdd:
		this->onAdd ( );
		break;
	case CyWxShowRequestBudgetsMediator::kDelete:
		this->onDelete ( );
		break;
	case CyWxShowRequestBudgetsMediator::kEdit:
		this->onEdit ( );
		break;
	default:
		break;
	}
}

/* ---------------------------------------------------------------------------- */

void CyWxShowRequestBudgetsMediator::onAdd ( )
{
	CyQueryResult::CyQueryResultValuesRow newRow;
	this->m_pSqlBuilder->createRow ( newRow );
	// a entry text dialog box is created...
	wxTextEntryDialog* pAddBudgetDialog = new wxTextEntryDialog 	( 	
		NULL,//this->m_pWxShowRequestDialog ,
		CyGetText::getInstance ( ).getText ( "CyWxShowRequestBudgetsMediator.onAdd.Message" ),
		CyGetText::getInstance ( ).getText ( "CyWxShowRequestBudgetsMediator.onAdd.Caption" ) );
	if ( wxID_OK == pAddBudgetDialog->ShowModal ( ) )
	{
		newRow.at ( CyBudgetsSqlBuilder::kBudgetDescription )->set ( pAddBudgetDialog->GetValue ( ) );
		if ( this->m_pSqlBuilder->doInsert ( newRow ) )
		{
			// update of the grid
			this->m_pWxShowRequestDialog->refreshGrid ( );
			// update of the combo box in the main frame
			wxGetApp ( ).getBudgetsFrame ( )->UpdateBudgets ( );
		}
		else
		{
			// Error message...
			wxMessageDialog* pErrorDialog = new wxMessageDialog (
				this->m_pWxShowRequestDialog,
				wxString ( "CyWxShowRequestBudgetsMediator.onAdd.FailedText" ), 
				wxString ( "CyWxShowRequestBudgetsMediator.onAdd.FailedCaption" ),
				wxOK | wxICON_EXCLAMATION | wxCENTRE );
			pErrorDialog->ShowModal ( );
			pErrorDialog->Destroy ( );
		}
	}
	newRow.clear ( );
	pAddBudgetDialog->Destroy ( );
}

/* ---------------------------------------------------------------------------- */

void CyWxShowRequestBudgetsMediator::onDelete ( )
{
	wxMessageDialog* pWarningDialog = new wxMessageDialog (
		NULL,
		CyGetText::getInstance ( ).getText ( "CyWxShowRequestBudgetsMediator.onDelete.DeleteWarningText" ), 
		CyGetText::getInstance ( ).getText ( "CyWxShowRequestBudgetsMediator.onDelete.DeleteWarningCaption" ),
		wxOK | wxCANCEL | wxCANCEL_DEFAULT | wxICON_QUESTION | wxCENTRE );
	if ( wxID_OK == pWarningDialog->ShowModal ( ) )
	{
		if ( this->m_pSqlBuilder->doDelete ( this->m_pWxShowRequestDialog->getCurrentRow ( ).at ( CyBudgetsSqlBuilder::kBudgetObjId )->get ( CyLongValue::m_lDummyValue ) ) )
		{
			this->m_pWxShowRequestDialog->refreshGrid ( );
			// update of the combo box in the main frame
			wxGetApp ( ).getBudgetsFrame ( )->UpdateBudgets ( );
		}
		else
		{
			// Error message...
			wxMessageDialog* pErrorDialog = new wxMessageDialog (
				this->m_pWxShowRequestDialog,
				wxString ( "CyWxShowRequestBudgetsMediator.onDelete.FailedText" ), 
				wxString ( "CyWxShowRequestBudgetsMediator.onDelete.FailedCaption" ),
				wxOK | wxICON_EXCLAMATION | wxCENTRE );
			pErrorDialog->ShowModal ( );
			pErrorDialog->Destroy ( );
		}
	}
	pWarningDialog->Destroy ( );
}

/* ---------------------------------------------------------------------------- */

void CyWxShowRequestBudgetsMediator::onEdit ( )
{
	// a entry text dialog box is created...
	wxTextEntryDialog* pEditBudgetDialog = new wxTextEntryDialog 	( 	
		NULL,//this->m_pWxShowRequestDialog ,
		CyGetText::getInstance ( ).getText ( "CyWxShowRequestBudgetsMediator.onEdit.Message" ),
		CyGetText::getInstance ( ).getText ( "CyWxShowRequestBudgetsMediator.onEdit.Caption" ) );

	pEditBudgetDialog->SetValue ( this->m_pWxShowRequestDialog->getCurrentRow ( ).at ( CyBudgetsSqlBuilder::kBudgetDescription )->getAsString ( ));
	if ( wxID_OK == pEditBudgetDialog->ShowModal ( ) )
	{
		this->m_pWxShowRequestDialog->getCurrentRow ( ).at ( CyBudgetsSqlBuilder::kBudgetDescription )->set ( pEditBudgetDialog->GetValue ( ) );
		if ( this->m_pSqlBuilder->doUpdate ( this->m_pWxShowRequestDialog->getCurrentRow ( ) ) )
		{
			// update of the grid
			this->m_pWxShowRequestDialog->refreshCurrentRow ( );
			// update of the combo box in the main frame
			wxGetApp ( ).getBudgetsFrame ( )->UpdateBudgets ( );
		}
		else
		{
			// Error message...
			wxMessageDialog* pErrorDialog = new wxMessageDialog (
				this->m_pWxShowRequestDialog,
				wxString ( "CyWxShowRequestBudgetsMediator.onEdit.FailedText" ), 
				wxString ( "CyWxShowRequestBudgetsMediator.onEdit.FailedCaption" ),
				wxOK | wxICON_EXCLAMATION | wxCENTRE );
			pErrorDialog->ShowModal ( );
			pErrorDialog->Destroy ( );
		}
	}

	pEditBudgetDialog->Destroy ( );
}

/* ---------------------------------------------------------------------------- */

