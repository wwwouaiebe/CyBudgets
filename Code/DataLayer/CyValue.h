/* ---------------------------------------------------------------------------- */
//! CyValue.h
/* ---------------------------------------------------------------------------- */
//!
//! \file CyValue.h
//! \brief header file for class CyValue
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

//! \class CyValue
//! \brief virtual base class for classes CyStringValue and CyLongValue
//!
//! This class is used to do the data exchange betwwen the database and the user interface
//!
//! \version 1.0.3
//! Added formats. Formats are used to display values in wxGrid objects with a different presentation than
//! the standard presentation
//!
//! How to use formats:
//!	- A format is a value of wxString type 
//!	- A format is added when using the set method. When a format is not given, the previous value is used.
//!	- Characters used for the format string:
//!		- Mandatory first character : ➻ ( or the macro CyStartFormat )
//!	- Characters used for the horizontal alignment :
//!		- horizontal alignment left : ← ( or the macro CyHorizontalAlignmentLeft )
//!		- horizontal alignment right : → ( or the macro CyHorizontalAlignmentRight )
//!		- horizontal alignment center : ↔ ( or the macro CyHorizontalAlignmentCenter )
//!	- Vertical alignment :
//!		- vertical alignment top : ↑ ( or the macro CyVerticalAlignmentTop )
//!		- vertical alignment bottom : ↓ ( or the macro CyVerticalAlignmentBottom )
//!		- vertical alignment center : ↕ ( or the macro CyVerticalAlignmentCenter )
//!	- Characters used for the  value type :
//!		- currency : € ( or the macro CyFormatCurrency )
//!		- integer : ℤ ( or the macro CyFormatInteger )
//!		- real : ℝ ( or the macro CyFormatReal )
//!		- boolean : ✓ ( or the macro CyFormatBoolean )
//!		- string : α ( or the macro CyFormatString )
//!		- date : ≋ ( or the macro CyFormatDate )
//!		- hidden: ∅ ( or the macro CyFormatHidden )
//!	- Characters used for the foreground color :
//!		- foreground blue : ➀ ( or the macro CyForegroundBlue )
//!		- foreground cyan : ➁ ( or the macro CyForegroundCyan )
//!		- foreground green : ➂ ( or the macro CyForegroundGreen )
//!		- foreground yellow : ➃ ( or the macro CyForegroundYellow )
//!		- foreground red : ➄ ( or the macro CyForegroundRed )
//!		- foreground black : ➅ ( or the macro CyForegroundBlack )
//!		- foreground grey : ➆ ( or the macro CyForegroundGrey )
//!		- foreground white : ➇ ( or the macro CyForegroundWhite )
//!	- Characters used for the background color
//!		- background blue : ➊ ( or the macro CyBackgroundBlue )
//!		- background cyan : ➋ ( or the macro CyBackgroundCyan )
//!		- background green : ➌ ( or the macro CyBackgroundGreen )
//!		- background yellow : ➍ ( or the macro CyBackgroundYellow )
//!		- background red : ➎ ( or the macro CyBackgroundRed )
//!		- background black : ➏ ( or the macro CyBackgroundBlack )
//!		- background grey : ➐ ( or the macro CyBackgroundGrey )
//!		- background white : ➑ ( or the macro CyBackgroundWhite )
//!	- Characters used for the fonts:
//!		- font bold : ∎ ( or the macro CyFontBold )
//!		- font italic : ∕ ( or the macro CyFontItalic )
//!		- font underlined : ∸ ( or the macro CyFontUnderlined )
//!

class CyValue
{

	public:

		//! \fn CyValue ( ) 
		//! constructor

		CyValue ( );

		//! \fn ~CyValue ( ) 
		//! destructor

		virtual ~CyValue ( );

		//! \fn isNull ( ) 
		//! \return true when no value is assigned to the object

		bool isNull ( ) const;

		//! \fn getAsString ( )
		//! \return the valuse stored as a wxString

		virtual wxString getAsString ( ) const = 0;

		//! \fn get (  wxString strValue ) const
		//! get method
		//! @param [ in ] strValue a wxString used to force the compilator to select the correct virtual method. See also CyStringValue::m_strDummyValue
		//! \return the value stored in the object

		virtual const wxString& get ( wxString strValue ) const = 0;

		//! \fn get ( long long lValue ) const
		//! get method
		//! @param [ in ] lValue a long long used to force the compilator to select the correct virtual method. See also  CyLongValue::m_lDummyValue
		//! \return the value stored in the object

		virtual const long long & get ( long long lValue ) const = 0;

		//! \fn set ( const long long& lValue, const wxString& strStringFormat )
		//! set method
		//! @param [ in ] lValue a double reference to be stored in the object
		//! @param [ in ] strStringFormat a wxString reference with the format to use

		virtual void set ( const long long& lValue, const wxString& strStringFormat = wxEmptyString ) = 0;
	
		//! \fn set ( const wxString& strValue,  const wxString& strStringFormat )
		//! set method
		//! @param [ in ] strValue a wxString reference to be stored in the object
		//! @param [ in ] strStringFormat a wxString reference with the format to use

		virtual void set ( const wxString& strValue,  const wxString& strStringFormat  = wxEmptyString ) = 0;

		//! \fn getHorizontalAlignment ( ) const
		//! get method
		//! \return the character used for the horizontal alignment

		const wchar_t& getHorizontalAlignment ( ) const;

		//! \fn getVerticalAlignment ( ) const
		//! get method
		//! \return the character used for the vertical alignment

		const wchar_t& getVerticalAlignment ( ) const;

		//! \fn getForegroundColor ( ) const
		//! get method
		//! \return the character used for the foreground color

		const wchar_t& getForegroundColor ( ) const;

		//! \fn getBackgroundColor ( ) const
		//! get method
		//! \return the character used for the background color

		const wchar_t& getBackgroundColor ( ) const;

		//! \fn getValueType ( ) const
		//! get method
		//! \return the character used for the value type

		const wchar_t& getValueType ( ) const;

		//! \fn isFontBold ( ) const
		//! get method
		//! \return true when a bold font must be used

		bool isFontBold ( ) const;

		//! \fn isFontItalic ( ) const
		//! get method
		//! \return true when an italic font must be used

		bool isFontItalic ( ) const;

		//! \fn isFontUnderlined ( ) const
		//! get method
		//! \return true when an underlined font must be used

		bool isFontUnderlined ( ) const;

	protected:

		//! \fn setValueType ( const wchar_t& strValueType )
		//! This method set the value type
		//! @param [ in ] strValueType a wchar_t value to use as value type
		//! (must be CyFormatBoolean, CyFormatCurrency CyFormatDate, CyFormatHidde, CyFormatInteger, CyFormatReal or CyFormatString )
		//! \return true when the given parameter is a valid value type

		bool setValueType ( const wchar_t& strValueFormat );

		//! \fn setHorizontalAlignment ( const wchar_t& strHorizontalAlignment )
		//! This method set the horizontal alignment
		//! @param [ in ] strHorizontalAlignment a wchar_t value to use as horizontal alignment
		//! (must be CyHorizontalAlignmentCenter, CyHorizontalAlignmentLeft or CyHorizontalAlignmentRight )
		//! \return true when the given parameter is a valid horizontal alignment

		bool setHorizontalAlignment ( const wchar_t& strHorizontalAlignment );

		//! \fn setVerticalAlignment ( const wchar_t& strVerticalAlignment )
		//! This method set the vertical alignment
		//! @param [ in ] strVerticalAlignment a wchar_t value to use as vertical alignment
		//! (must be CyVerticalAlignmentBottom, CyVerticalAlignmentCenter or CyVerticalAlignmentTop )
		//! \return true when the given parameter is a valid vertical alignment

		bool setVerticalAlignment ( const wchar_t& strVerticalAlignment );

		//! \fn setForegroundColor ( const wchar_t& strForegroundColor )
		//! This method set the foreground color
		//! @param [ in ] strForegroundColor a wchar_t value to use as foreground color
		//! (must be CyForegroundBlack, CyForegroundBlue, CyForegroundCyan, CyForegroundGreen, CyForegroundGrey, CyForegroundRed, CyForegroundWhite or CyForegroundYellow )
		//! \return true when the given parameter is a valid foreground color

		bool setForegroundColor ( const wchar_t& strForegroundColor );

		//! \fn setBackgroundColor ( const wchar_t& strBackgroundColor )
		//! This method set the background color
		//! @param [ in ] strBackgroundColor a wchar_t value to use as background color
		//! (must be CyBackgroundBlack, CyBackgroundBlue, CyBackgroundCyan, CyBackgroundGreen, CyBackgroundGrey, CyBackgroundRed, CyBackgroundWhite or CyBackgroundYellow )
		//! \return true when the given parameter is a valid background color

		bool setBackgroundColor ( const wchar_t& strBackgroundColor );

		//! \fn setStringFormat ( const wxString& strFormat )
		//! This method set the format
		//! @param [ in ] strFormat a string with the format

		void setStringFormat ( const wxString& strFormat );

		//! \fn getStringFormat ( ) const
		//! get method
		//! \return the string ised for the format

		const wxString& getStringFormat ( ) const;

		//! \fn setNotNull ( )
		//! This method set the object to a not null value

		void setNotNull ( );

	private:

		//! \fn CyValue ( const CyValue& ) 
		//! copy constructor
		//! not implemented

		CyValue ( const CyValue& );

		//! \fn operator = ( const CyValue& ) 
		//! operator =
		//! \return a reference to a CyValue object
		//! not implemented

		CyValue& operator = ( const CyValue& );

		//! \var m_strStringFormat
		//! the string used for the format

		wxString m_strStringFormat;

		//! \var m_strValueType
		//! the character used for the value type

		wchar_t m_strValueType;

		//! \var m_strHorizontalAlignment
		//! the character used for the horizontal alignment

		wchar_t m_strHorizontalAlignment;

		//! \var m_strVerticalAlignment
		//! the character used for the vertical alignment

		wchar_t m_strVerticalAlignment;

		//! \var m_strForegroundColor
		//! the character used for the foreground color

		wchar_t m_strForegroundColor;

		//! \var m_strBackgroundColor
		//! the character used for the background color

		wchar_t m_strBackgroundColor;

		//! \var m_bFontBold
		//! true when the font is bold

		bool m_bFontBold;

		//! \var m_bFontItalic
		//! true when the font is italic

		bool m_bFontItalic;

		//! \var m_bFontUnderlined
		//! true when the font is underlined

		bool m_bFontUnderlined;

		//! \var m_bIsNull
		//! true when no value is assigned to the object

		bool m_bIsNull;
};