/* ---------------------------------------------------------------------------- */
//! CyCurrencyConverter.h
/* ---------------------------------------------------------------------------- */
//!
//! \file CyCurrencyConverter.h
//! \brief header file for class CyCurrencyConverter
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

//! \class CyCurrencyConverter
//! \brief class with static methods to convert from double to long long or from long long to double 
//!
//! for currency, the decimal number is fixed. So it'snt a good idea to store currency as double in the database 
//! To avoid problems with decimals, currency is stored as long long in the database. Then currency 
//! must be converted to double in dialog boxes.
//!
//! \since version 1.0.3

class CyCurrencyConverter
{

	public:

		//! \fn toDouble ( const long long& lValue )
		//! @param [ in ] lValue a reference to the value to convert
		//!
		//! \return the value converted to double

		static double toDouble ( const long long& lValue );

		//! \fn toLongLong ( const double& dValue )
		//! @param [ in ] dValue a reference to the value to convert
		//!
		//! \return the value converted to long long

		static long long toLongLong ( const double& dValue );

	private:

		//! \fn CyCurrencyConverter ( ) 
		//! constructor
		//! not implemented, so it's impossible to instantiate objects of this class. Only static methods can be used

		CyCurrencyConverter ( );

		//! \fn ~CyCurrencyConverter ( ) 
		//! destructor
		//! not implemented

		virtual ~CyCurrencyConverter ();

		//! \fn CyCurrencyConverter ( const CyCurrencyConverter& ) 
		//! copy constructor
		//! not implemented

		CyCurrencyConverter ( const CyCurrencyConverter& );

		//! \fn operator = ( const CyCurrencyConverter& ) 
		//! operator =
		//! \return a reference to a CyCurrencyConverter object
		//! not implemented

		CyCurrencyConverter& operator = ( const CyCurrencyConverter& );

};