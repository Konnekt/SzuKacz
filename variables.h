#pragma once

namespace szuKacz
{
	extern HWND window; //uchwyt okna
	extern HWND groupbox; //uchwyt GroupBoxa
	extern HWND edit; //uchwyt Edita
	extern HWND combobox1; //uchwyt ComboBoxa ze sposobem
	extern HWND combobox2; //uchwyt ComboBoxa z kryterium
	extern HWND checkbox; //uchwyt CheckBoxa
	extern HWND button; //uchwyt Buttona
	extern HWND listview; //uchwyt ListViewa
	extern HWND toolbar; //uchwyt Toolbara
	extern HWND QuickSearchToolbar; //uchwyt Toolbara z szybkim wyszukiwaniem
	extern HWND QuickSearchEdit; //uchwyt Edita w szybkim wyszukiwaniu
	extern MRU* MRUList; //obiekt do obs³ugi MRU
	extern std::list<Result> results; //wyniki wyszukiwania w okienku
	extern std::list<Result> QuickSearchResults; //wyniki szubkiego wyszukiwania
	extern WNDPROC old_main_wnd_proc; //stary proc g³ównego okna
	extern WNDPROC QuickSearchToolbarOldProc; //stary proc toolbara szybkiego wyszukiwania
	extern WNDPROC QuickSearchEditOldProc; //stary proc edita szybkiego wyszukiwania
	extern std::list<szuKacz::Result>::iterator* CurrentResult; //ostatni zaznaczony wynik
	extern HWND KonnektMainWindow; //uchwyt g³ównego okna K
	extern HWND CNTListWindow; //uchwyt okna listy kontkatów
	extern bool QuickSearchToolbarVisible; //czy toolbar szybkiego wyszukiwania jest ukryty
}