/* ---------------------------------------------------------------------------- */
//! CyWxPersistentUserPreferences.cpp
/* ---------------------------------------------------------------------------- */
//!
//! \file CyWxPersistentUserPreferences.cpp
//! \brief definition file for class CyWxPersistentUserPreferences
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
#include "DataLayer/CySqliteDb.h"

/* ---------------------------------------------------------------------------- */

CyWxPersistentUserPreferences::CyWxPersistentUserPreferences (  CyUserPreferences* pUserPreferences ) :
	wxPersistentObject ( pUserPreferences )
{
}

/* ---------------------------------------------------------------------------- */

wxString CyWxPersistentUserPreferences::GetKind ( ) const
{
	return wxString ( "CyWxPersistentUserPreferences" );
}

/* ---------------------------------------------------------------------------- */

CyUserPreferences* CyWxPersistentUserPreferences::Get ( ) const
{
	return static_cast < CyUserPreferences* > ( this->GetObject () );
}

/* ---------------------------------------------------------------------------- */

wxString CyWxPersistentUserPreferences::GetName ( ) const
{
	return this->Get ( )->getName ( );
}

/* ---------------------------------------------------------------------------- */

bool CyWxPersistentUserPreferences::Restore ( )
{
	bool bReturnValue = true;

	bReturnValue &=  CySqliteDb::getInstance ( ).getParameter ( wxString ( "CurrencyDecimalPrecision" ), this->Get ( )->m_lCurrencyDecimalPrecision );
	bReturnValue &= CySqliteDb::getInstance ( ).getParameter ( wxString ( "CurrencySymbol" ), this->Get ( )->m_strCurrencySymbol );

	bReturnValue &= this->RestoreValue ( wxString ( "CurrencyPositiveSymbol" ), &( this->Get ( )->m_strCurrencyPositiveSymbol ) );

	bReturnValue &= this->RestoreValue ( wxString ( "CurrencyNegativeSymbol" ), &( this->Get ( )->m_strCurrencyNegativeSymbol ) );

	wxString strTmpCurrencyPositiveColor;
	bool bTmpReturnValue = this->RestoreValue ( wxString ( "CurrencyPositiveColor" ), &strTmpCurrencyPositiveColor );
	if ( bTmpReturnValue && ( 0 < strTmpCurrencyPositiveColor.length ( ) ) )
	{
		this->Get ( )->m_strCurrencyPositiveColor = strTmpCurrencyPositiveColor.at ( 0 );
	}
	else
	{
		bTmpReturnValue = false;
	}
	bReturnValue &= bTmpReturnValue;

	wxString strTmpCurrencyNegativeColor;
	bTmpReturnValue = this->RestoreValue ( wxString ( "CurrencyNegativeColor" ), &strTmpCurrencyNegativeColor );
	if ( bTmpReturnValue && ( 0 < strTmpCurrencyNegativeColor.length ( ) ) )
	{
		this->Get ( )->m_strCurrencyNegativeColor = strTmpCurrencyNegativeColor.at ( 0 );
	}
	else
	{
		bTmpReturnValue = false;
	}
	bReturnValue &= bTmpReturnValue;

	bReturnValue &= this->RestoreValue ( wxString ( "DecimalSeparator" ), &( this->Get ( )->m_strDecimalSeparator ) );

	bReturnValue &= this->RestoreValue ( wxString ( "ThousandSeparator" ), &( this->Get ( )->m_strThousandSeparator ) );

	int iTmpGrouping;
	bTmpReturnValue = this->RestoreValue ( wxString ( "Grouping" ), &iTmpGrouping );
	if ( bTmpReturnValue )
	{
		this->Get ( )->m_lGrouping = iTmpGrouping;
	}
	bReturnValue &= bTmpReturnValue;

	int iTmpCurrencySymbolBefore;
	bTmpReturnValue = this->RestoreValue ( wxString ( "CurrencySymbolBefore" ), &iTmpCurrencySymbolBefore );
	if ( bTmpReturnValue && ( ( CyEnum::kYes == iTmpCurrencySymbolBefore ) || ( CyEnum::kNo == iTmpCurrencySymbolBefore ) ) )
	{
		this->Get ( )->m_bCurrencySymbolBefore = CyEnum::kYes == iTmpCurrencySymbolBefore ? CyEnum::kYes : CyEnum::kNo;
	}
	else
	{
		bTmpReturnValue = false;
	}
	bReturnValue &= bTmpReturnValue;

	bReturnValue &= this->RestoreValue ( wxString ( "BooleanTrueSymbol" ), &( this->Get ( )->m_strBooleanTrueSymbol ) );

	bReturnValue &= this->RestoreValue ( wxString ( "BooleanFalseSymbol" ), &( this->Get ( )->m_strBooleanFalseSymbol ) );

	bReturnValue &= this->RestoreValue ( wxString ( "UserLanguage" ), &( this->Get ( )->m_strUserLanguage ) );

	bReturnValue &= this->RestoreValue ( wxString ( "LastUsedFilePath" ), &( this->Get ( )->m_strLastUsedFilePath ) );

	bReturnValue &= this->RestoreValue ( wxString ( "LastUsedFileName" ), &( this->Get ( )->m_strLastUsedFileName ) );

	int iTmpReuseLastFile;
	bTmpReturnValue = this->RestoreValue ( wxString ( "ReuseLastFile" ), &iTmpReuseLastFile );
	if ( bTmpReturnValue && ( ( CyEnum::kYes == iTmpReuseLastFile ) || ( CyEnum::kNo == iTmpReuseLastFile ) ) )
	{
		this->Get ( )->m_bReuseLastFile = CyEnum::kYes == iTmpReuseLastFile ? CyEnum::kYes : CyEnum::kNo;
	}
	else
	{
		bTmpReturnValue = false;
	}
	bReturnValue &= bTmpReturnValue;

	int iTmpDeleteImportFile;
	bTmpReturnValue = this->RestoreValue ( wxString ( "DeleteImportFile" ), &iTmpDeleteImportFile );
	if ( bTmpReturnValue && ( ( CyEnum::kYes == iTmpDeleteImportFile ) || ( CyEnum::kNo == iTmpDeleteImportFile ) ) )
	{
		this->Get ( )->m_bDeleteImportFile = CyEnum::kYes == iTmpDeleteImportFile ? CyEnum::kYes : CyEnum::kNo;
	}
	else
	{
		bTmpReturnValue = false;
	}
	bReturnValue &= bTmpReturnValue;

	return bReturnValue;
}

/* ---------------------------------------------------------------------------- */

void CyWxPersistentUserPreferences::Save ( ) const
{
	CySqliteDb::getInstance ( ).setParameter ( wxString ( "CurrencyDecimalPrecision" ), this->Get ( )->getCurrencyDecimalPrecision ( ) );
	CySqliteDb::getInstance ( ).setParameter ( wxString ( "CurrencySymbol" ), this->Get ( )->getCurrencySymbol ( ) );

	this->SaveValue ( wxString ( "CurrencyPositiveSymbol" ), this->Get ( )->getCurrencyPositiveSymbol ( ) );

	this->SaveValue ( wxString ( "CurrencyNegativeSymbol" ), this->Get ( )->getCurrencyNegativeSymbol ( ) );

	wxString strTmpCurrencyPositiveColor;
	strTmpCurrencyPositiveColor
		<< this->Get ( )->getCurrencyPositiveColor ( );
	this->SaveValue ( wxString ( "CurrencyPositiveColor" ), strTmpCurrencyPositiveColor );

	wxString strTmpCurrencyNegativeColor;
	strTmpCurrencyNegativeColor
		<< this->Get ( )->getCurrencyNegativeColor ( );
	this->SaveValue ( wxString ( "CurrencyNegativeColor" ), strTmpCurrencyNegativeColor );

	this->SaveValue ( wxString ( "DecimalSeparator" ), this->Get ( )->getDecimalSeparator ( ) );

	this->SaveValue ( wxString ( "ThousandSeparator" ), this->Get ( )->getThousandSeparator ( ) );

	int iTmpGrouping = static_cast < int > ( this->Get ( )->getGrouping ( ) );
	this->SaveValue ( wxString ( "Grouping" ), iTmpGrouping );

	int iTmpCurrencySymbolBefore = this->Get ( )->isCurrencySymbolBefore ( ) ? CyEnum::kYes : CyEnum::kNo;
	this->SaveValue ( wxString ( "CurrencySymbolBefore" ), iTmpCurrencySymbolBefore );

	this->SaveValue ( wxString ( "BooleanTrueSymbol" ), this->Get ( )->getBooleanTrueSymbol ( ) );

	this->SaveValue ( wxString ( "BooleanFalseSymbol" ), this->Get ( )->getBooleanFalseSymbol ( ) );

	this->SaveValue ( wxString ( "UserLanguage" ), this->Get ( )->getUserLanguage ( ) );

	this->SaveValue ( wxString ( "LastUsedFilePath" ), this->Get ( )->m_strLastUsedFilePath );

	this->SaveValue ( wxString ( "LastUsedFileName" ), this->Get ( )->m_strLastUsedFileName );

	int iTmpReuseLastFile = this->Get ( )->m_bReuseLastFile ? CyEnum::kYes : CyEnum::kNo;
	this->SaveValue ( wxString ( "ReuseLastFile" ), iTmpReuseLastFile );

	int iTmpDeleteImportFile = this->Get ( )->m_bDeleteImportFile ? CyEnum::kYes : CyEnum::kNo;
	this->SaveValue ( wxString ( "DeleteImportFile" ), iTmpDeleteImportFile );

}

/* ---------------------------------------------------------------------------- */

wxPersistentObject *wxCreatePersistentObject ( CyUserPreferences* pUserPreferences )
{
    return new CyWxPersistentUserPreferences ( pUserPreferences );
}

/* ---------------------------------------------------------------------------- */
