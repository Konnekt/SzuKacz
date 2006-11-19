#pragma once

namespace szuKacz
{
	//funkcja obs�uguj�ca wiadomo�ci okienka
	LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

	//funkcja tworz�ca okienko
	void Window();

	//funkcja tworz�ca GroupBoxa
	void GroupBox(HWND parent);

	//funkcja tworz�ca Edita
	void Edit(HWND parent);

	//funkcja tworz�ca ComboBoxa ze sposobem
	void ComboBox1(HWND parent);

	//funkcja tworz�ca ComboBoxa z kryterium
	void ComboBox2(HWND parent);

	//funkcja tworz�ca CheckBoxa
	void CheckBox(HWND parent);

	//funkcja tworz�ca ListViewa
	void ListView(HWND parent);

	//funkcja tworz�ca Toolbara
	void Toolbar(HWND parent);
}