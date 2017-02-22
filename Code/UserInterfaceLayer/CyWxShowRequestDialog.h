/* ---------------------------------------------------------------------------- */
//! CyWxShowRequestDialog.h
/* ---------------------------------------------------------------------------- */
//!
//! \file CyWxShowRequestDialog.h
//! \brief header file for class CyWxShowRequestDialog
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

#include "DataLayer/CyQueryResult.h"
#include "UtilitiesLayer/CyWxIncludes.h"

/* ---------------------------------------------------------------------------- */

class CyWxShowRequestMediator;

/* ---------------------------------------------------------------------------- */

//! \class CyWxShowRequestDialog
//! \brief dialog box for displaying a query result
//!
//! This class is based on the design pattern Mediator
//! How to use this class:
//! - create an instance of the class CyWxShowRequestMediator or an instance of a class derived from CyWxShowRequestMediator
//! - create an instance of the class CyWxShowRequestDialog
//! - launch the Show ( ) method
//! - no need to delete the mediator. It's done in the ~CyWxShowRequestDialog

class CyWxShowRequestDialog: public wxDialog
{

	public:


		//! \fn CyWxShowRequestDialog ( wxWindow *pParent, CyWxShowRequestMediator* pWxShowRequestMediator ) 
		//! @param [ in ] pParent the parent window
		//! @param [ in ] pWxShowRequestMediator the mediator to be used
		//!
		//! constructor

		CyWxShowRequestDialog ( wxWindow *pParent, CyWxShowRequestMediator* pWxShowRequestMediator );

		//! \fn ~CyWxShowRequestDialog ( ) 
		//! destructor

		virtual ~CyWxShowRequestDialog ( );

		//! \fn getCurrentRow ( )
		//! get method
		//!
		//! \return the active row in the grid

		CyQueryResult::CyQueryResultValuesRow& getCurrentRow ( );

		//! \fn getNumberRows ( )
		//! get method
		//!
		//! \return the number of row in the m_objQueryResult variable

		size_t getNumberRows () const;

		//! \fn refreshCurrentRow ( )
		//! This method redraw the active row in the grid

		void refreshCurrentRow ( );

		//! \fn refreshGrid ( )
		//! this method relauch the SQL query and redraw the entire grid

		void refreshGrid ( );

	private:

		//! \fn CyWxShowRequestDialog ( const CyWxShowRequestDialog& ) 
		//! copy constructor
		//! not implemented

		CyWxShowRequestDialog ( const CyWxShowRequestDialog& );

		//! \fn operator = ( const CyWxShowRequestDialog& ) 
		//! operator =
		//! \return a reference to a CyWxShowRequestDialog object
		//! not implemented

		CyWxShowRequestDialog& operator = ( const CyWxShowRequestDialog& );

		//! \fn OnClose ( wxCloseEvent& )
		//! event handler for the "close dialog" user action

		virtual void OnClose( wxCloseEvent& );

		//! \fn onRightClickGrid ( )
		//! event handler for the "single right click on grid" user action
		//! @param [ in ] event the event send by the wxWidget framework

		void onRightClickGrid ( wxGridEvent& event );

		//! \fn onPopupRightClickGrid ( )
		//! event handler for the "selection in the popup menu grid displayed with a right click on the grid" user action
		//! @param [ in ] event the event send by the wxWidget framework

		void onPopupRightClickGrid ( wxCommandEvent& event );

		//! \fn onDoubleLeftClickGrid ( )
		//! event handler for the "double left click on grid" user action
		//! @param [ in ] event the event send by the wxWidget framework

		void onDoubleLeftClickGrid ( wxGridEvent& event );

		//! \fn onDoubleLeftClickLabel ( )
		//! event handler for the "double left click in the label of the grid" user action
		//! @param [ in ] event the event send by the wxWidget framework

		void onDoubleLeftClickLabel ( wxGridEvent& event );

		//! \fn displayGridRow ( int iRow, const CyQueryResult::CyQueryResultValuesRow& objQueryResultValuesRow )
		//! this method displays the values contained in the objQueryResultValuesRow in the frid at the position given by iRow
		//! @param [ in ] iRow the row to witch the values must be displayed
		//! @param [ in ] objQueryResultValuesRow the values to display

		void displayGridRow ( int iRow, const CyQueryResult::CyQueryResultValuesRow& objQueryResultValuesRow );

		//! \var m_pGrid
		//! the grid used to show the results
		//!
		
		wxGrid* m_pGrid;

		//! \var m_pWxShowRequestMediator
		//! a pointer to the associated mediator
		//!
		
		CyWxShowRequestMediator* m_pWxShowRequestMediator;

		//! \var m_objQueryResult
		//! the CyQueryResult object associated to the SQL query
		//!
		
		CyQueryResult m_objQueryResult;

		//! \var m_iCurrentRow
		//! the active row in the grid
		//!
		
		int m_iCurrentRow;
};

/* ---------------------------------------------------------------------------- */

