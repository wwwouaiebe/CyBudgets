/* ---------------------------------------------------------------------------- */
//! CyWxGeneralUserPreferencesPanel.h
/* ---------------------------------------------------------------------------- */
//!
//! \file CyWxGeneralUserPreferencesPanel.h
//! \brief header file for class CyWxGeneralUserPreferencesPanel
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

//! \class CyWxGeneralUserPreferencesPanel
//! \brief control panel for the CyWxUserPreferencesDialog class
//!

class CyWxGeneralUserPreferencesPanel : public wxPanel
{

	friend class CyWxUserPreferencesDialog;

	public:

		//! fn CyWxGeneralUserPreferencesPanel ( wxWindow* pParent, int id,	const wxPoint& pos, const wxSize& size, long style, const wxString& name )
		//! @param [ in ] pParent the parent window
		//! @param [ in ] id the id of the panel
		//! @param [ in ] pos the position of the panel
		//! @param [ in ] size the size of the panel
		//! @param [ in ] style the style of the panel
		//! @param [ in ] name the name of the panel
		//!
		//! constructor

		CyWxGeneralUserPreferencesPanel (
			wxWindow* pParent,
			int id,
			const wxPoint& pos,
			const wxSize& size,
			long style,
			const wxString& name );

		//! \fn ~CyWxGeneralUserPreferencesPanel ( ) 
		//! destructor

		virtual ~CyWxGeneralUserPreferencesPanel ( );

	private:

		//! \fn CyWxGeneralUserPreferencesPanel ( const CyWxGeneralUserPreferencesPanel& ) 
		//! copy constructor
		//! not implemented

		CyWxGeneralUserPreferencesPanel ( const CyWxGeneralUserPreferencesPanel& );

		//! \fn operator = ( const CyWxGeneralUserPreferencesPanel& ) 
		//! operator =
		//! \return a reference to a CyWxGeneralUserPreferencesPanel object
		//! not implemented

		CyWxGeneralUserPreferencesPanel& operator = ( const CyWxGeneralUserPreferencesPanel& );

		//! \enum wxId
		//! values for the controls in the dialog box
		//!
		//! \var kUserLanguage
		//! id for the user language control
		//!
		//! \var kReuseLastOpenedFile
		//! id for the reuse last opened file check box
		//!

		enum wxId
		{
			kUserLanguage,
			kReuseLastOpenedFile
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

		enum DialogSizeAndPosition
		{
			kTextGridWidth = 300,
			kTextGridHeight = 20,
			kControlGridWidth = 300,
			kControlGridHeight = 25
		};

		//! \var m_pUserLanguageComboBox
		//! the user language combo box

		wxComboBox* m_pUserLanguageComboBox;

		//! \var m_strUserLanguage
		//! the user language

		wxString m_strUserLanguage;

		//! \var m_pReuseLastOpenedFileCheckbox
		//! the reuse last opened file check box

		wxCheckBox* m_pReuseLastOpenedFileCheckbox;

		//! \var m_bReuseLastOpenedFile
		//! the reuse last opened file flag

		bool m_bReuseLastOpenedFile;

};

/* ---------------------------------------------------------------------------- */