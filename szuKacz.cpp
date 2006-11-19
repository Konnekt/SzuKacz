#include "stdafx.h"
#include "includes.h"

namespace szuKacz
{
	int IStart()
	{
		//rejestrujemy klasê okna
		{
			WNDCLASSEX window_class;
			window_class.style = CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS;
			window_class.lpfnWndProc = szuKacz::WindowProc;
			window_class.cbClsExtra = 0;
			window_class.cbWndExtra = 0;
			window_class.hInstance = Ctrl->hInst();
			window_class.hCursor = LoadCursor(0, IDC_ARROW);
			window_class.lpszMenuName = 0;
			window_class.lpszClassName = "szukacz_window_class";
			window_class.hbrBackground = GetSysColorBrush(COLOR_BTNFACE);
			window_class.hIcon = (HICON)Ctrl->ICMessage(IMI_ICONGET, szuKacz::Icons::szuKacz32, IML_32);
			window_class.hIconSm = (HICON)Ctrl->ICMessage(IMI_ICONGET, szuKacz::Icons::szuKacz16, IML_16);
			window_class.cbSize = sizeof(window_class);
			RegisterClassEx(&window_class);
		}

		return 1;
	}

	int IEnd()
	{
		//usuwamy obiekt do obs³ugi MRU
		{
			delete szuKacz::MRUList;
			szuKacz::MRUList = 0;
		}

		//usuwamy wskaŸnik na aktualny wynik
		{
			delete szuKacz::CurrentResult;
			szuKacz::CurrentResult = 0;
		}

		//sprawdzamy, czy nie s¹ wy³¹czone stworzone okna i w razie czego niszczymy je
		{
			if(szuKacz::window)
			{
				SendMessage(szuKacz::window, WM_CLOSE, 0, 0);
			}

			if(szuKacz::QuickSearchToolbar)
			{
				DestroyWindow(szuKacz::QuickSearchToolbar);
				szuKacz::QuickSearchToolbar = 0;
			}

			if(szuKacz::QuickSearchEdit)
			{
				DestroyWindow(szuKacz::QuickSearchEdit);
				szuKacz::QuickSearchEdit = 0;
			}			
		}

		//wyrejestrowujemy klasê okna
		{
			UnregisterClass("szukacz_window_class", Ctrl->hInst());
		}

		return 1;
	}

	int ISetCols()
	{
		//okno
		{
			Ctrl->SetColumn(DTCFG, szuKacz::Config::WindowX, DT_CT_INT, (GetSystemMetrics(SM_CXSCREEN) / 2) - ((180-(GetSystemMetrics(SM_CXFIXEDFRAME) * 2)) / 2), "szuKacz/Config/WindowX");
			Ctrl->SetColumn(DTCFG, szuKacz::Config::WindowY, DT_CT_INT, (GetSystemMetrics(SM_CYSCREEN) / 2) - ((120 - (GetSystemMetrics(SM_CYFIXEDFRAME) * 2) + GetSystemMetrics (SM_CYCAPTION)) / 2), "szuKacz/Config/WindowY");
			Ctrl->SetColumn(DTCFG, szuKacz::Config::WindowWidth, DT_CT_INT, 500 + GetSystemMetrics(SM_CXFIXEDFRAME) * 2, "szuKacz/Config/WindowWidth");
			Ctrl->SetColumn(DTCFG, szuKacz::Config::WindowHeight, DT_CT_INT, 300 + GetSystemMetrics(SM_CYFIXEDFRAME) * 2 + GetSystemMetrics(SM_CYCAPTION), "szuKacz/Config/WindowHeight");
			Ctrl->SetColumn(DTCFG, szuKacz::Config::ComboBox1, DT_CT_INT, 1, "szuKacz/Config/ComboBox1");
			Ctrl->SetColumn(DTCFG, szuKacz::Config::ComboBox2, DT_CT_INT, 0, "szuKacz/Config/ComboBox2");
			Ctrl->SetColumn(DTCFG, szuKacz::Config::CheckBox, DT_CT_INT, 0, "szuKacz/Config/CheckBox");
			Ctrl->SetColumn(DTCFG, szuKacz::Config::ListBoxColumn0, DT_CT_INT, 100, "szuKacz/Config/ListBoxColumn0");
			Ctrl->SetColumn(DTCFG, szuKacz::Config::ListBoxColumn1, DT_CT_INT, 200, "szuKacz/Config/ListBoxColumn1");
			Ctrl->SetColumn(DTCFG, szuKacz::Config::ButtonPosition, DT_CT_INT, 0, "szuKacz/ButtonPosition");
			Ctrl->SetColumn(DTCFG, szuKacz::Config::MRUSize, DT_CT_INT, 5, "szuKacz/MRUSize");
			Ctrl->SetColumn(DTCFG, szuKacz::Config::Criterion, DT_CT_INT, 0, "szuKacz/Criterion");
			Ctrl->SetColumn(DTCFG, szuKacz::Config::Method, DT_CT_INT, 0, "szuKacz/Method");
			Ctrl->SetColumn(DTCFG, szuKacz::Config::CaseSensitive, DT_CT_INT, 0, "szuKacz/CaseSensitive");
			Ctrl->SetColumn(DTCFG, szuKacz::Config::DefaultAction, DT_CT_INT, 0, "szuKacz/DefaultAction");
		}

		return 1;
	}

	int IPrepare()
	{
		//przygotowujemy klasê do obs³ugi MRU
		{
			szuKacz::MRUList = new MRU("szuKacz", szuKacz::Config::MRUSize, 1);
		}

		//rejestrujemy ikonki
		{
			IconRegister(IML_16, szuKacz::Icons::szuKacz16, (char*)szuKacz::Resources::szuKacz16);
			IconRegister(IML_32, szuKacz::Icons::szuKacz32, (char*)szuKacz::Resources::szuKacz32);
			IconRegister(IML_16, szuKacz::Icons::Previous, (char*)szuKacz::Resources::Previous);
			IconRegister(IML_16, szuKacz::Icons::Next, (char*)szuKacz::Resources::Next);
			IconRegister(IML_16, szuKacz::Icons::Criterion, (char*)szuKacz::Resources::Criterion);
			IconRegister(IML_16, szuKacz::Icons::Method, (char*)szuKacz::Resources::Method);
		}

		//przycisk
		switch(GETINT(szuKacz::Config::ButtonPosition))
		{
			case 0:
			{
				UIGroupAdd(IMIG_MAIN_CNT, szuKacz::Acts::Group, 0, "Szukaj na liœcie", szuKacz::Icons::szuKacz16);
				break;
			}
			case 1:
			{
				UIGroupAdd(Ctrl->IMessage(IMI_GETPLUGINSGROUP, 0, 0), szuKacz::Acts::Group, 0, "Szukaj na liœcie", szuKacz::Icons::szuKacz16);
				break;
			}
			case 2:
			{
				UIGroupAdd(IMIG_MAINTB, szuKacz::Acts::Group, 0, "Szukaj na liœcie", szuKacz::Icons::szuKacz16);
				break;
			}
		}

		UIActionAdd(szuKacz::Acts::Group, szuKacz::Acts::Search, 0, "Okienko wyszukiwania", szuKacz::Icons::szuKacz16);
		UIActionAdd(szuKacz::Acts::Group, szuKacz::Acts::QuickSearch, 0, "Szybkie wyszukiwanie", szuKacz::Icons::szuKacz16);

		UIGroupAdd(IMIG_CFG_PLUGS, szuKacz::Config::Group, 0, "SzuKacz", szuKacz::Icons::szuKacz16);
		{
			UIActionCfgAddPluginInfoBox2(szuKacz::Config::Group, "Wtyczka pozwala na szybkie przeszukiwanie listy kontaktów wed³ug ró¿nych kryteriów.", "<span class='note'>Skompilowano: <b>"__DATE__"</b> [<b>"__TIME__"</b>]</span><br/><br/>Copyright © 2004-2006 <b>Skolima</b><br/>Copyright © 2006 <b>Micha³ \"Dulek\" Dulko</b>", (char*)szuKacz::Resources::szuKacz32);

			if(Konnekt::ShowBits::checkLevel(Konnekt::ShowBits::levelIntermediate))
			{
				UIActionAdd(szuKacz::Config::Group, 0, ACTT_GROUP, "Opcje");
				{
					UIActionAdd(szuKacz::Config::Group, 0, ACTT_SEP, "Po³o¿enie przycisku");
					{
						UIActionAdd(szuKacz::Config::Group, 0, ACTT_RADIO|ACTSC_NEEDRESTART|ACTSRADIO_BYPOS, "W menu kontaktów", szuKacz::Config::ButtonPosition);
						UIActionAdd(szuKacz::Config::Group, 0, ACTT_RADIO|ACTSC_NEEDRESTART|ACTSRADIO_BYPOS, "W menu wtyczek", szuKacz::Config::ButtonPosition);
						UIActionAdd(szuKacz::Config::Group, 0, ACTT_RADIO|ACTSC_NEEDRESTART|ACTSRADIO_BYPOS|ACTSRADIO_LAST, "Na g³ównym toolbarze", szuKacz::Config::ButtonPosition);
					}
					UIActionAdd(szuKacz::Config::Group, 0, ACTT_SEP, "Domyœlna akcja");
					{
						UIActionAdd(szuKacz::Config::Group, 0, ACTT_COMBO|ACTSCOMBO_LIST|ACTSCOMBO_BYPOS, "Okienko wyszukiwania" CFGICO "512200" "\nSzybkie wyszukiwanie" CFGICO "512200", szuKacz::Config::DefaultAction, 150);
					}
				}
				UIActionCfgAdd(szuKacz::Config::Group, 0, ACTT_GROUPEND);
			}
			if(Konnekt::ShowBits::checkLevel(Konnekt::ShowBits::levelNormal))
			{
				UIActionAdd(szuKacz::Config::Group, 0, ACTT_GROUP, "Historia wyszukiwanych hase³");
				{
					UIActionAdd(szuKacz::Config::Group, 0, ACTT_COMMENT, "Iloœæ pozycji w historii:");
					UIActionAdd(szuKacz::Config::Group, 0, ACTT_SLIDER, "Ma³o\nDu¿o" AP_MINIMUM "1" AP_MAXIMUM "100", szuKacz::Config::MRUSize);
					UIActionAdd(szuKacz::Config::Group, 0, ACTT_SEPARATOR);
					UIActionAdd(szuKacz::Config::Group, szuKacz::Acts::ClearMRU, ACTT_BUTTON, "Wyczyœæ" AP_ICO "50");
				}
				UIActionCfgAdd(szuKacz::Config::Group, 0, ACTT_GROUPEND);
			}
		}

		//menu kontekstowe
		{
			UIGroupAdd(0, szuKacz::Acts::CriterionMenu, ACTR_INIT, "Menu kryterium");
			{
				UIActionAdd(szuKacz::Acts::CriterionMenu, szuKacz::Acts::CriterionMenuStatusInfo, ACTT_CHECK, "Opis");
				UIActionAdd(szuKacz::Acts::CriterionMenu, szuKacz::Acts::CriterionMenuUID, ACTT_CHECK, "UID");
				UIActionAdd(szuKacz::Acts::CriterionMenu, szuKacz::Acts::CriterionMenuDisplay, ACTT_CHECK, "Wyœwietl jako");
				UIActionAdd(szuKacz::Acts::CriterionMenu, szuKacz::Acts::CriterionMenuCellPhone, ACTT_CHECK, "Komórka");
				UIActionAdd(szuKacz::Acts::CriterionMenu, szuKacz::Acts::CriterionMenuHost, ACTT_CHECK, "IP");
				UIActionAdd(szuKacz::Acts::CriterionMenu, szuKacz::Acts::CriterionMenuLocality, ACTT_CHECK, "Miejscowoœæ");
				UIActionAdd(szuKacz::Acts::CriterionMenu, szuKacz::Acts::CriterionMenuName, ACTT_CHECK, "Imiê");
				UIActionAdd(szuKacz::Acts::CriterionMenu, szuKacz::Acts::CriterionMenuSurname, ACTT_CHECK, "Nazwisko");
				UIActionAdd(szuKacz::Acts::CriterionMenu, szuKacz::Acts::CriterionMenuNick, ACTT_CHECK, "Ksywka");
			}

			UIGroupAdd(0, szuKacz::Acts::MethodMenu, ACTR_INIT, "Menu sposobu");
			{
				UIActionAdd(szuKacz::Acts::MethodMenu, szuKacz::Acts::MethodMenuCaseSensitive, ACTT_CHECK, "Uwzglêdniaj wielkoœæ liter");
				UIActionAdd(szuKacz::Acts::MethodMenu, 0, ACTT_SEP);
				UIActionAdd(szuKacz::Acts::MethodMenu, szuKacz::Acts::MethodMenuContains, ACTT_CHECK, "Zawiera");
				UIActionAdd(szuKacz::Acts::MethodMenu, szuKacz::Acts::MethodMenuEqual, ACTT_CHECK, "Równe");
				UIActionAdd(szuKacz::Acts::MethodMenu, szuKacz::Acts::MethodMenuNotEqual, ACTT_CHECK, "Ró¿ne od");
				UIActionAdd(szuKacz::Acts::MethodMenu, szuKacz::Acts::MethodMenuBegins, ACTT_CHECK, "Zaczyna siê od");
				UIActionAdd(szuKacz::Acts::MethodMenu, szuKacz::Acts::MethodMenuEnds, ACTT_CHECK, "Koñczy siê na");
				UIActionAdd(szuKacz::Acts::MethodMenu, szuKacz::Acts::MethodMenuNotContains, ACTT_CHECK, "Nie zawiera");
				UIActionAdd(szuKacz::Acts::MethodMenu, szuKacz::Acts::MethodMenuPreg, ACTT_CHECK, "Wyra¿enie regularne");
			}
		}

		//jeœli jest k.Lawa to dodajemy siê do "Dodatkowych akcji k.Lawy"
		if(szuKacz::PluginExists(301))
		{
			UIActionAdd(301100, szuKacz::Acts::QuickSearchPrevious, 0, "Poprzedni wynik szuKacza", szuKacz::Icons::Previous);
			UIActionAdd(301100, szuKacz::Acts::QuickSearchNext, 0, "Nastêpny wynik szuKacza", szuKacz::Icons::Next);
		}

		//przygotowujemy sobie na póŸniej uchwyty do okien K
		{
			szuKacz::KonnektMainWindow = (HWND)UIGroupHandle(sUIAction(0, IMIG_MAINWND));
			szuKacz::CNTListWindow = GetDlgItem(szuKacz::KonnektMainWindow, 1000);
		}

		//tworzymy toolbar szybkiego wyszukiwania
		{
			szuKacz::QuickSearchToolbar = CreateWindowEx(WS_EX_PALETTEWINDOW, TOOLBARCLASSNAME, "", WS_POPUP|TBSTYLE_TOOLTIPS|TBSTYLE_TRANSPARENT|TBSTYLE_FLAT|CCS_NORESIZE|CCS_NODIVIDER|CCS_NOPARENTALIGN, 0, 0, 0, 0, szuKacz::KonnektMainWindow, 0, Ctrl->hInst(), 0);

			SendMessage(szuKacz::QuickSearchToolbar, TB_SETBITMAPSIZE, 0, MAKELONG(16, 16));
			SendMessage(szuKacz::QuickSearchToolbar, TB_SETIMAGELIST, 0, (LPARAM)(HIMAGELIST)Ctrl->ICMessage(IMI_GETICONLIST, IML_16));

			//dodajemy przyciski
			{
				TBBUTTON buttons[4];
				buttons[0].iBitmap = Ctrl->ICMessage(IMI_GETICONINDEX, szuKacz::Icons::Criterion, IML_16);
				buttons[0].idCommand = 1;
				buttons[0].fsState = TBSTATE_ENABLED;
				buttons[0].fsStyle = TBSTYLE_DROPDOWN|BTNS_AUTOSIZE;
				buttons[0].iString = (int)"Kryterium";
				buttons[1].iBitmap = Ctrl->ICMessage(IMI_GETICONINDEX, szuKacz::Icons::Method, IML_16);
				buttons[1].idCommand = 2;
				buttons[1].fsState = TBSTATE_ENABLED;
				buttons[1].fsStyle = TBSTYLE_DROPDOWN|BTNS_AUTOSIZE;
				buttons[1].iString = (int)"Sposób";
				buttons[2].iBitmap = Ctrl->ICMessage(IMI_GETICONINDEX, szuKacz::Icons::Previous, IML_16);
				buttons[2].idCommand = 3;
				buttons[2].fsState = TBSTATE_ENABLED;
				buttons[2].fsStyle = TBSTYLE_BUTTON|BTNS_AUTOSIZE;
				buttons[2].iString = (int)"Poprzedni";
				buttons[3].iBitmap = Ctrl->ICMessage(IMI_GETICONINDEX, szuKacz::Icons::Next, IML_16);
				buttons[3].idCommand = 4;
				buttons[3].fsState = TBSTATE_ENABLED;
				buttons[3].fsStyle = TBSTYLE_BUTTON|BTNS_AUTOSIZE;
				buttons[3].iString = (int)"Nastêpny";
				SendMessage(szuKacz::QuickSearchToolbar, TB_ADDBUTTONS, 4, (LPARAM)&buttons);
				SendMessage(szuKacz::QuickSearchToolbar, TB_SETMAXTEXTROWS, 0, 0);
			}

			szuKacz::QuickSearchEdit = CreateWindowEx(WS_EX_CLIENTEDGE, WC_EDIT, 0, WS_CHILD, 0, 0, 0, 0, szuKacz::QuickSearchToolbar, 0, Ctrl->hInst(), 0);

			//ustawiamy czcionkê
			{
				HFONT font = CreateFont(-11, 0, 0, 0, 0, 0, 0, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, "Tahoma");
				SendMessage(szuKacz::QuickSearchEdit, WM_SETFONT, (WPARAM)font, 0);
			}

			szuKacz::QuickSearchToolbarVisible = 0;

			//subclassujemy g³ówne okno programu, …
			szuKacz::old_main_wnd_proc = (WNDPROC)SetWindowLongPtr(szuKacz::KonnektMainWindow, GWLP_WNDPROC, (LONG_PTR)szuKacz::KonnektMainWindowProc);

			//…toolbar szybkiego wyszukiwania…
			szuKacz::QuickSearchToolbarOldProc = (WNDPROC)SetWindowLongPtr(szuKacz::QuickSearchToolbar, GWLP_WNDPROC, (LONG_PTR)szuKacz::QuickSearchToolbarProc);
		
			//…i edit szybkiego wyszukiwnia
			szuKacz::QuickSearchEditOldProc = (WNDPROC)SetWindowLongPtr(szuKacz::QuickSearchEdit, GWLP_WNDPROC, (LONG_PTR)szuKacz::QuickSearchEditProc);
		}

		return 1;
	}

	int ActionProc(sUIActionNotify_base* anBase)
	{
		switch (anBase->act.id)
		{
			case szuKacz::Acts::Group:
			{
				switch (GETINT(szuKacz::Config::DefaultAction))
				{
					case 0:
					{
						CallAction(szuKacz::Acts::Group, szuKacz::Acts::Search);
						break;
					}
					case 1:
					{
						CallAction(szuKacz::Acts::Group, szuKacz::Acts::QuickSearch);
						break;
					}
				}
				break;
			}
			case szuKacz::Acts::Search:
			{
				if(anBase->code == ACTN_ACTION)
				{
					IMLOG("[ActionProc]: anBase->act.id = szuKacz::Acts::Search, anBase->code = ACTN_ACTION");

					szuKacz::Window();
				}
				break;
			}
			case szuKacz::Acts::QuickSearch:
			{
				if(anBase->code == ACTN_ACTION)
				{
					IMLOG("[ActionProc]: anBase->act.id = szuKacz::Acts::QuickSearch, anBase->code = ACTN_ACTION");

					if(!szuKacz::QuickSearchToolbarVisible)
					{
						ShowWindow(szuKacz::QuickSearchToolbar, SW_SHOWNORMAL);
						ShowWindow(szuKacz::QuickSearchEdit, SW_SHOWNORMAL);

						RECT rc1;
						GetWindowRect(szuKacz::CNTListWindow, &rc1);
						int ToolbarWidth = rc1.right - rc1.left - ((GetWindowLong(szuKacz::CNTListWindow, GWL_STYLE) & WS_VSCROLL) ? GetSystemMetrics(SM_CXVSCROLL) : 0);
						MoveWindow(szuKacz::QuickSearchToolbar, rc1.left, rc1.bottom - 22 - ((GetWindowLong(szuKacz::CNTListWindow, GWL_STYLE) & WS_HSCROLL) ? GetSystemMetrics(SM_CXHSCROLL) : 0), ToolbarWidth, 22, 1);
						int width = LOWORD(SendMessage(szuKacz::QuickSearchToolbar, TB_GETBUTTONSIZE, 0, 0));
						SendMessage(szuKacz::QuickSearchToolbar, TB_SETINDENT, ToolbarWidth - (4 * width), 0);
						MoveWindow(szuKacz::QuickSearchEdit, 0, 1, ToolbarWidth - (4 * width), 20, 1);

						SetFocus(szuKacz::QuickSearchEdit);
						SendMessage(szuKacz::QuickSearchEdit, EM_SETSEL, 0, -1);

						szuKacz::QuickSearchToolbarVisible = 1;
					}
					else
					{
						ShowWindow(szuKacz::QuickSearchEdit, SW_HIDE);
						ShowWindow(szuKacz::QuickSearchToolbar, SW_HIDE);

						szuKacz::QuickSearchToolbarVisible = 0;
					}
				}
				break;
			}
			case szuKacz::Acts::CriterionMenu:
			{
				if(anBase->code == ACTN_CREATEGROUP)
				{
					int temp = GETINT(szuKacz::Config::Criterion);
					UIActionSetStatus(sUIAction(szuKacz::Acts::CriterionMenu, szuKacz::Acts::CriterionMenuStatusInfo), temp == 0 ? ACTS_CHECKED : 0);
					UIActionSetStatus(sUIAction(szuKacz::Acts::CriterionMenu, szuKacz::Acts::CriterionMenuUID), temp == 1 ? ACTS_CHECKED : 0);
					UIActionSetStatus(sUIAction(szuKacz::Acts::CriterionMenu, szuKacz::Acts::CriterionMenuDisplay), temp == 2 ? ACTS_CHECKED : 0);
					UIActionSetStatus(sUIAction(szuKacz::Acts::CriterionMenu, szuKacz::Acts::CriterionMenuCellPhone), temp == 3 ? ACTS_CHECKED : 0);
					UIActionSetStatus(sUIAction(szuKacz::Acts::CriterionMenu, szuKacz::Acts::CriterionMenuHost), temp == 4 ? ACTS_CHECKED : 0);
					UIActionSetStatus(sUIAction(szuKacz::Acts::CriterionMenu, szuKacz::Acts::CriterionMenuLocality), temp == 5 ? ACTS_CHECKED : 0);
					UIActionSetStatus(sUIAction(szuKacz::Acts::CriterionMenu, szuKacz::Acts::CriterionMenuName), temp == 6 ? ACTS_CHECKED : 0);
					UIActionSetStatus(sUIAction(szuKacz::Acts::CriterionMenu, szuKacz::Acts::CriterionMenuSurname), temp == 7 ? ACTS_CHECKED : 0);
					UIActionSetStatus(sUIAction(szuKacz::Acts::CriterionMenu, szuKacz::Acts::CriterionMenuNick), temp == 8 ? ACTS_CHECKED : 0);
				}
				break;
			}
			case szuKacz::Acts::CriterionMenuStatusInfo:
			case szuKacz::Acts::CriterionMenuUID:
			case szuKacz::Acts::CriterionMenuDisplay:
			case szuKacz::Acts::CriterionMenuCellPhone:
			case szuKacz::Acts::CriterionMenuHost:
			case szuKacz::Acts::CriterionMenuLocality:
			case szuKacz::Acts::CriterionMenuName:
			case szuKacz::Acts::CriterionMenuSurname:
			case szuKacz::Acts::CriterionMenuNick:
			{
				if(anBase->code == ACTN_ACTION)
				{
					SETINT(szuKacz::Config::Criterion, anBase->act.id == szuKacz::Acts::CriterionMenuStatusInfo ? 0 :
						anBase->act.id == szuKacz::Acts::CriterionMenuUID ? 1 :
						anBase->act.id == szuKacz::Acts::CriterionMenuDisplay ? 2 :
						anBase->act.id == szuKacz::Acts::CriterionMenuCellPhone ? 3 :
						anBase->act.id == szuKacz::Acts::CriterionMenuHost ? 4 :
						anBase->act.id == szuKacz::Acts::CriterionMenuLocality ? 5 :
						anBase->act.id == szuKacz::Acts::CriterionMenuName ? 6 :
						anBase->act.id == szuKacz::Acts::CriterionMenuSurname ? 7 :
						anBase->act.id == szuKacz::Acts::CriterionMenuNick ? 8 : 0
					);

					SendMessage(szuKacz::KonnektMainWindow, WM_COMMAND, MAKELPARAM(0, EN_CHANGE), (LPARAM)szuKacz::QuickSearchEdit);
				}
				break;
			}
			case szuKacz::Acts::MethodMenu:
			{
				if(anBase->code == ACTN_CREATEGROUP)
				{
					UIActionSetStatus(sUIAction(szuKacz::Acts::MethodMenu, szuKacz::Acts::MethodMenuCaseSensitive), GETINT(szuKacz::Config::CaseSensitive) == 1 ? ACTS_CHECKED : 0);
					int temp = GETINT(szuKacz::Config::Method);
					UIActionSetStatus(sUIAction(szuKacz::Acts::MethodMenu, szuKacz::Acts::MethodMenuContains), temp == 0 ? ACTS_CHECKED : 0);
					UIActionSetStatus(sUIAction(szuKacz::Acts::MethodMenu, szuKacz::Acts::MethodMenuEqual), temp == 1 ? ACTS_CHECKED : 0);
					UIActionSetStatus(sUIAction(szuKacz::Acts::MethodMenu, szuKacz::Acts::MethodMenuNotEqual), temp == 2 ? ACTS_CHECKED : 0);
					UIActionSetStatus(sUIAction(szuKacz::Acts::MethodMenu, szuKacz::Acts::MethodMenuBegins), temp == 3 ? ACTS_CHECKED : 0);
					UIActionSetStatus(sUIAction(szuKacz::Acts::MethodMenu, szuKacz::Acts::MethodMenuEnds), temp == 4 ? ACTS_CHECKED : 0);
					UIActionSetStatus(sUIAction(szuKacz::Acts::MethodMenu, szuKacz::Acts::MethodMenuNotContains), temp == 5 ? ACTS_CHECKED : 0);
					UIActionSetStatus(sUIAction(szuKacz::Acts::MethodMenu, szuKacz::Acts::MethodMenuPreg), temp == 6 ? ACTS_CHECKED : 0);
				}
				break;
			}
			case szuKacz::Acts::MethodMenuCaseSensitive:
			{
				SETINT(szuKacz::Config::CaseSensitive, !GETINT(szuKacz::Config::CaseSensitive));
				break;
			}
			case szuKacz::Acts::MethodMenuContains:
			case szuKacz::Acts::MethodMenuEqual:
			case szuKacz::Acts::MethodMenuNotEqual:
			case szuKacz::Acts::MethodMenuBegins:
			case szuKacz::Acts::MethodMenuEnds:
			case szuKacz::Acts::MethodMenuNotContains:
			case szuKacz::Acts::MethodMenuPreg:
			{
				if(anBase->code == ACTN_ACTION)
				{
					SETINT(szuKacz::Config::Method, anBase->act.id == szuKacz::Acts::MethodMenuContains ? 0 :
						anBase->act.id == szuKacz::Acts::MethodMenuEqual ? 1 :
						anBase->act.id == szuKacz::Acts::MethodMenuNotEqual ? 2 :
						anBase->act.id == szuKacz::Acts::MethodMenuBegins ? 3 :
						anBase->act.id == szuKacz::Acts::MethodMenuEnds ? 4 :
						anBase->act.id == szuKacz::Acts::MethodMenuNotContains ? 5 :
						anBase->act.id == szuKacz::Acts::MethodMenuPreg ? 6 : 0
					);

					SendMessage(szuKacz::KonnektMainWindow, WM_COMMAND, MAKELPARAM(0, EN_CHANGE), (LPARAM)szuKacz::QuickSearchEdit);
				}
				break;
			}
			case szuKacz::Acts::QuickSearchPrevious:
			{
				if(anBase->code == ACTN_ACTION)
				{
					SendMessage(szuKacz::KonnektMainWindow, WM_COMMAND, MAKELPARAM(3, 0), (LPARAM)szuKacz::QuickSearchToolbar);
					break;
				}
			}
			case szuKacz::Acts::QuickSearchNext:
			{
				if(anBase->code == ACTN_ACTION)
				{
					SendMessage(szuKacz::KonnektMainWindow, WM_COMMAND, MAKELPARAM(4, 0), (LPARAM)szuKacz::QuickSearchToolbar);
					break;
				}
			}
		}
		return 0;
	}
}



int __stdcall IMessageProc(sIMessage_base * msgBase)
{
    sIMessage_2params * msg = (msgBase->s_size>=sizeof(sIMessage_2params))?static_cast<sIMessage_2params*>(msgBase):0;
    switch(msgBase->id)
	{
		case IM_PLUG_NET: return szuKacz::Net;
		case IM_PLUG_TYPE: return IMT_UI|IMT_CONFIG;
		case IM_PLUG_VERSION: return 0;
		case IM_PLUG_SDKVERSION: return KONNEKT_SDK_V;
		case IM_PLUG_SIG: return (int)szuKacz::Sig;
		case IM_PLUG_NAME: return (int)szuKacz::Name;
		case IM_PLUG_NETNAME: return 0;
		case IM_PLUG_INIT: Plug_Init(msg->p1, msg->p2); return 1;
		case IM_PLUG_DEINIT: Plug_Deinit(msg->p1, msg->p2); return 1;
		case IM_SETCOLS: return szuKacz::ISetCols();
		case IM_UI_PREPARE: return szuKacz::IPrepare();
		case IM_START: return szuKacz::IStart();
		case IM_END: return szuKacz::IEnd();
		case IM_UIACTION: return szuKacz::ActionProc((sUIActionNotify_base*)msg->p1);
	}

	if(Ctrl)
		Ctrl->setError(IMERROR_NORESULT);
	return 0;
}