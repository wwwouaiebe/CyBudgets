/* ---------------------------------------------------------------------------- */
//! CyEnum.h
/* ---------------------------------------------------------------------------- */
//!
//! \file CyEnum.h
//! \brief header file for class CyEnum
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

//! \def CyNoFormat
//! No format must be applied

#define CyNoFormat 0x0

//! \def CyStartFormat
//! Mandatory character used to start a format string

#define CyStartFormat L'➻'

//! \def CyHorizontalAlignmentLeft
//! Horizontal alignment left

#define CyHorizontalAlignmentLeft L'←'

//! \def CyHorizontalAlignmentRight
//! Horizontal alignment right

#define CyHorizontalAlignmentRight L'→'

//! \def CyHorizontalAlignmentCenter
//! Horizontal alignment center

#define CyHorizontalAlignmentCenter L'↔'

//! \def CyVerticalAlignmentTop
//! Vertical alignment top

#define CyVerticalAlignmentTop L'↑'

//! \def CyVerticalAlignmentBottom
//! Vertical alignment bottom

#define CyVerticalAlignmentBottom L'↓'

//! \def CyVerticalAlignmentCenter
//! Vertical alignment center

#define CyVerticalAlignmentCenter L'↕'

//! \def CyFormatCurrency
//! Numbers are displayed as currency

#define CyFormatCurrency L'€'

//! \def CyFormatInteger
//! Numbers are displayed as integer

#define CyFormatInteger L'ℤ'

//! \def CyFormatReal
//! Numbers are displayed as real

#define CyFormatReal L'ℝ'

//! \def CyFormatBoolean
//! Numbers are displayed as boolean

#define CyFormatBoolean L'✓'

//! \def CyFormatString
//! Values are displayed as string

#define CyFormatString L'α'

//! \def CyFormatDate
//! Strings in the ISO 8601 format are displayed as date

#define CyFormatDate L'≋'

//! \def CyFormatHidden
//! Values are not displayed

#define CyFormatHidden L'∅'

//! \def CyForegroundBlue
//! The foreground color is blue

#define CyForegroundBlue L'➀'

//! \def CyForegroundCyan
//! The foreground color is cyan

#define CyForegroundCyan L'➁'

//! \def CyForegroundGreen
//! The foreground color is green

#define CyForegroundGreen L'➂'

//! \def CyForegroundYellow
//! The foreground color is eyllow

#define CyForegroundYellow L'➃'

//! \def CyForegroundRed
//! The foreground color is red

#define CyForegroundRed L'➄'

//! \def CyForegroundBlack
//! The foreground color is black

#define CyForegroundBlack L'➅'

//! \def CyForegroundGrey
//! The foreground color is grey

#define CyForegroundGrey L'➆'

//! \def CyForegroundWhite
//! The foreground color is white

#define CyForegroundWhite L'➇'

//! \def CyBackgroundBlue
//! The background color is blue

#define CyBackgroundBlue L'➊'

//! \def CyBackgroundCyan
//! The background color is cyan

#define CyBackgroundCyan L'➋'

//! \def CyBackgroundGreen
//! The background color is green

#define CyBackgroundGreen L'➌'

//! \def CyBackgroundYellow
//! The background color is yellow

#define CyBackgroundYellow L'➍'

//! \def CyBackgroundRed
//! The background color is red

#define CyBackgroundRed L'➎'

//! \def CyBackgroundBlack
//! The background color is black

#define CyBackgroundBlack L'➏'

//! \def CyBackgroundGrey
//! The background color is grey

#define CyBackgroundGrey L'➐'

//! \def CyBackgroundWhite
//! The background color is white

#define CyBackgroundWhite L'➑'

//! \def CyFontBold
//! The font bold is used

#define CyFontBold L'∎'

//! \def CyFontItalic
//! The font italic is used

#define CyFontItalic L'∕'

//! \def CyFontUnderlined
//! The font underlined is used

#define CyFontUnderlined L'∸'

//! \class CyEnum
//! \brief Simple class to store configuration settings
//!

class CyEnum
{

	public:

		//! \enum WindowsSizeAndPosition
		//! default values for Windows size, position and margins
		//!
		//! \var kWindowWidth
		//! the initial width of the main window
		//!
		//! \var kWindowHeight
		//! the initial height of the main window
		//!
		//! \var kLeft
		//! the initial width of the main window
		//!
		//! \var kTop
		//! the initial top position of the upper left corner of the main window
		//!
		//! \var kMarginSize
		//! the margin size between widgets in the windows

		enum WindowsSizeAndPosition
		{
			kWindowWidth = 1600,
			kWindowHeight = 800,
			kLeft = 0,
			kTop = 0,
			kMarginSize = 5
		};

		//! \enum ObjId
		//! value for ObjId  not already attribued ( see data model - ObjId is the primary key of each table )
		//!
		//! \var kInvalidObjId
		//! the initial value of an ObjId
		//!

		enum ObjId
		{
			kInvalidObjId = -1
		};

		//! \enum Version
		//! value for version
		//!
		//! \var kInvalidVersion
		//!value for version  not found
		//!

		enum Version
		{
			kInvalidVersion = -1
		};

		//! \enum AccountCanBeImported
		//! logical values Yes / No
		//!
		//! \var kNo
		//! the 'No' value
		//!
		//! \var kYes
		//! the 'Yes' value
		//!

		enum AccountCanBeImported
		{
			kNo = 0,
			kYes = 1
		};

		//! \enum wxTreeCtrlImages
		//! Values used for the creation of wxTreeItemId objects
		//!
		//! \var kNoImage
		//! See wxTreeCtr::AddRoot ( ) and  wxTreeCtrl::AppendItem ( ) documentation
		//!
		//! \var kNoSelectedImage
		//! See wxTreeCtr::AddRoot ( ) and  wxTreeCtrl::AppendItem ( ) documentation
		//!

		enum wxTreeCtrlImages
		{
			kNoImage = -1,
			kNoSelectedImage = -1
		};

};