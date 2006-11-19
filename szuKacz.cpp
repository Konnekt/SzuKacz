#include "includes.h"

namespace szuKacz
{
	int IStart()
	{
		//rejestrujemy klasê okna
		{
			szuKacz::window_class.style = CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS;
			szuKacz::window_class.lpfnWndProc = szuKacz::WindowProc;
			szuKacz::window_class.cbClsExtra = 0;
			szuKacz::window_class.cbWndExtra = 0;
			szuKacz::window_class.hInstance = Ctrl->hInst();
			szuKacz::window_class.hCursor = LoadCursor(0, IDC_ARROW);
			szuKacz::window_class.lpszMenuName = 0;
			szuKacz::window_class.lpszClassName = "szukacz_window_class";
			szuKacz::window_class.hbrBackground = GetSysColorBrush(COLOR_BTNFACE);
			szuKacz::window_class.hIcon = (HICON)Ctrl->ICMessage(IMI_ICONGET, szuKacz::Icons::szuKacz32, IML_32);
			szuKacz::window_class.hIconSm = (HICON)Ctrl->ICMessage(IMI_ICONGET, szuKacz::Icons::szuKacz16, IML_16);
			szuKacz::window_class.cbSize = sizeof(szuKacz::window_class);
			RegisterClassEx(&szuKacz::window_class);
		}

		return 1;
	}

	int IEnd()
	{
		//sprawdzamy, czy nie jest w³¹czone okienko i w razie czego wy³¹czamy je
		{
			if(szuKacz::window)
			{
				SendMessage(szuKacz::window, WM_CLOSE, 0, 0);
			}

			//wyrejestrowujemy klasê okna
			{
				UnregisterClass("szukacz_window_class", Ctrl->hInst());
			}
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
			Ctrl->SetColumn(DTCFG, szuKacz::Config::ButtonOnToolbar, DT_CT_INT, 0, "kLock/ButtonOnToolbar");
			Ctrl->SetColumn(DTCFG, szuKacz::Config::ButtonInCntMenu, DT_CT_INT, 1, "kLock/ButtonInCntMenu");
			Ctrl->SetColumn(DTCFG, szuKacz::Config::ButtonOnMainToolbar, DT_CT_INT, 0, "kLock/ButtonOnMainToolbar");

		}

		return 1;
	}

	int IPrepare()
	{
		//rejestrujemy ikonki
		{
			IconRegister(IML_16, szuKacz::Icons::szuKacz16, (char*)szuKacz::Resources::szuKacz16);
			IconRegister(IML_32, szuKacz::Icons::szuKacz32, (char*)szuKacz::Resources::szuKacz32);
		}

		//przycisk na toolbarze wtyczek
		if(GETINT(szuKacz::Config::ButtonOnToolbar))
		{
			IMLOG("Tworzê przycisk w grupie wtyczek");
			UIActionAdd(Ctrl->IMessage(IMI_GETPLUGINSGROUP, 0, 0), szuKacz::Acts::Search, 0, "Szukaj na liœcie", szuKacz::Icons::szuKacz16);
		}

		//przycisk w tray'u
		if(GETINT(szuKacz::Config::ButtonInCntMenu))
		{
			IMLOG("Tworzê przycisk w menu kontaktów");
			UIActionAdd(IMIG_MAIN_CNT, szuKacz::Acts::Search, 0, "Szukaj na liœcie", szuKacz::Icons::szuKacz16);
		}

		//przycisk na g³ównym toolbarze
		if(GETINT(szuKacz::Config::ButtonOnMainToolbar))
		{
			if(Ctrl->IMessage(IMI_GETPLUGINSGROUP, 0, 0) != IMIG_MAINTB || !GETINT(szuKacz::Config::ButtonOnToolbar))
			{
				IMLOG("Tworzê przycisk na g³ównym toolbarze");
				UIActionAdd(IMIG_MAINTB, szuKacz::Acts::Search, 0, "Szukaj na liœcie", szuKacz::Icons::szuKacz16);
			}
		}

		UIGroupAdd(IMIG_CFG_PLUGS, szuKacz::Config::Group, 0, "SzuKacz", szuKacz::Icons::szuKacz16);
		{
			UIActionCfgAddPluginInfoBox2(szuKacz::Config::Group, "Wtyczka pozwala na szybkie przeszukiwanie listy kontaktów wed³ug ró¿nych kryteriów.", "<span class='note'>Skompilowano: <b>"__DATE__"</b> [<b>"__TIME__"</b>]</span><br/><br/>Copyright © 2004-2006 <b>Skolima</b><br/>Copyright © 2006 <b>Micha³ \"Dulek\" Dulko</b>", (char*)szuKacz::Resources::szuKacz32);

			UIActionCfgAdd(szuKacz::Config::Group, 0, ACTT_GROUP, "Opcje");
			{
				UIActionCfgAdd(szuKacz::Config::Group, 0, ACTT_SEP, "Po³o¿enie przycisku");
				UIActionCfgAdd(szuKacz::Config::Group, szuKacz::Config::ButtonOnToolbar, ACTT_CHECK|ACTSC_NEEDRESTART, "W menu wtyczek", szuKacz::Config::ButtonOnToolbar);
				UIActionCfgAdd(szuKacz::Config::Group, szuKacz::Config::ButtonInCntMenu, ACTT_CHECK|ACTSC_NEEDRESTART, "W menu kontaktów", szuKacz::Config::ButtonInCntMenu);
				UIActionCfgAdd(szuKacz::Config::Group, szuKacz::Config::ButtonOnMainToolbar, ACTT_CHECK|ACTSC_NEEDRESTART, "Na g³ównym toolbarze", szuKacz::Config::ButtonOnMainToolbar);
			}
		}

		return 1;
	}

	ActionProc(sUIActionNotify_base * anBase)
	{
		sUIActionNotify_2params * an = (anBase->s_size>=sizeof(sUIActionNotify_2params))?static_cast<sUIActionNotify_2params*>(anBase):0;

		switch (anBase->act.id)
		{
			case szuKacz::Acts::Search:
			{
				ACTIONONLY(an);

				IMLOG("[ActionProc]: anBase->act.id = szuKacz::Acts::Search, anBase->code = ACTN_ACTION");

				szuKacz::Window();
				break;
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
	{
		Ctrl->setError(IMERROR_NORESULT);
	}
	return 0;
}