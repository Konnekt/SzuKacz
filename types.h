/*
 * License - http://www.gnu.org/licenses/lgpl.txt
 */

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

	typedef std::list<SzuKacz::Result> tResults;

	struct sUICnt
	{
		unsigned int net, status; //obie wartosc nie zawsze musza byc PRAWDZIWE!!!
		unsigned int ID;
	};

	//functor do sortowania result�w po display'u
	struct SortResult
	{
		bool operator()(Result& start, Result& end)
		{
			return _stricoll(start.display.c_str(), end.display.c_str()) < 0;
		}
	};
}