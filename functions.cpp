#include "includes.h"

namespace szuKacz
{
	std::vector<Result> szuKacz::findContact(int fieldID, std::string &toMatch, int relationType, bool casesensitive)
	{
		IMLOG("[findContact]: fieldID = %i, toMatch = %s, relationType = %i, casesensitive = %i", fieldID, toMatch.c_str(), relationType, casesensitive);
		
		std::vector<Result> results;
		szuKacz::Result new_found;

		if(!casesensitive)
		{
			transform(toMatch.begin(), toMatch.end(), toMatch.begin(), tolower);
		}

		Ctrl->DTlock(DTCNT, -1);

		for(int i = 1; i < ICMessage(IMC_CNT_COUNT); i++)
		{
			std::string read_result = GETCNTC(i, fieldID);
			if(!casesensitive)
			{
				transform (read_result.begin(),read_result.end(), read_result.begin(), tolower);
			}
			switch (relationType)
			{
				case 0: //zawiera
				{
					if(read_result.find(toMatch) != std::string::npos)
					{
						new_found.cnt = i;
						new_found.display = GETCNTC(i, CNT_DISPLAY);
						new_found.found_value = GETCNTC(i, fieldID);
						new_found.net = GETCNTI(i, CNT_NET);
						results.push_back(new_found);
					}
					break;
				}
				case 1: //równe
				{
					if(read_result == toMatch)
					{
						new_found.cnt = i;
						new_found.display = GETCNTC(i, CNT_DISPLAY);
						new_found.found_value = GETCNTC(i, fieldID);
						new_found.net = GETCNTI(i, CNT_NET);
						results.push_back(new_found);
					}
					break;
				}
				case 2: //nie równe
				{
					if(read_result != toMatch)
					{
						new_found.cnt = i;
						new_found.display = GETCNTC(i, CNT_DISPLAY);
						new_found.found_value = GETCNTC(i, fieldID);
						new_found.net = GETCNTI(i, CNT_NET);
						results.push_back(new_found);
					}
					break;
				}
				case 3: //zaczyna siê od
				{
					if(read_result.find(toMatch) == 0)
					{
						new_found.cnt = i;
						new_found.display = GETCNTC(i, CNT_DISPLAY);
						new_found.found_value = GETCNTC(i, fieldID);
						new_found.net = GETCNTI(i, CNT_NET);
						results.push_back(new_found);
					}
					break;
				}
				case 4: //koñczy siê na
				{
					std::string::size_type end = read_result.size() - toMatch.size();
					if(read_result.rfind(toMatch) == end && read_result.rfind(toMatch) != std::string::npos)
					{
						new_found.cnt = i;
						new_found.display = GETCNTC(i, CNT_DISPLAY);
						new_found.found_value = GETCNTC(i, fieldID);
						new_found.net = GETCNTI(i, CNT_NET);
						results.push_back(new_found);
					}
					break;
				}
				case 5: //nie zawiera
				{
					if(read_result.find(toMatch) == std::string::npos)
					{
						new_found.cnt = i;
						new_found.display = GETCNTC(i, CNT_DISPLAY);
						new_found.found_value = GETCNTC(i, fieldID);
						new_found.net = GETCNTI(i, CNT_NET);
						results.push_back(new_found);
					}
					break;
				}
				case 6: //wyra¿enie regularne
				{
					try
					{
						boost::regex expression(toMatch, casesensitive ? 0 : boost::regex::icase);
						if(boost::regex_search(read_result, expression))
						{
							new_found.cnt = i;
							new_found.display = GETCNTC(i, CNT_DISPLAY);
							new_found.found_value = GETCNTC(i, fieldID);
							new_found.net = GETCNTI(i, CNT_NET);
							results.push_back(new_found);
						}
						break;
					}
					catch(...)
					{
					}
				}
			}
		}

		Ctrl->DTunlock(DTCNT,-1);
		return results;
	}
}