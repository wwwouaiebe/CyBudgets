/* ---------------------------------------------------------------------------- */
//! CySqliteDb.cpp
/* ---------------------------------------------------------------------------- */
//!
//! \file CySqliteDb.cpp
//! \brief definition file for class CySqliteDb
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

#ifdef CY_COMPILER_VC10
#pragma warning( disable : 4820 )
#endif

#include "DataLayer/CyLongValue.h"
#include "DataLayer/CyStringValue.h"
#include "DataLayer/CySqliteDb.h"
#include "DataLayer/CySqliteFunctions.h"
#include "UtilitiesLayer/CyEnum.h"
#include "UtilitiesLayer/CyFilesService.h"
#include "UtilitiesLayer/CyGetText.h"
#include "UtilitiesLayer/CyStringParser.h"
#include "UtilitiesLayer/CyUtf8WxStringTranslator.h"
#include "UtilitiesLayer/CyWxVersionInfo.h"

/* ---------------------------------------------------------------------------- */

CySqliteDb CySqliteDb::m_objSqliteDb;

/* ---------------------------------------------------------------------------- */

CySqliteDb::CySqliteDb ( ):
	m_bInitialized ( false )
{
}

/* ---------------------------------------------------------------------------- */

bool CySqliteDb::IsInitialized ( ) const
{
	return this->m_bInitialized;
}

/* ---------------------------------------------------------------------------- */

CySqliteDb::NewOpenErrors CySqliteDb::newFile ( const wxString& strPathName, const wxString& strFileName )
{
	// The previously used db is closed
	if ( this->IsInitialized () )
	{
		sqlite3_close ( m_pSqlite3 );
		this->closeLogFiles ( );
		this->m_bInitialized = false;
	}

	// Log files are opened
	CySqliteDb::NewOpenErrors eReturnCode =  this->openLogFiles ( strPathName, strFileName );
	if ( CySqliteDb::kNewOpenOk != eReturnCode )
	{
		this->closeLogFiles ( );
		return eReturnCode;
	}

	// the SQLite db is opened
	int iOpenCode = sqlite3_open ( strPathName + strFileName, &m_pSqlite3 );
	if ( SQLITE_OK != iOpenCode )
	{
		this->closeLogFiles ( );
		return CySqliteDb::kNewOpenSqliteDb;
	}

	this->m_bInitialized = true;

	// Starting creation of db...
	bool bTransactionOk = true;

	// ... table creation...
	bTransactionOk &= this->executeSql ( wxString ( "BEGIN EXCLUSIVE TRANSACTION;" ) );
	bTransactionOk &= this->executeSql ( wxString ( "CREATE TABLE IF NOT EXISTS Accounts (ObjId INTEGER PRIMARY KEY DESC, AccountNumber TEXT, AccountOwner TEXT, CanBeImported INTEGER, InitialAmount INTEGER, ValidSinceDate TEXT, ValidToDate TEXT);" ) );
	bTransactionOk &= this->executeSql ( wxString ( "CREATE TABLE IF NOT EXISTS OperationsAttributions (ObjId INTEGER PRIMARY KEY DESC, AttributionObjId INTEGER, OperationObjId INTEGER, Amount INTEGER);" ) );
	bTransactionOk &= this->executeSql ( wxString ( "CREATE TABLE IF NOT EXISTS AttributionsGroups (ObjId INTEGER PRIMARY KEY DESC, GroupDescription TEXT);" ));
	bTransactionOk &= this->executeSql ( wxString ( "CREATE TABLE IF NOT EXISTS Attributions (ObjId INTEGER PRIMARY KEY DESC, GroupObjId INTEGER, Description TEXT, BudgetObjId INTEGER, ValidToDate TEXT);" ) );
	bTransactionOk &= this->executeSql ( wxString ( "CREATE TABLE IF NOT EXISTS Operations (ObjId INTEGER PRIMARY KEY DESC, AccountObjId INTEGER, OperationNumber INTEGER,OperationDate TEXT,ValueDate TEXT,AttributionDate TEXT, Amount INTEGER, Description TEXT);" ) );
	bTransactionOk &= this->executeSql ( wxString ( "CREATE TABLE IF NOT EXISTS OperationsDetails (ObjId INTEGER PRIMARY KEY DESC, OperationObjId INTEGER, Detail TEXT);" ) );
	bTransactionOk &= this->executeSql ( wxString ( "CREATE TABLE IF NOT EXISTS Budgets (ObjId INTEGER PRIMARY KEY DESC, Description TEXT);" ) );
	bTransactionOk &= this->executeSql ( wxString ( "CREATE TABLE IF NOT EXISTS Versions (Application TEXT, MajorVersion INTEGER, MinorVersion INTEGER, MicroVersion INTEGER);" ) );
	bTransactionOk &= this->executeSql ( wxString ( "CREATE TABLE IF NOT EXISTS Parameters (ParameterName TEXT, TextValue TEXT, IntegerValue INTEGER);" ) );

	// ... version is added to the version table...
	wxString strSql;
	strSql
		<< wxString ( "INSERT INTO Versions ( Application, MajorVersion, MinorVersion, MicroVersion ) values ( \"CyBudgets\", " )
		<< CyWxVersionInfo::getInstance ( ).GetMajor ( )
		<< wxString ( ", " )
		<< CyWxVersionInfo::getInstance ( ).GetMinor ( )
		<< wxString ( ", " )
		<< CyWxVersionInfo::getInstance ( ).GetMicro ( )
		<< wxString ( "); " ); 
	bTransactionOk &= this->executeSql ( strSql );

	// ...index creation...
	// Indexes creation
	bTransactionOk &= this->executeSql ( wxString ( "CREATE INDEX IF NOT EXISTS Accounts_ObjId ON Accounts ( ObjId );" ) );
	bTransactionOk &= this->executeSql ( wxString ( "CREATE INDEX IF NOT EXISTS Accounts_AccountNumber ON Accounts ( AccountNumber );" ) );

	bTransactionOk &= this->executeSql ( wxString ( "CREATE INDEX IF NOT EXISTS Operations_ObjId ON Operations ( ObjId );" ) );
	bTransactionOk &= this->executeSql ( wxString ( "CREATE INDEX IF NOT EXISTS Operations_AccountObjId ON Operations ( AccountObjId );" ) );
	bTransactionOk &= this->executeSql ( wxString ( "CREATE INDEX IF NOT EXISTS Operations_Operations ON Operations ( AccountObjId, OperationDate DESC, OperationNumber DESC );" ) );
	bTransactionOk &= this->executeSql ( wxString ( "CREATE INDEX IF NOT EXISTS Operations_ValueDate ON Operations ( ValueDate );" ) );

	bTransactionOk &= this->executeSql ( wxString ( "CREATE INDEX IF NOT EXISTS OperationsDetails_ObjId ON OperationsDetails ( ObjId );" ) );
	bTransactionOk &= this->executeSql ( wxString ( "CREATE INDEX IF NOT EXISTS OperationsDetails_OperationObjId ON OperationsDetails ( OperationObjId );" ) );

	bTransactionOk &= this->executeSql ( wxString ( "CREATE INDEX IF NOT EXISTS Budgets_ObjId ON Budgets ( ObjId );" ) );
	bTransactionOk &= this->executeSql ( wxString ( "CREATE INDEX IF NOT EXISTS Budgets_Description ON Budgets ( Description );" ) );

	bTransactionOk &= this->executeSql ( wxString ( "CREATE INDEX IF NOT EXISTS AttributionsGroups_ObjId ON AttributionsGroups ( ObjId );" ) );
	bTransactionOk &= this->executeSql ( wxString ( "CREATE INDEX IF NOT EXISTS AttributionsGroups_GroupDescription ON AttributionsGroups ( GroupDescription );" ) );

	bTransactionOk &= this->executeSql ( wxString ( "CREATE INDEX IF NOT EXISTS Attributions_ObjId ON Attributions ( ObjId );" ) );
	bTransactionOk &= this->executeSql ( wxString ( "CREATE INDEX IF NOT EXISTS Attributions_GroupObjId ON Attributions ( GroupObjId );" ) );
	bTransactionOk &= this->executeSql ( wxString ( "CREATE INDEX IF NOT EXISTS Attributions_BudgetObjId ON Attributions ( BudgetObjId );" ) );

	bTransactionOk &= this->executeSql ( wxString ( "CREATE INDEX IF NOT EXISTS OperationsAttributions_ObjId ON OperationsAttributions ( ObjId );" ) );
	bTransactionOk &= this->executeSql ( wxString ( "CREATE INDEX IF NOT EXISTS OperationsAttributions_OperationObjId ON OperationsAttributions ( OperationObjId );" ) );
	bTransactionOk &= this->executeSql ( wxString ( "CREATE INDEX IF NOT EXISTS OperationsAttributions_AttributionObjId ON OperationsAttributions ( AttributionObjId );" ) );

	bTransactionOk &= this->executeSql ( wxString ( "CREATE INDEX IF NOT EXISTS Parameters_ParameterName ON Parameters ( ParameterName );") );

	// ... view creation...
	bTransactionOk &= this->executeSql ( wxString ( "CREATE VIEW IF NOT EXISTS AccountsView AS SELECT ObjId as AccObjId, CanBeImported, AccountNumber FROM Accounts;" ) );
	bTransactionOk &= this->executeSql ( wxString ( "CREATE VIEW IF NOT EXISTS OperationsView AS SELECT ObjId AS OpeObjId, AccountObjId, OperationNumber, OperationDate, ValueDate, AttributionDate, Amount, Description FROM Operations;" ) );
	bTransactionOk &= this->executeSql ( wxString ( "CREATE VIEW IF NOT EXISTS OperationsDetailsView AS SELECT COUNT ( 1 ) AS DetailNumber, OperationObjId FROM OperationsDetails GROUP BY OperationObjId;" ) );
	bTransactionOk &= this->executeSql ( wxString ( "CREATE VIEW IF NOT EXISTS OperationsAttributionsView AS SELECT COUNT ( 1 ) AS AttributionNumber, OperationObjId FROM OperationsAttributions GROUP BY OperationObjId;" ) );

	// ... trigger creation...
	bTransactionOk &= this->executeSql ( wxString ( "CREATE TRIGGER IF NOT EXISTS DeleteAccountTrigger BEFORE DELETE ON Accounts BEGIN DELETE FROM Operations WHERE AccountObjId = old.ObjId; END;" ) ); 
	bTransactionOk &= this->executeSql ( wxString ( "CREATE TRIGGER IF NOT EXISTS DeleteAttributionGroupTrigger BEFORE DELETE ON AttributionsGroups BEGIN DELETE FROM Attributions WHERE GroupObjId = old.ObjId; END;" ) );
	bTransactionOk &= this->executeSql ( wxString ( "CREATE TRIGGER IF NOT EXISTS DeleteBudgetTrigger BEFORE DELETE ON Budgets BEGIN DELETE FROM Attributions WHERE BudgetObjId = old.ObjId; END;" ) );
	bTransactionOk &= this->executeSql ( wxString ( "CREATE TRIGGER IF NOT EXISTS DeleteAttributionTrigger BEFORE DELETE ON Attributions BEGIN DELETE FROM OperationsAttributions WHERE AttributionObjId = old.ObjId; END;" ) );
	bTransactionOk &= this->executeSql ( wxString ( "CREATE TRIGGER IF NOT EXISTS DeleteOperationTrigger BEFORE DELETE ON Operations BEGIN DELETE FROM OperationsDetails WHERE OperationObjId = old.ObjId; DELETE FROM OperationsAttributions WHERE OperationObjId = old.ObjId; END;" ) );

	if ( bTransactionOk )
	{
		// ... and commit
		this->executeSql ( wxString ( "COMMIT;") );
		eReturnCode = CySqliteDb::kNewOpenOk;
		this->m_bInitialized = true;
	}
	else
	{
		// ... or rollback
		this->executeSql ( wxString ( "ROLLBACK TRANSACTION;") );
		eReturnCode = CySqliteDb::kNewOpenErrorSqlCreation;
		this->closeLogFiles ( );
		sqlite3_close ( m_pSqlite3 );
	}

	return eReturnCode;
}

/* ---------------------------------------------------------------------------- */

CySqliteDb::NewOpenErrors CySqliteDb::openFile ( const wxString& strPathName, const wxString& strFileName )
{
	// The previously used db is closed
	if ( this->IsInitialized () )
	{
		sqlite3_close ( m_pSqlite3 );
		this->closeLogFiles ( );
		this->m_bInitialized = false;
	}

	// a backup of the db is made. The name of the backup = the current name + the current datetime
	wxDateTime objCurrentDateTime;
	objCurrentDateTime.SetToCurrent ( );
	wxString strCurrentDateTime = objCurrentDateTime.FormatISOCombined ( );
	strCurrentDateTime.Replace ( wxString ( "-" ), wxString ( "" ) );
	strCurrentDateTime.Replace ( wxString ( ":" ), wxString ( "" ) );
	std::ifstream originalDb ( wxString ( strPathName + strFileName ).ToStdString ( ).data ( ), std::ios::binary);
	std::ofstream backupDb ( wxString ( strPathName + strFileName + strCurrentDateTime  ).ToStdString ( ).data ( ), std::ios::binary);
    backupDb << originalDb.rdbuf();

    originalDb.close();
    backupDb.close();

	// Log files are opened
	CySqliteDb::NewOpenErrors eReturnCode =  this->openLogFiles ( strPathName, strFileName );
	if ( CySqliteDb::kNewOpenOk != eReturnCode )
	{
		this->closeLogFiles ( );
		return eReturnCode;
	}

	// the SQLite db is opened
	int iOpenCode = sqlite3_open ( strPathName + strFileName, &m_pSqlite3 );
	if ( SQLITE_OK != iOpenCode )
	{
		this->closeLogFiles ( );
		return CySqliteDb::kNewOpenSqliteDb;
	}

	// it's needed to considere that the db is initialized to validate...
	this->m_bInitialized = true;
	eReturnCode = this->validateDatabase ( );
	if ( CySqliteDb::kNewOpenOk != eReturnCode )
	{
		sqlite3_close ( m_pSqlite3 );
		this->closeLogFiles ( );
		this->m_bInitialized = false;
		return eReturnCode;
	}
	
	// database upgrade
	eReturnCode = this->upgradeDatabase ( );

	if ( CySqliteDb::kNewOpenOk != eReturnCode )
	{
		// closing the db if an error occured
		sqlite3_close ( m_pSqlite3 );
		this->closeLogFiles ( );
		this->m_bInitialized = false;
		return eReturnCode;
	}

	return CySqliteDb::kNewOpenOk;
}

/* ---------------------------------------------------------------------------- */

CySqliteDb::NewOpenErrors CySqliteDb::openLogFiles ( const wxString& strPathName, const wxString& strFileName )
{
	// the first part of the file name is searched
	CyStringParser objStringParser;
	objStringParser.parse ( ".", strFileName.ToStdString ( ) );
	wxString strFileNameBase = wxString ( objStringParser.at ( 0 ) );

	// the error log file is opened
	this->m_ErrorLogStream.open ( wxString (strPathName + strFileNameBase + wxString ( "-ErrorLog.txt" ) ).ToStdString ( ).data ( ), std::ios::app /*& std::ios::out*/ );
	if ( ! m_ErrorLogStream )
	{
		return CySqliteDb::kNewOpenErrorLog;
	}

	// the SQL log file is opened
	this->m_SqlLogStream.open (  wxString (strPathName + strFileNameBase + wxString ( "-SqlLog.sql" ) ).ToStdString ( ).data ( ), std::ios::app /*& std::ios::out*/ );
	if ( ! m_SqlLogStream )
	{
		return CySqliteDb::kNewOpenSqlLog;
	}

	return CySqliteDb::kNewOpenOk;
}

/* ---------------------------------------------------------------------------- */

void CySqliteDb::closeLogFiles ( )
{
	if ( this->m_ErrorLogStream )
	{
		this->m_ErrorLogStream.close ( );
	}
	if ( this->m_SqlLogStream )
	{
		this->m_SqlLogStream.close ( );
	}
}

/* ---------------------------------------------------------------------------- */

CySqliteDb::~CySqliteDb ( )
{
	// the db and log files are closed
	sqlite3_close ( m_pSqlite3 );
	this->m_ErrorLogStream.close ( );
	this->m_SqlLogStream.close ( );
}

/* ---------------------------------------------------------------------------- */

CySqliteDb::NewOpenErrors CySqliteDb::validateDatabase ( )
{
	// the db version is searched
	CyQueryResult objQueryResult;
	bool bVersionFound = this->executeQuery ( wxString ( "select Application from Versions" ), objQueryResult );

	if ( wxString ( "1.0.2" ) == CyWxVersionInfo::getInstance ( ).getVersion ( ) && ( ! bVersionFound ) )
	{
		// the table versions don't exist in the version 1.0.1. Creating the table...
		bool bTransactionOk = true;
		bTransactionOk &= this->executeSql ( wxString ( "BEGIN EXCLUSIVE TRANSACTION;"  ) );
		bTransactionOk &= this->executeSql ( wxString ( "CREATE TABLE IF NOT EXISTS Versions (Application TEXT, MajorVersion INTEGER, MinorVersion INTEGER, MicroVersion INTEGER);" ) );
		bTransactionOk &= this->executeSql ( wxString ( "INSERT INTO Versions ( Application, MajorVersion, MinorVersion, MicroVersion ) values ( \"CyBudgets\", 1, 0, 1);" ) );
		if ( bTransactionOk )
		{
			this->executeSql ( wxString ( "COMMIT;") );
		}
		else
		{
			this->executeSql ( wxString ( "ROLLBACK TRANSACTION;") );
		}
		return kNewOpenErrorValidateBefore102;
	}
	if ( bVersionFound )
	{
		// a version is found. We verify that the db is a correct one
		if ( ( 1 == objQueryResult.size ( ) ) && ( wxString ( "CyBudgets" ) == objQueryResult.at ( 0 ).at ( 0 )->getAsString ( ) ) )
		{
			// The db is a CyBudgets db
			return kNewOpenOk;
		}
	}

	return kNewOpenErrorValidate;
}


/* ---------------------------------------------------------------------------- */

CySqliteDb::NewOpenErrors CySqliteDb::upgradeDatabase ( )
{
	// we search the version saved in the database
	CyQueryResult objQueryResult;
	bool bVersionFound = this->executeQuery ( wxString ( "select Application, MajorVersion, MinorVersion, MicroVersion from Versions" ), objQueryResult );
	if ( ! bVersionFound )
	{
		// the versions table is not found or another error occurs
		return CySqliteDb::kNewOpenVersionNotFound;
	}

	if ( ( 1 != objQueryResult.size ( ) ) || 4 != objQueryResult.at ( 0 ).size ( ) || ( wxString ( "CyBudgets" ) != objQueryResult.at ( 0 ).at ( 0 )->getAsString ( ) ) )
	{
		// the versions table is found but the application is not correct
		return CySqliteDb::kNewOpenVersionNotFound;
	}

	long long lMajorVersion = objQueryResult.at ( 0 ).at ( 1 )->get ( CyLongValue::m_lDummyValue );
	long long lMinorVersion = objQueryResult.at ( 0 ).at ( 2 )->get ( CyLongValue::m_lDummyValue );
	long long lMicroVersion = objQueryResult.at ( 0 ).at ( 3 )->get ( CyLongValue::m_lDummyValue );

	if ( ( CyEnum::kInvalidVersion == lMajorVersion ) || ( CyEnum::kInvalidVersion == lMinorVersion ) || ( CyEnum::kInvalidVersion == lMicroVersion ) )
	{
		// not possible to read a correct version from the db
		return CySqliteDb::kNewOpenVersionNotFound;
	}

	CySqliteDb::NewOpenErrors eReturnCode = CySqliteDb::kNewOpenUnknown;
	if ( ( 1 == lMajorVersion ) && ( 0 == lMinorVersion ) && ( 1 == lMicroVersion ) )
	{
		// upgrading to version 1.0.2
		eReturnCode = this->upgradeToVersion102 ( );
		if ( CySqliteDb::kNewOpenOk == eReturnCode )
		{
			lMicroVersion = 2;
		}
		else
		{
			return eReturnCode;
		}
	}

	eReturnCode = CySqliteDb::kNewOpenUnknown;
	if ( ( 1 == lMajorVersion ) && ( 0 == lMinorVersion ) && ( 2 == lMicroVersion ) )
	{
		// upgrading to version 1.0.3
		eReturnCode = this->upgradeToVersion103 ( );
		if ( CySqliteDb::kNewOpenOk == eReturnCode )
		{
			lMicroVersion = 3;
		}
		else
		{
			return eReturnCode;
		}
	}

	eReturnCode = CySqliteDb::kNewOpenUnknown;
	if ( ( 1 == lMajorVersion ) && ( 0 == lMinorVersion ) && ( 3 == lMicroVersion ) )
	{
		// upgrading to version 1.1.0
		eReturnCode = this->upgradeToVersion110 ( );
		if ( CySqliteDb::kNewOpenOk == eReturnCode )
		{
			lMinorVersion = 1;
			lMicroVersion = 0;
		}
		else
		{
			return eReturnCode;
		}
	}
	// to continue for future versions...

	return CySqliteDb::kNewOpenOk;
}

/* ---------------------------------------------------------------------------- */

CySqliteDb::NewOpenErrors CySqliteDb::upgradeToVersion102 ( )
{
	bool bTransactionOk = true;
	bTransactionOk &= this->executeSql ( wxString ( "BEGIN EXCLUSIVE TRANSACTION;"  ) );
	// the table Accounts is updated
	bTransactionOk &= this->executeSql ( wxString ( "Alter table Accounts add column InitialAmount REAL;" ) );
	bTransactionOk &= this->executeSql ( wxString ( "Alter table Accounts add column ValidSinceDate TEXT;") );
	bTransactionOk &= this->executeSql ( wxString ( "Update Accounts set InitialAmount = 0;") );
	bTransactionOk &= this->executeSql ( wxString ( "Update Accounts set ValidSinceDate = \"1900-01-01\";" ) );
	bTransactionOk &= this->executeSql ( wxString ( "Update Versions set MicroVersion = 2;" ) );
	bTransactionOk &= this->executeSql ( wxString ( "CREATE view IF NOT EXISTS AccountsView as select ObjId as AccObjId, AccountNumber from Accounts;" ) );
	bTransactionOk &= this->executeSql ( wxString ( "CREATE view IF NOT EXISTS OperationsView as select ObjId as OpeObjId, AccountObjId, OperationNumber, OperationDate, ValueDate, AttributionDate, Amount, Description from Operations;" ) );
	bTransactionOk &= this->executeSql ( wxString ( "CREATE view IF NOT EXISTS OperationsDetailsView as select count ( 1 ) as DetailNumber, OperationObjId from OperationsDetails group by OperationObjId;" ) );
	bTransactionOk &= this->executeSql ( wxString ( "CREATE view IF NOT EXISTS OperationsAttributionsView as select count ( 1 ) as AttributionNumber, OperationObjId from OperationsAttributions group by OperationObjId;" ) );
	bTransactionOk &= this->executeSql ( wxString ( "CREATE TRIGGER IF NOT EXISTS DeleteAccountTrigger BEFORE DELETE ON Accounts BEGIN DELETE FROM Operations WHERE AccountObjId = old.ObjId; END;" ) ); 
	bTransactionOk &= this->executeSql ( wxString ( "CREATE TRIGGER IF NOT EXISTS DeleteOperationTrigger BEFORE DELETE ON Operations BEGIN DELETE FROM OperationsDetails WHERE OperationObjId = old.ObjId; DELETE FROM OperationsAttributions WHERE OperationObjId = old.ObjId; END;" ) );
	bTransactionOk &= this->executeSql ( wxString ( "CREATE TRIGGER IF NOT EXISTS DeleteBudgetTrigger BEFORE DELETE ON Budgets BEGIN DELETE FROM Attributions WHERE BudgetObjId = old.ObjId; END;" ) );
	bTransactionOk &= this->executeSql ( wxString ( "CREATE TRIGGER IF NOT EXISTS DeleteAttributionTrigger BEFORE DELETE ON Attributions BEGIN DELETE FROM OperationsAttributions WHERE AttributionObjId = old.ObjId; END;" ) );

	if ( bTransactionOk )
	{
		// update executed correctly
		this->executeSql ( wxString ( "COMMIT;") );
		return CySqliteDb::kNewOpenOk;
	}
	else
	{
		// update not executed
		this->executeSql ( wxString ( "ROLLBACK TRANSACTION;") );
		return CySqliteDb::kNewOpenErrorUpgrade102;
	}
}

/* ---------------------------------------------------------------------------- */

CySqliteDb::NewOpenErrors CySqliteDb::upgradeToVersion103 ( )
{
	// a sqlite function to transform real to integer is added to the db
	sqlite3_create_function ( m_pSqlite3, "double_to_currency", 1, SQLITE_UTF8, NULL, &CySqliteFunctions::DoubleToCurrency, NULL, NULL );

	// starting the upgrade
	bool bTransactionOk = true;

	bTransactionOk &= this->executeSql ( wxString ( "BEGIN EXCLUSIVE TRANSACTION;"  ) );

	// accounts table update
	bTransactionOk &= this->executeSql ( wxString ( "CREATE TABLE IF NOT EXISTS AccountsTmp (ObjId INTEGER PRIMARY KEY DESC, AccountNumber TEXT, AccountOwner TEXT, CanBeImported INTEGER, InitialAmount INTEGER, ValidSinceDate TEXT);" ) );
	bTransactionOk &= this->executeSql ( wxString ( "INSERT INTO AccountsTmp ( ObjId, AccountNumber, AccountOwner, CanBeImported, InitialAmount, ValidSinceDate ) SELECT ObjId, AccountNumber, AccountOwner, CanBeImported, double_to_currency ( InitialAmount ), ValidSinceDate from Accounts;" ) );
	bTransactionOk &= this->executeSql ( wxString ( "DROP TABLE IF EXISTS Accounts;" ) );
	bTransactionOk &= this->executeSql ( wxString ( "ALTER TABLE AccountsTmp RENAME TO Accounts;" ) );

	// OperationsAttributions table update
	bTransactionOk &= this->executeSql ( wxString ( "CREATE TABLE IF NOT EXISTS OperationsAttributionsTmp (ObjId INTEGER PRIMARY KEY DESC, AttributionObjId INTEGER, OperationObjId INTEGER, Amount INTEGER);" ) );
	bTransactionOk &= this->executeSql ( wxString ( "INSERT INTO OperationsAttributionsTmp ( ObjId, AttributionObjId, OperationObjId, Amount ) SELECT ObjId, AttrbutionObjId, OperationObjId, double_to_currency ( Amount ) from AttrbutionOperations;" ) );
	bTransactionOk &= this->executeSql ( wxString ( "DROP TABLE IF EXISTS AttrbutionOperations;" ) );
	bTransactionOk &= this->executeSql ( wxString ( "ALTER TABLE OperationsAttributionsTmp RENAME TO OperationsAttributions;" ) );

	// Operations table update
	bTransactionOk &= this->executeSql ( wxString ( "CREATE TABLE IF NOT EXISTS OperationsTmp (ObjId INTEGER PRIMARY KEY DESC, AccountObjId INTEGER, OperationNumber INTEGER, OperationDate TEXT, ValueDate TEXT,AttributionDate TEXT, Amount INTEGER, Description TEXT)" ) );
	bTransactionOk &= this->executeSql ( wxString ( "INSERT INTO OperationsTmp ( ObjId, AccountObjId, OperationNumber, OperationDate, ValueDate, AttributionDate, Amount, Description ) SELECT ObjId, AccountObjId, OperationNumber, OperationDate, ValueDate, AttrbutionDate, double_to_currency ( Amount ), Description from Operations;" ) );
	bTransactionOk &= this->executeSql ( wxString ( "DROP TABLE IF EXISTS Operations;" ) );
	bTransactionOk &= this->executeSql ( wxString ( "ALTER TABLE OperationsTmp RENAME TO Operations;" ) );

	// AttributionsGroups table creation
	bTransactionOk &= this->executeSql ( wxString ( "CREATE TABLE IF NOT EXISTS AttributionsGroups (ObjId INTEGER PRIMARY KEY DESC, GroupDescription TEXT);" ));
	bTransactionOk &= this->executeSql ( wxString ( "INSERT INTO AttributionsGroups( GroupDescription) SELECT DISTINCT MainDescription FROM Attributions;" ) );
	bTransactionOk &= this->executeSql ( wxString ( "UPDATE AttributionsGroups SET ObjId = RowId - 1;" ) );

	// Attributions table update
	bTransactionOk &= this->executeSql ( wxString ( "CREATE TABLE IF NOT EXISTS AttributionsTmp (ObjId INTEGER PRIMARY KEY DESC, GroupObjId INTEGER, Description TEXT, BudgetObjId INTEGER);" ));
	bTransactionOk &= this->executeSql ( wxString ( "CREATE VIEW IF NOT EXISTS AttributionsGroupsView AS SELECT a.ObjId, g.ObjId as GroupObjId, a.Description, a.BudgetObjId FROM AttributionsGroups g JOIN Attributions a ON g.GroupDescription = a.MainDescription;" ));
	bTransactionOk &= this->executeSql ( wxString ( "INSERT INTO AttributionsTmp ( ObjId, GroupObjId, Description, BudgetObjId ) SELECT ObjId, GroupObjId, Description, BudgetObjId from AttributionsGroupsView;" ) );
	bTransactionOk &= this->executeSql ( wxString ( "DROP TABLE IF EXISTS Attributions;" ) );
	bTransactionOk &= this->executeSql ( wxString ( "ALTER TABLE AttributionsTmp RENAME TO Attributions;" ) );
	bTransactionOk &= this->executeSql ( wxString ( "DROP view AttributionsGroupsView;" ) );

	// Trigger deletion
	// Due to previous operations on tables it's needed to remove and recreate all triggers
	bTransactionOk &= this->executeSql ( wxString ( "DROP TRIGGER IF EXISTS DeleteAccountTrigger;" ) ); 
	bTransactionOk &= this->executeSql ( wxString ( "DROP TRIGGER IF EXISTS DeleteAttributionGroupTrigger;" ) );
	bTransactionOk &= this->executeSql ( wxString ( "DROP TRIGGER IF EXISTS DeleteBudgetTrigger;" ) );
	bTransactionOk &= this->executeSql ( wxString ( "DROP TRIGGER IF EXISTS DeleteAttributionTrigger;" ) );
	bTransactionOk &= this->executeSql ( wxString ( "DROP TRIGGER IF EXISTS DeleteOperationTrigger;" ) );

	// Trigger creation
	bTransactionOk &= this->executeSql ( wxString ( "CREATE TRIGGER IF NOT EXISTS DeleteAccountTrigger BEFORE DELETE ON Accounts BEGIN DELETE FROM Operations WHERE AccountObjId = old.ObjId; END;" ) ); 
	bTransactionOk &= this->executeSql ( wxString ( "CREATE TRIGGER IF NOT EXISTS DeleteAttributionGroupTrigger BEFORE DELETE ON AttributionsGroups BEGIN DELETE FROM Attributions WHERE GroupObjId = old.ObjId; END;" ) );
	bTransactionOk &= this->executeSql ( wxString ( "CREATE TRIGGER IF NOT EXISTS DeleteBudgetTrigger BEFORE DELETE ON Budgets BEGIN DELETE FROM Attributions WHERE BudgetObjId = old.ObjId; END;" ) );
	bTransactionOk &= this->executeSql ( wxString ( "CREATE TRIGGER IF NOT EXISTS DeleteAttributionTrigger BEFORE DELETE ON Attributions BEGIN DELETE FROM OperationsAttributions WHERE AttributionObjId = old.ObjId; END;" ) );
	bTransactionOk &= this->executeSql ( wxString ( "CREATE TRIGGER IF NOT EXISTS DeleteOperationTrigger BEFORE DELETE ON Operations BEGIN DELETE FROM OperationsDetails WHERE OperationObjId = old.ObjId; DELETE FROM OperationsAttributions WHERE OperationObjId = old.ObjId; END;" ) );

	// Old indexes deletion
	bTransactionOk &= this->executeSql ( wxString ( "DROP INDEX IF EXISTS AccountsObjId;" ) );
	bTransactionOk &= this->executeSql ( wxString ( "DROP INDEX IF EXISTS AccountsAccountNumber;" ) );
	bTransactionOk &= this->executeSql ( wxString ( "DROP INDEX IF EXISTS OperationsAttributionsObjId;" ) ); 
	bTransactionOk &= this->executeSql ( wxString ( "DROP INDEX IF EXISTS OperationsAttributionsOperationObjId;" ) );
	bTransactionOk &= this->executeSql ( wxString ( "DROP INDEX IF EXISTS AttributionsObjId;" ) ); 
	bTransactionOk &= this->executeSql ( wxString ( "DROP INDEX IF EXISTS AttributionsDescriptions;" ) );
	bTransactionOk &= this->executeSql ( wxString ( "DROP INDEX IF EXISTS OperationsObjId;" ) ); 
	bTransactionOk &= this->executeSql ( wxString ( "DROP INDEX IF EXISTS OperationsOperations;" ) );
	bTransactionOk &= this->executeSql ( wxString ( "DROP INDEX IF EXISTS OperationsDetailsObjId;" ) ); 
	bTransactionOk &= this->executeSql ( wxString ( "DROP INDEX IF EXISTS OperationsDetailsOperationObjId;" ) );
	bTransactionOk &= this->executeSql ( wxString ( "DROP INDEX IF EXISTS BudgetsObjId;" ) ); 
	bTransactionOk &= this->executeSql ( wxString ( "DROP INDEX IF EXISTS BudgetsDescription;" ) );

	// Indexes creation
	bTransactionOk &= this->executeSql ( wxString ( "CREATE INDEX IF NOT EXISTS Accounts_ObjId ON Accounts ( ObjId );" ) );
	bTransactionOk &= this->executeSql ( wxString ( "CREATE INDEX IF NOT EXISTS Accounts_AccountNumber ON Accounts ( AccountNumber );" ) );

	bTransactionOk &= this->executeSql ( wxString ( "CREATE INDEX IF NOT EXISTS Operations_ObjId ON Operations ( ObjId );" ) );
	bTransactionOk &= this->executeSql ( wxString ( "CREATE INDEX IF NOT EXISTS Operations_AccountObjId ON Operations ( AccountObjId );" ) );
	bTransactionOk &= this->executeSql ( wxString ( "CREATE INDEX IF NOT EXISTS Operations_Operations ON Operations ( AccountObjId, OperationDate DESC, OperationNumber DESC );" ) );
	bTransactionOk &= this->executeSql ( wxString ( "CREATE INDEX IF NOT EXISTS Operations_ValueDate ON Operations ( ValueDate );" ) );

	bTransactionOk &= this->executeSql ( wxString ( "CREATE INDEX IF NOT EXISTS OperationsDetails_ObjId ON OperationsDetails ( ObjId );" ) );
	bTransactionOk &= this->executeSql ( wxString ( "CREATE INDEX IF NOT EXISTS OperationsDetails_OperationObjId ON OperationsDetails ( OperationObjId );" ) );

	bTransactionOk &= this->executeSql ( wxString ( "CREATE INDEX IF NOT EXISTS Budgets_ObjId ON Budgets ( ObjId );" ) );
	bTransactionOk &= this->executeSql ( wxString ( "CREATE INDEX IF NOT EXISTS Budgets_Description ON Budgets ( Description );" ) );

	bTransactionOk &= this->executeSql ( wxString ( "CREATE INDEX IF NOT EXISTS AttributionsGroups_ObjId ON AttributionsGroups ( ObjId );" ) );
	bTransactionOk &= this->executeSql ( wxString ( "CREATE INDEX IF NOT EXISTS AttributionsGroups_GroupDescription ON AttributionsGroups ( GroupDescription );" ) );

	bTransactionOk &= this->executeSql ( wxString ( "CREATE INDEX IF NOT EXISTS Attributions_ObjId ON Attributions ( ObjId );" ) );
	bTransactionOk &= this->executeSql ( wxString ( "CREATE INDEX IF NOT EXISTS Attributions_GroupObjId ON Attributions ( GroupObjId );" ) );
	bTransactionOk &= this->executeSql ( wxString ( "CREATE INDEX IF NOT EXISTS Attributions_BudgetObjId ON Attributions ( BudgetObjId );" ) );

	bTransactionOk &= this->executeSql ( wxString ( "CREATE INDEX IF NOT EXISTS OperationsAttributions_ObjId ON OperationsAttributions ( ObjId );" ) );
	bTransactionOk &= this->executeSql ( wxString ( "CREATE INDEX IF NOT EXISTS OperationsAttributions_OperationObjId ON OperationsAttributions ( OperationObjId );" ) );
	bTransactionOk &= this->executeSql ( wxString ( "CREATE INDEX IF NOT EXISTS OperationsAttributions_AttributionObjId ON OperationsAttributions ( AttributionObjId );" ) );

	// view deletion
	bTransactionOk &= this->executeSql ( wxString ( "DROP VIEW IF EXISTS OperationsView;" ) );
	bTransactionOk &= this->executeSql ( wxString ( "DROP VIEW IF EXISTS AttrbutionOperationsView;" ) );
	bTransactionOk &= this->executeSql ( wxString ( "DROP VIEW IF EXISTS AccountsView;" ) );
	bTransactionOk &= this->executeSql ( wxString ( "DROP VIEW IF EXISTS OperationsDetailsView;" ) );

	// view update
	bTransactionOk &= this->executeSql ( wxString ( "CREATE VIEW IF NOT EXISTS OperationsView AS SELECT ObjId AS OpeObjId, AccountObjId, OperationNumber, OperationDate, ValueDate, AttributionDate, Amount, Description FROM Operations;" ) );
	bTransactionOk &= this->executeSql ( wxString ( "CREATE VIEW IF NOT EXISTS OperationsAttributionsView AS SELECT count ( 1 ) AS AttributionNumber, OperationObjId FROM OperationsAttributions group by OperationObjId;" ) );
	bTransactionOk &= this->executeSql ( wxString ( "CREATE VIEW IF NOT EXISTS AccountsView AS SELECT ObjId AS AccObjId, CanBeImported, AccountNumber FROM Accounts;" ) );
	bTransactionOk &= this->executeSql ( wxString ( "CREATE VIEW IF NOT EXISTS OperationsDetailsView AS SELECT COUNT ( 1 ) AS DetailNumber, OperationObjId FROM OperationsDetails GROUP BY OperationObjId;" ) );

	// Version update
	bTransactionOk &= this->executeSql ( wxString ( "Update Versions set MicroVersion = 3;" ) );

	if ( bTransactionOk )
	{
		// update executed correctly
		this->executeSql ( wxString ( "COMMIT;") );
		return CySqliteDb::kNewOpenOk;
	}
	else
	{
		// update not executed
		this->executeSql ( wxString ( "ROLLBACK TRANSACTION;") );
		return CySqliteDb::kNewOpenErrorUpgrade103;
	}
}

/* ---------------------------------------------------------------------------- */

CySqliteDb::NewOpenErrors CySqliteDb::upgradeToVersion110()
{
	// starting the upgrade
	bool bTransactionOk = true;

	bTransactionOk &= this->executeSql ( wxString ( "BEGIN EXCLUSIVE TRANSACTION;" ) );

	// parameters table creation
	bTransactionOk &= this->executeSql ( wxString ( "CREATE TABLE IF NOT EXISTS Parameters (ParameterName TEXT, TextValue TEXT, IntegerValue INTEGER);" ) );
	bTransactionOk &= this->executeSql ( wxString ( "CREATE INDEX IF NOT EXISTS Parameters_ParameterName ON Parameters ( ParameterName );" ) );

	// Accounts table modification
	bTransactionOk &= this->executeSql ( wxString ( "ALTER TABLE Accounts ADD COLUMN ValidToDate TEXT;" ) );
	bTransactionOk &= this->executeSql ( wxString ( "UPDATE Accounts SET ValidToDate = \"2099-12-31\";" ) );

	// Attributions table modification
	bTransactionOk &= this->executeSql ( wxString ( "ALTER TABLE Attributions ADD COLUMN ValidToDate TEXT;" ) );
	bTransactionOk &= this->executeSql ( wxString ( "UPDATE Attributions SET ValidToDate = \"2099-12-31\";" ) );

	// Version update
	bTransactionOk &= this->executeSql ( wxString ( "UPDATE Versions SET MinorVersion = 1;" ) );
	bTransactionOk &= this->executeSql ( wxString ( "UPDATE Versions SET MicroVersion = 0;" ) );

	if (bTransactionOk)
	{
		// update executed correctly
		this->executeSql(wxString("COMMIT;"));
		return CySqliteDb::kNewOpenOk;
	}
	else
	{
		// update not executed
		this->executeSql(wxString("ROLLBACK TRANSACTION;"));
		return CySqliteDb::kNewOpenErrorUpgrade103;
	}
}

/* ---------------------------------------------------------------------------- */

CySqliteDb& CySqliteDb::getInstance ( )
{
	return m_objSqliteDb;
};

/* ---------------------------------------------------------------------------- */

wxString CySqliteDb::getLastError ( )
{
	return wxString ( sqlite3_errmsg ( this->m_pSqlite3 ) );
}

/* ---------------------------------------------------------------------------- */

bool CySqliteDb::evaluateSql ( const wxString& strSql )
{
	// testing if the SQLite db is opened
	if ( ! m_objSqliteDb.m_bInitialized )
	{
		return false;
	}

	this->logSql ( strSql );

	// compilation of the SQL statement...
	const char* pstrUnusedSql = NULL;
	sqlite3_stmt* pSqlite3Stmt;
	int iReturnCode = sqlite3_prepare_v2 (
							this->m_pSqlite3,
							strSql.ToUTF8 ( ),
							-1,
							&pSqlite3Stmt,
							&pstrUnusedSql );

	sqlite3_finalize ( pSqlite3Stmt );

	return SQLITE_OK == iReturnCode;
}

/* ---------------------------------------------------------------------------- */

bool CySqliteDb::executeSql ( const wxString& strSql )
{
	// testing if the SQLite db is opened
	if ( ! m_objSqliteDb.m_bInitialized )
	{
		return false;
	}

	this->logSql ( strSql );

	// compilation of the SQL statement...
	const char* pstrUnusedSql = NULL;
	sqlite3_stmt* pSqlite3Stmt;
	int iReturnCode = sqlite3_prepare_v2 (
							this->m_pSqlite3,
							strSql.ToUTF8 ( ),
							-1,
							&pSqlite3Stmt,
							&pstrUnusedSql );

	if ( SQLITE_OK != iReturnCode )
	{
		// an error occurs. We log the error and we exit
		this->logError ( strSql );
		sqlite3_finalize ( pSqlite3Stmt );

		return false;
	}

	// Execution of the SQL statement
	iReturnCode = sqlite3_step ( pSqlite3Stmt );

	if ( SQLITE_DONE != iReturnCode )
	{
		// an error occurs. We log the error and we exit
		this->logError ( strSql );
		sqlite3_finalize ( pSqlite3Stmt );

		return false;
	}

	// the SQL statement is closed
	iReturnCode = sqlite3_finalize ( pSqlite3Stmt );

	if ( SQLITE_OK != iReturnCode )
	{
		// an error occurs. We log the error and we exit
		this->logError ( strSql );

		return false;
	}

	return true;
}

/* ---------------------------------------------------------------------------- */

bool CySqliteDb::getSingleValue ( const wxString & strSql, long long* pValue )
{
	CyLongValue lObjLongValue;
	if ( this->getSingleValue ( strSql, &lObjLongValue ) )
	{
		*pValue = lObjLongValue.get ( CyLongValue::m_lDummyValue );
		return true;
	}

	return false;
}

/* ---------------------------------------------------------------------------- */

bool CySqliteDb::getSingleValue ( const wxString & strSql, wxString* pValue )
{
	CyStringValue lObjStringValue;
	if ( this->getSingleValue ( strSql, &lObjStringValue ) )
	{
		*pValue = lObjStringValue.get ( CyStringValue::m_strDummyValue );
		return true;
	}

	return false;
}

/* ---------------------------------------------------------------------------- */

bool CySqliteDb::getSingleValue ( const wxString & strSql, CyValue* pValue )
{
	// testing if the SQLite db is opened
	if ( ! m_objSqliteDb.m_bInitialized )
	{
		return false;
	}

	this->logSql ( strSql );

	// compilation of the SQL statement...
	const char* pstrUnusedSql = NULL;
	sqlite3_stmt* pSqlite3Stmt;
	int iReturnCode = sqlite3_prepare_v2 (
							this->m_pSqlite3,
							strSql.ToUTF8 ( ),
							-1,
							&pSqlite3Stmt,
							&pstrUnusedSql );

	if ( SQLITE_OK != iReturnCode )
	{
		// an error occurs. We log the error and we exit
		this->logError ( strSql );
		sqlite3_finalize ( pSqlite3Stmt );

		return false;
	}

	int iColumnNumber = sqlite3_column_count ( pSqlite3Stmt );
	if ( 1 != iColumnNumber )
	{
		// More or less than one column found. The SQL is invalid...
		sqlite3_finalize ( pSqlite3Stmt );

		return false;
	}

	// Execution of the SQL statement
	iReturnCode = sqlite3_step ( pSqlite3Stmt );

	if ( SQLITE_ROW != iReturnCode )
	{
		// an error occurs. We log the error and we exit
		this->logError ( strSql );
		sqlite3_finalize ( pSqlite3Stmt );

		return false;
	}

	CyValue * pTmpValue = NULL;

	// we search the type of the column
	switch (  sqlite3_column_type ( pSqlite3Stmt, 0 ) )
	{
		case SQLITE_INTEGER:
			{
				// the type is integer
				long long lValue = sqlite3_column_int64 ( pSqlite3Stmt , 0 );

				// we test if the value is not null (sqlite3_column_text returns a null pointer in this case)...
				const unsigned char* pUCharValue = sqlite3_column_text ( pSqlite3Stmt, 0 );
				if ( pUCharValue )
				{
					// ... and we add the value 
					pTmpValue = new CyLongValue;
					pTmpValue->set ( lValue );
				}
			}
			break;

		case SQLITE_FLOAT:
			{
				sqlite3_finalize ( pSqlite3Stmt );

				return false;
			}
			break;

		case SQLITE_TEXT:
			{
				// the type is text

				// we test if the value is not null (sqlite3_column_text returns a null pointer in this case)...
				const unsigned char* pUCharValue = sqlite3_column_text ( pSqlite3Stmt, 0 );
				wxString strValue = wxEmptyString;
				if ( pUCharValue )
				{
					// ... and we add the value 
					strValue = wxString::FromUTF8Unchecked ( ( char* ) ( pUCharValue ) );
				}

				if ( 0 < strValue.length ( ) )
				{
					pTmpValue = new CyStringValue;
					pTmpValue->set ( strValue );
				}
			}
			break;

		default:
			{
				sqlite3_finalize ( pSqlite3Stmt );

				return false;
			}
			break;
	}

	iReturnCode = sqlite3_step ( pSqlite3Stmt );
	if ( SQLITE_DONE != iReturnCode )
	{
		// more than one row was returned
		sqlite3_finalize ( pSqlite3Stmt );
		if ( NULL != pTmpValue )
		{
			delete pTmpValue;
		}

		return false;
	}

	// the SQL statement is closed
	iReturnCode = sqlite3_finalize ( pSqlite3Stmt );
	if ( SQLITE_OK != iReturnCode )
	{
		// an error occurs.
		return false;
	}

	bool bReturnValue = false;

	if ( ( NULL != dynamic_cast < CyLongValue* > ( pValue ) ) && ( NULL != dynamic_cast < CyLongValue* > ( pTmpValue ) ) )
	{
		pValue->set ( pTmpValue->get ( CyLongValue::m_lDummyValue ) );
		bReturnValue = true;
	}
	else if ( ( NULL != dynamic_cast < CyStringValue* > ( pValue ) ) && ( NULL != dynamic_cast < CyStringValue* > ( pTmpValue ) ) )
	{
		pValue->set ( pTmpValue->get ( CyStringValue::m_strDummyValue ) );
		bReturnValue = true;
	}

	if ( NULL != pTmpValue )
	{
		delete pTmpValue;
	}

	return bReturnValue;
}

/* ---------------------------------------------------------------------------- */

bool CySqliteDb::executeQuery ( wxString strSql, CyQueryResult& objQueryResult )
{
	// the query result is cleaned
	objQueryResult.clear ( );

	// testing if the SQLite db is opened
	if ( ! m_objSqliteDb.m_bInitialized )
	{
		return false;
	}

	this->logSql ( strSql );

	// compilation of the SQL statement...
	const char* pstrUnusedSql = NULL;
	sqlite3_stmt* pSqlite3Stmt;
	int iReturnCode = sqlite3_prepare_v2 (
							this->m_pSqlite3,
							strSql.ToUTF8 ( ),
							-1,
							&pSqlite3Stmt,
							&pstrUnusedSql );

	if ( SQLITE_OK != iReturnCode )
	{
		// an error occurs. We log the error and we exit
		this->logError ( strSql );
		sqlite3_finalize ( pSqlite3Stmt );

		return false;
	}

	// Iteration on the columns
	int iColumnNumber = sqlite3_column_count ( pSqlite3Stmt );

	for ( int iColumnCounter = 0; iColumnCounter < iColumnNumber; iColumnCounter++ )
	{
		// and the column name is added to the header of the query result object
		wxString strHeaderName = wxString::FromUTF8Unchecked ( sqlite3_column_name ( pSqlite3Stmt, iColumnCounter ) );
		if ( 
			( 
			 ( 0 < strHeaderName.length ( ) ) 
			 && 
			 ( CyStartFormat != strHeaderName.at ( 0 ) ) 
			)
			|| 
			( 0 == strHeaderName.length ( ) )
		   )
		{
			objQueryResult.m_strHeadersVector.push_back ( strHeaderName );
		}
		 
	}

	// iteration on the rows
	iReturnCode = SQLITE_ROW;
	int iRowCount = 0;
	wxString strFormat = wxEmptyString;
	while ( SQLITE_ROW == iReturnCode  )
	{
		// Execution of the SQL statement
		iReturnCode = sqlite3_step ( pSqlite3Stmt );

		if ( SQLITE_DONE == iReturnCode )
		{	// No new row found we go to the end of the loop
			continue;
		}

		if ( SQLITE_ROW != iReturnCode  && SQLITE_DONE != iReturnCode )
		{
			// an error occurs. We log the error and we exit
			this->logError ( strSql );
			sqlite3_finalize ( pSqlite3Stmt );
			objQueryResult.clear ( );

			return false;
		}

		// iteration on the row values
		CyQueryResult::CyQueryResultValuesRow valuesRowVector;
		for ( int iColumnCounter = 0; iColumnCounter < iColumnNumber; iColumnCounter++ )
		{
			CyValue* pValue;

			// we search the type of the column
			switch (  sqlite3_column_type ( pSqlite3Stmt, iColumnCounter ) )
			{
				case SQLITE_INTEGER:
				{
					// the type is integer
					pValue = new CyLongValue;
					long long lValue = sqlite3_column_int64 ( pSqlite3Stmt , iColumnCounter );

					// we test if the value is not null (sqlite3_column_text returns a null pointer in this case)...
					const unsigned char* pUCharValue = sqlite3_column_text ( pSqlite3Stmt, iColumnCounter );
					if ( pUCharValue )
					{
						// ... and we add the value 
						pValue->set ( lValue, strFormat );
					}
					strFormat.clear ( );
				}
				break;

				case SQLITE_FLOAT:
				break;

				case SQLITE_TEXT:
				{
					// the type is text

					// we test if the value is not null (sqlite3_column_text returns a null pointer in this case)...
					const unsigned char* pUCharValue = sqlite3_column_text ( pSqlite3Stmt, iColumnCounter );
					wxString strValue = wxEmptyString;
					if ( pUCharValue )
					{
						// ... and we add the value 
						strValue = wxString::FromUTF8Unchecked ( ( char* ) ( pUCharValue ) );
					}

					if ( ( 0 < strValue.length ( ) ) && ( CyStartFormat == strValue.at ( 0 ) ) )
					{
						strFormat = strValue;
					}
					else
					{
						pValue = new CyStringValue;
						pValue->set ( strValue, strFormat );
						strFormat.clear ( );
					}
				}
				break;

				default:
					// a null CyStringValue is added
					pValue = new CyStringValue;
					strFormat.clear ( );
					break;
			}

			if ( strFormat.empty ( ) )
			{
				// the value is added to the row
				valuesRowVector.push_back ( pValue );
			}
		} // end of the iteration on the row values

		// the row is added to the CyQueryResult object
		objQueryResult.m_QueryResultValues.push_back ( valuesRowVector );

		iRowCount++;

	}// end of the iteration on the rows

	if ( SQLITE_DONE != iReturnCode )
	{
		// an error occurs. We log the error, we clean the CyQueryResult object and we exit
		this->logError ( strSql );
		sqlite3_finalize ( pSqlite3Stmt );
		objQueryResult.clear ( );

		return false;
	}

	// the SQL statement is closed
	iReturnCode = sqlite3_finalize ( pSqlite3Stmt );
	if ( SQLITE_OK != iReturnCode )
	{
		// an error occurs. We log the error, we clean the CyQueryResult object and we exit
		sqlite3_finalize ( pSqlite3Stmt );
		objQueryResult.clear ( );

		return false;
	}

	return true;
}

/* ---------------------------------------------------------------------------- */

void CySqliteDb::logError ( const wxString& strSql )
{
		// the current datetime is searched...
		wxDateTime objCurrentDateTime;
		objCurrentDateTime.SetToCurrent ( );
		// ... and added  to the error log file
		this->m_ErrorLogStream << "--" << objCurrentDateTime.FormatISOCombined ( ).ToStdString ( )  << std::endl;

		// last error message is searched...
		std::string strErrorMessage = sqlite3_errmsg ( this->m_pSqlite3 );
		//... and added to the error log file
		this->m_ErrorLogStream << strErrorMessage << std::endl << strSql.ToStdString ( ) << std::endl << std::flush;
}

/* ---------------------------------------------------------------------------- */

void CySqliteDb::logSql ( const wxString& strSql )
{
	// the current datetime is searched...
	wxDateTime objCurrentDateTime;
	objCurrentDateTime.SetToCurrent ( );
	// ... and added as remark to the SQL log file
	this->m_SqlLogStream << "--" << objCurrentDateTime.FormatISOCombined ( ).ToStdString ( )  << std::endl;
	this->m_SqlLogStream << CyUtf8WxStringTranslator().fromWxStringToUtf8 ( strSql ) << std::endl << std::flush;
}

/* ---------------------------------------------------------------------------- */
