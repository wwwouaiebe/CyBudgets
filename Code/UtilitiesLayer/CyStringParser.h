/* ---------------------------------------------------------------------------- */
//! CyStringParser.h
/* ---------------------------------------------------------------------------- */
//!
//! \file CyStringParser.h
//! \brief header file for class CyStringParser
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

//! \class CyStringParser
//! \brief Parser for string variables of type std::string
//!
//! How to use this class:
//! - implement an instance of the class
//! - use the parse method to parse the string
//! - use the std::vector < > methods to work with the results of the parse method

class CyStringParser: public std::vector < std::string >
{

	public:

		//! \fn CyStringParser ( ) 
		//! constructor

		CyStringParser ( );

		//! \fn ~CyStringParser ( ) 
		//! destructor

		virtual ~CyStringParser ( void );

		//! \fn parse ( const std::string& strDelimiter, const std::string& strStringToParse ) 
		//! @param [ in ] strDelimiter the string used as delimiter (can be > 1)
		//! @param [ in ] strStringToParse the string to parse
		//!
		//! It's the programmmer responsability to empty or not the vector before using this method.

		void parse ( const std::string& strDelimiter, const std::string& strStringToParse );

	private:

		//! \fn CyStringParser ( const CyStringParser& ) 
		//! copy constructor
		//! not implemented

		CyStringParser ( const CyStringParser& );

		//! \fn operator = ( const CyStringParser& ) 
		//! operator =
		//! \return a reference to a CyStringParser object
		//! not implemented

		CyStringParser& operator = ( const CyStringParser& );
};

/* ---------------------------------------------------------------------------- */
