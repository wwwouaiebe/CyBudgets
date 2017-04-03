/* ---------------------------------------------------------------------------- */
//! CyUserPreferences.h
/* ---------------------------------------------------------------------------- */
//!
//! \file CyUserPreferences.h
//! \brief header file for class CyUserPreferences
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

#include "UtilitiesLayer/CyWxIncludes.h"

/* ---------------------------------------------------------------------------- */

class CyWxUserPreferencesDialog;

/* ---------------------------------------------------------------------------- */

//! \class CyUserPreferences
//! \brief this class stores and get informations about the user preferences
//!
//! This class is based on the "Singleton" design pattern
//!
//! \since version 1.0.3
//!

class CyUserPreferences
{
	friend class CyWxBudgetsApp;
	friend class CyWxPersistentUserPreferences;
	friend class CyWxUserPreferencesDialog;
	friend class CySqliteDb;

	public:

		//! \fn getInstance ( )
		//! \return a constant reference to the one and only one instance of this class

		static CyUserPreferences& getInstance ( );

		//! \fn getCurrencyDecimalPrecision ( ) const
		//! get method
		//! \return the number of digits to dsplay for the decimal part of currency

		const long long& getCurrencyDecimalPrecision ( ) const;

		//! \fn getCurrencyPositiveSymbol ( ) const
		//! get method
		//! \return the symbol used to display a positive currency value

		const wxString& getCurrencyPositiveSymbol ( ) const;

		//! \fn getCurrencyNegativeSymbol ( ) const
		//! get method
		//! \return the symbol used to display a negative currency value

		const wxString& getCurrencyNegativeSymbol ( ) const;

		//! \fn getCurrencyPositiveColor ( ) const
		//! get method
		//! \return the color used to display a positive currency value

		const wchar_t& getCurrencyPositiveColor ( ) const;

		//! \fn getCurrencyNegativeColor ( ) const
		//! get method
		//! \return the color used to display a negative currency value

		const wchar_t& getCurrencyNegativeColor ( ) const;

		//! \fn getDecimalSeparator ( ) const
		//! get method
		//! \return the symbol used for decimal separator

		const wxString& getDecimalSeparator ( ) const;

		//! \fn getThousandSeparator ( ) const
		//! get method
		//! \return the symbol used for thousand separator

		const wxString& getThousandSeparator ( ) const;

		//! \fn getGrouping ( ) const
		//! get method
		//! \return the number of digits to dsplay for the thousand part of currency

		const long long& getGrouping ( ) const;

		//! \fn getCurrencySymbol ( ) const
		//! get method
		//! \return the symbol used for currency

		const wxString& getCurrencySymbol ( ) const;

		//! \fn isCurrencySymbolBefore ( ) const
		//! get method
		//! \return true when the currency symbol is displayed first

		const bool& isCurrencySymbolBefore ( ) const;

		//! \fn getBooleanTrueSymbol ( ) const
		//! get method
		//! \return the symbol used for display a true value

		const wxString& getBooleanTrueSymbol ( ) const;

		//! \fn getBooleanFalseSymbol ( ) const
		//! get method
		//! \return the symbol used for display a false value

		const wxString& getBooleanFalseSymbol ( ) const;

		//! \fn getUserLanguage ( ) const
		//! get method
		//! \return the user language

		const wxString& getUserLanguage ( ) const;

		//! \fn getLastUsedFile ( wxString& strPath, wxString& strFileName ) const
		//! @param [ out ] strPath the last used path
		//! @param [ out ] strFileName the last used file name
		//! get method
		//! \return true when the last used file can be reused

		bool getLastUsedFile ( wxString& strPath, wxString& strFileName ) const;

		//! \fn getReuseLastFile ( ) const
		//! get method
		//! \return true when the last opened file is reopened when launching the program

		bool getReuseLastFile ( ) const;

		//! \fn getDeleteImportFile ( ) const
		//! get method
		//! \return true when the import files must be deleted after the import

		bool getDeleteImportFile ( ) const;

		//! \fn getName ( ) const
		//! get method
		//! \return the name of the object ( needed for the persistence. See wxWidgets documentation )

		const wxString& getName ( ) const;

		//! \fn setName ( const wxString& strName )
		//! @param [ in ] strName the object name
		//! set method
		//! set the name of the object ( needed for the persistance. See wxWidgets documentation )

		void setName ( const wxString& strName );

		//! \fn save ( )
		//! Call the wxPersistenceManager object and save

		void save ( ) ;

		//! \fn saveAndUnregister ( )
		//! Call the wxPersistenceManager object, save and unregister

		void saveAndUnregister ( );

	private:

		//! \fn init ( )
		//! initialize the object

		void init ( );

		//! \fn CyUserPreferences ( ) 
		//! constructor

		CyUserPreferences ( );

		//! \fn ~CyUserPreferences ( ) 
		//! destructor

		~CyUserPreferences ( );

		//! \fn CyUserPreferences ( const CyUserPreferences& ) 
		//! copy constructor
		//! not implemented

		CyUserPreferences ( const CyUserPreferences& );

		//! \fn operator = ( const CyUserPreferences& ) 
		//! operator =
		//! \return a reference to a CyUserPreferences object
		//! not implemented

		CyUserPreferences& operator = ( const CyUserPreferences& );

		//! \var m_objUserPreferences
		//! the one and only one instance of the class

		static CyUserPreferences m_objUserPreferences;

		//! \var m_lCurrencyDecimalPrecision
		//! stores the number of digits to dsplay for the decimal part of currency

		long long m_lCurrencyDecimalPrecision;

		//! \var m_strCurrencyPositiveSymbol
		//! stores the symbol used to display a positive currency value

		wxString m_strCurrencyPositiveSymbol;

		//! \var m_strCurrencyNegativeSymbol
		//! stores the symbol used to display a negative currency value

		wxString m_strCurrencyNegativeSymbol;

		//! \var m_strCurrencyPositiveColor
		//! stores the color used to display a positive currency value

		wchar_t m_strCurrencyPositiveColor;

		//! \var m_strCurrencyNegativeColor
		//! stores the color used to display a negative currency value

		wchar_t m_strCurrencyNegativeColor;

		//! \var m_strDecimalSeparator
		//! stores the symbol used for decimal separator

		wxString m_strDecimalSeparator;

		//! \var m_strThousandSeparator
		//! stores the symbol used for thousand separator

		wxString m_strThousandSeparator;

		//! \var m_lGrouping
		//! stores the number of digits to dsplay for the thousand part of currency

		long long m_lGrouping;

		//! \var m_strCurrencySymbol
		//! stores the symbol used for currency

		wxString m_strCurrencySymbol;

		//! \var m_bCurrencySymbolBefore
		//! true when the currency symbol is displayed first

		bool m_bCurrencySymbolBefore;

		//! \var m_strBooleanTrueSymbol
		//! stores the symbol used for display a true value

		wxString m_strBooleanTrueSymbol;

		//! \var m_strBooleanFalseSymbol
		//! stores the symbol used for display a false value

		wxString m_strBooleanFalseSymbol;

		//! \var m_strUserLanguage
		//! stores the user language

		wxString m_strUserLanguage;

		//! \var m_strName
		//! stores the name used for the persistence

		wxString m_strName;

		//! \var m_strLastUsedFileName
		//! the last used file name
		wxString m_strLastUsedFileName;

		//! \var m_strLastUsedFilePath
		//! the last used path file
		wxString m_strLastUsedFilePath;

		//! \var m_bReuseLastFile
		//! a flag indicating when the last used file have to be reopened when starting the program

		bool m_bReuseLastFile;

		//! \var m_bDeleteImportFile
		//! a flag indicating when the import files have to be deleted

		bool m_bDeleteImportFile;

		//! \var m_bInit
		//! true when the object is initialized

		bool m_bInit;

};

/* ---------------------------------------------------------------------------- */

