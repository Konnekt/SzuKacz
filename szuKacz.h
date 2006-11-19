#pragma once

namespace szuKacz
{
	const int Net = 512; //wartoœæ Net
	const int Sig = (int)"SZUKACZ"; //sygnatura
	const int Name = (int)"szuKacz"; //nazwa

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
		const unsigned ButtonInCntMenu = Net * 1000 + 110; //przycisk w menu kontaktów
		const unsigned ButtonOnToolbar = Net * 1000 + 111; //przycisk na toolbarze wtyczek
		const unsigned ButtonOnMainToolbar = Net * 1000 + 112; //przycisk na g³ównym toolbarze
	}

	//akcje
	namespace Acts
	{
		const int Search = Net * 1000 + 1;
	}

	//ikony
	namespace Icons
	{
		const unsigned szuKacz16 = Net * 1000 + 200; //identyfikator ikonki 16px
		const unsigned szuKacz32 = Net * 1000 + 201; //identyfikator ikonki 32px
	}

	//zasoby
	namespace Resources
	{
		const int szuKacz16 = (int)"res://dll/101.ico#size=16"; //ikonka 16px
		const int szuKacz32 = (int)"res://dll/102.ico#size=32"; //ikonka 32px
	}
}