#pragma once

namespace szuKacz
{
	//funkcja obs�uguj�ca toolbar szybkiego wyszukiwania
	LRESULT CALLBACK QuickSearchToolbarProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam);

	//funkcja obs�uguj�ca edit szybkiego wyszukiwania
	LRESULT CALLBACK QuickSearchEditProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam);

	//funkcja od�wie�aj�ca toolbar szybkiego wyszukiwania
	void QuickSearchToolbarRefresh(bool Move = 0);

	//funkcja chowa toolbar szybkiego wyszukiwania
	void QuickSearchToolbarHide(bool FocusRooster = 1);
}