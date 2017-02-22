/* ---------------------------------------------------------------------------- */
//! CyIngDateParser.cpp
/* ---------------------------------------------------------------------------- */
//!
//! \file CyIngDateParser.cpp
//! \brief definition file for class CyIngDateParser
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

#include "UtilitiesLayer/CyIngDateParser.h"
#include "UtilitiesLayer/CyStringParser.h"

/* ---------------------------------------------------------------------------- */

CyIngDateParser::CyIngDateParser ( )
{
}

/* ---------------------------------------------------------------------------- */

CyIngDateParser::~CyIngDateParser ( )
{
}

/* ---------------------------------------------------------------------------- */

std::string CyIngDateParser::parseDate ( const std::string strDate )
{
	// the string is parsed with a CyStringParser object and a / as delimiter
	CyStringParser objStringParser;
	objStringParser.parse ( "/", strDate );

	if ( 3 == objStringParser.size ( ) )
	{
		// 3 substrings are found
		if ( 1 == objStringParser.at ( 0 ).size ( ) )
		{
			// days < 10 are completed with a 0
			objStringParser.at ( 0 ) = "0" + objStringParser.at ( 0 );
		}
		if ( 1 == objStringParser.at ( 1 ).size ( ) )
		{
			// month < 10 are completed with a 0
			objStringParser.at ( 1 ) = "0" + objStringParser.at ( 1 );
		}

		// returning the date
		return objStringParser.at ( 2 ).substr ( 0, 4 ) + "-" + objStringParser.at ( 1 ) + "-" + objStringParser.at ( 0 );
	}
	else
	{
		// substrings not found...
		return "";
	}
}

/* ---------------------------------------------------------------------------- */

