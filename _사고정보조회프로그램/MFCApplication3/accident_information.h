
#ifndef ACCIDENT_INFORMATION_H
#define ACCIDENT_INFORMATION_H 
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
using namespace std;
class AccidentInformation
{
private:
	vector<string> lines;
	string si, gu;

public:
	AccidentInformation();
	AccidentInformation(string _si, string _gu);
	void set_si_gu(string _si, string _gu);
	void set_si(string _si);
	void upload_all_data();
	vector<string> get_lines();

};
#endif // ACCIDENT_INFORMATION_CHECK_H