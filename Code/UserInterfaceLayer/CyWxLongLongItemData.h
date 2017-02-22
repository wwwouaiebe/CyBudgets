/* ---------------------------------------------------------------------------- */
//! CyWxLongLongItemData.h
/* ---------------------------------------------------------------------------- */
//!
//! \file CyWxLongLongItemData.h
//! \brief header file for class CyWxLongLongItemData
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

//! \class CyWxLongLongItemData
//! \brief overload of the class wxTreeItemData used to store the Attribution ObjId
//! in the tree view of the CyWxEditOperationAttributionDialog
//!

class CyWxLongLongItemData : public wxClientData
{

	public:

		//! \fn CyWxLongLongItemData ( long long lValue )
		//! @param [ in ] lValue the value to store in the object
		//!
		//! constructor

		explicit CyWxLongLongItemData ( long long lValue );

		//! \fn ~CyWxLongLongItemData ( ) 
		//! destructor

		virtual ~CyWxLongLongItemData ( );

		//! \fn getValue ( )
		//! get method
		//!
		//! \return the value stored in the Item data of the corresponding tree item

		const long long & getValue ( ) const;

	private:

		//! \fn CyWxLongLongItemData ( const CyWxLongLongItemData& ) 
		//! copy constructor
		//! \return a reference to a CyWxLongLongItemData object
		//! not implemented

		CyWxLongLongItemData ( const CyWxLongLongItemData& );

		//! \fn operator = ( const CyWxLongLongItemData& ) 
		//! operator =
		//! \return a reference to a CyWxLongLongItemData object
		//! not implemented

		CyWxLongLongItemData& operator = ( const CyWxLongLongItemData& );

		//! \var m_lValue
		//! the value stored in the Item data of the corresponding tree item

		long long m_lValue;
};
