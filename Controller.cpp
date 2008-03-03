/*
 * License - http://www.gnu.org/licenses/lgpl.txt
 */

#include "StdAfx.h"
#include "Includes.h"

namespace SzuKacz
{
	SharedPtr<Controller> Controller::instance = 0;

	Controller::Controller()
	{
		this->config = new CfgController(this);

		this->setStaticValue(IM_PLUG_TYPE, IMT_UI|IMT_CONFIG);
		this->setStaticValue(IM_PLUG_PRIORITY, PLUGP_STANDARD);
		this->setStaticValue(IM_PLUG_NAME, SzuKacz::name);
		this->setStaticValue(IM_PLUG_SIG, SzuKacz::sig);
		this->setStaticValue(IM_PLUG_NET, SzuKacz::net);

		this->registerObserver(IM_UI_PREPARE, bind(resolve_cast0(&Controller::onPrepare), this));
		this->registerObserver(IM_UIACTION, bind(resolve_cast0(&Controller::onAction), this));

		config->setColumn(DTCFG, SzuKacz::CFG::windowPosX, DT_CT_INT, (GetSystemMetrics(SM_CXSCREEN) / 2) - ((180-(GetSystemMetrics(SM_CXFIXEDFRAME) * 2)) / 2), "SzuKacz/Config/WindowX");
		config->setColumn(DTCFG, SzuKacz::CFG::windowPosY, DT_CT_INT, (GetSystemMetrics(SM_CYSCREEN) / 2) - ((120 - (GetSystemMetrics(SM_CYFIXEDFRAME) * 2) + GetSystemMetrics (SM_CYCAPTION)) / 2), "SzuKacz/Config/WindowY");
		config->setColumn(DTCFG, SzuKacz::CFG::windowWidth, DT_CT_INT, 500 + GetSystemMetrics(SM_CXFIXEDFRAME) * 2, "SzuKacz/Config/WindowWidth");
		config->setColumn(DTCFG, SzuKacz::CFG::windowHeight, DT_CT_INT, 300 + GetSystemMetrics(SM_CYFIXEDFRAME) * 2 + GetSystemMetrics(SM_CYCAPTION), "SzuKacz/Config/WindowHeight");
		config->setColumn(DTCFG, SzuKacz::CFG::selectedMethod, DT_CT_INT, 0, "SzuKacz/Config/ComboBox1");
		config->setColumn(DTCFG, SzuKacz::CFG::selectedCriterion, DT_CT_INT, 2, "SzuKacz/Config/ComboBox2");
		config->setColumn(DTCFG, SzuKacz::CFG::selectedCaseSensitive, DT_CT_INT, 0, "SzuKacz/Config/CheckBox");
		config->setColumn(DTCFG, SzuKacz::CFG::column0Width, DT_CT_INT, 100, "SzuKacz/Config/ListBoxColumn0");
		config->setColumn(DTCFG, SzuKacz::CFG::column1Width, DT_CT_INT, 200, "SzuKacz/Config/ListBoxColumn1");
		config->setColumn(DTCFG, SzuKacz::CFG::buttonPosition, DT_CT_INT, 0, "SzuKacz/ButtonPosition");
		config->setColumn(DTCFG, SzuKacz::CFG::mruSize, DT_CT_INT, 5, "SzuKacz/MRUSize");
		config->setColumn(DTCFG, SzuKacz::CFG::quickSearchSelectedCriterion, DT_CT_INT, 2, "SzuKacz/Criterion");
		config->setColumn(DTCFG, SzuKacz::CFG::quickSearchSelectedMethod, DT_CT_INT, 0, "SzuKacz/Method");
		config->setColumn(DTCFG, SzuKacz::CFG::quickSearchSelectedCaseSensitive, DT_CT_INT, 0, "SzuKacz/CaseSensitive");
		config->setColumn(DTCFG, SzuKacz::CFG::toolbarAction, DT_CT_INT, 0, "SzuKacz/ToolbarAction");
		config->setColumn(DTCFG, SzuKacz::CFG::quickSearchEnterAction, DT_CT_INT, 0, "SzuKacz/EnterAction");
		config->setColumn(DTCFG, SzuKacz::CFG::quickSearchCtrlEnterAction, DT_CT_INT, 1, "SzuKacz/CtrlEnterAction");

		this->quickSearchToolbarVisible = 0;
		this->quickSearchToolbarMoved = 0;
		this->currentQuickSearchResult = 0;
	}

	void Controller::onPrepare()
	{
		//ustawiamy locale (dla wszelkich sortowañ - u¿ywamy _stricoll)
		setlocale(LC_ALL, "Polish");

		//przygotowujemy klasê do obs³ugi MRU
		this->mruList = new MRU("SzuKacz", SzuKacz::CFG::mruSize, 1);

		//rejestrujemy ikonki
		{
			IconRegister(IML_16, SzuKacz::ICO::szuKacz16, SzuKacz::RES::szuKacz16);
			IconRegister(IML_32, SzuKacz::ICO::szuKacz32, SzuKacz::RES::szuKacz32);
			IconRegister(IML_16, SzuKacz::ICO::previous, SzuKacz::RES::previous);
			IconRegister(IML_16, SzuKacz::ICO::next, SzuKacz::RES::next);
			IconRegister(IML_16, SzuKacz::ICO::criterion, SzuKacz::RES::criterion);
			IconRegister(IML_16, SzuKacz::ICO::method, SzuKacz::RES::method);
		}

		//przycisk
		switch(GETINT(SzuKacz::CFG::buttonPosition))
		{
			case 0:
			{
				UIGroupAdd(IMIG_MAIN_CNT, SzuKacz::ACT::groupButton, 0, "Szukaj na liœcie", SzuKacz::ICO::szuKacz16);
				break;
			}
			case 1:
			{
				UIGroupAdd(Ctrl->IMessage(IMI_GETPLUGINSGROUP, 0, 0), SzuKacz::ACT::groupButton, 0, "Szukaj na liœcie", SzuKacz::ICO::szuKacz16);
				break;
			}
			case 2:
			{
				UIGroupAdd(IMIG_MAINTB, SzuKacz::ACT::groupButton, 0, "Szukaj na liœcie", SzuKacz::ICO::szuKacz16);
				break;
			}
		}

		UIActionAdd(SzuKacz::ACT::groupButton, SzuKacz::ACT::search, 0, "Okienko wyszukiwania", SzuKacz::ICO::szuKacz16);
		UIActionAdd(SzuKacz::ACT::groupButton, SzuKacz::ACT::quickSearch, 0, "Szybkie wyszukiwanie", SzuKacz::ICO::szuKacz16);

		UIGroupAdd(IMIG_CFG_PLUGS, SzuKacz::CFG::group, 0, "SzuKacz", SzuKacz::ICO::szuKacz16);
		{
			UIActionCfgAddPluginInfoBox2(SzuKacz::CFG::group, "Wtyczka pozwala na szybkie przeszukiwanie listy kontaktów wed³ug ró¿nych kryteriów.", "<span class='note'>Skompilowano: <b>"__DATE__"</b> [<b>"__TIME__"</b>]</span><br/><br/>Copyright © 2004-2006 <b>Skolima</b><br/>Copyright © 2006 <b>Micha³ \"Dulek\" Dulko</b>", (char*)SzuKacz::RES::szuKacz32);

			if(Konnekt::ShowBits::checkLevel(Konnekt::ShowBits::levelIntermediate))
			{
				UIActionAdd(SzuKacz::CFG::group, 0, ACTT_GROUP, "Akcje");
				{
					UIActionAdd(SzuKacz::CFG::group, 0, ACTT_COMMENT|ACTSC_INLINE, "Przycisku na toolbarze:", 0, 180);
					UIActionAdd(SzuKacz::CFG::group, SzuKacz::CFG::toolbarAction, ACTT_COMBO|ACTSCOMBO_LIST|ACTSCOMBO_BYPOS, "Okienko wyszukiwania" CFGICO "512200" "\nSzybkie wyszukiwanie" CFGICO "512200", SzuKacz::CFG::toolbarAction, 200);
					UIActionAdd(SzuKacz::CFG::group, 0, ACTT_COMMENT|ACTSC_INLINE, "Enter w szybkim wyszukiwaniu:", 0, 180);
					UIActionAdd(SzuKacz::CFG::group, SzuKacz::CFG::quickSearchEnterAction, ACTT_COMBO|ACTSCOMBO_LIST|ACTSCOMBO_BYPOS, "Brak akcji" "\nOtwórz okno rozmowy" CFGICO "1342177296" "\nOtwórz okno w³aœciwoœci" CFGICO "30" "\nZamknij szybkie wyszukiwanie" CFGICO "46", SzuKacz::CFG::quickSearchEnterAction, 200);
					UIActionAdd(SzuKacz::CFG::group, 0, ACTT_COMMENT|ACTSC_INLINE, "Ctrl+Enter w szybkim wyszukiwaniu:", 0, 180);
					UIActionAdd(SzuKacz::CFG::group, SzuKacz::CFG::quickSearchCtrlEnterAction, ACTT_COMBO|ACTSCOMBO_LIST|ACTSCOMBO_BYPOS, "Brak akcji" "\nOtwórz okno rozmowy" CFGICO "1342177296" "\nOtwórz okno w³aœciwoœci" CFGICO "30" "\nZamknij szybkie wyszukiwanie" CFGICO "46", SzuKacz::CFG::quickSearchCtrlEnterAction, 200);
				}
				UIActionCfgAdd(SzuKacz::CFG::group, 0, ACTT_GROUPEND);
				UIActionAdd(SzuKacz::CFG::group, 0, ACTT_GROUP, "Opcje");
				{
					UIActionAdd(SzuKacz::CFG::group, 0, ACTT_SEP, "Po³o¿enie przycisku");
					{
						UIActionAdd(SzuKacz::CFG::group, SzuKacz::ACT::buttonPositionContactMenu, ACTT_RADIO|ACTSC_NEEDRESTART|ACTSRADIO_BYPOS|ACTR_STATUS, "W menu kontaktów", SzuKacz::CFG::buttonPosition);
						UIActionAdd(SzuKacz::CFG::group, SzuKacz::ACT::buttonPositionPluginsMenu, ACTT_RADIO|ACTSC_NEEDRESTART|ACTSRADIO_BYPOS|ACTR_STATUS, "W menu wtyczek", SzuKacz::CFG::buttonPosition);
						UIActionAdd(SzuKacz::CFG::group, SzuKacz::ACT::buttonPositionMainToolbar, ACTT_RADIO|ACTSC_NEEDRESTART|ACTSRADIO_BYPOS|ACTR_STATUS|ACTSRADIO_LAST, "Na g³ównym toolbarze", SzuKacz::CFG::buttonPosition);
					}

				}
				UIActionCfgAdd(SzuKacz::CFG::group, 0, ACTT_GROUPEND);
			}
			if(Konnekt::ShowBits::checkLevel(Konnekt::ShowBits::levelNormal))
			{
				UIActionAdd(SzuKacz::CFG::group, 0, ACTT_GROUP, "Historia wyszukiwanych hase³");
				{
					UIActionAdd(SzuKacz::CFG::group, 0, ACTT_COMMENT, "Iloœæ pozycji w historii:");
					UIActionAdd(SzuKacz::CFG::group, 0, ACTT_SLIDER, "Ma³o\nDu¿o" AP_MINIMUM "0" AP_MAXIMUM "100", SzuKacz::CFG::mruSize);
					UIActionAdd(SzuKacz::CFG::group, 0, ACTT_SEPARATOR);
					UIActionAdd(SzuKacz::CFG::group, SzuKacz::ACT::clearMRU, ACTT_BUTTON, "Wyczyœæ" AP_ICO "50");
				}
				UIActionCfgAdd(SzuKacz::CFG::group, 0, ACTT_GROUPEND);
			}
		}

		//menu kontekstowe
		{
			UIGroupAdd(0, SzuKacz::ACT::criterionMenu, ACTR_INIT, "Menu kryterium");
			{
				UIActionAdd(SzuKacz::ACT::criterionMenu, SzuKacz::ACT::criterionMenuStatusInfo, ACTT_CHECK, "Opis");
				UIActionAdd(SzuKacz::ACT::criterionMenu, SzuKacz::ACT::criterionMenuUID, ACTT_CHECK, "UID");
				UIActionAdd(SzuKacz::ACT::criterionMenu, SzuKacz::ACT::criterionMenuDisplay, ACTT_CHECK, "Wyœwietl jako");
				UIActionAdd(SzuKacz::ACT::criterionMenu, SzuKacz::ACT::criterionMenuCellPhone, ACTT_CHECK, "Komórka");
				UIActionAdd(SzuKacz::ACT::criterionMenu, SzuKacz::ACT::criterionMenuHost, ACTT_CHECK, "IP");
				UIActionAdd(SzuKacz::ACT::criterionMenu, SzuKacz::ACT::criterionMenuLocality, ACTT_CHECK, "Miejscowoœæ");
				UIActionAdd(SzuKacz::ACT::criterionMenu, SzuKacz::ACT::criterionMenuName, ACTT_CHECK, "Imiê");
				UIActionAdd(SzuKacz::ACT::criterionMenu, SzuKacz::ACT::criterionMenuSurname, ACTT_CHECK, "Nazwisko");
				UIActionAdd(SzuKacz::ACT::criterionMenu, SzuKacz::ACT::criterionMenuNick, ACTT_CHECK, "Ksywka");
			}

			UIGroupAdd(0, SzuKacz::ACT::methodMenu, ACTR_INIT, "Menu sposobu");
			{
				UIActionAdd(SzuKacz::ACT::methodMenu, SzuKacz::ACT::methodMenuCaseSensitive, ACTT_CHECK, "Uwzglêdniaj wielkoœæ liter");
				UIActionAdd(SzuKacz::ACT::methodMenu, 0, ACTT_SEP);
				UIActionAdd(SzuKacz::ACT::methodMenu, SzuKacz::ACT::methodMenuContains, ACTT_CHECK, "Zawiera");
				UIActionAdd(SzuKacz::ACT::methodMenu, SzuKacz::ACT::methodMenuEqual, ACTT_CHECK, "Równe");
				UIActionAdd(SzuKacz::ACT::methodMenu, SzuKacz::ACT::methodMenuNotEqual, ACTT_CHECK, "Ró¿ne od");
				UIActionAdd(SzuKacz::ACT::methodMenu, SzuKacz::ACT::methodMenuBegins, ACTT_CHECK, "Zaczyna siê od");
				UIActionAdd(SzuKacz::ACT::methodMenu, SzuKacz::ACT::methodMenuEnds, ACTT_CHECK, "Koñczy siê na");
				UIActionAdd(SzuKacz::ACT::methodMenu, SzuKacz::ACT::methodMenuNotContains, ACTT_CHECK, "Nie zawiera");
				UIActionAdd(SzuKacz::ACT::methodMenu, SzuKacz::ACT::methodMenuPreg, ACTT_CHECK, "Wyra¿enie regularne");
			}
		}

		//jeœli jest k.Lawa to dodajemy siê do "Dodatkowych akcji k.Lawy"
		if(SzuKacz::pluginExists(301))
		{
			UIActionAdd(301100, SzuKacz::ACT::quickSearchPrevious, 0, "Poprzedni wynik SzuKacza", SzuKacz::ICO::previous);
			UIActionAdd(301100, SzuKacz::ACT::quickSearchNext, 0, "Nastêpny wynik SzuKacza", SzuKacz::ICO::next);
		}

		//przygotowujemy sobie na póŸniej uchwyty do okien K
		{
			this->konnektWindow = (HWND)UIGroupHandle(sUIAction(0, IMIG_MAINWND));
			this->konnektRoster = GetDlgItem(konnektWindow, 1000);
		}

		//tworzymy toolbar szybkiego wyszukiwania
		{
			this->quickSearchToolbar = CreateWindowEx(WS_EX_PALETTEWINDOW, TOOLBARCLASSNAME, "", WS_POPUP|TBSTYLE_TOOLTIPS|TBSTYLE_TRANSPARENT|TBSTYLE_FLAT|CCS_NORESIZE|CCS_NODIVIDER|CCS_NOPARENTALIGN, 0, 0, 0, 0, this->konnektWindow, 0, Ctrl->hInst(), 0);

			SendMessage(this->quickSearchToolbar, TB_SETBITMAPSIZE, 0, MAKELONG(16, 16));
			SendMessage(this->quickSearchToolbar, TB_SETIMAGELIST, 0, (LPARAM)(HIMAGELIST)Ctrl->ICMessage(IMI_GETICONLIST, IML_16));

			//dodajemy przyciski
			{
				TBBUTTON buttons[4];
				buttons[0].iBitmap = Ctrl->ICMessage(IMI_GETICONINDEX, SzuKacz::ICO::criterion, IML_16);
				buttons[0].idCommand = 1;
				buttons[0].fsState = TBSTATE_ENABLED;
				buttons[0].fsStyle = TBSTYLE_DROPDOWN|BTNS_AUTOSIZE;
				buttons[0].iString = (int)"Kryterium";
				buttons[1].iBitmap = Ctrl->ICMessage(IMI_GETICONINDEX, SzuKacz::ICO::method, IML_16);
				buttons[1].idCommand = 2;
				buttons[1].fsState = TBSTATE_ENABLED;
				buttons[1].fsStyle = TBSTYLE_DROPDOWN|BTNS_AUTOSIZE;
				buttons[1].iString = (int)"Sposób";
				buttons[2].iBitmap = Ctrl->ICMessage(IMI_GETICONINDEX, SzuKacz::ICO::previous, IML_16);
				buttons[2].idCommand = 3;
				buttons[2].fsState = TBSTATE_ENABLED;
				buttons[2].fsStyle = TBSTYLE_BUTTON|BTNS_AUTOSIZE;
				buttons[2].iString = (int)"Poprzedni";
				buttons[3].iBitmap = Ctrl->ICMessage(IMI_GETICONINDEX, SzuKacz::ICO::next, IML_16);
				buttons[3].idCommand = 4;
				buttons[3].fsState = TBSTATE_ENABLED;
				buttons[3].fsStyle = TBSTYLE_BUTTON|BTNS_AUTOSIZE;
				buttons[3].iString = (int)"Nastêpny";
				SendMessage(this->quickSearchToolbar, TB_ADDBUTTONS, 4, (LPARAM)&buttons);
				SendMessage(this->quickSearchToolbar, TB_SETMAXTEXTROWS, 0, 0);
			}

			this->quickSearchEdit = CreateWindowEx(WS_EX_CLIENTEDGE, WC_EDIT, 0, WS_CHILD|ES_AUTOHSCROLL, 0, 0, 0, 0, this->quickSearchToolbar, 0, Ctrl->hInst(), 0);

			//ustawiamy czcionkê
			{
				HFONT font = CreateFont(-11, 0, 0, 0, 0, 0, 0, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, "Tahoma");
				SendMessage(this->quickSearchEdit, WM_SETFONT, (WPARAM)font, 0);
			}
		}

		//subclassujemy kilka okien…
		{
			//…g³ówne okno K, …
			this->konnektWindowOldProc = (WNDPROC)SetWindowLongPtr(this->konnektWindow, GWLP_WNDPROC, (LONG_PTR)SzuKacz::konnektMainWindowProc);

			//…toolbar szybkiego wyszukiwania…
			this->quickSearchToolbarOldProc = (WNDPROC)SetWindowLongPtr(this->quickSearchToolbar, GWLP_WNDPROC, (LONG_PTR)SzuKacz::quickSearchToolbarProc);
		
			//…i edit szybkiego wyszukiwnia
			this->quickSearchEditOldProc = (WNDPROC)SetWindowLongPtr(this->quickSearchEdit, GWLP_WNDPROC, (LONG_PTR)SzuKacz::quickSearchEditProc);
		}

		//okienko wyszukiwania
		{
			//rejestrujemy klasê okna
			{
				WNDCLASSEX window_class;
				window_class.style = CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS;
				window_class.lpfnWndProc = SzuKacz::searchWindowProc;
				window_class.cbClsExtra = 0;
				window_class.cbWndExtra = 0;
				window_class.hInstance = Ctrl->hInst();
				window_class.hCursor = LoadCursor(0, IDC_ARROW);
				window_class.lpszMenuName = 0;
				window_class.lpszClassName = "SzuKaczSearchWindow";
				window_class.hbrBackground = GetSysColorBrush(COLOR_BTNFACE);
				window_class.hIcon = (HICON)Ctrl->ICMessage(IMI_ICONGET, SzuKacz::ICO::szuKacz32, IML_32);
				window_class.hIconSm = (HICON)Ctrl->ICMessage(IMI_ICONGET, SzuKacz::ICO::szuKacz16, IML_16);
				window_class.cbSize = sizeof(window_class);
				RegisterClassEx(&window_class);
			}
		}
	}

	void Controller::onEnd()
	{
		//usuwamy obiekt do obs³ugi MRU
		if(this->mruList)
		{
			delete this->mruList;
			this->mruList = 0;
		}

		//usuwamy wskaŸnik na aktualny wynik
		if(this->currentQuickSearchResult)
		{
			delete this->currentQuickSearchResult;
			this->currentQuickSearchResult = 0;
		}

		//niszczymy okna
		{
			if(this->searchWindow)
			{
				DestroyWindow(this->searchWindow);
				this->searchWindow = 0;
			}

			if(this->quickSearchToolbar)
			{
				DestroyWindow(this->quickSearchToolbar);
				this->quickSearchToolbar = 0;
			}

			if(this->quickSearchEdit)
			{
				DestroyWindow(this->quickSearchEdit);
				this->quickSearchEdit = 0;
			}
		}

		//wyrejestrowujemy klasê okna
		UnregisterClass("SzuKaczSearchWindow", Ctrl->hInst());
	}

	void Controller::onAction()
	{
		sUIActionNotify_2params* an = this->getAN();

		switch(an->act.id)
		{
			case SzuKacz::ACT::groupButton:
			{
				switch (GETINT(SzuKacz::CFG::toolbarAction))
				{
					case 0:
					{
						SzuKacz::callAction(SzuKacz::ACT::groupButton, SzuKacz::ACT::search);
						break;
					}
					case 1:
					{
						SzuKacz::callAction(SzuKacz::ACT::groupButton, SzuKacz::ACT::quickSearch);
						break;
					}
				}
				break;
			}
			case SzuKacz::ACT::search:
			{
				if(an->code == ACTN_ACTION)
				{
					IMLOG("[ActionProc]: an->act.id = SzuKacz::ACT::search, an->code = ACTN_ACTION");

					this->openSearchWindow();
				}
				break;
			}
			case SzuKacz::ACT::quickSearch:
			{
				if(an->code == ACTN_ACTION)
				{
					IMLOG("[ActionProc]: an->act.id = SzuKacz::ACT::quickSearch, an->code = ACTN_ACTION");

					if(!this->quickSearchToolbarVisible)
					{
						ShowWindow(this->quickSearchToolbar, SW_SHOWNORMAL);
						ShowWindow(this->quickSearchEdit, SW_SHOWNORMAL);

						this->quickSearchToolbarRefresh(this->quickSearchToolbarMoved);

						SetFocus(this->quickSearchEdit);
						SendMessage(this->quickSearchEdit, EM_SETSEL, 0, -1);

						this->quickSearchToolbarVisible = 1;
					}
					else
					{
						this->quickSearchToolbarHide();
					}
				}
				break;
			}
			case SzuKacz::ACT::criterionMenu:
			{
				if(an->code == ACTN_CREATEGROUP)
				{
					int temp = GETINT(SzuKacz::CFG::quickSearchSelectedCriterion);
					UIActionSetStatus(sUIAction(SzuKacz::ACT::criterionMenu, SzuKacz::ACT::criterionMenuStatusInfo), temp == 0 ? ACTS_CHECKED : 0);
					UIActionSetStatus(sUIAction(SzuKacz::ACT::criterionMenu, SzuKacz::ACT::criterionMenuUID), temp == 1 ? ACTS_CHECKED : 0);
					UIActionSetStatus(sUIAction(SzuKacz::ACT::criterionMenu, SzuKacz::ACT::criterionMenuDisplay), temp == 2 ? ACTS_CHECKED : 0);
					UIActionSetStatus(sUIAction(SzuKacz::ACT::criterionMenu, SzuKacz::ACT::criterionMenuCellPhone), temp == 3 ? ACTS_CHECKED : 0);
					UIActionSetStatus(sUIAction(SzuKacz::ACT::criterionMenu, SzuKacz::ACT::criterionMenuHost), temp == 4 ? ACTS_CHECKED : 0);
					UIActionSetStatus(sUIAction(SzuKacz::ACT::criterionMenu, SzuKacz::ACT::criterionMenuLocality), temp == 5 ? ACTS_CHECKED : 0);
					UIActionSetStatus(sUIAction(SzuKacz::ACT::criterionMenu, SzuKacz::ACT::criterionMenuName), temp == 6 ? ACTS_CHECKED : 0);
					UIActionSetStatus(sUIAction(SzuKacz::ACT::criterionMenu, SzuKacz::ACT::criterionMenuSurname), temp == 7 ? ACTS_CHECKED : 0);
					UIActionSetStatus(sUIAction(SzuKacz::ACT::criterionMenu, SzuKacz::ACT::criterionMenuNick), temp == 8 ? ACTS_CHECKED : 0);
				}
				break;
			}
			case SzuKacz::ACT::criterionMenuStatusInfo:
			case SzuKacz::ACT::criterionMenuUID:
			case SzuKacz::ACT::criterionMenuDisplay:
			case SzuKacz::ACT::criterionMenuCellPhone:
			case SzuKacz::ACT::criterionMenuHost:
			case SzuKacz::ACT::criterionMenuLocality:
			case SzuKacz::ACT::criterionMenuName:
			case SzuKacz::ACT::criterionMenuSurname:
			case SzuKacz::ACT::criterionMenuNick:
			{
				if(an->code == ACTN_ACTION)
				{
					SETINT(SzuKacz::CFG::quickSearchSelectedCriterion, an->act.id == SzuKacz::ACT::criterionMenuStatusInfo ? 0 :
						an->act.id == SzuKacz::ACT::criterionMenuUID ? 1 :
						an->act.id == SzuKacz::ACT::criterionMenuDisplay ? 2 :
						an->act.id == SzuKacz::ACT::criterionMenuCellPhone ? 3 :
						an->act.id == SzuKacz::ACT::criterionMenuHost ? 4 :
						an->act.id == SzuKacz::ACT::criterionMenuLocality ? 5 :
						an->act.id == SzuKacz::ACT::criterionMenuName ? 6 :
						an->act.id == SzuKacz::ACT::criterionMenuSurname ? 7 :
						an->act.id == SzuKacz::ACT::criterionMenuNick ? 8 : 0
					);

					SendMessage(this->konnektWindow, WM_COMMAND, MAKELPARAM(0, EN_CHANGE), (LPARAM)this->quickSearchEdit);
				}
				break;
			}
			case SzuKacz::ACT::methodMenu:
			{
				if(an->code == ACTN_CREATEGROUP)
				{
					UIActionSetStatus(sUIAction(SzuKacz::ACT::methodMenu, SzuKacz::ACT::methodMenuCaseSensitive), GETINT(SzuKacz::CFG::quickSearchSelectedCaseSensitive) == 1 ? ACTS_CHECKED : 0);
					int temp = GETINT(SzuKacz::CFG::quickSearchSelectedMethod);
					UIActionSetStatus(sUIAction(SzuKacz::ACT::methodMenu, SzuKacz::ACT::methodMenuContains), temp == 0 ? ACTS_CHECKED : 0);
					UIActionSetStatus(sUIAction(SzuKacz::ACT::methodMenu, SzuKacz::ACT::methodMenuEqual), temp == 1 ? ACTS_CHECKED : 0);
					UIActionSetStatus(sUIAction(SzuKacz::ACT::methodMenu, SzuKacz::ACT::methodMenuNotEqual), temp == 2 ? ACTS_CHECKED : 0);
					UIActionSetStatus(sUIAction(SzuKacz::ACT::methodMenu, SzuKacz::ACT::methodMenuBegins), temp == 3 ? ACTS_CHECKED : 0);
					UIActionSetStatus(sUIAction(SzuKacz::ACT::methodMenu, SzuKacz::ACT::methodMenuEnds), temp == 4 ? ACTS_CHECKED : 0);
					UIActionSetStatus(sUIAction(SzuKacz::ACT::methodMenu, SzuKacz::ACT::methodMenuNotContains), temp == 5 ? ACTS_CHECKED : 0);
					UIActionSetStatus(sUIAction(SzuKacz::ACT::methodMenu, SzuKacz::ACT::methodMenuPreg), temp == 6 ? ACTS_CHECKED : 0);
				}
				break;
			}
			case SzuKacz::ACT::methodMenuCaseSensitive:
			{
				if(an->code == ACTN_ACTION)
					SETINT(SzuKacz::CFG::quickSearchSelectedCaseSensitive, !GETINT(SzuKacz::CFG::quickSearchSelectedCaseSensitive));
				break;
			}
			case SzuKacz::ACT::methodMenuContains:
			case SzuKacz::ACT::methodMenuEqual:
			case SzuKacz::ACT::methodMenuNotEqual:
			case SzuKacz::ACT::methodMenuBegins:
			case SzuKacz::ACT::methodMenuEnds:
			case SzuKacz::ACT::methodMenuNotContains:
			case SzuKacz::ACT::methodMenuPreg:
			{
				if(an->code == ACTN_ACTION)
				{
					SETINT(SzuKacz::CFG::quickSearchSelectedMethod, an->act.id == SzuKacz::ACT::methodMenuContains ? 0 :
						an->act.id == SzuKacz::ACT::methodMenuEqual ? 1 :
						an->act.id == SzuKacz::ACT::methodMenuNotEqual ? 2 :
						an->act.id == SzuKacz::ACT::methodMenuBegins ? 3 :
						an->act.id == SzuKacz::ACT::methodMenuEnds ? 4 :
						an->act.id == SzuKacz::ACT::methodMenuNotContains ? 5 :
						an->act.id == SzuKacz::ACT::methodMenuPreg ? 6 : 0
					);

					SendMessage(this->konnektWindow, WM_COMMAND, MAKELPARAM(0, EN_CHANGE), (LPARAM)this->quickSearchEdit);
				}
				break;
			}
			case SzuKacz::ACT::quickSearchPrevious:
			{
				if(an->code == ACTN_ACTION)
					SendMessage(this->konnektWindow, WM_COMMAND, MAKELPARAM(3, 0), (LPARAM)this->quickSearchToolbar);
				break;
			}
			case SzuKacz::ACT::quickSearchNext:
			{
				if(an->code == ACTN_ACTION)
					SendMessage(this->konnektWindow, WM_COMMAND, MAKELPARAM(4, 0), (LPARAM)this->quickSearchToolbar);
				break;
			}
			case SzuKacz::ACT::buttonPositionContactMenu:
			case SzuKacz::ACT::buttonPositionPluginsMenu:
			case SzuKacz::ACT::buttonPositionMainToolbar:
			{
				if((*UIActionCfgGetValue(sUIAction(SzuKacz::CFG::group, SzuKacz::ACT::buttonPositionPluginsMenu), 0, 0) == '1' && GETINT(188) != 15) || (*UIActionCfgGetValue(sUIAction(SzuKacz::CFG::group, SzuKacz::ACT::buttonPositionMainToolbar), 0, 0) == '2'))
					UIActionSetStatus(sUIAction(SzuKacz::CFG::group, SzuKacz::CFG::toolbarAction), 0, ACTS_DISABLED);
				else
					UIActionSetStatus(sUIAction(SzuKacz::CFG::group, SzuKacz::CFG::toolbarAction), -1, ACTS_DISABLED);
				break;
			}
		}
	}

	//funkcja przeszukuj¹ca listê kontaktów i zwracaj¹ca tablicê z wynikami
	SzuKacz::tResults Controller::findContact(int field, std::string &toMatch, int relationType, bool caseSensitive, bool fromList, bool save)
	{
		IMLOG("[findContact]: field = %i, toMatch = %s, relationType = %i, caseSensitive = %i, fromList = %i, save = %i", field, toMatch.c_str(), relationType, caseSensitive, fromList, save);
		
		SzuKacz::tResults results;

		//zapisujemy do MRU
		if(save)
			this->mruList->append(toMatch);

		//sprawdzamy, czy mamy uwa¿aæ na wielkoœæ znaków i jeœli tak lowercasujemy stringa
		if(!caseSensitive)
			transform(toMatch.begin(), toMatch.end(), toMatch.begin(), tolower);

		switch(field)
		{
			case 0: field = CNT_STATUSINFO; break;
			case 1: field = CNT_UID; break;
			case 2: field = CNT_DISPLAY; break;
			case 3: field = CNT_CELLPHONE; break;
			case 4: field = CNT_HOST; break;
			case 5: field = CNT_LOCALITY; break;
			case 6: field = CNT_NAME; break;
			case 7: field = CNT_SURNAME; break;
			case 8: field = CNT_NICK; break;
		}

		//blokujemy listê kontaktów
		Ctrl->DTlock(DTCNT, -1);

		if(fromList)
		{
			const int listCount = ListView_GetItemCount(this->konnektRoster);
			LVITEM lvi;
			lvi.iSubItem = 0;
			lvi.mask = LVIF_PARAM;
			int i;
			for(int i2 = 0; i2 < listCount; i2++)
			{
				lvi.iItem = i2;
				ListView_GetItem(this->konnektRoster, &lvi);
				i = GETCNTPOS(((sUICnt*)(lvi.lParam))->ID);

				std::string readResult = GETCNTC(i, field);
				
				//sprawdzamy, czy mamy uwa¿aæ na wielkoœæ znaków i jeœli tak lowercasujemy stringa
				if(!caseSensitive)
					transform(readResult.begin(), readResult.end(), readResult.begin(), tolower);

				switch (relationType)
				{
					case 0: //zawiera
					{
						if(readResult.find(toMatch) != std::string::npos)
							results.push_back(SzuKacz::Result(i, field));
						break;
					}
					case 1: //równe
					{
						if(readResult == toMatch)
							results.push_back(SzuKacz::Result(i, field));
						break;
					}
					case 2: //nie równe
					{
						if(readResult != toMatch)
							results.push_back(SzuKacz::Result(i, field));
						break;
					}
					case 3: //zaczyna siê od
					{
						if(readResult.find(toMatch) == 0)
							results.push_back(SzuKacz::Result(i, field));
						break;
					}
					case 4: //koñczy siê na
					{
						std::string::size_type end = readResult.size() - toMatch.size();
						if(readResult.rfind(toMatch) == end && readResult.rfind(toMatch) != std::string::npos)
							results.push_back(SzuKacz::Result(i, field));
						break;
					}
					case 5: //nie zawiera
					{
						if(readResult.find(toMatch) == std::string::npos)
							results.push_back(SzuKacz::Result(i, field));
						break;
					}
					case 6: //wyra¿enie regularne
					{
						try
						{
							boost::regex expression(toMatch, caseSensitive ? 0 : boost::regex::icase);
							if(boost::regex_search(readResult, expression))
								results.push_back(SzuKacz::Result(i, field));
							break;
						}
						catch(...)
						{
						}
					}
				}

			}
		}
		else
		{
			const int listCount = ICMessage(IMC_CNT_COUNT);
			for(int i = 1; i < listCount; i++)
			{
				std::string readResult = GETCNTC(i, field);

				//sprawdzamy, czy mamy uwa¿aæ na wielkoœæ znaków i jeœli tak lowercasujemy stringa
				if(!caseSensitive)
					transform(readResult.begin(), readResult.end(), readResult.begin(), tolower);

				switch (relationType)
				{
					case 0: //zawiera
					{
						if(readResult.find(toMatch) != std::string::npos)
							results.push_back(SzuKacz::Result(i, field));
						break;
					}
					case 1: //równe
					{
						if(readResult == toMatch)
							results.push_back(SzuKacz::Result(i, field));
						break;
					}
					case 2: //nie równe
					{
						if(readResult != toMatch)
							results.push_back(SzuKacz::Result(i, field));
						break;
					}
					case 3: //zaczyna siê od
					{
						if(readResult.find(toMatch) == 0)
							results.push_back(SzuKacz::Result(i, field));
						break;
					}
					case 4: //koñczy siê na
					{
						std::string::size_type end = readResult.size() - toMatch.size();
						if(readResult.rfind(toMatch) == end && readResult.rfind(toMatch) != std::string::npos)
							results.push_back(SzuKacz::Result(i, field));
						break;
					}
					case 5: //nie zawiera
					{
						if(readResult.find(toMatch) == std::string::npos)
							results.push_back(SzuKacz::Result(i, field));
						break;
					}
					case 6: //wyra¿enie regularne
					{
						try
						{
							boost::regex expression(toMatch, caseSensitive ? 0 : boost::regex::icase);
							if(boost::regex_search(readResult, expression))
								results.push_back(SzuKacz::Result(i, field));
							break;
						}
						catch(...)
						{
						}
					}
				}
			}
		}

		results.sort(SzuKacz::SortResult());

		//odblokowujemy listê kontaktów
		Ctrl->DTunlock(DTCNT,-1);

		return results;
	}

	//funkcja tworz¹ca okienko
	void Controller::openSearchWindow()
	{
		IMLOG("[Controller::searchWindow]:");

		//sprawdzamy, czy okienko nie poka¿e siê poza ekranem
		if(GETINT(SzuKacz::CFG::windowPosX) < GetSystemMetrics(SM_XVIRTUALSCREEN) || GETINT(SzuKacz::CFG::windowPosX) > GetSystemMetrics(SM_CXVIRTUALSCREEN))
		{
			IMLOG("Wspó³rzêdne osi X s¹ poza ekranem, zmieniam");
			SETINT(SzuKacz::CFG::windowPosX, 100);
		}
		if(GETINT(SzuKacz::CFG::windowPosY) < GetSystemMetrics(SM_YVIRTUALSCREEN) || GETINT(SzuKacz::CFG::windowPosX) > GetSystemMetrics(SM_CYVIRTUALSCREEN))
		{
			IMLOG("Wspó³rzêdne osi Y s¹ poza ekranem, zmieniam");
			SETINT(SzuKacz::CFG::windowPosY, 100);
		}
		if(GETINT(SzuKacz::CFG::windowWidth) < 0 || GETINT(SzuKacz::CFG::windowWidth) > GetSystemMetrics(SM_CXVIRTUALSCREEN))
		{
			IMLOG("Szerokoœæ okienka nieodpowiednia, zmieniam");
			SETINT(SzuKacz::CFG::windowWidth, GetSystemMetrics(SM_CXVIRTUALSCREEN));
		}
		if(GETINT(SzuKacz::CFG::windowHeight) < 0 || GETINT(SzuKacz::CFG::windowHeight) > GetSystemMetrics(SM_CYVIRTUALSCREEN))
		{
			IMLOG("Wysokoœæ okienka nieodpowiednia, zmieniam");
			SETINT(SzuKacz::CFG::windowHeight, GetSystemMetrics(SM_CYVIRTUALSCREEN));
		}

		//tworzymy okno
		this->searchWindow = CreateWindowEx(0, "SzuKaczSearchWindow", "Szukaj na liœcie", WS_VISIBLE|WS_CAPTION|WS_SYSMENU|WS_MINIMIZEBOX|WS_MAXIMIZEBOX|WS_THICKFRAME, GETINT(SzuKacz::CFG::windowPosX), GETINT(SzuKacz::CFG::windowPosY), GETINT(SzuKacz::CFG::windowWidth), GETINT(SzuKacz::CFG::windowHeight), 0, 0, Ctrl->hInst(), 0);
	}

	//funkcja odœwie¿aj¹ca toolbar szybkiego wyszukiwania
	void Controller::quickSearchToolbarRefresh(bool move)
	{
		this->quickSearchToolbarMoved = move;

		RECT rc1;
		GetWindowRect(this->konnektRoster, &rc1);
		int toolbarWidth = rc1.right - rc1.left - ((GetWindowLong(this->konnektRoster, GWL_STYLE) & WS_VSCROLL) ? GetSystemMetrics(SM_CXVSCROLL) : 0);
		MoveWindow(this->quickSearchToolbar, rc1.left, rc1.bottom - (this->quickSearchToolbarMoved ? 40 : 22) - ((GetWindowLong(this->konnektRoster, GWL_STYLE) & WS_HSCROLL) ? GetSystemMetrics(SM_CXHSCROLL) : 0), toolbarWidth, 22, 1);
		int width = LOWORD(SendMessage(this->quickSearchToolbar, TB_GETBUTTONSIZE, 0, 0));
		SendMessage(this->quickSearchToolbar, TB_SETINDENT, toolbarWidth - (4 * width), 0);
		MoveWindow(this->quickSearchEdit, 0, 1, toolbarWidth - (4 * width), 20, 1);
	}

	//funkcja ukrywaj¹ca toolbar szybkiego wyszukiwania
	void Controller::quickSearchToolbarHide(bool focusRooster)
	{
		this->quickSearchToolbarRefresh(0);

		ShowWindow(this->quickSearchEdit, SW_HIDE);
		ShowWindow(this->quickSearchToolbar, SW_HIDE);

		this->quickSearchToolbarVisible = 0;

		if(focusRooster)
			SetFocus(this->konnektRoster);
	}

	//funkcja zaznaczaj¹ca na liœcie kontakt o podanym ID
	void Controller::selectCnt(HWND listView, int cnt)
	{
		this->quickSearchToolbarRefresh(0);

		const int listCount = ListView_GetItemCount(listView);
		LVITEM lvi;
		lvi.iSubItem = 0;
		lvi.mask = LVIF_PARAM;
		for(int i = 0; i < listCount; i++)
		{
			lvi.iItem = i;
			ListView_GetItem(listView, &lvi);
			if(((sUICnt*)(lvi.lParam))->ID == cnt)
			{
				ListView_SetItemState(listView, i, LVIS_SELECTED|LVIS_FOCUSED, LVIS_SELECTED|LVIS_FOCUSED);
				RECT rc;
				RECT rc2;
				GetWindowRect(listView, &rc);
				ListView_GetItemRect(listView, i, (LPARAM)&rc2, LVIR_SELECTBOUNDS);
				if(rc2.bottom > rc.bottom - rc.top - 22 && i == listCount - 1 && !ListView_IsGroupViewEnabled(listView))
				{
					SendMessage(listView, WM_VSCROLL, SB_BOTTOM, 0);
					this->quickSearchToolbarRefresh(1);
				}
				else if(rc2.bottom > rc.bottom - rc.top - 22)
				{
					ListView_Scroll(listView, 0, rc2.bottom - (rc.bottom - rc.top - 22));
					ListView_Scroll(listView, 0, 1);
				}
				else if(rc2.top < 0)
				{
					ListView_Scroll(listView, 0, rc2.top);
					ListView_Scroll(listView, 0, -1);
				}
				return;
			}
		}
	}
}