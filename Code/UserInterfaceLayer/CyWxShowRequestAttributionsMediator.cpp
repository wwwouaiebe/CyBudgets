/* ---------------------------------------------------------------------------- */
//! CyWxShowRequestAttributionsMediator.cpp
/* ---------------------------------------------------------------------------- */
//!
//! \file CyWxShowRequestAttributionsMediator.cpp
//! \brief definition file for class CyWxShowRequestAttributionsMediator
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
#include "UserInterfaceLayer/CyWxShowRequestAttributionsMediator.h"
#include "UserInterfaceLayer/CyWxShowRequestDialog.h"
#include "CoreLayer/CyAttributionsGroupsSqlBuilder.h"
#include "CoreLayer/CyBudgetsSqlBuilder.h"
#include "CoreLayer/CyAttributionsSqlBuilder.h"
#include "DataLayer/CyLongValue.h"
#include "UtilitiesLayer/CyGetText.h"

/* ---------------------------------------------------------------------------- */

CyWxShowRequestAttributionsMediator::CyWxShowRequestAttributionsMediator ( CySqlBuilder* pSqlBuilder ):
CyWxShowRequestMediator ( pSqlBuilder )
{
}

/* ---------------------------------------------------------------------------- */

CyWxShowRequestAttributionsMediator::~CyWxShowRequestAttributionsMediator ( )
{
}

/* ---------------------------------------------------------------------------- */

bool CyWxShowRequestAttributionsMediator::addPopupItems ( wxMenu& objMenu )
{
	objMenu.Append ( CyWxShowRequestAttributionsMediator::kEdit,
					 CyGetText::getInstance ( ).getText ( "CyWxShowRequestAttributionsMediator.addPopupItems.Edit" ) );
	objMenu.Append ( CyWxShowRequestAttributionsMediator::kAdd,
					 CyGetText::getInstance ( ).getText ( "CyWxShowRequestAttributionsMediator.addPopupItems.Add" ) );
	objMenu.Append ( CyWxShowRequestAttributionsMediator::kDelete,
					 CyGetText::getInstance ( ).getText ( "CyWxShowRequestAttributionsMediator.addPopupItems.Delete" ) );

	return true;
}

/* ---------------------------------------------------------------------------- */

void CyWxShowRequestAttributionsMediator::onPopupRightClickGrid ( wxCommandEvent& event )
{	
	switch ( event.GetId ( ) )
	{
	case CyWxShowRequestAttributionsMediator::kAdd:
		this->onAdd ( );
		break;
	case CyWxShowRequestAttributionsMediator::kDelete:
		this->onDelete ( );
		break;
	case CyWxShowRequestAttributionsMediator::kEdit:
		this->onEdit ( );
		break;
	default:
		break;
	}
}

/* ---------------------------------------------------------------------------- */

void CyWxShowRequestAttributionsMediator::onDoubleLeftClickGrid ( )
{
	this->onEdit ( );
}

/* ---------------------------------------------------------------------------- */

void CyWxShowRequestAttributionsMediator::onDoubleLeftClickLabel ( )
{
	bool bHaveBudgetAndGroup = false;
	{
		CyAttributionsGroupsSqlBuilder objAttributionsGroupsSqlBuilder;
		CyQueryResult objAttributionsGroupsQueryResult;
		objAttributionsGroupsSqlBuilder.doSelect ( objAttributionsGroupsQueryResult );

		CyBudgetsSqlBuilder objBudgetsSqlBuilder;
		CyQueryResult objBudgetsQueryResult;
		objBudgetsSqlBuilder.doSelect ( objBudgetsQueryResult );

		bHaveBudgetAndGroup = ( 0 < objAttributionsGroupsQueryResult.size ( ) ) && ( 0 < objBudgetsQueryResult.size ( ) );
	}
	
	if ( bHaveBudgetAndGroup )
	{
		this->onAdd ( );
	}
	else
	{
		wxMessageDialog* pErrorDialog = new wxMessageDialog (
			this->m_pWxShowRequestDialog,
			CyGetText::getInstance ( ).getText ( "CyWxShowRequestAttributionsMediator.onDoubleLeftClickLabel.ErrorText" ), 
			CyGetText::getInstance ( ).getText ( "CyWxShowRequestAttributionsMediator.onDoubleLeftClickLabel.ErrorCaption" ),
			wxOK | wxICON_EXCLAMATION | wxCENTRE );
		pErrorDialog->ShowModal ( );
		pErrorDialog->Destroy ( );
	}
}

/* ---------------------------------------------------------------------------- */

void CyWxShowRequestAttributionsMediator::onAdd ( )
{
	// An empty row is created
	CyQueryResult::CyQueryResultValuesRow newRow;
	this->m_pSqlBuilder->createRow ( newRow );

	// a dialog box is created and displayed
	CyWxEditAttributionDialog* pEditAttributionDialog = new CyWxEditAttributionDialog ( 
		newRow , 
		this->m_pWxShowRequestDialog, 
		CyGetText::getInstance ( ).getText ( "CyWxShowRequestAttributionsMediator.onAdd.Add" ) );
	if (wxID_OK == pEditAttributionDialog->ShowModal ( ) )
	{		
		if ( this->m_pSqlBuilder->doInsert ( newRow ) )
		{
			// update of the grid
			this->m_pWxShowRequestDialog->refreshGrid ( );
		}
		else
		{
			// Error message...
			wxMessageDialog* pErrorDialog = new wxMessageDialog (
				this->m_pWxShowRequestDialog,
				CyGetText::getInstance ( ).getText ( "CyWxShowRequestAttributionsMediator.onAdd.FailedText" ), 
				CyGetText::getInstance ( ).getText ( "CyWxShowRequestAttributionsMediator.onAdd.FailedCaption" ),
				wxOK | wxICON_EXCLAMATION | wxCENTRE );
			pErrorDialog->ShowModal ( );
			pErrorDialog->Destroy ( );
		}
 	}
}

/* ---------------------------------------------------------------------------- */

void CyWxShowRequestAttributionsMediator::onDelete ( )
{
	wxMessageDialog* pWarningDialog = new wxMessageDialog (
		NULL,
		CyGetText::getInstance ( ).getText ( "CyWxShowRequestAttributionsMediator.onDelete.DeleteWarningText" ), 
		CyGetText::getInstance ( ).getText ( "CyWxShowRequestAttributionsMediator.onDelete.DeleteWarningCaption" ),
		wxOK | wxCANCEL | wxCANCEL_DEFAULT | wxICON_QUESTION | wxCENTRE );
	if ( wxID_OK == pWarningDialog->ShowModal ( ) )
	{
		if ( this->m_pSqlBuilder->doDelete ( this->m_pWxShowRequestDialog->getCurrentRow ( ).at ( CyAttributionsSqlBuilder::kAttributionObjId )->get ( CyLongValue::m_lDummyValue ) ) )
		{
			this->m_pWxShowRequestDialog->refreshGrid ( );
		}
		else
		{
			// Error message...
			wxMessageDialog* pErrorDialog = new wxMessageDialog (
				this->m_pWxShowRequestDialog,
				CyGetText::getInstance ( ).getText ( "CyWxShowRequestAttributionsMediator.onDelete.FailedText" ), 
				CyGetText::getInstance ( ).getText ( "CyWxShowRequestAttributionsMediator.onDelete.FailedCaption" ),
				wxOK | wxICON_EXCLAMATION | wxCENTRE );
			pErrorDialog->ShowModal ( );
			pErrorDialog->Destroy ( );
		}
	}
	pWarningDialog->Destroy ( );
}

/* ---------------------------------------------------------------------------- */

void CyWxShowRequestAttributionsMediator::onEdit ( )
{
	// a dialog box is created and displayed
	CyWxEditAttributionDialog* pEditAttributionDialog = new CyWxEditAttributionDialog ( 
		this->m_pWxShowRequestDialog->getCurrentRow ( ), 
		this->m_pWxShowRequestDialog,
		CyGetText::getInstance ( ).getText ( "CyWxShowRequestAttributionsMediator.onEdit.DialogTitle" ) );
	if (wxID_OK == pEditAttributionDialog->ShowModal ( ) )
	{		
		if ( this->m_pSqlBuilder->doUpdate ( this->m_pWxShowRequestDialog->getCurrentRow ( ) ) )
		{
			// update of the grid
			this->m_pWxShowRequestDialog->refreshCurrentRow ( );
		}
		else
		{
			// Error message...
			wxMessageDialog* pErrorDialog = new wxMessageDialog (
				this->m_pWxShowRequestDialog,
				CyGetText::getInstance ( ).getText ( "CyWxShowRequestAttributionsMediator.onEdit.FailedText" ), 
				CyGetText::getInstance ( ).getText ( "CyWxShowRequestAttributionsMediator.onEdit.FailedCaption" ),
				wxOK | wxICON_EXCLAMATION | wxCENTRE );
			pErrorDialog->ShowModal ( );
			pErrorDialog->Destroy ( );
		}
	}
	pEditAttributionDialog->Destroy ( );
}

/* ---------------------------------------------------------------------------- */

