#ifndef _CSVWRITER
#define _CSVWRITER

#include <string>

namespace CSVWriter
{
	void InitData(const std::string& FileName);
	void LineFeed(const std::string& FileName);
	template<typename T_n> void WriteData(T_n Data,const std::string& FileName);
}

template<typename T_n> void CSVWriter::WriteData(T_n Data, const std::string& FileName)
{
	std::ofstream output;
	output.open(FileName.c_str(), std::ios::out|std::ios::app);
	std::string str;
	output << Data << ',' ;
	return;
}

#endif