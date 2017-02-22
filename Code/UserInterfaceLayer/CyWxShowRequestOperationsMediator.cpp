/* ---------------------------------------------------------------------------- */
//! CyWxShowRequestOperationsMediator.cpp
/* ---------------------------------------------------------------------------- */
//!
//! \file CyWxShowRequestOperationsMediator.cpp
//! \brief definition file for class CyWxShowRequestOperationsMediator
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

#include "UserInterfaceLayer/CyWxEditOperationDialog.h"
#include "UserInterfaceLayer/CyWxShowRequestDialog.h"
#include "UserInterfaceLayer/CyWxShowRequestOperationsMediator.h"
#include "CoreLayer/CyOperationsSqlManager.h"
#include "CoreLayer/CyOperationsSqlBuilder.h"
#include "CoreLayer/CyAccountsSqlBuilder.h"
#include "DataLayer/CyLongValue.h"
#include "DataLayer/CySqliteDb.h"
#include "DataLayer/CyStringValue.h"
#include "UtilitiesLayer/CyEnum.h"
#include "UtilitiesLayer/CyGetText.h"

/* ---------------------------------------------------------------------------- */

CyWxShowRequestOperationsMediator::CyWxShowRequestOperationsMediator ( CySqlBuilder* pSqlBuilder ):
CyWxShowRequestMediator ( pSqlBuilder )
{
}

/* ---------------------------------------------------------------------------- */

CyWxShowRequestOperationsMediator::~CyWxShowRequestOperationsMediator ( )
{
}

/* ---------------------------------------------------------------------------- */

void CyWxShowRequestOperationsMediator::onDoubleLeftClickGrid ( )
{
	this->onEdit ( );
}

/* ---------------------------------------------------------------------------- */

bool CyWxShowRequestOperationsMediator::addPopupItems ( wxMenu& objMenu )
{
	// we search if the account data are imported or not
	long long lAccountCanBeImported = this->m_pWxShowRequestDialog->getCurrentRow ( ).at ( CyOperationsSqlBuilder::kOperationAccountCanBeImported )->get ( CyLongValue::m_lDummyValue );

	// and items are added to the menu
	objMenu.Append ( CyWxShowRequestOperationsMediator::kEdit,
						CyGetText::getInstance ( ).getText ( "CyWxShowRequestOperationsMediator.addPopupItems.Edit" ) );
	if ( CyEnum::kNo == lAccountCanBeImported )
	{
		objMenu.Append ( CyWxShowRequestOperationsMediator::kAdd,
							CyGetText::getInstance ( ).getText ( "CyWxShowRequestOperationsMediator.addPopupItems.Add" ) );
		objMenu.Append ( CyWxShowRequestOperationsMediator::kDelete,
							CyGetText::getInstance ( ).getText ( "CyWxShowRequestOperationsMediator.addPopupItems.Delete" ) );
	}
	return true;
}

/* ---------------------------------------------------------------------------- */

void CyWxShowRequestOperationsMediator::onPopupRightClickGrid ( wxCommandEvent& event )
{	
	switch ( event.GetId ( ) )
	{
	case CyWxShowRequestOperationsMediator::kAdd:
		this->onAdd ( this->m_pWxShowRequestDialog->getCurrentRow ( ).at ( CyOperationsSqlBuilder::kOperationAccountNumber )->getAsString ( ) );
		break;
	case CyWxShowRequestOperationsMediator::kDelete:
		this->onDelete ( );
		break;
	case CyWxShowRequestOperationsMediator::kEdit:
		this->onEdit ( );
		break;
	default:
		break;
	}
}

/* ---------------------------------------------------------------------------- */

void CyWxShowRequestOperationsMediator::onDoubleLeftClickLabel ( )
{
	CyQueryResult objAccountsQueryResult;
	CyAccountsSqlBuilder objAccountsSqlBuilder;
	objAccountsSqlBuilder.doSelect ( objAccountsQueryResult );

	wxArrayString strAccountsArray;
	CyQueryResult::const_iterator accountIterator;
	for ( accountIterator = objAccountsQueryResult.begin ( ); accountIterator != objAccountsQueryResult.end ( ); ++ accountIterator)
	{
		if ( CyEnum::kNo == accountIterator->at ( CyAccountsSqlBuilder::kAccountImported )->get ( CyLongValue::m_lDummyValue ) )
		{
			strAccountsArray.Add ( accountIterator->at ( CyAccountsSqlBuilder::kAccountNumber )->getAsString ( ) );
		}
	}

	// We verify first that an account exists
	if ( 0 == strAccountsArray.size ( ) )
	{
		wxMessageDialog* pErrorDialog = new wxMessageDialog (
			this->m_pWxShowRequestDialog,
			CyGetText::getInstance ( ).getText ( "CyWxShowRequestOperationsMediator.onDoubleLeftClickLabel.ErrorText" ), 
			CyGetText::getInstance ( ).getText ( "CyWxShowRequestOperationsMediator.onDoubleLeftClickLabel.ErrorCaption" ),
			wxOK | wxICON_EXCLAMATION | wxCENTRE );
		pErrorDialog->ShowModal ( );
		pErrorDialog->Destroy ( );
		return;
	}

	wxSingleChoiceDialog* pSelectAccountChoiceDialog = new wxSingleChoiceDialog	( 
		this->m_pWxShowRequestDialog,
		CyGetText::getInstance ( ).getText ( "CyWxShowRequestOperationsMediator.onAdd.SelectAccountText" ),
		CyGetText::getInstance ( ).getText ( "CyWxShowRequestOperationsMediator.onAdd.SelectAccountCaption" ),
		strAccountsArray ) ;	

	if ( wxID_OK == pSelectAccountChoiceDialog->ShowModal ( ) )
	{
		this->onAdd ( pSelectAccountChoiceDialog->GetStringSelection ( ) );
	}

	pSelectAccountChoiceDialog->Destroy ( );
}

/* ---------------------------------------------------------------------------- */

void CyWxShowRequestOperationsMediator::onAdd ( wxString strAccountNumber )
{
	CyOperationsSqlManager objOperationsSqlManager ( this->m_pSqlBuilder, strAccountNumber );

	// a dialog is show
	CyWxEditOperationDialog* pEditOperationDialog = new CyWxEditOperationDialog ( 
		&objOperationsSqlManager,
		this->m_pWxShowRequestDialog,
		CyGetText::getInstance ( ).getText ( "CyWxShowRequestOperationsMediator.addOperation.Add" ) );
	if (wxID_OK == pEditOperationDialog->ShowModal ( ) )
	{
		if ( objOperationsSqlManager.doInsert ( ) )
		{
			this->m_pWxShowRequestDialog->refreshGrid ( );
		}
		else
		{
			// error dialog
			wxMessageDialog* pErrorDialog = new wxMessageDialog (
				this->m_pWxShowRequestDialog,
				CyGetText::getInstance ( ).getText ( "CyWxShowRequestOperationsMediator.onAdd.FailedText" ), 
				CyGetText::getInstance ( ).getText ( "CyWxShowRequestOperationsMediator.onAdd.FailedCaption" ),
				wxOK | wxICON_EXCLAMATION | wxCENTRE );
			pErrorDialog->ShowModal ( );
			pErrorDialog->Destroy ( );
		}
	}
	pEditOperationDialog->Destroy ( );
}

/* ---------------------------------------------------------------------------- */

void CyWxShowRequestOperationsMediator::onDelete ( )
{
	CyOperationsSqlManager objOperationsSqlManager ( this->m_pSqlBuilder, &( this->m_pWxShowRequestDialog->getCurrentRow ( ) ) );
	wxMessageDialog* pWarningDialog = new wxMessageDialog (
		NULL,
		CyGetText::getInstance ( ).getText ( "CyWxShowRequestOperationsMediator.onDelete.DeleteWarningText" ), 
		CyGetText::getInstance ( ).getText ( "CyWxShowRequestOperationsMediator.onDelete.DeleteWarningCaption" ),
		wxOK | wxCANCEL | wxCANCEL_DEFAULT | wxICON_QUESTION | wxCENTRE );
	if ( wxID_OK == pWarningDialog->ShowModal ( ) )
	{
		// Commit or Rollback
		if ( objOperationsSqlManager.doDelete ( ) )
		{
			// and the grid is refreshed
			this->m_pWxShowRequestDialog->refreshGrid ( );
		}
		else
		{
			wxMessageDialog* pErrorDialog = new wxMessageDialog (
				this->m_pWxShowRequestDialog,
				CyGetText::getInstance ( ).getText ( "CyWxShowRequestOperationsMediator.onDelete.FailedText" ), 
				CyGetText::getInstance ( ).getText ( "CyWxShowRequestOperationsMediator.onDelete.FailedCaption" ),
				wxOK | wxICON_EXCLAMATION | wxCENTRE );
			pErrorDialog->ShowModal ( );
			pErrorDialog->Destroy ( );

		}
	}

	pWarningDialog->Destroy ( );
}

/* ---------------------------------------------------------------------------- */

void CyWxShowRequestOperationsMediator::onEdit ( )
{
	CyOperationsSqlManager objOperationsSqlManager ( this->m_pSqlBuilder, &( this->m_pWxShowRequestDialog->getCurrentRow ( ) ) );

	// a dialog is show
	CyWxEditOperationDialog* pEditOperationDialog = new CyWxEditOperationDialog ( 
		&objOperationsSqlManager,
		this->m_pWxShowRequestDialog, 
		CyGetText::getInstance ( ).getText ( "CyWxShowRequestOperationsMediator.editOperation.Edit" ) );
	if (wxID_OK == pEditOperationDialog->ShowModal ( ) )
	{	
		if ( objOperationsSqlManager.doUpdate ( ) )
		{
			this->m_pWxShowRequestDialog->refreshCurrentRow ( );
		}
		else
		{
			// error message
			wxMessageDialog* pErrorDialog = new wxMessageDialog (
				this->m_pWxShowRequestDialog,
				CyGetText::getInstance ( ).getText ( "CyWxShowRequestOperationsMediator.onEdit.FailedText" ), 
				CyGetText::getInstance ( ).getText ( "CyWxShowRequestOperationsMediator.onEdit.FailedCaption" ),
				wxOK | wxICON_EXCLAMATION | wxCENTRE );
			pErrorDialog->ShowModal ( );
			pErrorDialog->Destroy ( );
		}
		
	}
	pEditOperationDialog->Destroy ( );
}

/* ---------------------------------------------------------------------------- */
