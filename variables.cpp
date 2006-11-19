#include "includes.h"

namespace szuKacz
{
	HWND window; //uchwyt okna
	HWND groupbox; //uchwyt GroupBoxa
	HWND edit; //uchwyt Edita
	HWND combobox1; //uchwyt ComboBoxa ze sposobem
	HWND combobox2; //uchwyt ComboBoxa z kryterium
	HWND checkbox; //uchwyt CheckBoxa
	HWND listview; //uchwyt ListViewa
	HWND toolbar; //uchwyt Toolbara
	WNDCLASSEX window_class; //klasa dla okna
	std::vector<Result> results; //wyniki wyszukiwania
}