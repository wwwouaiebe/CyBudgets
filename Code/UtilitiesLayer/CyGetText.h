/* ---------------------------------------------------------------------------- */
//! CyGetText.h
/* ---------------------------------------------------------------------------- */
//!
//! \file CyGetText.h
//! \brief header file for class CyGetText
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

//! \todo Store the last language used and create a method to change the language

/* ---------------------------------------------------------------------------- */

#pragma once

/* ---------------------------------------------------------------------------- */

#include "UtilitiesLayer/CyStdIncludes.h"

/* ---------------------------------------------------------------------------- */

class wxString;

/* ---------------------------------------------------------------------------- */

//! \class CyGetText
//! \brief class used to manage the displayed texts
//!
//! this class is used to:
//! - read the message file at the beginning of the application
//! - store the messages
//! - give the message to the application when needed
//!
//! This class is implemented following the 'Singleton' design pattern
//!
//! How to use this class:
//! - call the one and only one possible instance with the getInstance ( ) method
//! - use the getText ( ) method to find a message

class CyGetText
{

	public:

		//! \fn ~CyGetText ( ) 
		//! destructor

		virtual ~CyGetText ( );

		//! \fn getInstance ( )
		//! this method gives the unique instance of the class
		//! \return a reference to the one and only one instance of the class

		static const CyGetText& getInstance ( );

		//! \fn getText ( )
		//! @param [ in ] strKey the key corresponding to the desired message
		//! 
		//! \return the text corresponding to the key, if the key is found, the key itself otherwise

		const wxString& getText ( const wxString& strKey ) const;

	private:

		//! \fn CyGetText ( ) 
		//! constructor

		CyGetText ( );

		//! \fn init ( )
		//! this method do the initialization of the instance.

		void init ( );

		//! \fn CyGetText ( const CyGetText& ) 
		//! copy constructor
		//! not implemented

		CyGetText ( const CyGetText& );

		//! \fn operator = ( const CyGetText& ) 
		//! operator =
		//! \return a reference to a CyGetText object
		//! not implemented

		CyGetText& operator = ( const CyGetText );

		//! \var m_MessagesMap
		//! a map with the messages. The msgid string from the .po file is the key and the msgstr string is the value
		
		std::map < wxString, wxString > m_MessagesMap;

		//! \var m_bInitialized
		//! true when a message file is loaded in the m_MessagesMap variable

		bool m_bInitialized;

		//! \var m_objGetText
		//! the one and only one instance

		static CyGetText m_objGetText;
};

/* ---------------------------------------------------------------------------- */
