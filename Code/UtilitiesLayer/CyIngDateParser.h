/* ---------------------------------------------------------------------------- */
//! CyIngDateParser.h
/* ---------------------------------------------------------------------------- */
//!
//! \file CyIngDateParser.h
//! \brief header file for class CyIngDateParser
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

//! \class CyIngDateParser
//! \brief simple parser used to transform a date in the format dd/mm/yyyy to an ISO date
//!
//! How to use this class:
//! - implement an instance of the class
//! - use the parseDate method to parse the date

class CyIngDateParser
{

	public:

		//! \fn CyIngDateParser ( ) 
		//! constructor

		CyIngDateParser ( );

		//! \fn ~CyIngDateParser ( ) 
		//! destructor

		virtual ~CyIngDateParser ( );

		//! \fn parseDate ( const std::string strDate ) 
		//! @param [ in ] strDate the date to transform
		//!
		//! \return a std::string representing the data in the ISO format
		//!
		//! This method transform a string representing a date in the format dd/mm/yyyy to a string representing 
		//! a date in the ISO format.
		//! The entry date is supposed to be a correct date!

		std::string parseDate ( const std::string strDate );

	private:

		//! \fn CyIngDateParser ( const CyIngDateParser& ) 
		//! copy constructor
		//! not implemented

		CyIngDateParser ( const CyIngDateParser& );

		//! \fn operator = ( const CyIngDateParser& ) 
		//! operator =
		//! \return a reference to a CyIngDateParser object
		//! not implemented

		CyIngDateParser& operator = ( const CyIngDateParser );

};

/* ---------------------------------------------------------------------------- */

