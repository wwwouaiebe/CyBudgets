/* ---------------------------------------------------------------------------- */
//! CyWxDisplayUserPreferencesPanel.h
/* ---------------------------------------------------------------------------- */
//!
//! \file CyWxDisplayUserPreferencesPanel.h
//! \brief header file for class CyWxDisplayUserPreferencesPanel
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

//! \class CyWxDisplayUserPreferencesPanel
//! \brief control panel for the CyWxUserPreferencesDialog class
//!

class CyWxDisplayUserPreferencesPanel : public wxPanel
{

	friend class CyWxUserPreferencesDialog;

	public:

		//! fn CyWxDisplayUserPreferencesPanel ( wxWindow* pParent, int id,	const wxPoint& pos, const wxSize& size, long style, const wxString& name )
		//! @param [ in ] pParent the parent window
		//! @param [ in ] id the id of the panel
		//! @param [ in ] pos the position of the panel
		//! @param [ in ] size the size of the panel
		//! @param [ in ] style the style of the panel
		//! @param [ in ] name the name of the panel
		//!
		//! constructor

		CyWxDisplayUserPreferencesPanel (
			wxWindow* pParent,
			int id,
			const wxPoint& pos,
			const wxSize& size,
			long style,
			const wxString& name );

		//! \fn ~CyWxDisplayUserPreferencesPanel ( ) 
		//! destructor

		virtual ~CyWxDisplayUserPreferencesPanel ( );

	private:

		//! \fn CyWxDisplayUserPreferencesPanel ( const CyWxDisplayUserPreferencesPanel& ) 
		//! copy constructor
		//! not implemented

		CyWxDisplayUserPreferencesPanel ( const CyWxDisplayUserPreferencesPanel& );

		//! \fn operator = ( const CyWxDisplayUserPreferencesPanel& ) 
		//! operator =
		//! \return a reference to a CyWxDisplayUserPreferencesPanel object
		//! not implemented

		CyWxDisplayUserPreferencesPanel& operator = ( const CyWxDisplayUserPreferencesPanel& );

		//! \enum wxId
		//! values for the controls in the dialog box
		//!
		//! \var kBooleanTrue
		//! id for the boolean true control
		//!
		//! \var kBooleanFalse
		//! id for the boolean false control
		//!
		//! \var kCurrencyPositiveSymbol
		//! id for the currency positive symbol control
		//!
		//! \var kCurrencyNegativeSymbol
		//! id for the currency negative symbol control
		//!
		//! \var kCurrencyPositiveColor
		//! id for the currency positive color control
		//!
		//! \var kCurrencyNegativeColor
		//! id for the currency negative color control
		//!
		//! \var kCurrencySymbolPosition
		//! id for the currency symbol podition control
		//!
		//! \var kDecimalSeparator
		//! id for the decimal separator control
		//!
		//! \var kThousandSeparator
		//! id for the thousand separator control
		//!
		//! \var kGrouping
		//! id for the grouping control

		enum wxId
		{
			kBooleanTrue,
			kBooleanFalse,
			kCurrencyPositiveSymbol,
			kCurrencyNegativeSymbol,
			kCurrencyPositiveColor,
			kCurrencyNegativeColor,
			kCurrencySymbolPosition,
			kDecimalSeparator,
			kThousandSeparator,
			kGrouping
		};

		//! \enum DialogSizeAndPosition
		//! values for the dialog sizes and controls positions
		//!
		//! \var kTextGridWidth
		//! the width of the text in the gridbag
		//!
		//! \var kTextGridHeight
		//! the height of the text in the gridbag
		//!
		//! \var kControlGridWidth
		//! the width of the control in the gridbag
		//!
		//! \var kControlGridHeight
		//! the height of the control in the gridbag
		//!
		//! \var kSpinControlGridWidth
		//! the width of the spin control in the gridbag
		//!

		enum DialogSizeAndPosition
		{
			kTextGridWidth = 300,
			kTextGridHeight = 20,
			kControlGridWidth = 300,
			kControlGridHeight = 25,
			kSpinControlGridWidth = 40
		};

		//! \var m_pBooleanFalseSymbolCtrl
		//! the boolean false symbol edit box

		wxTextCtrl* m_pBooleanFalseSymbolCtrl;

		//! \var m_strBooleanFalseSymbol
		//! the boolean false symbol

		wxString m_strBooleanFalseSymbol;
		
		//! \var m_pBooleanTrueSymbolCtrl
		//! the boolean true symbol edit box

		wxTextCtrl* m_pBooleanTrueSymbolCtrl;

		//! \var m_strBooleanTrueSymbol
		//! the boolean true symbol

		wxString m_strBooleanTrueSymbol;

		//! \var m_pCurrencyPositiveSymbolCtrl
		//! the currency positive symbol edit box

		wxTextCtrl* m_pCurrencyPositiveSymbolCtrl;

		//! \var m_strCurrencyPositiveSymbol
		//! the currency positive symbol

		wxString m_strCurrencyPositiveSymbol;

		//! \var m_pCurrencyPositiveColorComboBox
		//! the currency positive color combo box

		wxComboBox* m_pCurrencyPositiveColorComboBox;

		//! \var m_strCurrencyPositiveColor
		//! the currency positive color

		wchar_t m_strCurrencyPositiveColor;

		//! \var m_pCurrencyNegativeSymbolCtrl
		//! the currency negative symbol edit box

		wxTextCtrl* m_pCurrencyNegativeSymbolCtrl;

		//! \var m_strCurrencyNegativeSymbol
		//! the currency negative symbol

		wxString m_strCurrencyNegativeSymbol;

		//! \var m_pCurrencyNegativeColorComboBox
		//! the currency negative color combo box

		wxComboBox* m_pCurrencyNegativeColorComboBox;

		//! \var m_strCurrencyNegativeColor
		//! the currency negative color

		wchar_t m_strCurrencyNegativeColor;

		//! \var m_pDecimalSeparatorCtrl
		//! the decimal separator edit box

		wxTextCtrl* m_pDecimalSeparatorCtrl;

		//! \var m_strDecimalSeparator
		//! the decimal separator

		wxString m_strDecimalSeparator;

		//! \var m_pThousandSeparatorCtrl
		//! the thousand separator edit box

		wxTextCtrl* m_pThousandSeparatorCtrl;

		//! \var m_strThousandSeparator
		//! the thousand separator

		wxString m_strThousandSeparator;

		//! \var m_pGroupingSpinCtrl
		//! the grouping spin control

		wxSpinCtrl* m_pGroupingSpinCtrl;

		//! \var m_lGrouping
		//! the grouping

		long long m_lGrouping;

		//! \var m_pCurrencySymbolPositionComboBox
		//! the currency symbol position combo box

		wxComboBox* m_pCurrencySymbolPositionComboBox;

		//! \var m_bCurrencySymbolBefore
		//! the currency symbol position

		bool m_bCurrencySymbolBefore;
};
/* ---------------------------------------------------------------------------- */

