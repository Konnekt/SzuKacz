/*
 * License - http://www.gnu.org/licenses/lgpl.txt
 */

#pragma once

namespace SzuKacz
{
	//funkcja do sortowania itemów ListViewa
	int CALLBACK sort(LPARAM idItem1, LPARAM idItem2, LPARAM lParamSort);

	//funkcja wywo³uj¹ca akcjê
	void callAction(sUIAction act);

	//funkcja wywo³uj¹ca akcjê
	void callAction(int parent, int id, int cnt = -2);

	//funkcja pobieraj¹ca domyœln¹ akcje (by Aule)
	int getDefaultAction(int cnt);

	//funkcja sprawdzaj¹ca, czy punt znajduje siê w kwadracie
	bool isInside(POINT pt, RECT r);

	//funkcja sprawdzaj¹ca, czy plugin o danym necie istnieje
	int pluginExists(int net, int type = IMT_ALL);

	//funkcja otwieraj¹ca okno rozmowy dla danego kontaktu
	void openMsgWindow(int cnt);

	//funkcja otwieraj¹ca okno w³aœciwoœci dla danego kontaktu
	void openInfoWindow(int cnt);

	//funkcja odpalaj¹ca domyœln¹ akcjê
	void callDefaultAction(int cnt);
}