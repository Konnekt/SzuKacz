#include "stdafx.h"
#include "includes.h"

namespace SzuKacz
{
	//funkcja obs³uguj¹ca okno wyszukiwania
	LRESULT CALLBACK searchWindowProc(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
	{
		static HWND groupBox; //uchwyt GroupBoxa
		static HWND findWhatComboBox; //uchwyt Edita
		static HWND criterionComboBox; //uchwyt ComboBoxa ze sposobem
		static HWND methodComboBox; //uchwyt ComboBoxa z kryterium
		static HWND caseSensitiveCheckBox; //uchwyt CheckBoxa
		static HWND searchButton; //uchwyt Buttona
		static HWND resultsListView; //uchwyt ListViewa
		static HWND actionsToolbar; //uchwyt Toolbara
		static Controller* IMCtrl;
		if(!IMCtrl)
			IMCtrl = Controller::getInstance();

		switch(iMsg)
		{
			case WM_CREATE:
			{
				IMLOG("[searchWindowProc]: iMsg = WM_CREATE, wParam = %i, lParam = %i", wParam, lParam);

				//inicjujemy kontrolki
				{
					//GroupBox
					{
						//tworzymy kontrolkê
						groupBox = CreateWindowEx(0, WC_BUTTON, "Kryteria", WS_VISIBLE|WS_CHILD|BS_GROUPBOX, 0, 0, 0, 0, hWnd, 0, Ctrl->hInst(), 0);
						
						//ustawiamy czcionkê
						{
							HFONT font;
							font = CreateFont(-11, 0, 0, 0, FW_BOLD, 0, 0, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, "Tahoma");
							SendMessage(groupBox, WM_SETFONT, (WPARAM)font, 0);
						}
					}

					//ComboBox z tekstem do wyszukania
					{
						//tworzymy kontrolkê
						findWhatComboBox = CreateWindowEx(WS_EX_RIGHTSCROLLBAR, WC_COMBOBOXEX, 0, WS_CHILD|WS_VISIBLE|WS_TABSTOP|CBS_DROPDOWN, 0, 0, 0, 100, hWnd, 0, Ctrl->hInst(), 0);

						//ustawiamy czcionkê
						{
							HFONT font;
							font = CreateFont(-11, 0, 0, 0, 0, 0, 0, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, "Tahoma");
							SendMessage(findWhatComboBox, WM_SETFONT, (WPARAM)font, 0);
						}

						//dodajemy itemy (z MRU)
						{
							tMRUlist list = IMCtrl->mruList->get();
							COMBOBOXEXITEM cbei;
							cbei.mask = CBEIF_TEXT;
							cbei.iItem = -1;
							for(tMRUlist::iterator i = list.begin(); i != list.end(); i++)
							{
								if(i->size())
								{
									cbei.pszText = (LPSTR)i->c_str();
									SendMessage(findWhatComboBox, CBEM_INSERTITEM, 0, (LPARAM)&cbei);
								}
							}
						}
					}

					//ComboBox ze sposobem
					{
						//tworzymy kontrolkê
						criterionComboBox = CreateWindowEx(WS_EX_RIGHTSCROLLBAR, WC_COMBOBOXEX, 0, WS_VISIBLE|WS_CHILD|WS_TABSTOP|CBS_DROPDOWNLIST, 0, 0, 0, 100, hWnd, 0, Ctrl->hInst(), 0);

						//ustawiamy czcionkê
						{
							HFONT font;
							font = CreateFont(-11, 0, 0, 0, 0, 0, 0, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, "Tahoma");
							SendMessage(criterionComboBox, WM_SETFONT, (WPARAM)font, 0);
						}

						//dodajemy elementy
						{
							COMBOBOXEXITEM cbei;
							cbei.mask = CBEIF_TEXT;
							cbei.iItem = -1;
							cbei.pszText = "Opis";
							SendMessage(criterionComboBox, CBEM_INSERTITEM, 0, (LPARAM)&cbei);
							cbei.pszText = "UID";
							SendMessage(criterionComboBox, CBEM_INSERTITEM, 0, (LPARAM)&cbei);
							cbei.pszText = "Wyœwietl jako";
							SendMessage(criterionComboBox, CBEM_INSERTITEM, 0, (LPARAM)&cbei);
							cbei.pszText = "Komórka";
							SendMessage(criterionComboBox, CBEM_INSERTITEM, 0, (LPARAM)&cbei);
							cbei.pszText = "IP";
							SendMessage(criterionComboBox, CBEM_INSERTITEM, 0, (LPARAM)&cbei);
							cbei.pszText = "Miejscowoœæ";
							SendMessage(criterionComboBox, CBEM_INSERTITEM, 0, (LPARAM)&cbei);
							cbei.pszText = "Imiê";
							SendMessage(criterionComboBox, CBEM_INSERTITEM, 0, (LPARAM)&cbei);
							cbei.pszText = "Nazwisko";
							SendMessage(criterionComboBox, CBEM_INSERTITEM, 0, (LPARAM)&cbei);
							cbei.pszText = "Ksywka";
							SendMessage(criterionComboBox, CBEM_INSERTITEM, 0, (LPARAM)&cbei);

							SendMessage(criterionComboBox, CB_SETCURSEL, GETINT(SzuKacz::CFG::selectedMethod), 0);
						}
					}

					//ComboBox z kryterium
					{
						//tworzymy kontrolkê
						methodComboBox = CreateWindowEx(WS_EX_RIGHTSCROLLBAR, WC_COMBOBOXEX, 0, WS_VISIBLE|WS_CHILD|WS_TABSTOP|CBS_DROPDOWNLIST, 0, 0, 0, 100, hWnd, 0, Ctrl->hInst(), 0);

						//ustawiamy czcionkê
						{
							HFONT font;
							font = CreateFont(-11, 0, 0, 0, 0, 0, 0, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, "Tahoma");
							SendMessage(methodComboBox, WM_SETFONT, (WPARAM)font, 0);
						}

						//dodajemy elementy
						{
							COMBOBOXEXITEM cbei;
							cbei.mask = CBEIF_TEXT;
							cbei.iItem = -1;
							cbei.pszText = "Zawiera";
							SendMessage(methodComboBox, CBEM_INSERTITEM, 0, (LPARAM)&cbei);
							cbei.pszText = "Równe";
							SendMessage(methodComboBox, CBEM_INSERTITEM, 0, (LPARAM)&cbei);
							cbei.pszText = "Ró¿ne od";
							SendMessage(methodComboBox, CBEM_INSERTITEM, 0, (LPARAM)&cbei);
							cbei.pszText = "Zaczyna siê od";
							SendMessage(methodComboBox, CBEM_INSERTITEM, 0, (LPARAM)&cbei);
							cbei.pszText = "Koñczy siê na";
							SendMessage(methodComboBox, CBEM_INSERTITEM, 0, (LPARAM)&cbei);
							cbei.pszText = "Nie zawiera";
							SendMessage(methodComboBox, CBEM_INSERTITEM, 0, (LPARAM)&cbei);
							cbei.pszText = "Wyra¿enie regularne";
							SendMessage(methodComboBox, CBEM_INSERTITEM, 0, (LPARAM)&cbei);

							SendMessage(methodComboBox, CB_SETCURSEL, GETINT(SzuKacz::CFG::selectedCriterion), 0);
						}
					}

					//CheckBox czy uwzglêdniaæ wielkoœæ znaków
					{
						//tworzymy kontrolkê
						caseSensitiveCheckBox = CreateWindowEx(0, WC_BUTTON, "Uwzglêdniaj wielkoœæ liter", WS_VISIBLE|WS_CHILD|WS_TABSTOP|BS_AUTOCHECKBOX, 0, 0, 0, 0, hWnd, 0, Ctrl->hInst(), 0);

						if(GETINT(SzuKacz::CFG::selectedCaseSensitive))
							SendMessage(caseSensitiveCheckBox, BM_SETCHECK, BST_CHECKED, 0);

						//ustawiamy czcionkê
						{
							HFONT font;
							font = CreateFont(-11, 0, 0, 0, 0, 0, 0, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, "Tahoma");
							SendMessage(caseSensitiveCheckBox, WM_SETFONT, (WPARAM)font, 0);
						}
					}

					//Button "Szukaj"
					{
						//tworzymy kontrolkê
						searchButton = CreateWindowEx(0, WC_BUTTON, "Szukaj", WS_VISIBLE|WS_CHILD|WS_TABSTOP, 0, 0, 0, 0, hWnd, 0, Ctrl->hInst(), 0);

						//ustawiamy czcionkê
						{
							HFONT font;
							font = CreateFont(-11, 0, 0, 0, 0, 0, 0, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, "Tahoma");
							SendMessage(searchButton, WM_SETFONT, (WPARAM)font, 0);
						}
					}

					//ListView z wynikami
					{
						//tworzymy kontrolkê
						{
							resultsListView = CreateWindowEx(WS_EX_CLIENTEDGE, WC_LISTVIEW, "", WS_CHILD|WS_VISIBLE|WS_TABSTOP|WS_HSCROLL|LVS_SHOWSELALWAYS|LVS_REPORT|LVS_SHAREIMAGELISTS, 0, 0, 0, 0, hWnd, 0, Ctrl->hInst(), 0);
							ListView_SetExtendedListViewStyle(resultsListView, LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
						}

						//ustawiamy imagelist
						SendMessage(resultsListView, LVM_SETIMAGELIST, LVSIL_SMALL, (LPARAM)(HIMAGELIST)Ctrl->ICMessage(IMI_GETICONLIST, IML_16));

						//kolumny
						{
							LV_COLUMN lvc;

							lvc.mask = LVCF_FMT|LVCF_WIDTH|LVCF_TEXT;
							lvc.fmt = LVCFMT_LEFT;
							lvc.cx = GETINT(SzuKacz::CFG::column0Width);
							lvc.pszText = "Kontakt";
							ListView_InsertColumn(resultsListView, 0, &lvc);

							lvc.mask = LVCF_FMT|LVCF_WIDTH|LVCF_TEXT;
							lvc.fmt = LVCFMT_LEFT;
							lvc.cx = GETINT(SzuKacz::CFG::column1Width);
							lvc.pszText = "Znaleziona wartoœæ";
							ListView_InsertColumn(resultsListView, 1, &lvc);
						}
					}

					//Toolbar z akcjami
					{
						//tworzymy kontrolkê
						actionsToolbar = CreateWindowEx(0, TOOLBARCLASSNAME, "", WS_CHILD|WS_VISIBLE|TBSTYLE_TOOLTIPS|TBSTYLE_TRANSPARENT|TBSTYLE_FLAT|TBSTYLE_LIST|CCS_NORESIZE|CCS_NODIVIDER|CCS_NOPARENTALIGN, 0, 0, 0, 0, hWnd, 0, Ctrl->hInst(), 0);

						//ustawiamy rozmiar ikonek, imagelist
						{
							SendMessage(actionsToolbar, TB_SETBITMAPSIZE, 0, MAKELONG(16, 16));
							SendMessage(actionsToolbar, TB_SETIMAGELIST, 0, (LPARAM)(HIMAGELIST)Ctrl->ICMessage(IMI_GETICONLIST, IML_16));
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
							SendMessage(actionsToolbar, TB_ADDBUTTONS, 2, (LPARAM)&buttons);
							SendMessage(actionsToolbar, TB_SETMAXTEXTROWS, 1, 0);
						}
					}
				}

				//ustawiamy focus
				SetFocus(hWnd);

				break;
			}
			case WM_CLOSE:
			{
				IMLOG("[searchWindowProc]: iMsg = WM_CLOSE");

				IMCtrl->searchWindow = 0;
				DestroyWindow(hWnd);

				return 0;
			}
			case WM_DESTROY:
			{
				IMLOG("[searchWindowProc]: iMsg = WM_DESTROY");

				//zapisujemy pozycjê okna i kilka innych danych
				{
					WINDOWPLACEMENT placement;
					placement.length = sizeof(WINDOWPLACEMENT);
					GetWindowPlacement(hWnd, &placement);
					SETINT(SzuKacz::CFG::windowPosX, placement.rcNormalPosition.left);
					SETINT(SzuKacz::CFG::windowPosY, placement.rcNormalPosition.top);
					SETINT(SzuKacz::CFG::windowWidth, placement.rcNormalPosition.right - placement.rcNormalPosition.left);
					SETINT(SzuKacz::CFG::windowHeight, placement.rcNormalPosition.bottom - placement.rcNormalPosition.top);

					SETINT(SzuKacz::CFG::selectedMethod, SendMessage(criterionComboBox, CB_GETCURSEL, 0, 0));
					SETINT(SzuKacz::CFG::selectedCriterion, SendMessage(methodComboBox, CB_GETCURSEL, 0, 0));
					SETINT(SzuKacz::CFG::selectedCaseSensitive, SendMessage(caseSensitiveCheckBox, BM_GETCHECK, 0, 0) == BST_CHECKED);

					LV_COLUMN lvc;
					lvc.mask = LVCF_WIDTH;
					ListView_GetColumn(resultsListView, 0, &lvc);
					SETINT(SzuKacz::CFG::column0Width, lvc.cx);
					ListView_GetColumn(resultsListView, 1, &lvc);
					SETINT(SzuKacz::CFG::column1Width, lvc.cx);
				}
				return 0;
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
					MoveWindow(groupBox, x, y, width, height, 1);
				}

				//findWhatComboBox
				{
					x = 10;
					y = 20;
					width = 142;
					height = 22;
					MoveWindow(findWhatComboBox, x, y, width, height, 1);
				}

				//ComboBox1
				{
					y = 47;
					height = 22;
					MoveWindow(criterionComboBox, x, y, width, height, 1);
				}

				//ComboBox2
				{
					y = 74;
					height = 22;
					MoveWindow(methodComboBox, x, y, width, height, 1);
				}

				//CheckBox
				{
					y = 101;
					height = 20;
					MoveWindow(caseSensitiveCheckBox, x, y, width, height, 1);
				}

				//Button
				{
					y = HIWORD(lParam) - 30;
					height = 23;
					MoveWindow(searchButton, x, y, width, height, 1);
				}

				//ListView
				{
					x = 162;
					y = 13;
					width = LOWORD(lParam) - 167;
					height = HIWORD(lParam) - 48;
					MoveWindow(resultsListView, x, y, width, height, 1);
				}

				//Toolbar
				{
					y = height + 18;
					height = 25;
					MoveWindow(actionsToolbar, x, y, width, height, 1);
				}
				break;
			}
			case WM_NOTIFY:
			{
				switch(((LPNMHDR)lParam)->code)
				{
					case NM_DBLCLK:
					{
						IMLOG("[searchWindowProc]: iMsg = WM_NOTIFY, lParam->code = NM_DBLCLK, wParam = %i, lParam = %i", wParam, lParam);
						
						int pos = SendMessage(resultsListView, LVM_GETNEXTITEM, -1, LVNI_FOCUSED);
						if(pos != -1)
						{
							LVITEM lvi;
							lvi.mask = LVIF_PARAM;
							lvi.iItem = pos;
							ListView_GetItem(resultsListView, &lvi);

							SzuKacz::callDefaultAction(((SzuKacz::Result*)lvi.lParam)->cnt);
						}
						break;
					}
					case LVN_COLUMNCLICK:
					{
						IMLOG("[searchWindowProc]: iMsg = WM_NOTIFY, lParam->code = LVN_COLUMNCLICK, wParam = %i, lParam = %i", wParam, lParam);

						SortStruct sort;
						static bool asc = true;

						sort.listView = resultsListView;
						sort.col = ((LPNMLISTVIEW)lParam)->iSubItem;
						sort.asc = asc = asc ? false : true;
						ListView_SortItemsEx(resultsListView, SzuKacz::sort, (LPARAM)&sort);
						break;
					}
					case LVN_ITEMCHANGED:
					case LVN_DELETEALLITEMS:
					{
						IMLOG("[searchWindowProc]: iMsg = WM_NOTIFY, lParam->code = LVN_ITEMCHANGED|LVN_DELETEALLITEMS, wParam = %i, lParam = %i", wParam, lParam);

						int pos = SendMessage(resultsListView, LVM_GETNEXTITEM, -1, LVNI_FOCUSED);
						if(pos != -1)
						{
							LVITEM lvi;
							lvi.mask = LVIF_PARAM;
							lvi.iItem = pos;
							ListView_GetItem(resultsListView, &lvi);

							SendMessage(actionsToolbar, TB_ENABLEBUTTON, 1, pos != -1 ? SzuKacz::getDefaultAction(((SzuKacz::Result*)lvi.lParam)->cnt) == IMIA_CNT_MSG : 0);
							SendMessage(actionsToolbar, TB_ENABLEBUTTON, 2, pos != -1 ? 1 : 0);
						}
						break;
					}
				}
				break;
			}
			case WM_COMMAND:
			{
				if((lParam == (LPARAM)searchButton && HIWORD(wParam) == BN_CLICKED) || (lParam == 0 && HIWORD(wParam) == 0 && LOWORD(wParam) == 1))
				{
					IMLOG("[searchWindowProc]: iMsg = WM_COMMAND, lParam = button|0, HIWORD(wParam) = BN_CLICKED|0, wParam = %i, lParam = %i", wParam, lParam);

					IMCtrl->searchResults.clear();
					ListView_DeleteAllItems(resultsListView);

					char buff[500];
					SendMessage(findWhatComboBox, WM_GETTEXT, 500, (LPARAM)&buff);
					if(!strlen(buff))
						break;
					std::string text = buff;
					int field = SendMessage(criterionComboBox, CB_GETCURSEL, 0, 0);
					int method = SendMessage(methodComboBox, CB_GETCURSEL, 0, 0);
					bool casesensitive = SendMessage(caseSensitiveCheckBox, BM_GETCHECK, 0, 0) == BST_CHECKED;

					IMCtrl->searchResults = IMCtrl->findContact(field, text, method, casesensitive, 0, 1);

					//reset ComboBoxa z has³ami
					{
						SendMessage(findWhatComboBox, CB_RESETCONTENT, 0, 0);
						tMRUlist list = IMCtrl->mruList->get();
						COMBOBOXEXITEM cbei;
						cbei.mask = CBEIF_TEXT;
						cbei.iItem = -1;
						for(tMRUlist::iterator i = list.begin(); i != list.end(); i++)
						{
							if(i->size())
							{
								cbei.pszText = (LPSTR)i->c_str();
								SendMessage(findWhatComboBox, CBEM_INSERTITEM, 0, (LPARAM)&cbei);
							}
						}
					}

					LV_ITEM lvi;
					lvi.mask = LVIF_TEXT|LVIF_PARAM|LVIF_IMAGE|LVIF_PARAM;
					lvi.iSubItem = 0;
					for(SzuKacz::tResults::iterator i = IMCtrl->searchResults.begin(); i != IMCtrl->searchResults.end(); i++)
					{
						lvi.iItem = ListView_GetItemCount(resultsListView);
						lvi.lParam = ListView_GetItemCount(resultsListView);
						lvi.iImage = ICMessage(IMI_GETICONINDEX, UIIcon(IT_LOGO, i->net, 0, 0), IML_16);
						lvi.iImage = lvi.iImage == -1 ? lvi.iImage = ICMessage(IMI_GETICONINDEX, 0x40000000, IML_16) : lvi.iImage;
						lvi.pszText = (LPSTR)i->display.c_str();
						lvi.lParam = (LPARAM)&*i;
						ListView_InsertItem(resultsListView, &lvi);
						ListView_SetItemText(resultsListView, lvi.iItem, 1, (LPSTR)i->foundValue.c_str());
					}
				}
				else if(lParam == (LPARAM)actionsToolbar)
				{
					switch(LOWORD(wParam))
					{
						case 1:
						{
							IMLOG("[searchWindowProc]: iMsg = WM_COMMAND, LOWORD(wParam) = 1, lParam = toolbar");
							int pos = SendMessage(resultsListView, LVM_GETNEXTITEM, -1, LVNI_FOCUSED);
							if(pos != -1)
							{
								LVITEM lvi;
								lvi.mask = LVIF_PARAM;
								lvi.iItem = pos;
								ListView_GetItem(resultsListView, &lvi);

								SzuKacz::openMsgWindow(((SzuKacz::Result*)lvi.lParam)->cnt);
							}
							break;
						}
						case 2:
						{
							IMLOG("[searchWindowProc]: iMsg = WM_COMMAND, LOWORD(wParam) = 2, lParam = toolbar");
							int pos = SendMessage(resultsListView, LVM_GETNEXTITEM, -1, LVNI_FOCUSED);
							if(pos != -1)
							{
								LVITEM lvi;
								lvi.mask = LVIF_PARAM;
								lvi.iItem = pos;
								ListView_GetItem(resultsListView, &lvi); 

								SzuKacz::openInfoWindow(((SzuKacz::Result*)lvi.lParam)->cnt);
							}
							break;
						}
					}
				}
				break;
			}
			case WM_CONTEXTMENU:
			{
				if((HWND)wParam == resultsListView)
				{
					IMLOG("[searchWindowProc]: iMsg = WM_CONTEXTMENU, wParam = listview, LOWORD(lParam) = %i, HIWORD(lParam) = %i", LOWORD(lParam), HIWORD(lParam));

					POINT p;
					POINT pl;
					RECT r;

					p.x = LOWORD(lParam);
					p.y = HIWORD(lParam);

					if(p.x == 65535)
					{
						int pos = SendMessage(resultsListView, LVM_GETNEXTITEM, -1, LVNI_FOCUSED);
						if(pos != -1)
						{
							LVITEM lvi;
							lvi.mask = LVIF_PARAM;
							lvi.iItem = pos;
							ListView_GetItem(resultsListView, &lvi); 

							ListView_GetItemRect(resultsListView, pos, (LPARAM)&r, LVIR_BOUNDS);
							p.x = r.left;
							p.y = r.top;
							ClientToScreen(resultsListView, &p);
							IMessage(&sIMessage_UIMakePopup(sUIAction(IMIG_MAINWND, IMIG_CNT, ((SzuKacz::Result*)lvi.lParam)->cnt), TPM_LEFTBUTTON|TPM_RIGHTBUTTON, p.x, p.y, 0, hWnd));
						}
					}
					else
					{
						pl = p;
						ScreenToClient(resultsListView, &pl);
						LVHITTESTINFO lvhti;
						lvhti.pt = pl;
						if(SendMessage(resultsListView, (LPARAM)LVM_HITTEST, 0, (LPARAM)&lvhti) != -1)
						{
							LVITEM lvi;
							lvi.mask = LVIF_PARAM;
							lvi.iItem = lvhti.iItem;
							ListView_GetItem(resultsListView, &lvi);
							IMessage(&sIMessage_UIMakePopup(sUIAction(IMIG_MAINWND, IMIG_CNT, ((SzuKacz::Result*)lvi.lParam)->cnt), TPM_LEFTBUTTON|TPM_RIGHTBUTTON, p.x, p.y, 0, hWnd));
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
				SendMessage(IMCtrl->konnektWindow, iMsg, wParam, lParam);
				break;
			}
		}
		return DefWindowProc(hWnd, iMsg, wParam, lParam);
	}

	//funkcja obs³uguj¹ca g³ówne okno Konnekta
	LRESULT CALLBACK konnektMainWindowProc(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
	{
		static Controller* IMCtrl;
		if(!IMCtrl)
			IMCtrl = Controller::getInstance();

		int ReturnedProcValue = CallWindowProc(IMCtrl->konnektWindowOldProc, hWnd, iMsg, wParam, lParam);

		if(!IMCtrl->quickSearchToolbarVisible)
			return ReturnedProcValue;

		switch(iMsg)
		{
			case WM_SIZE:
			case WM_MOVE:
			case WM_WINDOWPOSCHANGED:
			{
				if(IsWindowVisible(hWnd))
					IMCtrl->quickSearchToolbarRefresh(IMCtrl->quickSearchToolbarMoved);
				else
					IMCtrl->quickSearchToolbarHide(0);
				break;
			}
			case WM_NOTIFY:
			{
				switch(((LPNMHDR)lParam)->code)
				{
					case TBN_DROPDOWN:
					{
						IMLOG("[konnektMainWindowProc]: iMsg = WM_NOTIFY, lParam->code = TBN_DROPDOWN");

						LPNMTOOLBAR nmt = (LPNMTOOLBAR)lParam;
						if(nmt->hdr.hwndFrom == IMCtrl->quickSearchToolbar)
						{
							POINT pt;
							pt.x = nmt->rcButton.right;
							pt.y = nmt->rcButton.top;
							ClientToScreen(IMCtrl->quickSearchToolbar, &pt);
							if(nmt->iItem == 1)
								IMessage(&sIMessage_UIMakePopup(sUIAction(0, SzuKacz::ACT::criterionMenu), TPM_LEFTBUTTON|TPM_RIGHTBUTTON|TPM_RIGHTALIGN|TPM_BOTTOMALIGN, pt.x, pt.y, 0, hWnd));
							else if(nmt->iItem == 2)
								IMessage(&sIMessage_UIMakePopup(sUIAction(0, SzuKacz::ACT::methodMenu), TPM_LEFTBUTTON|TPM_RIGHTBUTTON|TPM_RIGHTALIGN|TPM_BOTTOMALIGN, pt.x, pt.y, 0, hWnd));
							return TBDDRET_DEFAULT;
						}
					}
				}
				break;
			}
			case WM_COMMAND:
			{
				if(lParam == (LPARAM)IMCtrl->quickSearchEdit && HIWORD(wParam) == EN_CHANGE)
				{
					IMLOG("[konnektMainWindowProc]: iMsg = WM_COMMAND, lParam = QuickSearchEdit, HIWORD(wParam) = EN_CHANGE, wParam = %i, lParam = %i");

					if(!IMCtrl->currentQuickSearchResult)
						delete IMCtrl->currentQuickSearchResult;
					IMCtrl->currentQuickSearchResult = 0;
					IMCtrl->quickSearchResults.clear();
					ListView_SetItemState(IMCtrl->konnektRoster, -1, 0, LVIS_SELECTED|LVIS_FOCUSED);
					IMCtrl->quickSearchToolbarRefresh(0);

					char buff[500];
					SendMessage(IMCtrl->quickSearchEdit, WM_GETTEXT, 500, (LPARAM)&buff);
					if(!strlen(buff))
						break;
					std::string text = buff;
					int field = GETINT(SzuKacz::CFG::quickSearchSelectedCriterion);
					int method = GETINT(SzuKacz::CFG::quickSearchSelectedMethod);
					int caseSensitive = GETINT(SzuKacz::CFG::quickSearchSelectedCaseSensitive);

					IMCtrl->quickSearchResults = IMCtrl->findContact(field, text, method, caseSensitive);
					if(IMCtrl->quickSearchResults.size())
					{
						IMCtrl->currentQuickSearchResult = new SzuKacz::tResults::iterator(IMCtrl->quickSearchResults.begin());
						IMCtrl->selectCnt(IMCtrl->konnektRoster, (*IMCtrl->currentQuickSearchResult)->cnt);
					}
				}
				else if(lParam == (LPARAM)IMCtrl->quickSearchToolbar)
				{
					switch(LOWORD(wParam))
					{
						case 3:
						{
							IMLOG("[konnektMainWindowProc]: iMsg = WM_COMMAND, LOWORD(wParam) = 3, lParam = QuickSearchToolbar");
							if(IMCtrl->currentQuickSearchResult)
							{
								if((*IMCtrl->currentQuickSearchResult) == IMCtrl->quickSearchResults.begin())
								{
									delete IMCtrl->currentQuickSearchResult;
									IMCtrl->currentQuickSearchResult = new SzuKacz::tResults::iterator((IMCtrl->quickSearchResults.end()));
								}
								(*IMCtrl->currentQuickSearchResult)--;
								ListView_SetItemState(IMCtrl->konnektRoster, -1, 0, LVIS_SELECTED|LVIS_FOCUSED);
								IMCtrl->selectCnt(IMCtrl->konnektRoster, (*IMCtrl->currentQuickSearchResult)->cnt);
						
							}
							break;
						}
						case 4:
						{
							IMLOG("[konnektMainWindowProc]: iMsg = WM_COMMAND, LOWORD(wParam) = 4, lParam = QuickSearchToolbar");
							if(IMCtrl->currentQuickSearchResult)
							{
								(*IMCtrl->currentQuickSearchResult)++;
								if((*IMCtrl->currentQuickSearchResult) == IMCtrl->quickSearchResults.end())
								{
									delete IMCtrl->currentQuickSearchResult;
									IMCtrl->currentQuickSearchResult = new SzuKacz::tResults::iterator(IMCtrl->quickSearchResults.begin());
								}
								ListView_SetItemState(IMCtrl->konnektRoster, -1, 0, LVIS_SELECTED|LVIS_FOCUSED);
								IMCtrl->selectCnt(IMCtrl->konnektRoster, (*IMCtrl->currentQuickSearchResult)->cnt);
							}
							break;
						}
					}
				}
				break;
			}
			case WM_KEYUP:
			{
				if(wParam == VK_ESCAPE)
					IMCtrl->quickSearchToolbarHide(1);
				break;
			}
		}
		return ReturnedProcValue;
	}

	//funkcja obs³uguj¹ca toolbar szybkiego wyszukiwania
	LRESULT CALLBACK quickSearchToolbarProc(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
	{
		static Controller* IMCtrl;
		if(!IMCtrl)
			IMCtrl = Controller::getInstance();

		switch(iMsg)
		{
			case WM_KEYUP:
			{
				if(wParam == VK_RETURN)
				{
					IMLOG("[quickSearchToolbarProc]: iMsg = WM_KEYUP, wParam = VK_RETURN");

					if(HIWORD(GetKeyState(VK_CONTROL)) == 0)
					{
						switch(GETINT(SzuKacz::CFG::quickSearchEnterAction))
						{
							case 1:
							{
								int pos = SendMessage(IMCtrl->konnektRoster, LVM_GETNEXTITEM, -1, LVNI_FOCUSED);
								if(pos != -1)
								{
									LVITEM lvi;
									lvi.mask = LVIF_PARAM;
									lvi.iItem = pos;
									ListView_GetItem(IMCtrl->konnektRoster, &lvi); 

									SzuKacz::openMsgWindow(((sUICnt*)lvi.lParam)->ID);
								}
								IMCtrl->quickSearchToolbarHide(0);
								break;
							}
							case 2:
							{
								int pos = SendMessage(IMCtrl->konnektRoster, LVM_GETNEXTITEM, -1, LVNI_FOCUSED);
								if(pos != -1)
								{
									LVITEM lvi;
									lvi.mask = LVIF_PARAM;
									lvi.iItem = pos;
									ListView_GetItem(IMCtrl->konnektRoster, &lvi); 

									SzuKacz::openInfoWindow(((sUICnt*)lvi.lParam)->ID);
								}
								IMCtrl->quickSearchToolbarHide(0);
								break;
							}
							case 3:
							{
								IMCtrl->quickSearchToolbarHide();
								break;
							}
						}
					}
					else
					{
						switch(GETINT(SzuKacz::CFG::quickSearchCtrlEnterAction))
						{
							case 1:
							{
								int pos = SendMessage(IMCtrl->konnektRoster, LVM_GETNEXTITEM, -1, LVNI_FOCUSED);
								if(pos != -1)
								{
									LVITEM lvi;
									lvi.mask = LVIF_PARAM;
									lvi.iItem = pos;
									ListView_GetItem(IMCtrl->konnektRoster, &lvi); 

									SzuKacz::openMsgWindow(((sUICnt*)lvi.lParam)->ID);
								}
								IMCtrl->quickSearchToolbarHide(0);
								break;
							}
							case 2:
							{
								int pos = SendMessage(IMCtrl->konnektRoster, LVM_GETNEXTITEM, -1, LVNI_FOCUSED);
								if(pos != -1)
								{
									LVITEM lvi;
									lvi.mask = LVIF_PARAM;
									lvi.iItem = pos;
									ListView_GetItem(IMCtrl->konnektRoster, &lvi); 

									SzuKacz::openInfoWindow(((sUICnt*)lvi.lParam)->ID);
								}
								IMCtrl->quickSearchToolbarHide(0);
								break;
							}
							case 3:
							{
								IMCtrl->quickSearchToolbarHide();
								break;
							}
						}
					}
				}
				SendMessage(IMCtrl->konnektWindow, iMsg, wParam, lParam);
				break;
			}
		}
		return CallWindowProc(IMCtrl->quickSearchToolbarOldProc, hWnd, iMsg, wParam, lParam);
	}

	//funkcja obs³uguj¹ca edit szybkiego wyszukiwania
	LRESULT CALLBACK quickSearchEditProc(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
	{
		static Controller* IMCtrl;
		if(!IMCtrl)
			IMCtrl = Controller::getInstance();

		switch(iMsg)
		{
			case WM_KEYUP:
			{
				SendMessage(IMCtrl->quickSearchToolbar, iMsg, wParam, lParam);
				break;
			}
		}
		return CallWindowProc(IMCtrl->quickSearchEditOldProc, hWnd, iMsg, wParam, lParam);
	}
}