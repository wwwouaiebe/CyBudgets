/* ---------------------------------------------------------------------------- */
//! CyWxShowRequestAnalyseMediator.cpp
/* ---------------------------------------------------------------------------- */
//!
//! \file CyWxShowRequestAnalyseMediator.cpp
//! \brief definition file for class CyWxShowRequestAnalyseMediator
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

#include "UserInterfaceLayer/CyWxBudgetsFrame.h"
#include "UserInterfaceLayer/CyWxShowRequestAnalyseMediator.h"
#include "UserInterfaceLayer/CyWxShowRequestDialog.h"
#include "UserInterfaceLayer/CyWxShowRequestOperationsMediator.h"
#include "CoreLayer/CyOperationsSqlBuilder.h"
#include "CoreLayer/CyAnalyseSqlBuilder.h"
#include "DataLayer/CyValue.h"
#include "DataLayer/CyLongValue.h"
#include "UtilitiesLayer/CyGetText.h"

/* ---------------------------------------------------------------------------- */

CyWxShowRequestAnalyseMediator::CyWxShowRequestAnalyseMediator ( CySqlBuilder* pSqlBuilder ):
	CyWxShowRequestMediator ( pSqlBuilder )
{
}

/* ---------------------------------------------------------------------------- */

CyWxShowRequestAnalyseMediator::~CyWxShowRequestAnalyseMediator ( )
{
}

/* ---------------------------------------------------------------------------- */

bool CyWxShowRequestAnalyseMediator::addPopupItems ( wxMenu& objMenu )
{
	objMenu.Append ( CyWxShowRequestAnalyseMediator::kViewOperations,
					 CyGetText::getInstance ( ).getText ( "CyWxShowRequestAnalyseMediator.addPopupItems.ViewOperation" ) );

	return true;
}

/* ---------------------------------------------------------------------------- */

void CyWxShowRequestAnalyseMediator::onDoubleLeftClickGrid ( )
{
	this->onViewOperations ( );
}

/* ---------------------------------------------------------------------------- */

void CyWxShowRequestAnalyseMediator::onViewOperations ( )
{
	CyWxShowRequestDialog* pOperationsDialog = new CyWxShowRequestDialog ( 
		this->m_pWxShowRequestDialog,
		new CyWxShowRequestOperationsMediator ( 
			new CyOperationsSqlBuilder (
				this->m_pWxShowRequestDialog->getCurrentRow ( ),
				dynamic_cast < CyWxBudgetsFrame* > ( this->m_pWxShowRequestDialog->GetParent ( ) )->getStartDate ( ),
				dynamic_cast < CyWxBudgetsFrame* > ( this->m_pWxShowRequestDialog->GetParent ( ) )->getEndDate ( ) ) ) );
	pOperationsDialog->Show ( true );
}

/* ---------------------------------------------------------------------------- */

void CyWxShowRequestAnalyseMediator::onPopupRightClickGrid ( wxCommandEvent& event )
{	
	switch ( event.GetId ( ) )
	{
	case CyWxShowRequestAnalyseMediator::kViewOperations:
		this->onViewOperations ( );
		break;
	default:
		break;
	}
}

/* ---------------------------------------------------------------------------- */

