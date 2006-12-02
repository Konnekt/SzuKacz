/*
 * License - http://www.gnu.org/licenses/lgpl.txt
 */

#pragma once

namespace SzuKacz
{
	//funkcja do sortowania item�w ListViewa
	int CALLBACK sort(LPARAM idItem1, LPARAM idItem2, LPARAM lParamSort);

	//funkcja wywo�uj�ca akcj�
	void callAction(sUIAction act);

	//funkcja wywo�uj�ca akcj�
	void callAction(int parent, int id, int cnt = -2);

	//funkcja pobieraj�ca domy�ln� akcje (by Aule)
	int getDefaultAction(int cnt);

	//funkcja sprawdzaj�ca, czy punt znajduje si� w kwadracie
	bool isInside(POINT pt, RECT r);

	//funkcja sprawdzaj�ca, czy plugin o danym necie istnieje
	int pluginExists(int net, int type = IMT_ALL);

	//funkcja otwieraj�ca okno rozmowy dla danego kontaktu
	void openMsgWindow(int cnt);

	//funkcja otwieraj�ca okno w�a�ciwo�ci dla danego kontaktu
	void openInfoWindow(int cnt);

	//funkcja odpalaj�ca domy�ln� akcj�
	void callDefaultAction(int cnt);
}