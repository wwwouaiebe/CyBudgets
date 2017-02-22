/* ---------------------------------------------------------------------------- */
//! CyWxVersionInfo.cpp
/* ---------------------------------------------------------------------------- */
//!
//! \file CyWxVersionInfo.cpp
//! \brief definition file for class CyWxVersionInfo
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

#include "UtilitiesLayer/CyWxVersionInfo.h"
#include "sqlite3.h"

/* ---------------------------------------------------------------------------- */

CyWxVersionInfo CyWxVersionInfo::m_objWxVersionInfo;

/* ---------------------------------------------------------------------------- */

CyWxVersionInfo::CyWxVersionInfo ( ) :
	wxVersionInfo ( 
		wxString ( "CyBudgets" ),
		1,
		0,
		3, 
		wxString (
			wxString ( char ( 10 ) )
			+ wxString ( "This program is free software: you can redistribute it and/or modify it under the terms" )
			+ wxString ( char ( 10 ) )
			+ wxString ( "of the GNU General Public License as published by the Free Software Foundation, " )
			+ wxString ( char ( 10 ) )
			+ wxString ( "either version 3 of the License, or any later version." )
			+ wxString ( char ( 10 ) )
			+ wxString ( char ( 10 ) )
			+ wxString ( "This program is build with ")
			+ wxString ( wxVERSION_STRING )
			+ wxString ( " and SQLite " )
			+ wxString ( SQLITE_VERSION )
			+ wxString ( char ( 10 ) ) ),
		wxString ( "Copyright ( C ) 2014 - Christian Guyette" ) )
{
}

/* ---------------------------------------------------------------------------- */

CyWxVersionInfo::~CyWxVersionInfo( )
{
}

/* ---------------------------------------------------------------------------- */

const CyWxVersionInfo& CyWxVersionInfo::getInstance ( )
{
	return CyWxVersionInfo::m_objWxVersionInfo;
}

/* ---------------------------------------------------------------------------- */


const wxString CyWxVersionInfo::getVersion ( ) const
{
	wxString strVersion;
	strVersion
		<< this->GetMajor ( )
		<< wxString ( "." )
		<< this->GetMinor ( )
		<< wxString ( "." )
		<< this->GetMicro ( );

	return strVersion;
}


/* ---------------------------------------------------------------------------- */

const wxString CyWxVersionInfo::getWebSite ( ) const
{
	return  wxString ( "http://www.ouaie.be/" ) ;
}


/* ---------------------------------------------------------------------------- */




















