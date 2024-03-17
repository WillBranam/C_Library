//#include "BST.hpp"
//#include "Book.hpp"
#include "Library.hpp"
#include <iostream>
using namespace std;

int main() {
	 //Testing book comparisons
	 Book b1("Acorns","Shmoe, Joe", 1972, "Science Books",12345,3.5);
//	 Book b2("Birch Trees","Shmoe, Joe", 1999, "Science Books",34567,4.0);
//	 Book b3("Dogs Are My Best Friend","David, Alex",2001, "Books for Children",22222,4.0);
//	 cout << (b1 < b1);
//	 cout << (b1 < b2);
//	 cout << (b1 < b3);
//	 cout << (b1 == b1);
//	 cout << (b1 == b2);
//	 cout << (b1 != b3);
//	 cout << (b1 > b1);
//	 cout << (b1 > b2);
//	 cout << (b1 > b3);
//	 cout << (b1 <= b1);
//	 cout << (b1 <= b2);
//	 cout << (b1 <= b3);
//	 cout << (b1 >= b1);
//	 cout << (b1 >= b2);
//	 cout << (b1 >= b3);

	Library library("/Users/williambranam/Desktop/School 2023-2024/Data Structures/BSTLibrary 2/full_library.txt");
	library.menu();


	return 0;
}
