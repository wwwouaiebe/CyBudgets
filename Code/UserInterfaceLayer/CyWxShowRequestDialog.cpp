/* ---------------------------------------------------------------------------- */
//! CyWxShowRequestDialog.cpp
/* ---------------------------------------------------------------------------- */
//!
//! \file CyWxShowRequestDialog.cpp
//! \brief definition file for class CyWxShowRequestDialog
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

#include "UserInterfaceLayer/CyWxShowRequestDialog.h"
#include "UserInterfaceLayer/CyWxShowRequestMediator.h"
#include "DataLayer/CyValue.h"
#include "UtilitiesLayer/CyEnum.h"

/* ---------------------------------------------------------------------------- */

CyWxShowRequestDialog::CyWxShowRequestDialog ( 
			wxWindow *pParent, 
			CyWxShowRequestMediator* pWxShowRequestMediator ) :
	wxDialog ( 
		pParent, 
		-1, 
		wxEmptyString, 
		wxPoint ( CyEnum::kLeft, CyEnum::kTop ), 
		wxSize ( CyEnum::kWindowWidth, CyEnum::kWindowHeight ), 
		wxRESIZE_BORDER | wxCLOSE_BOX | wxMAXIMIZE_BOX | wxMINIMIZE_BOX | wxCAPTION),
	m_pWxShowRequestMediator ( pWxShowRequestMediator ),
	m_iCurrentRow ( 0 )
{
	//Mediator initialization
	this->m_pWxShowRequestMediator->setDialog ( this );

	// dialog title
	this->SetTitle ( this->m_pWxShowRequestMediator->getDialogTitle ( ) );

	// data are searched in the db
	this->m_pWxShowRequestMediator->select ( m_objQueryResult );

	// A sizer is created...
	wxBoxSizer* pBoxSizer = new wxStaticBoxSizer (
		wxVERTICAL,
		this,
		wxEmptyString );

	// and a grid created
	this->m_pGrid = new wxGrid ( this, -1,wxDefaultPosition,wxDefaultSize );
	this->m_pGrid->CreateGrid ( 0, static_cast < int > ( m_objQueryResult.getHeaders ( ).size ( ) - this->m_pWxShowRequestMediator->getHiddenColumns ( ) ) );

	// loop on the data header
	std::vector < wxString >::const_iterator headerIterator;
	int iHeaderCounter = 0;
	for ( headerIterator = m_objQueryResult.getHeaders ( ).begin ( ) + this->m_pWxShowRequestMediator->getHiddenColumns ( );
		  headerIterator != m_objQueryResult.getHeaders ( ).end ( );
		  ++ headerIterator )
	{
		this->m_pGrid->SetColLabelValue ( iHeaderCounter, *headerIterator );
		++ iHeaderCounter;
	}

	// loop on the data
	CyQueryResult::const_iterator rowIterator;
	int iRow = 0;
	for ( rowIterator = m_objQueryResult.begin ( ); rowIterator != m_objQueryResult.end ( ); ++ rowIterator )
	{
		this->m_pGrid->AppendRows ( 1 );
		this->displayGridRow ( iRow, *rowIterator );
		++ iRow;
	}

	// the grid is rearanged
	this->m_pGrid->AutoSize ( );
	this->m_pGrid->EnableEditing ( false );
	// and added to the sizer
	pBoxSizer->Add (  this->m_pGrid, 1, wxEXPAND, 5 );
	this->SetSizer ( pBoxSizer );

	// Events...
	this->Connect (
		this->m_pGrid->GetId ( ),
		wxEVT_GRID_CELL_RIGHT_CLICK,
		wxGridEventHandler ( CyWxShowRequestDialog::onRightClickGrid ) );
	this->Connect (
		this->m_pGrid->GetId ( ),
		wxEVT_GRID_CELL_LEFT_DCLICK,
		wxGridEventHandler ( CyWxShowRequestDialog::onDoubleLeftClickGrid ) );
	this->Connect (
		this->m_pGrid->GetId ( ),
		wxEVT_GRID_LABEL_LEFT_DCLICK,
		wxGridEventHandler ( CyWxShowRequestDialog::onDoubleLeftClickLabel ) );
	this->Connect ( 
		wxEVT_CLOSE_WINDOW,
		wxCloseEventHandler ( CyWxShowRequestDialog::OnClose ) );
}

/* ---------------------------------------------------------------------------- */

void CyWxShowRequestDialog::displayGridRow ( int iRow, const CyQueryResult::CyQueryResultValuesRow& objQueryResultValuesRow )
{
	std::vector < CyValue* >::const_iterator valueIterator;
	int iColumn = 0;
	for ( valueIterator = objQueryResultValuesRow.begin ( ) +this->m_pWxShowRequestMediator->getHiddenColumns ( ); valueIterator != objQueryResultValuesRow.end ( ); ++ valueIterator )
	{
		if ( ( CyNoFormat != ( *valueIterator )->getHorizontalAlignment ( ) ) || ( CyNoFormat != ( *valueIterator )->getVerticalAlignment ( ) ) )
		{
			int iHorizontalAlignment = wxALIGN_LEFT;
			switch ( ( *valueIterator )->getHorizontalAlignment ( ) )
			{
			case CyHorizontalAlignmentLeft:
				iHorizontalAlignment = wxALIGN_LEFT;
				break;
			case CyHorizontalAlignmentCenter:
				iHorizontalAlignment = wxALIGN_CENTRE;
				break;
			case CyHorizontalAlignmentRight:
				iHorizontalAlignment = wxALIGN_RIGHT;
				break;
			}

			int iVerticalAlignment = wxALIGN_LEFT;
			switch ( ( *valueIterator )->getVerticalAlignment ( ) )
			{
			case CyVerticalAlignmentBottom:
				iVerticalAlignment = wxALIGN_BOTTOM;
				break;
			case CyVerticalAlignmentCenter:
				iVerticalAlignment = wxALIGN_CENTRE;
				break;
			case CyVerticalAlignmentTop:
				iVerticalAlignment = wxALIGN_TOP;
				break;
			}
			this->m_pGrid->SetCellAlignment ( iRow, iColumn, iHorizontalAlignment, iVerticalAlignment );
		}

		if ( CyNoFormat != ( *valueIterator )->getForegroundColor ( ) )
		{
			const wxColour* pForegroundColor = wxBLACK;
			switch ( ( *valueIterator )->getForegroundColor ( ) )
			{
			case CyForegroundBlue:
				pForegroundColor = wxBLUE;
				break;
			case CyForegroundCyan:
				pForegroundColor = wxCYAN;
				break;
			case CyForegroundGreen:
				pForegroundColor = wxGREEN;
				break;
			case CyForegroundYellow:
				pForegroundColor = wxYELLOW;
				break;
			case CyForegroundRed:
				pForegroundColor = wxRED;
				break;
			case CyForegroundBlack:
				pForegroundColor = wxBLACK;
				break;
			case CyForegroundGrey:
				pForegroundColor = wxLIGHT_GREY;
				break;
			case CyForegroundWhite:
				pForegroundColor = wxWHITE;
				break;
			}

			this->m_pGrid->SetCellTextColour (  iRow, iColumn, *pForegroundColor );
		}
		if ( CyNoFormat != ( *valueIterator )->getBackgroundColor ( ) )
		{
			const wxColour* pBackgroundColor = wxBLACK;
			switch ( ( *valueIterator )->getBackgroundColor ( ) )
			{
			case CyBackgroundBlue:
				pBackgroundColor = wxBLUE;
				break;
			case CyBackgroundCyan:
				pBackgroundColor = wxCYAN;
				break;
			case CyBackgroundGreen:
				pBackgroundColor = wxGREEN;
				break;
			case CyBackgroundYellow:
				pBackgroundColor = wxYELLOW;
				break;
			case CyBackgroundRed:
				pBackgroundColor = wxRED;
				break;
			case CyBackgroundBlack:
				pBackgroundColor = wxBLACK;
				break;
			case CyBackgroundGrey:
				pBackgroundColor = wxLIGHT_GREY;
				break;
			case CyBackgroundWhite:
				pBackgroundColor = wxWHITE;
				break;
			}

			this->m_pGrid->SetCellBackgroundColour (  iRow, iColumn, *pBackgroundColor );
		}

		wxFont gridFont = this->m_pGrid->GetFont ( );
		if ( (*valueIterator)->isFontBold ( ) )
		{
			gridFont = gridFont.Bold ( );
			this->m_pGrid->SetCellFont ( iRow, iColumn, gridFont );
		}
		if ( (*valueIterator)->isFontItalic ( ) )
		{
			gridFont = gridFont.Italic ( );
			this->m_pGrid->SetCellFont ( iRow, iColumn, gridFont );
		}
		if ( (*valueIterator)->isFontUnderlined ( ) )
		{
			gridFont = gridFont.Underlined ( );
			this->m_pGrid->SetCellFont ( iRow, iColumn, gridFont );
		}


		this->m_pGrid->SetCellValue ( iRow, iColumn, (*valueIterator)->getAsString ( ) );
		++ iColumn;
	}
}

/* ---------------------------------------------------------------------------- */

CyWxShowRequestDialog::~CyWxShowRequestDialog ( )
{
	this->Disconnect (
		m_pGrid->GetId ( ),
		wxEVT_GRID_CELL_RIGHT_CLICK,
		wxGridEventHandler ( CyWxShowRequestDialog::onRightClickGrid ) );
	this->Disconnect (
		m_pGrid->GetId ( ),
		wxEVT_GRID_CELL_LEFT_DCLICK,
		wxGridEventHandler ( CyWxShowRequestDialog::onDoubleLeftClickGrid ) );
	this->Disconnect (
		this->m_pGrid->GetId ( ),
		wxEVT_GRID_LABEL_LEFT_DCLICK,
		wxGridEventHandler ( CyWxShowRequestDialog::onDoubleLeftClickLabel ) );
	this->Disconnect ( 
		wxEVT_CLOSE_WINDOW,
		wxCloseEventHandler ( CyWxShowRequestDialog::OnClose ) );

	delete this->m_pWxShowRequestMediator;
}

/* ---------------------------------------------------------------------------- */

void CyWxShowRequestDialog::refreshGrid ( )
{
	if ( 0 < this->m_pGrid->GetNumberRows ( ) )
	{
		// old data are removed from the grid
		this->m_pGrid->DeleteRows (0, this->m_pGrid->GetNumberRows ( ) );
	}

	// the query is restarted
	this->m_pWxShowRequestMediator->select ( m_objQueryResult );
	
	// and added to the grid
	CyQueryResult::const_iterator rowIterator;
	int iRow = 0;
	for ( rowIterator = m_objQueryResult.begin ( ); rowIterator != m_objQueryResult.end ( ); ++ rowIterator )
	{
		this->m_pGrid->AppendRows ( 1 );
		this->displayGridRow ( iRow, *rowIterator );
		++ iRow;
	}
}

/* ---------------------------------------------------------------------------- */

void CyWxShowRequestDialog::OnClose( wxCloseEvent& )
{
	this->Destroy ( );
}

/* ---------------------------------------------------------------------------- */

void CyWxShowRequestDialog::onDoubleLeftClickLabel ( wxGridEvent& )
{
	this->m_pWxShowRequestMediator->onDoubleLeftClickLabel ( );
}

/* ---------------------------------------------------------------------------- */

void CyWxShowRequestDialog::onDoubleLeftClickGrid ( wxGridEvent& event )
{
	m_iCurrentRow = event.GetRow ( );
	this->m_pWxShowRequestMediator->onDoubleLeftClickGrid ( );
}

/* ---------------------------------------------------------------------------- */

void CyWxShowRequestDialog::onRightClickGrid ( wxGridEvent& event )
{
	m_iCurrentRow = event.GetRow ( );
	wxMenu objMenu;

	if ( this->m_pWxShowRequestMediator->addPopupItems ( objMenu ) )
	{
		objMenu.Connect (
			wxEVT_COMMAND_MENU_SELECTED,
			( wxObjectEventFunction ) &CyWxShowRequestDialog::onPopupRightClickGrid,
			NULL,
			this );

		this->PopupMenu ( &objMenu );

		objMenu.Disconnect (
			wxEVT_COMMAND_MENU_SELECTED,
			( wxObjectEventFunction ) &CyWxShowRequestDialog::onPopupRightClickGrid,
			NULL,
			this );
	}
}

/* ---------------------------------------------------------------------------- */

void CyWxShowRequestDialog::onPopupRightClickGrid ( wxCommandEvent& event )
{
	this->m_pWxShowRequestMediator->onPopupRightClickGrid ( event );
}

/* ---------------------------------------------------------------------------- */

size_t CyWxShowRequestDialog::getNumberRows ( ) const
{
	return 	this->m_objQueryResult.size ( );
}

/* ---------------------------------------------------------------------------- */

CyQueryResult::CyQueryResultValuesRow& CyWxShowRequestDialog::getCurrentRow ( )
{
	return this->m_objQueryResult.at ( static_cast < size_t > ( this->m_iCurrentRow ) );
}

/* ---------------------------------------------------------------------------- */

void CyWxShowRequestDialog::refreshCurrentRow ( )
{
	this->displayGridRow (  this->m_iCurrentRow, this->m_objQueryResult.at ( static_cast < size_t > ( this->m_iCurrentRow ) ) );
}

/* ---------------------------------------------------------------------------- */
