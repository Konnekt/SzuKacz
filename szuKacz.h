/*
 * License - http://www.gnu.org/licenses/lgpl.txt
 */

#pragma once

namespace SzuKacz
{
	const int net = 512; //wartoœæ net
	const int sig = (int)"SZUKACZ"; //sygnatura
	const int name = (int)"SzuKacz"; //nazwa

	//konfiguracja
	namespace CFG
	{
		const unsigned group = net * 1000 + 100; //grupa konfiguracji
		const unsigned windowPosX = net * 1000 + 101; //po³o¿enie okna na osi X
		const unsigned windowPosY = net * 1000 + 102; //po³o¿enie okna na osi Y
		const unsigned windowWidth = net * 1000 + 103; //szerokoœæ okna
		const unsigned windowHeight = net * 1000 + 104; //wysokoœæ okna
		const unsigned selectedMethod = net * 1000 + 105; //domyœlny item comboboxa ze sposobem
		const unsigned selectedCriterion = net * 1000 + 106; //domyœlny item comboboxa z kryterium
		const unsigned selectedCaseSensitive = net * 1000 + 109; //zaznaczenie checkboxa
		const unsigned column0Width = net * 1000 + 107; //szerokoœæ pierwszej kolumny listboxa
		const unsigned column1Width = net * 1000 + 108; //szerokoœæ drugiej kolumny listboxa
		const unsigned buttonPosition = net * 1000 + 110; //przycisk w menu kontaktów
		const unsigned mruSize = net * 1000 + 113; //iloœæ zapamiêtywanych hase³
		const unsigned quickSearchSelectedCriterion = net * 1000 + 114; //zaznaczone kryterium w szybkim wyszukiwaniu
		const unsigned quickSearchSelectedMethod = net * 1000 + 115; //zaznaczony sposób w szybkim wyszukiwaniu
		const unsigned quickSearchSelectedCaseSensitive = net * 1000 + 116; //czy reagowaæ na wielkoœæ znaków w szybkim wyszukiwaniu
		const unsigned toolbarAction = net * 1000 + 117; //domyœlna akcja po klikniêciu na przycisk na toolbarze
		const unsigned quickSearchEnterAction = net * 1000 + 118; //akcja po naciœniêciu entera w oknie szybkiego wyszukiwania
		const unsigned quickSearchCtrlEnterAction = net * 1000 + 119; //akcja po naciœniêciu ctrl+enter w oknie szybkiego wyszukiwania
	}

	//akcje
	namespace ACT
	{
		const unsigned groupButton = net * 1000 + 0;
		const unsigned search = net * 1000 + 1;
		const unsigned quickSearch = net * 1000 + 2;
		const unsigned clearMRU = net * 1000 + 3;
		const unsigned quickSearchPrevious = net * 1000 + 23;
		const unsigned quickSearchNext = net * 1000 + 24;

		const unsigned buttonPositionContactMenu = net * 1000 + 25;
		const unsigned buttonPositionPluginsMenu = net * 1000 + 26;
		const unsigned buttonPositionMainToolbar = net * 1000 + 27;

		const unsigned criterionMenu = net * 1000 + 4;
		const unsigned criterionMenuStatusInfo = net * 1000 + 5;
		const unsigned criterionMenuUID = net * 1000 + 6;
		const unsigned criterionMenuDisplay = net * 1000 + 7;
		const unsigned criterionMenuCellPhone = net * 1000 + 8;
		const unsigned criterionMenuHost = net * 1000 + 9;
		const unsigned criterionMenuLocality = net * 1000 + 10;
		const unsigned criterionMenuName = net * 1000 + 11;
		const unsigned criterionMenuSurname = net * 1000 + 12;
		const unsigned criterionMenuNick = net * 1000 + 13;

		const unsigned methodMenu = net * 1000 + 14;
		const unsigned methodMenuCaseSensitive = net * 1000 + 15;
		const unsigned methodMenuContains = net * 1000 + 16;
		const unsigned methodMenuEqual = net * 1000 + 17;
		const unsigned methodMenuNotEqual = net * 1000 + 18;
		const unsigned methodMenuBegins = net * 1000 + 19;
		const unsigned methodMenuEnds = net * 1000 + 20;
		const unsigned methodMenuNotContains = net * 1000 + 21;
		const unsigned methodMenuPreg = net * 1000 + 22;
	}

	//ikony
	namespace ICO
	{
		const unsigned SzuKacz16 = net * 1000 + 200; //identyfikator ikonki 16px
		const unsigned SzuKacz32 = net * 1000 + 201; //identyfikator ikonki 32px
		const unsigned previous = net * 1000 + 202; //identyfikator ikonki poprzedniego wyniku
		const unsigned next = net * 1000 + 203; //identyfikator ikonki nastêpnego wyniku
		const unsigned criterion = net * 1000 + 204; //identyfikator ikonki kryterium
		const unsigned method = net * 1000 + 205; //identyfikator ikonki sposobu
	}

	//zasoby
	namespace RES
	{
		const char SzuKacz16[] = "res://dll/101.ico#size=16"; //ikonka 16px
		const char SzuKacz32[] = "res://dll/102.ico#size=32"; //ikonka 32px
		const char previous[] = "res://dll/103.ico#size=16"; //ikonka poprzedniego wyniku
		const char next[] = "res://dll/104.ico#size=32"; //ikonka nastêpnego wyniku
		const char criterion[] = "res://dll/105.ico#size=16"; //ikonka kryterium
		const char method[] = "res://dll/106.ico#size=32"; //ikonka sposobu
	}
}