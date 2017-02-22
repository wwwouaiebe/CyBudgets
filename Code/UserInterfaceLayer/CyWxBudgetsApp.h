/* ---------------------------------------------------------------------------- */
//! CyWxBudgetsApp.h
/* ---------------------------------------------------------------------------- */
//!
//! \file CyWxBudgetsApp.h
//! \brief header file for class CyWxBudgetsApp
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

#include "UtilitiesLayer/CyWxIncludes.h"

/* ---------------------------------------------------------------------------- */

class CyWxBudgetsFrame;

/* ---------------------------------------------------------------------------- */

//! \class CyWxBudgetsApp
//! \brief This class is the entry point of the application. See wxApp documentation for more...
//!

class CyWxBudgetsApp: public wxApp
{

	public:

		//! \fn CyWxBudgetsApp ( ) 
		//! constructor

		CyWxBudgetsApp ( );

		//! \fn ~CyWxBudgetsApp ( ) 
		//! destructor

		virtual ~CyWxBudgetsApp ( );

		// \fn OnInit ( )
		//! this method do the initialization of the application. See also wxApp::OnInit ( ) documentation.
		//!
		//! \return always true;

		virtual bool OnInit();

		// \fn getBudgetsFrame ( )
		//! get method
		//!
		//! \return a pointer to the main frame of the application

		CyWxBudgetsFrame* getBudgetsFrame ( );

	private:

		//! \fn CyWxBudgetsApp ( const CyWxBudgetsApp& ) 
		//! copy constructor
		//! not implemented

		CyWxBudgetsApp ( const CyWxBudgetsApp& );

		//! \fn operator = ( const CyWxBudgetsApp& ) 
		//! operator =
		//! \return a reference to a CyWxBudgetsApp object
		//! not implemented

		const CyWxBudgetsApp& operator = ( const CyWxBudgetsApp& );

		//! \var m_pWxBudgetsFrame
		//! a pointer to the CyWxBudgetsFrame object

		CyWxBudgetsFrame* m_pWxBudgetsFrame;

};

/* ---------------------------------------------------------------------------- */

DECLARE_APP(CyWxBudgetsApp)

/* ---------------------------------------------------------------------------- */

