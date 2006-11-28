#include "stdafx.h"
#include "includes.h"

namespace SzuKacz
{
	//funkcja do sortowania itemów ListViewa
	int CALLBACK sort(LPARAM idItem1, LPARAM idItem2, LPARAM lParam)
	{
		char item1[256], item2[256];
		SortStruct* psort = (SortStruct*)lParam;

		if(psort->asc)
		{
			ListView_GetItemText(psort->listView, idItem1, psort->col, item1, 256);
			ListView_GetItemText(psort->listView, idItem2, psort->col, item2, 256);
			return strcoll(item1, item2);
		}
		else
		{
			ListView_GetItemText(psort->listView, idItem1, psort->col, item1, 256);
			ListView_GetItemText(psort->listView, idItem2, psort->col, item2, 256);
			return -strcoll(item1, item2);
		}
	}

	//funkcja wywo³uj¹ca akcjê
	void callAction(sUIAction act)
	{
		sUIActionNotify_2params akcja =	sUIActionNotify_2params();											
		akcja.act = act;
		akcja.code = ACTN_ACTION;
		ICMessage(IMI_ACTION_CALL, (int)&akcja, 0);
	}

	//funkcja wywo³uj¹ca akcjê
	void callAction(int parent, int id, int cnt)
	{
		SzuKacz::callAction(sUIAction(parent, id, cnt));
	}

	//funkcja pobieraj¹ca domyœln¹ akcje (by Aule)
	int getDefaultAction(int cnt)
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
	bool isInside(POINT pt, RECT r)
	{
		return (pt.x >= r.left && pt.x <= r.right) && (pt.y >= r.top && pt.y <= r.bottom);
	}

	//funkcja sprawdzaj¹ca, czy plugin o danym necie istnieje
	int pluginExists(int net, int type)
	{
		return Ctrl->ICMessage(IMC_FINDPLUG, net, type);
	}

	//funkcja otwieraj¹ca okno rozmowy dla danego kontaktu
	void openMsgWindow(int cnt)
	{
		if(SzuKacz::getDefaultAction(cnt) == IMIA_CNT_MSG)
		{
			SzuKacz::callAction(IMIG_CNT, IMIA_CNT_MSG, cnt);
		}
	}

	//funkcja otwieraj¹ca okno w³aœciwoœci dla danego kontaktu
	void openInfoWindow(int cnt)
	{
		SzuKacz::callAction(IMIA_NFO_DETAILS_NET, IMIA_MSG_INFO, cnt);
	}

	//funkcja odpalaj¹ca domyœln¹ akcjê
	void callDefaultAction(int cnt)
	{
		if(SzuKacz::getDefaultAction(cnt) != -1)
		{
			SzuKacz::callAction(IMIG_CNT, SzuKacz::getDefaultAction(cnt), cnt);
		}
	}
}