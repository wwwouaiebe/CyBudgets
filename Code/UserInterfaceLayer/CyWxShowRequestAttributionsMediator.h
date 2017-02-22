/* ---------------------------------------------------------------------------- */
//! CyWxShowRequestAttributionsMediator.h
/* ---------------------------------------------------------------------------- */
//!
//! \file CyWxShowRequestAttributionsMediator.h
//! \brief header file for class CyWxShowRequestAttributionsMediator
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

//! \class CyWxShowRequestAttributionsMediator
//! \brief mediator class for the CyWxShowRequestDialog when this is used to show the attributions
//!

class CyWxShowRequestAttributionsMediator: public CyWxShowRequestMediator
{

	friend class CyWxShowRequestDialog;

	public:
	
		//! \fn CyWxShowRequestAttributionsMediator (  CySqlBuilder* pSqlBuilder )
		//! @param [ in ] pSqlBuilder a SQL builder used to do the SQL operations
		//!
		//! constructor

		explicit CyWxShowRequestAttributionsMediator ( CySqlBuilder* pSqlBuilder );

		//! \fn ~CyWxShowRequestAttributionsMediator ( ) 
		//! destructor

		virtual ~CyWxShowRequestAttributionsMediator ( );

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
		//! manage the events send by the framework when the user double click on a row in the grid.

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

		//! \fn CyWxShowRequestAttributionsMediator ( const CyWxShowRequestAttributionsMediator& )
		//! copy constructor
		//! not implemented

		CyWxShowRequestAttributionsMediator ( const CyWxShowRequestAttributionsMediator& );

		//! \fn operator = ( const CyWxShowRequestAttributionsMediator& ) 
		//! operator =
		//! \return a reference to a CyWxShowRequestAttributionsMediator object
		//! not implemented

		CyWxShowRequestAttributionsMediator& operator = ( const CyWxShowRequestAttributionsMediator& );

		//! \fn onAdd ( )
		//!
		//! this method is called by the onPopupRightClickGrid ( ) when
		//! the user select the Add item in the popup menu or by the and onDoubleLeftClickLabel ( )

		void onAdd ( );

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
