/* ---------------------------------------------------------------------------- */
//! CyIngDetailParser.cpp
/* ---------------------------------------------------------------------------- */
//!
//! \file CyIngDetailParser.cpp
//! \brief definition file for class CyIngDetailParser
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

#include "UtilitiesLayer/CyIngDetailParser.h"
#include "UtilitiesLayer/CyStringParser.h"

/* ---------------------------------------------------------------------------- */

CyIngDetailParser::CyIngDetailParser ( )
{
}

/* ---------------------------------------------------------------------------- */

CyIngDetailParser::~CyIngDetailParser ( )
{
}

/* ---------------------------------------------------------------------------- */

void CyIngDetailParser::parse ( const std::string& strStringToParse )
{
	// parsing the string. We consider that the substring are separed with 2 spaces
	CyStringParser objStringParser;
	objStringParser.parse ( "  ", strStringToParse );

	// now we remove the empty strings and the the strings with only one space
	CyStringParser::const_iterator iterator;
	for ( iterator = objStringParser.begin ( ); iterator != objStringParser.end ( ); ++ iterator )
	{
		if ( ! iterator->empty ( )  && ( *iterator != " " ) )
		{
			this->push_back ( *iterator );
		}
	}
}

/* ---------------------------------------------------------------------------- */

