/* ---------------------------------------------------------------------------- */
//! CyWxEditAttributionDialog.h
/* ---------------------------------------------------------------------------- */
//!
//! \file CyWxEditAttributionDialog.h
//! \brief header file for class CyWxEditAttributionDialog
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

#include "DataLayer/CyQueryResult.h"
#include "UtilitiesLayer/CyWxIncludes.h"

/* ---------------------------------------------------------------------------- */

//! \class CyWxEditAttributionDialog
//! \brief dialog box for the attribution edition
//!
//! How to use this class:
//! - create an instance of the class, giving the attribution values to be edited in the currentRow parameter
//! - launch the ShowModal ( ) method
//! - use the get methods to retreive the values given by the user.

class CyWxEditAttributionDialog : public wxDialog
{

	public:

		//! \fn CyWxEditAttributionDialog ( CyQueryResult::CyQueryResultValuesRow& currentRow, wxWindow* pParent, const wxString& strTitle ) 
		//! @param [ in ] currentRow a reference to a vector with the attribution informations to be edited
		//! @param [ in ] pParent the parent window
		//! @param [ in ] strTitle the title to be displayed on the title bar
		//!
		//! constructor

		CyWxEditAttributionDialog ( CyQueryResult::CyQueryResultValuesRow& currentRow, wxWindow* pParent, const wxString& strTitle );

		//! \fn ~CyWxEditAttributionDialog ( ) 
		//! destructor

		virtual ~CyWxEditAttributionDialog ( );

		//! \fn ShowModal ( )
		//! overload of the wxWidget method ShowModal ( ).
		//! This method save the values given by the user when the OK button is used
		//!\return the code given by the base class method ShowModal ( )

		virtual int ShowModal ( );

	private:

		//! \fn getAttributionGroupDescription ( ) 
		//! get method
		//!
		//! \return the attribution group description as it is in the group description combo box

		const wxString getAttributionGroupDescription ( ) const;

		//! \fn getAttributionDescription ( ) 
		//! get method
		//!
		//! \return the attribution description as it is in the main description text control
		
		const wxString getAttributionDescription ( ) const;

		//! \fn getAttributionGroupObjId ( ) 
		//! get method
		//!
		//! \return the group objid linked to the group selected by the user

		const long long getAttributionGroupObjId ( ) const;

		//! \fn getAttributionBudgetDescription ( ) 
		//! get method
		//!
		//! \return the attribution budget as it is in the attribution budget combo box

		const wxString getAttributionBudgetDescription ( ) const;

		//! \fn getAttributionBudgetObjId ( ) 
		//! get method
		//!
		//! \return the budget objid linked to the budget selected by the user

		const long long getAttributionBudgetObjId ( ) const;

		//! \enum wxId
		//! values for the controls in the dialog box
		//!
		//! \var kAttributionGroupDescription
		//! id for the main description combo box
		//!
		//! \var kAttributionDescription
		//! id for the description edit box
		//!
		//! \var kBudgetDescription
		//! id for the budget combo box
		//!

		enum wxId
		{
			kAttributionGroupDescription,
			kAttributionDescription,
			kBudgetDescription
		};

		//! \enum DialogSizeAndPosition
		//! values for the dialog sizes and controls positions
		//!
		//! \var kDialogWidth
		//! the width of the dialog
		//!
		//! \var kDialogHeight
		//! the height of the dialog
		//!
		//! \var kTextGridWidth
		//! the width of the texts in the grid
		//!
		//! \var kTextGridHeight
		//! the height of the texts in the grid
		//!
		//! \var kControlGridWidth
		//! the width of the controls in the grid
		//!
		//! \var kControlGridHeight
		//! the height of the controls in the grid
		//!

		enum DialogSizeAndPosition
		{
			kDialogWidth = 650,
			kDialogHeight = 250,
			kTextGridWidth = 150,
			kTextGridHeight = 20,
			kControlGridWidth = 300,
			kControlGridHeight = 25
		};

		//! \fn CyWxEditAttributionDialog ( const CyWxEditAttributionDialog& ) 
		//! copy constructor
		//! not implemented

		CyWxEditAttributionDialog ( const CyWxEditAttributionDialog& );

		//! \fn operator = ( const CyWxEditAttributionDialog& ) 
		//! operator =
		//! \return a reference to a CyWxEditAttributionDialog object
		//! not implemented

		CyWxEditAttributionDialog& operator = ( const CyWxEditAttributionDialog& );

		//! \var m_pAttributionGroupDescriptionComboBox
		//! the attribution group description combo box
		//!

		wxComboBox* m_pAttributionGroupDescriptionComboBox;

		//! \var m_pAttributionDescriptionCtrl
		//! the attribution description edit box
		//!

		wxTextCtrl* m_pAttributionDescriptionCtrl;

		//! \var m_pBudgetComboBox
		//! the attribution budget combo box
		//!

		wxComboBox* m_pBudgetComboBox;

		//! \var m_currentRow
		//! the edited row

		CyQueryResult::CyQueryResultValuesRow& m_currentRow;
};