/* ---------------------------------------------------------------------------- */
//! CyGetText.cpp
/* ---------------------------------------------------------------------------- */
//!
//! \file CyGetText.cpp
//! \brief definition file for class CyGetText
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

#include "UtilitiesLayer/CyFilesService.h"
#include "UtilitiesLayer/CyGetText.h"
#include "UtilitiesLayer/CyUtf8WxStringTranslator.h"

/* ---------------------------------------------------------------------------- */

CyGetText CyGetText::m_objGetText;

/* ---------------------------------------------------------------------------- */

CyGetText::CyGetText ( ) :
	m_bInitialized ( false ) 
{
}

/* ---------------------------------------------------------------------------- */

CyGetText::~CyGetText ( )
{
}

/* ---------------------------------------------------------------------------- */

CyGetText& CyGetText::getInstance ( )
{
	if ( ! m_objGetText.m_bInitialized )
	{
		m_objGetText.init ( );
	}

	return m_objGetText;
}

/* ---------------------------------------------------------------------------- */

const wxString& CyGetText::getText ( const wxString& strKey ) const
{
	std::map < wxString, wxString >::const_iterator messageIterator = this->m_MessagesMap.find ( strKey );

	return ( this->m_MessagesMap.end ( ) !=  messageIterator ) ? messageIterator->second : strKey;
}

/* ---------------------------------------------------------------------------- */

void CyGetText::loadMessages ( const wxString& strLanguage )
{
	 // the message file is opened
	 std::ifstream fileStream ( ( CyFilesService::getInstance ( ).getMessagesPath ( ) + strLanguage + wxString ( ".po" ) ).ToStdString ( ).data ( ) );

	 // all the previous messages are removed from the message map
	 this->m_MessagesMap.clear ( );

	 std::string strUtf8Message;
	 CyUtf8WxStringTranslator objUtf8Translator;
	 wxString strMsgId;
	 wxString strMsgStr;

	 while ( ! fileStream.eof ( ) )
	 {
		 if ( ! fileStream.good ( ) || fileStream.bad ( ) || fileStream.fail ( ) )
		 {
			 this->m_MessagesMap.clear ( );
			 break;
		 }

		 // Reading a line...
		 getline ( fileStream, strUtf8Message );

		 if ( ! strUtf8Message.empty ( ) )
		 {
			 wxString strWxMessage = objUtf8Translator.fromUtf8ToWxString ( strUtf8Message );
			 strWxMessage.Trim ( true ).Trim ( false );

			 int iMsgIdPos = strWxMessage.Find ( wxString ( "msgid" ) );

			 int iMsgStrPos = strWxMessage.Find ( wxString ( "msgstr" ) );

			 wxString strContains = wxString ( "" );
			 if ( ( 0 == iMsgIdPos ) || ( 0 == iMsgStrPos ) )
			 {
				 strContains = strWxMessage.substr ( strWxMessage.find_first_of ( wxString ( "\"" ) ) + 1 );
				 strContains.erase ( strContains.find_last_of ( "\"" ) );
			 }

			 if ( 0 == iMsgIdPos )
			 {
				 strMsgId = strContains;
			 }

			 if ( 0 == iMsgStrPos )
			 {
				 strMsgStr = strContains;
			 }

			 if ( ( ! strMsgId.empty ( ) ) && ( ! strMsgStr.empty ( ) ) )
			 {
				 // ... and the message added to the map
				 this->m_MessagesMap.insert ( std::map < wxString, wxString >::value_type ( strMsgId, strMsgStr ) );
				 strMsgId.clear ( );
				 strMsgStr.clear ( );
			 }
		 }
	 }

	 fileStream.close ( );
}

/* ---------------------------------------------------------------------------- */

void CyGetText::init ( )
{
	// because we need an instance of the CyFilesService class to read the messages file, 
	// it's not possible to read the messages file from the constructor ( the initialization order
	// of global instances is C++ implementation dependant).
	this->loadMessages ( wxString ( "FR_be" ) );

	this->m_bInitialized = true;
}

/* ---------------------------------------------------------------------------- */

