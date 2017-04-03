/* ---------------------------------------------------------------------------- */
//! CyAttributionsSqlBuilder.cpp
/* ---------------------------------------------------------------------------- */
//!
//! \file CyAttributionsSqlBuilder.cpp
//! \brief definition file for class CyAttributionsSqlBuilder
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

#include "CoreLayer/CyAttributionsSqlBuilder.h"
#include "DataLayer/CyLongValue.h"
#include "DataLayer/CyStringValue.h"
#include "UtilitiesLayer/CyEnum.h"
#include "UtilitiesLayer/CyGetText.h"

/* ---------------------------------------------------------------------------- */

CyAttributionsSqlBuilder::CyAttributionsSqlBuilder ( )
{
	this->m_strWhereClause = wxEmptyString;
}

/* ---------------------------------------------------------------------------- */

CyAttributionsSqlBuilder::CyAttributionsSqlBuilder ( const wxDateTime& objAttributionValidToDate )
{
	//
	// this->m_strWhereClause =

	// WHERE 
	//		a.ValidToDate >= "2017-02-26" 
	//

	this->m_strWhereClause
		<<"WHERE a.ValidToDate >= \""
		<< objAttributionValidToDate.Format ( wxString ( "%Y-%m-%d" ) )
		<< "\" ";
}

/* ---------------------------------------------------------------------------- */

CyAttributionsSqlBuilder::~CyAttributionsSqlBuilder ( )
{
}

/* ---------------------------------------------------------------------------- */

wxString CyAttributionsSqlBuilder::getDialogTitle ( ) const
{
	return CyGetText::getInstance ( ).getText ( "CyAttributionsSqlBuilder.getDialogTitle.AttributionsTitle" );
}

/* ---------------------------------------------------------------------------- */

wxString CyAttributionsSqlBuilder::getDeleteSql ( long long lObjId) const
{
	//
	//	strDeleteSql =
	//
	//	DELETE FROM
	//		Attributions 
	//	WHERE 
	//		objId = 60;
	//	

	wxString strDeleteSql = wxEmptyString;

	strDeleteSql
		<< wxString ( "DELETE FROM Attributions WHERE objId = ") 
		<< lObjId
		<< wxString ( ";" );

	return strDeleteSql;
}

/* ---------------------------------------------------------------------------- */

 wxString CyAttributionsSqlBuilder::getInsertSql ( const CyQueryResult::CyQueryResultValuesRow& newRow ) const
{

	//	strInsertSql =
	//
	//	INSERT INTO 
	//		Attributions 
	//		( 
	//			ObjId, 
	//			GroupObjId, 
	//			Description, 
	//			BudgetObjId,
	//			ValidToDate
	//		) 
	//		VALUES 
	//		(  
	//			( SELECT IFNULL ( MAX ( ObjId ), -1 ) + 1 FROM Attributions ),
	//			0,
	//			"Maison", 
	//			1 ,
	//			"2015-02-06"
	//		);
	//

	wxString strInsertSql = wxEmptyString;

	strInsertSql
		<< wxString ( "INSERT INTO Attributions ( ObjId, GroupObjId, Description, BudgetObjId, ValidToDate ) VALUES (  ( SELECT IFNULL ( MAX ( ObjId ), -1 ) + 1 FROM Attributions ), " )
		<< newRow.at ( CyAttributionsSqlBuilder::kAttributionGroupObjId )->get ( CyLongValue::m_lDummyValue )
		<< wxString ( ", \"" )
		<< newRow.at ( CyAttributionsSqlBuilder::kAttributionDescription )->get ( CyStringValue::m_strDummyValue )
		<< wxString ( "\", " )
		<< newRow.at ( CyAttributionsSqlBuilder::kBudgetObjId )->get ( CyLongValue::m_lDummyValue )
		<< wxString ( ", \"" )
		<< newRow.at ( CyAttributionsSqlBuilder::kAttributionValidToDate )->get ( CyStringValue::m_strDummyValue )
		<< wxString ( "\" );" );

	return strInsertSql;
}

/* ---------------------------------------------------------------------------- */

void CyAttributionsSqlBuilder::createRow ( CyQueryResult::CyQueryResultValuesRow& newRow ) const
{
	wxString strStringFormat;

	// Group ObjId ...
	strStringFormat
		<< CyStartFormat 
		<< CyFormatHidden;
	CyLongValue* pGroupObjId = new CyLongValue;
	pGroupObjId->set ( CyEnum::kInvalidObjId, strStringFormat );
	newRow.push_back  ( pGroupObjId );

	// ... Attribution ObjId ...
	CyLongValue* pAttributionObjId = new CyLongValue;
	pAttributionObjId->set ( CyEnum::kInvalidObjId, strStringFormat );
	newRow.push_back  ( pAttributionObjId );

	// ... Budget ObjId ...
	CyLongValue* pBudgetObjId = new CyLongValue;
	pBudgetObjId->set ( CyEnum::kInvalidObjId, strStringFormat );
	newRow.push_back  ( pBudgetObjId );

	// ... Group description ...
	strStringFormat.clear ( );
	strStringFormat
		<< CyStartFormat 
		<< CyFormatString;
	CyStringValue* pAttributionMainDescription = new CyStringValue;
	pAttributionMainDescription->set ( wxString ( "" ), strStringFormat );
	newRow.push_back ( pAttributionMainDescription );

	// ... Attribution description ...
	CyStringValue* pAttributionDescription = new CyStringValue;
	pAttributionDescription->set ( wxString ( "" ), strStringFormat );
	newRow.push_back ( pAttributionDescription );

	// ... Budget description ...
	CyStringValue* pBudgetDescription = new CyStringValue;
	pBudgetDescription->set ( wxString ( "" ), strStringFormat );
	newRow.push_back ( pBudgetDescription );

	// ... Validity date
	strStringFormat.clear ( );
	strStringFormat
		<< CyStartFormat
		<< CyFormatDate;
	CyStringValue* pValidityDate = new CyStringValue;
	pValidityDate->set ( wxString ( "2099-12-31" ), strStringFormat );
	newRow.push_back ( pValidityDate );
}

/* ---------------------------------------------------------------------------- */

wxString CyAttributionsSqlBuilder::getSelectSql ( ) const
{
	//
	//	strSelectSql =
	//
	//	SELECT 
	//		"➻∅" AS ➻,
	//		g.ObjId AS "GroupObjId",
	//		"➻∅" AS ➻,
	//		a.ObjId AS "AttributionObjId",
	//		"➻∅" AS ➻, 
	//		b.ObjId AS "BudgetObjId",
	//		"➻α" AS ➻,
	//		g.GroupDescription AS "Groupe",
	//		"➻α" AS ➻, 
	//		a.Description AS "Sous-groupe", 
	//		"➻α" AS ➻, 
	//		b.Description AS "Budget",
	//		"➻≋" AS ➻,
	//		a.ValidToDate AS "Utilisé jusqu'au"
	//	FROM 
	//		Attributions a 
	//		LEFT JOIN AttributionsGroups g ON g.ObjId = a.GroupObjId 
	//		LEFT JOIN Budgets b ON a.BudgetObjId = b.ObjId 
	//	ORDER BY 
	//		g.GroupDescription, 
	//		a.Description;
	//

	wxString strSelectSql = wxEmptyString;

	strSelectSql
		<< wxString ( "SELECT " )
		<< this->getFieldSql ( wxString ( "g.ObjId" ),wxString ( "GroupObjId" ), CyFormatHidden )
		<< this->getFieldSql ( wxString ( "a.ObjId" ),wxString ( "AttributionObjId" ), CyFormatHidden )
		<< this->getFieldSql ( wxString ( "b.ObjId" ),wxString ( "BudgetObjId" ), CyFormatHidden )
		<< this->getFieldSql ( wxString ( "g.GroupDescription" ), CyGetText::getInstance ( ).getText ( "CyAttributionsSqlBuilder.getSelectSql.GroupDescription" ), CyFormatString )
		<< this->getFieldSql ( wxString ( "a.Description" ), CyGetText::getInstance ( ).getText ( "CyAttributionsSqlBuilder.getSelectSql.Description" ), CyFormatString )
		<< this->getFieldSql ( wxString ( "b.Description" ), CyGetText::getInstance ( ).getText ( "CyAttributionsSqlBuilder.getSelectSql.Budget" ), CyFormatString )
		<< this->getFieldSql ( wxString ( "a.ValidToDate" ), CyGetText::getInstance ( ).getText ( "CyAttributionsSqlBuilder.getSelectSql.ValidToDate" ), CyFormatDate, true )
		<< wxString ( "FROM Attributions a LEFT JOIN AttributionsGroups g ON g.ObjId = a.GroupObjId LEFT JOIN Budgets b ON a.BudgetObjId = b.ObjId " )
		<< this->m_strWhereClause
		<< wxString ( "ORDER BY g.GroupDescription, a.Description;" );

	return strSelectSql;
}

/* ---------------------------------------------------------------------------- */

wxString CyAttributionsSqlBuilder::getUpdateSql ( const CyQueryResult::CyQueryResultValuesRow& newRow ) const
{
	//
	//	strUpdateSql =
	//
	//	UPDATE
	//		Attributions 
	//	SET 
	//		GroupObjId = 0 ,
	//		BudgetObjId = 0 ,
	//		Description = "Assurances",
	//		ValidToDate = ""2017-02-06""
	//	WHERE 
	//		ObjId = 20;
	//

	wxString strUpdateSql = wxEmptyString;

	strUpdateSql << wxString ( "UPDATE Attributions SET " )
		<< wxString ( "GroupObjId = " )
		<< newRow.at ( CyAttributionsSqlBuilder::kAttributionGroupObjId )->get ( CyLongValue::m_lDummyValue )
		<< wxString ( ", BudgetObjId = " )
		<< newRow.at ( CyAttributionsSqlBuilder::kBudgetObjId )->get ( CyLongValue::m_lDummyValue )
		<< wxString ( ", Description = \"" )
		<< newRow.at ( CyAttributionsSqlBuilder::kAttributionDescription )->get ( CyStringValue::m_strDummyValue )
		<< wxString ( "\", ValidToDate = \"" )
		<< newRow.at ( CyAttributionsSqlBuilder::kAttributionValidToDate )->get ( CyStringValue::m_strDummyValue )
		<< wxString ( "\" WHERE ObjId = " )
		<< newRow.at ( CyAttributionsSqlBuilder::kAttributionObjId )->get ( CyLongValue::m_lDummyValue )
		<< wxString ( ";" );

	return strUpdateSql;
}

/* ---------------------------------------------------------------------------- */

int CyAttributionsSqlBuilder::getHiddenColumns ( ) const
{
	return 3;
}

/* ---------------------------------------------------------------------------- */
