#pragma once
#include "Books.h"
#include <string>
#include <map>
using namespace std;
class LibraryMember
{
private:
	int library_member_number;
	CString name;
	map<int, CString> book_num_name_map;
public:
	LibraryMember();
	LibraryMember(int _library_member_number, CString _name, int _book_num, CString _book_name);
	void borrow_book(Book& book);
	void return_book(CString book_name);
	
	int get_member_num();
	CString get_member_name();
	map<int, CString>& get_book_num_name_map();

	
};



