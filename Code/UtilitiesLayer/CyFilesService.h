/* ---------------------------------------------------------------------------- */
//! CyFilesService.h
/* ---------------------------------------------------------------------------- */
//!
//! \file CyFilesService.h
//! \brief header file for class CyFilesService
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

//!
//! \class CyFilesService
//! \brief Classe de base abstraite proposant des méthodes pour la gestion des fichiers
//! Il faut utiliser la classe CyServicesManager pour obtenir une référence vers cette classe.
//!
//! \version 1.0.3
//! Methods are not anymore inlined
//!
class CyFilesService
{
	public:

		//! \fn getMessagesPath ( ) const
		//! \return le répertoire où sont stockés les fichiers de traduction des messages
		wxString getMessagesPath ( ) const;

		//! \fn getResourcesPath ( ) const
		//! \return le répertoire où sont stockés les fichiers de resources
		wxString getResourcesPath ( ) const;

		//! \fn getMessagesFiles ( ) const
		//! This method search all the.po files with messages
		//! \return an array with the file names

		wxArrayString getMessagesFiles ( ) const;

		//! \fn setPaths ( wxString strExePath )
		//! Cette méthode crée les chemins d'accès aux différents fichiers utilisés par l'application
		//! @param [ in ] strExePath le nom et le chemin d'accès à l'exécutable donné
		//! en premier paramètre par le système d'exploitation

		void setPaths ( wxString strExePath );

		//! \fn getInstance ( )
		//! \return a reference to the one and only one object of the class
		static CyFilesService& getInstance ( );

	protected:

		//! \fn CyFilesService ( )
		//! constructeur
		CyFilesService ( );

		//! \fn ~CyFilesService ( )
		//!destructeur
		virtual ~CyFilesService ( );

		//! \fn CyFilesService ( const CyFilesService& objFilesService )
		//! constructeur de recopie
		//! @param [ in ] objFilesService l'objet à copier
		CyFilesService ( const CyFilesService& objFilesService );

		//! \fn operator = ( const CyFilesService& objFilesService )
		//! opérateur =
		//! @param [ in ] objFilesService
		//! \return
		CyFilesService& operator = ( const CyFilesService& objFilesService );

	private:

		//! \var m_strMessagesPath
		//! a string where the path of the message files are stored

		wxString  m_strMessagesPath;

		//! \var m_strResourcesPath
		//! a string where the path of the resources files are stored

		wxString m_strResourcesPath;

		//! \var m_objFileService
		//! the one and only one instance of the class

		static CyFilesService m_objFileService;

};

/* ---------------------------------------------------------------------------- */
