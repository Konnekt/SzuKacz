#include "includes.h"

namespace szuKacz
{
	LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
	{
		switch(msg)
		{
			case WM_CREATE:
			{
				IMLOG("[WindowProc]: iMsg = WM_CREATE, wParam = %i, lParam = %i", wParam, lParam);

				//inicjujemy kontrolki
				{
					szuKacz::GroupBox(hwnd);
					szuKacz::Edit(hwnd);
					szuKacz::ComboBox1(hwnd);
					szuKacz::ComboBox2(hwnd);
					szuKacz::CheckBox(hwnd);
					szuKacz::ListView(hwnd);
					szuKacz::Toolbar(hwnd);
				}

				//ustawiamy focus
				{
					SetFocus(szuKacz::window);
				}

				break;
			}
			case WM_CLOSE:
			{
				IMLOG("[WindowProc]: iMsg = WM_CLOSE, wParam = %i, lParam = %i", wParam, lParam);

				//zapisujemy kilka danych
				{
					SETINT(szuKacz::Config::ComboBox1, SendMessage(szuKacz::combobox1, CB_GETCURSEL, 0, 0));
					SETINT(szuKacz::Config::ComboBox2, SendMessage(szuKacz::combobox2, CB_GETCURSEL, 0, 0));

					SETINT(szuKacz::Config::CheckBox, SendMessage(szuKacz::checkbox, BM_GETCHECK, 0, 0) == BST_CHECKED);

					LV_COLUMN lvc;
					lvc.mask = LVCF_WIDTH;
					ListView_GetColumn(szuKacz::listview, 0, &lvc);
					SETINT(szuKacz::Config::ListBoxColumn0, lvc.cx);
					ListView_GetColumn(szuKacz::listview, 1, &lvc);
					SETINT(szuKacz::Config::ListBoxColumn1, lvc.cx);
				}

				//niszczymy kontrolki i okienko
				{
					DestroyWindow(szuKacz::groupbox);
					DestroyWindow(szuKacz::edit);
					DestroyWindow(szuKacz::combobox1);
					DestroyWindow(szuKacz::combobox2);
					DestroyWindow(szuKacz::checkbox);
					DestroyWindow(szuKacz::listview);
					DestroyWindow(szuKacz::toolbar);
					DestroyWindow(hwnd);
				}

				//zerujemy uchwyt
				{
					szuKacz::window = 0;
				}

				return 0;
				break;
			}
			case WM_DESTROY:
			{
				IMLOG("[WindowProc]: iMsg = WM_DESTROY, wParam = %i, lParam = %i", wParam, lParam);

				//zapisujemy pozycjê okna
				{
					WINDOWPLACEMENT placement;
					placement.length = sizeof(WINDOWPLACEMENT);
					GetWindowPlacement(hwnd, &placement);
					SETINT(szuKacz::Config::WindowX, placement.rcNormalPosition.left);
					SETINT(szuKacz::Config::WindowY, placement.rcNormalPosition.top);
					SETINT(szuKacz::Config::WindowWidth, placement.rcNormalPosition.right - placement.rcNormalPosition.left);
					SETINT(szuKacz::Config::WindowHeight, placement.rcNormalPosition.bottom - placement.rcNormalPosition.top);
				}
				break;
			}
			case WM_GETMINMAXINFO:
			{
				//nie pozwalamy na zmniejszenie lub powiêkszenie okienka poza zakres
				{
					MINMAXINFO* minmax = (MINMAXINFO*)lParam;

					minmax->ptMinTrackSize.x = 400 + GetSystemMetrics(SM_CXFIXEDFRAME) * 2;
					minmax->ptMinTrackSize.y = 200 + GetSystemMetrics(SM_CYFIXEDFRAME) * 2 + GetSystemMetrics(SM_CYCAPTION);
				}
				break;
			}
			case WM_SIZE:
			{
				IMLOG("[WindowProc]: iMsg = WM_SIZE, wParam = %i, lParam = %i", wParam, lParam);

				//zmienne
				int width;
				int height;
				int x;
				int y;

				//GroupBox
				{
					x = 5;
					y = 5;
					width = 152;
					height = HIWORD(lParam) - 40;
					MoveWindow(szuKacz::groupbox, x, y, width, height, 1);
				}

				//Edit
				{
					x = 10;
					y = 20;
					width = 142;
					height = 20;
					MoveWindow(szuKacz::edit, x, y, width, height, 1);
				}

				//ComboBox1
				{
					y = 45;
					height = 22;
					MoveWindow(szuKacz::combobox1, x, y, width, height, 1);
				}

				//ComboBox2
				{
					y = 72;
					height = 22;
					MoveWindow(szuKacz::combobox2, x, y, width, height, 1);
				}

				//CheckBox
				{
					y = 99;
					height = 20;
					MoveWindow(szuKacz::checkbox, x, y, width, height, 1);
				}

				//ListView
				{
					x = 162;
					y = 13;
					width = LOWORD(lParam) - 167;
					height = HIWORD(lParam) - 48;
					MoveWindow(szuKacz::listview, x, y, width, height, 1);
				}

				//Toolbar
				{
					y = height + 18;
					height = 25;
					MoveWindow(szuKacz::toolbar, x, y, width, height, 1);
				}
				break;
			}
			case WM_NOTIFY:
			{
				switch(((LPNMHDR)lParam)->code)
				{
					case NM_DBLCLK:
					{
						IMLOG("[WindowProc]: iMsg = WM_NOTIFY, lParam->code = NM_DBLCLK, wParam = %i, lParam = %i", wParam, lParam);
						
						int pos = SendMessage(szuKacz::listview, LVM_GETNEXTITEM, -1, LVNI_FOCUSED);
						if(pos != -1)
						{
							LVITEM lvi;
							lvi.mask = LVIF_PARAM;
							lvi.iItem = pos;
							ListView_GetItem(szuKacz::listview, &lvi);

							if(GetDefaultAction(((szuKacz::Result*)lvi.lParam)->cnt) != -1)
							{
								CallAction(IMIG_CNT, GetDefaultAction(((szuKacz::Result*)lvi.lParam)->cnt), ((szuKacz::Result*)lvi.lParam)->cnt);
							}
						}
						break;
					}
					case LVN_COLUMNCLICK:
					{
						IMLOG("[WindowProc]: iMsg = WM_NOTIFY, lParam->code = LVN_COLUMNCLICK, wParam = %i, lParam = %i", wParam, lParam);

						SortStruct sort;
						static bool asc = true;

						sort.col = ((LPNMLISTVIEW)lParam)->iSubItem;
						sort.asc = asc = asc ? false : true;
						ListView_SortItemsEx(szuKacz::listview, szuKacz::Sort, (LPARAM)&sort);
						break;
					}
					case LVN_ITEMCHANGED:
					case LVN_DELETEALLITEMS:
					{
						int pos = SendMessage(szuKacz::listview, LVM_GETNEXTITEM, -1, LVNI_FOCUSED);
						if(pos != -1)
						{
							LVITEM lvi;
							lvi.mask = LVIF_PARAM;
							lvi.iItem = pos;
							ListView_GetItem(szuKacz::listview, &lvi);

							SendMessage(szuKacz::toolbar, TB_ENABLEBUTTON, 1, pos != -1 ? GetDefaultAction(((szuKacz::Result*)lvi.lParam)->cnt) == IMIA_CNT_MSG : 0);
							SendMessage(szuKacz::toolbar, TB_ENABLEBUTTON, 2, pos != -1 ? 1 : 0);
						}
						break;
					}
				}
				break;
			}
			case WM_COMMAND:
			{
				if((lParam == (LPARAM)szuKacz::edit && HIWORD(wParam) == EN_CHANGE) || (lParam == (LPARAM)szuKacz::combobox1 && HIWORD(wParam) == CBN_SELCHANGE) || (lParam == (LPARAM)szuKacz::combobox2 && HIWORD(wParam) == CBN_SELCHANGE) || (lParam == (LPARAM)szuKacz::checkbox && HIWORD(wParam) == BN_CLICKED))
				{
					szuKacz::results.clear();
					ListView_DeleteAllItems(szuKacz::listview);

					char buff[500];
					SendMessage(szuKacz::edit, WM_GETTEXT, 500, (LPARAM)&buff);
					if(strlen(buff) == 0)
					{
						break;
					}
					std::string text = buff;
					int field = SendMessage(szuKacz::combobox1, CB_GETCURSEL, 0, 0);
					int criterion = SendMessage(szuKacz::combobox2, CB_GETCURSEL, 0, 0);
					bool casesensitive = SendMessage(szuKacz::checkbox, BM_GETCHECK, 0, 0) == BST_CHECKED;
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

					szuKacz::results = szuKacz::findContact(field, text, criterion, casesensitive);

					LV_ITEM lvi;
					lvi.mask = LVIF_TEXT|LVIF_PARAM|LVIF_IMAGE|LVIF_PARAM;
					lvi.iSubItem = 0;
					for(std::vector<szuKacz::Result>::iterator i = szuKacz::results.begin(); i != szuKacz::results.end(); i++)
					{
						lvi.iItem = ListView_GetItemCount(szuKacz::listview);
						lvi.lParam = ListView_GetItemCount(szuKacz::listview);
						lvi.iImage = ICMessage(IMI_GETICONINDEX, UIIcon(IT_LOGO, i->net, 0, 0), IML_16);
						lvi.iImage = lvi.iImage == -1 ? lvi.iImage = ICMessage(IMI_GETICONINDEX, 0x40000000, IML_16) : lvi.iImage;
						lvi.pszText = (LPSTR)i->display.c_str();
						lvi.lParam = (LPARAM)&*i;
						ListView_InsertItem(szuKacz::listview, &lvi);
						ListView_SetItemText(szuKacz::listview, lvi.iItem, 1, (LPSTR)i->found_value.c_str());
					}
				}
				else if(lParam == (LPARAM)szuKacz::toolbar)
				{
					switch(LOWORD(wParam))
					{
						case 1:
						{
							IMLOG("[WindowProc]: iMsg = WM_COMMAND, LOWORD(wParam) = 1, lParam = toolbar");
							int pos = SendMessage(szuKacz::listview, LVM_GETNEXTITEM, -1, LVNI_FOCUSED);
							if(pos != -1)
							{
								LVITEM lvi;
								lvi.mask = LVIF_PARAM;
								lvi.iItem = pos;
								ListView_GetItem(szuKacz::listview, &lvi);

								if(GetDefaultAction(((szuKacz::Result*)lvi.lParam)->cnt) == IMIA_CNT_MSG)
								{
									CallAction(IMIG_CNT, IMIA_CNT_MSG, ((szuKacz::Result*)lvi.lParam)->cnt);
								}
							}
							break;
						}
						case 2:
						{
							IMLOG("[WindowProc]: iMsg = WM_COMMAND, LOWORD(wParam) = 2, lParam = toolbar");
							int pos = SendMessage(szuKacz::listview, LVM_GETNEXTITEM, -1, LVNI_FOCUSED);
							if(pos != -1)
							{
								LVITEM lvi;
								lvi.mask = LVIF_PARAM;
								lvi.iItem = pos;
								ListView_GetItem(szuKacz::listview, &lvi); 

								CallAction(IMIA_NFO_DETAILS_NET, IMIA_MSG_INFO, ((szuKacz::Result*)lvi.lParam)->cnt);
							}
							break;
						}
					}
				}
				break;
			}
			case WM_CONTEXTMENU:
			{
				if((HWND)wParam == szuKacz::listview)
				{
					IMLOG("[WindowProc]: iMsg = WM_CONTEXTMENU, wParam = treeview, LOWORD(lParam) = %i, HIWORD(lParam) = %i", LOWORD(lParam), HIWORD(lParam));

					POINT p;
					POINT pl;
					RECT r;

					p.x = LOWORD(lParam);
					p.y = HIWORD(lParam);

					if(p.x == 65535)
					{
						int pos = SendMessage(szuKacz::listview, LVM_GETNEXTITEM, -1, LVNI_FOCUSED);
						if(pos != -1)
						{
							LVITEM lvi;
							lvi.mask = LVIF_PARAM;
							lvi.iItem = pos;
							ListView_GetItem(szuKacz::listview, &lvi); 

							ListView_GetItemRect(szuKacz::listview, pos, (LPARAM)&r, LVIR_BOUNDS);
							p.x = r.left;
							p.y = r.top;
							ClientToScreen(szuKacz::listview, &p);
							IMessage(&sIMessage_UIMakePopup(sUIAction(IMIG_MAINWND, IMIG_CNT, ((szuKacz::Result*)lvi.lParam)->cnt), TPM_LEFTBUTTON|TPM_RIGHTBUTTON, p.x, p.y, 0, szuKacz::window));
						}
					}
					else
					{
						pl = p;
						ScreenToClient(szuKacz::listview, &pl);
						for(int pos = ListView_GetNextItem(szuKacz::listview, -1, LVNI_ALL);pos != -1;pos = ListView_GetNextItem(szuKacz::listview, pos, LVNI_ALL))
						{
							LVITEM lvi;
							lvi.mask = LVIF_PARAM;
							lvi.iItem = pos;
							ListView_GetItem(szuKacz::listview, &lvi); 

							if(ListView_GetItemRect(szuKacz::listview, pos, (LPARAM)&r, LVIR_BOUNDS) && IsInside(pl, r))
							{
								IMessage(&sIMessage_UIMakePopup(sUIAction(IMIG_MAINWND, IMIG_CNT, ((szuKacz::Result*)lvi.lParam)->cnt), TPM_LEFTBUTTON|TPM_RIGHTBUTTON, p.x, p.y, 0, szuKacz::window));
								break;
							}
						}
					}
				}
				break;
			}
			case WM_DRAWITEM:
			case WM_MEASUREITEM:
			case WM_ENTERIDLE:
			case WM_INITMENUPOPUP:
			{
				SendMessage((HWND)UIGroupHandle(sUIAction(0, IMIG_MAINWND)), msg, wParam, lParam);
				break;
			}
		}

		return DefWindowProc(hwnd, msg, wParam, lParam);
	}

	//funkcja tworz¹ca okienko
	void Window()
	{
		IMLOG("[Window]:");

		if(szuKacz::window)
		{
			return;
		}

		//sprawdzamy, czy okienko nie poka¿e siê poza ekranem
		if(GETINT(szuKacz::Config::WindowX) < GetSystemMetrics(SM_XVIRTUALSCREEN) || GETINT(szuKacz::Config::WindowX) > GetSystemMetrics(SM_CXVIRTUALSCREEN))
		{
			IMLOG("Wspó³rzêdne osi X s¹ poza ekranem, zmieniam");
			SETINT(szuKacz::Config::WindowX, 100);
		}
		if(GETINT(szuKacz::Config::WindowY) < GetSystemMetrics(SM_YVIRTUALSCREEN) || GETINT(szuKacz::Config::WindowX) > GetSystemMetrics(SM_CYVIRTUALSCREEN))
		{
			IMLOG("Wspó³rzêdne osi Y s¹ poza ekranem, zmieniam");
			SETINT(szuKacz::Config::WindowY, 100);
		}
		if(GETINT(szuKacz::Config::WindowWidth) < 0 || GETINT(szuKacz::Config::WindowWidth) > GetSystemMetrics(SM_CXVIRTUALSCREEN))
		{
			IMLOG("Szerokoœæ okienka nieodpowiednia, zmieniam");
			SETINT(szuKacz::Config::WindowWidth, GetSystemMetrics(SM_CXVIRTUALSCREEN));
		}
		if(GETINT(szuKacz::Config::WindowHeight) < 0 || GETINT(szuKacz::Config::WindowHeight) > GetSystemMetrics(SM_CYVIRTUALSCREEN))
		{
			IMLOG("Wysokoœæ okienka nieodpowiednia, zmieniam");
			SETINT(szuKacz::Config::WindowHeight, GetSystemMetrics(SM_CYVIRTUALSCREEN));
		}

		//tworzymy okno
		szuKacz::window = CreateWindowEx(0, "szukacz_window_class", "Szukaj na liœcie", WS_VISIBLE|WS_CAPTION|WS_SYSMENU|WS_MINIMIZEBOX|WS_MAXIMIZEBOX|WS_THICKFRAME, GETINT(szuKacz::Config::WindowX), GETINT(szuKacz::Config::WindowY), GETINT(szuKacz::Config::WindowWidth), GETINT(szuKacz::Config::WindowHeight), 0, 0, Ctrl->hInst(), 0);
	}

	void GroupBox(HWND parent)
	{
		szuKacz::groupbox = CreateWindowEx(0, WC_BUTTON, "Kryteria", WS_VISIBLE|WS_CHILD|BS_GROUPBOX, 0, 0, 0, 0, parent, 0, Ctrl->hInst(), 0);
	
		//ustawiamy czcionkê
		{
			HFONT font;
			font = CreateFont(-11, 0, 0, 0, FW_BOLD, 0, 0, 0, EASTEUROPE_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, "Tahoma");
			SendMessage(szuKacz::groupbox, WM_SETFONT, (WPARAM)font, 0);
		}
	}

	void Edit(HWND parent)
	{
		szuKacz::edit = CreateWindowEx(WS_EX_CLIENTEDGE, WC_EDIT, NULL, WS_CHILD|WS_VISIBLE|ES_LEFT|WS_TABSTOP, 0, 0, 0, 0, parent, 0, Ctrl->hInst(), 0);

		//ustawiamy czcionkê
		{
			HFONT font;
			font = CreateFont(-11, 0, 0, 0, 0, 0, 0, 0, EASTEUROPE_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, "Tahoma");
			SendMessage(szuKacz::edit, WM_SETFONT, (WPARAM)font, 0);
		}
	}

	void ComboBox1(HWND parent)
	{
		szuKacz::combobox1 = CreateWindowEx(WS_EX_RIGHTSCROLLBAR, WC_COMBOBOXEX, 0, WS_VISIBLE|WS_CHILD|WS_TABSTOP|CBS_DROPDOWNLIST, 0, 0, 0, 100, parent, NULL, Ctrl->hInst(), 0);

		//ustawiamy czcionkê
		{
			HFONT font;
			font = CreateFont(-11, 0, 0, 0, 0, 0, 0, 0, EASTEUROPE_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, "Tahoma");
			SendMessage(szuKacz::combobox1, WM_SETFONT, (WPARAM)font, 0);
		}

		//dodajemy elementy
		{
			COMBOBOXEXITEM cbei;
			cbei.mask = CBEIF_TEXT;
			cbei.iItem = -1;
			cbei.pszText = "Opis";
			SendMessage(szuKacz::combobox1, CBEM_INSERTITEM, 0, (LPARAM)&cbei);
			cbei.pszText = "UID";
			SendMessage(szuKacz::combobox1, CBEM_INSERTITEM, 0, (LPARAM)&cbei);
			cbei.pszText = "Wyœwietl jako";
			SendMessage(szuKacz::combobox1, CBEM_INSERTITEM, 0, (LPARAM)&cbei);
			cbei.pszText = "Komórka";
			SendMessage(szuKacz::combobox1, CBEM_INSERTITEM, 0, (LPARAM)&cbei);
			cbei.pszText = "IP";
			SendMessage(szuKacz::combobox1, CBEM_INSERTITEM, 0, (LPARAM)&cbei);
			cbei.pszText = "Miejscowoœæ";
			SendMessage(szuKacz::combobox1, CBEM_INSERTITEM, 0, (LPARAM)&cbei);
			cbei.pszText = "Imiê";
			SendMessage(szuKacz::combobox1, CBEM_INSERTITEM, 0, (LPARAM)&cbei);
			cbei.pszText = "Nazwisko";
			SendMessage(szuKacz::combobox1, CBEM_INSERTITEM, 0, (LPARAM)&cbei);
			cbei.pszText = "Ksywka";
			SendMessage(szuKacz::combobox1, CBEM_INSERTITEM, 0, (LPARAM)&cbei);

			SendMessage(szuKacz::combobox1, CB_SETCURSEL, GETINT(szuKacz::Config::ComboBox1), 0);
		}
	}

	void ComboBox2(HWND parent)
	{
		szuKacz::combobox2 = CreateWindowEx(WS_EX_RIGHTSCROLLBAR, WC_COMBOBOXEX, 0, WS_VISIBLE|WS_CHILD|WS_TABSTOP|CBS_DROPDOWNLIST, 0, 0, 0, 100, parent, NULL, Ctrl->hInst(), 0);

		//ustawiamy czcionkê
		{
			HFONT font;
			font = CreateFont(-11, 0, 0, 0, 0, 0, 0, 0, EASTEUROPE_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, "Tahoma");
			SendMessage(szuKacz::combobox2, WM_SETFONT, (WPARAM)font, 0);
		}

		//dodajemy elementy
		{
			COMBOBOXEXITEM cbei;
			cbei.mask = CBEIF_TEXT;
			cbei.iItem = -1;
			cbei.pszText = "Zawiera";
			SendMessage(szuKacz::combobox2, CBEM_INSERTITEM, 0, (LPARAM)&cbei);
			cbei.pszText = "Równe";
			SendMessage(szuKacz::combobox2, CBEM_INSERTITEM, 0, (LPARAM)&cbei);
			cbei.pszText = "Ró¿ne od";
			SendMessage(szuKacz::combobox2, CBEM_INSERTITEM, 0, (LPARAM)&cbei);
			cbei.pszText = "Zaczyna siê od";
			SendMessage(szuKacz::combobox2, CBEM_INSERTITEM, 0, (LPARAM)&cbei);
			cbei.pszText = "Koñczy siê na";
			SendMessage(szuKacz::combobox2, CBEM_INSERTITEM, 0, (LPARAM)&cbei);
			cbei.pszText = "Nie zawiera";
			SendMessage(szuKacz::combobox2, CBEM_INSERTITEM, 0, (LPARAM)&cbei);
			cbei.pszText = "Wyra¿enie regularne";
			SendMessage(szuKacz::combobox2, CBEM_INSERTITEM, 0, (LPARAM)&cbei);

			SendMessage(szuKacz::combobox2, CB_SETCURSEL, GETINT(szuKacz::Config::ComboBox2), 0);
		}
	}

	void CheckBox(HWND parent)
	{
		szuKacz::checkbox = CreateWindowEx(0, WC_BUTTON, "Uwzglêdniaj wielkoœæ liter", WS_VISIBLE|WS_CHILD|WS_TABSTOP|BS_AUTOCHECKBOX, 0, 0, 0, 0, parent, 0, Ctrl->hInst(), 0);

		if(GETINT(szuKacz::Config::CheckBox))
		{
			SendMessage(szuKacz::checkbox, BM_SETCHECK, BST_CHECKED, 0);
		}

		//ustawiamy czcionkê
		{
			HFONT font;
			font = CreateFont(-11, 0, 0, 0, 0, 0, 0, 0, EASTEUROPE_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, "Tahoma");
			SendMessage(szuKacz::checkbox, WM_SETFONT, (WPARAM)font, 0);
		}
	}

	//funkcja tworz¹ca TreeViewa
	void ListView(HWND parent)
	{
		//tworzymy kontrolkê
		{
			szuKacz::listview = CreateWindowEx(WS_EX_CLIENTEDGE, WC_LISTVIEW, "", WS_CHILD|WS_VISIBLE|WS_TABSTOP|WS_HSCROLL|LVS_SHOWSELALWAYS|LVS_REPORT|LVS_SHAREIMAGELISTS, 0, 0, 0, 0, parent, 0, Ctrl->hInst(), 0);
			ListView_SetExtendedListViewStyle(szuKacz::listview, LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
		}

		//ustawiamy imagelist
		{
			SendMessage(szuKacz::listview, LVM_SETIMAGELIST, LVSIL_SMALL, (LPARAM)(HIMAGELIST)Ctrl->ICMessage(IMI_GETICONLIST, IML_16));
		}

		//kolumny
		{
			LV_COLUMN lvc;

			lvc.mask = LVCF_FMT|LVCF_WIDTH|LVCF_TEXT;
			lvc.fmt = LVCFMT_LEFT;
			lvc.cx = GETINT(szuKacz::Config::ListBoxColumn0);
			lvc.pszText = "Kontakt";
			ListView_InsertColumn(szuKacz::listview, 0, &lvc);

			lvc.mask = LVCF_FMT|LVCF_WIDTH|LVCF_TEXT;
			lvc.fmt = LVCFMT_LEFT;
			lvc.cx = GETINT(szuKacz::Config::ListBoxColumn1);
			lvc.pszText = "Znaleziona wartoœæ";
			ListView_InsertColumn(szuKacz::listview, 1, &lvc);
		}
	}

	//funkcja tworz¹ca Toolbara
	void Toolbar(HWND parent)
	{
		//tworzymy kontrolkê
		{
			szuKacz::toolbar = CreateWindowEx(0, TOOLBARCLASSNAME, "", WS_CHILD|WS_VISIBLE|TBSTYLE_TOOLTIPS|TBSTYLE_TRANSPARENT|TBSTYLE_FLAT|TBSTYLE_LIST|CCS_NORESIZE|CCS_NODIVIDER|CCS_NOPARENTALIGN, 0, 0, 0, 0, parent, 0, Ctrl->hInst(), 0);
		}

		//ustawiamy rozmiar ikonek, imagelist, rozmiar struktury, wy³aczamy wyœiwetlanie tekstu
		{
			SendMessage(szuKacz::toolbar, TB_SETBITMAPSIZE, 0, MAKELONG(16, 16));
			SendMessage(szuKacz::toolbar, TB_SETIMAGELIST, 0, (LPARAM)(HIMAGELIST)Ctrl->ICMessage(IMI_GETICONLIST, IML_16));
		}

		//dodajemy przyciski
		{
			TBBUTTON buttons[2];
			buttons[0].iBitmap = Ctrl->ICMessage(IMI_GETICONINDEX, 1342177296, IML_16);
			buttons[0].idCommand = 1;
			buttons[0].fsState = 0;
			buttons[0].fsStyle = TBSTYLE_BUTTON|BTNS_AUTOSIZE;
			buttons[0].iString = (int)"Okno rozmowy";
			buttons[1].iBitmap = Ctrl->ICMessage(IMI_GETICONINDEX, 30, IML_16);
			buttons[1].idCommand = 2;
			buttons[1].fsState = 0;
			buttons[1].fsStyle = TBSTYLE_BUTTON|BTNS_AUTOSIZE;
			buttons[1].iString = (int)"W³aœciwoœci";
			SendMessage(szuKacz::toolbar, TB_ADDBUTTONS, 2, (LPARAM)&buttons);
			SendMessage(szuKacz::toolbar, TB_SETMAXTEXTROWS, 1, 0);
		}
	}
}