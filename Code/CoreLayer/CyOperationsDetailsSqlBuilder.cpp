/* ---------------------------------------------------------------------------- */
//! CyOperationsDetailsSqlBuilder.cpp
/* ---------------------------------------------------------------------------- */
//!
//! \file CyOperationsDetailsSqlBuilder.cpp
//! \brief definition file for class CyOperationsDetailsSqlBuilder
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

#include "CoreLayer/CyOperationsDetailsSqlBuilder.h"
#include "UtilitiesLayer/CyEnum.h"

/* ---------------------------------------------------------------------------- */

CyOperationsDetailsSqlBuilder::CyOperationsDetailsSqlBuilder ( long long lOperationObjId ) :
	m_lOperationObjId ( lOperationObjId )
{
}

/* ---------------------------------------------------------------------------- */

CyOperationsDetailsSqlBuilder::~CyOperationsDetailsSqlBuilder ( )
{
}

/* ---------------------------------------------------------------------------- */

wxString CyOperationsDetailsSqlBuilder::getDialogTitle ( ) const
{
	return wxEmptyString;
}

/* ---------------------------------------------------------------------------- */

wxString CyOperationsDetailsSqlBuilder::getDeleteSql ( long long lOperationObjId ) const
{
	//
	//	strDeleteSql =
	//
	//	DELETE 
	//	FROM 
	//		OperationsDetails 
	//	WHERE 
	//		OperationObjId = 10;
	//

	wxString strDeleteSql = wxEmptyString;

	strDeleteSql
		<< wxString ( "DELETE FROM OperationsDetails WHERE OperationObjId = " )
		<< lOperationObjId
		<< wxString ( ";");

	return strDeleteSql;
}

/* ---------------------------------------------------------------------------- */

 wxString CyOperationsDetailsSqlBuilder::getInsertSql (  const CyQueryResult::CyQueryResultValuesRow& /*newRow*/ ) const
{
	return wxEmptyString;
}

/* ---------------------------------------------------------------------------- */

void CyOperationsDetailsSqlBuilder::createRow ( CyQueryResult::CyQueryResultValuesRow& /*newRow*/ ) const
{
}

/* ---------------------------------------------------------------------------- */

wxString CyOperationsDetailsSqlBuilder::getSelectSql () const
{
	//
	//	strSelectSql =
	//
	//	SELECT 
	//		od.ObjId, 
	//		od.OperationObjId, 
	//		od.Detail 
	//	FROM 
	//		OperationsDetails od 
	//	WHERE 
	//		od.OperationObjId = 4220 ;
	//

	wxString strSelectSql = wxEmptyString;

	if ( CyEnum::kInvalidObjId != this->m_lOperationObjId )
	{
		strSelectSql
			<< wxString ( "SELECT od.ObjId, od.OperationObjId, od.Detail FROM OperationsDetails od WHERE od.OperationObjId = ")
			<< this->m_lOperationObjId
			<< wxString ( " ORDER BY od.ObjId;" );
	}

	return strSelectSql;
}

/* ---------------------------------------------------------------------------- */

wxString CyOperationsDetailsSqlBuilder::getUpdateSql ( const CyQueryResult::CyQueryResultValuesRow& ) const
{
	return wxEmptyString;
}

/* ---------------------------------------------------------------------------- */

int CyOperationsDetailsSqlBuilder::getHiddenColumns ( ) const
{
	return 2;
}

/* ---------------------------------------------------------------------------- */
