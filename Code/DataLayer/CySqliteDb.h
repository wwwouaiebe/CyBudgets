/* ---------------------------------------------------------------------------- */
//! CySqliteDb.h
/* ---------------------------------------------------------------------------- */
//!
//! \file CySqliteDb.h
//! \brief header file for class CySqliteDb
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

#ifdef CY_COMPILER_VC10
#pragma warning(push)
#pragma warning( disable : 4820 )
#endif

#include "sqlite3.h"

#ifdef CY_COMPILER_VC10
#pragma warning(pop)
#endif


#include "DataLayer/CyQueryResult.h"

/* ---------------------------------------------------------------------------- */

//! \class CySqliteDb
//! \brief this class manage the SQLite database
//!
//! This class is based on the "Singleton" design pattern
//! \version 1.0.3
//!
//! Added formats, methods getSingleValue ( ), upgradeToVersion103 ( ) and enum NewOpenErrors

class CySqliteDb
{

	public:

		//! \fn getInstance ( )
		//! \return a reference to the one and only one instance of the database

		static CySqliteDb& getInstance ( );

		//! \enum NewOpenErrors
		//! error codes for the newFile ( ) and openFile ( ) methods
		//!
		//! \var kNewOpenOk
		//! no errors encountered when opening the files
		//!
		//! \var kNewOpenErrorLog
		//! not possible to open the error log file
		//!
		//! \var kNewOpenSqlLog
		//! not possible to open the sql log file
		//!
		//! \var kNewOpenSqliteDb
		//! not possible to open the sqlite file
		//!
		//! \var kNewOpenErrorSqlCreation
		//! an error occurs when creating the tables, indexes, views... for a new db
		//!
		//! \var kNewOpenErrorValidateBefore102
		//! an error occurs when validating a db from version 1.0.1
		//!
		//! \var kNewOpenErrorValidate
		//! an error occurs when validating the db
		//!
		//! \var kNewOpenVersionNotFound
		//! not possible to find the version in the database
		//!
		//! \var kNewOpenErrorUpgrade102
		//! an error occurs when upgrading the database to version 1.0.2
		//!
		//! \var kNewOpenErrorUpgrade103
		//! an error occurs when upgrading the database to version 1.0.3
		//!
		//! \var kNewOpenUnknown
		//! an unknown error occurs

		enum NewOpenErrors
		{
			kNewOpenOk = 1,
			kNewOpenErrorLog = 2,
			kNewOpenSqlLog = 3,
			kNewOpenSqliteDb = 4,
			kNewOpenErrorSqlCreation = 5,
			kNewOpenErrorValidateBefore102 = 6,
			kNewOpenErrorValidate = 7,
			kNewOpenVersionNotFound = 8,
			kNewOpenErrorUpgrade102 = 9,
			kNewOpenErrorUpgrade103 = 10,
			kNewOpenErrorUpgrade110 = 11,
			kNewOpenUnknown = 12
		};

		//! \fn newFile ( const wxString& strPathName, const wxString& strFileName )
		//! This method creates a new SQLite database
		//! @param [ in ] strPathName the database path terminated with a path separator
		//! @param [ in ] strFileName the database name 
		//!
		//! \return 
		//! - the error code given by the openLogFiles ( ) method if an error occurs when opening a log file
		//! - kNewOpenSqliteDb when the db cannot be opened
		//! - kNewOpenErrorSqlCreation when tables or view or index or triggers cannot be created
		//! - kNewOpenOk when no problem occurs

		NewOpenErrors newFile ( const wxString& strPathName, const wxString& strFileName );

		//! \fn openFile ( const wxString& strPathName, const wxString& strFileName )
		//! This method open a SQLite database
		//! @param [ in ] strPathName the database path terminated with a path separator
		//! @param [ in ] strFileName the database name 
		//!
		//! \return
		//! - the error code given by the openLogFiles ( ) method if an error occurs when opening a log file
		//! - kNewOpenSqliteDb when the db cannot be opened
		//! - the error code given by the validateDatabase ( ) method if an error occurs when validating the database
		//! - the error code given by the upgradeDatabase ( ) method if an error occurs whenv upgrading the database
		//! - kNewOpenOk when no problem occurs

		NewOpenErrors openFile ( const wxString& strPathName, const wxString& strFileName );

		//! \fn executeSql ( const wxString& strSql )
		//! This method execute an SQL instruction. See also the getLastError ( ) method
		//! @param [ in ] strSql the SQL instruction to be executed
		//!
		//! \return true when the SQL instruction is executed correctly, false otherwise. 

		bool executeSql ( const wxString& strSql );

		//! \fn evaluateSql ( const wxString& strSql )
		//! This method evaluate an SQL instruction. See also the getLastError ( ) method
		//! @param [ in ] strSql the SQL instruction to be evaluate
		//!
		//! \return true when the SQL instruction is a valid SQL instruction, false otherwise. 

		bool evaluateSql ( const wxString& strSql );

		//! \fn executeQuery ( const wxString& strSql, CyQueryResult& objQueryResult )
		//! This method execute an SQL "select" statement. See also the getLastError ( ) method
		//! @param [ in ] strSql the SQL "select" statement to be executed
		//! @param [ out ] objQueryResult the result of the select statement
		//!
		//! \return true when the SQL select statement is executed correctly, false otherwise. 

		bool executeQuery ( wxString strSql, CyQueryResult& objQueryResult );

		// \fn getSingleValue ( const wxString & strSql, CyValue* pValue )
		// This method execute an SQL statement that gives a one and only one value as result
		//! @param [ in ] strSql the SQL "select" statement to be executed
		//! @param [ out ] pValue a pointer to a variable where the result is stored
		//!
		//! \return true when successfull

		bool getSingleValue ( const wxString & strSql, CyValue* pValue );

		// \fn getSingleValue ( const wxString & strSql, long long* pValue )
		// This method execute an SQL statement that gives a one and only one value as result
		//! @param [ in ] strSql the SQL "select" statement to be executed
		//! @param [ out ] pValue a pointer to a variable where the result is stored
		//!
		//! \return true when successfull

		bool getSingleValue ( const wxString & strSql, long long* pValue );

		// \fn getSingleValue ( const wxString & strSql, wxString* pValue )
		// This method execute an SQL statement that gives a one and only one value as result
		//! @param [ in ] strSql the SQL "select" statement to be executed
		//! @param [ out ] pValue a pointer to a variable where the result is stored
		//!
		//! \return true when successfull

		bool getSingleValue ( const wxString & strSql, wxString* pValue );

		//! \fn getLastError ( )
		//! This method gives the last error encountered in the database
		//!
		//! \return a string with the last error. See also the SQLite method sqlite3_errmsg ( ) documentation
		
		wxString getLastError ( );

		//! \fn IsInitialized ( )
		//!
		//! \return true when a valid database is opened

		bool IsInitialized ( ) const;

		//! \fn setParameter ( const wxString& strParameterName, const wxString& strParameterValue )
		//! @param [ in ] strParameterName the name of the parameter
		//! @param [ in ] strParameterValue the parameter value
		//!
		//! This method inserts or updates a string value in the parameters table
		//! \return true when the parameter is added correctly

		bool setParameter ( const wxString& strParameterName, const wxString& strParameterValue );

		//! \fn setParameter ( const wxString& strParameterName, const long long& lParameterValue )
		//! @param [ in ] strParameterName the name of the parameter
		//! @param [ in ] lParameterValue the parameter value
		//!
		//! This method inserts or updates a long long value in the parameters table
		//! \return true when the parameter is added correctly

		bool setParameter ( const wxString& strParameterName, const long long& lParameterValue );

		//! \fn getParameter ( const wxString& strParameterName, wxString& strParameterValue )
		//! @param [ in ] strParameterName the name of the parameter
		//! @param [ out ] strParameterValue the parameter value
		//!
		//! This method read a string parameter in the parameters table
		//! \return true when the parameter was found

		bool getParameter ( const wxString& strParameterName, wxString& strParameterValue );

		//! \fn getParameter ( const wxString& strParameterName, long long& lParameterValue )
		//! @param [ in ] strParameterName the name of the parameter
		//! @param [ out ] lParameterValue the parameter value
		//!
		//! This method read a long long parameter in the parameters table
		//! \return true when the parameter was found

		bool getParameter ( const wxString& strParameterName, long long& lParameterValue );

	private:

		//! \fn CySqliteDb ( ) 
		//! constructor

		CySqliteDb ( );

		//! \fn ~CySqliteDb ( ) 
		//! destructor

		~CySqliteDb ( );


		//! \fn CySqliteDb ( const CySqliteDb& ) 
		//! copy constructor
		//! not implemented

		CySqliteDb ( const CySqliteDb& );

		//! \fn operator = ( const CySqliteDb& ) 
		//! operator =
		//! not implemented
		//! \return a reference to a CySqliteDb object

		CySqliteDb& operator = ( const CySqliteDb& );

		//! \fn openLogFiles ( const wxString& strPathName, const wxString& strFileName )
		//! This method open the log files associated with the database
		//! @param [ in ] strPathName the database path terminated with a path separator
		//! @param [ in ] strFileName the database name 
		//!
		//! \return 
		//! - kNewOpenErrorLog when an error occurs on the log file, 
		//! - kNewOpenSqlLog when an error occurs on the SQL log file
		//! - kNewOpenOk when successfull

		NewOpenErrors openLogFiles ( const wxString& strPathName, const wxString& strFileName );

		//! \fn closeLogFiles ( )
		//! This method closes the log files associated with the database

		void closeLogFiles ( );

		//! \fn validateDatabase ( )
		//! this method verify that the opened database is a valid CyBudgets database
		//! 
		//! \return
		//! - kNewOpenErrorValidateBefore102 when an error occurs validating a database created with version 1.0.1
		//! - kNewOpenErrorValidate when an error occurs validating the database
		//! - kNewOpenOk when sucessfull

		NewOpenErrors validateDatabase ( );

		//! \fn upgradeDatabase ( )
		//! this method upgrade the database when the version is changed.
		//! \return 
		//! - kNewOpenVersionNotFound when the version cannot be found in the db
		//! - the error code given by the methods upgradetoVersionXXX ( )
		//! - kNewOpenOk when successfull

		NewOpenErrors upgradeDatabase ( );

		//! \fn upgradeToVersion102 ( )
		//! this method upgrade the database to the version 1.0.2
		//! \return 
		//! - kNewOpenErrorUpgrade102 when an error occurs
		//! - kNewOpenOk when successfull

		NewOpenErrors upgradeToVersion102 ( );

		//! \fn upgradeToVersion103 ( )
		//! this method upgrade the database to the version 1.0.3
		//! \return 
		//! - kNewOpenErrorUpgrade103 when an error occurs
		//! - kNewOpenOk when successfull

		NewOpenErrors upgradeToVersion103();

		//! \fn upgradeToVersion110 ( )
		//! this method upgrade the database to the version 1.1.0
		//! \return 
		//! - kNewOpenErrorUpgrade110 when an error occurs
		//! - kNewOpenOk when successfull

		NewOpenErrors upgradeToVersion110();

		//! \fn logError ( const wxString& strSql )
		//! This method log the error message and the SQL instruction associated to the error
		//! @param [ in ] strSql the SQL instruction to be logged

		void logError ( const wxString& strSql );

		//! \fn logSql ( const wxString& strSql )
		//! This method log  the SQL instruction
		//! @param [ in ] strSql the SQL instruction to be logged

		void logSql ( const wxString& strSql );

		//! \fn updatePreferences ( const wxString& strPathName, const wxString& strFileName )
		//! @param [in ] strPathName the path of the last used file
		//! @param [in ] strFileName the name of the last used file
		//! This method updates the CyUserPreferences object when a db is created or opened
		void updatePreferences ( const wxString& strPathName, const wxString& strFileName );

		//! \var m_bInitialized
		//! true when the database is opened correctly

		bool m_bInitialized;

		//! \var m_pSqlite3
		//! the SQLite database

		sqlite3* m_pSqlite3;

		//! \var m_objSqliteDb 
		//! the one and only one instance of the class
		
		static CySqliteDb m_objSqliteDb;

		//! \var m_ErrorLogStream
		//! the error log file

		std::ofstream m_ErrorLogStream;
		
		//! \var m_SqlLogStream
		//! the SQL log file

		std::ofstream m_SqlLogStream;
};

/* ---------------------------------------------------------------------------- */
