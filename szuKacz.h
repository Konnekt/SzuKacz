#pragma once

namespace szuKacz
{
	const int Net = 512; //wartoœæ Net
	const int Sig = (int)"SZUKACZ"; //sygnatura
	const int Name = (int)"SzuKacz"; //nazwa

	//konfiguracja
	namespace Config
	{
		const unsigned Group = Net * 1000 + 100; //grupa konfiguracji
		const unsigned WindowX = Net * 1000 + 101; //po³o¿enie okna na osi X
		const unsigned WindowY = Net * 1000 + 102; //po³o¿enie okna na osi Y
		const unsigned WindowWidth = Net * 1000 + 103; //szerokoœæ okna
		const unsigned WindowHeight = Net * 1000 + 104; //wysokoœæ okna
		const unsigned ComboBox1 = Net * 1000 + 105; //domyœlny item comboboxa ze sposobem
		const unsigned ComboBox2 = Net * 1000 + 106; //domyœlny item comboboxa z kryterium
		const unsigned CheckBox = Net * 1000 + 109; //zaznaczenie checkboxa
		const unsigned ListBoxColumn0 = Net * 1000 + 107; //szerokoœæ pierwszej kolumny listboxa
		const unsigned ListBoxColumn1 = Net * 1000 + 108; //szerokoœæ drugiej kolumny listboxa
		const unsigned ButtonPosition = Net * 1000 + 110; //przycisk w menu kontaktów
		const unsigned MRUSize = Net * 1000 + 113; //iloœæ zapamiêtywanych hase³
		const unsigned Criterion = Net * 1000 + 114; //zaznaczone kryterium w szybkim wyszukiwaniu
		const unsigned Method = Net * 1000 + 115; //zaznaczony sposób w szybkim wyszukiwaniu
		const unsigned CaseSensitive = Net * 1000 + 116; //czy reagowaæ na wielkoœæ znaków w szybkim wyszukiwaniu
		const unsigned DefaultAction = Net * 1000 + 117; //domyœlna akcja po klikniêciu na przycisk na toolbarze
	}

	//akcje
	namespace Acts
	{
		const unsigned Group = Net * 1000 + 0;
		const unsigned Search = Net * 1000 + 1;
		const unsigned QuickSearch = Net * 1000 + 2;
		const unsigned ClearMRU = Net * 1000 + 3;
		const unsigned QuickSearchPrevious = Net * 1000 + 24;
		const unsigned QuickSearchNext = Net * 1000 + 23;

		const unsigned CriterionMenu = Net * 1000 + 4;
		const unsigned CriterionMenuStatusInfo = Net * 1000 + 5;
		const unsigned CriterionMenuUID = Net * 1000 + 6;
		const unsigned CriterionMenuDisplay = Net * 1000 + 7;
		const unsigned CriterionMenuCellPhone = Net * 1000 + 8;
		const unsigned CriterionMenuHost = Net * 1000 + 9;
		const unsigned CriterionMenuLocality = Net * 1000 + 10;
		const unsigned CriterionMenuName = Net * 1000 + 11;
		const unsigned CriterionMenuSurname = Net * 1000 + 12;
		const unsigned CriterionMenuNick = Net * 1000 + 13;

		const unsigned MethodMenu = Net * 1000 + 14;
		const unsigned MethodMenuCaseSensitive = Net * 1000 + 15;
		const unsigned MethodMenuContains = Net * 1000 + 16;
		const unsigned MethodMenuEqual = Net * 1000 + 17;
		const unsigned MethodMenuNotEqual = Net * 1000 + 18;
		const unsigned MethodMenuBegins = Net * 1000 + 19;
		const unsigned MethodMenuEnds = Net * 1000 + 20;
		const unsigned MethodMenuNotContains = Net * 1000 + 21;
		const unsigned MethodMenuPreg = Net * 1000 + 22;
	}

	//ikony
	namespace Icons
	{
		const unsigned szuKacz16 = Net * 1000 + 200; //identyfikator ikonki 16px
		const unsigned szuKacz32 = Net * 1000 + 201; //identyfikator ikonki 32px
		const unsigned Previous = Net * 1000 + 202; //identyfikator ikonki poprzedniego wyniku
		const unsigned Next = Net * 1000 + 203; //identyfikator ikonki nastêpnego wyniku
		const unsigned Criterion = Net * 1000 + 204; //identyfikator ikonki kryterium
		const unsigned Method = Net * 1000 + 205; //identyfikator ikonki sposobu
	}

	//zasoby
	namespace Resources
	{
		const int szuKacz16 = (int)"res://dll/101.ico#size=16"; //ikonka 16px
		const int szuKacz32 = (int)"res://dll/102.ico#size=32"; //ikonka 32px
		const int Previous = (int)"res://dll/103.ico#size=16"; //ikonka poprzedniego wyniku
		const int Next = (int)"res://dll/104.ico#size=32"; //ikonka nastêpnego wyniku
		const int Criterion = (int)"res://dll/105.ico#size=16"; //ikonka kryterium
		const int Method = (int)"res://dll/106.ico#size=32"; //ikonka sposobu
	}
}