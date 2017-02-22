/* ---------------------------------------------------------------------------- */
//! CyLongValue.cpp
/* ---------------------------------------------------------------------------- */
//!
//! \file CyLongValue.cpp
//! \brief definition file for class CyLongValue
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

#include "DataLayer/CyLongValue.h"
#include "DataLayer/CyUserPreferences.h"
#include "UtilitiesLayer/CyEnum.h"

/* ---------------------------------------------------------------------------- */

const long long CyLongValue::m_lDummyValue = 0;

/* ---------------------------------------------------------------------------- */

CyLongValue::CyLongValue ( ) :
	m_lValue ( 0 )
{
	this->setValueType ( CyFormatInteger );
}

/* ---------------------------------------------------------------------------- */

CyLongValue::~CyLongValue ( )
{
}

/* ---------------------------------------------------------------------------- */

wxString CyLongValue::getAsBoolean ( ) const
{
	return 
		( ( 0 != this->m_lValue ) && ( ! this->isNull ( ) ) )
		? 
		CyUserPreferences::getInstance ( ).getBooleanTrueSymbol ( ) 
		:
		CyUserPreferences::getInstance ( ).getBooleanFalseSymbol ( );
}

/* ---------------------------------------------------------------------------- */

wxString CyLongValue::getAsCurrency ( ) const
{
	long long lValue = this->m_lValue;

	wxString strCurrencyToStringValue;

	if ( CyUserPreferences::getInstance ( ).isCurrencySymbolBefore ( ) )
	{
		strCurrencyToStringValue
			<< CyUserPreferences::getInstance ( ).getCurrencySymbol ( );
	}

	if ( 0 < lValue )
	{
		strCurrencyToStringValue
			<< CyUserPreferences::getInstance ( ).getCurrencyPositiveSymbol ( );
	}
	else if ( 0 > lValue )
	{
		strCurrencyToStringValue
			<< CyUserPreferences::getInstance ( ).getCurrencyNegativeSymbol ( );
	}

	lValue = abs ( lValue );

	long long lDec = 1;

	for (int iCounter = 0; iCounter < CyUserPreferences::getInstance ( ).getCurrencyDecimalPrecision ( ); ++ iCounter )
	{
		lDec *= 10;
	}

	wxString strInteger;
	strInteger
		<< ( lValue / lDec );


	long long lSplitEndPos = static_cast < long long > ( strInteger.length ( ) ) % CyUserPreferences::getInstance ( ).getGrouping ( );
	if ( 0 == lSplitEndPos )
	{
		lSplitEndPos = CyUserPreferences::getInstance ( ).getGrouping ( );
	}
	long long lSplitLength = lSplitEndPos;
	long long lSplitSartPos = 0;

	while ( lSplitEndPos <= static_cast < long long > ( strInteger.length ( ) ) )
	{
		strCurrencyToStringValue
			<< strInteger.substr ( static_cast < size_t > ( lSplitSartPos ), static_cast < size_t > ( lSplitLength ) );
		lSplitSartPos += lSplitLength;
		lSplitLength = CyUserPreferences::getInstance ( ).getGrouping ( );
		if ( lSplitEndPos < static_cast < long long > ( strInteger.length ( ) ) )
		{
			strCurrencyToStringValue
				<< CyUserPreferences::getInstance ( ).getThousandSeparator ( );
		}
		lSplitEndPos += lSplitLength;
	}

	if ( 0 != CyUserPreferences::getInstance ( ).getCurrencyDecimalPrecision ( ) )
	{
		strCurrencyToStringValue
			<< CyUserPreferences::getInstance ( ).getDecimalSeparator ( );

		wxString strDecimal;
		strDecimal
			<< ( lValue % lDec );

		strDecimal.Pad ( static_cast < size_t > ( CyUserPreferences::getInstance ( ).getCurrencyDecimalPrecision ( ) ) - strDecimal.Length ( ) , L'\x30', false );

		strCurrencyToStringValue
			<< strDecimal;
	}

	if ( ! CyUserPreferences::getInstance ( ).isCurrencySymbolBefore ( ) )
	{
		strCurrencyToStringValue
			<< CyUserPreferences::getInstance ( ).getCurrencySymbol ( );
	}


	return strCurrencyToStringValue;
}

/* ---------------------------------------------------------------------------- */

wxString CyLongValue::getAsString ( ) const
{
	switch ( this->getValueType ( ) )
	{
	case CyFormatBoolean:
		return this->getAsBoolean ( );
		break;
	case CyFormatCurrency:
		return this->getAsCurrency ( );
	}

	wxString strTmp;
	if ( this->isNull ( ) )
	{
		strTmp << wxEmptyString;
	}
	else
	{
		strTmp << this->m_lValue;
	}

	return strTmp;
}

/* ---------------------------------------------------------------------------- */

const wxString& CyLongValue::get ( wxString ) const
{

#ifdef CY_COMPILER_VC10
#pragma warning ( push )
#pragma warning ( disable: 4365 )
	assert ( "Invalid call to CyLongValue::get ( wxString ) method" );
#endif
#ifdef CY_COMPILER_VC10
#pragma warning ( pop )
#endif

	throw ( std::exception ( ) );
}

/* ---------------------------------------------------------------------------- */

const long long & CyLongValue::get ( long long ) const
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

	return this->m_lValue;
}

/* ---------------------------------------------------------------------------- */

void CyLongValue::set (const long long& lValue, const wxString& strStringFormat /* = wxEmptyString */ )
{
	wxString strTmpStringFormat = strStringFormat;
	bool bReuseStringFormat = false;
	if ( strTmpStringFormat.empty ( ) )
	{
		strTmpStringFormat = this->getStringFormat ( );
		bReuseStringFormat = true;
	}
	this->setNotNull ( );
	this->m_lValue = lValue;
	this->setStringFormat ( strTmpStringFormat );
	switch ( this->getValueType ( ) )
	{
	case CyFormatCurrency:
		if ( ( CyNoFormat == this->getForegroundColor ( ) ) || ( bReuseStringFormat  ) )
		{
			this->setForegroundColor ( ( 0 > this->m_lValue ) ? CyUserPreferences::getInstance ( ).getCurrencyNegativeColor ( ) : CyUserPreferences::getInstance ( ).getCurrencyPositiveColor ( ) );
		}
		if ( CyNoFormat == this->getHorizontalAlignment ( ) )
		{
			this->setHorizontalAlignment ( CyHorizontalAlignmentRight );
		}
		break;
	case CyFormatBoolean:
		if ( CyNoFormat == this->getHorizontalAlignment ( ) )
		{
			this->setHorizontalAlignment ( CyHorizontalAlignmentCenter );
		}
		break;
	case CyFormatInteger:
		if ( CyNoFormat == this->getHorizontalAlignment ( ) )
		{
			this->setHorizontalAlignment ( CyHorizontalAlignmentRight );
		}
		break;
	}
}

/* ---------------------------------------------------------------------------- */

void CyLongValue::set ( const wxString&, const wxString& )
{

#ifdef CY_COMPILER_VC10
#pragma warning ( push )
#pragma warning ( disable: 4365 )
	assert ( "Invalid call to CyLongValue::set ( const wxString& strValue, const wxString& strStringFormat ) method" );
#endif
#ifdef CY_COMPILER_VC10
#pragma warning ( pop )
#endif

	throw ( std::exception ( ) );
}

/* ---------------------------------------------------------------------------- */

