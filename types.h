#pragma once

namespace szuKacz
{
	struct SortStruct
	{
		int col;
		bool asc;
	};

	struct Result
	{
		Result(int Row, int FieldID)
		{
			this->cnt = GETCNTID(Row);
			this->display = GETCNTC(Row, CNT_DISPLAY);
			this->found_value = GETCNTC(Row, FieldID);
			this->net = GETCNTI(Row, CNT_NET);
		}

		int cnt;
		int row;
		std::string display;
		std::string found_value;
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