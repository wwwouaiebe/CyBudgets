/* ---------------------------------------------------------------------------- */
//! CyWxShowRequestAccountsMediator.cpp
/* ---------------------------------------------------------------------------- */
//!
//! \file CyWxEditAccountDialog.cpp
//! \brief definition file for class CyWxShowRequestAccountsMediator
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
#include "UserInterfaceLayer/CyWxEditAccountDialog.h"
#include "UserInterfaceLayer/CyWxShowRequestAccountsMediator.h"
#include "UserInterfaceLayer/CyWxShowRequestDialog.h"
#include "CoreLayer/CyAccountsSqlBuilder.h"
#include "DataLayer/CyLongValue.h"
#include "UtilitiesLayer/CyGetText.h"

/* ---------------------------------------------------------------------------- */

CyWxShowRequestAccountsMediator::CyWxShowRequestAccountsMediator ( CySqlBuilder* pSqlBuilder ):
CyWxShowRequestMediator (pSqlBuilder )
{
}

/* ---------------------------------------------------------------------------- */

CyWxShowRequestAccountsMediator::~CyWxShowRequestAccountsMediator ( )
{
}

/* ---------------------------------------------------------------------------- */

bool CyWxShowRequestAccountsMediator::addPopupItems ( wxMenu& objMenu )
{
	objMenu.Append ( CyWxShowRequestAccountsMediator::kEdit, CyGetText::getInstance ( ).getText ( "CyWxShowRequestAccountsMediator.addPopupItems.Edit" ) );
	objMenu.Append ( CyWxShowRequestAccountsMediator::kAdd, CyGetText::getInstance ( ).getText ( "CyWxShowRequestAccountsMediator.addPopupItems.Add" ) );
	objMenu.Append ( CyWxShowRequestAccountsMediator::kDelete, CyGetText::getInstance ( ).getText ( "CyWxShowRequestAccountsMediator.addPopupItems.Delete" ) );

	return true;
}

/* ---------------------------------------------------------------------------- */

void CyWxShowRequestAccountsMediator::onPopupRightClickGrid ( wxCommandEvent& event )
{	
	switch ( event.GetId ( ) )
	{
	case CyWxShowRequestAccountsMediator::kAdd:
		this->onAdd ( );
		break;
	case CyWxShowRequestAccountsMediator::kDelete:
		this->onDelete ( );
		break;
	case CyWxShowRequestAccountsMediator::kEdit:
		this->onEdit ( );
		break;
	default:
		break;
	}
}

/* ---------------------------------------------------------------------------- */

void CyWxShowRequestAccountsMediator::onDoubleLeftClickGrid ( )
{
	this->onEdit ( );
}

/* ---------------------------------------------------------------------------- */

void CyWxShowRequestAccountsMediator::onDoubleLeftClickLabel ( )
{
	this->onAdd ( );
}

/* ---------------------------------------------------------------------------- */

void CyWxShowRequestAccountsMediator::onAdd ( )
{
	// a dummy row is created
	CyQueryResult::CyQueryResultValuesRow newRow;
	this->m_pSqlBuilder->createRow ( newRow );

	// a dialog box is created and displayed
	CyWxEditAccountDialog* pEditAccountDialog = new CyWxEditAccountDialog ( 
		newRow, 
		this->m_pWxShowRequestDialog, 
		CyGetText::getInstance ( ).getText ( "CyWxShowRequestAccountsMediator.onAdd.AddTitle" ) );
	if ( wxID_OK == pEditAccountDialog->ShowModal ( ))
	{
		if ( this->m_pSqlBuilder->doInsert ( newRow ) )
		{
			// and the grid is refreshed
			this->m_pWxShowRequestDialog->refreshGrid ( );
			// update of the combo box in the main frame
			wxGetApp ( ).getBudgetsFrame ( )->UpdateAccounts ( );
		}
		else
		{
			// Error message...
			wxMessageDialog* pErrorDialog = new wxMessageDialog (
				this->m_pWxShowRequestDialog,
				CyGetText::getInstance ( ).getText ( "CyWxShowRequestAccountsMediator.onAdd.FailedText" ), 
				CyGetText::getInstance ( ).getText ( "CyWxShowRequestAccountsMediator.onAdd.FailedCaption" ),
				wxOK | wxICON_EXCLAMATION | wxCENTRE );
			pErrorDialog->ShowModal ( );
			pErrorDialog->Destroy ( );
		}
	}

	newRow.clear ( );
}

/* ---------------------------------------------------------------------------- */

void CyWxShowRequestAccountsMediator::onDelete ( )
{
	wxMessageDialog* pWarningDialog = new wxMessageDialog (
		NULL,
		CyGetText::getInstance ( ).getText ( "CyWxShowRequestAccountsMediator.onDelete.DeleteWarningText" ), 
		CyGetText::getInstance ( ).getText ( "CyWxShowRequestAccountsMediator.onDelete.DeleteWarningCaption" ),
		wxOK | wxCANCEL | wxCANCEL_DEFAULT | wxICON_QUESTION | wxCENTRE );
	if ( wxID_OK == pWarningDialog->ShowModal ( ) )
	{
		if ( this->m_pSqlBuilder->doDelete ( this->m_pWxShowRequestDialog->getCurrentRow ( ).at ( CyAccountsSqlBuilder::kAccountObjId )->get ( CyLongValue::m_lDummyValue ) ) )
		{
			this->m_pWxShowRequestDialog->refreshGrid ( );
			// update of the combo box in the main frame
			wxGetApp ( ).getBudgetsFrame ( )->UpdateAccounts ( );
		}
		else
		{
			// Error message...
			wxMessageDialog* pErrorDialog = new wxMessageDialog (
				this->m_pWxShowRequestDialog,
				CyGetText::getInstance ( ).getText ( "CyWxShowRequestAccountsMediator.onDelete.FailedText" ), 
				CyGetText::getInstance ( ).getText ( "CyWxShowRequestAccountsMediator.onDelete.FailedCaption" ),
				wxOK | wxICON_EXCLAMATION | wxCENTRE );
			pErrorDialog->ShowModal ( );
			pErrorDialog->Destroy ( );
		}
	}
	pWarningDialog->Destroy ( );
}

/* ---------------------------------------------------------------------------- */

void CyWxShowRequestAccountsMediator::onEdit ( )
{
	// a dialog box is created and displayed
	CyWxEditAccountDialog* pEditAccountDialog = new CyWxEditAccountDialog ( 
		this->m_pWxShowRequestDialog->getCurrentRow ( ), 
		this->m_pWxShowRequestDialog, 
		CyGetText::getInstance ( ).getText ( "CyWxShowRequestAccountsMediator.onEdit.EditTitle" ) );
	if ( wxID_OK == pEditAccountDialog->ShowModal ( ))
	{
		if ( this->m_pSqlBuilder->doUpdate ( this->m_pWxShowRequestDialog->getCurrentRow ( ) ) )
		{
			// update of the grid
			this->m_pWxShowRequestDialog->refreshCurrentRow ( );

			// update of the combo box in the main frame
			wxGetApp ( ).getBudgetsFrame ( )->UpdateAccounts ( );
		}
		else
		{
			// Error message...
			wxMessageDialog* pErrorDialog = new wxMessageDialog (
				this->m_pWxShowRequestDialog,
				CyGetText::getInstance ( ).getText ( "CyWxShowRequestAccountsMediator.onEdit.FailedText" ), 
				CyGetText::getInstance ( ).getText ( "CyWxShowRequestAccountsMediator.onEdit.FailedCaption" ),
				wxOK | wxICON_EXCLAMATION | wxCENTRE );
			pErrorDialog->ShowModal ( );
			pErrorDialog->Destroy ( );
		}
	}
	pEditAccountDialog->Destroy ( );
}

/* ---------------------------------------------------------------------------- */

