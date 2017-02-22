/* ---------------------------------------------------------------------------- */
//! CyOperationsAttributionsSqlBuilder.cpp
/* ---------------------------------------------------------------------------- */
//!
//! \file CyOperationsAttributionsSqlBuilder.cpp
//! \brief definition file for class CyOperationsAttributionsSqlBuilder
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

#include "CoreLayer/CyOperationsAttributionsSqlBuilder.h"
#include "DataLayer/CyLongValue.h"
#include "DataLayer/CyStringValue.h"
#include "UtilitiesLayer/CyEnum.h"

/* ---------------------------------------------------------------------------- */

CyOperationsAttributionsSqlBuilder::CyOperationsAttributionsSqlBuilder (  long long lOperationObjId  ):
	m_lOperationObjId ( lOperationObjId )
{
}

/* ---------------------------------------------------------------------------- */

CyOperationsAttributionsSqlBuilder::~CyOperationsAttributionsSqlBuilder ( )
{
}

/* ---------------------------------------------------------------------------- */

wxString CyOperationsAttributionsSqlBuilder::getDialogTitle ( ) const
{
	return wxEmptyString;
}

/* ---------------------------------------------------------------------------- */

wxString CyOperationsAttributionsSqlBuilder::getDeleteSql ( long long lOperationObjId ) const
{
	//
	//	strDeleteSql =
	//
	//	DELETE 
	//	FROM 
	//		OperationsAttributions 
	//	WHERE 
	//		OperationObjId = 4221;
	//

	wxString strDeleteSql = wxEmptyString;

	strDeleteSql
		<< wxString ( "DELETE FROM OperationsAttributions WHERE OperationObjId = " )
		<< lOperationObjId
		<< wxString ( ";");

	return strDeleteSql;
}

/* ---------------------------------------------------------------------------- */

 wxString CyOperationsAttributionsSqlBuilder::getInsertSql (  const CyQueryResult::CyQueryResultValuesRow& newRow) const
{

	//
	//	strInsertSql =
	//
	//	INSERT INTO 
	//		OperationsAttributions 
	//		( 
	//			ObjId, 
	//			AttributionObjId, 
	//			OperationObjId, 
	//			Amount 
	//		) 
	//		VALUES 
	//		( 
	//			( SELECT IFNULL ( MAX ( ObjId ), -1) + 1 FROM OperationsAttributions ),
	//			8, 
	//			4221,
	//			3000 
	//		);
	//

	wxString strInsertSql = wxEmptyString;

	strInsertSql
		<< wxString ( "INSERT INTO OperationsAttributions ( ObjId, AttributionObjId, OperationObjId, Amount ) VALUES ( " )
		<< wxString ( "( SELECT IFNULL ( MAX ( ObjId ), -1) + 1 FROM OperationsAttributions )" )
		<< wxString ( ", " )
		<< newRow.at ( CyOperationsAttributionsSqlBuilder::kAtributionObjId )->get ( CyLongValue::m_lDummyValue )
		<< wxString ( ", " )
		<< newRow.at ( CyOperationsAttributionsSqlBuilder::kOperationObjId )->get ( CyLongValue::m_lDummyValue )
		<< wxString ( ", " )
		<< newRow.at ( CyOperationsAttributionsSqlBuilder::kAttributionOperationAmount )->get ( CyLongValue::m_lDummyValue )
		<< wxString ( " );" );

	return strInsertSql;
}

/* ---------------------------------------------------------------------------- */

void CyOperationsAttributionsSqlBuilder::createRow ( CyQueryResult::CyQueryResultValuesRow& newRow ) const
{
	wxString strStringFormat;
	// OperationsAttributions ObjId...
	strStringFormat
		<< CyStartFormat 
		<< CyFormatHidden;
	CyLongValue* pOperationAttributionObjId = new CyLongValue;
	pOperationAttributionObjId->set ( CyEnum::kInvalidObjId, strStringFormat );
	newRow.push_back  ( pOperationAttributionObjId );

	// ...OperationsAttributions OperationObjId...
	CyLongValue* pOperationObjId = new CyLongValue;
	pOperationObjId->set ( CyEnum::kInvalidObjId, strStringFormat );
	newRow.push_back  ( pOperationObjId );

	// ...Attributions ObjId... 
	CyLongValue* pAttributionObjId = new CyLongValue;
	pAttributionObjId->set ( CyEnum::kInvalidObjId, strStringFormat );
	newRow.push_back  ( pAttributionObjId );

	// ...AttributionsGroups Description ... 
	strStringFormat.clear ( );
	strStringFormat
		<< CyStartFormat 
		<< CyFormatString;
	CyStringValue* pAttributionGroupDescription = new CyStringValue;
	pAttributionGroupDescription->set ( wxString ( "" ), strStringFormat );
	newRow.push_back ( pAttributionGroupDescription );

	// ...Attributions Description ... 
	strStringFormat.clear ( );
	strStringFormat
		<< CyStartFormat 
		<< CyFormatString;
	CyStringValue* pAttributionDescription = new CyStringValue;
	pAttributionDescription->set ( wxString ( "" ), strStringFormat );
	newRow.push_back ( pAttributionDescription );

	// ...OperationsAttributions Amount
	strStringFormat.clear ( );
	strStringFormat
		<< CyStartFormat 
		<< CyFormatCurrency;
	CyLongValue* pAmount = new CyLongValue;
	pAmount->set ( 0, strStringFormat );
	newRow.push_back ( pAmount );
}

/* ---------------------------------------------------------------------------- */

wxString CyOperationsAttributionsSqlBuilder::getSelectSql () const
{
	//
	//	strSelectSql =
	//
	//	SELECT 
	//		"➻∅" AS ➻, 
	//		ao.ObjId, 
	//		"➻∅" AS ➻,
	//		ao.OperationObjId,
	//		"➻∅" AS ➻,
	//		a.ObjId,
	//		"➻α" AS ➻,
	//		g.GroupDescription,
	//		"➻α" AS ➻, 
	//		a.Description,
	//		"➻€" AS ➻,
	//		ao.Amount 
	//	FROM 
	//		OperationsAttributions ao 
	//		LEFT JOIN Attributions a on ao.AttributionObjId = a.ObjId 
	//		LEFT JOIN AttributionsGroups g on a.GroupObjId = g.ObjId 
	//	WHERE 
	//		ao.OperationObjId = 4221;
	//

	wxString strSelectSql = wxEmptyString;

	if ( CyEnum::kInvalidObjId != this ->m_lOperationObjId )
	{
		strSelectSql
			<< wxString ( "SELECT " )
			<< this->getFieldSql ( wxString ( "ao.ObjId" ),wxEmptyString, CyFormatHidden )
			<< this->getFieldSql ( wxString ( "ao.OperationObjId" ), wxEmptyString, CyFormatHidden )
			<< this->getFieldSql ( wxString ( "a.ObjId"), wxEmptyString, CyFormatHidden )
			<< this->getFieldSql ( wxString ( "g.GroupDescription"), wxEmptyString, CyFormatString )
			<< this->getFieldSql ( wxString ( "a.Description"), wxEmptyString, CyFormatString )
			<< this->getFieldSql ( wxString ( "ao.Amount"), wxEmptyString, CyFormatCurrency, true )
			<< wxString ( "FROM OperationsAttributions ao LEFT JOIN Attributions a on ao.AttributionObjId = a.ObjId LEFT JOIN AttributionsGroups g on a.GroupObjId = g.ObjId WHERE ao.OperationObjId = " )
			<< this->m_lOperationObjId
			<< wxString ( ";" );
	}

	return strSelectSql;
}

/* ---------------------------------------------------------------------------- */

wxString CyOperationsAttributionsSqlBuilder::getUpdateSql ( const CyQueryResult::CyQueryResultValuesRow& ) const
{
	return wxEmptyString;
}

/* ---------------------------------------------------------------------------- */

int CyOperationsAttributionsSqlBuilder::getHiddenColumns ( ) const
{
	return 1;
}

/* ---------------------------------------------------------------------------- */
