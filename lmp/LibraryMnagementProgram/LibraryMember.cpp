#include "pch.h"
#include "LibraryMember.h"

LibraryMember::LibraryMember()
{
	library_member_number = 0;
	name = _T(" ");
}
LibraryMember::LibraryMember(int _library_member_number, CString _name, CString _book_num, CString _book_name)
{
	library_member_number = _library_member_number;
	name = _name;

	CString   resToken;
	int curPos = 0;
	resToken = _book_num.TrimRight(_T(" ")).Tokenize(_T(","), curPos);
	book_num_vector.push_back(resToken);
	while (resToken != "")
	{
		resToken = _book_num.Tokenize(_T(","), curPos);
		if (resToken == "")
		{
			break;
		}
		book_num_vector.push_back(resToken);
	};

	curPos = 0;
	resToken = _book_name.TrimRight(_T(" ")).Tokenize(_T(","), curPos);
	book_name_vector.push_back(resToken);
	while (resToken != "")
	{
		resToken = _book_name.Tokenize(_T(","), curPos);
		if (resToken == "")
		{
			break;
		}
		book_name_vector.push_back(resToken);
	};


}
void LibraryMember::borrow_book(Book& book)
{
	CString book_number_cstr;
	book_number_cstr.Format(_T("%d"), book.get_book_number());
	book_name_vector.push_back(book.get_book_name());
	book_num_vector.push_back(book_number_cstr);
}

void LibraryMember::return_book(CString book_num)
{
	for (int i = 0; i < get_book_num_vector().size(); i++)
	{
		if (book_num_vector[i] == book_num)
		{
			book_num_vector.erase(book_num_vector.begin()+i);
			book_name_vector.erase(book_name_vector.begin() + i);

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


vector<CString>& LibraryMember::get_book_num_vector()
{
	return book_num_vector;
}

vector<CString>& LibraryMember::get_book_name_vector()
{
	return book_name_vector;
}
