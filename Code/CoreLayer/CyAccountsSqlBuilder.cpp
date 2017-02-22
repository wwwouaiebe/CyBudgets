/* ---------------------------------------------------------------------------- */
//! CyAccountsSqlBuilder.cpp
/* ---------------------------------------------------------------------------- */
//!
//! \file CyAccountsSqlBuilder.cpp
//! \brief definition file for class CyAccountsSqlBuilder
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

#include "CoreLayer/CyAccountsSqlBuilder.h"
#include "DataLayer/CySqliteDb.h"
#include "DataLayer/CyLongValue.h"
#include "DataLayer/CyStringValue.h"
#include "UtilitiesLayer/CyEnum.h"
#include "UtilitiesLayer/CyGetText.h"

/* ---------------------------------------------------------------------------- */

CyAccountsSqlBuilder::CyAccountsSqlBuilder ( )
{
}

/* ---------------------------------------------------------------------------- */

CyAccountsSqlBuilder::~CyAccountsSqlBuilder ( )
{
}

/* ---------------------------------------------------------------------------- */

wxString CyAccountsSqlBuilder::getDialogTitle ( ) const
{
	return CyGetText::getInstance ( ).getText ( "CyAccountsSqlBuilder.getDialogTitle.AccountTitle" );
}

/* ---------------------------------------------------------------------------- */

wxString CyAccountsSqlBuilder::getDeleteSql ( long long lObjId ) const
{
	//
	//	strDeleteSql =
	//
	//	DELETE 
	//	FROM 
	//		Accounts 
	//	WHERE 
	//		objId = 10;
	//

	wxString strDeleteSql = wxEmptyString;

	strDeleteSql
		<< wxString ( "DELETE FROM Accounts WHERE objId = ") 
		<< lObjId
		<< wxString ( ";" );

	return strDeleteSql;
}

/* ---------------------------------------------------------------------------- */

 wxString CyAccountsSqlBuilder::getInsertSql ( const CyQueryResult::CyQueryResultValuesRow& newRow ) const
{
	//
	//	strInsertSql =
	//
	//	INSERT INTO 
	//		Accounts 
	//		( 
	//			ObjId, 
	//			AccountNumber, 
	//			AccountOwner, 
	//			CanBeImported, 
	//			ValidSinceDate, 
	//			InitialAmount 
	//		) 
	//		VALUES 
	//		( 
	//			(SELECT IFNULL ( MAX ( ObjId ), -1) + 1 FROM Accounts ),
	//			"123456",
	//			"Nouveau compte",
	//			0,
	//			"2015-02-06",
	//			0
	//		);
	//

	wxString strInsertSql = wxEmptyString;

	strInsertSql 
		<< wxString ( "INSERT INTO Accounts ( ObjId, AccountNumber, AccountOwner, CanBeImported, ValidSinceDate, InitialAmount ) " )
		<< wxString ( "VALUES ( (SELECT IFNULL ( MAX ( ObjId ), -1) + 1 FROM Accounts ), \"" )
		<< newRow.at ( CyAccountsSqlBuilder::kAccountNumber )->get ( CyStringValue::m_strDummyValue )
		<< wxString ( "\", \"" )
		<< newRow.at ( CyAccountsSqlBuilder::kAccountOwner )->get ( CyStringValue::m_strDummyValue )
		<< wxString ( "\", " )
		<< newRow.at ( CyAccountsSqlBuilder::kAccountImported )->get ( CyLongValue::m_lDummyValue )
		<< wxString ( ", \"" )
		<< newRow.at ( CyAccountsSqlBuilder::kAccountValidSinceDate )->get ( CyStringValue::m_strDummyValue )
		<< wxString ("\", " )
		<< newRow.at ( CyAccountsSqlBuilder::kAccountInitialAmount )->get ( CyLongValue::m_lDummyValue )
		<< wxString ( ");");

	return strInsertSql;
}

/* ---------------------------------------------------------------------------- */

void CyAccountsSqlBuilder::createRow ( CyQueryResult::CyQueryResultValuesRow& newRow ) const
{
	wxString strStringFormat;

	// Account ObjId...
	strStringFormat
		<< CyStartFormat 
		<< CyFormatHidden;
	CyLongValue* pObjId = new CyLongValue;
	pObjId->set ( CyEnum::kInvalidObjId, strStringFormat );
	newRow.push_back  ( pObjId );

	// ... account number...
	strStringFormat.clear ( );
	strStringFormat
		<< CyStartFormat 
		<< CyFormatString;
	CyStringValue* pAccountNumber = new CyStringValue;
	pAccountNumber->set ( wxString ( "" ), strStringFormat );
	newRow.push_back ( pAccountNumber );

	// ... account owner
	CyStringValue* pAccountOwner = new CyStringValue;
	pAccountOwner->set ( wxString ( "" ), strStringFormat );
	newRow.push_back ( pAccountOwner );

	// ... account can be imported....
	strStringFormat.clear ( );
	strStringFormat
		<< CyStartFormat 
		<< CyFormatBoolean;
	CyLongValue* pAccountCanBeImported = new CyLongValue;
	pAccountCanBeImported->set ( CyEnum::kNo, strStringFormat );
	newRow.push_back ( pAccountCanBeImported );

	// ... account valid since date...
	strStringFormat.clear ( );
	strStringFormat
		<< CyStartFormat 
		<< CyFormatDate;
	wxDateTime now;
	now.SetToCurrent ( );
	CyStringValue* pAccountValidSinceDate = new CyStringValue;
	pAccountValidSinceDate->set ( now.FormatISODate ( ), strStringFormat );
	newRow.push_back ( pAccountValidSinceDate );

	// ... account initial amount...
	strStringFormat.clear ( );
	strStringFormat
		<< CyStartFormat 
		<< CyFormatCurrency;
	CyLongValue* pAccountInitialAmount = new CyLongValue;
	pAccountInitialAmount->set ( 0, strStringFormat );
	newRow.push_back ( pAccountInitialAmount );

	// ... and account balance.
	strStringFormat.clear ( );
	strStringFormat
		<< CyStartFormat 
		<< CyFormatCurrency;
	CyLongValue* pAccountBalance = new CyLongValue;
	pAccountBalance->set ( 0, strStringFormat );
	newRow.push_back ( pAccountBalance );
}

/* ---------------------------------------------------------------------------- */

wxString CyAccountsSqlBuilder::getSelectSql ( ) const
{
	//
	//	strSelectSql =
	//
	//	SELECT 
	//		"➻∅" AS ➻, 
	//		a.ObjId, 
	//		"➻α" AS ➻, 
	//		a.AccountNumber AS "N° de compte",
	//		"➻α" AS ➻,
	//		a.AccountOwner AS "Description",
	//		"➻✓" AS ➻,
	//		a.CanBeImported AS "Importation",
	//		"➻≋" AS ➻,
	//		a.ValidSinceDate AS "Date d'ouverture",
	//		"➻€" AS ➻,
	//		a.InitialAmount AS "Montant initial",
	//		"➻€" AS ➻,
	//		IFNULL ( SUM ( o.Amount), 0) + a.InitialAmount AS "Solde" 
	//	FROM Accounts a LEFT OUTER JOIN Operations o ON a.ObjId = o.AccountObjId 
	//	GROUP BY o.AccountObjId 
	//	ORDER BY a.AccountNumber;
	//

	wxString strSelectSql = wxEmptyString;

	strSelectSql
		<< wxString ( "SELECT " )
		<< this->getFieldSql ( wxString ( "a.ObjId" ),wxEmptyString, CyFormatHidden )
		<< this->getFieldSql ( wxString ( "a.AccountNumber" ), CyGetText::getInstance ( ).getText ( "CyAccountsSqlBuilder.getSelectSql.AccountNumber" ), CyFormatString )
		<< this->getFieldSql ( wxString ( "a.AccountOwner"), CyGetText::getInstance ( ).getText ( "CyAccountsSqlBuilder.getSelectSql.AccountDescription" ), CyFormatString )
		<< this->getFieldSql ( wxString ( "a.CanBeImported"), CyGetText::getInstance ( ).getText ( "CyAccountsSqlBuilder.getSelectSql.AccountCanBeImported" ), CyFormatBoolean )
		<< this->getFieldSql ( wxString ( "a.ValidSinceDate"), CyGetText::getInstance ( ).getText ( "CyAccountsSqlBuilder.getSelectSql.AccountValidSinceDate" ), CyFormatDate )
		<< this->getFieldSql ( wxString ( "a.InitialAmount"), CyGetText::getInstance ( ).getText ( "CyAccountsSqlBuilder.getSelectSql.AccountInitialAmount" ), CyFormatCurrency )
		<< this->getFieldSql ( wxString ( "IFNULL ( SUM ( o.Amount), 0) + a.InitialAmount" ), CyGetText::getInstance ( ).getText ( "CyAccountsSqlBuilder.getSelectSql.Balance" ), CyFormatCurrency, true )
		<< wxString ( "FROM Accounts a LEFT OUTER JOIN Operations o ON a.ObjId = o.AccountObjId GROUP BY a.ObjId ORDER BY o.AccountObjId;" );

	return strSelectSql;
}

/* ---------------------------------------------------------------------------- */

wxString CyAccountsSqlBuilder::getUpdateSql ( const CyQueryResult::CyQueryResultValuesRow& newRow ) const
{
	//
	//	strUpdateSql =
	//
	//	UPDATE 
	//		Accounts 
	//	SET  
	//		AccountNumber = "123456" , 
	//		AccountOwner = "Nouveau compte modifié", 
	//		CanBeImported = 0, 
	//		ValidSinceDate = "2015-02-06", 
	//		InitialAmount = 0 
	//	WHERE 
	//		ObjId = 10 ;
	//

	wxString strUpdateSql = wxEmptyString;

	strUpdateSql 
		<< wxString ( "UPDATE Accounts SET " )
		<< wxString (" AccountNumber = \"")
		<< newRow.at ( CyAccountsSqlBuilder::kAccountNumber )->get ( CyStringValue::m_strDummyValue )
		<< wxString ( "\" , AccountOwner = \"" )
		<< newRow.at ( CyAccountsSqlBuilder::kAccountOwner )->get ( CyStringValue::m_strDummyValue )
		<< wxString ( "\", CanBeImported = " )
		<< newRow.at ( CyAccountsSqlBuilder::kAccountImported )->get ( CyLongValue::m_lDummyValue )
		<< wxString ( ", ValidSinceDate = \"" )
		<< newRow.at ( CyAccountsSqlBuilder::kAccountValidSinceDate )->get ( CyStringValue::m_strDummyValue )
		<< wxString ( "\", InitialAmount = " )
		<< newRow.at ( CyAccountsSqlBuilder::kAccountInitialAmount )->get ( CyLongValue::m_lDummyValue )
		<< wxString ( " WHERE ObjId = " )
		<< newRow.at ( CyAccountsSqlBuilder::kAccountObjId )->get ( CyLongValue::m_lDummyValue)
		<< wxString ( " ;" );

	return strUpdateSql;
}

/* ---------------------------------------------------------------------------- */

int CyAccountsSqlBuilder::getHiddenColumns ( ) const
{
	return 1;
}

/* ---------------------------------------------------------------------------- */

bool CyAccountsSqlBuilder::doUpdate ( const CyQueryResult::CyQueryResultValuesRow& newRow  ) const
{
	// update of the Accounts table
	bool bTranactionOk = CySqliteDb::getInstance ( ).executeSql ( wxString ( "BEGIN EXCLUSIVE TRANSACTION;") );

	bTranactionOk &= CySqliteDb::getInstance ( ).executeSql ( this->getUpdateSql ( newRow ) );
	if  ( bTranactionOk )
	{
		CySqliteDb::getInstance ( ).executeSql ( wxString ( "COMMIT;") );
		
		// the account balance is recomputed, due to a possible modification of the account initial amount in the edit account dialog box

		//		
		//		strSql =
		//
		//		SELECT IFNULL ( SUM ( o.Amount), 0) 
		//			FROM Operations o 
		//			WHERE o.AccountObjId = 10 ;
		//

		wxString strSql = wxEmptyString;
		strSql
			<< wxString ( "SELECT IFNULL ( SUM ( o.Amount), 0) FROM Operations o WHERE o.AccountObjId = " )
			<< newRow.at ( CyAccountsSqlBuilder::kAccountObjId )->get ( CyLongValue::m_lDummyValue )
			<< wxString (" ;");

		CySqliteDb::getInstance ( ).getSingleValue ( strSql, newRow.at ( CyAccountsSqlBuilder::kAccountBalance ) );
	}
	else
	{
		CySqliteDb::getInstance ( ).executeSql ( wxString ( "ROLLBACK;") );
	}

	return bTranactionOk;
}

/* ---------------------------------------------------------------------------- */
