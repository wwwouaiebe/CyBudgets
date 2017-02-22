/* ---------------------------------------------------------------------------- */
//! CySqliteFunctions.h
/* ---------------------------------------------------------------------------- */
//!
//! \file CySqliteFunctions.h
//! \brief header file for class CySqliteFunctions
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

#ifdef CY_COMPILER_VC10
#pragma warning(push)
#pragma warning( disable : 4820 )
#endif

#include "sqlite3.h"

#ifdef CY_COMPILER_VC10
#pragma warning(pop)
#endif

/* ---------------------------------------------------------------------------- */

//! \class CySqliteFunctions
//! \brief this class is used to add new SQL functions to Sqlite 
//! It's not possible to instantiate this class. only static methods can be used by the sqlite3_create_function method
//!
//! \since version 1.0.3

class CySqliteFunctions
{

	public:

		//! \fn DoubleToCurrency ( sqlite3_context* context, int iArgumentCount, sqlite3_value** argumentsArray )
		//! @param [ in ] context see the Sqlite documentation
		//! @param [ in ] iArgumentCount see the Sqlite documentation
		//! @param [ in ] argumentsArray see the Sqlite documentation
		//! This method extend the SQL functions of SQLite db
		//! This new SQL function transform a value of type SQLITE_FLOAT to a value of type SQLITE_INTEGER with the foolowing transformations:
		//! - the value is multiplied by 100
		//! - ...
		// ! in other words: a value in EUR is transformed to a value in CENTS

		static void DoubleToCurrency ( sqlite3_context* context, int iArgumentCount, sqlite3_value** argumentsArray );

	private:

		//! \fn CySqliteFunctions ( ) 
		//! constructor
		//! not implemented

		CySqliteFunctions ( );

		//! \fn ~CySqliteFunctions ( ) 
		//! destructor
		//! not implemented

		 ~CySqliteFunctions ( );

		//! \fn CySqliteFunctions ( const CySqliteFunctions& ) 
		//! copy constructor
		//! not implemented

		 CySqliteFunctions ( const CySqliteFunctions& );

		//! \fn operator = ( const CySqliteFunctions& ) 
		//! operator =
		//! \return a reference to a CySqliteFunctions object
		//! not implemented

		 CySqliteFunctions& operator = ( const CySqliteFunctions& );
};