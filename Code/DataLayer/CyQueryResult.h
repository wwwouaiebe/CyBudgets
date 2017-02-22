/* ---------------------------------------------------------------------------- */
//! CyQueryResult.h
/* ---------------------------------------------------------------------------- */
//!
//! \file CyQueryResult.h
//! \brief header file for class CyQueryResult
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

class CyValue;
class wxString;

/* ---------------------------------------------------------------------------- */

//! \class CyQueryResult
//! \brief container used to store the results of a SQL query
//!
//! This class is used to do the data exchange betwwen the database and the user interface

//! \todo at ( ), push_back ( ) and erase ( ) methods must be private (encapsulation rules...).
//! Attention: work on Linux and Visual Studio at the same time...


class CyQueryResult
{

	friend class CySqliteDb;

	public:

		//! \class CyQueryResultValuesRow
		//! \brief 
		//! \since version 1.0.3

		class CyQueryResultValuesRow: public std::vector < CyValue* >
		{

			public:

				//! \fn CyQueryResultValuesRow ( ) 
				//! constructor

				CyQueryResultValuesRow ( );

				//! \fn ~CyQueryResultValuesRow ( ) 
				//! destructor

				~CyQueryResultValuesRow ( );

				//! \fn clear ( )
				//! This method delete each CyValue object in the vector and finally clear the vector
				void clear ( );
		};

		//! \fn CyQueryResult ( ) 
		//! constructor

		CyQueryResult ( );

		//! \fn ~CyQueryResult ( ) 
		//! destructor

		~CyQueryResult ( );

		//! \typedef CyQueryResultValues
		//! equivalent to std::vector < CyQueryResultValuesRow >

		typedef std::vector < CyQueryResultValuesRow > CyQueryResultValues;

		//! \typedef const_iterator
		//! equivalent to 

		typedef std::vector < CyQueryResultValuesRow >::const_iterator const_iterator;

		//! \typedef iterator
		//! equivalent to 

		typedef std::vector < CyQueryResultValuesRow >::iterator iterator;

		//! \fn begin ( ) const
		//!
		//! \return a const iterator to the first row of the query result

		const_iterator begin ( ) const;

		//! \fn begin ( )
		//!
		//! \return a iterator to the first row of the query result

		iterator begin ( );

		//! \fn end ( ) const
		//!
		//! \return a const iterator to the element following the last row of the query result

		const_iterator end ( ) const;

		//! \fn at ( CyQueryResultValues::size_type Position ) const
		//! @param [ in ] Position the position of the desired element
		//!
		//! \return a reference to the element at specified location Position

		const CyQueryResultValuesRow& at ( CyQueryResultValues::size_type Position ) const;

		//! \fn at ( CyQueryResultValues::size_type Position )
		//! @param [ in ] Position the position of the desired element
		//!
		//! \return a reference to the element at specified location Position

		CyQueryResultValuesRow& at ( CyQueryResultValues::size_type Position );

		//! \fn size ( )
		//!
		//! \return the number of rows in the query results

		size_t size ( ) const;

		//! \fn getHeaders ( ) 
		//! get method
		//!
		//! \return a vector with the headers of the query

		const std::vector < wxString >& getHeaders ( ) const;

		//! \fn push_back ( CyQueryResultValuesRow newRow ) 
		//! @param [ in ] newRow the values to add
		//! This method add a CyQueryResultValuesRow object at the end

		void push_back ( CyQueryResultValuesRow newRow );

		//! \fn erase ( std::vector < CyQueryResult::CyQueryResultValuesRow >::iterator pos ) 
		//! @param [ in ] pos the position of the element to remove
		//! This method remove a row at the given position
		//!
		//! \return an iterator to the object following the removed object

		iterator erase ( std::vector < CyQueryResult::CyQueryResultValuesRow >::iterator pos );

	private:

		//! \fn CyQueryResult ( const CyQueryResult& ) 
		//! copy constructor
		//! not implemented

		CyQueryResult ( const CyQueryResult& );

		//! \fn operator = ( const CyQueryResult& ) 
		//! operator =
		//! \return a reference to a CyQueryResult object
		//! not implemented

		CyQueryResult& operator = ( const CyQueryResult& );

		//! \fn clear ( )
		//! this method remove all the rows from the query results and from the headers

		void clear ( );

		//! \var m_strHeadersVector
		//! a vector of strings with the headers of the columns

		std::vector < wxString > m_strHeadersVector;

		//! \var m_QueryResultValues
		//! the query results

		CyQueryResultValues m_QueryResultValues;

};