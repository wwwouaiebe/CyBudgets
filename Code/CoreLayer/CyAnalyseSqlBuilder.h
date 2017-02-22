/* ---------------------------------------------------------------------------- */
//! CyAnalyseSqlBuilder.h
/* ---------------------------------------------------------------------------- */
//!
//! \file CyAnalyseSqlBuilder.h
//! \brief header file for class CyAnalyseSqlBuilder
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

//! \class CyAnalyseSqlBuilder
//! \brief Helper class for SQL operations for the analyse
//!
//! \since version 1.0.3

class CyAnalyseSqlBuilder: public CySqlBuilder
{

	public:

		//! \fn CyAnalyseSqlBuilder ( long long lBudgetObjId, const wxDateTime& objStartDate, const wxDateTime& objEndDate ) 
		//! @param [ in ] lBudgetObjId the ObjId of the budget for witch the analyse must be computed
		//! @param [ in ] objStartDate the start date for witch the analyse must be computed
		//! @param [ in ] objEndDate the end date for witch the analyse must be computed
		//! constructor

		CyAnalyseSqlBuilder ( long long lBudgetObjId, const wxDateTime& objStartDate, const wxDateTime& objEndDate );

		//! \fn ~CyAnalyseSqlBuilder ( ) 
		//! destructor

		~CyAnalyseSqlBuilder ( );

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
		//! \var kDisplayOrder
		//! A computed field user to order the results
		//!
		//! \var kGroupObjId
		//! The ObjId field of the table AttributionsGroups
		//!
		//! \var kAttributionObjId
		//! The ObjId field of the table Attributions
		//!
		//! \var kHiddenBudgetDate
		//! The month for witch the results are computed by the SQL statement
		//!
		//! \var kGroupDescription
		//! The GroupDescription field of the table AttributionsGroups
		//! 
		//! \var kAttributionDescription
		//! The Description field of the table Attributions
		//!
		//! \var kBudgetDate
		//! The month for witch the results are computed by the SQL statement
		//!
		//! \var kAmount
		//! The amount computed by the SQL statement
		//!
		//! \var kAttributionDescriptionTotal
		//! The Description field of the table Attributions modified by the SQL statement
		//!
		//! \var kAttributionAmount
		//! The amount computed for the attribution by the SQL statement
		//!
		//! \var kGroupDescriptionTotal
		//! The Description field of the table AttributionsGroups modified by the SQL statement
		//!
		//! \var kGroupAmount
		//! The amount computed for the group by the SQL statement
		//!
		//! \var kTotal
		//! The amount computed for the complete analyse by the SQL statement

		enum ColumnPosition
		{
			kDisplayOrder = 0,
			kGroupObjId = 1,
			kAttributionObjId = 2,
			kHiddenBudgetDate = 3,
			kGroupDescription = 4,
			kAttributionDescription = 5,
			kBudgetDate = 6,
			kAmount = 7,
			kAttributionDescriptionTotal = 8,
			kAttributionAmount = 9,
			kGroupDescriptionTotal = 10,
			kGroupAmount = 11,
			kTotal = 12
		};

	protected:

		//! \fn getDeleteSql ( long long lObjId ) const
		//! @param [ in ] lObjId the ObjId of the row to delete
		//!
		//! \return the SQL instruction to delete a row in a table. Used by the base class method doDelete ( )
		//! Not implemented in this class

		virtual wxString getDeleteSql ( long long lObjId ) const;

		//! \fn getInsertSql ( const CyQueryResult::CyQueryResultValuesRow& newRow ) const
		//! @param [ in ] newRow a reference to a vector of type  CyQueryResult::CyQueryResultValuesRow with the values to insert
		//!
		//! \return the SQL instruction to insert a row in a table. Used by the base class method doInsert ( )
		//! Not implemented in this class

		virtual wxString getInsertSql ( const CyQueryResult::CyQueryResultValuesRow& newRow ) const;

		//! \fn wxString getSelectSql ( ) const
		//!
		//! \return the SQL instruction to select rows in a table. Used by the base class method doSelect ( )

		virtual wxString getSelectSql ( ) const;

		//! \fn wxString getUpdateSql ( const CyQueryResult::CyQueryResultValuesRow& newRow ) const
		//! @param [ in ] newRow a reference to a vector of type  CyQueryResult::CyQueryResultValuesRow with the values to update
		//!
		//! \return the SQL instruction to update a row in a table. Used by the base class method doInsert ( )
		//! Not implemented in this class

		virtual wxString getUpdateSql ( const CyQueryResult::CyQueryResultValuesRow& newRow ) const;

	private:

		//! \fn CyAnalyseSqlBuilder ( const CyAnalyseSqlBuilder& ) 
		//! copy constructor
		//! not implemented

		CyAnalyseSqlBuilder ( const CyAnalyseSqlBuilder& );

		//! \fn operator = ( const CyAnalyseSqlBuilder& ) 
		//! operator =
		//! \return a reference to a CyAnalyseSqlBuilder object
		//! not implemented

		CyAnalyseSqlBuilder& operator = ( const CyAnalyseSqlBuilder& );

		//! \var m_lBudgetObjId
		//! The BudgetId of the budget for witch the analyse is computed

		long long m_lBudgetObjId;

		//! \var m_objStartDate
		//! The start date of the analyse
		
		const wxDateTime m_objStartDate;

		//! \var m_objEndDate
		//! The end date of the analyse
		
		const wxDateTime m_objEndDate;

};

/* ---------------------------------------------------------------------------- */
