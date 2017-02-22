/* ---------------------------------------------------------------------------- */
//! CyWxVersionInfo.h
/* ---------------------------------------------------------------------------- */
//!
//! \file CyWxVersionInfo.h
//! \brief header file for class CyWxVersionInfo
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

#include "UtilitiesLayer/CyWxIncludes.h"

/* ---------------------------------------------------------------------------- */

//! \class CyWxVersionInfo
//! \brief this class get informations about the current version
//!
//! This class is based on the "Singleton" design pattern

class CyWxVersionInfo: public wxVersionInfo
{
	public:

		//! \fn getInstance ( )
		//! \return a constant reference to the one and only one instance of this class

		static const CyWxVersionInfo& getInstance ( );

		//! \fn getVersion ( )
		//! \return the version as string ( = Major + '.' + Minor +'.' + Micro )

		const wxString getVersion ( ) const;

		//! \fn getWebSite
		//! \return the web site linked to the application

		const wxString getWebSite ( ) const;

	private:

		//! \fn ~CyWxVersionInfo ( ) 
		//! contructor

		CyWxVersionInfo ( );

		//! \fn ~CyWxVersionInfo ( ) 
		//! destructor

		virtual ~CyWxVersionInfo( );

		//! \fn CyWxVersionInfo ( const CyWxVersionInfo& ) 
		//! copy constructor
		//! not implemented

		CyWxVersionInfo ( const CyWxVersionInfo& );

		//! \fn operator = ( const CyWxVersionInfo& ) 
		//! operator =
		//! \return a reference to a CyWxVersionInfo object
		//! not implemented

		CyWxVersionInfo& operator = ( const CyWxVersionInfo& );

		//! \var m_objWxVersionInfo
		//! the one and only one instance of the class

		static CyWxVersionInfo m_objWxVersionInfo;

};