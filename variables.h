#pragma once

namespace szuKacz
{
	extern HWND window; //uchwyt okna
	extern HWND groupbox; //uchwyt GroupBoxa
	extern HWND edit; //uchwyt Edita
	extern HWND combobox1; //uchwyt ComboBoxa ze sposobem
	extern HWND combobox2; //uchwyt ComboBoxa z kryterium
	extern HWND checkbox; //uchwyt CheckBoxa
	extern HWND listview; //uchwyt ListViewa
	extern HWND toolbar; //uchwyt Toolbara
	extern WNDCLASSEX window_class; //klasa dla okna
	extern std::vector<Result> results; //wyniki wyszukiwania
}