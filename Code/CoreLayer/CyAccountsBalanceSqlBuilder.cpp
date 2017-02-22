/* ---------------------------------------------------------------------------- */
//! CyAccountsBalanceSqlBuilder.cpp
/* ---------------------------------------------------------------------------- */
//!
//! \file CyAccountsBalanceSqlBuilder.cpp
//! \brief definition file for class CyAccountsBalanceSqlBuilder
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

#include "CoreLayer/CyAccountsBalanceSqlBuilder.h"
#include "DataLayer/CySqliteDb.h"
#include "UtilitiesLayer/CyEnum.h"
#include "UtilitiesLayer/CyGetText.h"

/* ---------------------------------------------------------------------------- */

CyAccountsBalanceSqlBuilder::CyAccountsBalanceSqlBuilder ( long long lAccountObjId ):
m_lAccountObjId ( lAccountObjId )
{
}

/* ---------------------------------------------------------------------------- */

CyAccountsBalanceSqlBuilder::~CyAccountsBalanceSqlBuilder ( )
{
}

/* ---------------------------------------------------------------------------- */

wxString CyAccountsBalanceSqlBuilder::getDialogTitle ( ) const
{
	wxString strDialogTitle = CyGetText::getInstance ( ).getText ( "CyAccountsBalanceSqlBuilder.getDialogTitle.AccountsBalanceTitle" );

	if ( CyEnum::kInvalidObjId != this->m_lAccountObjId )
	{
		// An account was selected in the combo box of the frame. Searching the account number
		wxString strAccountNumber = wxEmptyString;
		wxString strSql;
		strSql
			<< wxString ( "SELECT AccountNumber FROM Accounts WHERE ObjId = ")
			<< this->m_lAccountObjId
			<< wxString ( ";");
		if ( CySqliteDb::getInstance ( ).getSingleValue ( strSql, &strAccountNumber ) )
		{
			// The account number is found in the dB. Adding the account number to the dialog title
			strDialogTitle
				<< wxString ( " - " )
				<< CyGetText::getInstance ( ).getText ( "CyAccountsBalanceSqlBuilder.getDialogTitle.AccountTitle" )
				<< wxString ( " " )
				<< strAccountNumber;
		}
	}

	return strDialogTitle;
}

/* ---------------------------------------------------------------------------- */

wxString CyAccountsBalanceSqlBuilder::getDeleteSql ( long long ) const
{
	// Not implemented in this class
	return wxEmptyString;
}

/* ---------------------------------------------------------------------------- */

 wxString CyAccountsBalanceSqlBuilder::getInsertSql ( const CyQueryResult::CyQueryResultValuesRow& ) const
{
	// Not implemented in this class
	return wxEmptyString;
}

/* ---------------------------------------------------------------------------- */

void CyAccountsBalanceSqlBuilder::createRow ( CyQueryResult::CyQueryResultValuesRow& ) const
{
	// Not implemented in this class
}

/* ---------------------------------------------------------------------------- */

wxString CyAccountsBalanceSqlBuilder::getSelectSql ( ) const
{

	wxString strSelectSql = wxEmptyString;
	wxString strWhereClause = wxEmptyString;
	wxString strSumWhereClause = wxEmptyString;

	if ( CyEnum::kInvalidObjId !=  this->m_lAccountObjId )
	{
		// An account was selected in the combo box of the frame. Preparing the WHERE clauses
		strWhereClause 
			<< wxString ( "WHERE a.ObjId = " )
			<< this->m_lAccountObjId 
			<< wxString ( " " );
		strSumWhereClause
			<< wxString ( "  AND o1.AccountObjId = o.AccountObjId" );
	}

	//
	//	strSelectSql = with an account :
	//
	//	SELECT 
	//		"➻≋" AS ➻, 
	//		o.ValueDate  AS "date", 
	//		"➻€" AS ➻, 
	//		(SELECT SUM ( o1.Amount ) FROM Operations o1 WHERE o1.ValueDate <= o.ValueDate   AND o1.AccountObjId = o.AccountObjId ) AS "Solde" 
	//	FROM 
	//		Operations o JOIN Accounts a ON o.AccountObjId = a.ObjId 
	//	WHERE
	//		a.ObjId = 2 
	//	GROUP BY 
	//		o.ValueDate 
	//	ORDER BY
	//		o.ValueDate DESC;
	//	
	//	strSelectSql = without account :
	//	
	//	SELECT 
	//		"➻≋" AS ➻, 
	//		o.ValueDate  AS "date", 
	//		"➻€" AS ➻, 
	//		(SELECT SUM ( o1.Amount ) FROM Operations o1 WHERE o1.ValueDate <= o.ValueDate  ) AS "Solde" 
	//	FROM 
	//		Operations o JOIN Accounts a ON o.AccountObjId = a.ObjId 
	//	GROUP BY 
	//		o.ValueDate 
	//	ORDER BY 
	//		o.ValueDate DESC;
	//

	strSelectSql
		<< wxString ( "SELECT " )
		<< this->getFieldSql ( wxString ( "o.ValueDate "), CyGetText::getInstance ( ).getText ( "CyAccountsBalanceSqlBuilder.getSelectSql.ValueDate" ), CyFormatDate )
		<< this->getFieldSql ( 
				wxString ( "(SELECT SUM ( o1.Amount ) FROM Operations o1 WHERE o1.ValueDate <= o.ValueDate " ) + strSumWhereClause + wxString ( " )"),
				CyGetText::getInstance ( ).getText ( "CyAccountsBalanceSqlBuilder.getSelectSql.Amount" ),
				CyFormatCurrency,
				true )
		<< wxString ( "FROM Operations o JOIN Accounts a ON o.AccountObjId = a.ObjId " )
		<< strWhereClause
		<< wxString ( "GROUP BY o.ValueDate ORDER BY o.ValueDate DESC;" );

	return strSelectSql;
}

/* ---------------------------------------------------------------------------- */

wxString CyAccountsBalanceSqlBuilder::getUpdateSql ( const CyQueryResult::CyQueryResultValuesRow& ) const
{
	// Not implemented in this class
	return wxEmptyString;
}

/* ---------------------------------------------------------------------------- */

int CyAccountsBalanceSqlBuilder::getHiddenColumns ( ) const
{
	return 0;
}

/* ---------------------------------------------------------------------------- */
