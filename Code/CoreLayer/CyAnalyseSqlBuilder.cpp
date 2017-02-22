/* ---------------------------------------------------------------------------- */
//! CyAnalyseSqlBuilder.cpp
/* ---------------------------------------------------------------------------- */
//!
//! \file CyAnalyseSqlBuilder.cpp
//! \brief definition file for class CyAnalyseSqlBuilder
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

#include "CoreLayer/CyAnalyseSqlBuilder.h"
#include "DataLayer/CyLongValue.h"
#include "DataLayer/CySqliteDb.h"
#include "UtilitiesLayer/CyEnum.h"
#include "UtilitiesLayer/CyGetText.h"

/* ---------------------------------------------------------------------------- */

CyAnalyseSqlBuilder::CyAnalyseSqlBuilder ( long long lBudgetObjId, const wxDateTime& objStartDate, const wxDateTime& objEndDate ):
		m_lBudgetObjId ( lBudgetObjId ),
		m_objStartDate ( objStartDate ),
		m_objEndDate ( objEndDate )
{
}

/* ---------------------------------------------------------------------------- */

CyAnalyseSqlBuilder::~CyAnalyseSqlBuilder ( )
{
}

/* ---------------------------------------------------------------------------- */

wxString CyAnalyseSqlBuilder::getDialogTitle ( ) const
{
	wxString strDialogTitle = CyGetText::getInstance ( ).getText ( "CyAnalyseSqlBuilder.getDialogTitle.AnayseTitle" );

	if ( CyEnum::kInvalidObjId != this->m_lBudgetObjId )
	{
		// A budget was given. Searching the description in the table Budgets 
		wxString strBudget = wxEmptyString;

		wxString strSql;
		strSql 
			<< wxString ( "SELECT Description FROM Budgets WHERE ObjId = " )
			<< this->m_lBudgetObjId
			<< wxString ( ";");
		CySqliteDb::getInstance ( ).getSingleValue ( strSql, &strBudget );

		// The descrition is added to the dialog title
		strDialogTitle
			<< wxString ( " - " )
			<< CyGetText::getInstance ( ).getText ( "CyAnalyseSqlBuilder.getDialogTitle.BudgetTitle" )
			<< strBudget;
	}

	// ... and dates are added to the dialog title
	strDialogTitle
		<< wxString ( " - " )
		<< CyGetText::getInstance ( ).getText ( "CyAnalyseSqlBuilder.getDialogTitle.StartDateTitle" )
		<< wxString ( " " )
		<< this->m_objStartDate.Format ( wxString ( "%d-%m-%Y" ) )
		<< wxString ( " " )
		<< CyGetText::getInstance ( ).getText ( "CyAnalyseSqlBuilder.getDialogTitle.EndDateTitle" )
		<< wxString ( " " )
		<< this->m_objEndDate.Format ( wxString ( "%d-%m-%Y" ) );

	return strDialogTitle;
}

/* ---------------------------------------------------------------------------- */

wxString CyAnalyseSqlBuilder::getDeleteSql ( long long ) const
{
	// Not implemented in this class
	return wxEmptyString;
}

/* ---------------------------------------------------------------------------- */

 wxString CyAnalyseSqlBuilder::getInsertSql ( const CyQueryResult::CyQueryResultValuesRow& ) const
{
	// Not implemented in this class
	return wxEmptyString;
}

/* ---------------------------------------------------------------------------- */

void CyAnalyseSqlBuilder::createRow ( CyQueryResult::CyQueryResultValuesRow& ) const
{
}

/* ---------------------------------------------------------------------------- */

wxString CyAnalyseSqlBuilder::getSelectSql (  ) const
{
	wxString strSelectSql = wxEmptyString;

	// ... and creating a SQL 'where' clause with the dates...
	wxString strWhereClause = 
		wxString ( "WHERE o.AttributionDate >= \"" )
		+ this->m_objStartDate.Format ( wxString ( "%Y-%m-%d" ) )
		+ wxString ( "\" AND o.AttributionDate <= \"")
		+ this->m_objEndDate.Format ( wxString ( "%Y-%m-%d" ) )
		+ wxString ( "\" " );

	if ( CyEnum::kInvalidObjId != m_lBudgetObjId )
	{
		// a valid budget was found. The budget is added to the SQL 'where' clause
		strWhereClause
			<< wxString ( "AND b.BudgetObjId = " )
			<< m_lBudgetObjId
			<< wxString ( " " );
	}

	//
	//	strSelectSql = 
	//
	//	SELECT 
	//		Format1 as ➻, 
	//		DisplayOrder , 
	//		Format2 as ➻, 
	//		GroupObjId, 
	//		Format3 as ➻, 
	//		AttributionObjId, 
	//		Format4 as ➻, 
	//		BudgetDate, 
	//		Format5 as ➻, 
	//		Groupe AS "Groupe", 
	//		Format6 as ➻, 
	//		Sousgroupe AS "Sous-groupe", 
	//		Format7 as ➻, 
	//		Mois AS "Mois", 
	//		Format8 as ➻, 
	//		Montant AS "Montant €", 
	//		Format9 as ➻, 
	//		SousgroupeName AS "Nom du sous-groupe",
	//		Format10 as ➻,
	//		SousgroupeTotal AS "Total du sous-groupe €", 
	//		Format11 as ➻,
	//		GroupeName AS "Nom du groupe", 
	//		Format12 as ➻,
	//		GroupeTotal AS "Total du groupe €", 
	//		Format13 as ➻, 
	//		Total AS "Total €" 
	//	FROM 
	//		(
	//				SELECT 
	//					"➻∅" AS "Format1", 
	//					g.GroupDescription AS DisplayOrder, 
	//					"➻∅" AS "Format2", 
	//					g.ObjId AS GroupObjId, 
	//					"➻∅" AS "Format3", 
	//					-1 AS AttributionObjId, 
	//					"➻∅" AS "Format4", 
	//					"" AS BudgetDate, 
	//					"➻α" AS "Format5", 
	//					g.GroupDescription AS Groupe, 
	//					"➻α" AS "Format6",
	//					"" AS Sousgroupe, 
	//					"➻≋" AS "Format7",
	//					"" AS Mois,
	//					"➻€" AS "Format8", 
	//					"" AS Montant,
	//					"➻α" AS "Format9",
	//					"" AS SousgroupeName,
	//					"➻€" AS "Format10",
	//					"" AS SousgroupeTotal,
	//					"➻α" AS "Format11",
	//					"" AS GroupeName, 
	//					"➻€" AS "Format12", 
	//					"" AS GroupeTotal,
	//					"➻€" AS "Format13",
	//					"" AS Total 
	//				FROM 
	//					AttributionsGroups g 
	//					LEFT JOIN Attributions b ON g.ObjId = b.GroupObjId 
	//					LEFT JOIN OperationsAttributions bo ON b.ObjId = bo.AttributionObjId 
	//					LEFT JOIN Operations o ON bo.OperationObjId = o.ObjId 
	//				WHERE 
	//					o.AttributionDate >= "2015-01-01" 
	//					AND o.AttributionDate <= "2015-02-07" 
	//					AND b.BudgetObjId = 0 
	//				GROUP BY 
	//					g.GroupDescription, 
	//					b.Description, 
	//					STRFTIME ( "%Y-%m", o.AttributionDate ) 
	//					
	//			UNION 
	//				
	//				SELECT 
	//					"➻∅" AS "Format1", 
	//					g.GroupDescription || ";" || b.Description AS DisplayOrder,
	//					"➻∅" AS "Format2", 
	//					-1 AS GroupObjId, 
	//					"➻∅" AS "Format3",
	//					b.ObjId AS AttributionObjId,
	//					"➻∅" AS "Format4", 
	//					"" AS BudgetDate,
	//					"➻α" AS "Format5", 
	//					"" AS Groupe,
	//					"➻α" AS "Format6",
	//					b.Description AS Sousgroupe, 
	//					"➻≋" AS "Format7", 
	//					"" AS Mois,
	//					"➻€" AS "Format8",
	//					"" AS Montant, 
	//					"➻α" AS "Format9", 
	//					"" AS SousgroupeName,
	//					"➻€" AS "Format10",
	//					"" AS SousgroupeTotal,
	//					"➻α" AS "Format11",
	//					"" AS GroupeName, 
	//					"➻€" AS "Format12",
	//					"" AS GroupeTotal,
	//					"➻€" AS "Format13",
	//					"" AS Total 
	//				FROM 
	//					AttributionsGroups g 
	//					LEFT JOIN Attributions b ON g.ObjId = b.GroupObjId 
	//					LEFT JOIN OperationsAttributions bo ON b.ObjId = bo.AttributionObjId 
	//					LEFT JOIN Operations o ON bo.OperationObjId = o.ObjId 
	//				WHERE 
	//					o.AttributionDate >= "2015-01-01" 
	//					AND o.AttributionDate <= "2015-02-07" 
	//					AND b.BudgetObjId = 0 
	//				GROUP BY 
	//					g.GroupDescription, 
	//					b.Description, 
	//					STRFTIME ( "%Y-%m", o.AttributionDate ) 
	//				
	//			UNION 
	//			
	//				SELECT 
	//					"➻∅" AS "Format1",
	//					g.GroupDescription || ";" || b.Description || ";" || STRFTIME ( "%Y-%m", o.AttributionDate ) AS DisplayOrder,
	//					"➻∅" AS "Format2",
	//					-1 AS GroupObjId,
	//					"➻∅" AS "Format3",
	//					b.ObjId AS AttributionObjId,
	//					"➻∅" AS "Format4", 
	//					STRFTIME ( "%Y-%m", o.AttributionDate ) AS BudgetDate,
	//					"➻α" AS "Format5",
	//					"" AS Groupe, 
	//					"➻α" AS "Format6",
	//					"" AS Sousgroupe, 
	//					"➻≋" AS "Format7", 
	//					STRFTIME ( "%Y-%m", o.AttributionDate ) AS Mois,
	//					"➻€" AS "Format8", 
	//					SUM ( bo.Amount ) AS Montant,
	//					"➻α" AS "Format9",
	//					"" AS SousgroupeName,
	//					"➻€" AS "Format10", 
	//					"" AS SousgroupeTotal,
	//					"➻α" AS "Format11",
	//					"" AS GroupeName,
	//					"➻€" AS "Format12",
	//					"" AS GroupeTotal, 
	//					"➻€" AS "Format13",
	//					"" AS Total 
	//				FROM 
	//					AttributionsGroups g 
	//					LEFT JOIN Attributions b ON g.ObjId = b.GroupObjId 
	//					LEFT JOIN OperationsAttributions bo ON b.ObjId = bo.AttributionObjId
	//					LEFT JOIN Operations o ON bo.OperationObjId = o.ObjId
	//				WHERE
	//					o.AttributionDate >= "2015-01-01" 
	//					AND o.AttributionDate <= "2015-02-07"
	//					AND b.BudgetObjId = 0 
	//				GROUP BY 
	//					g.GroupDescription, 
	//					b.Description, 
	//					STRFTIME ( "%Y-%m", o.AttributionDate ) 
	//				
	//			UNION 
	//			
	//				SELECT 
	//					"➻∅" AS "Format1", 
	//					g.GroupDescription || ";" || b.Description || ";" || "XXXXXXXXXXX" AS DisplayOrder,
	//					"➻∅" AS "Format2", 
	//					-1 AS GroupObjId,
	//					"➻∅" AS "Format3",
	//					b.ObjId AS AttributionObjId,
	//					"➻∅" AS "Format4",
	//					"" AS BudgetDate, 
	//					"➻α" AS "Format5", 
	//					"" AS Groupe, 
	//					"➻α" AS "Format6", 
	//					"" AS Sousgroupe, 
	//					"➻≋" AS "Format7",
	//					"" AS Mois,
	//					"➻€" AS "Format8",
	//					"" AS Montant,
	//					"➻α" AS "Format9", 
	//					"Total del'attribution: " || b.Description AS SousgroupeName,
	//					"➻€" AS "Format10", 
	//					SUM ( bo.Amount ) AS SousgroupeTotal,
	//					"➻α" AS "Format11",
	//					"" AS GroupeName, 
	//					"➻€" AS "Format12",
	//					"" AS GroupeTotal,
	//					"➻€" AS "Format13", 
	//					"" AS Total
	//				FROM 
	//					AttributionsGroups g 
	//					LEFT JOIN Attributions b ON g.ObjId = b.GroupObjId 
	//					LEFT JOIN OperationsAttributions bo ON b.ObjId = bo.AttributionObjId 
	//					LEFT JOIN Operations o ON bo.OperationObjId = o.ObjId
	//				WHERE
	//					o.AttributionDate >= "2015-01-01" 
	//					AND o.AttributionDate <= "2015-02-07" 
	//					AND b.BudgetObjId = 0 
	//				GROUP BY 
	//					g.GroupDescription,
	//					b.Description 
	//				
	//			UNION 
	//			
	//				SELECT
	//					"➻∅" AS "Format1",
	//					g.GroupDescription || ";" || "XXXXXXXXXXX" AS DisplayOrder,
	//					"➻∅" AS "Format2",
	//					g.ObjId AS GroupObjId, 
	//					"➻∅" AS "Format3", 
	//					-1 AS AttributionObjId,
	//					"➻∅" AS "Format4",
	//					"" AS BudgetDate,
	//					"➻α" AS "Format5", 
	//					"" AS Groupe, 
	//					"➻α" AS "Format6", 
	//					"" AS Sousgroupe, 
	//					"➻≋" AS "Format7",
	//					"" AS Mois, 
	//					"➻€" AS "Format8", 
	//					"" AS Montant,
	//					"➻α" AS "Format9",
	//					"" AS SousgroupeName, 
	//					"➻€" AS "Format10", 
	//					"" AS SousgroupeTotal,
	//					"➻α" AS "Format11",
	//					"Total du groupe " || g.GroupDescription AS GroupeName,
	//					"➻€" AS "Format12", SUM ( bo.Amount ) AS GroupeTotal,
	//					"➻€" AS "Format13", 
	//					"" as Total 
	//				FROM 
	//					AttributionsGroups g 
	//					LEFT JOIN Attributions b ON g.ObjId = b.GroupObjId 
	//					LEFT JOIN OperationsAttributions bo ON b.ObjId = bo.AttributionObjId
	//					LEFT JOIN Operations o ON bo.OperationObjId = o.ObjId 
	//				WHERE 
	//					o.AttributionDate >= "2015-01-01" 
	//					AND o.AttributionDate <= "2015-02-07" 
	//					AND b.BudgetObjId = 0 
	//				GROUP BY
	//					g.GroupDescription 
	//				
	//			UNION 
	//			
	//				SELECT 
	//					"➻∅" AS "Format1",
	//					"XXXXXXXXXXX" AS DisplayOrder, 
	//					"➻∅" AS "Format2", 
	//					-1 AS GroupObjId, 
	//					"➻∅" AS "Format3", 
	//					-1 AS AttributionObjId,
	//					"➻∅" AS "Format4",
	//					"" AS BudgetDate,
	//					"➻α" AS "Format5",
	//					"" AS Groupe,
	//					"➻α" AS "Format6",
	//					"" AS Sousgroupe,
	//					"➻≋" AS "Format7",
	//					"" AS Mois, 
	//					"➻€" AS "Format8",
	//					"" AS Montant,
	//					"➻α" AS "Format9", 
	//					"" AS SousgroupeName,
	//					"➻€" AS "Format10",
	//					"" AS SousgroupeTotal,
	//					"➻α" AS "Format11",
	//					"" AS GroupeName,
	//					"➻€" AS "Format12",
	//					"" AS GroupeTotal, 
	//					"➻€" AS "Format13",
	//					SUM ( bo.Amount )
	//					AS Total 
	//				FROM 
	//					AttributionsGroups g 
	//					LEFT JOIN Attributions b ON g.ObjId = b.GroupObjId 
	//					LEFT JOIN OperationsAttributions bo ON b.ObjId = bo.AttributionObjId 
	//					LEFT JOIN Operations o ON bo.OperationObjId = o.ObjId
	//				WHERE 
	//					o.AttributionDate >= "2015-01-01" 
	//					AND o.AttributionDate <= "2015-02-07" 
	//					AND b.BudgetObjId = 0 
	//		) 
	//		order by DisplayOrder;
	//

	strSelectSql

		// Main select

		<< wxString ( "SELECT Format1 as " )
		<< CyStartFormat
		<< wxString ( ", DisplayOrder ")
		<< wxString ( ", Format2 as " )
		<< CyStartFormat
		<< wxString ( ", GroupObjId" )
		<< wxString ( ", Format3 as " )
		<< CyStartFormat
		<< wxString ( ", AttributionObjId" )
		<< wxString ( ", Format4 as " )
		<< CyStartFormat
		<< wxString ( ", BudgetDate" )
		<< wxString ( ", Format5 as " )
		<< CyStartFormat
		<< wxString ( ", Groupe AS \"" )
		<< CyGetText::getInstance ( ).getText ( "CyAnalyseSqlBuilder.getSelectSql.MainDescription" )
		<< wxString ( "\", Format6 as " )
		<< CyStartFormat
		<< wxString ( ", Sousgroupe AS \"")
		<<  CyGetText::getInstance ( ).getText ( "CyAnalyseSqlBuilder.getSelectSql.Description" )
		<< wxString ( "\", Format7 as " )
		<< CyStartFormat
		<< wxString ( ", Mois AS \"" )
		<<  CyGetText::getInstance ( ).getText ( "CyAnalyseSqlBuilder.getSelectSql.Month" )
		<< wxString ( "\", Format8 as " )
		<< CyStartFormat
		<< wxString ( ", Montant AS \"" )
		<<  CyGetText::getInstance ( ).getText ( "CyAnalyseSqlBuilder.getSelectSql.Amount" )
		<< wxString ( "\", Format9 as " )
		<< CyStartFormat
		<< wxString (", SousgroupeName AS \"" )
		<< CyGetText::getInstance ( ).getText ( "CyAnalyseSqlBuilder.getSelectSql.DescriptionName" )
		<< wxString ( "\", Format10 as " )
		<< CyStartFormat
		<< wxString ( ", SousgroupeTotal AS \"" )
		<< CyGetText::getInstance ( ).getText ( "CyAnalyseSqlBuilder.getSelectSql.DescriptionTotal" )
		<< wxString ( "\", Format11 as " )
		<< CyStartFormat
		<< wxString ( ", GroupeName AS \"" )
		<< CyGetText::getInstance ( ).getText ( "CyAnalyseSqlBuilder.getSelectSql.MainDescriptionName" )
		<< wxString ( "\", Format12 as " )
		<< CyStartFormat
		<< wxString (", GroupeTotal AS \"" )
		<< CyGetText::getInstance ( ).getText ( "CyAnalyseSqlBuilder.getSelectSql.MainDescriptionTotal" )
		<< wxString ( "\", Format13 as " )
		<< CyStartFormat
		<< wxString ( ", Total AS \"" )
		<<CyGetText::getInstance ( ).getText ( "CyAnalyseSqlBuilder.getSelectSql.Total" )
		<< wxString ( "\" FROM (" )

		// Selection for groups

		<< wxString ( "SELECT \"" )
		<< CyStartFormat
		<< CyFormatHidden
		<< wxString ( "\" AS \"Format1\", " )
		<< wxString ( "g.GroupDescription AS DisplayOrder, \"" )
		<< CyStartFormat
		<< CyFormatHidden
		<< wxString ( "\" AS \"Format2\", " )
		<< wxString ( "g.ObjId AS GroupObjId, \"" )
		<< CyStartFormat
		<< CyFormatHidden
		<< wxString ( "\" AS \"Format3\", " )
		<< CyEnum::kInvalidObjId
		<< wxString ( " AS AttributionObjId, \"" )
		<< CyStartFormat
		<< CyFormatHidden
		<< wxString ( "\" AS \"Format4\", " )
		<< wxString ( "\"\" AS BudgetDate, \"" )
		<< CyStartFormat
		<< CyFormatString
		<< wxString ( "\" AS \"Format5\", " )
		<< wxString ( "g.GroupDescription AS Groupe, \"")
		<< CyStartFormat
		<< CyFormatString
		<< wxString ( "\" AS \"Format6\", " )
		<< wxString ( "\"\" AS Sousgroupe, \"")
		<< CyStartFormat
		<< CyFormatDate
		<< wxString ( "\" AS \"Format7\", " )
		<< wxString ( "\"\" AS Mois, \"" )
		<< CyStartFormat
		<< CyFormatCurrency
		<< wxString ( "\" AS \"Format8\", " )
		<< wxString ( "\"\" AS Montant, \"" )
		<< CyStartFormat
		<< CyFormatString
		<< wxString ( "\" AS \"Format9\", " )
		<< wxString ( "\"\" AS SousgroupeName, \"" )
		<< CyStartFormat
		<< CyFormatCurrency
		<< wxString ( "\" AS \"Format10\", " )
		<< wxString ( "\"\" AS SousgroupeTotal, \"")
		<< CyStartFormat
		<< CyFormatString
		<< wxString ( "\" AS \"Format11\", " )
		<< wxString ( "\"\" AS GroupeName, \"")
		<< CyStartFormat
		<< CyFormatCurrency
		<< wxString ( "\" AS \"Format12\", " )
		<< wxString ( "\"\" AS GroupeTotal, \"")
		<< CyStartFormat
		<< CyFormatCurrency
		<< wxString ( "\" AS \"Format13\", " )
		<< wxString ( "\"\" AS Total ")
		<< wxString ( "FROM AttributionsGroups g LEFT JOIN Attributions b ON g.ObjId = b.GroupObjId LEFT JOIN OperationsAttributions bo ON b.ObjId = bo.AttributionObjId LEFT JOIN Operations o ON bo.OperationObjId = o.ObjId ")
		<< strWhereClause
		<< wxString ( "GROUP BY g.GroupDescription, b.Description, STRFTIME ( \"%Y-%m\", o.AttributionDate ) ")

		<< wxString ( "UNION " )

		// Selection for attribution

		<< wxString ( "SELECT \"" )
		<< CyStartFormat
		<< CyFormatHidden
		<< wxString ( "\" AS \"Format1\", " )
		<< wxString ( "g.GroupDescription || \";\" || b.Description AS DisplayOrder, \"" )
		<< CyStartFormat
		<< CyFormatHidden
		<< wxString ( "\" AS \"Format2\", " )
		<< CyEnum::kInvalidObjId
		<< wxString ( " AS GroupObjId, \"" )
		<< CyStartFormat
		<< CyFormatHidden
		<< wxString ( "\" AS \"Format3\", " )
		<< wxString ( "b.ObjId AS AttributionObjId, \"" )
		<< CyStartFormat
		<< CyFormatHidden
		<< wxString ( "\" AS \"Format4\", " )
		<< wxString ( "\"\" AS BudgetDate, \"" )
		<< CyStartFormat
		<< CyFormatString
		<< wxString ( "\" AS \"Format5\", " )
		<< wxString ( "\"\" AS Groupe, \"")
		<< CyStartFormat
		<< CyFormatString
		<< wxString ( "\" AS \"Format6\", " )
		<< wxString ( "b.Description AS Sousgroupe, \"" )
		<< CyStartFormat
		<< CyFormatDate
		<< wxString ( "\" AS \"Format7\", " )
		<< wxString ( "\"\" AS Mois, \"" )
		<< CyStartFormat
		<< CyFormatCurrency
		<< wxString ( "\" AS \"Format8\", " )
		<< wxString ( "\"\" AS Montant, \"" )
		<< CyStartFormat
		<< CyFormatString
		<< wxString ( "\" AS \"Format9\", " )
		<< wxString ( "\"\" AS SousgroupeName, \"" )
		<< CyStartFormat
		<< CyFormatCurrency
		<< wxString ( "\" AS \"Format10\", " )
		<< wxString ( "\"\" AS SousgroupeTotal, \"")
		<< CyStartFormat
		<< CyFormatString
		<< wxString ( "\" AS \"Format11\", " )
		<< wxString ( "\"\" AS GroupeName, \"")
		<< CyStartFormat
		<< CyFormatCurrency
		<< wxString ( "\" AS \"Format12\", " )
		<< wxString ( "\"\" AS GroupeTotal, \"")
		<< CyStartFormat
		<< CyFormatCurrency
		<< wxString ( "\" AS \"Format13\", " )
		<< wxString ( "\"\" AS Total ")
		<< wxString ( "FROM AttributionsGroups g LEFT JOIN Attributions b ON g.ObjId = b.GroupObjId LEFT JOIN OperationsAttributions bo ON b.ObjId = bo.AttributionObjId LEFT JOIN Operations o ON bo.OperationObjId = o.ObjId ")
		<< strWhereClause
		<< wxString ( "GROUP BY g.GroupDescription, b.Description, STRFTIME ( \"%Y-%m\", o.AttributionDate ) ")

		<< wxString ( "UNION " )

		// selection by month

		<< wxString ( "SELECT \"" )
		<< CyStartFormat
		<< CyFormatHidden
		<< wxString ( "\" AS \"Format1\", " )
		<< wxString ( "g.GroupDescription || \";\" || b.Description || \";\" || STRFTIME ( \"%Y-%m\", o.AttributionDate ) AS DisplayOrder, \"")
		<< CyStartFormat
		<< CyFormatHidden
		<< wxString ( "\" AS \"Format2\", " )
		<< CyEnum::kInvalidObjId
		<< wxString ( " AS GroupObjId, \"" )
		<< CyStartFormat
		<< CyFormatHidden
		<< wxString ( "\" AS \"Format3\", " )
		<< wxString ( "b.ObjId AS AttributionObjId, \"" )
		<< CyStartFormat
		<< CyFormatHidden
		<< wxString ( "\" AS \"Format4\", " )
		<< wxString ( "STRFTIME ( \"%Y-%m\", o.AttributionDate ) AS BudgetDate, \"" )
		<< CyStartFormat
		<< CyFormatString
		<< wxString ( "\" AS \"Format5\", " )
		<< wxString ( "\"\" AS Groupe, \"" )
		<< CyStartFormat
		<< CyFormatString
		<< wxString ( "\" AS \"Format6\", " )
		<< wxString ( "\"\" AS Sousgroupe, \"")
		<< CyStartFormat
		<< CyFormatDate
		<< wxString ( "\" AS \"Format7\", " )
		<< wxString ( "STRFTIME ( \"%Y-%m\", o.AttributionDate ) AS Mois, \"")
		<< CyStartFormat
		<< CyFormatCurrency
		<< wxString ( "\" AS \"Format8\", " )
		<< wxString ( "SUM ( bo.Amount ) AS Montant, \"" )
		<< CyStartFormat
		<< CyFormatString
		<< wxString ( "\" AS \"Format9\", " )
		<< wxString ( "\"\" AS SousgroupeName, \"" )
		<< CyStartFormat
		<< CyFormatCurrency
		<< wxString ( "\" AS \"Format10\", " )
		<< wxString ( "\"\" AS SousgroupeTotal, \"")
		<< CyStartFormat
		<< CyFormatString
		<< wxString ( "\" AS \"Format11\", " )
		<< wxString ( "\"\" AS GroupeName, \"")
		<< CyStartFormat
		<< CyFormatCurrency
		<< wxString ( "\" AS \"Format12\", " )
		<< wxString ( "\"\" AS GroupeTotal, \"")
		<< CyStartFormat
		<< CyFormatCurrency
		<< wxString ( "\" AS \"Format13\", " )
		<< wxString ( "\"\" AS Total ")
		<< wxString ( "FROM AttributionsGroups g LEFT JOIN Attributions b ON g.ObjId = b.GroupObjId LEFT JOIN OperationsAttributions bo ON b.ObjId = bo.AttributionObjId LEFT JOIN Operations o ON bo.OperationObjId = o.ObjId ")
		<< strWhereClause
		<< wxString ( "GROUP BY g.GroupDescription, b.Description, STRFTIME ( \"%Y-%m\", o.AttributionDate ) ")

		<< wxString ( "UNION " )

		// Selection for the sum by attribution

		<< wxString ( "SELECT \"" )
		<< CyStartFormat
		<< CyFormatHidden
		<< wxString ( "\" AS \"Format1\", " )
		<< wxString ( "g.GroupDescription || \";\" || b.Description || \";\" || \"XXXXXXXXXXX\" AS DisplayOrder, \"")
		<< CyStartFormat
		<< CyFormatHidden
		<< wxString ( "\" AS \"Format2\", " )
		<< CyEnum::kInvalidObjId
		<< wxString ( " AS GroupObjId, \"" )
		<< CyStartFormat
		<< CyFormatHidden
		<< wxString ( "\" AS \"Format3\", " )
		<< wxString ( "b.ObjId AS AttributionObjId, \"" )
		<< CyStartFormat
		<< CyFormatHidden
		<< wxString ( "\" AS \"Format4\", " )
		<< wxString ( "\"\" AS BudgetDate, \"" )
		<< CyStartFormat
		<< CyFormatString
		<< wxString ( "\" AS \"Format5\", " )
		<< wxString ( "\"\" AS Groupe, \"" )
		<< CyStartFormat
		<< CyFormatString
		<< wxString ( "\" AS \"Format6\", " )
		<< wxString ( "\"\" AS Sousgroupe, \"")
		<< CyStartFormat
		<< CyFormatDate
		<< wxString ( "\" AS \"Format7\", " )
		<< wxString ( "\"\" AS Mois, \"" )
		<< CyStartFormat
		<< CyFormatCurrency
		<< wxString ( "\" AS \"Format8\", " )
		<< wxString ( "\"\" AS Montant, \"" )
		<< CyStartFormat
		<< CyFormatString
		<< wxString ( "\" AS \"Format9\", \"" )
		<< CyGetText::getInstance ( ).getText ( "CyAnalyseSqlBuilder.getSelectSql.TotalForAttribution" )
		<< wxString ( "\" || b.Description AS SousgroupeName, \"")
		<< CyStartFormat
		<< CyFormatCurrency
		<< wxString ( "\" AS \"Format10\", " )
		<< wxString ( "SUM ( bo.Amount ) AS SousgroupeTotal, \"")
		<< CyStartFormat
		<< CyFormatString
		<< wxString ( "\" AS \"Format11\", " )
		<< wxString ( "\"\" AS GroupeName, \"")
		<< CyStartFormat
		<< CyFormatCurrency
		<< wxString ( "\" AS \"Format12\", " )
		<< wxString ( "\"\" AS GroupeTotal, \"")
		<< CyStartFormat
		<< CyFormatCurrency
		<< wxString ( "\" AS \"Format13\", " )
		<< wxString ( "\"\" AS Total ")
		<< wxString ( "FROM AttributionsGroups g LEFT JOIN Attributions b ON g.ObjId = b.GroupObjId LEFT JOIN OperationsAttributions bo ON b.ObjId = bo.AttributionObjId LEFT JOIN Operations o ON bo.OperationObjId = o.ObjId ")
		<< strWhereClause
		<< wxString ( "GROUP BY g.GroupDescription, b.Description ")

		<< wxString ( "UNION " )

		// Selection for the sum by groups

		<< wxString ( "SELECT \"" )
		<< CyStartFormat
		<< CyFormatHidden
		<< wxString ( "\" AS \"Format1\", ")
		<< wxString ( "g.GroupDescription || \";\" || \"XXXXXXXXXXX\" AS DisplayOrder, \"")
		<< CyStartFormat
		<< CyFormatHidden
		<< wxString ( "\" AS \"Format2\", " )
		<< wxString ( "g.ObjId AS GroupObjId, \"" )
		<< CyStartFormat
		<< CyFormatHidden
		<< wxString ( "\" AS \"Format3\", " )
		<< CyEnum::kInvalidObjId
		<< wxString ( " AS AttributionObjId, \"" )
		<< CyStartFormat
		<< CyFormatHidden
		<< wxString ( "\" AS \"Format4\", " )
		<< wxString ( "\"\" AS BudgetDate, \"" )
		<< CyStartFormat
		<< CyFormatString
		<< wxString ( "\" AS \"Format5\", " )
		<< wxString ( "\"\" AS Groupe, \"" )
		<< CyStartFormat
		<< CyFormatString
		<< wxString ( "\" AS \"Format6\", " )
		<< wxString ( "\"\" AS Sousgroupe, \"")
		<< CyStartFormat
		<< CyFormatDate
		<< wxString ( "\" AS \"Format7\", " )
		<< wxString ( "\"\" AS Mois, \"" )
		<< CyStartFormat
		<< CyFormatCurrency
		<< wxString ( "\" AS \"Format8\", " )
		<< wxString ( "\"\" AS Montant, \"" )
		<< CyStartFormat
		<< CyFormatString
		<< wxString ( "\" AS \"Format9\", " )
		<< wxString ( "\"\" AS SousgroupeName, \"" )
		<< CyStartFormat
		<< CyFormatCurrency
		<< wxString ( "\" AS \"Format10\", " )
		<< wxString ( "\"\" AS SousgroupeTotal, \"")
		<< CyStartFormat
		<< CyFormatString
		<< wxString ( "\" AS \"Format11\", \"" )
		<< CyGetText::getInstance ( ).getText ( "CyAnalyseSqlBuilder.getSelectSql.TotalForGroup" )
		<< wxString ( "\" || g.GroupDescription AS GroupeName, \"")
		<< CyStartFormat
		<< CyFormatCurrency
		<< wxString ( "\" AS \"Format12\", " )
		<< wxString ( "SUM ( bo.Amount ) AS GroupeTotal, \"")
		<< CyStartFormat
		<< CyFormatCurrency
		<< wxString ( "\" AS \"Format13\", " )
		<< wxString ( "\"\" as Total ")
		<< wxString ( "FROM AttributionsGroups g LEFT JOIN Attributions b ON g.ObjId = b.GroupObjId LEFT JOIN OperationsAttributions bo ON b.ObjId = bo.AttributionObjId LEFT JOIN Operations o ON bo.OperationObjId = o.ObjId ")
		<< strWhereClause
		<< wxString ( "GROUP BY g.GroupDescription ")

		<< wxString ( "UNION " )

		// Selection for the sum

		<< wxString ( "SELECT \"" )
		<< CyStartFormat
		<< CyFormatHidden
		<< wxString ( "\" AS \"Format1\", ")
		<< wxString ( "\"XXXXXXXXXXX\" AS DisplayOrder, \"")
		<< CyStartFormat
		<< CyFormatHidden
		<< wxString ( "\" AS \"Format2\", " )
		<< CyEnum::kInvalidObjId
		<< wxString ( " AS GroupObjId, \"" )
		<< CyStartFormat
		<< CyFormatHidden
		<< wxString ( "\" AS \"Format3\", " )
		<< CyEnum::kInvalidObjId
		<< wxString ( " AS AttributionObjId, \"" )
		<< CyStartFormat
		<< CyFormatHidden
		<< wxString ( "\" AS \"Format4\", " )
		<< wxString ( "\"\" AS BudgetDate, \"" )
		<< CyStartFormat
		<< CyFormatString
		<< wxString ( "\" AS \"Format5\", " )
		<< wxString ( "\"\" AS Groupe, \"" )
		<< CyStartFormat
		<< CyFormatString
		<< wxString ( "\" AS \"Format6\", " )
		<< wxString ( "\"\" AS Sousgroupe, \"")
		<< CyStartFormat
		<< CyFormatDate
		<< wxString ( "\" AS \"Format7\", " )
		<< wxString ( "\"\" AS Mois, \"" )
		<< CyStartFormat
		<< CyFormatCurrency
		<< wxString ( "\" AS \"Format8\", " )
		<< wxString ( "\"\" AS Montant, \"" )
		<< CyStartFormat
		<< CyFormatString
		<< wxString ( "\" AS \"Format9\", " )
		<< wxString ( "\"\" AS SousgroupeName, \"" )
		<< CyStartFormat
		<< CyFormatCurrency
		<< wxString ( "\" AS \"Format10\", " )
		<< wxString ( "\"\" AS SousgroupeTotal, \"")
		<< CyStartFormat
		<< CyFormatString
		<< wxString ( "\" AS \"Format11\", " )
		<< wxString ( "\"\" AS GroupeName, \"")
		<< CyStartFormat
		<< CyFormatCurrency
		<< wxString ( "\" AS \"Format12\", " )
		<< wxString ( "\"\" AS GroupeTotal, \"")
		<< CyStartFormat
		<< CyFormatCurrency
		<< wxString ( "\" AS \"Format13\", " )
		<< wxString ( "SUM ( bo.Amount ) AS Total ")
		<< wxString ( "FROM AttributionsGroups g LEFT JOIN Attributions b ON g.ObjId = b.GroupObjId LEFT JOIN OperationsAttributions bo ON b.ObjId = bo.AttributionObjId LEFT JOIN Operations o ON bo.OperationObjId = o.ObjId ")
		<< strWhereClause
		<< wxString ( ") order by DisplayOrder;" );

	return strSelectSql;
}

/* ---------------------------------------------------------------------------- */

wxString CyAnalyseSqlBuilder::getUpdateSql ( const CyQueryResult::CyQueryResultValuesRow& ) const
{
	// Not implemented in this class
	return wxEmptyString;
}

/* ---------------------------------------------------------------------------- */

int CyAnalyseSqlBuilder::getHiddenColumns ( ) const
{
	return 4;
}

/* ---------------------------------------------------------------------------- */
