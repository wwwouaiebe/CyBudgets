/* ---------------------------------------------------------------------------- */
//! CyBudgets.cpp
/* ---------------------------------------------------------------------------- */
//!
//! \file CyBudgets.cpp
//! \brief
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

//! \mainpage CyBudgets
//! contact: http://www.ouaie.be/
//!
//! Copyright ( C ) 2014 - Christian Guyette
//!
//! This program is free software: you can redistribute it and/or modify
//! it under the terms of the GNU General Public License as published by
//! the Free Software Foundation, either version 3 of the License, or
//! any later version.
//!
//! This program is distributed in the hope that it will be useful,
//! but WITHOUT ANY WARRANTY; without even the implied warranty of
//! MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
//! GNU General Public License for more details.
//! You should have received a copy of the GNU General Public License
//! along with this program. If not, see http://www.gnu.org/licenses/.
//!
//!		<h1>Libraries documentation</h1>
//!
//! <a href = "../warning.txt">Doxygen warnings</a>
//!
//! <a href="https://www.sqlite.org/c3ref/intro.html" target="_blank">SQLite documentation</a>
//!
//! <a href="http://docs.wxwidgets.org/3.0/" target="_blank">wxWidgets documentation</a>
//!
//! <a href="http://en.cppreference.com/w/" target="_blank">cppreference</a>
//!
//! <a href="http://www.cplusplus.com/reference/" target="_blank">cplusplus</a>
//!
//!
//!		<h1>Data model</h1>
//!
//!		<h2>TABLE Accounts</h2>
//!			- ObjId INTEGER PRIMARY KEY DESC
//!			- AccountNumber TEXT
//!			- AccountOwner TEXT
//!			- CanBeImported INTEGER
//!			- InitialAmount REAL ( till version 1.0.2 )
//!			- InitialAmount INTEGER (since version (1.0.3 )
//!			- ValidSinceDate TEXT
//!
//!		This table stores informations about the accounts
//!
//!		Field ObjId : unique identifier for the account used internaly for SQL requests
//!
//!		Field AccountNumber: the account number as described in the .CSV files used for the importation of the operations
//!
//!		Field AccountOwner : free text for the account description
//!
//!		Field CanBeImported : a value indicating when the operations on an account are imported from a file ( CanBeImported = 1 ) or no ( CanBeImported = 0 ). See also CyEnum::AccountCanBeImported
//!
//!		Field InitialAmount : the initial amount of the account (since version 1.0.2)
//!
//!		Field ValidSinceDate : the date since the initial amount is valid (since version 1.0.2)
//!
//!		<h2>TABLE Operations</h2>
//!			- ObjId INTEGER PRIMARY KEY DESC
//!			- AccountObjId INTEGER
//!			- OperationNumber INTEGER
//!			- OperationDate TEXT
//!			- ValueDate TEXT
//!			- AttributionDate TEXT
//!			- Amount REAL ( till version 1.0.2 )
//!			- Amount INTEGER (since version (1.0.3 )
//!			- Description TEXT
//!
//!		This table stores informations about the operations on an account
//!
//!		Field ObjId : unique identifier for the operation used internaly for SQL requests
//!
//!		Field AccountObjId : The ObjId field of the account in the table Account
//!
//!		Field OperationNumber : the operation number as given in the .CSV files used for the importation of the operations
//!
//!		Field OperationDate : the operation date in the ISO format as given in the .CSV files used for the importation of the operations
//!
//!		Field ValueDate : the value date in the ISO format as given in the .CSV files used for the importation of the operations
//!
//!		Field AttributionDate : the attribution date (given by user) in the ISO format. This is the date used for the budget analyses
//!
//!		Field Amount : the operation amount as given in the .CSV files used for the importation of the operations
//!
//!		Field Description : free text for the operation description. Can be modified by the user
//!
//!		<h2>TABLE OperationsDetails</h2>
//!			- ObjId INTEGER PRIMARY KEY DESC
//!			- OperationObjId INTEGER
//!			- Detail TEXT
//!
//!		This table stores informations about the operations details. Details are coming from the .CSV files used for the importation
//!		and cannot be modified
//!
//!		Field ObjId : unique identifier for the detail used internaly for SQL requests
//!
//!		Field OperationObjId the ObjId field of the operation in the table Operations
//!
//!		Field Detail : a description coming from the .CSV files used for the importation
//!
//!		<h2>TABLE Budgets</h2>
//!			- ObjId INTEGER PRIMARY KEY DESC
//!			- Description TEXT
//!
//!		This table stores informations about the budgets. Budgets are used for the analyse and are created by the user
//!
//!		Field ObjId : unique identifier for the budget used internaly for SQL requests
//!
//!		Field Description : free text for the budget description. Can be modified by the user
//!
//!		<h2>TABLE AttributionsGroups</h2>
//!			- ObjId  INTEGER PRIMARY KEY DESC
//!			- GroupDescription TEXT
//!
//!			This table stores informations about attribution's groups.
//!
//!		Field ObjId : unique identifier for the groups used internaly for SQL requests
//!
//!		Field GroupDescription : free text for the group description
//!
//!		<h2>TABLE Attributions</h2>
//!			- ObjId INTEGER PRIMARY KEY DESC
//!			- MainDescription TEXT ( till version 1.0.2 )
//!			- GroupObjId INTEGER ( since version 1.0.3 )
//!			- Description TEXT
//!			- BudgetObjId INTEGER
//!
//!		This table stores informations about attributions.
//!		Attributions are used to group the account operations in an analyse
//!
//!		Field ObjId : unique identifier for the attributiosn used internaly for SQL requests
//!
//!		Field MainDescription : free text used to group the attributions
//!
//!		Field GroupObjId : the ObjId field of the group in the table AttributionsGroups
//!
//!		Field Description : free text for the attribution description
//!
//!		Field BudgetObjId : the ObjId field of the budget in the table Budgets
//!
//!		<h2>TABLE OperationsAttributions</h2>
//!			- ObjId INTEGER PRIMARY KEY DESC
//!			- AttributionObjId INTEGER
//!			- OperationObjId INTEGER
//!			- Amount REAL ( till version 1.0.2 )
//!			- Amount INTEGER (since version (1.0.3 )
//!
//!		This table is used to do the link between operations and attributions. An operation can have more than one Attribution but
//!		the sum of the amounts of attribution must be equal to the operation ammount
//!
//!		Field ObjId : unique identifier for the group ( attribution - operation ) used internaly for SQL requests
//!
//!		Field AttributionObjId : the objId in the table Attributions
//!
//!		Field OperationObjId : the ObjId in the table Operations
//!
//!		Field Amount: the amount given by user.
//!
//!		<h2>TABLE Versions (since version 1.0.2)</h2>
//!			- Application TEXT
//!			- MajorVersion INTEGER
//!			- MinorVersion INTEGER
//!			- MicroVersion INTEGER
//!
//!		This table is used to store the current version of the database
//!
//!		Field Application : the name of the application
//!
//!		Field MajorVersion : the major version of the database
//!
//!		Field MinorVersion : the minor version of the database
//!
//!		Field MicroVersion : the macro version of the database
//!
//!		<h1>SQL for database creation</h1>
//!		<h2>SQL for tables creation</h2>
//!
//!		CREATE TABLE IF NOT EXISTS Accounts (ObjId INTEGER PRIMARY KEY DESC, AccountNumber TEXT, AccountOwner TEXT, CanBeImported INTEGER, InitialAmount INTEGER, ValidSinceDate TEXT);
//!
//!		CREATE TABLE IF NOT EXISTS OperationsAttributions (ObjId INTEGER PRIMARY KEY DESC, AttributionObjId INTEGER, OperationObjId INTEGER, Amount INTEGER);
//!
//!		CREATE TABLE IF NOT EXISTS AttributionsGroups (ObjId INTEGER PRIMARY KEY DESC, GroupDescription TEXT);
//!
//!		CREATE TABLE IF NOT EXISTS Attributions (ObjId INTEGER PRIMARY KEY DESC, GroupObjId INTEGER, Description TEXT, BudgetObjId INTEGER);
//!
//!		CREATE TABLE IF NOT EXISTS Operations (ObjId INTEGER PRIMARY KEY DESC, AccountObjId INTEGER, OperationNumber INTEGER, OperationDate TEXT, ValueDate TEXT,AttributionDate TEXT, Amount INTEGER, Description TEXT);
//!
//!		CREATE TABLE IF NOT EXISTS OperationsDetails (ObjId INTEGER PRIMARY KEY DESC, OperationObjId INTEGER, Detail TEXT);
//!
//!		CREATE TABLE IF NOT EXISTS Budgets (ObjId INTEGER PRIMARY KEY DESC, Description TEXT);
//!
//!		CREATE TABLE IF NOT EXISTS Versions (Application TEXT, MajorVersion INTEGER, MinorVersion INTEGER, MicroVersion INTEGER);
//!
//!		<h2>SQL for triggers creation</h2>
//!
//!		<h3>Trigger for account deletion</h3>
//!
//!		CREATE TRIGGER IF NOT EXISTS DeleteAccountTrigger BEFORE DELETE ON Accounts BEGIN DELETE FROM Operations WHERE AccountObjId = old.ObjId; END; 
//!
//!		<h3>Trigger for account deletion and operation deletion</h3>
//!
//!		CREATE TRIGGER IF NOT EXISTS DeleteOperationTrigger BEFORE DELETE ON Operations BEGIN DELETE FROM OperationsDetails WHERE OperationObjId = old.ObjId; DELETE FROM OperationsAttributions WHERE OperationObjId = old.ObjId; END;
//!
//!		<h3>Triggers for budget deletion</h3>
//!
//!		CREATE TRIGGER IF NOT EXISTS DeleteBudgetTrigger BEFORE DELETE ON Budgets BEGIN DELETE FROM Attributions WHERE BudgetObjId = old.ObjId; END;
//!
//!		CREATE TRIGGER IF NOT EXISTS DeleteAttributionGroupTrigger BEFORE DELETE ON AttributionsGroups BEGIN DELETE FROM Attributions WHERE GroupObjId = old.ObjId; END;
//!
//!		CREATE TRIGGER IF NOT EXISTS DeleteAttributionTrigger BEFORE DELETE ON Attributions BEGIN DELETE FROM OperationsAttributions WHERE AttributionObjId = old.ObjId; END;
//!
//!		<h2>SQL for records creation</h2>
//!
//!		INSERT INTO Versions ( Application, MajorVersion, MinorVersion, MicroVersion ) values ( "CyBudgets", 1, 0, 3);
//!
//!		<h2>SQL for indexes creation</h2>
//!
//!		CREATE INDEX IF NOT EXISTS Accounts_ObjId ON Accounts ( ObjId );
//!		
//!		CREATE INDEX IF NOT EXISTS Accounts_AccountNumber ON Accounts ( AccountNumber );
//!		
//!		CREATE INDEX IF NOT EXISTS Operations_ObjId ON Operations ( ObjId );
//!		
//!		CREATE INDEX IF NOT EXISTS Operations_AccountObjId ON Operations ( AccountObjId );
//!		
//!		CREATE INDEX IF NOT EXISTS Operations_Operations ON Operations ( AccountObjId, OperationDate DESC, OperationNumber DESC );
//!		
//!		CREATE INDEX IF NOT EXISTS Operations_ValueDate ON Operations ( ValueDate );
//!		
//!		CREATE INDEX IF NOT EXISTS OperationsDetails_ObjId ON OperationsDetails ( ObjId );
//!		
//!		CREATE INDEX IF NOT EXISTS OperationsDetails_OperationObjId ON OperationsDetails ( OperationObjId );
//!		
//!		CREATE INDEX IF NOT EXISTS Budgets_ObjId ON Budgets ( ObjId );
//!		
//!		CREATE INDEX IF NOT EXISTS Budgets_Description ON Budgets ( Description );
//!		
//!		CREATE INDEX IF NOT EXISTS AttributionsGroups_ObjId ON AttributionsGroups ( ObjId );
//!		
//!		CREATE INDEX IF NOT EXISTS AttributionsGroups_GroupDescription ON AttributionsGroups ( GroupDescription );
//!		
//!		CREATE INDEX IF NOT EXISTS Attributions_ObjId ON Attributions ( ObjId );
//!		
//!		CREATE INDEX IF NOT EXISTS Attributions_GroupObjId ON Attributions ( GroupObjId );
//!		
//!		CREATE INDEX IF NOT EXISTS Attributions_BudgetObjId ON Attributions ( BudgetObjId );
//!		
//!		CREATE INDEX IF NOT EXISTS OperationsAttributions_ObjId ON OperationsAttributions ( ObjId );
//!		
//!		CREATE INDEX IF NOT EXISTS OperationsAttributions_OperationObjId ON OperationsAttributions ( OperationObjId );
//!		
//!		CREATE INDEX IF NOT EXISTS OperationsAttributions_AttributionObjId ON OperationsAttributions ( AttributionObjId );
//!
//!		<h2>SQL for view creation</h2>
//!
//!		CREATE view IF NOT EXISTS AccountsView as select ObjId as AccObjId, CanBeImported, AccountNumber from Accounts;
//!
//!		CREATE view IF NOT EXISTS OperationsView as select ObjId as OpeObjId, AccountObjId, OperationNumber, OperationDate, ValueDate, AttributionDate, Amount, Description from Operations;
//!
//!		CREATE view IF NOT EXISTS OperationsDetailsView as select count ( 1 ) as DetailNumber, OperationObjId from OperationsDetails group by OperationObjId;
//!
//!		CREATE view IF NOT EXISTS OperationsAttributionsView as select count ( 1 ) as AttributionNumber, OperationObjId from OperationsAttributions group by OperationObjId;
//!

/* ---------------------------------------------------------------------------- */

#include "UserInterfaceLayer/CyWxBudgetsApp.h"

/* ---------------------------------------------------------------------------- */

//! \fn wxIMPLEMENT_APP(CyWxBudgetsApp)
//! See wxWidget documentation

wxIMPLEMENT_APP(CyWxBudgetsApp);

/* ---------------------------------------------------------------------------- */
