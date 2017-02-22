/* ---------------------------------------------------------------------------- */
//! CyStringValue.cpp
/* ---------------------------------------------------------------------------- */
//!
//! \file CyStringValue.cpp
//! \brief definition file for class CyStringValue
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

#include "DataLayer/CyStringValue.h"

/* ---------------------------------------------------------------------------- */

const wxString CyStringValue::m_strDummyValue = wxEmptyString;

/* ---------------------------------------------------------------------------- */

CyStringValue::CyStringValue ( )
{
}

/* ---------------------------------------------------------------------------- */

CyStringValue::~CyStringValue ( )
{
}

/* ---------------------------------------------------------------------------- */

wxString CyStringValue::getAsString ( ) const
{
	if ( this->isNull ( ) )
	{
		return wxEmptyString;
	}

	return this->m_strValue;
}

/* ---------------------------------------------------------------------------- */

void CyStringValue::set ( const wxString& strValue,  const wxString& strStringFormat /* = wxEmptyString */)
{
	wxString strTmpStringFormat = strStringFormat;
	if ( strTmpStringFormat.empty ( ) )
	{
		strTmpStringFormat = this->getStringFormat ( );
	}
	this->setNotNull ( );
	this->m_strValue = strValue;
	this->setStringFormat ( strTmpStringFormat );

}

/* ---------------------------------------------------------------------------- */

void CyStringValue::set ( const long long&,  const wxString& )
{

#ifdef CY_COMPILER_VC10
#pragma warning ( push )
#pragma warning ( disable: 4365 )
	assert ( "Invalid call to CyStringValue::set ( const long long&, const wxString& ) method" );
#endif
#ifdef CY_COMPILER_VC10
#pragma warning ( pop )
#endif

	throw ( std::exception ( ) );
}

/* ---------------------------------------------------------------------------- */


const wxString& CyStringValue::get ( wxString ) const
{

#ifdef CY_COMPILER_VC10
#pragma warning ( push )
#pragma warning ( disable: 4365 )
	assert ( ! this->isNull ( ) );
#endif
#ifdef CY_COMPILER_VC10
#pragma warning ( pop )
#endif

	if ( this->isNull ( ) )
	{
		throw ( std::exception ( ) );
	}

	return this->m_strValue;

}


/* ---------------------------------------------------------------------------- */

const long long & CyStringValue::get ( long long ) const
{

#ifdef CY_COMPILER_VC10
#pragma warning ( push )
#pragma warning ( disable: 4365 )
	assert ( "Invalid call to CyStringValue::get ( long long ) method" );
#endif
#ifdef CY_COMPILER_VC10
#pragma warning ( pop )
#endif

	throw ( std::exception ( ) );
}

/* ---------------------------------------------------------------------------- */

