#include "pch.h"
#include "Books.h"
Book::Book()
{
	rental_status = false;
	book_name = "-";
	book_number = 0;
	borrower = 0;
}
Book::Book(int _book_number, CString _book_name, bool _rental_status, int _borrower)
{
	book_name = _book_name;
	book_number = _book_number;
	rental_status = _rental_status;
	borrower = _borrower;
}
void Book::set_borrower(int _borrower)
{
	borrower = _borrower;
	rental_status = true;
}
CString Book::get_book_name()
{
	return book_name;
}
int Book::get_book_number()
{
	return book_number;
}