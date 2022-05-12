#include "Admin.h"
#include <string>
#include <iostream>
using namespace std;

//settle
void Admin::adminOptions()
{
	system("cls");
	system("title Car Rental Management System");
	cout << "--- Welcome To Car Rental Management System ---" << endl << endl;
	cout << "--- Admin Home Page ---" << endl << endl << endl;
	cout << " A. Manage Car Details" << endl;
	cout << " 1. Add new car" << endl;
	cout << " 2. Delete car" << endl << endl;
	cout << " B. Manage Admin Details" << endl;
	cout << " 3. Add new admin" << endl << endl;
	cout << " C. Manage User Details" << endl;
	cout << " 4. Add new user" << endl;
	cout << " 5. Show all users" << endl;
	cout << " 6. Edit user details" << endl << endl;
	cout << " D. Manage Booking Details" << endl;
	cout << " 7. Add new booking" << endl;
	cout << " 8. Remove booking" << endl;
	cout << " 9. Find booking" << endl << endl;
	cout << " E. Others" << endl;
	cout << "10. Track payment" << endl;
	cout << "11. View feedback" << endl;
	cout << "12. Generate Statistic" << endl;
	cout << "13. Exit" << endl;
}