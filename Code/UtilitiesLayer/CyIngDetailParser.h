/* ---------------------------------------------------------------------------- */
//! CyIngDetailParser.h
/* ---------------------------------------------------------------------------- */
//!
//! \file CyIngDetailParser.h
//! \brief header file for class CyIngDetailParser
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

#include "UtilitiesLayer/CyStdIncludes.h"

/* ---------------------------------------------------------------------------- */

//! \class CyIngDetailParser
//! \brief simple parser used to split a chain of substring separed with multiple spaces
//! into a vector of strings
//!
//! How to use this class:
//! - implement an instance of the class
//! - use the parse method to parse the string

class CyIngDetailParser : public std::vector < std::string >
{

	public:

		//! \fn CyIngDetailParser ( ) 
		//! constructor

		CyIngDetailParser ( );

		//! \fn ~CyIngDetailParser ( ) 
		//! destructor

		~CyIngDetailParser ( );

		//! \fn parse ( )
		//! this method parse the string
		//!
		//! @param [ in ] strStringToParse the string to parse

		void parse ( const std::string& strStringToParse );

	private:

		//! \fn CyIngDetailParser ( const CyIngDetailParser& ) 
		//! copy constructor
		//! not implemented

		CyIngDetailParser ( const CyIngDetailParser& );

		//! \fn operator = ( const CyIngDetailParser& ) 
		//! operator =
		//! \return a reference to a CyIngDetailParser object
		//! not implemented

		CyIngDetailParser& operator = ( const CyIngDetailParser& );

};