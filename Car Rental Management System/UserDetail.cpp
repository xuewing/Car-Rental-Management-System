#include "UserDetail.h"
#include <string>
#include <iostream>
#include <cstdlib>

using namespace std;

//settle
void UserDetail::userOptions()
{
	system("cls");
	system("title Car Rental Management System");
	cout << "--- Welcome To Car Rental Management System ---" << endl << endl;
	cout << "--- User Home Page ---" << endl << endl << endl;
	cout << "1. Check Available Car" << endl;
	cout << "2. Make Car Booking" << endl;
	cout << "3. Make Payment" << endl;
	cout << "4. Write a Feedback" << endl;
	cout << "5. Check Booking history" << endl;
	cout << "6. Exit" << endl << endl;
}