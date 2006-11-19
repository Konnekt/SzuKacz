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
		int cnt;
		std::string display;
		std::string found_value;
		int net;
	};
}