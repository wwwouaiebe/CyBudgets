/* ---------------------------------------------------------------------------- */
//! CySqliteFunctions.cpp
/* ---------------------------------------------------------------------------- */
//!
//! \file CySqliteFunctions.cpp
//! \brief definition file for class CySqliteFunctions
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

#include "DataLayer/CySqliteFunctions.h"
#include "UtilitiesLayer/CyStdIncludes.h"

/* ---------------------------------------------------------------------------- */

void CySqliteFunctions::DoubleToCurrency ( sqlite3_context* context, int iArgumentCount, sqlite3_value** argumentsArray )
{
	if ( 1 == iArgumentCount )
	{

		// see the CyCurrencyConverter::toLongLong ( ) method for more explanations...
		double dValue = sqlite3_value_double ( argumentsArray [ 0 ] );

		dValue = dValue * 100;
		long long lValue = static_cast < long long > ( dValue );

		long long lTmp = lValue + 1;

		if ( abs ( dValue - lTmp ) < 0.01f )
		{
			++ lValue;
		}

		 lTmp = lValue - 1;

		if ( abs ( dValue - lTmp ) < 0.01f )
		{
			-- lValue;
		}

		sqlite3_result_int64 ( context, lValue );

		return;
	}
	sqlite3_result_null ( context );
}

/* ---------------------------------------------------------------------------- */

