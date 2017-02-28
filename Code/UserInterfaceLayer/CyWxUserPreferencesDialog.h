/* ---------------------------------------------------------------------------- */
//! CyWxUserPreferencesDialog.h
/* ---------------------------------------------------------------------------- */
//!
//! \file CyWxUserPreferencesDialog.h
//! \brief header file for class CyWxUserPreferencesDialog
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

#include "UserInterfaceLayer/CyWxGeneralUserPreferencesPanel.h"
#include "UserInterfaceLayer/CyWxDisplayUserPreferencesPanel.h"
#include "UserInterfaceLayer/CyWxDatabaseUserPreferencesPanel.h"

/* ---------------------------------------------------------------------------- */

//! \class CyWxUserPreferencesDialog
//! \brief dialog box for the user preferences edition
//!
//! How to use this class:
//! - create an instance of the class
//! - launch the ShowModal ( ) method

class CyWxUserPreferencesDialog : public wxDialog
{

	public:

		//! fn CyWxUserPreferencesDialog ( wxWindow* pParent, const wxString& strTitle )
		//! @param [ in ] pParent the parent window
		//! @param [ in ] strTitle the title to be displayed on the title bar
		//!
		//! constructor

		CyWxUserPreferencesDialog ( wxWindow* pParent, const wxString& strTitle );

		//! \fn ~CyWxUserPreferencesDialog ( ) 
		//! destructor

		~CyWxUserPreferencesDialog ( );

		//! \enum DialogSizeAndPosition
		//! values for the dialog sizes and controls positions
		//!
		//! \var kDialogWidth
		//! the width of the dialog
		//!
		//! \var kDialogHeight
		//! the height of the dialog
		//!
		//! \var kPanelWidth
		//! the width of the panels
		//!
		//! \var kPanelHeight
		//! the height of the panels

		enum DialogSizeAndPosition
		{
			kDialogWidth = 650,
			kDialogHeight = 650,
			kPanelWidth = 600,
			kPanelHeight = 600
		};

		//! \fn ShowModal ( )
		//! overload of the wxWidget method ShowModal ( ).
		//! This method save the values given by the user when the OK button is used
		//!\return the code given by the base class method ShowModal ( )

		virtual int ShowModal ( );

	private:

		//! \fn CyWxUserPreferencesDialog ( const CyWxUserPreferencesDialog& ) 
		//! copy constructor
		//! not implemented

		CyWxUserPreferencesDialog ( const CyWxUserPreferencesDialog& );

		//! \fn operator = ( const CyWxUserPreferencesDialog& ) 
		//! operator =
		//! \return a reference to a CyWxUserPreferencesDialog object
		//! not implemented

		CyWxUserPreferencesDialog& operator = ( const CyWxUserPreferencesDialog& );

		//! \enum wxId
		//! values for the controls in the dialog box
		//!
		//! \var kNotebook
		//! id for the wxNotebook object
		//!
		//! \var kGeneralUserPreferencesPanel
		//! id for the General panel
		//!
		//! \var kDisplayUserPreferencesPanel
		//! id for the Display panel
		//!
		//! \var kDatabaseUserPreferencesPanel
		//! id for the Database panel
		//!

		enum wxId
		{
			kNotebook,
			kGeneralUserPreferencesPanel,
			kDisplayUserPreferencesPanel,
			kDatabaseUserPreferencesPanel
		};

		//! \var m_pNotebook
		//! the wxNotebook object

		wxNotebook* m_pNotebook;

		//! \var m_pGeneralUserPreferencesPanel
		//! the general preferences panel object

		CyWxGeneralUserPreferencesPanel* m_pGeneralUserPreferencesPanel;

		//! \var m_pDisplayUserPreferencesPanel
		//! the display preferences panel object

		CyWxDisplayUserPreferencesPanel* m_pDisplayUserPreferencesPanel;

		//! \var m_pDatabaseUserPreferencesPanel
		//! the database preferences panel object

		CyWxDatabaseUserPreferencesPanel* m_pDatabaseUserPreferencesPanel;

};

/* ---------------------------------------------------------------------------- */