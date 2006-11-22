#include "stdafx.h"
#include "includes.h"

namespace szuKacz
{
	//funkcja przeszukuj¹ca listê kontaktów i zwracaj¹ca tablicê z wynikami
	std::list<Result> findContact(int field, std::string &toMatch, int relationType, bool CaseSensitive, bool FromList, bool save)
	{
		IMLOG("[findContact]: field = %i, toMatch = %s, relationType = %i, CaseSensitive = %i, FromList = %i, save = %i", field, toMatch.c_str(), relationType, CaseSensitive, FromList, save);
		
		std::list<Result> results;

		//zapisujemy do MRU
		if(save)
		{
			//zapis
			szuKacz::MRUList->append(toMatch);

			//reset ComboBoxa z has³ami
			{
				SendMessage(szuKacz::edit, CB_RESETCONTENT, 0, 0);
				tMRUlist list = MRUList->get();
				COMBOBOXEXITEM cbei;
				cbei.mask = CBEIF_TEXT;
				cbei.iItem = -1;
				for(tMRUlist::iterator i = list.begin(); i != list.end(); i++)
				{
					if(i->size())
					{
						cbei.pszText = (LPSTR)i->c_str();
						SendMessage(szuKacz::edit, CBEM_INSERTITEM, 0, (LPARAM)&cbei);
					}
				}
			}
		}

		//sprawdzamy, czy mamy uwa¿aæ na wielkoœæ znaków i jeœli tak lowercasujemy stringa
		if(!CaseSensitive)
		{
			transform(toMatch.begin(), toMatch.end(), toMatch.begin(), tolower);
		}

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

		if(FromList)
		{
			const int ListCount = ListView_GetItemCount(szuKacz::CNTListWindow);
			LVITEM lvi;
			lvi.iSubItem = 0;
			lvi.mask = LVIF_PARAM;
			int i;
			for(int i2 = 0; i2 < ListCount; i2++)
			{
				lvi.iItem = i2;
				ListView_GetItem(szuKacz::CNTListWindow, &lvi);
				i = GETCNTPOS(((sUICnt*)(lvi.lParam))->ID);

				std::string read_result = GETCNTC(i, field);
				
				//sprawdzamy, czy mamy uwa¿aæ na wielkoœæ znaków i jeœli tak lowercasujemy stringa
				if(!CaseSensitive)
				{
					transform(read_result.begin(), read_result.end(), read_result.begin(), tolower);
				}

				switch (relationType)
				{
					case 0: //zawiera
					{
						if(read_result.find(toMatch) != std::string::npos)
						{
							results.push_back(szuKacz::Result(i, field));
						}
						break;
					}
					case 1: //równe
					{
						if(read_result == toMatch)
						{
							results.push_back(szuKacz::Result(i, field));
						}
						break;
					}
					case 2: //nie równe
					{
						if(read_result != toMatch)
						{
							results.push_back(szuKacz::Result(i, field));
						}
						break;
					}
					case 3: //zaczyna siê od
					{
						if(read_result.find(toMatch) == 0)
						{
							results.push_back(szuKacz::Result(i, field));
						}
						break;
					}
					case 4: //koñczy siê na
					{
						std::string::size_type end = read_result.size() - toMatch.size();
						if(read_result.rfind(toMatch) == end && read_result.rfind(toMatch) != std::string::npos)
						{
							results.push_back(szuKacz::Result(i, field));
						}
						break;
					}
					case 5: //nie zawiera
					{
						if(read_result.find(toMatch) == std::string::npos)
						{
							results.push_back(szuKacz::Result(i, field));
						}
						break;
					}
					case 6: //wyra¿enie regularne
					{
						try
						{
							boost::regex expression(toMatch, CaseSensitive ? 0 : boost::regex::icase);
							if(boost::regex_search(read_result, expression))
							{
								results.push_back(szuKacz::Result(i, field));
							}
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
			//iterujemy siê przez listê kontaktów i dodajemy pasuj¹ce kontakty do tablicy
			for(int i = 1; i < ICMessage(IMC_CNT_COUNT); i++)
			{
				std::string read_result = GETCNTC(i, field);

				//sprawdzamy, czy mamy uwa¿aæ na wielkoœæ znaków i jeœli tak lowercasujemy stringa
				if(!CaseSensitive)
				{
					transform(read_result.begin(), read_result.end(), read_result.begin(), tolower);
				}

				switch (relationType)
				{
					case 0: //zawiera
					{
						if(read_result.find(toMatch) != std::string::npos)
						{
							results.push_back(szuKacz::Result(i, field));
						}
						break;
					}
					case 1: //równe
					{
						if(read_result == toMatch)
						{
							results.push_back(szuKacz::Result(i, field));
						}
						break;
					}
					case 2: //nie równe
					{
						if(read_result != toMatch)
						{
							results.push_back(szuKacz::Result(i, field));
						}
						break;
					}
					case 3: //zaczyna siê od
					{
						if(read_result.find(toMatch) == 0)
						{
							results.push_back(szuKacz::Result(i, field));
						}
						break;
					}
					case 4: //koñczy siê na
					{
						std::string::size_type end = read_result.size() - toMatch.size();
						if(read_result.rfind(toMatch) == end && read_result.rfind(toMatch) != std::string::npos)
						{
							results.push_back(szuKacz::Result(i, field));
						}
						break;
					}
					case 5: //nie zawiera
					{
						if(read_result.find(toMatch) == std::string::npos)
						{
							results.push_back(szuKacz::Result(i, field));
						}
						break;
					}
					case 6: //wyra¿enie regularne
					{
						try
						{
							boost::regex expression(toMatch, CaseSensitive ? 0 : boost::regex::icase);
							if(boost::regex_search(read_result, expression))
							{
								results.push_back(szuKacz::Result(i, field));
							}
							break;
						}
						catch(...)
						{
						}
					}
				}
			}
		}

		results.sort(szuKacz::SortResult());

		//odblokowujemy listê kontaktów
		Ctrl->DTunlock(DTCNT,-1);

		return results;
	}

	//funkcja obs³uguj¹ca g³ówne okno
	LRESULT CALLBACK KonnektMainWindowProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
	{
		int ReturnedProcValue = CallWindowProc(old_main_wnd_proc, hwnd, iMsg, wParam, lParam);

		if(!szuKacz::QuickSearchToolbarVisible)
			return ReturnedProcValue;

		switch(iMsg)
		{
			case WM_SIZE:
			case WM_MOVE:
			case WM_WINDOWPOSCHANGED:
			{
				if(IsWindowVisible(szuKacz::KonnektMainWindow))
				{
					szuKacz::QuickSearchToolbarRefresh(szuKacz::QuickSearchToolbarMoved);
				}
				else
				{
					szuKacz::QuickSearchToolbarHide(0);
				}
				break;
			}
			case WM_NOTIFY:
			{
				switch(((LPNMHDR)lParam)->code)
				{
					case TBN_DROPDOWN:
					{
						IMLOG("[KonnektMainWindowProc]: iMsg = WM_NOTIFY, lParam->code = TBN_DROPDOWN, wParam = %i, lParam = %i", wParam, lParam);

						LPNMTOOLBAR nmt = (LPNMTOOLBAR)lParam;
						if(nmt->hdr.hwndFrom == szuKacz::QuickSearchToolbar)
						{
							POINT pt;
							pt.x = nmt->rcButton.right;
							pt.y = nmt->rcButton.top;
							ClientToScreen(szuKacz::QuickSearchToolbar, &pt);
							if(nmt->iItem == 1)
							{
								IMessage(&sIMessage_UIMakePopup(sUIAction(0, szuKacz::Acts::CriterionMenu), TPM_LEFTBUTTON|TPM_RIGHTBUTTON|TPM_RIGHTALIGN|TPM_BOTTOMALIGN, pt.x, pt.y, 0, szuKacz::KonnektMainWindow));
							}
							else if(nmt->iItem == 2)
							{
								IMessage(&sIMessage_UIMakePopup(sUIAction(0, szuKacz::Acts::MethodMenu), TPM_LEFTBUTTON|TPM_RIGHTBUTTON|TPM_RIGHTALIGN|TPM_BOTTOMALIGN, pt.x, pt.y, 0, szuKacz::KonnektMainWindow));
							}
							return TBDDRET_DEFAULT;
						}
					}
				}
				break;
			}
			case WM_COMMAND:
			{
				if(lParam == (LPARAM)szuKacz::QuickSearchEdit && HIWORD(wParam) == EN_CHANGE)
				{
					IMLOG("[KonnektMainWindowProc]: iMsg = WM_COMMAND, lParam = QuickSearchEdit, HIWORD(wParam) = EN_CHANGE, wParam = %i, lParam = %i", wParam, lParam);

					delete szuKacz::CurrentResult;
					szuKacz::CurrentResult = 0;
					szuKacz::QuickSearchResults.clear();
					ListView_SetItemState(szuKacz::CNTListWindow, -1, 0, LVIS_SELECTED|LVIS_FOCUSED);
					szuKacz::QuickSearchToolbarRefresh(0);

					char buff[500];
					SendMessage(szuKacz::QuickSearchEdit, WM_GETTEXT, 500, (LPARAM)&buff);
					if(strlen(buff) == 0)
						break;
					std::string text = buff;
					int field = GETINT(szuKacz::Config::Criterion);
					int method = GETINT(szuKacz::Config::Method);
					int CaseSensitive = GETINT(szuKacz::Config::CaseSensitive);

					szuKacz::QuickSearchResults = szuKacz::findContact(field, text, method, CaseSensitive);
					if(szuKacz::QuickSearchResults.size())
					{
						szuKacz::CurrentResult = new std::list<szuKacz::Result>::iterator(szuKacz::QuickSearchResults.begin());
						SelectCNT(szuKacz::CNTListWindow, (*szuKacz::CurrentResult)->cnt);
					}
				}
				else if(lParam == (LPARAM)szuKacz::QuickSearchToolbar)
				{
					switch(LOWORD(wParam))
					{
						case 3:
						{
							IMLOG("[KonnektMainWindowProc]: iMsg = WM_COMMAND, LOWORD(wParam) = 3, lParam = QuickSearchToolbar");
							if(szuKacz::CurrentResult)
							{
								if((*szuKacz::CurrentResult) == szuKacz::QuickSearchResults.begin())
								{
									delete szuKacz::CurrentResult;
									szuKacz::CurrentResult = new std::list<szuKacz::Result>::iterator((szuKacz::QuickSearchResults.end()));
								}
								(*szuKacz::CurrentResult)--;
								ListView_SetItemState(szuKacz::CNTListWindow, -1, 0, LVIS_SELECTED|LVIS_FOCUSED);
								SelectCNT(szuKacz::CNTListWindow, (*szuKacz::CurrentResult)->cnt);
						
							}
							break;
						}
						case 4:
						{
							IMLOG("[KonnektMainWindowProc]: iMsg = WM_COMMAND, LOWORD(wParam) = 4, lParam = QuickSearchToolbar");
							if(szuKacz::CurrentResult)
							{
								(*szuKacz::CurrentResult)++;
								if((*szuKacz::CurrentResult) == szuKacz::QuickSearchResults.end())
								{
									delete szuKacz::CurrentResult;
									szuKacz::CurrentResult = new std::list<szuKacz::Result>::iterator(szuKacz::QuickSearchResults.begin());
								}
								ListView_SetItemState(szuKacz::CNTListWindow, -1, 0, LVIS_SELECTED|LVIS_FOCUSED);
								SelectCNT(szuKacz::CNTListWindow, (*szuKacz::CurrentResult)->cnt);
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
				{
					szuKacz::QuickSearchToolbarHide(1);
				}
				break;
			}
		}

		return ReturnedProcValue;
	}
}