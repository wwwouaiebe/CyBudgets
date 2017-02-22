/* ---------------------------------------------------------------------------- */
//! CyQueryResult.cpp
/* ---------------------------------------------------------------------------- */
//!
//! \file CyQueryResult.cpp
//! \brief definition file for class CyQueryResult
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

#include "DataLayer/CyQueryResult.h"
#include "DataLayer/CyValue.h"

/* ---------------------------------------------------------------------------- */

CyQueryResult::CyQueryResult ( )
{
}

/* ---------------------------------------------------------------------------- */

CyQueryResult::~CyQueryResult ( )
{
	this->clear ( );
}

/* ---------------------------------------------------------------------------- */

CyQueryResult::const_iterator CyQueryResult::begin ( ) const
{
	return m_QueryResultValues.begin ( );
};

/* ---------------------------------------------------------------------------- */

CyQueryResult::iterator CyQueryResult::begin ( )
{
	return m_QueryResultValues.begin ( );
};

/* ---------------------------------------------------------------------------- */

CyQueryResult::const_iterator CyQueryResult::end ( ) const
{
	return m_QueryResultValues.end ( );
};

/* ---------------------------------------------------------------------------- */

const CyQueryResult::CyQueryResultValuesRow& CyQueryResult::at ( CyQueryResultValues::size_type Position ) const
{
	return m_QueryResultValues.at ( Position );
};

/* ---------------------------------------------------------------------------- */

CyQueryResult::CyQueryResultValuesRow& CyQueryResult::at ( CyQueryResultValues::size_type Position )
{
	return m_QueryResultValues.at ( Position );
};

/* ---------------------------------------------------------------------------- */

size_t CyQueryResult::size ( ) const
{
	return m_QueryResultValues.size ( );
}

/* ---------------------------------------------------------------------------- */

void CyQueryResult::clear ( )
{
	this->m_strHeadersVector.clear ( );
	iterator queryResultIterator;
	for ( queryResultIterator = this->m_QueryResultValues.begin ( ); queryResultIterator != this->m_QueryResultValues.end ( ); ++ queryResultIterator )
	{
		queryResultIterator->clear ( );
	}

	this->m_QueryResultValues.clear ( );
}

/* ---------------------------------------------------------------------------- */

const std::vector < wxString >& CyQueryResult::getHeaders ( ) const
{
	return this->m_strHeadersVector;
}

/* ---------------------------------------------------------------------------- */

void CyQueryResult::push_back ( CyQueryResultValuesRow newRow )
{
	this->m_QueryResultValues.push_back ( newRow );
}

/* ---------------------------------------------------------------------------- */

CyQueryResult::iterator CyQueryResult::erase ( std::vector < CyQueryResult::CyQueryResultValuesRow >::iterator pos )
{
	return this->m_QueryResultValues.erase ( pos );
}

/* ---------------------------------------------------------------------------- */

CyQueryResult::CyQueryResultValuesRow::CyQueryResultValuesRow ( )
{
}

/* ---------------------------------------------------------------------------- */

CyQueryResult::CyQueryResultValuesRow::~CyQueryResultValuesRow ( )
{
}

/* ---------------------------------------------------------------------------- */

void CyQueryResult::CyQueryResultValuesRow::clear ( )
{
	// clear ( ) must be called only from CyQueryResult::clear ( ). Adding clear in the destructor is not a good idea
	std::vector < CyValue* >::iterator valuesIterator;
	for ( valuesIterator = this->begin ( );
		valuesIterator != this->end ( );
		++ valuesIterator )
	{
		delete *valuesIterator;
	}
	std::vector < CyValue* >::clear ( );
}

/* ---------------------------------------------------------------------------- */

