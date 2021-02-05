#include "pch.h"
#include "accident_information.h"

AccidentInformation::AccidentInformation()
{
	si = "";
	gu = "";
}
AccidentInformation::AccidentInformation(string _si, string _gu)
{
	si = _si;
	gu = _gu;
}

void AccidentInformation::set_si_gu(string _si, string _gu)
{
	si = _si;
	gu = _gu;
}
void AccidentInformation::set_si(string _si)
{
	si = _si;
}

void AccidentInformation::upload_all_data()
{
	ifstream data("data.csv");
	string line;
	
	/*전체 문장 불러오는 부분*/
	while (getline(data, line))
	{
		lines.push_back(line);
	
	}

	/*각 문장 을 , 로 구분하여 하나씩 cell로
	stringstream lineStream(line);
	string cell;
	while (getline(lineStream, cell, ','))
	{

	}
	*/
}
vector<string> AccidentInformation::get_lines()
{
	return lines;
}