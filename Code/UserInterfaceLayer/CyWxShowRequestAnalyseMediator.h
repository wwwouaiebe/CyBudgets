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

class CyWxShowRequestDialog;

/* ---------------------------------------------------------------------------- */

//! \class CyWxShowRequestAnalyseMediator
//! \brief mediator class for the CyWxShowRequestDialog when this is used to show the analyse
//!

class CyWxShowRequestAnalyseMediator : public CyWxShowRequestMediator
{

	friend class CyWxShowRequestDialog;

	public:

		//! \fn CyWxShowRequestAnalyseMediator ( CySqlBuilder* pSqlBuilder )
		//! @param [ in ] pSqlBuilder a SQL builder used to do the SQL operations
		//!
		//! constructor

		explicit CyWxShowRequestAnalyseMediator ( CySqlBuilder* pSqlBuilder );

		//! \fn ~CyWxShowRequestAnalyseMediator ( ) 
		//! destructor

		virtual ~CyWxShowRequestAnalyseMediator ( );

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

	private:

		//! \enum wxId
		//! values for the items in the popup menu
		//!
		//! \var kViewOperations
		//! id for the ViewOperations menu item
		//!

		enum wxId
		{
			kViewOperations
		};

		//! \fn CyWxShowRequestAnalyseMediator ( const CyWxShowRequestAnalyseMediator& )
		//! copy constructor
		//! not implemented

		CyWxShowRequestAnalyseMediator ( const CyWxShowRequestAnalyseMediator& );

		//! \fn operator = ( const CyWxShowRequestAnalyseMediator& ) 
		//! operator =
		//! \return a reference to a CyWxShowRequestAnalyseMediator object
		//! not implemented

		CyWxShowRequestAnalyseMediator& operator = ( const CyWxShowRequestAnalyseMediator& );

		//! \fn onViewOperations ( )
		//!
		//! this method is called by the onPopupRightClickGrid ( ) when
		//! the user select the Add item in the popup menu or by the and onDoubleLeftClickLabel ( )

		void onViewOperations ( );

};

/* ---------------------------------------------------------------------------- */

