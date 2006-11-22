#include "stdafx.h"
#include "includes.h"

namespace szuKacz
{
	//funkcja obs³uguj¹ca toolbar szybkiego wyszukiwania
	LRESULT CALLBACK QuickSearchToolbarProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
	{
		switch(iMsg)
		{
			case WM_KEYUP:
			{
				if(wParam == VK_RETURN)
				{
					IMLOG("[KonnektMainWindowProc]: iMsg = WM_KEYUP, wParam = VK_RETURN");

					if(HIWORD(GetKeyState(VK_CONTROL)) == 0)
					{
						switch(GETINT(szuKacz::Config::EnterAction))
						{
							case 1:
							{
								int pos = SendMessage(szuKacz::CNTListWindow, LVM_GETNEXTITEM, -1, LVNI_FOCUSED);
								if(pos != -1)
								{
									LVITEM lvi;
									lvi.mask = LVIF_PARAM;
									lvi.iItem = pos;
									ListView_GetItem(szuKacz::CNTListWindow, &lvi); 

									szuKacz::OpenMsgWindow(((sUICnt*)lvi.lParam)->ID);
								}
								szuKacz::QuickSearchToolbarHide(0);
								break;
							}
							case 2:
							{
								int pos = SendMessage(szuKacz::CNTListWindow, LVM_GETNEXTITEM, -1, LVNI_FOCUSED);
								if(pos != -1)
								{
									LVITEM lvi;
									lvi.mask = LVIF_PARAM;
									lvi.iItem = pos;
									ListView_GetItem(szuKacz::CNTListWindow, &lvi); 

									szuKacz::OpenInfoWindow(((sUICnt*)lvi.lParam)->ID);
								}
								szuKacz::QuickSearchToolbarHide(0);
								break;
							}
							case 3:
							{
								szuKacz::QuickSearchToolbarHide();
								break;
							}
						}
					}
					else
					{
						switch(GETINT(szuKacz::Config::CtrlEnterAction))
						{
							case 1:
							{
								int pos = SendMessage(szuKacz::CNTListWindow, LVM_GETNEXTITEM, -1, LVNI_FOCUSED);
								if(pos != -1)
								{
									LVITEM lvi;
									lvi.mask = LVIF_PARAM;
									lvi.iItem = pos;
									ListView_GetItem(szuKacz::CNTListWindow, &lvi); 

									szuKacz::OpenMsgWindow(((sUICnt*)lvi.lParam)->ID);
								}
								szuKacz::QuickSearchToolbarHide(0);
								break;
							}
							case 2:
							{
								int pos = SendMessage(szuKacz::CNTListWindow, LVM_GETNEXTITEM, -1, LVNI_FOCUSED);
								if(pos != -1)
								{
									LVITEM lvi;
									lvi.mask = LVIF_PARAM;
									lvi.iItem = pos;
									ListView_GetItem(szuKacz::CNTListWindow, &lvi); 

									szuKacz::OpenInfoWindow(((sUICnt*)lvi.lParam)->ID);
								}
								szuKacz::QuickSearchToolbarHide(0);
								break;
							}
							case 3:
							{
								szuKacz::QuickSearchToolbarHide();
								break;
							}
						}
					}
				}

				SendMessage(szuKacz::KonnektMainWindow, iMsg, wParam, lParam);
				break;
			}
		}

		return CallWindowProc(szuKacz::QuickSearchToolbarOldProc, hwnd, iMsg, wParam, lParam);
	}

	//funkcja obs³uguj¹ca edit szybkiego wyszukiwania
	LRESULT CALLBACK QuickSearchEditProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
	{
		switch(iMsg)
		{
			case WM_KEYUP:
			{
				SendMessage(szuKacz::QuickSearchToolbar, iMsg, wParam, lParam);
				break;
			}
		}

		return CallWindowProc(szuKacz::QuickSearchEditOldProc, hwnd, iMsg, wParam, lParam);
	}

	void CreateQuickSearchToolbar()
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

		szuKacz::QuickSearchEdit = CreateWindowEx(WS_EX_CLIENTEDGE, WC_EDIT, 0, WS_CHILD|ES_AUTOHSCROLL, 0, 0, 0, 0, szuKacz::QuickSearchToolbar, 0, Ctrl->hInst(), 0);

		//ustawiamy czcionkê
		{
			HFONT font = CreateFont(-11, 0, 0, 0, 0, 0, 0, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, "Tahoma");
			SendMessage(szuKacz::QuickSearchEdit, WM_SETFONT, (WPARAM)font, 0);
		}
	}

	//funkcja odœwie¿aj¹ca toolbar szybkiego wyszukiwania
	void QuickSearchToolbarRefresh(bool Move)
	{
		szuKacz::QuickSearchToolbarMoved = Move;

		RECT rc1;
		GetWindowRect(szuKacz::CNTListWindow, &rc1);
		int ToolbarWidth = rc1.right - rc1.left - ((GetWindowLong(szuKacz::CNTListWindow, GWL_STYLE) & WS_VSCROLL) ? GetSystemMetrics(SM_CXVSCROLL) : 0);
		MoveWindow(szuKacz::QuickSearchToolbar, rc1.left, rc1.bottom - (Move ? 40 : 22) - ((GetWindowLong(szuKacz::CNTListWindow, GWL_STYLE) & WS_HSCROLL) ? GetSystemMetrics(SM_CXHSCROLL) : 0), ToolbarWidth, 22, 1);
		int width = LOWORD(SendMessage(szuKacz::QuickSearchToolbar, TB_GETBUTTONSIZE, 0, 0));
		SendMessage(szuKacz::QuickSearchToolbar, TB_SETINDENT, ToolbarWidth - (4 * width), 0);
		MoveWindow(szuKacz::QuickSearchEdit, 0, 1, ToolbarWidth - (4 * width), 20, 1);
	}

	void QuickSearchToolbarHide(bool FocusRooster)
	{
		szuKacz::QuickSearchToolbarRefresh(0);

		ShowWindow(szuKacz::QuickSearchEdit, SW_HIDE);
		ShowWindow(szuKacz::QuickSearchToolbar, SW_HIDE);

		szuKacz::QuickSearchToolbarVisible = 0;

		if(FocusRooster)
		{
			SetFocus(szuKacz::CNTListWindow);
		}
	}
}