#pragma once

namespace szuKacz
{
	//funkcja do sortowania itemów ListViewa
	int CALLBACK Sort(LPARAM idItem1, LPARAM idItem2, LPARAM lParamSort);

	//funkcja wywo³uj¹ca akcjê
	void CallAction(sUIAction act);

	//funkcja wywo³uj¹ca akcjê
	void CallAction(int parent, int id, int cnt = -2);

	//funkcja pobieraj¹ca domyœln¹ akcje (by Aule)
	int GetDefaultAction(int cnt);

	//funkcja sprawdzaj¹ca, czy punt znajduje siê w kwadracie
	bool IsInside(POINT pt, RECT r);

	//funkcja zaznaczaj¹ca na liœcie kontakt o podanym ID
	void SelectCNT(HWND ListView, int CNT);

	//funkcja sprawdzaj¹ca, czy plugin o danym necie istnieje
	int PluginExists(int net, int type = IMT_ALL);
}