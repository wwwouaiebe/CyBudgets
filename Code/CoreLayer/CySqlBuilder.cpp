/* ---------------------------------------------------------------------------- */
//! CySqlBuilder.cpp
/* ---------------------------------------------------------------------------- */
//!
//! \file CySqlBuilder.cpp
//! \brief definition file for class CySqlBuilder
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

#include "CoreLayer/CySqlBuilder.h"
#include "DataLayer/CySqliteDb.h"
#include "UtilitiesLayer/CyEnum.h"

/* ---------------------------------------------------------------------------- */

CySqlBuilder::CySqlBuilder ( )
{
}

/* ---------------------------------------------------------------------------- */

CySqlBuilder::~CySqlBuilder ( )
{
}

/* ---------------------------------------------------------------------------- */
	
const wxString CySqlBuilder::getFieldSql ( const wxString& strField, const wxString& strAlias, const wchar_t strValueType, bool bLastField /* = false */ ) const
{
	wxString strReturnValue = wxEmptyString;

	switch ( strValueType )
	{
	case CyFormatBoolean:
		strReturnValue
			<< wxString ( "\"" )
			<< CyStartFormat
			<< CyFormatBoolean
			<< wxString ( "\" AS " )
			<< CyStartFormat
			<< wxString ( ", " );
		break;
	case CyFormatCurrency:
		strReturnValue
			<< wxString ( "\"" )
			<< CyStartFormat
			<< CyFormatCurrency
			<< wxString ( "\" AS " )
			<< CyStartFormat
			<< wxString ( ", " );
		break;
	case CyFormatDate:
		strReturnValue
			<< wxString ( "\"" )
			<< CyStartFormat
			<< CyFormatDate
			<< wxString ( "\" AS " )
			<< CyStartFormat
			<< wxString ( ", " );
		break;
	case CyFormatHidden:
		strReturnValue
			<< wxString ( "\"" )
			<< CyStartFormat
			<< CyFormatHidden
			<< wxString ( "\" AS " )
			<< CyStartFormat
			<< wxString ( ", " );
		break;
	case CyFormatInteger:
		strReturnValue
			<< wxString ( "\"" )
			<< CyStartFormat
			<< CyFormatInteger
			<< wxString ( "\" AS " )
			<< CyStartFormat
			<< wxString ( ", " );
		break;
	case CyFormatString:
		strReturnValue
			<< wxString ( "\"" )
			<< CyStartFormat
			<< CyFormatString
			<< wxString ( "\" AS " )
			<< CyStartFormat
			<< wxString ( ", " );
		break;
	default:
		break;
	}
	strReturnValue << strField;
	if ( ! strAlias.empty ( ) )
	{
		strReturnValue << wxString ( " AS \"" ) << strAlias << wxString ( "\"" );
	}
	if ( ! bLastField )
	{
		strReturnValue << wxString ( ", ");
	}
	else
	{
		strReturnValue << wxString ( " ");
	}

	return strReturnValue;
}

/* ---------------------------------------------------------------------------- */
	
void CySqlBuilder::doSelect ( CyQueryResult& objQueryResult ) const
{
	CySqliteDb::getInstance ( ).executeQuery ( this->getSelectSql ( ), objQueryResult );
}

/* ---------------------------------------------------------------------------- */
	
bool CySqlBuilder::doInsert ( const CyQueryResult::CyQueryResultValuesRow& newRow ) const
{
	return CySqliteDb::getInstance ( ).executeSql ( this->getInsertSql ( newRow ) );
}

/* ---------------------------------------------------------------------------- */

bool CySqlBuilder::doDelete ( long long lObjId ) const
{
	return CySqliteDb::getInstance ( ).executeSql ( this->getDeleteSql ( lObjId ) );
}

/* ---------------------------------------------------------------------------- */

bool CySqlBuilder::doUpdate (  const CyQueryResult::CyQueryResultValuesRow& newRow  ) const
{
	return CySqliteDb::getInstance ( ).executeSql ( this->getUpdateSql ( newRow ) );
}

/* ---------------------------------------------------------------------------- */
