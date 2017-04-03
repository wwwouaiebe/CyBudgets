/* ---------------------------------------------------------------------------- */
//! CyWxIncludes.h
/* ---------------------------------------------------------------------------- */
//!
//! \file CyWxIncludes.h
//! \brief fichier d'en-tête de wxWidgets
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
#pragma warning( disable : 4100 )
#pragma warning( disable : 4191 ) //x64 only
#pragma warning( disable : 4365 )
#pragma warning( disable : 4371 ) //x64 only
#pragma warning( disable : 4464 )
#pragma warning( disable : 4574 )
#pragma warning( disable : 4625 )
#pragma warning( disable : 4626 )
#pragma warning( disable : 4668 )
#pragma warning( disable : 4774 )
#pragma warning( disable : 4820 )
#pragma warning( disable : 4986 )
#pragma warning( disable : 4996 )
#pragma warning( disable : 5026 )
#pragma warning( disable : 5027 )
#endif

#include <wx/aboutdlg.h>
#include <wx/clntdata.h>
#include <wx/colour.h>
#include <wx/combobox.h>
#include <wx/datectrl.h>
#include <wx/filename.h>
#include <wx/frame.h>
#include <wx/gdicmn.h>
#include <wx/gbsizer.h>
#include <wx/grid.h>
#include <wx/stdpaths.h>
#include <wx/string.h>
#include <wx/toolbar.h>
#include <wx/treectrl.h>
#include <wx/treebase.h>
#include <wx/valnum.h>
#include <wx/wx.h>
#include <wx/persist.h>
#include <wx/persist/window.h>
#include <wx/notebook.h>
#include <wx/spinctrl.h>
#include <wx/filesys.h>
#include <wx/dirdlg.h>

#ifdef CY_COMPILER_VC10
#pragma warning(pop)
#endif

/* ---------------------------------------------------------------------------- */

