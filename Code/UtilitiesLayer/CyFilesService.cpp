/* ---------------------------------------------------------------------------- */
//! CyFilesService.cpp
/* ---------------------------------------------------------------------------- */
//!
//! \file CyFilesService.cpp
//! \brief definition file for class CyFilesService
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

#include "UtilitiesLayer/CyFilesService.h"

/* ---------------------------------------------------------------------------- */

CyFilesService CyFilesService::m_objFileService;

/* ---------------------------------------------------------------------------- */

CyFilesService::CyFilesService ( )
{
}

/* ---------------------------------------------------------------------------- */

CyFilesService::~CyFilesService ( )
{
}

/* ---------------------------------------------------------------------------- */

void CyFilesService::setPaths ( wxString strExePath )
{
	wxFileName objMainPath (
		wxFileName ( strExePath ).GetPath ( true )
		+ wxString ( L".." )
		+ wxFileName::GetPathSeparator ( ) );
	objMainPath.Normalize (  );

	wxFileName objMessagesPath (
		objMainPath.GetFullPath ( )
		+ wxString ( L"messages" )
		+ wxFileName::GetPathSeparator ( ) );

	this->m_strMessagesPath = objMessagesPath.GetFullPath ( );

	wxFileName objResourcesPath (
		objMainPath.GetFullPath ( )
		+ wxString ( L"resources" )
		+ wxFileName::GetPathSeparator ( ) );

	this->m_strResourcesPath = objResourcesPath.GetFullPath ( );
}

/* ---------------------------------------------------------------------------- */

CyFilesService& CyFilesService::getInstance ( )
{
	return m_objFileService;
}

/* ---------------------------------------------------------------------------- */

wxString CyFilesService::getMessagesPath ( ) const
{
	return this->m_strMessagesPath ;
}

/* ---------------------------------------------------------------------------- */

wxString CyFilesService::getResourcesPath ( ) const
{
	return this->m_strResourcesPath ;
}

/* ---------------------------------------------------------------------------- */

wxArrayString CyFilesService::getMessagesFiles ( )const
{
	wxArrayString strFilesArray;
	wxFileSystem objFileSystem;
	objFileSystem.ChangePathTo ( this->getMessagesPath ( ) );
	wxString strFileName = objFileSystem.FindFirst ( wxString ( "*.po" ) ) ;
	do 
	{
		wxFileName objFileName ( strFileName );
		strFileName = objFileName.GetName ( );
		strFilesArray.Add ( strFileName );
		strFileName = objFileSystem.FindNext ( );
	}
	while ( ! strFileName.empty ( ) );
	strFilesArray.Sort ( );

	return strFilesArray;
}

/* ---------------------------------------------------------------------------- */
