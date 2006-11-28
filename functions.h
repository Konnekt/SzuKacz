#pragma once

namespace SzuKacz
{
	//funkcja obs�uguj�ca okno wyszukiwania
	LRESULT CALLBACK searchWindowProc(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam);

	//funkcja obs�uguj�ca g��wne okno Konnekta
	LRESULT CALLBACK konnektMainWindowProc(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam);

	//funkcja obs�uguj�ca toolbar szybkiego wyszukiwania
	LRESULT CALLBACK quickSearchToolbarProc(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam);

	//funkcja obs�uguj�ca edit szybkiego wyszukiwania
	LRESULT CALLBACK quickSearchEditProc(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam);
}