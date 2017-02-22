/* ---------------------------------------------------------------------------- */
//! CyIngImportTool.h
/* ---------------------------------------------------------------------------- */
//!
//! \file CyIngImportTool.h
//! \brief header file for class CyIngImportTool
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

#include "UtilitiesLayer/CyStdIncludes.h"

/* ---------------------------------------------------------------------------- */

class wxString;

/* ---------------------------------------------------------------------------- */

//! \class CyIngImportTool
//! \brief import tool for the operations on an ING account
//!
//! This class is used to import the operations from an ING account with a CSV file
//!
//! \version 1.0.3
//! Added the ImportError enum
//! \version 1.0.3
//! Modified the import method:
//! - an error code is returned
//! - a callback parameter is added

class CyIngImportTool
{

	public:

		//! \fn CyIngImportTool ( ) 
		//! constructor

		CyIngImportTool ( );

		//! \fn ~CyIngImportTool ( ) 
		//! destructor

		~CyIngImportTool ( );

		//! \enum ImportError
		//! enumeration with the errors occuring during the import operations
		//!
		//! \var kImportOk
		//! import terminated correctly
		//!
		//! \var kImportErrorGetObjId
		//! An error occurs when asking an ObjId to the database
		//!
		//! \var kImportErrorOpenFile
		//! An error occurs when opening the import file
		//!
		//! \var kImportErrorReadFile
		//! An error occurs when reading the import file

		enum ImportError
		{
			kImportOk,
			kImportErrorGetObjId,
			kImportErrorOpenFile,
			kImportErrorReadFile
		};

		//! \fn import ( const wxString& strFileName, void ( callback ) ( const wxString & strMessage, const wxString& strCaption ) )
		//! @param [ in ] strFileName the filename to be imported
		//! @param [ in ] ( callback ) a callback function used when an error occurs
		//!
		//! this method import the operations from a .csv file to the SQLite database
		//! \return an error code from the enum ImportError

		ImportError import ( const wxString& strFileName, void ( callback ) ( const wxString & strMessage, const wxString& strCaption ) );

	private:

		//! \fn CyIngImportTool ( const CyIngImportTool& ) 
		//! copy constructor
		//! not implemented

		CyIngImportTool ( const CyIngImportTool& );

		//! \fn operator = ( const CyIngImportTool& ) 
		//! operator =
		//! \return a reference to a CyIngImportTool object
		//! not implemented

		CyIngImportTool& operator = ( const CyIngImportTool& );

		//! \fn getObjId ( wxString strTable )
		//! @param [ in ] strTable the table for witch the ObjId is searched
		//!
		//! This method search the next usable ObjId in a table
		//! \return the next usable ObjId or CyEnum::kInvalidObjId if no ObjId was found

		long long getObjId ( wxString strTable );

		//! \fn insertDetails ( const std::vector < std::string >& detailsVector )
		//! @param [ in ] detailsVector a vector with the details to insert
		//!
		//! this method insert the details for an operation in the OperationsDetails table
		//! \return true when the details are correctly loaded in the database

		bool insertDetails ( const std::vector < std::string >& detailsVector );

		//! \var m_lOperationObjId
		//! the ObjId used for the current operation

		long long m_lOperationObjId;

		//! \var m_lOperationDetailObjId
		//! the ObjId used for the current operation detail
		long long m_lOperationDetailObjId;

};