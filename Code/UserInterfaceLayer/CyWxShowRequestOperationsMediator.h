/* ---------------------------------------------------------------------------- */
//! CyWxShowRequestOperationsMediator.h
/* ---------------------------------------------------------------------------- */
//!
//! \file CyWxShowRequestOperationsMediator.h
//! \brief header file for class CyWxShowRequestOperationsMediator
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

#include "UserInterfaceLayer/CyWxShowRequestMediator.h"

/* ---------------------------------------------------------------------------- */

//! \class CyWxShowRequestOperationsMediator
//! \brief mediator class for the CyWxShowRequestDialog when this is used to show the operations
//!

class CyWxShowRequestOperationsMediator: public CyWxShowRequestMediator
{

	friend class CyWxShowRequestDialog;

	public:
	
		//! \fn CyWxShowRequestOperationsMediator ( CySqlBuilder* pSqlBuilder )
		//! @param [ in ] pSqlBuilder a SQL builder used to do the SQL operations
		//!
		//! constructor

		explicit CyWxShowRequestOperationsMediator ( CySqlBuilder* pSqlBuilder );

		//! \fn ~CyWxShowRequestOperationsMediator ( ) 
		//! destructor

		virtual ~CyWxShowRequestOperationsMediator ( );

	protected:

		//! \fn addPopupItems ( wxMenu& objMenu )
		//! @param [ in ] objMenu the popup menu of the parent Window
		//!
		//! this method is called by the CyWxShowRequestDialog::onRightClickGrid ( ) and
		//! is used to add the items in the popup menu.
		//! \return true

		virtual bool addPopupItems ( wxMenu& objMenu );

		//! \fn onPopupRightClickGrid ( wxCommandEvent& event )
		//! @param [ in ] event the event creted by the framwork
		//!
		//! this method is called by the CyWxShowRequestDialog::onPopupRightClickGrid ( ) and
		//! manage the events send by the framework when the user select an item in the popup menu.

		virtual void onPopupRightClickGrid ( wxCommandEvent& event );

		//! \fn onDoubleLeftClickGrid ( )
		//!
		//! this method is called by the CyWxShowRequestDialog::onDoubleLeftClickGrid ( ) and
		//! manage the events send by the framework when the user do a double-click on a line of the grid.

		virtual void onDoubleLeftClickGrid ( );

		//! \fn onDoubleLeftClickLabel ( )
		//! this method is called by the CyWxShowRequestDialog::onDoubleLeftClickLabel ( ) and
		//! manage the events send by the framework when the user double click on a label of the grid.

		virtual void onDoubleLeftClickLabel ( );
	private:

		//! \enum wxId
		//! values for the items in the popup menu
		//!
		//! \var kEdit
		//! id for the Edit menu item
		//!
		//! \var kAdd
		//! id for the Add menu item
		//!
		//! \var kDelete
		//! id for the Delete menu item
		//!

		enum wxId
		{
			kEdit,
			kAdd,
			kDelete
		};

		//! \fn CyWxShowRequestOperationsMediator ( const CyWxShowRequestOperationsMediator& )
		//! copy constructor
		//! not implemented

		CyWxShowRequestOperationsMediator ( const CyWxShowRequestOperationsMediator& );

		//! \fn operator = ( const CyWxShowRequestOperationsMediator& ) 
		//! operator =
		//! \return a reference to a CyWxShowRequestOperationsMediator object
		//! not implemented

		CyWxShowRequestOperationsMediator& operator = ( const CyWxShowRequestOperationsMediator& );

		//! \fn onAdd ( wxString strAccountNumber )
		//! @param [ in ] strAccountNumber the account number on witch the operation will be added
		//!
		//! this method is called by the onPopupRightClickGrid ( ) when
		//! the user select the Add item in the popup menu or by the and onDoubleLeftClickLabel ( )

		void onAdd  ( wxString strAccountNumber );

		//! \fn onDelete ( )
		//!
		//! this method is called by the onPopupRightClickGrid ( ) when
		//! the user select the Delete item in the popup menu.

		void onDelete ( );

		//! \fn onEdit ( )
		//!
		//! this method is called by the onPopupRightClickGrid ( ) when
		//! the user select the Edit item in the popup menu.

		void onEdit ( );

};

/* ---------------------------------------------------------------------------- */

