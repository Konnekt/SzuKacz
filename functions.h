#pragma once

namespace szuKacz
{
	//funkcja przeszukuj�ca list� kontakt�w i zwracaj�ca tablic� z wynikami
	std::list<Result> findContact(int field, std::string &toMatch, int relationType, bool CaseSensitive, bool FromList = 1, bool save = 0);

	//funkcja obs�uguj�ca g��wne okno
	LRESULT CALLBACK KonnektMainWindowProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam);

	//funkcja obs�uguj�ca toolbar szybkiego wyszukiwania
	LRESULT CALLBACK QuickSearchToolbarProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam);

	//funkcja obs�uguj�ca edit szybkiego wyszukiwania
	LRESULT CALLBACK QuickSearchEditProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam);
}