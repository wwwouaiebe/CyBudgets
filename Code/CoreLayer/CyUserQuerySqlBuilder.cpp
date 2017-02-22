/* ---------------------------------------------------------------------------- */
//! CyUserQuerySqlBuilder.cpp
/* ---------------------------------------------------------------------------- */
//!
//! \file CyUserQuerySqlBuilder.cpp
//! \brief definition file for class CyUserQuerySqlBuilder
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

#include "CoreLayer/CyUserQuerySqlBuilder.h"
#include "UtilitiesLayer/CyGetText.h"

/* ---------------------------------------------------------------------------- */

CyUserQuerySqlBuilder::CyUserQuerySqlBuilder ( const wxString& strUserQuery ):
	m_strUserQuery ( strUserQuery )
{
}

/* ---------------------------------------------------------------------------- */

CyUserQuerySqlBuilder::~CyUserQuerySqlBuilder ( )
{
}

/* ---------------------------------------------------------------------------- */

wxString CyUserQuerySqlBuilder::getDialogTitle ( ) const
{
	return CyGetText::getInstance ( ).getText ( "CyUserQuerySqlBuilder.getDialogTitle.QueryTitle" ) + wxString ( " - " ) + this->m_strUserQuery;
}

/* ---------------------------------------------------------------------------- */

wxString CyUserQuerySqlBuilder::getDeleteSql ( long long ) const
{
	return wxEmptyString;
}

/* ---------------------------------------------------------------------------- */

 wxString CyUserQuerySqlBuilder::getInsertSql ( const CyQueryResult::CyQueryResultValuesRow& ) const
{
	return wxEmptyString;
}

/* ---------------------------------------------------------------------------- */

void CyUserQuerySqlBuilder::createRow ( CyQueryResult::CyQueryResultValuesRow& ) const
{
}

/* ---------------------------------------------------------------------------- */

wxString CyUserQuerySqlBuilder::getSelectSql ( ) const
{
	return this->m_strUserQuery;
}

/* ---------------------------------------------------------------------------- */

wxString CyUserQuerySqlBuilder::getUpdateSql ( const CyQueryResult::CyQueryResultValuesRow& ) const
{
	return wxEmptyString;
}

/* ---------------------------------------------------------------------------- */

int CyUserQuerySqlBuilder::getHiddenColumns ( ) const
{
	return 0;
}

/* ---------------------------------------------------------------------------- */
