#include "pch.h"
#include "LibraryMember.h"

LibraryMember::LibraryMember()
{
	library_member_number = 0;
	name = _T(" ");
}
LibraryMember::LibraryMember(int _library_member_number, CString _name, int _book_num, CString _book_name)
{
	library_member_number = _library_member_number;
	name = _name;
	book_num_name_map.insert(make_pair(_book_num, _book_name));

}
void LibraryMember::borrow_book(Book& book)
{
	book_num_name_map.insert(make_pair(book.get_book_number(), book.get_book_name()));
}

void LibraryMember::return_book(CString book_name)
{
	map<int, string>::iterator iter;

	for (auto it = book_num_name_map.begin(); it != book_num_name_map.end(); it++) {
		if (it->second == book_name)
		{
			book_num_name_map.erase(it->first);
		}
	}
}

int LibraryMember::get_member_num()
{
	return library_member_number;
}
CString LibraryMember::get_member_name()
{
	return name;
}
map<int, CString>& LibraryMember::get_book_num_name_map()
{
	return book_num_name_map;
}

