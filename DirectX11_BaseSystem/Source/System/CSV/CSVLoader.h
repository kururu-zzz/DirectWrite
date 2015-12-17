#ifndef _CSVLOADER
#define _CSVLOADER

#include "../Base/DXMath.h" 
#include <string>
#include <istream>
#include <fstream>
#include <assert.h>

using namespace DirectX;

namespace CSVLoader
{
	template<typename T_n> T_n LoadData(int rowNum, int columnNum, const std::string& FileName);
	//template<> std::string LoadData<std::string>(int rowNum, int columnNum, const std::string& FileName);
	int GetRowNum(const std::string& fileName);
	int GetColumnNum(const std::string& fileName,const int rowNum);
}

template<typename T_n> T_n CSVLoader::LoadData(int rowNum, int columnNum, const std::string& FileName)
{
	if ((rowNum >= 0) || (columnNum >= 0)){
		std::ifstream input;
		input.open(FileName.c_str());
		std::string str;
		for (int i = 0; i < rowNum; i++)
			std::getline(input, str);
		for (int i = 0; i < columnNum + 1; i++)
			std::getline(input, str, ',');
		assert(str != "");
		double num = std::atof(str.c_str());
		return static_cast<T_n>(num);
	}
	return 0;
}

/*
template<> const std::string& CSVLoader::LoadData<const std::string&>(int rowNum, int columnNum, const std::string& FileName)
{
	if ((rowNum >= 0) || (columnNum >= 0)){
		std::ifstream input;
		input.open(FileName.c_str());
		std::string str;
		for (int i = 0; i < rowNum; i++)
			std::getline(input, str);
		for (int i = 0; i < columnNum + 1; i++)
			std::getline(input, str, ',');
		return str;
	}
	return NULL;
}
*/
#endif