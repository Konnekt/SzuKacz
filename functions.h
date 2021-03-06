/*
 * License - http://www.gnu.org/licenses/lgpl.txt
 */

#pragma once

namespace SzuKacz
{
	//funkcja obsługująca okno wyszukiwania
	LRESULT CALLBACK searchWindowProc(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam);

	//funkcja obsługująca główne okno Konnekta
	LRESULT CALLBACK konnektMainWindowProc(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam);

	//funkcja obsługująca toolbar szybkiego wyszukiwania
	LRESULT CALLBACK quickSearchToolbarProc(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam);

	//funkcja obsługująca edit szybkiego wyszukiwania
	LRESULT CALLBACK quickSearchEditProc(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam);
}