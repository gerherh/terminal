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
	
	/*��ü ���� �ҷ����� �κ�*/
	while (getline(data, line))
	{
		lines.push_back(line);
	
	}

	/*�� ���� �� , �� �����Ͽ� �ϳ��� cell��
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