/* ---------------------------------------------------------------------------- */
//! CyWxEditOperationDialog.h
/* ---------------------------------------------------------------------------- */
//!
//! \file CyWxEditOperationDialog.h
//! \brief header file for class CyWxEditOperationDialog
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

class CyOperationsSqlManager;
class CyOperationsAttributionsSqlBuilder;
class CyOperationsDetailsSqlBuilder;

/* ---------------------------------------------------------------------------- */

//! \class CyWxEditOperationDialog
//! \brief dialog box for the operation edition
//!
//! How to use this class:
//! - create an instance of the class, giving the account values to be edited in the currentRow parameter
//! - launch the ShowModal ( ) method
//! - use the get methods to retreive the values given by the user.

class CyWxEditOperationDialog : public wxDialog
{

	public:

		//! \fn CyWxEditOperationDialog (CyOperationsSqlManager* pOperationsSqlManager, wxWindow* pParent, const wxString& strTitle ) 
		//! @param [ in ] pOperationsSqlManager a pointer to a CyOperationsSqlManager object
		//! @param [ in ] pParent the parent window
		//! @param [ in ] strTitle the title to be displayed on the title bar
		//!
		//! constructor

		CyWxEditOperationDialog ( 
			CyOperationsSqlManager* pOperationsSqlManager,
			wxWindow* pParent, 
			const wxString& strTitle );

		//! \fn ~CyWxEditOperationDialog ( ) 
		//! destructor

		virtual ~CyWxEditOperationDialog ( );

		//! \fn ShowModal ( )
		//! overload of the wxWidget method ShowModal ( ).
		//! This method save the values given by the user when the OK button is used
		//!\return the code given by the base class method ShowModal ( )

		int ShowModal ( );

	private:

		//! \enum wxId
		//! values for the controls in the dialog box
		//!
		//! \var kOperationDate
		//! id for the operation date picker
		//!
		//! \var kValueDate
		//! id for the value date picker
		//!
		//! \var kBudgetDate
		//! id for the budget date picker
		//!
		//! \var kAmount
		//! id for the amount edit box
		//!
		//! \var kDetails
		//! id for the details edit box
		//!
		//! \var kDescription
		//! id for the description edit box
		//!
		//! \var kEditAttribution
		//! id for the Edit item of the popup menu of the attribution grid
		//!
		//! \var kAddAttribution
		//! id for the Add item of the popup menu of the attribution grid
		//!
		//! \var kDeleteAttribution
		//! id for the Delete item of the popup menu of the attribution grid
		//!

		enum wxId
		{
			kOperationDate,
			kValueDate,
			kBudgetDate,
			kAmount,
			kDetails,
			kDescription,
			kEditAttribution,
			kAddAttribution,
			kDeleteAttribution
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
		//! the width of the text in the gridbag
		//!
		//! \var kTextHeight
		//! the height of the text in the gridbag
		//!
		//! \var kControlGridWidth
		//! the width of the control in the gridbag
		//!
		//! \var kControlGridHeight
		//! the height of the control in the gridbag
		//!
		//! \var kSingleControlWidth
		//! the width of the controls that are not in the gridbag
		//!
		//! \var kAttributionsHeigth
		//! the height of the attribution grid control
		//!
		//! \var kDetailsHeight
		//! the height of details edit box
		//!
		//! \var kDescriptionHeight
		//! the height of the description edit box
		//!

		enum DialogSizeAndPosition
		{
			kDialogWidth = 650,
			kDialogHeight = 250,
			kTextGridWidth = 300,
			kTextHeight = 20,
			kControlGridWidth = 100,
			kControlGridHeight = 30,
			kSingleControlWidth = 600,
			kAttributionsHeigth = 200,
			kDetailsHeight = 150,
			kDescriptionHeight = 30
		};

		//! \fn CyWxEditOperationDialog ( const CyWxEditOperationDialog& ) 
		//! copy constructor
		//! not implemented

		CyWxEditOperationDialog ( const CyWxEditOperationDialog& );

		//! \fn operator = ( const CyWxEditOperationDialog& ) 
		//! operator =
		//! \return a reference to a CyWxEditOperationDialog object
		//! not implemented

		CyWxEditOperationDialog& operator = ( const CyWxEditOperationDialog& );

		//! \fn canAccountBeImported ( ) 
		//! get method
		//!
		//! \return true when the operations for the account are imported from a file

		bool canAccountBeImported ( ) const;

		//! \fn getAccountNumber ( ) 
		//! get method
		//!
		//! \return the account number for the edited operation

		const wxString getAccountNumber ( ) const;

		//! \fn getOperationDate ( ) 
		//! get method
		//!
		//! \return the operation date as it is in the operation date picker

		const wxString getOperationDate ( ) const;

		//! \fn getValueDate ( ) 
		//! get method
		//!
		//! \return the value date as it is in the value date picker

		const wxString getValueDate ( ) const;

		//! \fn getBudgetDate ( ) 
		//! get method
		//!
		//! \return the budget date as it is in the budget date picker

		const wxString getBudgetDate ( ) const;

		//! \fn getAmount ( ) 
		//! get method
		//!
		//! \return the amount as it is in the amount edit box

		long long getAmount ( ) const;

		//! \fn getDescription ( ) 
		//! get method
		//!
		//! \return the description as it is in the description edit box

		const wxString getDescription ( ) const;

		//! \fn hasOperationAttributions ( ) 
		//! get method
		//!
		//! \return true when the operation have attributions

		bool hasOperationAttributions ( ) const;

		//! \fn hasOperationDetails ( ) 
		//! get method
		//!
		//! \return true when the operation have details

		bool hasOperationDetails ( ) const;

		//! \fn hasDescription ( ) 
		//! get method
		//!
		//! \return true when the operation have a description

		bool hasDescription ( ) const;

		//! \fn isAttributionModified ( ) 
		//! get method
		//!
		//! \return true when the attributios of the operation are modified

		bool isAttributionModified ( )const;

		//! \fn onRightClickGrid ( )
		//! event handler for the "right click in the attribution grid" user action
		//! @param [ in ] event the event send by the wxWidget framework

		void onRightClickGrid ( wxGridEvent& event );

		//! \fn onDoubleLeftClickGrid ( )
		//! event handler for the "double left click in the attribution grid" user action
		//! @param [ in ] event the event send by the wxWidget framework

		void onDoubleLeftClickGrid ( wxGridEvent& event );

		//! \fn onPopupRightClickGrid ( )
		//! event handler for the "click on the popup menu in the attribution grid" user action
		//! @param [ in ] event the event send by the wxWidget framework

		void onPopupRightClickGrid ( wxCommandEvent& event );

		//! \fn onRightClickLabel ( )
		//! event handler for the "right click on the label of the attribution grid" user action
		//! @param [ in ] event the event send by the wxWidget framework

		void onRightClickLabel ( wxGridEvent& event );

		//! \fn onPopupRightClickLabel ( )
		//! event handler for the "click on the popup menu of the label of the attribution grid" user action
		//! @param [ in ] event the event send by the wxWidget framework

		void onPopupRightClickLabel ( wxCommandEvent& event );

		//! \fn onDoubleLeftClickLabel ( )
		//! event handler for the "double left click in the label of the attribution grid" user action
		//! @param [ in ] event the event send by the wxWidget framework

		void onDoubleLeftClickLabel ( wxGridEvent& event );

		//! \fn editAttribution ( )
		//! this method do the needed actions to edit an attribution

		void editAttribution ( );

		//! \fn addAttribution ( )
		//! this method do the needed actions to add an attribution

		void addAttribution ( );

		//! \fn deleteAttribution ( )
		//! this method do the needed actions to delete an attribution

		void deleteAttribution ( );

		//! \var m_pOperationDateCtrl
		//! the operation date picker control

		wxDatePickerCtrl* m_pOperationDateCtrl;

		//! \var m_pValueDateCtrl
		//! the value date picker control

		wxDatePickerCtrl* m_pValueDateCtrl;

		//! \var m_pBudgetDateCtrl
		//! the budget date picker control

		wxDatePickerCtrl* m_pBudgetDateCtrl;

		//! \var m_pAmountCtrl
		//! the amount edit box

		wxTextCtrl* m_pAmountCtrl;

		//! \var m_pDetailsCtrl
		//! the details edit box

		wxTextCtrl* m_pDetailsCtrl;

		//! \var m_pDescriptionCtrl
		//! the description edit box

		wxTextCtrl* m_pDescriptionCtrl;

		//! \var m_pAttributionsGrid
		//! the attributions grid control

		wxGrid* m_pAttributionsGrid;

		//! \var m_bAccountCanBeImported
		//! the  "account can be imported" value of the linked account

		bool m_bAccountCanBeImported;

		//! \var m_strAccountNumber
		//! the  account number of the linked account

		wxString m_strAccountNumber;

		//! \var m_dAmount
		//! the amount of the edited operation

		double m_dAmount;

		//! \var m_lOperationObjId
		//! the ObjId of the edited operation

		long long m_lOperationObjId;

		//! \var m_bAttributionModified
		//! true when the Attributions are modified

		bool m_bAttributionModified;

		//! \var m_iCurrentAttributionRow
		//! the current row of the attribution grid

		int m_iCurrentAttributionRow;

		//! \var m_pOperationsSqlManager
		//! An object used to manage the records linked to the edited operation

		CyOperationsSqlManager* m_pOperationsSqlManager;
};