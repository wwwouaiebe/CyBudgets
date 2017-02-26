/* ---------------------------------------------------------------------------- */
//! CyOperationsSqlBuilder.h
/* ---------------------------------------------------------------------------- */
//!
//! \file CyOperationsSqlBuilder.h
//! \brief header file for class CyOperationsSqlBuilder
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

//! \class CyOperationsSqlBuilder
//! \brief Helper class for SQL operations for the operations
//!
//! \since version 1.0.3

class CyOperationsSqlBuilder: public CySqlBuilder
{

	public:

		//! \fn CyOperationsSqlBuilder ( ) 
		//! constructor
		//!
		//! This constructor is used from the CyWxBudgetFrame window to select the Operations
		//! without attributions or incomplete attributions

		CyOperationsSqlBuilder ( );

		//! \fn CyOperationsSqlBuilder ( const wxString& strAccount, long long lAccountObjId, const wxDateTime& objStartDate, const wxDateTime& objEndDate ) 
		//! @param [ in ] strAccount the account number for witch the opearation are searched
		//! @param [ in ] lAccountObjId for witch the opearation are searched
		//! @param [ in ] objStartDate the starting date of the search
		//! @param [ in ] objEndDate the ending date of the search
		//! constructor
		//!
		//! This constructor is used from the CyWxBudgetFrame window to select the Operations
		//! with an account number and start and end dates

		CyOperationsSqlBuilder ( 
			const wxString& strAccount, 
			long long lAccountObjId, 
			const wxDateTime& objStartDate, 
			const wxDateTime& objEndDate );

		//! \fn CyOperationsSqlBuilder ( const CyQueryResult::CyQueryResultValuesRow& currentRow, const wxDateTime& objStartDate, const wxDateTime& objEndDate ) 
		//! @param [ in ] currentRow a CyQueryResult::CyQueryResultValuesRow from an CyQueryResult selected by an CyAnalyseSqlBuilder object
		//! @param [ in ] objStartDate the starting date of the search
		//! @param [ in ] objEndDate the ending date of the search
		//! constructor
		//!
		//! This constructor is used from the CyWxShowRequestAnalyseMediator object to select the Operations
		//! linked to a row in an analyse result

		CyOperationsSqlBuilder ( 
			const CyQueryResult::CyQueryResultValuesRow& currentRow, 
			const wxDateTime& objStartDate, 
			const wxDateTime& objEndDate  );

		//! \fn ~CyOperationsSqlBuilder ( ) 
		//! destructor

		~CyOperationsSqlBuilder ( );

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

		//! \enum ColumnPosition
		//! values for fields position in the query results
		//!
		//! \var kOperationObjId
		//! The ObjId field of the table Operations
		//!
		//! \var kOperationDescription
		//! The Description field of the table Operations
		//!
		//! \var kOperationAccountCanBeImported
		//! The CanBeImported field of the table Accounts
		//!
		//! \var kOperationAccountNumber
		//! The AccountNumber field of the table Accounts
		//!
		//! \var kOperationNumber
		//! The ObjId field of the table Operations
		//!
		//! \var kOperationDate
		//! The OperationDate field of the table Operations
		//!
		//! \var kOperationValueDate
		//! The ValueDate field of the table Operations
		//!
		//! \var kOperationAttributionDate
		//! The AttributionDate field of the table Operations
		//!
		//! \var kOperationAmount
		//! The Amount  field of the table Operations
		//!
		//! \var kOperationHaveNote
		//! A numeric value ( 1 or 0 ) indicating when the field Description of the table
		//! Operations is filled or not
		//!
		//! \var kOperationHaveDetails
		//! A numeric value ( 1 or 0 ) indicating when some records in the table OperationsDetails
		//! are linked or not with the current record of the table Operations
		//!
		//! \var kOperationHaveAttribution
		//! A numeric value ( 1 or 0 ) indicating when some records in the table OperationsAttributions
		//! are linkedor not  with the current record of the table Operations

		enum ColumnPosition
		{
			kOperationObjId = 0,
			kOperationDescription = 1,
			kOperationAccountCanBeImported = 2,
			kOperationAccountNumber = 3,
			kOperationNumber = 4,
			kOperationDate = 5,
			kOperationValueDate = 6,
			kOperationAttributionDate = 7,
			kOperationAmount = 8,
			kOperationHaveNote = 9,
			kOperationHaveDetails = 10,
			kOperationHaveAttribution = 11
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

		//! \fn CyOperationsSqlBuilder ( const CyOperationsSqlBuilder& ) 
		//! copy constructor
		//! not implemented

		CyOperationsSqlBuilder ( const CyOperationsSqlBuilder& );

		//! \fn operator = ( const CyOperationsSqlBuilder& ) 
		//! operator =
		//! \return a reference to a CyOperationsSqlBuilder object
		//! not implemented

		CyOperationsSqlBuilder& operator = ( const CyOperationsSqlBuilder& );

		//! \var m_strDialogTitle
		//! this variable is used to build the dialog title. See constructor and getDialogTitle ( ) implementation

		wxString m_strDialogTitle;

		//! \var m_strWhereClause
		//! this variable is used to build a where clause for the getSelectSql () method. See also constructor implementation

		wxString m_strWhereClause;

		//! \var m_strTables
		//! this variable is used to store the tables name used by the getSelectSql () method. See also constructor implementation

		wxString m_strTables;
};

/* ---------------------------------------------------------------------------- */
