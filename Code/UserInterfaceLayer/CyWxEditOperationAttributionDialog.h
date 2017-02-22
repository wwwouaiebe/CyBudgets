/* ---------------------------------------------------------------------------- */
//! CyWxEditOperationAttributionDialog.h
/* ---------------------------------------------------------------------------- */
//!
//! \file CyWxEditOperationAttributionDialog.h
//! \brief header file for class CyWxEditOperationAttributionDialog
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
#include "UserInterfaceLayer/CyWxTreeItemData.h"

/* ---------------------------------------------------------------------------- */

class CyWxEditOperationAttributionDialog : public wxDialog
{

//! \class CyWxEditOperationAttributionDialog
//! \brief dialog box for the attributions of an operation edition
//!
//! How to use this class:
//! - create an instance of the class, giving the attribution values to be edited in the currentRow parameter
//! - launch the ShowModal ( ) method
//! - use the get methods to retreive the values given by the user.

	public:

		//! \fn CyWxEditOperationAttributionDialog ( CyQueryResult::CyQueryResultValuesRow& currentRow, wxWindow* pParent, const wxString& strTitle ) 
		//! @param [ in ] currentRow a reference to a vector with the account informations to be edited
		//! @param [ in ] pParent the parent window
		//! @param [ in ] strTitle the title to be displayed on the title bar
		//!
		//! constructor

		CyWxEditOperationAttributionDialog ( CyQueryResult::CyQueryResultValuesRow& currentRow, wxWindow* pParent, const wxString& strTitle );

		//! \fn ~CyWxEditOperationAttributionDialog ( ) 
		//! destructor

		virtual ~CyWxEditOperationAttributionDialog ( );

		//! \fn ShowModal ( )
		//! overload of the wxWidget method ShowModal ( ).
		//! This method save the values given by the user when the OK button is used
		//!\return the code given by the base class method ShowModal ( )

		int ShowModal ( );

	private:
		//! \fn getAmount ( ) 
		//! get method
		//!
		//! \return the account number as it is in the amount text control

		const long long getAmount ( ) const;

		//! \fn getGroupDescription ( ) 
		//! get method
		//!
		//! \return the main description as it is in the attribution tree control

		const wxString getGroupDescription ( ) const;

		//! \fn getDescription ( ) 
		//! get method
		//!
		//! \return the description as it is in the attribution tree control

		const wxString getDescription ( ) const;

		//! \fn getAttributionObjId ( ) 
		//! get method
		//!
		//! \return tha attribution operation objid defined in the currentRow parameter of the constructor

		const long long getAttributionObjId ( ) const;

		//! \enum wxId
		//! values for the controls in the dialog box
		//!
		//! \var kAmount
		//! id for the amount edit box
		//!
		//! \var kAttribution
		//! id for the attribution tree control
		//!

		enum wxId
		{
			kAmount,
			kAttribution
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
		//! \var kTextWidth
		//! the width of the texts
		//!
		//! \var kTextHeight
		//! the height of the texts
		//!
		//! \var kControlWidth
		//! the width of the controls
		//!
		//! \var kControlHeight
		//! the height of the controls
		//!
		//! \var kTreeControlHeight
		//! the height of the tree control
		//!

		enum DialogSizeAndPosition
		{
			kDialogWidth = 650,
			kDialogHeight = 800,
			kTextWidth = 600,
			kTextHeight = 20,
			kControlWidth = 600,
			kControlHeight = 25,
			kTreeControlHeight = 400
		};

		//! \fn CyWxEditOperationAttributionDialog ( const CyWxEditOperationAttributionDialog& ) 
		//! copy constructor
		//! not implemented

		CyWxEditOperationAttributionDialog ( const CyWxEditOperationAttributionDialog& );

		//! \fn operator = ( const CyWxEditOperationAttributionDialog& ) 
		//! operator =
		//! \return a reference to a CyWxEditOperationAttributionDialog object
		//! not implemented

		CyWxEditOperationAttributionDialog& operator = ( const CyWxEditOperationAttributionDialog& );

		//! \fn onAttributionSelected ( wxTreeEvent& event  )
		//! event handler for the "selection changed in the attribution tree control" user action
		//! @param [ in ] event the event send by the wxWidget framework
		//! This method enable or disable the OK button, depending of the user choice

		void onAttributionSelected ( wxTreeEvent& event  );

		//! \var m_pAmountCtrl
		//! the amount edit box
		//!

		wxTextCtrl* m_pAmountCtrl;

		//! \var m_pAttributionCtrl
		//! the attribution tree control
		//!

		wxTreeCtrl* m_pAttributionCtrl;

		//! \var m_dAmount;
		//! the amount of the edited attribution
		//!

		double m_dAmount;

		//! \var m_pSelectedItemData;
		//! the item data corresponding to the selected item in the tree control
		//!

		CyWxTreeItemData* m_pSelectedItemData;

		//! \var m_currentRow
		//! the edited row

		CyQueryResult::CyQueryResultValuesRow& m_currentRow;

		//! \var m_objAttributionsQueryResult;
		//! a colllection of all the possible attributions
		//!

		CyQueryResult m_objAttributionsQueryResult;

};