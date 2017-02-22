/* ---------------------------------------------------------------------------- */
//! CyIngImportTool.cpp
/* ---------------------------------------------------------------------------- */
//!
//! \file CyIngImportTool.cpp
//! \brief definition file for class CyIngImportTool
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

#include "CoreLayer/CyIngImportTool.h"
#include "DataLayer/CyLongValue.h"
#include "DataLayer/CySqliteDb.h"
#include "UtilitiesLayer/CyEnum.h"
#include "UtilitiesLayer/CyGetText.h"
#include "UtilitiesLayer/CyIngDateParser.h"
#include "UtilitiesLayer/CyIngDetailParser.h"
#include "UtilitiesLayer/CyStringParser.h"

/* ---------------------------------------------------------------------------- */

CyIngImportTool::CyIngImportTool ( )
{
}

/* ---------------------------------------------------------------------------- */

CyIngImportTool::~CyIngImportTool ( )
{
}

/* ---------------------------------------------------------------------------- */

CyIngImportTool::ImportError CyIngImportTool::import ( const wxString& strFileName, void ( callback ) ( const wxString & strMessage, const wxString& strCaption ) )
{
	this->m_lOperationObjId = this->getObjId ( wxString ( "Operations" ) );
	this->m_lOperationDetailObjId = this->getObjId ( wxString ( "OperationsDetails" ) );

	if ( ( CyEnum::kInvalidObjId == this->m_lOperationObjId ) || ( CyEnum::kInvalidObjId == this->m_lOperationDetailObjId ) )
	{
		return CyIngImportTool::kImportErrorGetObjId;
	}

	std::ifstream fileStream ( strFileName.ToStdString ( ).data ( ) );
	if ( ! fileStream )
	{
		return CyIngImportTool::kImportErrorOpenFile;
	}

	unsigned int iImportCounter = 0;
	unsigned int iCounter = 1;
	std::string strRow;
	if ( ! fileStream.good ( ) || fileStream.bad ( ) || fileStream.fail ( ) )
	{
		return CyIngImportTool::kImportErrorOpenFile;
	}

	// reading the header line in the file
	std::getline ( fileStream, strRow );

	CyStringParser objLineParser;
	CyIngDateParser objDateParser;

	// reading the file
	while ( ( ! fileStream.eof (  ) ) )
	{
		++ iCounter;

		if ( ! fileStream.good ( ) || fileStream.bad ( ) || fileStream.fail ( ) )
		{
			return CyIngImportTool::kImportErrorReadFile;
		}

		bool bTransactionOk = false;
		// reading a line in the file
		std::getline ( fileStream, strRow );

		// and parsing the line
		objLineParser.parse ( ";", strRow) ;

		enum
		{
			kParserAccountNumber = 0,
			kParserAccountName = 1,
			kParserOtherAccountNumber = 2,
			kParserOperationNumber = 3,
			kParserOperationDate = 4,
			kParserValueDate = 5,
			kParserAmount = 6,
			kParserDevise = 7,
			kParserLibelle = 8,
			kParserDetails = 9,
			kParserMessage = 10
		};

		if ( 10 <= objLineParser.size ( ) )
		{
			// starting the transaction
			bTransactionOk = CySqliteDb::getInstance ( ).executeSql ( wxString ( "BEGIN EXCLUSIVE TRANSACTION;") );
	
			// Search of the account ObjId
			wxString strOperationAccountNumber = wxString ( objLineParser.at ( kParserAccountNumber ) );
			long long lAccountObjId = CyEnum::kInvalidObjId;
			wxString strSql;
			strSql 
				<< wxString ( "SELECT a.objId from Accounts a where a.AccountNumber = \"" ) 
				<< strOperationAccountNumber
				<< wxString ( "\";" );

			bTransactionOk &= CySqliteDb::getInstance ( ).getSingleValue ( strSql, &lAccountObjId );

			bTransactionOk &= ( CyEnum::kInvalidObjId != lAccountObjId );

			// Operation number and dates
			long long lOperationNumber = atol ( objLineParser.at ( kParserOperationNumber ).data ( ) );
			wxString strOperationDate = wxString ( objDateParser.parseDate ( objLineParser.at ( kParserOperationDate ) ) );
			wxString strValueDate = wxString ( objDateParser.parseDate ( objLineParser.at ( kParserValueDate ) ) );

			// Operation amount.
			std::string strOperationAmount;
			std::string::const_iterator amountIterator;
			for ( amountIterator = objLineParser.at ( kParserAmount ).begin ( ); amountIterator != objLineParser.at ( kParserAmount ).end ( ); ++ amountIterator )
			{
				if ( ',' != *amountIterator )
				{
					strOperationAmount.push_back ( *amountIterator );
				}
			}

			// Libellés...
			long long  lOperationAmount = atol ( strOperationAmount.data ( ) );
			CyIngDetailParser objLibeleParser;
			objLibeleParser.parse (  objLineParser.at ( kParserLibelle ) );

			// ...and details
			CyIngDetailParser objDetailParser;
			objDetailParser.parse (  objLineParser.at ( kParserDetails ) );

			// Messages
			CyIngDetailParser objMessageParser;
			if ( 11 == objLineParser.size ( ) )
			{
				objMessageParser.parse (  objLineParser.at ( kParserMessage ) );
			}

			// Searching if the operation was already imported previously
			if ( ( ! objLineParser.at ( kParserOperationNumber ).empty ( ) ) && ( CyEnum::kInvalidObjId != lAccountObjId ) )
			{
				strSql.Clear ( );
				strSql
					<< wxString ( "select count ( 1 ) from Accounts a join Operations o on a.ObjId = o.AccountObjId " )
					<< wxString ( "where a.AccountNumber = \"" )
					<< strOperationAccountNumber
					<< wxString ( "\" and o.OperationNumber = " )
					<< lOperationNumber
					<< wxString ( " and o.OperationDate = \"" )
					<< strOperationDate
					<< wxString ( "\";" );

				long long lOperationCount = CyEnum::kInvalidObjId;
				bTransactionOk &= CySqliteDb::getInstance ( ).getSingleValue ( strSql, &lOperationCount );

				if ( bTransactionOk  &&  ( 0 == lOperationCount ) ) 
				{
					// The operation was not found. The operation is added to the db
					strSql.Clear ( );
					strSql
						<< wxString ( "INSERT into Operations " )
						<< wxString ( "( ObjId, AccountObjId, OperationNumber, OperationDate, ValueDate ,AttributionDate, Amount, Description ) " )
						<< wxString ( "values ( " )
						<< this->m_lOperationObjId
						<< wxString ( ", " )
						<< lAccountObjId
						<< wxString ( ", " )
						<< lOperationNumber
						<< wxString ( ", \"" )
						<< strOperationDate
						<< wxString ( "\", \"" )
						<< strValueDate
						<< wxString ("\", \"\", " )
						<< lOperationAmount
						<< wxString ( ", \"\" );" );

					bTransactionOk &= CySqliteDb::getInstance ( ).executeSql ( strSql );

					bTransactionOk &= this->insertDetails ( objLibeleParser );
					bTransactionOk &= this->insertDetails ( objDetailParser );
					bTransactionOk &= this->insertDetails ( objMessageParser );

					++ this->m_lOperationObjId;
					++ iImportCounter;
				}
			} //end if ( ( ! objLineParser.at ( 3 ).empty ( ) ) && ( CyEnum::kInvalidObjId != lAccountObjId ) )

			// Commit or Rollback
			if ( bTransactionOk )
			{
				CySqliteDb::getInstance ( ).executeSql ( wxString ( "COMMIT;") );
			}
			else
			{
				CySqliteDb::getInstance ( ).executeSql ( wxString ( "ROLLBACK TRANSACTION;") );
			}

			objLibeleParser.clear ( );
			objDetailParser.clear ( );
			objMessageParser.clear ( );

		} // end if ( 10 <= objLineParser.size ( ) )

		objLineParser.clear ( );

		if ( strRow.empty ( ) )
		{
			// to avoid an error message on the empty lines...
			bTransactionOk = true;
		}
		if ( ! bTransactionOk )
		{
			// error dialog
			wxString strErrorMessage;
			strErrorMessage
				<< CyGetText::getInstance ( ).getText ( "CyIngImportTool.import.FailedText1" )
				<< iCounter
				<< char ( 10 )
				<< CyGetText::getInstance ( ).getText ( "CyIngImportTool.import.FailedText2" )
				<< strFileName
				<< char ( 10 )
				<<CyGetText::getInstance ( ).getText ( "CyIngImportTool.import.FailedText3" );
			if ( NULL != callback )
			{
				callback (strErrorMessage, CyGetText::getInstance ( ).getText ( "CyIngImportTool.import.FailedCaption" ) );
			}
		}
	} // end while ( ( ! fileStream.eof (  ) ) )

	fileStream.close ( );

	wxString strInformationMessage;
	strInformationMessage
		<< CyGetText::getInstance ( ).getText ( "CyIngImportTool.import.InformationText1" )
		<<  wxString ( char ( 10 ) )
		<< iImportCounter
		<< CyGetText::getInstance ( ).getText ( "CyIngImportTool.import.InformationText2" );

	if ( NULL != callback )
	{
		callback (strInformationMessage, CyGetText::getInstance ( ).getText ( "CyIngImportTool.import.InformationCaption" ) );
	}

	return CyIngImportTool::kImportOk;
}

/* ---------------------------------------------------------------------------- */

bool CyIngImportTool::insertDetails ( const std::vector < std::string >& detailsVector )
{
	bool bReturnValue = true;
	if ( detailsVector.empty ( ) )
	{
		return bReturnValue;
	}

	std::vector < std::string >::const_iterator iterator;
	for ( iterator = detailsVector.begin ( ); iterator != detailsVector.end ( ); ++ iterator )
	{
		wxString strSql;
		strSql 
			<< wxString ("INSERT into OperationsDetails " )
			<< wxString ( "( ObjId, OperationObjId, Detail ) " )
			<< wxString ( "values ( " )
			<< this->m_lOperationDetailObjId 
			<< wxString ( ", " )
			<< this->m_lOperationObjId
			<< wxString ( ", \"" )
			<< wxString ( *iterator ) 
			<< wxString ( "\" );" );
		bReturnValue &= CySqliteDb::getInstance ( ).executeSql ( strSql );
		++ this->m_lOperationDetailObjId;
	}

	return bReturnValue;
}

/* ---------------------------------------------------------------------------- */

long long CyIngImportTool::getObjId ( wxString strTable )
{
	wxString strSql = 
		wxString ( "SELECT IFNULL ( MAX ( ObjId ) + 1, 0) FROM " ) + strTable;

	long long lObjId = CyEnum::kInvalidObjId;
	CySqliteDb::getInstance ( ).getSingleValue ( strSql, &lObjId );

	return lObjId;
}

/* ---------------------------------------------------------------------------- */

