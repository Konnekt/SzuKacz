#pragma once

namespace szuKacz
{
	//funkcja do sortowania itemów ListViewa
	int CALLBACK Sort(LPARAM idItem1, LPARAM idItem2, LPARAM lParamSort);

	//funkcja wywo³uj¹ca akcjê
	void CallAction(sUIAction act);

	//funkcja wywo³uj¹ca akcjê
	void CallAction(int parent, int id, int cnt);

	//funkcja pobieraj¹ca domyœln¹ akcje (by Aule)
	int GetDefaultAction(int cnt);
}