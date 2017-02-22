/* ---------------------------------------------------------------------------- */
//! CyValue.cpp
/* ---------------------------------------------------------------------------- */
//!
//! \file CyValue.cpp
//! \brief definition file for class CyValue
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

#include "DataLayer/CyValue.h"
#include "UtilitiesLayer/CyEnum.h"

/* ---------------------------------------------------------------------------- */

CyValue::CyValue ( ):
	m_strStringFormat ( "" ),
	m_bIsNull ( true ),
	m_strValueType ( CyNoFormat ),
	m_strHorizontalAlignment ( CyNoFormat ),
	m_strVerticalAlignment ( CyNoFormat ),
	m_strForegroundColor ( CyNoFormat ),
	m_strBackgroundColor ( CyNoFormat ),
	m_bFontBold ( false ),
	m_bFontItalic ( false ),
	m_bFontUnderlined ( false )
{
}

/* ---------------------------------------------------------------------------- */

CyValue::~CyValue ( )
{
}

/* ---------------------------------------------------------------------------- */

bool CyValue::isNull ( ) const
{
	return this->m_bIsNull;
}

/* ---------------------------------------------------------------------------- */

const wchar_t& CyValue::getValueType ( ) const
{
	return this->m_strValueType;
}

/* ---------------------------------------------------------------------------- */

const wchar_t& CyValue::getHorizontalAlignment ( ) const
{
	return this->m_strHorizontalAlignment;
}

/* ---------------------------------------------------------------------------- */

const wchar_t& CyValue::getVerticalAlignment ( ) const
{
	return this->m_strVerticalAlignment;
}

/* ---------------------------------------------------------------------------- */

const wchar_t& CyValue::getForegroundColor ( ) const
{
	return this->m_strForegroundColor;
}

/* ---------------------------------------------------------------------------- */

const wchar_t& CyValue::getBackgroundColor ( ) const
{
	return this->m_strBackgroundColor;
}

/* ---------------------------------------------------------------------------- */

bool CyValue::setValueType ( const wchar_t& strValueType )
{
	switch ( strValueType )
	{
	case CyFormatBoolean:
	case CyFormatCurrency:
	case CyFormatDate:
	case CyFormatHidden:
	case CyFormatInteger:
	case CyFormatReal:
	case CyFormatString:
		this->m_strValueType = strValueType;
		return true;
		break;
	default:
		return false;
		break;
	}
}

/* ---------------------------------------------------------------------------- */

bool CyValue::setHorizontalAlignment ( const wchar_t& strHorizontalAlignment )
{
	switch ( strHorizontalAlignment )
	{
	case CyHorizontalAlignmentCenter:
	case CyHorizontalAlignmentLeft:
	case CyHorizontalAlignmentRight:
		this->m_strHorizontalAlignment = strHorizontalAlignment;
		return true;
		break;
	default:
		return false;
		break;
	}
}

/* ---------------------------------------------------------------------------- */

bool CyValue::setVerticalAlignment ( const wchar_t& strVerticalAlignment )
{
	switch ( strVerticalAlignment )
	{
	case CyVerticalAlignmentBottom:
	case CyVerticalAlignmentCenter:
	case CyVerticalAlignmentTop:
		this->m_strVerticalAlignment = strVerticalAlignment;
		return true;
		break;
	default:
		return false;
		break;
	}
}

/* ---------------------------------------------------------------------------- */

bool CyValue::setForegroundColor ( const wchar_t& strForegroundColor )
{
	switch ( strForegroundColor )
	{
	case CyForegroundBlack:
	case CyForegroundBlue:
	case CyForegroundCyan:
	case CyForegroundGreen:
	case CyForegroundGrey:
	case CyForegroundRed:
	case CyForegroundWhite:
	case CyForegroundYellow:
		this->m_strForegroundColor = strForegroundColor;
		return true;
		break;
	default:
		return false;
		break;
	}
}

/* ---------------------------------------------------------------------------- */

bool CyValue::setBackgroundColor ( const wchar_t& strBackgroundColor )
{
	switch ( strBackgroundColor )
	{
	case CyBackgroundBlack:
	case CyBackgroundBlue:
	case CyBackgroundCyan:
	case CyBackgroundGreen:
	case CyBackgroundGrey:
	case CyBackgroundRed:
	case CyBackgroundWhite:
	case CyBackgroundYellow:
		this->m_strBackgroundColor = strBackgroundColor;
		return true;
		break;
	default:
		return false;
		break;
	}
}

/* ---------------------------------------------------------------------------- */

const wxString& CyValue::getStringFormat ( ) const
{
	return this->m_strStringFormat;
}

/* ---------------------------------------------------------------------------- */

void CyValue::setNotNull ( )
{
	this->m_bIsNull = false;
}

/* ---------------------------------------------------------------------------- */

void CyValue::setStringFormat ( const wxString& strStringFormat )
{
	if ( strStringFormat.empty ( ) )
	{
		return;
	}

	this->m_strStringFormat = strStringFormat;
	
	wxString::const_iterator strIterator;
	for (strIterator = strStringFormat.begin ( ) + 1; strIterator != strStringFormat.end ( ) ; ++ strIterator )
	{
		switch ( wchar_t ( *strIterator ) )
		{
		case CyFormatCurrency:
		case CyFormatInteger:
		case CyFormatReal:
		case CyFormatString:
		case CyFormatBoolean:
		case CyFormatHidden:
		case CyFormatDate:
			this->m_strValueType = wchar_t ( *strIterator );
			break;

		case CyFontBold:
			this->m_bFontBold = true;
			break;
		case CyFontItalic:
			this->m_bFontItalic = true;
			break;
		case CyFontUnderlined:
			this->m_bFontUnderlined = true;
			break;

		case CyForegroundBlue:
		case CyForegroundCyan:
		case CyForegroundGreen:
		case CyForegroundYellow:
		case CyForegroundRed:
		case CyForegroundBlack:
		case CyForegroundGrey:
		case CyForegroundWhite:
			this->m_strForegroundColor = wchar_t ( *strIterator );
			break;

		case CyBackgroundBlue:
		case CyBackgroundCyan:
		case CyBackgroundGreen:
		case CyBackgroundYellow:
		case CyBackgroundRed:
		case CyBackgroundBlack:
		case CyBackgroundGrey:
		case CyBackgroundWhite:
			this->m_strBackgroundColor = wchar_t ( *strIterator );
			break;

		case CyHorizontalAlignmentLeft:
		case CyHorizontalAlignmentRight:
		case CyHorizontalAlignmentCenter:
			this->m_strHorizontalAlignment = wchar_t ( *strIterator );
			break;

		case CyVerticalAlignmentBottom:
		case CyVerticalAlignmentTop:
		case CyVerticalAlignmentCenter:
			this->m_strVerticalAlignment = wchar_t ( *strIterator );
			break;
		}
	}
}

/* ---------------------------------------------------------------------------- */

bool CyValue::isFontBold ( ) const
{
	return this->m_bFontBold;
}

/* ---------------------------------------------------------------------------- */

bool CyValue::isFontItalic ( ) const
{
	return this->m_bFontItalic;
}

/* ---------------------------------------------------------------------------- */

bool CyValue::isFontUnderlined ( ) const
{
	return this->m_bFontUnderlined;
}

/* ---------------------------------------------------------------------------- */

