﻿/* ---------------------------------------------------------------------------- */
//! CyBudgetsSqlBuilder.h
/* ---------------------------------------------------------------------------- */
//!
//! \file CyBudgetsSqlBuilder.h
//! \brief header file for class CyBudgetsSqlBuilder
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

//! \class CyBudgetsSqlBuilder
//! \brief Helper class for SQL operations for the budgets
//!
//! \since version 1.0.3

class CyBudgetsSqlBuilder: public CySqlBuilder
{

	public:

		//! \fn CyBudgetsSqlBuilder ( ) 
		//! constructor

		CyBudgetsSqlBuilder ( );

		//! \fn ~CyBudgetsSqlBuilder ( ) 
		//! destructor

		~CyBudgetsSqlBuilder ( );

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
		//! \var kBudgetObjId
		//! The ObjId field of the table Budgets
		//!
		//! \var kBudgetDescription
		//! The Description field of the table Budgets

		enum ColumnPosition
		{
			kBudgetObjId = 0,
			kBudgetDescription = 1
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

		//! \fn CyBudgetsSqlBuilder ( const CyBudgetsSqlBuilder& ) 
		//! copy constructor
		//! not implemented

		CyBudgetsSqlBuilder ( const CyBudgetsSqlBuilder& );

		//! \fn operator = ( const CyBudgetsSqlBuilder& ) 
		//! operator =
		//! \return a reference to a CyBudgetsSqlBuilder object
		//! not implemented

		CyBudgetsSqlBuilder& operator = ( const CyBudgetsSqlBuilder& );

};

/* ---------------------------------------------------------------------------- */
