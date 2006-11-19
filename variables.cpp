#include "stdafx.h"
#include "includes.h"

namespace szuKacz
{
	HWND window; //uchwyt okna
	HWND groupbox; //uchwyt GroupBoxa
	HWND edit; //uchwyt Edita
	HWND combobox1; //uchwyt ComboBoxa ze sposobem
	HWND combobox2; //uchwyt ComboBoxa z kryterium
	HWND checkbox; //uchwyt CheckBoxa
	HWND button; //uchwyt Buttona
	HWND listview; //uchwyt ListViewa
	HWND toolbar; //uchwyt Toolbara
	HWND QuickSearchToolbar; //uchwyt Toolbara z szybkim wyszukiwaniem
	HWND QuickSearchEdit; //uchwyt Edita w szybkim wyszukiwaniu
	MRU* MRUList; //obiekt do obs�ugi MRU
	std::list<Result> results; //wyniki wyszukiwania
	std::list<Result> QuickSearchResults; //wyniki szubkiego wyszukiwania
	WNDPROC old_main_wnd_proc; //stary proc g��wnego okna
	WNDPROC QuickSearchToolbarOldProc; //stary proc toolbara szybkiego wyszukiwania
	WNDPROC QuickSearchEditOldProc; //stary proc edita szybkiego wyszukiwania
	std::list<szuKacz::Result>::iterator* CurrentResult; //ostatni zaznaczony wynik
	HWND KonnektMainWindow; //uchwyt g��wnego okna K
	HWND CNTListWindow; //uchwyt okna listy kontkat�w
	bool QuickSearchToolbarVisible; //czy toolbar szybkiego wyszukiwania jest ukryty
}