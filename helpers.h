#pragma once

namespace szuKacz
{
	//funkcja do sortowania item�w ListViewa
	int CALLBACK Sort(LPARAM idItem1, LPARAM idItem2, LPARAM lParamSort);

	//funkcja wywo�uj�ca akcj�
	void CallAction(sUIAction act);

	//funkcja wywo�uj�ca akcj�
	void CallAction(int parent, int id, int cnt);

	//funkcja pobieraj�ca domy�ln� akcje (by Aule)
	int GetDefaultAction(int cnt);
}