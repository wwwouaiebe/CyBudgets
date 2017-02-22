/* ---------------------------------------------------------------------------- */
//! CyWxShowRequestAttributionsGroupsMediator.cpp
/* ---------------------------------------------------------------------------- */
//!
//! \file CyWxShowRequestAttributionsGroupsMediator.cpp
//! \brief definition file for class CyWxShowRequestAttributionsGroupsMediator
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

#include "UserInterfaceLayer/CyWxShowRequestDialog.h"
#include "UserInterfaceLayer/CyWxShowRequestAttributionsGroupsMediator.h"
#include "CoreLayer/CyAttributionsGroupsSqlBuilder.h"
#include "DataLayer/CyLongValue.h"
#include "DataLayer/CyStringValue.h"
#include "UtilitiesLayer/CyGetText.h"

/* ---------------------------------------------------------------------------- */

CyWxShowRequestAttributionsGroupsMediator::CyWxShowRequestAttributionsGroupsMediator ( CySqlBuilder* pSqlBuilder ):
CyWxShowRequestMediator ( pSqlBuilder )
{
}

/* ---------------------------------------------------------------------------- */

CyWxShowRequestAttributionsGroupsMediator::~CyWxShowRequestAttributionsGroupsMediator ( )
{
}

/* ---------------------------------------------------------------------------- */

void CyWxShowRequestAttributionsGroupsMediator::onDoubleLeftClickGrid ( )
{
	this->onEdit ( );
}

/* ---------------------------------------------------------------------------- */

void CyWxShowRequestAttributionsGroupsMediator::onDoubleLeftClickLabel ( )
{
	this->onAdd ( );
}

/* ---------------------------------------------------------------------------- */

bool CyWxShowRequestAttributionsGroupsMediator::addPopupItems ( wxMenu& objMenu)
{
	objMenu.Append ( CyWxShowRequestAttributionsGroupsMediator::kEdit,
					 CyGetText::getInstance ( ).getText ( "CyWxShowRequestAttributionsGroupsMediator.addPopupItems.Edit" ) );
	objMenu.Append ( CyWxShowRequestAttributionsGroupsMediator::kAdd,
					 CyGetText::getInstance ( ).getText ( "CyWxShowRequestAttributionsGroupsMediator.addPopupItems.Add" ) );
	objMenu.Append ( CyWxShowRequestAttributionsGroupsMediator::kDelete,
					 CyGetText::getInstance ( ).getText ( "CyWxShowRequestAttributionsGroupsMediator.addPopupItems.Delete" ) );

	return true;
}

/* ---------------------------------------------------------------------------- */

void CyWxShowRequestAttributionsGroupsMediator::onPopupRightClickGrid ( wxCommandEvent& event)
{
	switch ( event.GetId ( ) )
	{
	case CyWxShowRequestAttributionsGroupsMediator::kAdd:
		this->onAdd ( );
		break;
	case CyWxShowRequestAttributionsGroupsMediator::kDelete:
		this->onDelete ( );
		break;
	case CyWxShowRequestAttributionsGroupsMediator::kEdit:
		this->onEdit ( );
		break;
	default:
		break;
	}
}

/* ---------------------------------------------------------------------------- */

void CyWxShowRequestAttributionsGroupsMediator::onAdd ( )
{
	CyQueryResult::CyQueryResultValuesRow newRow;
	this->m_pSqlBuilder->createRow ( newRow );
	// a entry text dialog box is created...
	wxTextEntryDialog* pAddAttributionGroupDialog = new wxTextEntryDialog 	( 	
		NULL,//this->m_pWxShowRequestDialog ,
		CyGetText::getInstance ( ).getText ( "CyWxShowRequestAttributionsGroupsMediator.onAdd.Message" ),
		CyGetText::getInstance ( ).getText ( "CyWxShowRequestAttributionsGroupsMediator.onAdd.Caption" ) );
	if ( wxID_OK == pAddAttributionGroupDialog->ShowModal ( ) )
	{
		newRow.at ( CyAttributionsGroupsSqlBuilder::kGroupDescription )->set ( pAddAttributionGroupDialog->GetValue ( ) );
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
				wxString ( "CyWxShowRequestAttributionsGroupsMediator.onAdd.FailedText" ), 
				wxString ( "CyWxShowRequestAttributionsGroupsMediator.onAdd.FailedCaption" ),
				wxOK | wxICON_EXCLAMATION | wxCENTRE );
			pErrorDialog->ShowModal ( );
			pErrorDialog->Destroy ( );
		}
	}
	newRow.clear ( );
	pAddAttributionGroupDialog->Destroy ( );
}

/* ---------------------------------------------------------------------------- */

void CyWxShowRequestAttributionsGroupsMediator::onDelete ( )
{
	wxMessageDialog* pWarningDialog = new wxMessageDialog (
		NULL,
		CyGetText::getInstance ( ).getText ( "CyWxShowRequestAttributionsGroupsMediator.onDelete.DeleteWarningText" ), 
		CyGetText::getInstance ( ).getText ( "CyWxShowRequestAttributionsGroupsMediator.onDelete.DeleteWarningCaption" ),
		wxOK | wxCANCEL | wxCANCEL_DEFAULT | wxICON_QUESTION | wxCENTRE );
	if ( wxID_OK == pWarningDialog->ShowModal ( ) )
	{
		if ( this->m_pSqlBuilder->doDelete ( this->m_pWxShowRequestDialog->getCurrentRow ( ).at ( CyAttributionsGroupsSqlBuilder::kGroupObjId)->get ( CyLongValue::m_lDummyValue ) ) )
		{
			this->m_pWxShowRequestDialog->refreshGrid ( );
		}
		else
		{
			// Error message...
			wxMessageDialog* pErrorDialog = new wxMessageDialog (
				this->m_pWxShowRequestDialog,
				wxString ( "CyWxShowRequestAttributionsGroupsMediator.onDelete.FailedText" ), 
				wxString ( "CyWxShowRequestAttributionsGroupsMediator.onDelete.FailedCaption" ),
				wxOK | wxICON_EXCLAMATION | wxCENTRE );
			pErrorDialog->ShowModal ( );
			pErrorDialog->Destroy ( );
		}
	}
	pWarningDialog->Destroy ( );
}

/* ---------------------------------------------------------------------------- */

void CyWxShowRequestAttributionsGroupsMediator::onEdit ( )
{
	// a entry text dialog box is created...
	wxTextEntryDialog* pEditAttributionGroupDialog = new wxTextEntryDialog 	( 	
		NULL,//this->m_pWxShowRequestDialog ,
		CyGetText::getInstance ( ).getText ( "CyWxShowRequestAttributionsGroupsMediator.onEdit.Message" ),
		CyGetText::getInstance ( ).getText ( "CyWxShowRequestAttributionsGroupsMediator.onEdit.Caption" ) );

	pEditAttributionGroupDialog->SetValue (
		this->m_pWxShowRequestDialog->getCurrentRow ( ).at ( CyAttributionsGroupsSqlBuilder::kGroupDescription )->getAsString ( ));
	if ( wxID_OK == pEditAttributionGroupDialog->ShowModal ( ) )
	{
		this->m_pWxShowRequestDialog->getCurrentRow ( ).at ( CyAttributionsGroupsSqlBuilder::kGroupDescription )->set ( pEditAttributionGroupDialog->GetValue ( ) );
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
				wxString ( "CyWxShowRequestAttributionsGroupsMediator.onEdit.FailedText" ), 
				wxString ( "CyWxShowRequestAttributionsGroupsMediator.onEdit.FailedCaption" ),
				wxOK | wxICON_EXCLAMATION | wxCENTRE );
			pErrorDialog->ShowModal ( );
			pErrorDialog->Destroy ( );
		}
	}

	pEditAttributionGroupDialog->Destroy ( );
}

/* ---------------------------------------------------------------------------- */

