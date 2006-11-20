#include "stdafx.h"
#include "includes.h"

namespace szuKacz
{
	//funkcja do sortowania itemów ListViewa
	int CALLBACK Sort(LPARAM idItem1, LPARAM idItem2, LPARAM lParam)
	{
		char item1[256], item2[256];
		SortStruct* psort = (SortStruct*)lParam;

		if(psort->asc)
		{
			ListView_GetItemText(szuKacz::listview, idItem1, psort->col, item1, 256);
			ListView_GetItemText(szuKacz::listview, idItem2, psort->col, item2, 256);
			return strcoll(item1, item2);
		}
		else
		{
			ListView_GetItemText(szuKacz::listview, idItem1, psort->col, item1, 256);
			ListView_GetItemText(szuKacz::listview, idItem2, psort->col, item2, 256);
			return -strcoll(item1, item2);
		}
	}

	//funkcja wywo³uj¹ca akcjê
	void CallAction(sUIAction act)
	{
		sUIActionNotify_2params akcja =	sUIActionNotify_2params();											
		akcja.act = act;
		akcja.code = ACTN_ACTION;
		ICMessage(IMI_ACTION_CALL, (int)&akcja, 0);
	}

	//funkcja wywo³uj¹ca akcjê
	void CallAction(int parent, int id, int cnt)
	{
		CallAction(sUIAction(parent, id, cnt));
	}

	//funkcja pobieraj¹ca domyœln¹ akcje (by Aule)
	int GetDefaultAction(int cnt)
	{
		int actionCount = ICMessage(IMI_GROUP_ACTIONSCOUNT, (int)&sUIAction(IMIG_MAINWND, IMIG_CNT, cnt));
		int actionID = 0;
		for(int i=0;i<actionCount;i++)
		{
			actionID = ICMessage(IMI_ACTION_GETID, IMIG_CNT, i);
			if(!actionID)
				continue;
			if(ICMessage(IMI_ACTION_CALL, (int)&sUIActionNotify_2params(sUIAction(IMIG_CNT, actionID, cnt), ACTN_DEFAULT, 0, 0)))
				return actionID;
		}
		return -1;
	}

	//funkcja sprawdzaj¹ca, czy punt znajduje siê w kwadracie
	bool IsInside(POINT pt, RECT r)
	{
		return (pt.x >= r.left && pt.x <= r.right) && (pt.y >= r.top && pt.y <= r.bottom);
	}

	//funkcja zaznaczaj¹ca na liœcie kontakt o podanym ID
	void SelectCNT(HWND ListView, int CNT)
	{
		szuKacz::QuickSearchToolbarRefresh(0);

		const int ListCount = ListView_GetItemCount(ListView);
		LVITEM lvi;
		lvi.iSubItem = 0;
		lvi.mask = LVIF_PARAM;
		for(int i = 0; i < ListCount; i++)
		{
			lvi.iItem = i;
			ListView_GetItem(ListView, &lvi);
			if(((sUICnt*)(lvi.lParam))->ID == CNT)
			{
				ListView_SetItemState(ListView, i, LVIS_SELECTED|LVIS_FOCUSED, LVIS_SELECTED|LVIS_FOCUSED);
				RECT rc;
				RECT rc2;
				GetWindowRect(szuKacz::CNTListWindow, &rc);
				ListView_GetItemRect(ListView, i, (LPARAM)&rc2, LVIR_SELECTBOUNDS);
				if(rc2.bottom > rc.bottom - rc.top - 22 && i == ListCount - 1 && !ListView_IsGroupViewEnabled(szuKacz::CNTListWindow))
				{
					SendMessage(szuKacz::CNTListWindow, WM_VSCROLL, SB_BOTTOM, 0);
					szuKacz::QuickSearchToolbarRefresh(1);
				}
				else if(rc2.bottom > rc.bottom - rc.top - 22)
				{
					ListView_Scroll(ListView, 0, rc2.bottom - (rc.bottom - rc.top - 22));
					ListView_Scroll(ListView, 0, 1);
				}
				else if(rc2.top < 0)
				{
					ListView_Scroll(ListView, 0, rc2.top);
					ListView_Scroll(ListView, 0, -1);
				}
				return;
			}
		}
	}

	//funkcja sprawdzaj¹ca, czy plugin o danym necie istnieje
	int PluginExists(int net, int type)
	{
		return(Ctrl->ICMessage(IMC_FINDPLUG, net, type));
	}
}