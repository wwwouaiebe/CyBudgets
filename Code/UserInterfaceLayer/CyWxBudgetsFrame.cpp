/* ---------------------------------------------------------------------------- */
//! CyWxBudgetsFrame.cpp
/* ---------------------------------------------------------------------------- */
//!
//! \file CyWxBudgetsFrame.cpp
//! \brief definition file for class CyWxBudgetsFrame
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

#include "UserInterfaceLayer/CyWxBudgetsApp.h"
#include "UserInterfaceLayer/CyWxBudgetsFrame.h"
#include "UserInterfaceLayer/CyWxShowRequestAnalyseMediator.h"
#include "UserInterfaceLayer/CyWxShowRequestAttributionsMediator.h"
#include "UserInterfaceLayer/CyWxShowRequestAttributionsGroupsMediator.h"
#include "UserInterfaceLayer/CyWxShowRequestAccountsMediator.h"
#include "UserInterfaceLayer/CyWxShowRequestBudgetsMediator.h"
#include "UserInterfaceLayer/CyWxShowRequestDialog.h"
#include "UserInterfaceLayer/CyWxShowRequestOperationsMediator.h"
#include "UserInterfaceLayer/CyWxLongLongItemData.h"
#include "CoreLayer/CyAccountsBalanceSqlBuilder.h"
#include "CoreLayer/CyAccountsSqlBuilder.h"
#include "CoreLayer/CyAnalyseSqlBuilder.h"
#include "CoreLayer/CyAttributionsSqlBuilder.h"
#include "CoreLayer/CyAttributionsGroupsSqlBuilder.h"
#include "CoreLayer/CyBudgetsSqlBuilder.h"
#include "CoreLayer/CyIngImportTool.h"
#include "CoreLayer/CyOperationsSqlBuilder.h"
#include "CoreLayer/CyUserQuerySqlBuilder.h"
#include "DataLayer/CyValue.h"
#include "DataLayer/CyLongValue.h"
#include "UtilitiesLayer/CyEnum.h"
#include "UtilitiesLayer/CyFilesService.h"
#include "UtilitiesLayer/CyGetText.h"
#include "UtilitiesLayer/CyWxVersionInfo.h"

/* ---------------------------------------------------------------------------- */

CyWxBudgetsFrame::CyWxBudgetsFrame ( ) :
	wxFrame(
		NULL, 
		wxID_ANY, 
		CyGetText::getInstance ( ).getText ( "CyWxBudgetsFrame.CyWxBudgetsFrame.WindowTitle" ), 
		wxPoint ( CyEnum::kLeft, CyEnum::kTop ), 
		wxSize ( CyEnum::kWindowWidth, CyEnum::kWindowHeight ), 
		wxMAXIMIZE | wxDEFAULT_FRAME_STYLE )
{
	wxIcon objIcon ( CyFilesService::getInstance ( ).getResourcesPath ( ) +  wxString ( "CyBudgets.gif" ), wxBITMAP_TYPE_GIF, 32, 32 );
	this->SetIcon ( objIcon );

	// Toolbar creation
	wxToolBar* pToolBar = this->CreateToolBar( );

	// Quit button creation
	wxBitmap quitBitmap ( CyFilesService::getInstance ( ).getResourcesPath ( ) +  wxString ( "Quit.gif" ), wxBITMAP_TYPE_GIF );
	wxToolBarToolBase* pQuitTool = pToolBar->AddTool (
									   this->kQuitButton,
									   CyGetText::getInstance ( ).getText ( "CyWxBudgetsFrame.CyWxBudgetsFrame.Quit" ),
									   quitBitmap,
									   wxNullBitmap,
									   wxITEM_NORMAL,
									   CyGetText::getInstance ( ).getText ( "CyWxBudgetsFrame.CyWxBudgetsFrame.QuitTooltip" ),
									   CyGetText::getInstance ( ).getText ( "CyWxBudgetsFrame.CyWxBudgetsFrame.QuitToolHelp" ) );
	pToolBar->AddSeparator ();

	// About button creation 
	wxBitmap aboutBitmap ( CyFilesService::getInstance ( ).getResourcesPath ( ) +  wxString ( "about.gif" ), wxBITMAP_TYPE_GIF );
	wxToolBarToolBase* pAboutTool = pToolBar->AddTool (
									   this->kAboutButton,
									   CyGetText::getInstance ( ).getText ( "CyWxBudgetsFrame.CyWxBudgetsFrame.About" ),
									   aboutBitmap,
									   wxNullBitmap,
									   wxITEM_NORMAL,
									   CyGetText::getInstance ( ).getText ( "CyWxBudgetsFrame.CyWxBudgetsFrame.AboutTooltip" ),
									   CyGetText::getInstance ( ).getText ( "CyWxBudgetsFrame.CyWxBudgetsFrame.AboutToolHelp" ) );

	pToolBar->AddSeparator ();
	pToolBar->AddStretchableSpace ( );
	pToolBar->AddSeparator ();

	// New file creation
	wxBitmap newFileBitmap ( CyFilesService::getInstance ( ).getResourcesPath ( ) +  wxString ( "NewFile.gif" ), wxBITMAP_TYPE_GIF );
	wxToolBarToolBase* pNewFileTool = pToolBar->AddTool (
									   this->kNewFileButton,
									   CyGetText::getInstance ( ).getText ( "CyWxBudgetsFrame.CyWxBudgetsFrame.NewFile" ),
									   newFileBitmap,
									   wxNullBitmap,
									   wxITEM_NORMAL,
									   CyGetText::getInstance ( ).getText ( "CyWxBudgetsFrame.CyWxBudgetsFrame.NewFileTooltip" ),
									   CyGetText::getInstance ( ).getText ( "CyWxBudgetsFrame.CyWxBudgetsFrame.NewFileToolHelp" ) );

	// Open file creation
	wxBitmap openFileBitmap ( CyFilesService::getInstance ( ).getResourcesPath ( ) +  wxString ( "OpenFile.gif" ), wxBITMAP_TYPE_GIF );
	wxToolBarToolBase* pOpenFileTool = pToolBar->AddTool (
									   this->kOpenFileButton,
									   CyGetText::getInstance ( ).getText ( "CyWxBudgetsFrame.CyWxBudgetsFrame.OpenFile" ),
									   openFileBitmap,
									   wxNullBitmap,
									   wxITEM_NORMAL,
									   CyGetText::getInstance ( ).getText ( "CyWxBudgetsFrame.CyWxBudgetsFrame.OpenFileTooltip" ),
									   CyGetText::getInstance ( ).getText ( "CyWxBudgetsFrame.CyWxBudgetsFrame.OpenFileToolHelp" ) );
	pToolBar->AddSeparator ();

	// Operations button creation
	wxBitmap operationsBitmap ( CyFilesService::getInstance ( ).getResourcesPath ( ) +  wxString ( "Operations.gif" ), wxBITMAP_TYPE_GIF );
	wxToolBarToolBase* pOperationsTool = pToolBar->AddTool (
									   this->kOperationsButton,
									   CyGetText::getInstance ( ).getText ( "CyWxBudgetsFrame.CyWxBudgetsFrame.Operations" ),
									   operationsBitmap,
									   wxNullBitmap,
									   wxITEM_NORMAL,
									   CyGetText::getInstance ( ).getText ( "CyWxBudgetsFrame.CyWxBudgetsFrame.OperationsTooltip" ),
									   CyGetText::getInstance ( ).getText ( "CyWxBudgetsFrame.CyWxBudgetsFrame.OperationsToolHelp" ) );

	// Analyse button creation 
	wxBitmap analyseBitmap ( CyFilesService::getInstance ( ).getResourcesPath ( ) +  wxString ( "Analyse.gif" ), wxBITMAP_TYPE_GIF );
	wxToolBarToolBase* pAnalyseTool = pToolBar->AddTool (
									   this->kAnalyseButton,
									   CyGetText::getInstance ( ).getText ( "CyWxBudgetsFrame.CyWxBudgetsFrame.Analyse" ),
									   analyseBitmap,
									   wxNullBitmap,
									   wxITEM_NORMAL,
									   CyGetText::getInstance ( ).getText ( "CyWxBudgetsFrame.CyWxBudgetsFrame.AnalyseTooltip" ),
									   CyGetText::getInstance ( ).getText ( "CyWxBudgetsFrame.CyWxBudgetsFrame.AnalyseToolHelp" ) );

	// Account balance button creation 
	wxBitmap accountsBalanceBitmap ( CyFilesService::getInstance ( ).getResourcesPath ( ) +  wxString ( "AccountBalance.gif" ), wxBITMAP_TYPE_GIF );
	wxToolBarToolBase* pAccountBalanceTool = pToolBar->AddTool (
									   this->kAccountsBalanceButton,
									   CyGetText::getInstance ( ).getText ( "CyWxBudgetsFrame.CyWxBudgetsFrame.AccountsBalance" ),
									   accountsBalanceBitmap,
									   wxNullBitmap,
									   wxITEM_NORMAL,
									   CyGetText::getInstance ( ).getText ( "CyWxBudgetsFrame.CyWxBudgetsFrame.AccountsBalanceTooltip" ),
									   CyGetText::getInstance ( ).getText ( "CyWxBudgetsFrame.CyWxBudgetsFrame.AccountBalanceToolHelp" ) );

	// Non attributed operations button creation 
	wxBitmap operationsWithoutAttributionBitmap ( CyFilesService::getInstance ( ).getResourcesPath ( ) +  wxString ( "operationsWithoutAttribution.gif" ), wxBITMAP_TYPE_GIF );
	wxToolBarToolBase* pOperationsWithoutAttributionTool = pToolBar->AddTool (
									   this->kOperationsWithoutAttributionButton,
									   CyGetText::getInstance ( ).getText ( "CyWxBudgetsFrame.CyWxBudgetsFrame.OperationsWithoutAttribution" ),
									   operationsWithoutAttributionBitmap,
									   wxNullBitmap,
									   wxITEM_NORMAL,
									   CyGetText::getInstance ( ).getText ( "CyWxBudgetsFrame.CyWxBudgetsFrame.OperationsWithoutAttributionTooltip" ),
									   CyGetText::getInstance ( ).getText ( "CyWxBudgetsFrame.CyWxBudgetsFrame.OperationsWithoutAttributionToolHelp" ) );

	// Import button creation 
	wxBitmap importBitmap ( CyFilesService::getInstance ( ).getResourcesPath ( ) +  wxString ( "Import.gif" ), wxBITMAP_TYPE_GIF );
	wxToolBarToolBase* pImportTool = pToolBar->AddTool (
									   this->kImportButton,
									   CyGetText::getInstance ( ).getText ( "CyWxBudgetsFrame.CyWxBudgetsFrame.Import" ),
									   importBitmap,
									   wxNullBitmap,
									   wxITEM_NORMAL,
									   CyGetText::getInstance ( ).getText ( "CyWxBudgetsFrame.CyWxBudgetsFrame.ImportTooltip" ),
									   CyGetText::getInstance ( ).getText ( "CyWxBudgetsFrame.CyWxBudgetsFrame.ImportToolHelp" ) );
	pToolBar->AddSeparator ();

	// Account combo box creation
	wxArrayString strDummyArray;
	this->m_pAccountComboBox = new wxComboBox ( 
		pToolBar, 
		this->kAccountComboBox, 
		wxEmptyString,
		wxDefaultPosition, 
		wxSize ( kComboToolsWidth ,kToolsHeight ),
		strDummyArray,
		wxCB_READONLY );
	pToolBar->AddControl ( this->m_pAccountComboBox );

	// The combo box is filled
	this->UpdateAccounts ( );

	pToolBar->AddSeparator ();

	// Budget combo box creation
	this->m_pBudgetComboBox = new wxComboBox (
		pToolBar, 
		this->kBudgetComboBox,
		wxEmptyString,
		wxDefaultPosition,
		wxSize ( kComboToolsWidth ,kToolsHeight ),
		strDummyArray,
		wxCB_READONLY );
	pToolBar->AddControl ( m_pBudgetComboBox );

	// The combo box is filled
	this->UpdateBudgets ( );

	pToolBar->AddSeparator ();

	// Start date picker control creation
	m_pStartDateCtrl = new wxDatePickerCtrl ( 
		pToolBar, 
		this->kStartDateCtrl,
		wxDefaultDateTime,
		wxDefaultPosition , 
		wxSize ( kDateToolsWidth, kToolsHeight ),
		wxDP_DROPDOWN );
	pToolBar->AddControl ( m_pStartDateCtrl );

	// the start date picker is set to the begin of the year
	wxDateTime beginOfYear;
	beginOfYear.SetToCurrent ( );
	beginOfYear.SetToYearDay ( 1 );
	m_pStartDateCtrl->SetValue ( beginOfYear );

	pToolBar->AddSeparator ();

	// End date picker control creation
	m_pEndDateCtrl = new wxDatePickerCtrl ( 
		pToolBar, 
		this->kEndDateCtrl,
		wxDefaultDateTime,
		wxDefaultPosition ,
		wxSize ( kDateToolsWidth, kToolsHeight ),
		wxDP_DROPDOWN );
	pToolBar->AddControl ( m_pEndDateCtrl );

	pToolBar->AddStretchableSpace ( );
	pToolBar->AddSeparator ();

	// Account button creation 
	wxBitmap accountBitmap ( CyFilesService::getInstance ( ).getResourcesPath ( ) +  wxString ( "Account.gif" ), wxBITMAP_TYPE_GIF );
	wxToolBarToolBase* pAccountTool = pToolBar->AddTool (
									   this->kAccountsButton,
									   CyGetText::getInstance ( ).getText ( "CyWxBudgetsFrame.CyWxBudgetsFrame.Account" ),
									   accountBitmap,
									   wxNullBitmap,
									   wxITEM_NORMAL,
									   CyGetText::getInstance ( ).getText ( "CyWxBudgetsFrame.CyWxBudgetsFrame.AccountTooltip" ),
									   CyGetText::getInstance ( ).getText ( "CyWxBudgetsFrame.CyWxBudgetsFrame.AccountToolHelp" ) );

	// Budgets button creation 
	wxBitmap budgetsBitmap ( CyFilesService::getInstance ( ).getResourcesPath ( ) +  wxString ( "Budgets.gif" ), wxBITMAP_TYPE_GIF );
	wxToolBarToolBase* pBudgetsTool = pToolBar->AddTool (
									   this->kBudgetsButton,
									   CyGetText::getInstance ( ).getText ( "CyWxBudgetsFrame.CyWxBudgetsFrame.Budget" ),
									   budgetsBitmap,
									   wxNullBitmap,
									   wxITEM_NORMAL,
									   CyGetText::getInstance ( ).getText ( "CyWxBudgetsFrame.CyWxBudgetsFrame.BudgetTooltip" ),
									   CyGetText::getInstance ( ).getText ( "CyWxBudgetsFrame.CyWxBudgetsFrame.BudgetToolHelp" ) );

	// Attributions groups button creation 
	wxBitmap AttributionsGroupsBitmap ( CyFilesService::getInstance ( ).getResourcesPath ( ) +  wxString ( "AttributionsGroups.gif" ), wxBITMAP_TYPE_GIF );
	wxToolBarToolBase* pAttributionsGroupsTool = pToolBar->AddTool (
									   this->kAttributionsGroupsButton,
									   CyGetText::getInstance ( ).getText ( "CyWxBudgetsFrame.CyWxBudgetsFrame.AttributionsGroups" ),
									   AttributionsGroupsBitmap,
									   wxNullBitmap,
									   wxITEM_NORMAL,
									   CyGetText::getInstance ( ).getText ( "CyWxBudgetsFrame.CyWxBudgetsFrame.AttributionsGroupsTooltip" ),
									   CyGetText::getInstance ( ).getText ( "CyWxBudgetsFrame.CyWxBudgetsFrame.AttributionsGroupsToolHelp" ) );

	// Attributions button creation 
	wxBitmap AttributionsBitmap ( CyFilesService::getInstance ( ).getResourcesPath ( ) +  wxString ( "Attributions.gif" ), wxBITMAP_TYPE_GIF );
	wxToolBarToolBase* pAttributionsTool = pToolBar->AddTool (
									   this->kAttributionsButton,
									   CyGetText::getInstance ( ).getText ( "CyWxBudgetsFrame.CyWxBudgetsFrame.Attributions" ),
									   AttributionsBitmap,
									   wxNullBitmap,
									   wxITEM_NORMAL,
									   CyGetText::getInstance ( ).getText ( "CyWxBudgetsFrame.CyWxBudgetsFrame.AttributionsTooltip" ),
									   CyGetText::getInstance ( ).getText ( "CyWxBudgetsFrame.CyWxBudgetsFrame.AttributionsToolHelp" ) );

	pToolBar->AddSeparator ();

	// SQL button creation 
	wxBitmap sqlBitmap ( CyFilesService::getInstance ( ).getResourcesPath ( ) +  wxString ( "Sql.gif" ), wxBITMAP_TYPE_GIF );
	wxToolBarToolBase* pSqlTool = pToolBar->AddTool (
									   this->kSqlButton,
									   CyGetText::getInstance ( ).getText ( "CyWxBudgetsFrame.CyWxBudgetsFrame.Sql" ),
									   sqlBitmap,
									   wxNullBitmap,
									   wxITEM_NORMAL,
									   CyGetText::getInstance ( ).getText ( "CyWxBudgetsFrame.CyWxBudgetsFrame.SqlTooltip" ),
									   CyGetText::getInstance ( ).getText ( "CyWxBudgetsFrame.CyWxBudgetsFrame.SqlToolHelp" ) );

	// Query button creation 
	wxBitmap queryBitmap ( CyFilesService::getInstance ( ).getResourcesPath ( ) +  wxString ( "Query.gif" ), wxBITMAP_TYPE_GIF );
	wxToolBarToolBase* pQueryTool = pToolBar->AddTool (
									   this->kQueryButton,
									   CyGetText::getInstance ( ).getText ( "CyWxBudgetsFrame.CyWxBudgetsFrame.Query" ),
									   queryBitmap,
									   wxNullBitmap,
									   wxITEM_NORMAL,
									   CyGetText::getInstance ( ).getText ( "CyWxBudgetsFrame.CyWxBudgetsFrame.QueryTooltip" ),
									   CyGetText::getInstance ( ).getText ( "CyWxBudgetsFrame.CyWxBudgetsFrame.QueryToolHelp" ) );

	// End of toolbar creation
	pToolBar->Realize ( );
	this->SetToolBar ( pToolBar );

	// Events creation
	this->Connect ( pNewFileTool->GetId ( ), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler ( CyWxBudgetsFrame::onNewFile ) );
	this->Connect ( pOpenFileTool->GetId ( ), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler ( CyWxBudgetsFrame::onOpenFile ) );
	this->Connect ( pQuitTool->GetId ( ), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler ( CyWxBudgetsFrame::onQuit ) );
	this->Connect ( pAccountTool->GetId ( ), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler ( CyWxBudgetsFrame::onAccounts ) );
	this->Connect ( pBudgetsTool->GetId ( ), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler ( CyWxBudgetsFrame::onBudgets ) );
	this->Connect ( pAttributionsTool->GetId ( ), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler ( CyWxBudgetsFrame::onAttributions ) );
	this->Connect ( pAttributionsGroupsTool->GetId ( ), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler ( CyWxBudgetsFrame::onAttributionsGroups ) );
	this->Connect ( pOperationsTool->GetId ( ), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler ( CyWxBudgetsFrame::onOperations ) );
	this->Connect ( pOperationsWithoutAttributionTool->GetId ( ), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler ( CyWxBudgetsFrame::onOperationsWithoutAttribution ) );
	this->Connect ( pAnalyseTool->GetId ( ), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler ( CyWxBudgetsFrame::onAnalyse ) );
	this->Connect ( pAccountBalanceTool->GetId ( ), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler ( CyWxBudgetsFrame::onAccountsBalance ) );
	this->Connect ( pImportTool->GetId ( ), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler ( CyWxBudgetsFrame::onImport ) );
	this->Connect ( pSqlTool->GetId ( ), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler ( CyWxBudgetsFrame::onSql ) );
	this->Connect ( pQueryTool->GetId ( ), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler ( CyWxBudgetsFrame::onQuery ) );
	this->Connect ( pAboutTool->GetId ( ), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler ( CyWxBudgetsFrame::onAbout ) );
}

/* ---------------------------------------------------------------------------- */

CyWxBudgetsFrame::~CyWxBudgetsFrame ( )
{
	// Events deletion
	this->Disconnect ( this->kNewFileButton, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler ( CyWxBudgetsFrame::onNewFile ) );
	this->Disconnect ( this->kOpenFileButton, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler ( CyWxBudgetsFrame::onOpenFile ) );
	this->Disconnect ( this->kQuitButton, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler ( CyWxBudgetsFrame::onQuit ) );
	this->Disconnect ( this->kAccountsButton, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler ( CyWxBudgetsFrame::onAccounts ) );
	this->Disconnect ( this->kBudgetsButton, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler ( CyWxBudgetsFrame::onBudgets ) );
	this->Disconnect ( this->kAttributionsButton, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler ( CyWxBudgetsFrame::onAttributions ) );
	this->Disconnect ( this->kAttributionsGroupsButton, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler ( CyWxBudgetsFrame::onAttributionsGroups ) );
	this->Disconnect ( this->kOperationsButton, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler ( CyWxBudgetsFrame::onOperations ) );
	this->Disconnect ( this->kOperationsWithoutAttributionButton, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler ( CyWxBudgetsFrame::onOperations ) );
	this->Disconnect ( this->kAnalyseButton, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler ( CyWxBudgetsFrame::onAnalyse ) );
	this->Disconnect ( this->kAccountsBalanceButton, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler ( CyWxBudgetsFrame::onAccountsBalance ) );
	this->Disconnect ( this->kImportButton, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler ( CyWxBudgetsFrame::onImport ) );
	this->Disconnect ( this->kSqlButton, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler ( CyWxBudgetsFrame::onSql ) );
	this->Disconnect ( this->kQueryButton, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler ( CyWxBudgetsFrame::onQuery ) );
	this->Disconnect ( this->kAboutButton, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler ( CyWxBudgetsFrame::onAbout ) );
}

/* ---------------------------------------------------------------------------- */

void CyWxBudgetsFrame::onNewFile ( wxCommandEvent& )
{
	wxFileDialog sqlFileDialog ( 
		NULL, 
		CyGetText::getInstance ( ).getText ( "CyWxBudgetsFrame.onNewFile.Title" ),
		wxFileSelectorPromptStr,
		wxEmptyString,
		wxString ( "*.CyBudgets files (*.CyBudgets)|*.CyBudgets" ),
		wxFD_OPEN );
	if ( wxID_OK == sqlFileDialog.ShowModal ( ) )
	{
		CySqliteDb::NewOpenErrors eReturnCode = CySqliteDb::getInstance ( ).newFile ( 
			sqlFileDialog.GetDirectory ( ) + wxFileName::GetPathSeparator ( ),
			sqlFileDialog.GetFilename ( ) );

		this->displayDbErrorMessage ( eReturnCode );

		if ( CySqliteDb::kNewOpenOk == eReturnCode)
		{
			this->m_pBudgetComboBox->Select ( 0 );
			this->m_pAccountComboBox->Select ( 0 );
		}
	}
}

/* ---------------------------------------------------------------------------- */

void CyWxBudgetsFrame::onOpenFile ( wxCommandEvent& )
{
	wxFileDialog sqlFileDialog ( 
		NULL, 
		CyGetText::getInstance ( ).getText ( "CyWxBudgetsFrame.onOpenFile.Title" ),
		wxFileSelectorPromptStr,
		wxEmptyString,
		wxString ( "*.CyBudgets files (*.CyBudgets)|*.CyBudgets" ),
		wxFD_OPEN | wxFD_FILE_MUST_EXIST );
	if ( wxID_OK == sqlFileDialog.ShowModal ( ) )
	{
		CySqliteDb::NewOpenErrors eReturnCode = CySqliteDb::getInstance ( ).openFile ( 
			sqlFileDialog.GetDirectory ( ) + wxFileName::GetPathSeparator ( ),
			sqlFileDialog.GetFilename ( ) );

		this->displayDbErrorMessage ( eReturnCode );

		if ( CySqliteDb::kNewOpenOk == eReturnCode)
		{
			this->m_pBudgetComboBox->Select ( 0 );
			this->m_pAccountComboBox->Select ( 0 );
		}
	}
}

/* ---------------------------------------------------------------------------- */

void CyWxBudgetsFrame::displayMessage ( const wxString & strMessage, const wxString& strCaption )
{
	wxMessageDialog* pMessageDialog = new wxMessageDialog (
		wxGetApp ( ).getBudgetsFrame ( ),
		strMessage, 
		strCaption,
		wxOK | wxICON_EXCLAMATION | wxCENTRE );
	pMessageDialog->ShowModal ( );
	pMessageDialog->Destroy ( );
}

/* ---------------------------------------------------------------------------- */

void CyWxBudgetsFrame::displayDbErrorMessage ( CySqliteDb::NewOpenErrors eReturnCode )
{
	wxString strErrorCaption;
	wxString strErrorMessage;
	switch ( eReturnCode )
	{
	case CySqliteDb::kNewOpenOk:
		this->UpdateAccounts ( );
		this->UpdateBudgets ( );
		break;
	case CySqliteDb::kNewOpenErrorLog:
		strErrorMessage = CyGetText::getInstance ( ).getText ( "CyWxBudgetsFrame.displayDbErrorMessage.ErrorLogText" ); 
		strErrorCaption = CyGetText::getInstance ( ).getText ( "CyWxBudgetsFrame.displayDbErrorMessage.ErrorLogCaption" );
		break;
	case CySqliteDb::kNewOpenSqlLog:
		strErrorMessage = CyGetText::getInstance ( ).getText ( "CyWxBudgetsFrame.displayDbErrorMessage.SqlLogText" ); 
		strErrorCaption = CyGetText::getInstance ( ).getText ( "CyWxBudgetsFrame.displayDbErrorMessage.SqlLogCaption" );
		break;
	case CySqliteDb::kNewOpenSqliteDb:
		strErrorMessage = CyGetText::getInstance ( ).getText ( "CyWxBudgetsFrame.displayDbErrorMessage.ErrorDbText" ); 
		strErrorCaption = CyGetText::getInstance ( ).getText ( "CyWxBudgetsFrame.displayDbErrorMessage.ErrorDbCaption" );
		break;
	case CySqliteDb::kNewOpenErrorSqlCreation:
		strErrorMessage = CyGetText::getInstance ( ).getText ( "CyWxBudgetsFrame.displayDbErrorMessage.ErrorSqlText" ); 
		strErrorCaption = CyGetText::getInstance ( ).getText ( "CyWxBudgetsFrame.displayDbErrorMessage.ErrorSqlCaption" );
		break;
	case CySqliteDb::kNewOpenErrorValidateBefore102:
		strErrorMessage = CyGetText::getInstance ( ).getText ( "CyWxBudgetsFrame.displayDbErrorMessage.ErrorValidateBefore102Text" ); 
		strErrorCaption = CyGetText::getInstance ( ).getText ( "CyWxBudgetsFrame.displayDbErrorMessage.ErrorValidateBefore102Caption" );
		break;
	case CySqliteDb::kNewOpenErrorValidate:
		strErrorMessage = CyGetText::getInstance ( ).getText ( "CyWxBudgetsFrame.displayDbErrorMessage.ErrorValidateText" ); 
		strErrorCaption = CyGetText::getInstance ( ).getText ( "CyWxBudgetsFrame.displayDbErrorMessage.ErrorValidateCaption" );
		break;
	case CySqliteDb::kNewOpenVersionNotFound:
		strErrorMessage = CyGetText::getInstance ( ).getText ( "CyWxBudgetsFrame.displayDbErrorMessage.NewOpenVersionNotFoundText" ); 
		strErrorCaption = CyGetText::getInstance ( ).getText ( "CyWxBudgetsFrame.displayDbErrorMessage.NewOpenVersionNotFoundCaption" );
		break;
	case CySqliteDb::kNewOpenErrorUpgrade102:
		strErrorMessage = CyGetText::getInstance ( ).getText ( "CyWxBudgetsFrame.displayDbErrorMessage.UpgradeToVersion102Text" ); 
		strErrorCaption = CyGetText::getInstance ( ).getText ( "CyWxBudgetsFrame.displayDbErrorMessage.upgradeToVersion102Caption" );
		break;
	case CySqliteDb::kNewOpenErrorUpgrade103:
		strErrorMessage = CyGetText::getInstance().getText("CyWxBudgetsFrame.displayDbErrorMessage.UpgradeToVersion103Text");
		strErrorCaption = CyGetText::getInstance().getText("CyWxBudgetsFrame.displayDbErrorMessage.upgradeToVersion103Caption");
		break;
	case CySqliteDb::kNewOpenErrorUpgrade110:
		strErrorMessage = CyGetText::getInstance().getText("CyWxBudgetsFrame.displayDbErrorMessage.UpgradeToVersion110Text");
		strErrorCaption = CyGetText::getInstance().getText("CyWxBudgetsFrame.displayDbErrorMessage.upgradeToVersion110Caption");
		break;
	case CySqliteDb::kNewOpenUnknown:
		strErrorMessage = CyGetText::getInstance ( ).getText ( "CyWxBudgetsFrame.displayDbErrorMessage.NewOpenUnknownText" );
		strErrorCaption = CyGetText::getInstance ( ).getText ( "CyWxBudgetsFrame.displayDbErrorMessage.NewOpenUnknownCaption" );
		break;
	}

	if ( CySqliteDb::kNewOpenOk != eReturnCode )
	{
		wxMessageDialog* pErrorDialog = new wxMessageDialog (
			this,
			strErrorMessage, 
			strErrorCaption,
			wxOK | wxICON_EXCLAMATION | wxCENTRE );
		pErrorDialog->ShowModal ( );
		pErrorDialog->Destroy ( );
	}
}

/* ---------------------------------------------------------------------------- */

void CyWxBudgetsFrame::onQuit ( wxCommandEvent& )
{
	this->Destroy();
}

/* ---------------------------------------------------------------------------- */

void CyWxBudgetsFrame::onSql ( wxCommandEvent& )
{
	// testing if the db is opened
	if ( ! this->isDbOpen ( ) )
	{
		return;
	}

	// a entry text dialog box is created...
	wxTextEntryDialog* pSqlDialog = new wxTextEntryDialog 	( 	
		this,
		CyGetText::getInstance ( ).getText ( "CyWxBudgetsFrame.onSql.Message" ),
		CyGetText::getInstance ( ).getText ( "CyWxBudgetsFrame.onSql.Caption" ) );

	bool bValidSql = false;
	while ( ! bValidSql )
	{	// ... and displayed
		if ( wxID_OK == pSqlDialog->ShowModal ( ) )
		{
			// the user have pushed the OK button. We try to execute the SQL
			if ( CySqliteDb::getInstance ( ).executeSql ( pSqlDialog->GetValue ( ) ) )
			{
				// Sql executed
				wxMessageBox ( CyGetText::getInstance ( ).getText ( "CyWxBudgetsFrame.onSql.SqlExecuted" ) );
				bValidSql = true;
			}
			else
			{
				// Sql not executed. The error message is show.
				wxMessageBox ( CyGetText::getInstance ( ).getText ( "CyWxBudgetsFrame.onSql.SqlError" ) + CySqliteDb::getInstance ( ).getLastError ( ) );
			}
		}
		else
		{
			bValidSql = true;
		}
	}

	pSqlDialog->Destroy ( );
}

/* ---------------------------------------------------------------------------- */

void CyWxBudgetsFrame::onQuery ( wxCommandEvent& )
{
	// testing if the db is opened
	if ( ! this->isDbOpen ( ) )
	{
		return;
	}

	// a entry text dialog box is created...
	wxTextEntryDialog* pQueryDialog = new wxTextEntryDialog 	( 	
		this,
		CyGetText::getInstance ( ).getText ( "CyWxBudgetsFrame.onQuery.Message" ),
		CyGetText::getInstance ( ).getText ( "CyWxBudgetsFrame.onQuery.Caption" ) );

	bool bValidQuery = false;
	while ( ! bValidQuery )
	{
		// ... and displayed
		if ( wxID_OK == pQueryDialog->ShowModal ( ) )
		{
			// the user have pushed the OK button. We evaluate the SQL
			if ( CySqliteDb::getInstance ( ).evaluateSql ( pQueryDialog->GetValue ( ) ) )
			{
				bValidQuery = true;
				// Valid sql...dialog creation...
	
				CyWxShowRequestDialog* pShowQueryDialog = new CyWxShowRequestDialog ( 
					this,
					new CyWxShowRequestMediator ( new CyUserQuerySqlBuilder ( pQueryDialog->GetValue ( ) ) ) );
	
				pShowQueryDialog->Show ( true );
			}
			else
			{
				// invalid sql. The error message is show.
				wxMessageBox ( CyGetText::getInstance ( ).getText ( "CyWxBudgetsFrame.onQuery.QueryError" ) + CySqliteDb::getInstance ( ).getLastError ( ) );
			}
		}
		else
		{
			bValidQuery = true;
		}
	}

	pQueryDialog->Destroy ( );
}

/* ---------------------------------------------------------------------------- */

void CyWxBudgetsFrame::onAccounts ( wxCommandEvent& )
{
	if ( this->isDbOpen ( ) )
	{
		CyWxShowRequestDialog* pAccountDialog = new CyWxShowRequestDialog ( 
			this,
			new CyWxShowRequestAccountsMediator ( new CyAccountsSqlBuilder ) );
	
		pAccountDialog->Show ( true );
	}

}

/* ---------------------------------------------------------------------------- */

void CyWxBudgetsFrame::onBudgets ( wxCommandEvent& )
{
	if ( this->isDbOpen ( ) )
	{
		CyWxShowRequestDialog* pBudgetsDialog = new CyWxShowRequestDialog ( 
			this, 
			new CyWxShowRequestBudgetsMediator ( new CyBudgetsSqlBuilder ) );

		pBudgetsDialog->Show ( true );
	}
}

/* ---------------------------------------------------------------------------- */

void CyWxBudgetsFrame::onAttributions ( wxCommandEvent& )
{
	if ( this->isDbOpen ( ) )
	{
		CyWxShowRequestDialog* pAttributionsDialog = new CyWxShowRequestDialog ( 
			this,
			new CyWxShowRequestAttributionsMediator ( new CyAttributionsSqlBuilder ) );

		pAttributionsDialog->Show ( true );
	}
}

/* ---------------------------------------------------------------------------- */

void CyWxBudgetsFrame::onAttributionsGroups ( wxCommandEvent& )
{
	if ( this->isDbOpen ( ) )
	{
		CyWxShowRequestDialog* pAttributionsGroupsDialog = new CyWxShowRequestDialog ( 
			this, 
			new CyWxShowRequestAttributionsGroupsMediator ( new CyAttributionsGroupsSqlBuilder ) );

		pAttributionsGroupsDialog->Show ( true );
	}
}

/* ---------------------------------------------------------------------------- */

void CyWxBudgetsFrame::onOperationsWithoutAttribution ( wxCommandEvent& )
{
	if ( this->isDbOpen ( ) )
	{
		CyWxShowRequestDialog* pOperationsDialog = new CyWxShowRequestDialog (
			this, 
			new CyWxShowRequestOperationsMediator ( new CyOperationsSqlBuilder ( ) ) );

		pOperationsDialog->Show ( true );
	}
}

/* ---------------------------------------------------------------------------- */

void CyWxBudgetsFrame::onOperations ( wxCommandEvent& )
{
	if ( this->isDbOpen ( ) )
	{
		CyWxShowRequestDialog* pOperationsDialog = new CyWxShowRequestDialog (
			this, 
			new CyWxShowRequestOperationsMediator (
				new CyOperationsSqlBuilder (  
					this->m_pAccountComboBox->GetValue ( ),
					dynamic_cast < CyWxLongLongItemData* > ( this->m_pAccountComboBox->GetClientObject ( static_cast < unsigned int > ( this->m_pAccountComboBox->GetSelection ( ) ) ) )->getValue ( ),
					this->m_pStartDateCtrl->GetValue ( ),
					this->m_pEndDateCtrl->GetValue ( ) ) ) );

		pOperationsDialog->Show ( true );
	}
}

/* ---------------------------------------------------------------------------- */

void CyWxBudgetsFrame::onAccountsBalance ( wxCommandEvent& )
{
	// testing if the db is opened
	if ( this->isDbOpen ( ) )
	{
		CyWxShowRequestDialog* pAccountsBalanceDialog = new CyWxShowRequestDialog (
			this, 
			new CyWxShowRequestMediator ( 
				new CyAccountsBalanceSqlBuilder ( dynamic_cast < CyWxLongLongItemData* > ( this->m_pAccountComboBox->GetClientObject ( static_cast < unsigned int > ( this->m_pAccountComboBox->GetSelection ( ) ) ) )->getValue ( ) ) ) );

		pAccountsBalanceDialog->Show ( true );
	}
}

/* ---------------------------------------------------------------------------- */

void CyWxBudgetsFrame::onAnalyse ( wxCommandEvent& )
{
	// testing if the db is opened
	if ( this->isDbOpen ( ) )
	{
		CyWxShowRequestDialog* pAnalyseDialog = new CyWxShowRequestDialog (
			this, 
			new CyWxShowRequestAnalyseMediator (
				new CyAnalyseSqlBuilder ( 
					dynamic_cast < CyWxLongLongItemData* > ( this->m_pBudgetComboBox->GetClientObject ( static_cast < unsigned int > ( this->m_pBudgetComboBox->GetSelection ( ) ) ) )->getValue ( ),
					this->m_pStartDateCtrl->GetValue ( ) ,
					this->m_pEndDateCtrl->GetValue ( ) ) ) );

		pAnalyseDialog->Show ( true );
	}
}

/* ---------------------------------------------------------------------------- */

void CyWxBudgetsFrame::onImport ( wxCommandEvent& )
{
	// testing if the db is opened
	if ( ! this->isDbOpen ( ) )
	{
		return;
	}

	// import
	CyIngImportTool objImportTool;
		wxFileDialog csvFileDialog ( 
		this, 
		CyGetText::getInstance ( ).getText ( "CyIngImportTool.import.SelectFile" ),
		wxFileSelectorPromptStr,
		wxEmptyString,
		wxString ( "CSV files (*.csv)|*.csv" ),
		wxFD_OPEN | wxFD_FILE_MUST_EXIST );
	if (wxID_CANCEL == csvFileDialog.ShowModal ( ) )
	{
		return;
	}


	CyIngImportTool::ImportError eImportError = objImportTool.import ( csvFileDialog.GetPath ( ), &CyWxBudgetsFrame::displayMessage );

	switch ( eImportError )
	{
	case CyIngImportTool::kImportOk:
		break;
	case CyIngImportTool::kImportErrorGetObjId:
		{
			wxMessageDialog* pErrorDialog = new wxMessageDialog (
				NULL,
				CyGetText::getInstance ( ).getText ( "CyIngImportTool.import.ErrorObjIdText" ), 
				CyGetText::getInstance ( ).getText ( "CyIngImportTool.import.ErrorObjIdCaption" ),
				wxOK | wxICON_EXCLAMATION | wxCENTRE );
			pErrorDialog->ShowModal ( );
			pErrorDialog->Destroy ( );
		}
		break;
	case CyIngImportTool::kImportErrorOpenFile:
		{
			wxMessageDialog* pErrorDialog = new wxMessageDialog (
				NULL,
				CyGetText::getInstance ( ).getText ( "CyIngImportTool.import.ErrorOpenFileText" ), 
				CyGetText::getInstance ( ).getText ( "CyIngImportTool.import.ErrorOpenFileCaption" ),
				wxOK | wxICON_EXCLAMATION | wxCENTRE );
			pErrorDialog->ShowModal ( );
			pErrorDialog->Destroy ( );
		}
		break;
	case CyIngImportTool::kImportErrorReadFile:
		{
			wxMessageDialog* pErrorDialog = new wxMessageDialog (
				NULL,
				CyGetText::getInstance ( ).getText ( "CyIngImportTool.import.ErrorReadingFileText" ), 
				CyGetText::getInstance ( ).getText ( "CyIngImportTool.import.ErrorReadingFileCaption" ),
				wxOK | wxICON_EXCLAMATION | wxCENTRE );
			pErrorDialog->ShowModal ( );
			pErrorDialog->Destroy ( );
		}
		break;
	default:
		break;
	}
}

/* ---------------------------------------------------------------------------- */

void CyWxBudgetsFrame::onAbout ( wxCommandEvent& )
{
	// Creation of the dialog information	
	wxAboutDialogInfo aboutInfo;
	aboutInfo.SetName ( CyWxVersionInfo::getInstance ( ).GetName ( ) );
	aboutInfo.SetVersion ( CyWxVersionInfo::getInstance ( ).getVersion( )  );
	aboutInfo.SetDescription ( CyWxVersionInfo::getInstance ( ).GetDescription ( ) );
	aboutInfo.SetCopyright ( CyWxVersionInfo::getInstance ( ).GetCopyright ( ) );
	aboutInfo.SetWebSite ( CyWxVersionInfo::getInstance ( ).getWebSite ( ) );

	// showing the dialog
	wxAboutBox ( aboutInfo );
}

/* ---------------------------------------------------------------------------- */

void CyWxBudgetsFrame::UpdateBudgets ( )
{
	// The 'budget' combo box is updated. This is needed when the user do a CRUD operation on the Budgets table 
	// or when another database is opened
	// first the Budget ObjId of the selected account is searched...
	long long lSelectedBudgetObjId = CyEnum::kInvalidObjId;
	if ( ! this->m_pBudgetComboBox->IsListEmpty ( ) )
	{
		CyWxLongLongItemData* pLongLongItemData =  dynamic_cast < CyWxLongLongItemData* > ( this->m_pBudgetComboBox->GetClientObject (
			static_cast < unsigned int > ( this->m_pBudgetComboBox->GetSelection ( ) ) ) );
		if ( NULL != pLongLongItemData )
		{
			lSelectedBudgetObjId = pLongLongItemData->getValue ( );
		}
	}

	// ...then all items are removed from the list
	this->m_pBudgetComboBox->Clear ( );

	if ( ! CySqliteDb::getInstance ( ).IsInitialized ( ) )
	{
		return;
	}

	// an empty string is first added to the list
	this->m_pBudgetComboBox->Append ( 
	wxString ( "" ), 
	new CyWxLongLongItemData ( CyEnum::kInvalidObjId ) );

	// Bugets are searched...
	CyQueryResult objBudgetsQueryResult;
	CyBudgetsSqlBuilder objBudgetsSqlBuilder;
	objBudgetsSqlBuilder.doSelect ( objBudgetsQueryResult );

	// and added to the list of the combo box
	long long lItemCounter = 1;
	long long lSelectedItem = 0;
	CyQueryResult::const_iterator iterator;
	for ( iterator = objBudgetsQueryResult.begin (); iterator != objBudgetsQueryResult.end ( ); ++ iterator )
	{
		long long lBudgetObjId = iterator->at ( CyBudgetsSqlBuilder::kBudgetObjId )->get ( CyLongValue::m_lDummyValue ) ;
		this->m_pBudgetComboBox->Append ( 
			iterator->at ( CyBudgetsSqlBuilder::kBudgetDescription )->getAsString ( ), 
			new CyWxLongLongItemData ( lBudgetObjId ) );
		if ( lSelectedBudgetObjId == lBudgetObjId )
		{
			lSelectedItem = lItemCounter;
		}
		++ lItemCounter;
	}

	// the previously selected budget is reselected
	this->m_pBudgetComboBox->Select ( static_cast < int > ( lSelectedItem ) );
}

/* ---------------------------------------------------------------------------- */

void CyWxBudgetsFrame::UpdateAccounts ( )
{
	// The 'Account' combo box is updated. This is needed when the user do a CRUD operation on the Accounts table
	// or when another database is opened
	// first the Account ObjId of the selected account is searched...
	long long lSelectedAccountObjId = CyEnum::kInvalidObjId;
	if ( ! this->m_pAccountComboBox->IsListEmpty ( ) )
	{
		CyWxLongLongItemData* pLongLongItemData =  dynamic_cast < CyWxLongLongItemData* > ( this->m_pAccountComboBox->GetClientObject (
			static_cast < unsigned int > ( this->m_pAccountComboBox->GetSelection ( ) ) ) );
		if ( NULL != pLongLongItemData )
		{
			lSelectedAccountObjId = pLongLongItemData->getValue ( );
		}
	}

	// ...then all items are removed from the list
	this->m_pAccountComboBox->Clear ( );

	if ( ! CySqliteDb::getInstance ( ).IsInitialized ( ) )
	{
		return;
	}

	// an empty string is first added to the list
	this->m_pAccountComboBox->Append ( 
	wxString ( "" ), 
	new CyWxLongLongItemData ( CyEnum::kInvalidObjId ) );

	// Accounts are searched...
	CyQueryResult objAccountsQueryResult;
	wxDateTime objToday;
	objToday.SetToCurrent ( );
	CyAccountsSqlBuilder objAccountsSqlBuilder ( objToday );
	objAccountsSqlBuilder.doSelect ( objAccountsQueryResult );

	// and added to the list of the combo box
	long long lItemCounter = 1;
	long long lSelectedItem = 0;
	CyQueryResult::const_iterator iterator;
	for ( iterator = objAccountsQueryResult.begin (); iterator != objAccountsQueryResult.end ( ); ++ iterator )
	{
		long long lAccountObjId = iterator->at ( CyAccountsSqlBuilder::kAccountObjId )->get ( CyLongValue::m_lDummyValue ) ;
		this->m_pAccountComboBox->Append ( 
			iterator->at ( CyAccountsSqlBuilder::kAccountNumber )->getAsString ( ), 
			new CyWxLongLongItemData ( lAccountObjId ) );
		if ( lSelectedAccountObjId == lAccountObjId )
		{
			lSelectedItem = lItemCounter;
		}
		++ lItemCounter;
	}

	// the previously selected account is reselected
	this->m_pAccountComboBox->Select ( static_cast < int > ( lSelectedItem ) );
}

/* ---------------------------------------------------------------------------- */

wxDateTime CyWxBudgetsFrame::getStartDate ( ) const
{
	return this->m_pStartDateCtrl->GetValue ( );
}

/* ---------------------------------------------------------------------------- */

wxDateTime CyWxBudgetsFrame::getEndDate ( ) const
{
	return this->m_pEndDateCtrl->GetValue ( );
}

/* ---------------------------------------------------------------------------- */

bool CyWxBudgetsFrame::isDbOpen ( )
{
	if ( ! CySqliteDb::getInstance ( ).IsInitialized ( ) )
	{
		wxMessageDialog* pErrorDialog = new wxMessageDialog (
			NULL,
			CyGetText::getInstance ( ).getText ( "CyWxBudgetsFrame.isDbOpen.ErrorDbText" ), 
			CyGetText::getInstance ( ).getText ( "CyWxBudgetsFrame.isDbOpen.ErrorDbCaption" ),
			wxOK | wxICON_EXCLAMATION | wxCENTRE );
		pErrorDialog->ShowModal ( );
		pErrorDialog->Destroy ( );
		return false;
	}

	return true;
}

/* ---------------------------------------------------------------------------- */

