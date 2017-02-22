/* ---------------------------------------------------------------------------- */
//! CyOperationsSqlManager.cpp
/* ---------------------------------------------------------------------------- */
//!
//! \file CyOperationsSqlManager.cpp
//! \brief definition file for class CyOperationsSqlManager
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

#include "CoreLayer/CyOperationsSqlManager.h"
#include "CoreLayer/CyOperationsSqlBuilder.h"
#include "CoreLayer/CyOperationsAttributionsSqlBuilder.h"
#include "CoreLayer/CyOperationsDetailsSqlBuilder.h"
#include "DataLayer/CySqliteDb.h"
#include "DataLayer/CyLongValue.h"
#include "DataLayer/CyStringValue.h"
#include "UtilitiesLayer/CyEnum.h"

/* ---------------------------------------------------------------------------- */

CyOperationsSqlManager::CyOperationsSqlManager ( CySqlBuilder* pOperationsSqlBuilder, const wxString& strAccountNumber ):
m_pOperationsSqlBuilder ( pOperationsSqlBuilder ),
m_bDeleteRow ( true )
{
	// a new row for the operation is created
	this->m_pNewRow = new CyQueryResult::CyQueryResultValuesRow;
	this->m_pOperationsSqlBuilder->createRow ( *( this->m_pNewRow ) );
	this->m_pNewRow->at ( CyOperationsSqlBuilder::kOperationAccountNumber )->set ( strAccountNumber );

	// The operation ObjId is searched
	this->m_lOperationObjId = m_pNewRow->at ( CyOperationsSqlBuilder::kOperationObjId )->get ( CyLongValue::m_lDummyValue );

	// and CySqlBuilder for attributions and details are created
	this->m_pOperationsAttributionsSqlBuilder = new CyOperationsAttributionsSqlBuilder ( this->m_lOperationObjId );
	this->m_pOperationsDetailsSqlBuilder = new CyOperationsDetailsSqlBuilder ( this->m_lOperationObjId );

	// and attributions and details are searched
	this->doSelect ( );
}

/* ---------------------------------------------------------------------------- */

CyOperationsSqlManager::CyOperationsSqlManager ( CySqlBuilder* pOperationsSqlBuilder, CyQueryResult::CyQueryResultValuesRow* pNewRow ):
m_pOperationsSqlBuilder ( pOperationsSqlBuilder ),
m_pNewRow ( pNewRow ),
m_bDeleteRow ( false )
{
	// The operation ObjId is searched
	this->m_lOperationObjId = m_pNewRow->at ( CyOperationsSqlBuilder::kOperationObjId )->get ( CyLongValue::m_lDummyValue );

	// and CySqlBuilder for operations and details are created
	this->m_pOperationsAttributionsSqlBuilder = new CyOperationsAttributionsSqlBuilder ( this->m_lOperationObjId );
	this->m_pOperationsDetailsSqlBuilder = new CyOperationsDetailsSqlBuilder ( this->m_lOperationObjId );

	// and attributions and details are searched
	this->doSelect ( );
}

/* ---------------------------------------------------------------------------- */

CyOperationsSqlManager::~CyOperationsSqlManager ( )
{
	if ( this->m_bDeleteRow )
	{
		this->m_pNewRow->clear ( );
		delete this->m_pNewRow;
	}

	delete this->m_pOperationsAttributionsSqlBuilder;
	delete this->m_pOperationsDetailsSqlBuilder;
}

/* ---------------------------------------------------------------------------- */

bool CyOperationsSqlManager::doDelete ( )
{
	bool bTransactionOk = true;

	bTransactionOk &= CySqliteDb::getInstance ( ).executeSql ( wxString ( "BEGIN TRANSACTION;") );
	bTransactionOk &= this->m_pOperationsSqlBuilder->doDelete ( this->m_lOperationObjId );
	bTransactionOk &= this->m_pOperationsAttributionsSqlBuilder->doDelete ( this->m_lOperationObjId );
	bTransactionOk &= this->m_pOperationsDetailsSqlBuilder->doDelete ( this->m_lOperationObjId );
	if ( bTransactionOk )
	{
		// Commit
		CySqliteDb::getInstance ( ).executeSql ( wxString ( "COMMIT;") );
		return true;
	}
	else
	{
		// or Rollback
		CySqliteDb::getInstance ( ).executeSql ( wxString ( "ROLLBACK TRANSACTION;") );
		return false;
	}
}

/* ---------------------------------------------------------------------------- */

void CyOperationsSqlManager::doSelect ( )
{
	if ( CyEnum::kInvalidObjId != this->m_lOperationObjId )
	{
		this->m_pOperationsAttributionsSqlBuilder->doSelect ( this->m_objOperationsAttributionsQueryResult );
		this->m_pOperationsDetailsSqlBuilder->doSelect ( this->m_objOperationsDetailsQueryResult );
	}
}

/* ---------------------------------------------------------------------------- */

bool CyOperationsSqlManager::doInsert ( )
{
	bool bTransactionOk = true;
	bTransactionOk &= CySqliteDb::getInstance ( ).executeSql ( wxString ( "BEGIN TRANSACTION;") );

	long long lOperationObjId = CyEnum::kInvalidObjId;
	bTransactionOk &= CySqliteDb::getInstance ( ).getSingleValue ( wxString ( "SELECT IFNULL ( MAX ( ObjId ), -1) + 1 FROM Operations"), &lOperationObjId);

	bTransactionOk &= this->m_pOperationsSqlBuilder->doInsert ( *( this->m_pNewRow ) );
	CyQueryResult::iterator iterator;
	for (iterator = this->m_objOperationsAttributionsQueryResult.begin ( ); iterator != this->m_objOperationsAttributionsQueryResult.end ( ); ++ iterator )
	{
		iterator->at ( CyOperationsAttributionsSqlBuilder::kOperationObjId )->set ( lOperationObjId );
		bTransactionOk &= this->m_pOperationsAttributionsSqlBuilder->doInsert ( *iterator );
	}

	if ( bTransactionOk )
	{
		// Commit
		CySqliteDb::getInstance ( ).executeSql ( wxString ( "COMMIT;") );
		return true;
	}
	else
	{
		// or Rollback
		CySqliteDb::getInstance ( ).executeSql ( wxString ( "ROLLBACK TRANSACTION;") );
		return false;
	}
}

/* ---------------------------------------------------------------------------- */

bool CyOperationsSqlManager::doUpdate ( )
{

	bool bTransactionOk = true;
	// starting a transaction
	bTransactionOk &= CySqliteDb::getInstance ( ).executeSql ( wxString ( "BEGIN EXCLUSIVE TRANSACTION;") );
	bTransactionOk &= this->m_pOperationsSqlBuilder->doUpdate ( *( this->m_pNewRow ) );

	bTransactionOk = this->m_pOperationsAttributionsSqlBuilder->doDelete ( this->m_lOperationObjId );
	CyQueryResult::const_iterator iterator;
	for ( iterator = this->m_objOperationsAttributionsQueryResult.begin ( ); iterator != this->m_objOperationsAttributionsQueryResult.end ( ); ++ iterator) 
	{
		bTransactionOk &= this->m_pOperationsAttributionsSqlBuilder->doInsert ( *iterator );
	}

	// Commit or Rollback
	if ( bTransactionOk )
	{
	// Commit
		CySqliteDb::getInstance ( ).executeSql ( wxString ( "COMMIT;") );
		return true;
	}
	else
	{
		// or Rollback
		CySqliteDb::getInstance ( ).executeSql ( wxString ( "ROLLBACK TRANSACTION;") );
		return false;
	}
}

/* ---------------------------------------------------------------------------- */

CyQueryResult::CyQueryResultValuesRow* CyOperationsSqlManager::getRow ( )
{
	return this->m_pNewRow;
}

/* ---------------------------------------------------------------------------- */

CyQueryResult& CyOperationsSqlManager::getOperationsAttributionsQueryResult ( )
{
	return this->m_objOperationsAttributionsQueryResult;
}

/* ---------------------------------------------------------------------------- */

const CyQueryResult& CyOperationsSqlManager::getOperationsDetailsQueryResult ( ) const
{
	return this->m_objOperationsDetailsQueryResult;
}

/* ---------------------------------------------------------------------------- */

void CyOperationsSqlManager::createNewAttributionRow ( CyQueryResult::CyQueryResultValuesRow& newRow ) const
{
	this->m_pOperationsAttributionsSqlBuilder->createRow ( newRow );
	newRow.at ( CyOperationsAttributionsSqlBuilder::kOperationObjId )->set ( this->m_lOperationObjId );
}

/* ---------------------------------------------------------------------------- */
