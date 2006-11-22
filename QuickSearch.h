#pragma once

namespace szuKacz
{
	//funkcja obs³uguj¹ca toolbar szybkiego wyszukiwania
	LRESULT CALLBACK QuickSearchToolbarProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam);

	//funkcja obs³uguj¹ca edit szybkiego wyszukiwania
	LRESULT CALLBACK QuickSearchEditProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam);

	//funkcja odœwie¿aj¹ca toolbar szybkiego wyszukiwania
	void QuickSearchToolbarRefresh(bool Move = 0);

	//funkcja chowa toolbar szybkiego wyszukiwania
	void QuickSearchToolbarHide(bool FocusRooster = 1);
}