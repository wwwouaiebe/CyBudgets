/* ---------------------------------------------------------------------------- */
//! CyOperationsSqlBuilder.cpp
/* ---------------------------------------------------------------------------- */
//!
//! \file CyOperationsSqlBuilder.cpp
//! \brief definition file for class CyOperationsSqlBuilder
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

#include "CoreLayer/CyOperationsSqlBuilder.h"
#include "CoreLayer/CyAnalyseSqlBuilder.h"
#include "DataLayer/CyLongValue.h"
#include "DataLayer/CySqliteDb.h"
#include "DataLayer/CyStringValue.h"
#include "UtilitiesLayer/CyEnum.h"
#include "UtilitiesLayer/CyGetText.h"
#include "UtilitiesLayer/CyStringParser.h"

/* ---------------------------------------------------------------------------- */

CyOperationsSqlBuilder::CyOperationsSqlBuilder ( )
{
	// This constructor is used when searching the operations without attributions

	// Dialog title creation 
	this->m_strDialogTitle = CyGetText::getInstance ( ).getText ( "CyOperationsSqlBuilder.CyOperationsSqlBuilder.OperationWithoutAttributionsTitle" );

	// SQL 'WHERE' clause creation 

	//
	//	m_strWhereClause = 
	//
	//	WHERE 
	//		ope.OpeObjId IN 
	//		(
	//			SELECT 
	//				ObjId 
	//			FROM 
	//			(
	//				SELECT 
	//					o.ObjId,
	//					o.Amount,
	//					IFNULL ( SUM ( a.Amount ), 0 ) AS AttAmount 
	//				FROM Operations o LEFT JOIN OperationsAttributions a ON o.ObjId = a.OperationObjId 
	//				GROUP BY a.OperationObjId 
	//			) 
	//			WHERE Amount <> AttAmount
	//		)
	//

/*
	this->m_strWhereClause 
			<< wxString ( "WHERE ope.OpeObjId IN ( SELECT ObjId FROM (SELECT o.ObjId, o.Amount, IFNULL ( SUM ( a.Amount ), 0 ) AS AttAmount FROM Operations o LEFT JOIN OperationsAttributions a ON o.ObjId = a.OperationObjId GROUP BY a.OperationObjId ) WHERE Amount <> AttAmount)" );
*/
	this->m_strWhereClause 
			<< wxString ( "WHERE ope.OpeObjId IN ( SELECT o1.ObjId from Operations o1 LEFT JOIN OperationsAttributions oa1 on o1.ObjId = oa1.OperationObjId WHERE o1.Amount <> 0 and oa1.ObjId IS NULL UNION SELECT ObjId FROM (SELECT o.ObjId, o.Amount, IFNULL ( SUM ( a.Amount ), 0 ) AS AttAmount FROM Operations o LEFT JOIN OperationsAttributions a ON o.ObjId = a.OperationObjId GROUP BY a.OperationObjId ) WHERE Amount <> AttAmount)" );
	
	// Tables list creation

	//
	//	m_strTables = 
	//
	//	AccountsView Acc 
	//		JOIN OperationsView Ope ON Acc.AccobjId = Ope.AccountObjId
	//		LEFT JOIN OperationsDetailsView Det ON Ope.OpeObjId = Det.OperationObjId
	//		LEFT JOIN OperationsAttributionsView Att ON Ope.OpeObjId = Att.OperationObjId
	//

	this->m_strTables
		<< wxString ( "AccountsView Acc JOIN OperationsView Ope ON Acc.AccobjId = Ope.AccountObjId " )
		<< wxString ( "LEFT JOIN OperationsDetailsView Det ON Ope.OpeObjId = Det.OperationObjId " )
		<< wxString ( "LEFT JOIN OperationsAttributionsView Att ON Ope.OpeObjId = Att.OperationObjId " );
}

/* ---------------------------------------------------------------------------- */

CyOperationsSqlBuilder::CyOperationsSqlBuilder ( const wxString& strAccount, long long lAccountObjId, const wxDateTime& objStartDate, const wxDateTime& objEndDate )
{
	// this constructor is used when displaying the operations from the main frame

	// Dialog title creation 
	this->m_strDialogTitle = CyGetText::getInstance ( ).getText ( "CyOperationsSqlBuilder.CyOperationsSqlBuilder.OperationTitle" );

	if ( CyEnum::kInvalidObjId == lAccountObjId )
	{
		this->m_strDialogTitle
			<< wxString ( " - " );

		this->m_strWhereClause 
			<< wxString ( "WHERE " );
	}
	else
	{
		this->m_strDialogTitle
			<< wxString ( " - " )
			<< CyGetText::getInstance ( ).getText ( "CyOperationsSqlBuilder.CyOperationsSqlBuilder.AccountTitle" )
			<< wxString ( " " )
			<< strAccount
			<< wxString ( " - " );

		this->m_strWhereClause 
			<< wxString ( "WHERE Acc.AccObjId = " )
			<< lAccountObjId 
			<<  wxString ( " AND " );
	}

	this->m_strDialogTitle 
		<< CyGetText::getInstance ( ).getText ("CyOperationsSqlBuilder.CyOperationsSqlBuilder.Period1" )
		<< objStartDate.Format ( wxString ( "%d-%m-%Y" ) )
		<< CyGetText::getInstance ( ).getText ("CyOperationsSqlBuilder.CyOperationsSqlBuilder.Period2" )
		<< objEndDate.Format ( wxString ( "%d-%m-%Y" ) );

	// SQL 'WHERE' clause creation 

	//
	//	m_strWhereClause = 
	//
	//	WHERE 
	//		Acc.AccObjId = 3
	//		AND OperationDate >= "2014-11-01"
	//		AND OperationDate <= "2014-12-31"
	//

	this->m_strWhereClause 
		<< wxString ( "OperationDate >= \"" )
		<< objStartDate.FormatISODate ( )
		<< wxString ( "\" AND OperationDate <= \"")
		<< objEndDate.FormatISODate ( )
		<< wxString ( "\" " );

	// Tables list creation

	//
	//	m_strTables = 
	//
	//	AccountsView Acc 
	//		JOIN OperationsView Ope ON Acc.AccobjId = Ope.AccountObjId
	//		LEFT JOIN OperationsDetailsView Det ON Ope.OpeObjId = Det.OperationObjId
	//		LEFT JOIN OperationsAttributionsView Att ON Ope.OpeObjId = Att.OperationObjId
	//

	this->m_strTables
		<< wxString ( "AccountsView Acc JOIN OperationsView Ope ON Acc.AccobjId = Ope.AccountObjId " )
		<< wxString ( "LEFT JOIN OperationsDetailsView Det ON Ope.OpeObjId = Det.OperationObjId " )
		<< wxString ( "LEFT JOIN OperationsAttributionsView Att ON Ope.OpeObjId = Att.OperationObjId " );
}

/* ---------------------------------------------------------------------------- */

CyOperationsSqlBuilder::CyOperationsSqlBuilder ( const CyQueryResult::CyQueryResultValuesRow& currentRow, const wxDateTime& objStartDate, const wxDateTime& objEndDate  )
{
	// This constructor is used when searching the operations from an analyse

	// Dialog title creation start
	this->m_strDialogTitle = CyGetText::getInstance ( ).getText ("CyOperationsSqlBuilder.CyOperationsSqlBuilder.Title" );

	// A SQL 'WHERE' clause for the temporary view is created
	wxString strWhereClauseForView;


	long long lGroupObjId = currentRow.at ( CyAnalyseSqlBuilder::kGroupObjId )->get ( CyLongValue::m_lDummyValue );
	if ( CyEnum::kInvalidObjId != lGroupObjId )
	{
		// the user have selected a line for a group
		wxString strSql;
		strSql
			<< wxString ( "SELECT GroupDescription from AttributionsGroups WHERE ObjId = " )
			<< lGroupObjId
			<< wxString ( ";" );
		wxString strGroupDescription;
		CySqliteDb::getInstance ( ).getSingleValue ( strSql, &strGroupDescription );

		// Dialog title
		this->m_strDialogTitle
			<< wxString ( " - " )
			<< CyGetText::getInstance ( ).getText ("CyOperationsSqlBuilder.CyOperationsSqlBuilder.Group" )
			<< strGroupDescription
			<< wxString ( " - " );

		// 'WHERE' clause for the temporary view
		strWhereClauseForView
			<< wxString ( "WHERE Attributions.GroupObjId = " )
			<< lGroupObjId
			<< wxString (" ");
	}

	long long lAttributionObjId = currentRow.at ( CyAnalyseSqlBuilder::kAttributionObjId )->get ( CyLongValue::m_lDummyValue );
	if ( CyEnum::kInvalidObjId != lAttributionObjId )
	{
		// the user have selected a line for an attribution
		wxString strSql;
		strSql
			<< wxString ( "SELECT Description from Attributions WHERE ObjId = " )
			<< lAttributionObjId
			<< wxString ( ";" );
		wxString strAttributionDescription;
		CySqliteDb::getInstance ( ).getSingleValue ( strSql, &strAttributionDescription );

		strSql.clear ( );
		strSql
			<< wxString ( "SELECT g.GroupDescription from AttributionsGroups g JOIN Attributions a ON g.ObjId = a.GroupObjId WHERE a.ObjId = " )
			<< lAttributionObjId
			<< wxString ( ";" );
		wxString strGroupDescription;
		CySqliteDb::getInstance ( ).getSingleValue ( strSql, &strGroupDescription );

		// Dialog title
		this->m_strDialogTitle
			<< wxString ( " - " )
			<< CyGetText::getInstance ( ).getText ("CyOperationsSqlBuilder.CyOperationsSqlBuilder.Group" )
			<< strGroupDescription
			<< wxString ( " - " )
			<< CyGetText::getInstance ( ).getText ("CyOperationsSqlBuilder.CyOperationsSqlBuilder.Attribution" )
			<< strAttributionDescription
			<< wxString ( " - " );

		// 'WHERE' clause for the temporary view
		strWhereClauseForView
			<< wxString ( "WHERE Attributions.ObjId = " )
			<< lAttributionObjId
			<< wxString (" ");
	}

	// Because we start from an analyse we have always starting and ending dates that we add to the dialog title 
	// and to the 'WHERE' clause
	this->m_strDialogTitle
		<< CyGetText::getInstance ( ).getText ("CyOperationsSqlBuilder.CyOperationsSqlBuilder.Period1" );

	wxString strStartDate;
	wxString strEndDate;

	// we search a date in the row selected by the user
	wxString strBudgetDate = ( currentRow.at ( CyAnalyseSqlBuilder::kHiddenBudgetDate )->get ( CyStringValue::m_strDummyValue ) );
	if ( strBudgetDate.empty ( ) )
	{
		// a date is not found in the row. We use the dates of the main frame given in the parameters
		strStartDate = objStartDate.FormatISODate ( );
		strEndDate = objEndDate.FormatISODate ( );

		// and the dates are added to the dialog title
		this->m_strDialogTitle 
			<< objStartDate.Format ( wxString ( "%d-%m-%Y" ) )
			<< CyGetText::getInstance ( ).getText ("CyOperationsSqlBuilder.CyOperationsSqlBuilder.Period2" )
			<< objEndDate.Format ( wxString ( "%d-%m-%Y" ) );
	}
	else
	{
		// a date is found in the row. We use first day and last day of the month as filter
		strStartDate
			<< strBudgetDate
			<< wxString ( "-01" );
		strEndDate
			<< strBudgetDate
			<< wxString ( "-01" );
		// we search the last day of the month
		wxDateTime tmpDateTime;
		tmpDateTime.ParseISODate ( strEndDate );
		tmpDateTime.SetToLastMonthDay ( );
		strEndDate = tmpDateTime.FormatISODate ( );

		// and the dates are added to the dialog title
		this->m_strDialogTitle 
			<<  wxString ( "01-" )
			<< strBudgetDate.substr ( 5, 2 )
			<< wxString ( "-" )
			<< strBudgetDate.substr ( 0, 4 )
			<< CyGetText::getInstance ( ).getText ("CyOperationsSqlBuilder.CyOperationsSqlBuilder.Period2" )
			<< tmpDateTime.Format ( wxString ( "%d-%m-%Y" ) );
	}

	// The starting and ending dates are added to the 'WHERE' clause
	this->m_strWhereClause 
		<< wxString ( "WHERE AttributionDate >= \"" )
		<< strStartDate
		<< wxString ( "\" AND AttributionDate <= \"")
		<< strEndDate
		<< wxString ( "\" " );

	// View creation ( needed for Linux. We cannot use the "With" SQL instruction...)
	// The current date and time are added to the view name to be sure that we have an unique view name
	wxDateTime now;
	now.SetToCurrent ( );
	wxString strViewName;
	strViewName 
		<< wxString ( "OperationsView" )
		<< now.FormatISOCombined ( );

	// - and : are removed because it's invalid characters for a vienw name
	strViewName.Replace ( wxString ( "-" ), wxString ( "" ) );
	strViewName.Replace ( wxString ( ":" ), wxString ( "" ) );

	//
	// strSql = 
	//
	//	CREATE TEMPORARY VIEW IF NOT EXISTS OperationsView20141227T1425 AS
	//		SELECT 
	//			Operations.ObjId as OpeObjId, Operations.AccountObjId, Operations.OperationNumber,
	//			Operations.OperationDate, Operations.ValueDate, Operations.AttributionDate,
	//			Operations.Amount, Operations.Description
	//		FROM 
	//			Operations 
	//			LEFT JOIN OperationsAttributions ON Operations.ObjId = OperationsAttributions.OperationObjId 
	//			LEFT JOIN Attributions ON OperationsAttributions.AttributionObjId = Attributions.ObjId
	//		WHERE 
	//			Attributions.ObjId = 5;
	//

	wxString strSql;
	strSql
		<< wxString ( "CREATE TEMPORARY VIEW IF NOT EXISTS " )
		<< strViewName
		<< wxString ( " AS SELECT Operations.ObjId as OpeObjId, Operations.AccountObjId, Operations.OperationNumber, " )
		<< wxString ( "Operations.OperationDate, Operations.ValueDate, Operations.AttributionDate, Operations.Amount, Operations.Description " )
		<< wxString ( "FROM Operations LEFT JOIN OperationsAttributions " )
		<< wxString ( "ON Operations.ObjId = OperationsAttributions.OperationObjId LEFT JOIN Attributions ON OperationsAttributions.AttributionObjId = Attributions.ObjId " )
		<< strWhereClauseForView
		<< wxString ( ";" );

	CySqliteDb::getInstance ( ).executeSql ( strSql );

	//
	//	m_strTables = 
	//
	//	AccountsView Acc 
	//		JOIN OperationsView20141227T1425 Ope ON Acc.AccobjId = Ope.AccountObjId
	//		LEFT JOIN OperationsDetailsView Det ON Ope.OpeObjId = Det.OperationObjId
	//		LEFT JOIN OperationsAttributionsView Att ON Ope.OpeObjId = Att.OperationObjId
	//

	this->m_strTables
		<< wxString ( "AccountsView Acc JOIN " )
		<< strViewName 
		<< wxString ( " Ope ON Acc.AccobjId = Ope.AccountObjId " )
		<< wxString ( "LEFT JOIN OperationsDetailsView Det ON Ope.OpeObjId = Det.OperationObjId " )
		<< wxString ( "LEFT JOIN OperationsAttributionsView Att ON Ope.OpeObjId = Att.OperationObjId " );

}

/* ---------------------------------------------------------------------------- */

CyOperationsSqlBuilder::~CyOperationsSqlBuilder ( )
{
}

/* ---------------------------------------------------------------------------- */

wxString CyOperationsSqlBuilder::getDialogTitle ( ) const
{
	return this->m_strDialogTitle;
}

/* ---------------------------------------------------------------------------- */

wxString CyOperationsSqlBuilder::getDeleteSql ( long long lObjId ) const
{
	//
	//	strDeleteSql =
	//
	//	DELETE 
	//	FROM 
	//		Operations 
	//	WHERE 
	//		objId = 10;
	//

	wxString strDeleteSql = wxEmptyString;

	strDeleteSql
		<< wxString ( "DELETE FROM Operations WHERE objId = ") 
		<< lObjId
		<< wxString ( " ;" );

	return strDeleteSql;
}

/* ---------------------------------------------------------------------------- */

 wxString CyOperationsSqlBuilder::getInsertSql (  const CyQueryResult::CyQueryResultValuesRow& newRow ) const
{

	//
	//	strInsertSql =
	//
	//	INSERT INTO 
	//		Operations 
	//		( 
	//			ObjId, 
	//			AccountObjId, 
	//			OperationNumber, 
	//			OperationDate, 
	//			ValueDate, 
	//			AttributionDate, 
	//			Amount, 
	//			Description 
	//		) 
	//		VALUES 
	//		( 
	//			(SELECT IFNULL ( MAX ( ObjId ), -1) + 1 FROM Operations ),
	//			( SELECT ObjId FROM Accounts WHERE AccountNumber = "6060776915318355"),
	//			0,
	//			"2015-02-15",
	//			"2015-02-15", 
	//			"2015-02-15",
	//			1000,
	//			"Blabla" 
	//		);
	//

	wxString strInsertSql = wxEmptyString;

	strInsertSql
		<< wxString ( "INSERT INTO Operations ( ObjId, AccountObjId, OperationNumber, OperationDate, ValueDate, AttributionDate, Amount, Description ) " )
		<< wxString ( "VALUES ( ( SELECT IFNULL ( MAX ( ObjId ), -1) + 1 FROM Operations ), ( SELECT ObjId FROM Accounts WHERE AccountNumber = \"" )
		<< newRow.at ( CyOperationsSqlBuilder::kOperationAccountNumber )->get ( CyStringValue::m_strDummyValue )
		<< wxString ( "\"), " )
		<< newRow.at ( CyOperationsSqlBuilder::kOperationNumber )->get ( CyLongValue::m_lDummyValue )
		<< wxString ( ", \"" )
		<< newRow.at ( CyOperationsSqlBuilder::kOperationDate )->get ( CyStringValue::m_strDummyValue )
		<< wxString ( "\", \"" )
		<< newRow.at ( CyOperationsSqlBuilder::kOperationValueDate )->get ( CyStringValue::m_strDummyValue )
		<< wxString ( "\", \"" )
		<< newRow.at ( CyOperationsSqlBuilder::kOperationAttributionDate )->get ( CyStringValue::m_strDummyValue )
		<< wxString ( "\", " )
		<< newRow.at ( CyOperationsSqlBuilder::kOperationAmount )->get ( CyLongValue::m_lDummyValue )
		<< wxString ( ", \"" )
		<< newRow.at ( CyOperationsSqlBuilder::kOperationDescription )->get ( CyStringValue::m_strDummyValue )
		<< wxString ( "\" );" );

	return strInsertSql;
}

/* ---------------------------------------------------------------------------- */

void CyOperationsSqlBuilder::createRow ( CyQueryResult::CyQueryResultValuesRow& newRow ) const
{
	wxString strStringFormat;
	// Operation ObjId...
	strStringFormat
		<< CyStartFormat 
		<< CyFormatHidden;
	CyLongValue* pObjId = new CyLongValue;
	pObjId->set ( CyEnum::kInvalidObjId, strStringFormat );
	newRow.push_back  ( pObjId );

	// ... operation description...
	CyStringValue* pDescription = new CyStringValue;
	pDescription->set (  wxString ( "" ), strStringFormat );
	newRow.push_back  ( pDescription );

	// ... the "Account Can Be Imported" value ... 
	CyLongValue* pAccountCanBeImported = new CyLongValue;
	pAccountCanBeImported->set ( CyEnum::kNo, strStringFormat );
	newRow.push_back  ( pAccountCanBeImported );

	// ... account number... 
	strStringFormat.clear ( );
	strStringFormat
		<< CyStartFormat 
		<< CyFormatString;
	CyStringValue* pAccountNumber = new CyStringValue;
	pAccountNumber->set ( wxString ( "" ), strStringFormat );
	newRow.push_back ( pAccountNumber );

	// the operation number...
	strStringFormat.clear ( );
	strStringFormat
		<< CyStartFormat 
		<< CyFormatInteger;
	CyLongValue* pOperationNumber = new CyLongValue;
	pOperationNumber->set ( 0, strStringFormat );
	newRow.push_back  ( pOperationNumber );

	wxDateTime now;
	now.SetToCurrent ( );
	wxString strDate = now.FormatISODate ( );
	strStringFormat.clear ( );
	strStringFormat
		<< CyStartFormat 
		<< CyFormatDate;

	// ... operation date...
	CyStringValue* pOperationDate = new CyStringValue;
	pOperationDate->set ( strDate, strStringFormat );
	newRow.push_back ( pOperationDate );

	// ... value date...
	CyStringValue* pValueDate = new CyStringValue;
	pValueDate->set ( strDate, strStringFormat );
	newRow.push_back ( pValueDate );

	// ... attrinution date...
	CyStringValue* pBudgetDate = new CyStringValue;
	pBudgetDate->set ( strDate, strStringFormat );
	newRow.push_back ( pBudgetDate );

	// ... operation amount...
	strStringFormat.clear ( );
	strStringFormat
		<< CyStartFormat 
		<< CyFormatCurrency;
	CyLongValue* pAmount = new CyLongValue;
	pAmount->set ( 0, strStringFormat );
	newRow.push_back ( pAmount );

	// ... personnal notes symbol ...
	strStringFormat.clear ( );
	strStringFormat
		<< CyStartFormat 
		<< CyFormatBoolean;	
	CyLongValue* pNote = new CyLongValue;
	pNote->set ( CyEnum::kNo, strStringFormat );
	newRow.push_back ( pNote );

	// ...operation details symbol...
	CyLongValue* pOperationDetails = new CyLongValue;
	pOperationDetails->set ( CyEnum::kNo, strStringFormat );
	newRow.push_back (pOperationDetails ); // Detail

	// ...attributions symbol...
	CyLongValue* pAttributions = new CyLongValue;
	pAttributions->set ( CyEnum::kNo, strStringFormat );
	newRow.push_back ( pAttributions ); 
}

/* ---------------------------------------------------------------------------- */

wxString CyOperationsSqlBuilder::getSelectSql () const
{
	//
	//	strSelectSql =
	//
	//	SELECT 
	//		"➻∅" AS ➻,
	//		OpeObjId AS "ObjId",
	//		"➻∅" AS ➻,
	//		Description AS "Description",
	//		"➻∅" AS ➻, 
	//		CanBeImported AS "CanBeImported", 
	//		"➻α" AS ➻, 
	//		AccountNumber AS "n° Compte",
	//		"➻ℤ" AS ➻,
	//		OperationNumber AS "N° d'opération",
	//		"➻≋" AS ➻,
	//		OperationDate AS "Date d'opération",
	//		"➻≋" AS ➻,
	//		ValueDate AS "Date valeur",
	//		"➻≋" AS ➻, 
	//		AttributionDate AS "Date d'attribution", 
	//		"➻€" AS ➻, 
	//		Amount AS "Montant €",
	//		"➻✓" AS ➻, 
	//		IFNULL ( LENGTH ( Description ) / LENGTH ( Description ), 0 ) AS "Note",
	//		"➻✓" AS ➻, 
	//		IFNULL ( LENGTH ( DetailNumber ) / LENGTH ( DetailNumber ), 0 ) AS "Détails",
	//		"➻✓" AS ➻, 
	//		IFNULL ( LENGTH ( AttributionNumber ) / LENGTH ( AttributionNumber ), 0 ) AS "Attributions" 
	//	FROM 
	//		AccountsView Acc 
	//		JOIN OperationsView20150215T193743 Ope ON Acc.AccobjId = Ope.AccountObjId 
	//		LEFT JOIN OperationsDetailsView Det ON Ope.OpeObjId = Det.OperationObjId 
	//		LEFT JOIN OperationsAttributionsView Att ON Ope.OpeObjId = Att.OperationObjId 
	//	WHERE 
	//		AttributionDate >= "2015-01-01" AND AttributionDate <= "2015-02-15" 
	//	ORDER BY 
	//		AccountNumber, OperationDate DESC, OperationNumber DESC;
	//

	wxString strSelectSql = wxEmptyString;

	strSelectSql
		<< wxString ( "SELECT " )
		<< this->getFieldSql ( wxString ( "OpeObjId"), wxString ( "ObjId" ), CyFormatHidden )
		<< this->getFieldSql ( wxString ( "Description"), wxString ( "Description" ), CyFormatHidden )
		<< this->getFieldSql ( wxString ( "CanBeImported"), wxString ( "CanBeImported" ), CyFormatHidden )
		<< this->getFieldSql ( wxString ( "AccountNumber" ), CyGetText::getInstance ( ).getText ( "CyOperationsSqlBuilder.getSelectSql.Account" ), CyFormatString )
		<< this->getFieldSql ( wxString ( "OperationNumber" ), CyGetText::getInstance ( ).getText ( "CyOperationsSqlBuilder.getSelectSql.OperationNumber" ), CyFormatInteger )
		<< this->getFieldSql ( wxString ( "OperationDate" ), CyGetText::getInstance ( ).getText ( "CyOperationsSqlBuilder.getSelectSql.OperationDate" ), CyFormatDate )
		<< this->getFieldSql ( wxString ( "ValueDate" ), CyGetText::getInstance ( ).getText ( "CyOperationsSqlBuilder.getSelectSql.ValueDate" ), CyFormatDate )
		<< this->getFieldSql ( wxString ( "AttributionDate" ), CyGetText::getInstance ( ).getText ( "CyOperationsSqlBuilder.getSelectSql.AttributionDate" ), CyFormatDate )
		<< this->getFieldSql ( wxString ( "Amount"), CyGetText::getInstance ( ).getText ( "CyOperationsSqlBuilder.getSelectSql.Amount" ), CyFormatCurrency )
		<< this->getFieldSql ( wxString ( "IFNULL ( LENGTH ( Description ) / LENGTH ( Description ), 0 )" ), CyGetText::getInstance ( ).getText ( "CyOperationsSqlBuilder.getSelectSql.Note" ), CyFormatBoolean )
		<< this->getFieldSql ( wxString ( "IFNULL ( LENGTH ( DetailNumber ) / LENGTH ( DetailNumber ), 0 )" ), CyGetText::getInstance ( ).getText ( "CyOperationsSqlBuilder.getSelectSql.Details" ), CyFormatBoolean )
		<< this->getFieldSql ( wxString ( "IFNULL ( LENGTH ( AttributionNumber ) / LENGTH ( AttributionNumber ), 0 )"), CyGetText::getInstance ( ).getText ( "CyOperationsSqlBuilder.getSelectSql.Attributions" ), CyFormatBoolean, true)
		<< wxString ( "FROM " )
		<< this->m_strTables
		<< this->m_strWhereClause
		<< wxString ( "ORDER BY AccountNumber, OperationDate DESC, OperationNumber DESC;" );

	return strSelectSql;
}

/* ---------------------------------------------------------------------------- */

wxString CyOperationsSqlBuilder::getUpdateSql ( const CyQueryResult::CyQueryResultValuesRow& newRow ) const
{
	//
	//	strUpdateSql =
	//
	//	UPDATE 
	//		Operations 
	//	SET 
	//		OperationDate = "2015-02-15", 
	//		ValueDate = "2015-02-15", 
	//		AttributionDate = "2015-02-15", 
	//		Amount = 800, 
	//		Description = "Blabla"
	//	WHERE
	//		ObjId = 4219 ;
	//

	wxString strUpdateSql = wxEmptyString;

	strUpdateSql
		<< wxString ( "UPDATE Operations SET " )
		<< wxString ( "OperationDate = \"")
		<< newRow.at ( CyOperationsSqlBuilder::kOperationDate )->get ( CyStringValue::m_strDummyValue )
		<< wxString ( "\", ValueDate = \"" )
		<< newRow.at ( CyOperationsSqlBuilder::kOperationValueDate )->get ( CyStringValue::m_strDummyValue )
		<< wxString ( "\", AttributionDate = \"" ) 
		<< newRow.at ( CyOperationsSqlBuilder::kOperationAttributionDate )->get ( CyStringValue::m_strDummyValue )
		<< wxString ( "\", Amount = " )
		<< newRow.at ( CyOperationsSqlBuilder::kOperationAmount )->get ( CyLongValue::m_lDummyValue )
		<< wxString ( ", Description = \"" )
		<< newRow.at ( CyOperationsSqlBuilder::kOperationDescription )->get ( CyStringValue::m_strDummyValue )
		<< wxString ( "\" WHERE ObjId = " )
		<< newRow.at ( CyOperationsSqlBuilder::kOperationObjId )->get ( CyLongValue::m_lDummyValue )
		<< wxString ( " ;" );

	return strUpdateSql;
}

/* ---------------------------------------------------------------------------- */

int CyOperationsSqlBuilder::getHiddenColumns ( ) const
{
	return 3;
}

/* ---------------------------------------------------------------------------- */
