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

#include "CoreLayer/CySqlBuilder.h"

/* ---------------------------------------------------------------------------- */

class CyWxShowRequestDialog;

/* ---------------------------------------------------------------------------- */

//! \class CyWxShowRequestMediator
//! \brief mediator base class to personnalize the CyWxShowRequestDialog
//!
//! This class is based on the design pattern Mediator
//! How to use this class:
//! - create an instance of the class CyWxShowRequestMediator or an instance of a class derived from CyWxShowRequestMediator
//! - create an instance of the class CyWxShowRequestDialog
//! - launch the CyWxShowRequestDialog::Show ( ) method
//! - no need to delete the mediator. It's done in the ~CyWxShowRequestDialog

class CyWxShowRequestMediator
{

	friend class CyWxShowRequestDialog;

	public:

		//! \fn CyWxShowRequestMediator ( CySqlBuilder* pSqlBuilder )
		//!
		//! constructor
		//! @param [ in ] pSqlBuilder the SQL builder to use with this class

		explicit CyWxShowRequestMediator ( CySqlBuilder* pSqlBuilder );

		//! \fn ~CyWxShowRequestMediator ( ) 
		//! destructor

		virtual ~CyWxShowRequestMediator ( );

		//! \fn getDialogTitle ( ) const
		//! get method
		//! \return the title to display in the associated window

		wxString getDialogTitle ( ) const;

		//! \fn getHiddenColumns ( ) const
		//! get method
		//! \return the number of columns to hide in the associated window

		int getHiddenColumns ( ) const;

		//! \fn select ( CyQueryResult& objQueryResult ) const
		//! this method select in the database the data to display in the associated window
		//! @param [ in ] objQueryResult an objet CyQueryResult in witch the data are added

		void select ( CyQueryResult& objQueryResult ) const;

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
		//! By default, this method do nothing. To be implemented in the derived classes.
		//!
		//! \return true when items are added to the popup menu, false otherwise.

		virtual bool addPopupItems ( wxMenu& objMenu );

		//! \fn onPopupRightClickGrid ( wxCommandEvent& event )
		//! @param [ in ] event the event creted by the framwork
		//!
		//! this method is called by the CyWxShowRequestDialog::onPopupRightClickGrid ( ) and
		//! manage the events send by the framework when the user select an item in the popup menu.
		//! By default, this method do nothing. To be implemented in the derived classes.
		//!

		virtual void onPopupRightClickGrid ( wxCommandEvent& event );

		//! \fn onDoubleLeftClickGrid ( )
		//!
		//! this method is called by the CyWxShowRequestDialog::onDoubleLeftClickGrid ( ) and
		//! manage the events send by the framework when the user double click on a row in the grid.
		//! By default, this method do nothing. To be implemented in the derived classes.
		//!

		virtual void onDoubleLeftClickGrid ( );

		//! \fn onDoubleLeftClickLabel ( )
		//! this method is called by the CyWxShowRequestDialog::onDoubleLeftClickLabel ( ) and
		//! manage the events send by the framework when the user double click on a label of the grid.
		//! By default, this method do nothing. To be implemented in the derived classes.

		virtual void onDoubleLeftClickLabel ( );

		//! \var m_pWxShowRequestDialog
		//! a pointer to the associated CyWxShowRequestDialog

		CyWxShowRequestDialog* m_pWxShowRequestDialog;

		//! \var m_pSqlBuilder
		//! the SqlBuilder object responsible of the selection and edition of the data

		CySqlBuilder* m_pSqlBuilder;

	private:

		//! \fn CyWxShowRequestMediator ( const CyWxShowRequestMediator& )
		//! copy constructor
		//! not implemented

		CyWxShowRequestMediator ( const CyWxShowRequestMediator& );

		//! \fn operator = ( const CyWxShowRequestMediator& ) 
		//! operator =
		//! \return a reference to a CyWxShowRequestMediator object
		//! not implemented

		CyWxShowRequestMediator& operator = ( const CyWxShowRequestMediator& );

};

/* ---------------------------------------------------------------------------- */

