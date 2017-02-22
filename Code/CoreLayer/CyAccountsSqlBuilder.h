/* ---------------------------------------------------------------------------- */
//! CyAccountsSqlBuilder.h
/* ---------------------------------------------------------------------------- */
//!
//! \file CyAccountsSqlBuilder.h
//! \brief header file for class CyAccountsSqlBuilder
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


/* ---------------------------------------------------------------------------- */

#pragma once

/* ---------------------------------------------------------------------------- */

#include "CoreLayer/CySqlBuilder.h"

/* ---------------------------------------------------------------------------- */

//! \class CyAccountsSqlBuilder
//! \brief Helper class for SQL operations for the accounts 
//!
//! \since version 1.0.3

class CyAccountsSqlBuilder: public CySqlBuilder
{

	public:

		//! \fn CyAccountsSqlBuilder ( ) 
		//! constructor

		CyAccountsSqlBuilder ( );

		//! \fn ~CyAccountsSqlBuilder ( ) 
		//! destructor

		~CyAccountsSqlBuilder ( );

		//! \fn getDialogTitle ( ) const
		//!
		//! This method gives the title to add to the dialog used with this object
		//! \return the dialog title

		virtual wxString getDialogTitle ( ) const;

		//! \fn getHiddenColumns ( ) const
		//!
		//! This method gives the number of columns to be hidden on the dialog using this object
		//! \return the number of hidden columns

		virtual int getHiddenColumns ( ) const;

		//! \fn createRow ( CyQueryResult::CyQueryResultValuesRow& newRow ) const
		//! @param [ in ] newRow a reference to a vector to witch new values are added
		//!
		//! This method add values to a vector of type CyQueryResult::CyQueryResultValuesRow

		void createRow ( CyQueryResult::CyQueryResultValuesRow& newRow ) const;

		//! \fn doUpdate ( const CyQueryResult::CyQueryResultValuesRow& newRow  ) const
		//! @param [ in ] newRow a reference to a vector for witch values are aupdated
		//!
		//! special version of the doUpdate method of the base class due to recoputation of the account balnce after update.
		//! \return true when the update is successfull

		virtual bool doUpdate ( const CyQueryResult::CyQueryResultValuesRow& newRow  ) const;

		//! \enum ColumnPosition
		//! values for fields position in the query results
		//!
		//! \var kAccountObjId
		//! The ObjId field of the table Accounts
		//!
		//! \var kAccountNumber
		//! The AccountNumber field of the table Accounts
		//!
		//! \var kAccountOwner
		//! The AccountOwner field of the table Accounts
		//!
		//! \var kAccountImported
		//! The CanBeImported field of the table Accounts
		//!
		//! \var kAccountValidSinceDate
		//! The ValidSinceDate field of the table Accounts
		//! 
		//! \var kAccountInitialAmount
		//! The InitialAmount field of the table Accounts
		//!
		//! \var kAccountBalance
		//! The Account Balance computed in the Select statement

		enum ColumnPosition
		{
			kAccountObjId = 0,
			kAccountNumber = 1,
			kAccountOwner = 2,
			kAccountImported = 3,
			kAccountValidSinceDate = 4,
			kAccountInitialAmount = 5,
			kAccountBalance = 6
		};

	protected:

		//! \fn getDeleteSql ( long long lObjId ) const
		//! @param [ in ] lObjId the ObjId of the row to delete
		//!
		//! \return the SQL instruction to delete a row in a table. Used by the base class method doDelete ( )

		virtual wxString getDeleteSql ( long long lObjId ) const;

		//! \fn getInsertSql ( const CyQueryResult::CyQueryResultValuesRow& newRow ) const
		//! @param [ in ] newRow a reference to a vector of type  CyQueryResult::CyQueryResultValuesRow with the values to insert
		//!
		//! \return the SQL instruction to insert a row in a table. Used by the base class method doInsert ( )

		virtual wxString getInsertSql ( const CyQueryResult::CyQueryResultValuesRow& newRow ) const;

		//! \fn wxString getSelectSql ( ) const
		//!
		//! \return the SQL instruction to select rows in a table. Used by the base class method doSelect ( )

		virtual wxString getSelectSql ( ) const;

		//! \fn wxString getUpdateSql ( const CyQueryResult::CyQueryResultValuesRow& newRow ) const
		//! @param [ in ] newRow a reference to a vector of type  CyQueryResult::CyQueryResultValuesRow with the values to update
		//!
		//! \return the SQL instruction to update a row in a table. Used by the base class method doInsert ( )

		virtual wxString getUpdateSql ( const CyQueryResult::CyQueryResultValuesRow& newRow ) const;

	private:

		//! \fn CyAccountsSqlBuilder ( const CyAccountsSqlBuilder& ) 
		//! copy constructor
		//! not implemented

		CyAccountsSqlBuilder ( const CyAccountsSqlBuilder& );

		//! \fn operator = ( const CyAccountsSqlBuilder& ) 
		//! operator =
		//! \return a reference to a CyAccountsSqlBuilder object
		//! not implemented

		CyAccountsSqlBuilder& operator = ( const CyAccountsSqlBuilder& );

};

/* ---------------------------------------------------------------------------- */
