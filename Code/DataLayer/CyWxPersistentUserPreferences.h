/* ---------------------------------------------------------------------------- */
//! CyWxPersistentUserPreferences.h
/* ---------------------------------------------------------------------------- */
//!
//! \file CyWxPersistentUserPreferences.h
//! \brief header file for class CyWxPersistentUserPreferences
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

#include "DataLayer/CyUserPreferences.h"

/* ---------------------------------------------------------------------------- */

//! \class CyWxPersistentUserPreferences
//! \brief this implements the persistance for the CyUserPreferences class
//!
//! This class is based on the "Singleton" design pattern
//!
//! \since version 1.1.0
//!

class CyWxPersistentUserPreferences : public  wxPersistentObject
{
	public:

		//! \fn CyWxPersistentUserPreferences ( CyUserPreferences* pUserPreferences ) 
		//! @param [ in ] pUserPreferences a pointer to the one and only one CyUserPreferences object
		//!
		//! constructor

		CyWxPersistentUserPreferences ( CyUserPreferences* pUserPreferences );

		//! \fn GetKind ( ) const
		//! overload of the wxPersistentObject::GetKind ( ) method
		//! \return the category used for the persistence

		virtual wxString GetKind ( ) const;

		//! \fn GetName ( ) const
		//! overload of the wxPersistentObject::GetName ( ) method
		//! \return the name used for the persistence

		virtual wxString GetName ( ) const;

		//! \fn Restore ( ) 
		//! overload of the wxPersistentObject::Restore ( ) method
		//! \return true when the preferences are correctly saved

		virtual bool Restore ( );

		//! \fn Save ( ) const
		//! overload of the wxPersistentObject::Save ( ) method

		void Save ( ) const;

		//! \fn Get ( ) const
		//! overload of the wxPersistentObject::Get ( ) method
		//! \return a pointer to the associated CyUserPreferences object

		CyUserPreferences* Get ( ) const;

	private:

		//! \fn CyWxPersistentUserPreferences ( const CyWxPersistentUserPreferences& ) 
		//! copy constructor
		//! not implemented

		CyWxPersistentUserPreferences ( const CyWxPersistentUserPreferences& );

		//! \fn operator = ( const CyWxPersistentUserPreferences& ) 
		//! operator =
		//! \return a reference to a CyWxPersistentUserPreferences object
		//! not implemented

		CyWxPersistentUserPreferences& operator = ( const CyWxPersistentUserPreferences& );

};

/* ---------------------------------------------------------------------------- */

//! \fn wxCreatePersistentObject ( CyUserPreferences* pUserPreferences )
//! @param [ in ] pUserPreferences a pointer to the one and only one CyUserPreference object for witch the persistence is created 
//!
//! overload of the wxWidgets wxCreatePersistentObject function for CyUserPreferences
//! \return a pointer to an CyWxPersistentUserPreferences object managing the object pointed by pUserPreferences

wxPersistentObject *wxCreatePersistentObject ( CyUserPreferences* pUserPreferences );

/* ---------------------------------------------------------------------------- */
