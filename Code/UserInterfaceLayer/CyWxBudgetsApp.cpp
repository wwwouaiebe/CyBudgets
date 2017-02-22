/* ---------------------------------------------------------------------------- */
//! CyWxBudgetsApp.cpp
/* ---------------------------------------------------------------------------- */
//!
//! \file CyWxBudgetsApp.cpp
//! \brief definition file for class CyWxBudgetsApp
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
#include "UtilitiesLayer/CyFilesService.h"

/* ---------------------------------------------------------------------------- */

CyWxBudgetsApp::CyWxBudgetsApp ( ):
	 m_pWxBudgetsFrame ( NULL )
{
}

/* ---------------------------------------------------------------------------- */

CyWxBudgetsApp::~CyWxBudgetsApp ( )
{
}

/* ---------------------------------------------------------------------------- */

bool CyWxBudgetsApp::OnInit()
{
	// Initializations...
	// ...of the CyFilesService unique object...
	CyFilesService::getInstance ( ).setPaths (  wxApp::argv[ 0 ] );

	// ... and of the wxWidget image handlers.
	wxInitAllImageHandlers();

	//The frame is created and displayed
	this->m_pWxBudgetsFrame = new CyWxBudgetsFrame ( );
	this->m_pWxBudgetsFrame->Show( true );

	return true;
}

/* ---------------------------------------------------------------------------- */

CyWxBudgetsFrame* CyWxBudgetsApp::getBudgetsFrame ( )
{
	return this->m_pWxBudgetsFrame;
}

/* ---------------------------------------------------------------------------- */

