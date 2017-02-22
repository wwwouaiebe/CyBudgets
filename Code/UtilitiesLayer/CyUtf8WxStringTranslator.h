/* ---------------------------------------------------------------------------- */
//! CyUtf8WxStringTranslator.h
/* ---------------------------------------------------------------------------- */
//!
//! \file CyUtf8WxStringTranslator.h
//! \brief fichier d'en-tête de la classe CyUtf8WxStringTranslator
//!
/* ----------------------------------------------------------------------------
    contact: http://www.planetaires.net

    This file is a part of the CyGraphics program

    Copyright ( C ) 2012 - Christian Guyette

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

// Ligne ajoutée pour forcer Visual Studio à sauver en UTF-8 ŉŋ

/* ---------------------------------------------------------------------------- */

#pragma once

/* ---------------------------------------------------------------------------- */

#include "UtilitiesLayer/CyStdIncludes.h"

/* ---------------------------------------------------------------------------- */

class wxString;

/* ---------------------------------------------------------------------------- */

//!
//! \class CyUtf8WxStringTranslator
//! \brief this class transforms a std::string encoded as UTF-8 to a wxString or a wxString to a std::string encoded as UTF-8
//!

class CyUtf8WxStringTranslator
{
	public:

		//! \fn CyUtf8WxStringTranslator ( ) 
		//! constructor

		CyUtf8WxStringTranslator ( );

		//! \fn ~CyUtf8WxStringTranslator ( ) 
		//! destructor

		virtual ~CyUtf8WxStringTranslator ( );

		//! \fn fromWxStringToUtf8 ( wxString strWxString ) const
		//! This method transforms a wxString to a std:string encode as UTF-8
		//! @param [ in ] strWxString a wxString
		//! \return the entry transformed to a std::string encoded as UTF-8

		std::string fromWxStringToUtf8 ( wxString strWxString ) const;

		//! \fn fromUtf8ToWxString ( std::string strUtf8 )
		//! This method transforms a std:string encode as UTF-8 to a wxString
		//! @param [ in ] strUtf8 a std:string encoded as UTF-8
		//! \return the entry transformed to a wxString

		wxString fromUtf8ToWxString ( std::string strUtf8 ) const;

	private:

		//! \fn CyUtf8WxStringTranslator ( const CyUtf8WxStringTranslator& ) 
		//! copy constructor
		//! not implemented

		CyUtf8WxStringTranslator ( const CyUtf8WxStringTranslator& );

		//! \fn operator = ( const CyUtf8WxStringTranslator& ) 
		//! operator =
		//! \return a reference to a CyUtf8WxStringTranslator object
		//! not implemented

		CyUtf8WxStringTranslator& operator = ( const CyUtf8WxStringTranslator& );

};

/* ---------------------------------------------------------------------------- */

