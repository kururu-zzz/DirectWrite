#include "CSVLoader.h"
#include <sstream>

namespace CSVLoader
{
	int GetRowNum(const std::string& fileName)
	{
		std::ifstream input;
		std::string str;
		input.open(fileName.c_str());
		int num = -1;
		do
		{
			std::getline(input, str);
			num++;
		} while (str != "");
		return num;
	}

	int GetColumnNum(const std::string& fileName, const int rowNum)
	{
		std::ifstream input;
		std::string str;
		input.open(fileName.c_str());
		for (int i = 0; i < rowNum; i++)
		{
			std::getline(input, str);
		}
		std::getline(input, str);
		std::stringstream ss(str);
		int num = 0;
		while(std::getline(ss, str, ','))
		{
			if (str == "")
				return num;
			num++;
		};

		return num;
	}
}