/* ---------------------------------------------------------------------------- */
//! CyWxDatabaseUserPreferencesPanel.h
/* ---------------------------------------------------------------------------- */
//!
//! \file CyWxDatabaseUserPreferencesPanel.h
//! \brief header file for class CyWxDatabaseUserPreferencesPanel
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

//! \class CyWxDatabaseUserPreferencesPanel
//! \brief control panel for the CyWxUserPreferencesDialog class
//!

class CyWxDatabaseUserPreferencesPanel : public wxPanel
{

	friend class CyWxUserPreferencesDialog;

	public:

		//! fn CyWxDatabaseUserPreferencesPanel ( wxWindow* pParent, int id,	const wxPoint& pos, const wxSize& size, long style, const wxString& name )
		//! @param [ in ] pParent the parent window
		//! @param [ in ] id the id of the panel
		//! @param [ in ] pos the position of the panel
		//! @param [ in ] size the size of the panel
		//! @param [ in ] style the style of the panel
		//! @param [ in ] name the name of the panel
		//!
		//! constructor

		CyWxDatabaseUserPreferencesPanel (
			wxWindow* pParent,
			int id,
			const wxPoint& pos,
			const wxSize& size,
			long style,
			const wxString& name );

		//! \fn ~CyWxDatabaseUserPreferencesPanel ( ) 
		//! destructor

		virtual ~CyWxDatabaseUserPreferencesPanel ( );

	private:

		//! \fn CyWxDatabaseUserPreferencesPanel ( const CyWxDatabaseUserPreferencesPanel& ) 
		//! copy constructor
		//! not implemented

		CyWxDatabaseUserPreferencesPanel ( const CyWxDatabaseUserPreferencesPanel& );

		//! \fn operator = ( const CyWxDatabaseUserPreferencesPanel& ) 
		//! operator =
		//! \return a reference to a CyWxDatabaseUserPreferencesPanel object
		//! not implemented

		CyWxDatabaseUserPreferencesPanel& operator = ( const CyWxDatabaseUserPreferencesPanel& );

		//! \enum wxId
		//! values for the controls in the dialog box
		//!
		//! \var kCurrencySymbol
		//! id for the currency symbol control
		//
		//! \var kDbDecimalPrecistion
		//! id for the decimal precision control
		//

		enum wxId
		{
			kCurrencySymbol,
			kDbDecimalPrecistion,
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

		//! \var m_pDbCurrencySymbolCtrl
		//! the currency symbol edit box

		wxTextCtrl* m_pDbCurrencySymbolCtrl;

		//! \var m_strDbCurrencySymbol
		//! the currency symbol

		wxString m_strDbCurrencySymbol;

		//! \var m_pDbCurrencyDecimalPrecisionSpinCtrl
		//! the decimal precision spin control

		wxSpinCtrl* m_pDbCurrencyDecimalPrecisionSpinCtrl;

		//! \var m_lDbCurrencyDecimalPrecision
		//! the currency decimal precision 

		long long m_lDbCurrencyDecimalPrecision;
		

};
/* ---------------------------------------------------------------------------- */

