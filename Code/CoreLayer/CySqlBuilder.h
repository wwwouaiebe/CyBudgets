/* ---------------------------------------------------------------------------- */
//! CySqlBuilder.h
/* ---------------------------------------------------------------------------- */
//!
//! \file CySqlBuilder.h
//! \brief header file for class CySqlBuilder
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

#include "DataLayer/CyQueryResult.h"
#include "UtilitiesLayer/CyWxIncludes.h"

/* ---------------------------------------------------------------------------- */

//! \class CySqlBuilder
//! \brief base class for helper class for SQL operations
//!
//! \since version 1.0.3

class CySqlBuilder
{

	public:

		//! \fn CySqlBuilder ( ) 
		//! constructor

		CySqlBuilder ( );

		//! \fn ~CySqlBuilder ( ) 
		//! destructor

		virtual ~CySqlBuilder ( );

		//! \fn getDialogTitle ( ) const
		//!
		//! This method gives the title to add to the dialog used with this object
		//! \return the dialog title

		virtual wxString getDialogTitle ( ) const = 0;

		//! \fn getHiddenColumns ( ) const
		//!
		//! This method gives the number of columns to be hidden on the dialog using this object
		//! \return the number of hidden columns

		virtual int getHiddenColumns ( ) const = 0;

		//! \fn createRow ( CyQueryResult::CyQueryResultValuesRow& newRow ) const
		//! @param [ in ] newRow a reference to a vector to witch new values are added
		//!
		//! This method add values to a vector of type CyQueryResult::CyQueryResultValuesRow

		virtual void createRow ( CyQueryResult::CyQueryResultValuesRow& newRow ) const = 0;

		//! \fn doDelete ( long long lObjId ) const
		//! @param [ in ] lObjId The ObjId of the record to delete
		//!
		//! This method delete a record in a table using the SQL given by the getDeleteSql ( ) method
		//! \return true when the SQL is executed sucessfully

		virtual bool doDelete ( long long lObjId ) const;

		//! \fn doInsert ( const CyQueryResult::CyQueryResultValuesRow& newRow ) const
		//! @param [ in ] newRow a vector with the values to insert
		//!
		//! This method insert a record in a table using the SQL given by the getInsertSql ( ) method
		//! \return true when the SQL is executed sucessfully

		bool doInsert ( const CyQueryResult::CyQueryResultValuesRow& newRow ) const;

		//! \fn doSelect ( CyQueryResult& objQueryResult ) const
		//! @param [ in ] objQueryResult a reference to an object CyQueryResult to witch the selected records will be added
		//!
		//! This method select records in the database using the SQL given by the getSelectSql ( ) method
		//! \return true when the SQL is executed sucessfully

		void doSelect ( CyQueryResult& objQueryResult ) const;

		//! \fn doUpdate ( const CyQueryResult::CyQueryResultValuesRow& newRow ) const
		//! @param [ in ] newRow a vector with the values to update
		//!
		//! This method update a record in a table using the SQL given by the getUpdateSql ( ) method
		//! \return true when the SQL is executed sucessfully

		virtual bool doUpdate ( const CyQueryResult::CyQueryResultValuesRow& newRow ) const;

	protected:

		//! \fn getDeleteSql ( long long lObjId ) const
		//! @param [ in ] lObjId the ObjId of the row to delete
		//!
		//! \return the SQL instruction to delete a row in a table. Used by the base class method doDelete ( )

		virtual wxString getDeleteSql ( long long lObjId ) const = 0;

		//! \fn getInsertSql ( const CyQueryResult::CyQueryResultValuesRow& newRow ) const
		//! @param [ in ] newRow a reference to a vector of type  CyQueryResult::CyQueryResultValuesRow with the values to insert
		//!
		//! \return the SQL instruction to insert a row in a table. Used by the base class method doInsert ( )

		virtual wxString getInsertSql ( const CyQueryResult::CyQueryResultValuesRow& newRow ) const = 0;

		//! \fn wxString getSelectSql ( ) const
		//!
		//! \return the SQL instruction to select rows in a table. Used by the base class method doSelect ( )

		virtual wxString getSelectSql ( ) const = 0;

		//! \fn wxString getUpdateSql ( const CyQueryResult::CyQueryResultValuesRow& newRow ) const
		//! @param [ in ] newRow a reference to a vector of type  CyQueryResult::CyQueryResultValuesRow with the values to update
		//!
		//! \return the SQL instruction to update a row in a table. Used by the base class method doInsert ( )

		virtual wxString getUpdateSql ( const CyQueryResult::CyQueryResultValuesRow& newRow ) const = 0;

		//! \fn getFieldSql ( const wxString& strField, const wxString& strAlias, const wchar_t strValueType, bool bLastField = false ) const
		//! this method help to do a Select sql statement, adding a format string in the Sql statement
		//! @param [ in ] strField the name of the column to add
		//! @param [ in ] strAlias an alias for the column 
		//! @param [ in ] strValueType the tyepe of the value to select ( must be CyFormatBoolean, CyFormatCurrency, CyFormatDate, CyFormatHidden, CyFormatInteger or CyFormatString )
		//! @param [ in ] bLastField when false ( the default value ) a comma is added at the end of the returned string
		//! \return a string to be used in a select SQL

		const wxString getFieldSql ( const wxString& strField, const wxString& strAlias, const wchar_t strValueType, bool bLastField = false ) const;

	private:

		//! \fn CySqlBuilder ( const CySqlBuilder& ) 
		//! copy constructor
		//! not implemented

		CySqlBuilder ( const CySqlBuilder& );

		//! \fn operator = ( const CySqlBuilder& ) 
		//! operator =
		//! \return a reference to a CySqlBuilder object
		//! not implemented

		CySqlBuilder& operator = ( const CySqlBuilder& );
};

/* ---------------------------------------------------------------------------- */
