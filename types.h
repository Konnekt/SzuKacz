#pragma once

namespace SzuKacz
{
	struct SortStruct
	{
		HWND listView;
		int col;
		bool asc;
	};

	struct Result
	{
		Result(int row, int fieldId)
		{
			this->cnt = GETCNTID(row);
			this->display = GETCNTC(row, CNT_DISPLAY);
			this->foundValue = GETCNTC(row, fieldId);
			this->net = GETCNTI(row, CNT_NET);
		}

		int cnt;
		int row;
		std::string display;
		std::string foundValue;
		int net;
	};

	struct sUICnt
	{
		unsigned int net, status; //obie wartosc nie zawsze musza byc PRAWDZIWE!!!
		unsigned int ID;
	};

	//functor do sortowania resultów po display'u
	struct SortResult
	{
		bool operator()(Result& start, Result& end)
		{
			return strcoll(start.display.c_str(), end.display.c_str()) < 0;
		}
	};
}