/* ---------------------------------------------------------------------------- */
//! CyWxEditAccountDialog.h
/* ---------------------------------------------------------------------------- */
//!
//! \file CyWxEditAccountDialog.h
//! \brief header file for class CyWxEditAccountDialog
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
#include "UtilitiesLayer/CyEnum.h"
#include "UtilitiesLayer/CyWxIncludes.h"

/* ---------------------------------------------------------------------------- */

//! \class CyWxEditAccountDialog
//! \brief dialog box for the account edition
//!
//! How to use this class:
//! - create an instance of the class, giving the account values to be edited in the currentRow parameter
//! - launch the ShowModal ( ) method
//! - use the get methods to retreive the values given by the user.

class CyWxEditAccountDialog : public wxDialog
{

	public:

		//! \fn CyWxEditAccountDialog ( CyQueryResult::CyQueryResultValuesRow& currentRow, wxWindow* pParent, const wxString& strTitle ) 
		//! @param [ in ] currentRow a reference to a vector with the account informations to be edited
		//! @param [ in ] pParent the parent window
		//! @param [ in ] strTitle the title to be displayed on the title bar
		//!
		//! constructor

		CyWxEditAccountDialog ( CyQueryResult::CyQueryResultValuesRow& currentRow, wxWindow* pParent, const wxString& strTitle );

		//! \fn ~CyWxEditAccountDialog ( ) 
		//! destructor

		virtual ~CyWxEditAccountDialog ( );

		//! \fn ShowModal ( )
		//! overload of the wxWidget method ShowModal ( ).
		//! This method save the values given by the user when the OK button is used
		//!\return the code given by the base class method ShowModal ( )

		virtual int ShowModal ( );

	private:

		//! \enum wxId
		//! values for the controls in the dialog box
		//!
		//! \var kAccountNumber
		//! id for the account number edit box
		//!
		//! \var kAccountOwner
		//! id for the account owner edit box
		//!
		//! \var kAccountCanBeImported
		//! id for the account can be imported combo box
		//!

		enum wxId
		{
			kAccountNumber,
			kAccountOwner,
			kAccountCanBeImported,
			kAccountValidSinceDate,
			kAccountInitialAmount
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
			kTextGridWidth = 300,
			kTextGridHeight = 20,
			kControlGridWidth = 300,
			kControlGridHeight = 25
		};

		//! \fn CyWxEditAccountDialog ( const CyWxEditAccountDialog& ) 
		//! copy constructor
		//! not implemented

		CyWxEditAccountDialog ( const CyWxEditAccountDialog& );

		//! \fn operator = ( const CyWxEditAccountDialog& ) 
		//! operator =
		//! \return a reference to a CyWxEditAccountDialog object
		//! not implemented

		CyWxEditAccountDialog& operator = ( const CyWxEditAccountDialog& );

		//! \fn getAccountNumber ( ) 
		//! get method
		//!
		//! \return the account number as it is in the account number text control

		const wxString getAccountNumber ( ) const;

		//! \fn getAccountOwner ( ) 
		//! get method
		//!
		//! \return the account owner as it is in the account owner text control

		const wxString getAccountOwner ( ) const;

		//! \fn getAccountCanBeImported ( ) 
		//! get method
		//!
		//! \return the value of the CanBeImported field. 

		const CyEnum::AccountCanBeImported getAccountCanBeImported ( ) const;

		//! \fn getAccountObjId ( ) 
		//! get method
		//!
		//! \return the account objid defined in the currentRow parameter of the constructor

		const long long& getAccountObjId ( ) const;

		//! \fn getAccountValidSinceDate ( ) 
		//! get method
		//!
		//! \return the value of the valid since date field

		const wxString getAccountValidSinceDate ( ) const;

		//! \fn getAccountInitialAmount ( ) 
		//! get method
		//!
		//! \return the value of account initial amount field

		const long long getAccountInitialAmount ( ) const;

		//! \var m_pAccountNumberCtrl
		//! the account number edit box
		//!

		wxTextCtrl* m_pAccountNumberCtrl;

		//! \var m_pAccountOwnerCtrl
		//! the account owner edit box
		//!

		wxTextCtrl* m_pAccountOwnerCtrl;

		//! \var m_pAccountCanBeImportedComboBox
		//! the "account can be imported" combo box
		//!

		wxComboBox* m_pAccountCanBeImportedComboBox;

		//! \var m_pAccountValidSinceDateCtrl
		//! the account valid since date picker control

		wxDatePickerCtrl* m_pAccountValidSinceDateCtrl;

		//! \var m_pAccountInitialAmountCtrl
		//! the account initial amount edit box

		wxTextCtrl* m_pAccountInitialAmountCtrl;

		//! \var m_lAccountObjId
		//! the  objid of the edited account
		//!
		long long m_lAccountObjId;

		//! \var m_lAccountCanBeImported
		//! the  "Account can be edited" of the edited account
		//!

		long long m_lAccountCanBeImported;

		//! \var m_strAccountNumber
		//! the  number of the edited account
		//!

		wxString m_strAccountNumber;

		//! \var m_strAccountOwner
		//! the  owner of the edited account
		//!

		wxString m_strAccountOwner;

		//! \var m_dAccountInitialAmount
		//! the initial amount of the edited account

		double m_dAccountInitialAmount;

		//! \var m_currentRow
		//! the edited row

		CyQueryResult::CyQueryResultValuesRow& m_currentRow;
};