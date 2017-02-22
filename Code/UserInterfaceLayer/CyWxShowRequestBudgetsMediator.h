/* ---------------------------------------------------------------------------- */
//! CyWxShowRequestBudgetsMediator.h
/* ---------------------------------------------------------------------------- */
//!
//! \file CyWxShowRequestBudgetsMediator.h
//! \brief header file for class CyWxShowRequestBudgetsMediator
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

class CyWxShowRequestDialog;

/* ---------------------------------------------------------------------------- */

//! \class CyWxShowRequestBudgetsMediator
//! \brief mediator base class to personnalize the CyWxShowRequestDialog
//!
//! This class is based on the design pattern Mediator
//! How to use this class:
//! - create an instance of the class CyWxShowRequestBudgetsMediator or an instance of a class derived from CyWxShowRequestBudgetsMediator
//! - create an instance of the class CyWxShowRequestDialog
//! - launch the CyWxShowRequestDialog::Show ( ) method
//! - no need to delete the mediator. It's done in the ~CyWxShowRequestDialog

class CyWxShowRequestBudgetsMediator: public CyWxShowRequestMediator
{

	friend class CyWxShowRequestDialog;

	public:

		//! \fn CyWxShowRequestBudgetsMediator ( CySqlBuilder* pSqlBuilder )
		//! @param [ in ] pSqlBuilder a SQL builder used to do the SQL operations
		//!
		//! constructor

		explicit CyWxShowRequestBudgetsMediator ( CySqlBuilder* pSqlBuilder );

		//! \fn ~CyWxShowRequestBudgetsMediator ( ) 
		//! destructor

		virtual ~CyWxShowRequestBudgetsMediator ( );

	protected:

		//! \fn setDialog ( CyWxShowRequestDialog* pWxShowRequestDialog )
		//! @param [ in ] pWxShowRequestDialog the associated window
		//!
		//! this method save a pointer to the associated dialog in the m_pWxShowRequestDialog member

		void setDialog ( CyWxShowRequestDialog* pWxShowRequestDialog );

		//! \fn addPopupItems ( wxMenu& objMenu )
		//! @param [ in ] objMenu the popup menu of the parent Window
		//!
		//! this method is called by the CyWxShowRequestDialog::onRightClickGrid ( ) and
		//! is used to add the items in the popup menu.
		//!
		//! \return true when items are added to the popup menu, false otherwise.

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

		//! \fn CyWxShowRequestBudgetsMediator ( const CyWxShowRequestBudgetsMediator& )
		//! copy constructor
		//! not implemented

		CyWxShowRequestBudgetsMediator ( const CyWxShowRequestBudgetsMediator& );

		//! \fn operator = ( const CyWxShowRequestBudgetsMediator& ) 
		//! operator =
		//! \return a reference to a CyWxShowRequestBudgetsMediator object
		//! not implemented

		CyWxShowRequestBudgetsMediator& operator = ( const CyWxShowRequestBudgetsMediator& );

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

