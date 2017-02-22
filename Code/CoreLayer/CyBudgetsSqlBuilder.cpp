/* ---------------------------------------------------------------------------- */
//! CyBudgetsSqlBuilder.cpp
/* ---------------------------------------------------------------------------- */
//!
//! \file CyBudgetsSqlBuilder.cpp
//! \brief definition file for class CyBudgetsSqlBuilder
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

#include "CoreLayer/CyBudgetsSqlBuilder.h"
#include "DataLayer/CyLongValue.h"
#include "DataLayer/CyStringValue.h"
#include "UtilitiesLayer/CyEnum.h"
#include "UtilitiesLayer/CyGetText.h"

/* ---------------------------------------------------------------------------- */

CyBudgetsSqlBuilder::CyBudgetsSqlBuilder ( )
{
}

/* ---------------------------------------------------------------------------- */

CyBudgetsSqlBuilder::~CyBudgetsSqlBuilder ( )
{
}

/* ---------------------------------------------------------------------------- */

wxString CyBudgetsSqlBuilder::getDialogTitle ( ) const
{
	return CyGetText::getInstance ( ).getText ( "CyBudgetsSqlBuilder.getDialogTitle.BudgetTitle" );
}

/* ---------------------------------------------------------------------------- */

wxString CyBudgetsSqlBuilder::getDeleteSql ( long long lObjId ) const
{
	//
	//	strDeleteSql =
	//
	//	DELETE FROM 
	//		Budgets 
	//	WHERE
	//		objId = 2 ;
	//
	wxString strDeleteSql = wxEmptyString;

	strDeleteSql 
		<< wxString ( "DELETE FROM Budgets WHERE objId = ") 
		<< lObjId
		<< wxString ( " ;" );

	return strDeleteSql;
}

/* ---------------------------------------------------------------------------- */

 wxString CyBudgetsSqlBuilder::getInsertSql ( const CyQueryResult::CyQueryResultValuesRow& newRow ) const
{
	//	strInsertSql =
	//
	//	INSERT INTO 
	//		Budgets 
	//		( 
	//			ObjId, 
	//			Description
	//		) 
	//		VALUES 
	//		( 
	//			( SELECT IFNULL ( MAX ( ObjId ), -1) + 1 FROM Budgets ),
	//			"Travaux"
	//		);

	wxString strInsertSql = wxEmptyString;

	strInsertSql
		<< wxString ( "INSERT INTO Budgets ( ObjId, Description ) " )
		<< wxString ( "VALUES ( ( SELECT IFNULL ( MAX ( ObjId ), -1) + 1 FROM Budgets ), \"" )
		<< newRow.at ( CyBudgetsSqlBuilder::kBudgetDescription )->get ( CyStringValue::m_strDummyValue )
		<< wxString ( "\");");

	return strInsertSql;
}

/* ---------------------------------------------------------------------------- */

void CyBudgetsSqlBuilder::createRow ( CyQueryResult::CyQueryResultValuesRow& newRow ) const
{
	wxString strStringFormat;
	// Budget ObjId...
	strStringFormat
		<< CyStartFormat 
		<< CyFormatHidden;
	CyLongValue* pObjId = new CyLongValue;
	pObjId->set ( CyEnum::kInvalidObjId, strStringFormat );
	newRow.push_back  ( pObjId );

	// ...and budget description
	strStringFormat.clear ( );
	strStringFormat
		<< CyStartFormat 
		<< CyFormatString;
	CyStringValue* pBudgetDescription = new CyStringValue;
	pBudgetDescription->set ( wxString ( "" ), strStringFormat );
	newRow.push_back ( pBudgetDescription );
}

/* ---------------------------------------------------------------------------- */

wxString CyBudgetsSqlBuilder::getSelectSql ( ) const
{
	//
	//	strSelectSql =
	//
	//	SELECT 
	//		"➻∅" AS ➻, 
	//		b.ObjId, 
	//		"➻α" AS ➻, 
	//		b.Description AS "Intitulé" 
	//	FROM 
	//		Budgets b 
	//	ORDER BY 
	//	b.Description;
	//

	wxString strSelectSql = wxEmptyString;

	strSelectSql
		<< wxString ( "SELECT " )
		<< this->getFieldSql ( wxString ( "b.ObjId" ),wxEmptyString, CyFormatHidden )
		<<this->getFieldSql ( wxString ( "b.Description" ), CyGetText::getInstance ( ).getText ( "CyBudgetsSqlBuilder.getSelectSql.Description" ), CyFormatString, true )
		<< wxString ( "FROM Budgets b ORDER BY b.Description;" );

	return strSelectSql;
}

/* ---------------------------------------------------------------------------- */

wxString CyBudgetsSqlBuilder::getUpdateSql ( const CyQueryResult::CyQueryResultValuesRow& newRow ) const
{
	//
	//	strUpdateSql =
	//
	//	UPDATE 
	//		Budgets 
	//	SET 
	//		Description = "Budget extraordinaire"
	//	WHERE 
	//		ObjId = 1;

	wxString strUpdateSql = wxEmptyString;

	strUpdateSql 
		<< wxString ( "UPDATE Budgets SET Description = \"" )
		<< newRow.at ( CyBudgetsSqlBuilder::kBudgetDescription )->get ( CyStringValue::m_strDummyValue )
		<< wxString ( "\" WHERE ObjId = " )
		<< newRow.at ( CyBudgetsSqlBuilder::kBudgetObjId )->get ( CyLongValue::m_lDummyValue )
		<< wxString ( ";" );

	return strUpdateSql;
}

/* ---------------------------------------------------------------------------- */

int CyBudgetsSqlBuilder::getHiddenColumns ( ) const
{
	return 1;
}

/* ---------------------------------------------------------------------------- */
