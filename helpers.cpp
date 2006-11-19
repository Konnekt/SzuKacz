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
			return strcmpi(item1, item2);
		}
		else
		{
			ListView_GetItemText(szuKacz::listview, idItem1, psort->col, item1, 256);
			ListView_GetItemText(szuKacz::listview, idItem2, psort->col, item2, 256);
			return (-strcmpi(item1, item2));
		}
	}

	//funkcja wywo³uj¹ca akcjê
	void CallAction(sUIAction act)
	{
		sUIActionNotify_2params akcja =	sUIActionNotify_2params();											
		akcja.act = act;
		akcja.code = ACTN_ACTION;
		ICMessage(IMI_ACTION_CALL,	(int)&akcja, 0);
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
			actionID = ICMessage(IMI_ACTION_GETID, IMIG_CNT,  i);
			if(!actionID)
				continue;
			if(ICMessage(IMI_ACTION_CALL, (int)&sUIActionNotify_2params(sUIAction(IMIG_CNT, actionID, cnt), ACTN_DEFAULT, 0, 0)))
				return actionID;
		}
		return -1;
	}
}