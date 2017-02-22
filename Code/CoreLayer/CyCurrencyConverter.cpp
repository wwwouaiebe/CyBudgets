/* ---------------------------------------------------------------------------- */
//! CyCurrencyConverter.cpp
/* ---------------------------------------------------------------------------- */
//!
//! \file CyCurrencyConverter.cpp
//! \brief definition file for class CyCurrencyConverter
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

# include "CoreLayer/CyCurrencyConverter.h"
# include "DataLayer/CyUserPreferences.h"

/* ---------------------------------------------------------------------------- */

double CyCurrencyConverter::toDouble ( const long long& lValue )
{
	// we search the number of decimal used for the currency
	long long lDecimalPrecision = 1;

	for (int iCounter = 0; iCounter < CyUserPreferences::getInstance ( ).getCurrencyDecimalPrecision ( ); ++ iCounter )
	{
		lDecimalPrecision *= 10;
	}

	// and then the value is converted
	return static_cast < double> ( lValue ) / lDecimalPrecision;
}

/* ---------------------------------------------------------------------------- */

long long CyCurrencyConverter::toLongLong ( const double& dValue )
{
	// we search the number of decimal used for the currency
	long long lDecimalPrecision = 1;

	for (int iCounter = 0; iCounter < CyUserPreferences::getInstance ( ).getCurrencyDecimalPrecision ( ); ++ iCounter )
	{
		lDecimalPrecision *= 10;
	}

	// the value is converted as double...
	double dTmpValue = dValue * lDecimalPrecision;

	// ...and as long
	long long lValue = static_cast < long long > ( dTmpValue );

	// Sample 1 : ldecimalPrecision = 100, dValue = 5.20999999, dTmpValue = 520.999999, lValue = 520 but we expect to have 521
	// Sample 2 : ldecimalPrecision = 100, dValue = -5.20999999, dTmpValue = -520.999999, lValue = -520 but we expect to have -521

	// Then the long value + 1 is compared with the double value
	long long lTmp = lValue + 1;
	// Sample 1 : lTmp = 521
	// Sample 2 : lTmp = -519

	if ( abs ( dTmpValue - lTmp ) < 0.01f )
	{
		// Sample 1 : abs ( 520.999999 - 521 ) = 0.000001f < 0.01f
		// Sample 2 : abs ( -520.999999 - ( -519 ) ) = 1.999999f > 0.01f
		// if a delta is found the value is incremented
		++ lValue;
		// Sample 1 : lValue = 521
		// Sample 2 : lValue is not changed
	}

	// Then the long value - 1 is compared with the double value
	lTmp = lValue - 1;
	// Sample 1 : lTmp = 520
	// Sample 2 : lTmp = -521

	if ( abs ( dTmpValue - lTmp ) < 0.01f )
	{
		// Sample 1 : abs ( 520.999999 - 520 ) = 0.999999f > 0.01f
		// Sample 2 : abs ( -520.999999 - ( -521 ) ) = 0.000001f < 0.01f
		// if a delta is found the value is decremented
		-- lValue;
		// Sample 1 : lValue is not changed
		// Sample 2 : lValue = -521
	}

	// CyCurrencyConverter::toLongLong ( 5.20999999 ) returns 521
	// CyCurrencyConverter::toLongLong ( -5.20999999 ) returns -521
	// CyCurrencyConverter::toLongLong ( 5.20000001 ) returns 520
	// CyCurrencyConverter::toLongLong ( -5.20000001 ) returns -520

	return lValue;
}

/* ---------------------------------------------------------------------------- */
