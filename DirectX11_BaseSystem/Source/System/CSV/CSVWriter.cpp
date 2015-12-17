#include "CSVWriter.h"
#include <iostream>
#include <fstream>

void CSVWriter::InitData(const std::string& FileName)
{
	std::ofstream output;
	output.open(FileName.c_str(), std::ios::trunc);
	return;
}

void CSVWriter::LineFeed(const std::string& FileName)
{
	std::ofstream output;
	output.open(FileName.c_str(), std::ios::out | std::ios::app);
	output << std::endl;
	return;
}