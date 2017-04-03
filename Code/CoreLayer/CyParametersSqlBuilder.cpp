/* ---------------------------------------------------------------------------- */
//! CyParametersSqlBuilder.cpp
/* ---------------------------------------------------------------------------- */
//!
//! \file CyParametersSqlBuilder.cpp
//! \brief definition file for class CyParametersSqlBuilder
//!
/* ----------------------------------------------------------------------------

	contact: http://www.ouaie.be/

    This file is a part of the CyBudgets program

    Copyright ( C ) 2017 - Christian Guyette

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

#include "CoreLayer/CyParametersSqlBuilder.h"
#include "DataLayer/CySqliteDb.h"
#include "DataLayer/CyLongValue.h"
#include "DataLayer/CyStringValue.h"
#include "UtilitiesLayer/CyEnum.h"
#include "UtilitiesLayer/CyGetText.h"

/* ---------------------------------------------------------------------------- */

CyParametersSqlBuilder::CyParametersSqlBuilder ( ) :
	m_strWhereClause ( wxEmptyString )
{
}

/* ---------------------------------------------------------------------------- */

CyParametersSqlBuilder::CyParametersSqlBuilder ( const wxString& strParameterName ) :
	m_strWhereClause ( wxEmptyString )
{
	this->m_strWhereClause
		<< wxString ( " WHERE p.ParameterName = \"" )
		<< strParameterName
		<< wxString ( "\"" );
}

/* ---------------------------------------------------------------------------- */

CyParametersSqlBuilder::~CyParametersSqlBuilder ( )
{
}

/* ---------------------------------------------------------------------------- */

wxString CyParametersSqlBuilder::getDialogTitle ( ) const
{
	return wxEmptyString;
}

/* ---------------------------------------------------------------------------- */

wxString CyParametersSqlBuilder::getDeleteSql ( long long lObjId ) const
{
	//
	//	strDeleteSql =
	//
	//	DELETE 
	//	FROM 
	//		Parameters 
	//	WHERE 
	//		objId = 10;
	//

	wxString strDeleteSql = wxEmptyString;

	strDeleteSql
		<< wxString ( "DELETE FROM Parameters WHERE objId = ") 
		<< lObjId
		<< wxString ( ";" );

	return strDeleteSql;
}

/* ---------------------------------------------------------------------------- */

wxString CyParametersSqlBuilder::getInsertSql ( const CyQueryResult::CyQueryResultValuesRow& newRow ) const
{
	//
	//	strInsertSql =
	//
	//	INSERT INTO 
	//		Parameters 
	//		( 
	//			ObjId, 
	//			ParameterName, 
	//			TextValue, 
	//			IntegerValue
	//		) 
	//		VALUES 
	//		( 
	//			(SELECT IFNULL ( MAX ( ObjId ), -1) + 1 FROM Parameters ),
	//			"MyParameter",
	//			"xxxxxx",
	//			0
	//		);
	//


	wxString strIntegerValue = wxEmptyString;
	if ( newRow.at ( CyParametersSqlBuilder::kIntegerValue )->isNull ( ) )
	{
		strIntegerValue << wxString ( "NULL" );
	}
	else
	{
		strIntegerValue << newRow.at ( CyParametersSqlBuilder::kTextValue )->get ( CyLongValue::m_lDummyValue );
	}

	wxString strInsertSql = wxEmptyString;
	strInsertSql
		<< wxString ( "INSERT INTO Parameters ( ObjId, ParameterName, TextValue, IntegerValue ) " )
		<< wxString ( "VALUES ( (SELECT IFNULL ( MAX ( ObjId ), -1) + 1 FROM Accounts ), \"" )
		<< newRow.at ( CyParametersSqlBuilder::kParameterName )->get ( CyStringValue::m_strDummyValue )
		<< wxString ( "\", \"" )
		<< ( newRow.at ( CyParametersSqlBuilder::kTextValue )->isNull ( ) ? wxString ( "NULL" ) : newRow.at ( CyParametersSqlBuilder::kTextValue )->get ( CyStringValue::m_strDummyValue ) )
		<< wxString ( "\", " )
		<< strIntegerValue
		<< wxString ( ");" );

	return strInsertSql;
}

/* ---------------------------------------------------------------------------- */

void CyParametersSqlBuilder::createRow ( CyQueryResult::CyQueryResultValuesRow& newRow ) const
{
	wxString strStringFormat;

	// Parameter ObjId...
	strStringFormat
		<< CyStartFormat 
		<< CyFormatHidden;
	CyLongValue* pObjId = new CyLongValue;
	pObjId->set ( CyEnum::kInvalidObjId, strStringFormat );
	newRow.push_back  ( pObjId );

	// ... parameter name...
	strStringFormat.clear ( );
	strStringFormat
		<< CyStartFormat 
		<< CyFormatString;
	CyStringValue* pParameterName = new CyStringValue;
	pParameterName->set ( wxEmptyString, strStringFormat );
	newRow.push_back ( pParameterName );

	// ... text value
	CyStringValue* pTextValue = new CyStringValue;
	pTextValue->set ( wxEmptyString, strStringFormat );
	newRow.push_back ( pTextValue );

	// ... integer value....
	strStringFormat.clear ( );
	strStringFormat
		<< CyStartFormat 
		<< CyFormatInteger;
	CyLongValue* pIntegerValue = new CyLongValue;
	pIntegerValue->set ( CyLongValue::m_lDummyValue, strStringFormat );
	newRow.push_back ( pIntegerValue );
}

/* ---------------------------------------------------------------------------- */

wxString CyParametersSqlBuilder::getSelectSql ( ) const
{
	//
	//	strSelectSql =
	//
	//	SELECT 
	//		"➻∅" AS ➻, 
	//		p.ObjId, 
	//		"➻α" AS ➻, 
	//		p.ParameterName,
	//		"➻α" AS ➻,
	//		p.TextValue,
	//		"➻∅" AS ➻,
	//		p.IntegerValue
	//	FROM Parameters
	//	ORDER BY p.ParameterName, p.ObjId;
	//

	wxString strSelectSql = wxEmptyString;

	strSelectSql
		<< wxString ( "SELECT " )
		<< this->getFieldSql ( wxString ( "p.ObjId" ), wxEmptyString, CyFormatHidden )
		<< this->getFieldSql ( wxString ( "p.ParameterName" ), wxEmptyString, CyFormatString )
		<< this->getFieldSql ( wxString ( "p.TextValue"), wxEmptyString, CyFormatString )
		<< this->getFieldSql ( wxString ( "p.IntegerValue"), wxEmptyString, CyFormatInteger, true )
		<< wxString ( " FROM Parameters p" )
		<< this->m_strWhereClause
		<< wxString ( "	ORDER BY p.ParameterName, p.ObjId;" );

	return strSelectSql;
}

/* ---------------------------------------------------------------------------- */

wxString CyParametersSqlBuilder::getUpdateSql ( const CyQueryResult::CyQueryResultValuesRow& newRow ) const
{
	//
	//	strUpdateSql =
	//
	//	UPDATE 
	//		Parameters 
	//	SET  
	//		ParameterName = "Name" , 
	//		TextValue = "Nouvelle valeur", 
	//		IntergerValue = 0
	//	WHERE 
	//		ObjId = 10 ;
	//

	wxString strIntegerValue = wxEmptyString;
	if ( newRow.at ( CyParametersSqlBuilder::kIntegerValue )->isNull ( ) )
	{
		strIntegerValue << wxString ( "NULL" );
	}
	else
	{
		strIntegerValue << newRow.at ( CyParametersSqlBuilder::kTextValue )->get ( CyLongValue::m_lDummyValue );
	}

	wxString strUpdateSql = wxEmptyString;

	strUpdateSql
		<< wxString ( "UPDATE Parameters SET " )
		<< wxString ( " ParameterName = \"" )
		<< newRow.at ( CyParametersSqlBuilder::kParameterName )->get ( CyStringValue::m_strDummyValue )
		<< wxString ( "\" , TextValue = " )
		<< ( newRow.at ( CyParametersSqlBuilder::kTextValue )->isNull ( ) ? wxString ( "NULL" ) : ( wxString ( "\"" ) + newRow.at ( CyParametersSqlBuilder::kTextValue )->get ( CyStringValue::m_strDummyValue ) + wxString ( "\"" ) ) )
		<< wxString ( ", IntegerValue = " )
		<< strIntegerValue
		<< wxString ( " WHERE ObjId = " )
		<< newRow.at ( CyParametersSqlBuilder::kObjId )->get ( CyLongValue::m_lDummyValue )
		<< wxString ( " ;" );

	return strUpdateSql;
}

/* ---------------------------------------------------------------------------- */

int CyParametersSqlBuilder::getHiddenColumns ( ) const
{
	return 1;
}

/* ---------------------------------------------------------------------------- */