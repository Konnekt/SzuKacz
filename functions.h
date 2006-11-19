#pragma once

namespace szuKacz
{
	//funkcja przeszukuj¹ca listê kontaktów i zwracaj¹ca tablicê z wynikami
	std::list<Result> findContact(int field, std::string &toMatch, int relationType, bool CaseSensitive, bool FromList = 1, bool save = 0);

	//funkcja obs³uguj¹ca g³ówne okno
	LRESULT CALLBACK KonnektMainWindowProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam);

	//funkcja obs³uguj¹ca toolbar szybkiego wyszukiwania
	LRESULT CALLBACK QuickSearchToolbarProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam);

	//funkcja obs³uguj¹ca edit szybkiego wyszukiwania
	LRESULT CALLBACK QuickSearchEditProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam);
}