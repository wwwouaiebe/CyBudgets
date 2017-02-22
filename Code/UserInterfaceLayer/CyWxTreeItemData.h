/* ---------------------------------------------------------------------------- */
//! CyWxTreeItemData.h
/* ---------------------------------------------------------------------------- */
//!
//! \file CyWxTreeItemData.h
//! \brief header file for class CyWxTreeItemData
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

//! \class CyWxTreeItemData
//! \brief overload of the class wxTreeItemData used to store the Attribution ObjId
//! in the tree view of the CyWxEditOperationAttributionDialog
//!

class CyWxTreeItemData : public wxTreeItemData
{

	public:

		//! \fn CyWxTreeItemData ( size_t position )
		//! @param [ in ] position of the ObjId of the corresponding tree item
		//!
		//! constructor

		explicit CyWxTreeItemData ( size_t position );

		//! \fn ~CyWxTreeItemData ( ) 
		//! destructor

		virtual ~CyWxTreeItemData ( );

		//! \fn getPosition ( )
		//! get method
		//!
		//! \return the ObjId of the corresponding tree item

		const size_t& getPosition ( ) const;

	private:

		//! \fn CyWxTreeItemData ( const CyWxTreeItemData& ) 
		//! copy constructor
		//! not implemented

		CyWxTreeItemData ( const CyWxTreeItemData&);

		//! \fn operator = ( const CyWxTreeItemData& ) 
		//! operator =
		//! \return a reference to a CyWxTreeItemData object
		//! not implemented

		CyWxTreeItemData& operator = ( const CyWxTreeItemData& );

		//! \var m_Position
		//! store the position of the corresponding tree item

		size_t m_Position;
};
