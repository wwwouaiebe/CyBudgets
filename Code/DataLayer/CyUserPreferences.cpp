/* ---------------------------------------------------------------------------- */
//! CyUserPreferences.cpp
/* ---------------------------------------------------------------------------- */
//!
//! \file CyUserPreferences.cpp
//! \brief definition file for class CyUserPreferences
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

#include "DataLayer/CyWxPersistentUserPreferences.h"
#include "UtilitiesLayer/CyEnum.h"

/* ---------------------------------------------------------------------------- */

CyUserPreferences CyUserPreferences::m_objUserPreferences;

/* ---------------------------------------------------------------------------- */

CyUserPreferences::CyUserPreferences ( ):
	m_lCurrencyDecimalPrecision ( 2 ),
	m_strCurrencyPositiveSymbol ( L"+" ),
	m_strCurrencyNegativeSymbol ( L"-"),
	m_strCurrencyPositiveColor ( CyForegroundGreen ),
	m_strCurrencyNegativeColor ( CyForegroundRed ),
	m_strDecimalSeparator ( L",") ,
	m_strThousandSeparator (L"."),
	m_lGrouping ( 3 ),
	m_strCurrencySymbol ( L" €"),
	m_bCurrencySymbolBefore ( false ),
	m_strBooleanTrueSymbol (  L"✓" ),
	m_strBooleanFalseSymbol ( L"" ),
	m_strUserLanguage ( wxString ( "FR_be" ) ),
	m_strLastUsedFileName ( wxEmptyString ),
	m_strLastUsedFilePath ( wxEmptyString ),
	m_bReuseLastFile ( false ),
	m_bDeleteImportFile ( false ),
	m_bInit ( false )
{
}

/* ---------------------------------------------------------------------------- */

 CyUserPreferences::~CyUserPreferences ( )
{
}

/* ---------------------------------------------------------------------------- */

CyUserPreferences& CyUserPreferences::getInstance ( )
{
	if ( ! m_objUserPreferences.m_bInit )
	{
		m_objUserPreferences.init ( );
	}

	return m_objUserPreferences;
}

/* ---------------------------------------------------------------------------- */

void CyUserPreferences::init ( )
{
	this->setName ( wxString ( "CyUserPreferences" ) );
	wxPersistenceManager::Get ( ).RegisterAndRestore ( this );

	this->m_bInit = true;
}

/* ---------------------------------------------------------------------------- */

void CyUserPreferences::save ( ) 
{
	wxPersistenceManager::Get ( ).Save ( this );
}

/* ---------------------------------------------------------------------------- */

const long long& CyUserPreferences::getCurrencyDecimalPrecision ( ) const
{
	return this->m_lCurrencyDecimalPrecision;
}

/* ---------------------------------------------------------------------------- */

const wxString& CyUserPreferences::getCurrencyPositiveSymbol ( ) const
{
	return this->m_strCurrencyPositiveSymbol;
}

/* ---------------------------------------------------------------------------- */

const wxString& CyUserPreferences::getCurrencyNegativeSymbol ( ) const
{
	return this->m_strCurrencyNegativeSymbol;
}

/* ---------------------------------------------------------------------------- */

const wchar_t& CyUserPreferences::getCurrencyPositiveColor ( ) const
{
	return this->m_strCurrencyPositiveColor;
}

/* ---------------------------------------------------------------------------- */

const wchar_t& CyUserPreferences::getCurrencyNegativeColor ( ) const
{
	return this->m_strCurrencyNegativeColor;
}

/* ---------------------------------------------------------------------------- */

const wxString& CyUserPreferences::getDecimalSeparator ( ) const
{
	return this->m_strDecimalSeparator;
}

/* ---------------------------------------------------------------------------- */

const wxString& CyUserPreferences::getThousandSeparator ( ) const
{
	return this->m_strThousandSeparator;
}

/* ---------------------------------------------------------------------------- */

const long long& CyUserPreferences::getGrouping ( ) const
{
	return this->m_lGrouping;
}

/* ---------------------------------------------------------------------------- */

const wxString& CyUserPreferences::getCurrencySymbol ( ) const
{
	return this->m_strCurrencySymbol;
}

/* ---------------------------------------------------------------------------- */

const bool& CyUserPreferences::isCurrencySymbolBefore ( ) const
{
	return this->m_bCurrencySymbolBefore;
}

/* ---------------------------------------------------------------------------- */

const wxString& CyUserPreferences::getBooleanTrueSymbol ( ) const
{
	return this->m_strBooleanTrueSymbol;
}

/* ---------------------------------------------------------------------------- */

const wxString& CyUserPreferences::getBooleanFalseSymbol ( ) const
{
	return this->m_strBooleanFalseSymbol;
}

/* ---------------------------------------------------------------------------- */

const wxString& CyUserPreferences::getUserLanguage ( ) const
{
	return this->m_strUserLanguage;
}

/* ---------------------------------------------------------------------------- */

bool CyUserPreferences::getLastUsedFile ( wxString& strPath, wxString& strFileName ) const
{
	if ( ( this->m_bReuseLastFile ) && ( wxEmptyString != this->m_strLastUsedFileName ) && ( wxEmptyString != this->m_strLastUsedFilePath ) )
	{
		strPath = this->m_strLastUsedFilePath;
		strFileName = this->m_strLastUsedFileName;

		return true;
	}
	else
	{
		strPath = wxEmptyString;
		strFileName = wxEmptyString;

		return false;
	}
}

/* ---------------------------------------------------------------------------- */

bool CyUserPreferences::getReuseLastFile ( ) const
{
	return this->m_bReuseLastFile;
}

/* ---------------------------------------------------------------------------- */

bool CyUserPreferences::getDeleteImportFile ( ) const
{
	return this->m_bDeleteImportFile;
}

/* ---------------------------------------------------------------------------- */

const wxString& CyUserPreferences::getName ( ) const
{
	return this->m_strName;
}

/* ---------------------------------------------------------------------------- */

void CyUserPreferences::setName ( const wxString& strName )
{
	this->m_strName = strName;
}

/* ---------------------------------------------------------------------------- */