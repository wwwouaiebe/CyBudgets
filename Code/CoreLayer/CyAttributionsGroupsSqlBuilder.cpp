/* ---------------------------------------------------------------------------- */
//! CyAttributionsGroupsSqlBuilder.cpp
/* ---------------------------------------------------------------------------- */
//!
//! \file CyAttributionsGroupsSqlBuilder.cpp
//! \brief definition file for class CyAttributionsGroupsSqlBuilder
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

#include "CoreLayer/CyAttributionsGroupsSqlBuilder.h"
#include "DataLayer/CyLongValue.h"
#include "DataLayer/CyStringValue.h"
#include "UtilitiesLayer/CyEnum.h"
#include "UtilitiesLayer/CyGetText.h"

/* ---------------------------------------------------------------------------- */

CyAttributionsGroupsSqlBuilder::CyAttributionsGroupsSqlBuilder ( )
{
}

/* ---------------------------------------------------------------------------- */

CyAttributionsGroupsSqlBuilder::~CyAttributionsGroupsSqlBuilder ( )
{
}

/* ---------------------------------------------------------------------------- */

wxString CyAttributionsGroupsSqlBuilder::getDialogTitle ( ) const
{
	return CyGetText::getInstance ( ).getText ( "CyAttributionsGroupsSqlBuilder.getDialogTitle.GroupsTitle" );
}

/* ---------------------------------------------------------------------------- */

wxString CyAttributionsGroupsSqlBuilder::getDeleteSql ( long long lObjId ) const
{
	//
	//	strDeleteSql =
	//
	//	DELETE 
	//	FROM 
	//		AttributionsGroups 
	//	WHERE 
	//		objId = 10 ;
	//

	wxString strDeleteSql = wxEmptyString;

	strDeleteSql 
		<< wxString ( "DELETE FROM AttributionsGroups WHERE objId = ") 
		<< lObjId
		<< wxString ( " ;" );

	return strDeleteSql;
}

/* ---------------------------------------------------------------------------- */

 wxString CyAttributionsGroupsSqlBuilder::getInsertSql ( const CyQueryResult::CyQueryResultValuesRow& newRow ) const
{
	//
	//	strInsertSql =
	//
	//	INSERT INTO 
	//		AttributionsGroups 
	//		( 
	//			ObjId, 
	//			GroupDescription
	//		) 
	//		VALUES 
	//		( 
	//			( SELECT IFNULL ( MAX ( ObjId ), -1) + 1 FROM AttributionsGroups ),
	//			"Vêtements"
	//		);
	//

	wxString strInsertSql = wxEmptyString;

	strInsertSql
		<< wxString ( "INSERT INTO AttributionsGroups ( ObjId, GroupDescription ) " )
		<< wxString ( "VALUES ( ( SELECT IFNULL ( MAX ( ObjId ), -1) + 1 FROM AttributionsGroups ), \"" )
		<< newRow.at ( CyAttributionsGroupsSqlBuilder::kGroupDescription )->get ( CyStringValue::m_strDummyValue )
		<< wxString ( "\");");

	return strInsertSql;
}

/* ---------------------------------------------------------------------------- */

void CyAttributionsGroupsSqlBuilder::createRow ( CyQueryResult::CyQueryResultValuesRow& newRow ) const
{
	wxString strStringFormat;

	// AttributionsGroups ObjId...
	strStringFormat
		<< CyStartFormat 
		<< CyFormatHidden;
	CyLongValue* pObjId = new CyLongValue;
	pObjId->set ( CyEnum::kInvalidObjId, strStringFormat );
	newRow.push_back  ( pObjId );

	// ...AttributionsGroups Description
	strStringFormat.clear ( );
	strStringFormat
		<< CyStartFormat 
		<< CyFormatString;
	CyStringValue* pBudgetDescription = new CyStringValue;
	pBudgetDescription->set ( wxString ( "" ), strStringFormat );
	newRow.push_back ( pBudgetDescription );
}

/* ---------------------------------------------------------------------------- */

wxString CyAttributionsGroupsSqlBuilder::getSelectSql ( ) const
{
	//
	//	strSelectSql =
	//
	//	SELECT 
	//		"➻∅" AS ➻, 
	//		g.ObjId, 
	//		"➻α" AS ➻, 
	//		g.GroupDescription AS "Groupe" 
	//	FROM AttributionsGroups g 
	//	ORDER BY g.GroupDescription;
	//

	wxString strSelectSql = wxEmptyString;

	strSelectSql
		<< wxString ( "SELECT " )
		<< this->getFieldSql ( wxString ( "g.ObjId" ),wxEmptyString, CyFormatHidden )
		<<this->getFieldSql ( wxString ( "g.GroupDescription" ), CyGetText::getInstance ( ).getText ( "CyAttributionsGroupsSqlBuilder.getSelectSql.GroupDescription" ), CyFormatString, true )
		<< wxString ( "FROM AttributionsGroups g ORDER BY g.GroupDescription;" );

	return strSelectSql;
}

/* ---------------------------------------------------------------------------- */

wxString CyAttributionsGroupsSqlBuilder::getUpdateSql ( const CyQueryResult::CyQueryResultValuesRow& newRow ) const
{
//
//	strUpdateSql =
//
//	UPDATE 
//		AttributionsGroups 
//	SET 
//		GroupDescription = "Assurances" 
//	WHERE 
//		ObjId = 0;
//

	wxString strUpdateSql = wxEmptyString;

	strUpdateSql 
		<< wxString ( "UPDATE AttributionsGroups SET GroupDescription = \"" )
		<< newRow.at ( CyAttributionsGroupsSqlBuilder::kGroupDescription )->get ( CyStringValue::m_strDummyValue )
		<< wxString ( "\" WHERE ObjId = " )
		<< newRow.at ( CyAttributionsGroupsSqlBuilder::kGroupObjId )->get ( CyLongValue::m_lDummyValue )
		<< wxString ( ";" );

	return strUpdateSql;
}

/* ---------------------------------------------------------------------------- */

int CyAttributionsGroupsSqlBuilder::getHiddenColumns ( ) const
{
	return 1;
}

/* ---------------------------------------------------------------------------- */
