/* ---------------------------------------------------------------------------- */
//! CyStringParser.cpp
/* ---------------------------------------------------------------------------- */
//!
//! \file CyStringParser.cpp
//! \brief definition file for class CyStringParser
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

#include "UtilitiesLayer/CyStringParser.h"

/* ---------------------------------------------------------------------------- */

CyStringParser::CyStringParser ( )
{
}

/* ---------------------------------------------------------------------------- */

CyStringParser::~CyStringParser ( void )
{
}

/* ---------------------------------------------------------------------------- */

void CyStringParser::parse ( const std::string& strDelimiter, const std::string& strStringToParse )
{
	std::string strTmp;
	size_t iDelimiterLength = strDelimiter.length();
	size_t iCounter = 0;

	// loop on the string to parse
	for ( iCounter = 0; iCounter < strStringToParse.length ( ); ++ iCounter )
	{
		// searching the delimiter from the current position
		if ( 0 == strDelimiter.compare ( strStringToParse.substr ( iCounter, iDelimiterLength ) ) )
		{
			// the delimiter start at the current position. The result is pushed in the vector
			this->push_back ( strTmp );
			strTmp = "";
			iCounter = iCounter + iDelimiterLength - 1;
		}
		else
		{
			// the delimiter is not found at the current position
			strTmp += strStringToParse [ iCounter ];
		}
	}

	if ( ! strTmp.empty ( ) )
	{
		// the string is not finished with the delimiter.
		this->push_back ( strTmp );
	}
}

/* ---------------------------------------------------------------------------- */

