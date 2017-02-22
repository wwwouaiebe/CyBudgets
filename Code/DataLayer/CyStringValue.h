/* ---------------------------------------------------------------------------- */
//! CyStringValue.h
/* ---------------------------------------------------------------------------- */
//!
//! \file CyStringValue.h
//! \brief header file for class CyStringValue
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

#include "DataLayer/CyValue.h"

/* ---------------------------------------------------------------------------- */

//! \class CyStringValue
//! \brief simple container for values of type wxString
//!
//! This class is used to do the data exchange betwwen the database and the user interface

class CyStringValue : public CyValue
{

	public:

		//! \fn CyStringValue ( ) 
		//! constructor

		CyStringValue ( );

		//! \fn ~CyStringValue ( ) 
		//! destructor

		virtual ~CyStringValue ( );

		//! \fn getAsString ( )
		//! \return the value stored as a wxString if the container is not null, an empty string otherwise

		virtual wxString getAsString ( ) const;

		//! \fn get (  wxString strValue ) const
		//! get method
		//! @param [ in ] strValue a wxString used to force the compilator to select the correct virtual method. See also CyStringValue::m_strDummyValue
		//! \return the value stored in the object

		virtual const wxString& get ( wxString strValue ) const;

		//! \fn get ( long long lValue ) const
		//! get method
		//! @param [ in ] lValue a long long used to force the compilator to select the correct virtual method. See also  CyLongValue::m_lDummyValue
		//! \return the value stored in the object
		//! \throw std::exception
		//! this method throw always an exception and must never bbe called

		virtual const long long & get ( long long lValue ) const;


		//! \fn set ( const wxString& strValue,  const wxString& strStringFormat )
		//! set method
		//! @param [ in ] strValue a wxString reference to be stored in the object
		//! @param [ in ] strStringFormat a wxString reference with the format to use

		virtual void set ( const wxString& strValue,  const wxString& strStringFormat  = wxEmptyString );

		//! \fn set ( const long long& lValue, const wxString& strStringFormat )
		//! set method
		//! @param [ in ] lValue a double reference to be stored in the object
		//! @param [ in ] strStringFormat a wxString reference with the format to use

		virtual void set ( const long long& lValue, const wxString& strStringFormat = wxEmptyString );

		//! var m_strDummyValue
		//! Dummy variable to use with the get ( ) methods

		static const wxString m_strDummyValue;

	private:

		//! \fn CyStringValue ( const CyStringValue& ) 
		//! copy constructor
		//! not implemented

		CyStringValue ( const CyStringValue& );

		//! \fn operator = ( const CyStringValue& ) 
		//! operator =
		//! \return a reference to a CyStringValue object
		//! not implemented

		CyStringValue& operator = ( const CyStringValue& );

		//! \var m_strValue
		//! the varable where the value is stored

		wxString m_strValue;

};

/* ---------------------------------------------------------------------------- */

