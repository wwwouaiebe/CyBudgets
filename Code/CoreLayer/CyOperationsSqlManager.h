/* ---------------------------------------------------------------------------- */
//! CyOperationsSqlManager.h
/* ---------------------------------------------------------------------------- */
//!
//! \file CyOperationsSqlManager.h
//! \brief header file for class CyOperationsSqlManager
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

#pragma once

/* ---------------------------------------------------------------------------- */

#include "UtilitiesLayer/CyWxIncludes.h"
#include "DataLayer/CyQueryResult.h"

/* ---------------------------------------------------------------------------- */

class CySqlBuilder;
class CyOperationsAttributionsSqlBuilder;
class CyOperationsDetailsSqlBuilder;

/* ---------------------------------------------------------------------------- */

//! \class CyOperationsSqlManager
//! \brief Helper class for SQL operations for the operations
//!
//! this class manage the CyOperationsSqlBuilder, CyOperationsAttributionsSqlBuilder and CyOperationsDetailsSqlBuilder objects
//! used to edit the operations
//!
//! \since version 1.0.3

class CyOperationsSqlManager
{

	public:

		//! \fn CyOperationsSqlManager ( CySqlBuilder* pOperationsSqlBuilder, const  wxString& strAccountNumber )
		//! @param [ in ] pOperationsSqlBuilder a pointer to the CyOperationSqlBuilder used by the CyWxShowRequestOperationsMediator object
		//! @param [ in ] strAccountNumber the account number for witch the opearation is added
		//! constructor
		//!
		//! This constructor is used from tha CyWxShowRequestOperationsMediator object when adding a new operation

		CyOperationsSqlManager ( CySqlBuilder* pOperationsSqlBuilder, const  wxString& strAccountNumber );

		//! \fn CyOperationsSqlManager ( CySqlBuilder* pOperationsSqlBuilder, CyQueryResult::CyQueryResultValuesRow* pNewRow  )
		//! @param [ in ] pOperationsSqlBuilder a pointer to the CyOperationSqlBuilder used by the CyWxShowRequestOperationsMediator object
		//! @param [ in ] pNewRow a pointer to the edited operation
		//! constructor
		//!
		//! This constructor is used from tha CyWxShowRequestOperationsMediator object when editing an existing operation

		CyOperationsSqlManager ( CySqlBuilder* pOperationsSqlBuilder, CyQueryResult::CyQueryResultValuesRow* pNewRow );

		//! \fn ~CyOperationsSqlManager ( ) 
		//! destructor

		virtual ~CyOperationsSqlManager ( );

		//! \fn doDelete ( )
		//! This method performs the DELETE SQL operations for an operation
		//! \return true when the SQL operation is successfull

		bool doDelete ( );

		//! \fn doSelect ( )
		//! This method performs the SELECT SQL operations for an operation
		//! \return true when the SQL operation is successfull

		void doSelect ( );

		//! \fn doInsert ( )
		//! This method performs the INSERT SQL operations for an operation
		//! \return true when the SQL operation is successfull

		bool doInsert ( );

		//! \fn doUpdate ( )
		//! This method performs the UPDATE SQL operations for an operation
		//! \return true when the SQL operation is successfull

		bool doUpdate ( );

		//! \fn getRow ( )
		//! \return the CyQueryResult::CyQueryResultValuesRow for the edited operation

		CyQueryResult::CyQueryResultValuesRow* getRow ( );

		//! \fn createNewAttributionRow ( CyQueryResult::CyQueryResultValuesRow& newRow ) const
		//! @param [ in ] newRow a reference to a CyQueryResult::CyQueryResultValuesRow to witch values are added
		//! This method add values for attributions to an CyQueryResult::CyQueryResultValuesRow object

		void createNewAttributionRow ( CyQueryResult::CyQueryResultValuesRow& newRow ) const;

		//! \fn CyQueryResult& getOperationsAttributionsQueryResult ( )
		//! This method gives the attributions linked to the edited operation
		//! \return a reference to a CyQueryResult object with the attributions

		CyQueryResult& getOperationsAttributionsQueryResult ( );

		//! \fn CyQueryResult& getOperationsDetailsQueryResult ( )
		//! This method gives the details linked to the edited operation
		//! \return a reference to a CyQueryResult object with the details

		const CyQueryResult& getOperationsDetailsQueryResult ( ) const;

	private:

		//! \fn CyOperationsSqlManager ( const CyOperationsSqlManager& ) 
		//! copy constructor
		//! not implemented

		CyOperationsSqlManager ( const CyOperationsSqlManager& );

		//! \fn operator = ( const CyOperationsSqlManager& ) 
		//! operator =
		//! \return a reference to a CyOperationsSqlManager object
		//! not implemented

		CyOperationsSqlManager& operator = (const CyOperationsSqlManager& );

		//! \var m_pNewRow
		//! a pointer to the edited operation

		CyQueryResult::CyQueryResultValuesRow* m_pNewRow;

		//! \var m_pOperationsSqlBuilder
		//! a pointer to the CyOperationsSqlBuilder used

		CySqlBuilder* m_pOperationsSqlBuilder;

		//! \var m_pOperationsAttributionsSqlBuilder
		//! a pointer to the CyOperationsAttributionsSqlBuilder used

		CyOperationsAttributionsSqlBuilder* m_pOperationsAttributionsSqlBuilder;

		//! \var m_pOperationsDetailsSqlBuilder
		//! a pointer to the CyOperationsDetailsSqlBuilder used

		CyOperationsDetailsSqlBuilder* m_pOperationsDetailsSqlBuilder;

		//! \var m_objOperationsAttributionsQueryResult
		//! the attributions linked to the edited operation

		CyQueryResult m_objOperationsAttributionsQueryResult;

		//! \var m_objOperationsDetailsQueryResult
		//! the details linked to the edited operation

		CyQueryResult m_objOperationsDetailsQueryResult;

		//! \var m_bDeleteRow
		//! a boolean indicating if the row saved in the m_pNewRow variable must be cleaned
		//! in the destructor ( for the add operations ) or not ( for the edit operations )

		bool m_bDeleteRow;

		//! \var m_lOperationObjId
		//! The ObjId of the edited operation

		long long m_lOperationObjId;
};