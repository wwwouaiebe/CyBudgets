/* ---------------------------------------------------------------------------- */
//! CyWxBudgetsApp.h
/* ---------------------------------------------------------------------------- */
//!
//! \file CyWxBudgetsApp.h
//! \brief header file for class CyWxBudgetsApp
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

#include "DataLayer/CySqliteDb.h"
#include "UtilitiesLayer/CyWxIncludes.h"

/* ---------------------------------------------------------------------------- */

//! \class CyWxBudgetsFrame
//! \brief this is the main frame of the application
//!

class CyWxBudgetsFrame: public wxFrame
{

	public:

		//! \fn CyWxBudgetsFrame ( ) 
		//! constructor

		CyWxBudgetsFrame ( );

		//! \fn ~CyWxBudgetsFrame ( ) 
		//! destructor

		virtual ~CyWxBudgetsFrame ( );

		//! \fn UpdateAccounts ( )
		//! this method refresh the data in the account combo box after an update of the accounts

		void UpdateAccounts ( );

		//! \fn UpdateBudgets ( )
		//! this method refresh the data in the budgets combo box after an update of the budgets

		void UpdateBudgets ( );

		//! fn getStartDate ( )
		//! get method
		//! \return the date selected in the "Start date" control on the toolbar

		wxDateTime getStartDate ( ) const;

		//! fn getEndDate ( )
		//! get method
		//! \return the date selected in the "End date" control on the toolbar

		wxDateTime getEndDate ( ) const;

	private:

		//! \enum wxId
		//! values for the widgets on the toolbar
		//!
		//! \var kNewFileButton
		//! id for the new file button
		//!
		//! \var kOpenFileButton
		//! id for the open file button
		//!
		//! \var kQuitButton
		//! id for the quit button
		//!
		//! \var kAccountsButton
		//! id for the accounts button
		//!
		//! \var kAccountsBalanceButton
		//! id for the accounts balance button
		//!
		//! \var kBudgetsButton
		//! id for the budgets button
		//!
		//! \var kAttributionsButton
		//! id for the attributions button
		//!
		//! \var kAttributionsGroupsButton
		//! id for the attributions groups button
		//!
		//! \var kOperationsButton
		//! id for the operations button
		//!
		//! \var kOperationsWithoutAttributionButton
		//! id for the operations without attribution button
		//!
		//! \var kAnalyseButton
		//! id for the analyse button
		//!
		//! \var kImportButton
		//! id for the import button
		//!
		//! \var kAboutButton
		//! id for the about button
		//!
		//! \var kSqlButton
		//! id for the sql button
		//!
		//! \var kQueryButton
		//! id for the query button
		//!
		//! \var kAccountComboBox
		//! id for the account combo box
		//!
		//! \var kBudgetComboBox
		//! id for the budgets combo box
		//!
		//! \var kStartDateCtrl
		//! id for the start date control
		//!
		//! \var kEndDateCtrl
		//! id for the end date control

		enum wxId
		{
			kNewFileButton,
			kOpenFileButton,
			kQuitButton,
			kAccountsButton,
			kAccountsBalanceButton,
			kBudgetsButton,
			kAttributionsGroupsButton,
			kAttributionsButton,
			kOperationsButton,
			kOperationsWithoutAttributionButton,
			kAnalyseButton,
			kImportButton,
			kAboutButton,
			kSqlButton,
			kQueryButton,
			kAccountComboBox,
			kBudgetComboBox,
			kStartDateCtrl,
			kEndDateCtrl
		};

		//! \enum Sizes
		//! values for the widgets sizes on the toolbar
		//!
		//! \var kToolsHeight
		//! the height of the widgets
		//!
		//! \var kDateToolsWidth
		//! the width of the date pickers
		//!
		//! \var kComboToolsWidth
		//! the width of the combo boxes
		//!

		enum Sizes
		{
			kToolsHeight = 30,
			kDateToolsWidth = 100,
			kComboToolsWidth = 300
		};

		//! \fn isDbOpen ( )
		//! this method test if a database is opened and display a message when the db is not opened
		//! \return ture when the db is opened, false otherwise.

		bool isDbOpen ( );

		//! \fn onNewFile ( )
		//! event handler for the "single click on the New File button" user action
		//! @param [ in ] event the event send by the wxWidget framework

		void onNewFile ( wxCommandEvent& event );

		//! \fn onOpenFile ( )
		//! event handler for the "single click on the Open File button" user action
		//! @param [ in ] event the event send by the wxWidget framework

		void onOpenFile ( wxCommandEvent& event );

		//! \fn onQuit ( )
		//! event handler for the "single click on the Quit button" user action
		//! @param [ in ] event the event send by the wxWidget framework

		void onQuit ( wxCommandEvent& event );

		//! \fn onAccounts ( )
		//! event handler for the "single click on the Accounts button" user action
		//! @param [ in ] event the event send by the wxWidget framework

		void onAccounts ( wxCommandEvent& event );

		//! \fn onBudgets ( )
		//! event handler for the "single click on the Budgets button" user action
		//! @param [ in ] event the event send by the wxWidget framework

		void onBudgets ( wxCommandEvent& event );

		//! \fn onAccountsBalance ( )
		//! event handler for the "single click on the Acounts balance button" user action
		//! @param [ in ] event the event send by the wxWidget framework

		void onAccountsBalance ( wxCommandEvent& event );

		//! \fn onAttributions ( )
		//! event handler for the "single click on the Attributions button" user action
		//! @param [ in ] event the event send by the wxWidget framework

		void onAttributions ( wxCommandEvent& event );

		//! \fn onAttributionsGroups ( )
		//! event handler for the "single click on the Attributions button" user action
		//! @param [ in ] event the event send by the wxWidget framework

		void onAttributionsGroups ( wxCommandEvent& event );

		//! \fn onOperations ( )
		//! event handler for the "single click on the Operations button" user action
		//! @param [ in ] event the event send by the wxWidget framework

		void onOperations ( wxCommandEvent& event );

		//! \fn onOperationsWithoutAttribution ( )
		//! event handler for the "single click on the Operations Without Attribution button" user action
		//! @param [ in ] event the event send by the wxWidget framework

		void onOperationsWithoutAttribution ( wxCommandEvent& event );

		//! \fn onAnalyse ( )
		//! event handler for the "single click on the Analyse button" user action
		//! @param [ in ] event the event send by the wxWidget framework

		void onAnalyse ( wxCommandEvent& event );

		//! \fn onImport ( )
		//! event handler for the "single click on the Import button" user action
		//! @param [ in ] event the event send by the wxWidget framework

		void onImport ( wxCommandEvent& event );

		//! \fn onSql ( )
		//! event handler for the "single click on the SQL button" user action
		//! @param [ in ] event the event send by the wxWidget framework

		void onSql ( wxCommandEvent& event );

		//! \fn onQuery ( )
		//! event handler for the "single click on the Query button" user action
		//! @param [ in ] event the event send by the wxWidget framework

		void onQuery ( wxCommandEvent& event );

		//! \fn onAbout ( )
		//! event handler for the "single click on the About button" user action
		//! @param [ in ] event the event send by the wxWidget framework

		void onAbout ( wxCommandEvent& event );

		//! \fn displayDbErrorMessage ( CySqliteDb::NewOpenErrors eReturnCode )
		//! this method display an error message, depending of the parameter value
		//! @param [ in ] eReturnCode the error code for witch the error message must be displayed

		void displayDbErrorMessage ( CySqliteDb::NewOpenErrors eReturnCode );

		//! \fn displayMessage ( const wxString & strMessage, const wxString& strCaption )
		//! this method display a message. This method can be used as callback
		//! @param [ in ] strMessage the message to display
		//! @param [ in ] strCaption the caption of the message box

		static void displayMessage ( const wxString & strMessage, const wxString& strCaption );

		//! \fn CyWxBudgetsFrame ( const CyWxBudgetsFrame& ) 
		//! copy constructor
		//! not implemented

		CyWxBudgetsFrame ( const CyWxBudgetsFrame& );

		//! \fn operator = ( const CyWxBudgetsFrame& ) 
		//! operator =
		//! \return a reference to a CyWxBudgetsFrame object
		//! not implemented

		CyWxBudgetsFrame& operator = ( const CyWxBudgetsFrame& );

		//! \fn onNewOpenSuccess ( const wxString& strFilePath )
		//! this method display the file name on the window title and activate the toolbar button.
		//! @param [ in ] strFilePath the db path

		void onNewOpenSuccess ( const wxString& strFilePath );

		//! \var m_pAccountComboBox
		//! the account combo box on the toolbar
		//!

		wxComboBox* m_pAccountComboBox;

		//! \var m_pBudgetComboBox
		//! the budget combo box on the toolbar
		//!

		wxComboBox* m_pBudgetComboBox;

		//! \var m_pStartDateCtrl
		//! the start date picker on the toolbar
		//!

		wxDatePickerCtrl* m_pStartDateCtrl;

		//! \var m_pEndDateCtrl
		//! the start date picker on the toolbar
		//!

		wxDatePickerCtrl* m_pEndDateCtrl;

		wxToolBar* m_pToolBar;

};

/* ---------------------------------------------------------------------------- */
