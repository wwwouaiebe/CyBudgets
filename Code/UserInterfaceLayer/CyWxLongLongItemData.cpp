/* ---------------------------------------------------------------------------- */
//! CyWxLongLongItemData.cpp
/* ---------------------------------------------------------------------------- */
//!
//! \file CyWxLongLongItemData.cpp
//! \brief definition file for class CyWxLongLongItemData
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

#include "UserInterfaceLayer/CyWxLongLongItemData.h"

/* ---------------------------------------------------------------------------- */

CyWxLongLongItemData::CyWxLongLongItemData ( long long lValue ) :
	wxClientData ( ),
		m_lValue ( lValue )
{
}

/* ---------------------------------------------------------------------------- */

CyWxLongLongItemData::~CyWxLongLongItemData ( )
{
}

/* ---------------------------------------------------------------------------- */

const long long& CyWxLongLongItemData::getValue ( ) const
{
	return this->m_lValue;
}

/* ---------------------------------------------------------------------------- */

