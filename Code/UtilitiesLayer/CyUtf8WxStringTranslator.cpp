/* ---------------------------------------------------------------------------- */
//! CyUtf8WxStringTranslator.cpp
/* ---------------------------------------------------------------------------- */
//!
//! \file CyUtf8WxStringTranslator.cpp
//! \brief fichier de définition de la classe CyUtf8WxStringTranslator
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

#include "UtilitiesLayer/CyUtf8WxStringTranslator.h"
#include "UtilitiesLayer/CyWxIncludes.h"

/* ---------------------------------------------------------------------------- */

CyUtf8WxStringTranslator::CyUtf8WxStringTranslator ( )
{
}

/* ---------------------------------------------------------------------------- */

CyUtf8WxStringTranslator::~CyUtf8WxStringTranslator (  )
{
}

/* ---------------------------------------------------------------------------- */

std::string CyUtf8WxStringTranslator::fromWxStringToUtf8 ( wxString strWxString ) const
{
	std::wstring strUnicode = strWxString.ToStdWstring ( );
	std::string strUtf8 = "";

	for ( std::wstring::const_iterator strIterator = strUnicode.begin ( ); strIterator != strUnicode.end ( ); ++ strIterator )
	{
		// 0x3F->63->111 111
		// 0x80->128->10 000 000
		// 0xC0->192->11 000 000
		// 0xE0->224->11 100 000
		// 0xF0->240->11 110 000
		// 2048->0x800->100 000 000 000
		// 65536->0x10000->10 000 000 000 000 000
		// 2097152->0x200000->1 000 000 000 000 000 000 000

		if ( *strIterator < 0x80 )
		{
			// 0xxxxxxx
			strUtf8 += static_cast< std::string::value_type > ( *strIterator );
		}
		else if ( *strIterator < 0x800 )
		{
			// 110xxxxx 10xxxxxx
			strUtf8.push_back ( static_cast< std::string::value_type > ( 0xC0 | ( ( *strIterator ) >> 6 ) ) );
			strUtf8.push_back ( static_cast< std::string::value_type > ( 0x80 | ( ( *strIterator ) & 0x3F ) ) );
		}
		else if ( *strIterator < 0x10000 )
		{
			// 1110xxxx 10xxxxxx 10xxxxxx
			strUtf8.push_back ( static_cast< std::string::value_type > ( 0xE0 | ( ( *strIterator ) >> 12 ) ) );
			strUtf8.push_back ( static_cast< std::string::value_type > ( 0x80 | ( ( ( *strIterator ) >> 6 ) & 0x3F ) ) );
			strUtf8.push_back ( static_cast< std::string::value_type > ( 0x80 | ( ( *strIterator ) & 0x3F ) ) );
		}
		else if ( *strIterator < 0x200000 )
		{
			// 11110xxx 10xxxxxx 10xxxxxx 10xxxxxx
#ifdef CY_COMPILER_GCC
			strUtf8.push_back ( static_cast< std::string::value_type > ( 0xF0 | ( ( *strIterator ) >> 18 ) ) );
#endif
#ifdef CY_COMPILER_VC10
#pragma warning ( push )
#pragma warning ( disable: 4333 )
			strUtf8.push_back ( static_cast< std::string::value_type > ( 0xF0 | ( ( static_cast< int > ( *strIterator ) ) >> 18 ) ) );
#pragma warning ( pop )
#endif
			strUtf8.push_back ( static_cast< std::string::value_type > ( 0x80 | ( ( ( *strIterator ) >> 12 ) & 0x3F ) ) );
			strUtf8.push_back ( static_cast< std::string::value_type > ( 0x80 | ( ( ( *strIterator ) >> 6 ) & 0x3F ) ) );
			strUtf8.push_back ( static_cast< std::string::value_type > ( 0x80 | ( ( *strIterator ) & 0x3F ) ) );
		}
	}

	return strUtf8;
}

/* ---------------------------------------------------------------------------- */

wxString CyUtf8WxStringTranslator::fromUtf8ToWxString ( std::string strUtf8 ) const
{
	std::wstring strUnicode = L"";

	for ( unsigned int uUtf8Counter = 0; uUtf8Counter < strUtf8.size ( ); )
	{
		wchar_t strUnicodeLetter = 0;

		if ( ( strUtf8 [ uUtf8Counter ] & 0xF0 ) == 0xF0 )
		{
			// 11110xxx 10xxxxxx 10xxxxxx 10xxxxxx
			strUnicodeLetter = static_cast< wchar_t > ( ( ( strUtf8 [ uUtf8Counter ] & 0x07 ) << 18 )
							   | ( ( strUtf8 [ uUtf8Counter + 1 ] & 0x3F ) << 12 )
							   | ( ( strUtf8 [ uUtf8Counter + 2 ] & 0x3F ) << 6 )
							   | ( strUtf8 [ uUtf8Counter + 3 ] & 0x3F ) );
			uUtf8Counter += 4;
		}
		else if ( ( strUtf8 [ uUtf8Counter ] & 0xE0 ) == 0xE0 )
		{
			// 1110xxxx 10xxxxxx 10xxxxxx
			strUnicodeLetter = static_cast< wchar_t > ( ( ( strUtf8 [ uUtf8Counter ] & 0x0F ) << 12 )
							   | ( ( strUtf8 [ uUtf8Counter + 1 ] & 0x3F ) << 6 )
							   | ( strUtf8 [ uUtf8Counter + 2 ] & 0x3F ) );
			uUtf8Counter += 3;
		}
		else if ( ( strUtf8 [ uUtf8Counter ] & 0xC0 ) == 0xC0 )
		{
			// 110xxxxx 10xxxxxx
			strUnicodeLetter = static_cast< wchar_t > ( ( ( strUtf8 [ uUtf8Counter ] & 0x1F ) << 6 )
							   | ( strUtf8 [ uUtf8Counter + 1 ] & 0x3F ) );
			uUtf8Counter += 2;
		}
		else if ( strUtf8 [ uUtf8Counter ] < 0x80 )
		{
			// 0xxxxxxx
			strUnicodeLetter = static_cast< wchar_t > ( strUtf8 [ uUtf8Counter ] );
			uUtf8Counter += 1;
		}

		strUnicode.push_back ( strUnicodeLetter );

	}

	wxString strTmp ( strUnicode );

	return strTmp;
}

/* ---------------------------------------------------------------------------- */