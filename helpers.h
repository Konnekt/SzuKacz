#pragma once

namespace szuKacz
{
	//funkcja do sortowania item�w ListViewa
	int CALLBACK Sort(LPARAM idItem1, LPARAM idItem2, LPARAM lParamSort);

	//funkcja wywo�uj�ca akcj�
	void CallAction(sUIAction act);

	//funkcja wywo�uj�ca akcj�
	void CallAction(int parent, int id, int cnt = -2);

	//funkcja pobieraj�ca domy�ln� akcje (by Aule)
	int GetDefaultAction(int cnt);

	//funkcja sprawdzaj�ca, czy punt znajduje si� w kwadracie
	bool IsInside(POINT pt, RECT r);

	//funkcja zaznaczaj�ca na li�cie kontakt o podanym ID
	void SelectCNT(HWND ListView, int CNT);

	//funkcja sprawdzaj�ca, czy plugin o danym necie istnieje
	int PluginExists(int net, int type = IMT_ALL);
}