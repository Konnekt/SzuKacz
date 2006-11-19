#pragma once

namespace szuKacz
{
	//funkcja obs³uguj¹ca wiadomoœci okienka
	LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

	//funkcja tworz¹ca okienko
	void Window();

	//funkcja tworz¹ca GroupBoxa
	void GroupBox(HWND parent);

	//funkcja tworz¹ca Edita
	void Edit(HWND parent);

	//funkcja tworz¹ca ComboBoxa ze sposobem
	void ComboBox1(HWND parent);

	//funkcja tworz¹ca ComboBoxa z kryterium
	void ComboBox2(HWND parent);

	//funkcja tworz¹ca CheckBoxa
	void CheckBox(HWND parent);

	//funkcja tworz¹ca ListViewa
	void ListView(HWND parent);

	//funkcja tworz¹ca Toolbara
	void Toolbar(HWND parent);
}