#pragma once

namespace SzuKacz
{
	//funkcja obs³uguj¹ca okno wyszukiwania
	LRESULT CALLBACK searchWindowProc(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam);

	//funkcja obs³uguj¹ca g³ówne okno Konnekta
	LRESULT CALLBACK konnektMainWindowProc(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam);

	//funkcja obs³uguj¹ca toolbar szybkiego wyszukiwania
	LRESULT CALLBACK quickSearchToolbarProc(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam);

	//funkcja obs³uguj¹ca edit szybkiego wyszukiwania
	LRESULT CALLBACK quickSearchEditProc(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam);
}