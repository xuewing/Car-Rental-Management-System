#include "UserDetail.h"
#include "Admin.h"
#include <iostream>
#include <string>
#include<cstdio>
#include<fstream>
#include<sstream>
#include<conio.h>
#include<windows.h>
#include <mysql.h>
#include <chrono>
#include<stdlib.h>
using namespace std;

int qstate;
MYSQL* conn;
MYSQL_ROW row;
MYSQL_RES* res;
string strid;
string strpss;
char exitSecurity;
char choose;
const int WHITE = 15;

class db_response
{
public:
	static void ConnectionFunction()
	{
		conn = mysql_init(0);
		if (conn)
		{
			cout << "Database Connected" << endl;
			cout << "Press any key to continue..." << endl;
			system("cls");
		}
		else
		{
			cout << "Failed To Connect!" << mysql_errno(conn) << endl;
		}

		conn = mysql_real_connect(conn, "localhost", "root", "", "dbcrms", 3306, NULL, 0);
		if (conn)
		{
			cout << "Database Connected To MySql" << conn << endl;
			cout << "Press any key to continue..." << endl;
			//getch();
			system("cls");
		}
		else
			cout << "Failed To Connect!" << mysql_errno(conn) << endl;
	}
};

void timer(int);
void userRegister();
void forgotPassword(); 
void clearScreen(int characterLength);
void changeColour(int colour);
void load();
void load_CHECK();
void load_EXIT();

void load()
{
	int timer = 5 + rand() % 20;
	int r, c, q;
	cout << "BOOTING UP...";
	for (r = 1; r <= timer; r++)
	{
		for (q = 0; q <= 100000000; q++);//to display the character slowly
		printf("%c", 177);
	}
	Sleep(500);
	system("cls");
}

void load_CHECK()
{
	system("cls");
	int timer = rand() % 5 + 1;
	int r, c, q;
	printf("LOG IN...");
	for (r = 1; r <= timer; r++)
	{
		for (q = 0; q <= 100000000; q++);//to display the character slowly
		printf("%c", 177);
	}
	Sleep(500);
	system("cls");
}

void load_EXIT()
{
	system("cls");
	int r, c, q;
	int timer = rand() % 5 + 1;
	printf("LOGGING OFF...");
	for (r = 1; r <= timer; r++)
	{
		for (q = 0; q <= 100000000; q++);//to display the character slowly
		printf("%c", 177);
	}
	Sleep(500);
	system("cls");
}

void timer(int sec)
{
	Sleep(sec * 1000);
}

void clearScreen(int characterLength) {
	for (int i = 0; i < characterLength; i++) {
		cout << "\b";
	}
}

void changeColour(int colour)
{
	HANDLE hConsole;

	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, colour);
}

void showBlinkingLights() {
	cout << "   CAR ";
	timer(1);

	cout << " RENTAL ";
	timer(1); 

	cout << " MANAGEMENT ";
	timer(1);

	cout << " SYSTEM  " << endl;
	timer(1);

	changeColour(WHITE);
}

int main() 
{
	system("cls");
	system("title Car Rental Management System");
	db_response::ConnectionFunction();
	load();
	int option = 0;
	char exitSecurity;
	cout << " ***************************************" << endl << endl;
	showBlinkingLights();
	cout << endl;
	cout << " ***************************************" << endl << endl << endl << endl;
	timer(1);
	qstate = mysql_query(conn, "SELECT COUNT(booking_id) from booking");
	if (!qstate)
	{
		res = mysql_store_result(conn);
		while ((row = mysql_fetch_row(res)))
		{
			cout << " ---- CURRENTLY, WE HAVE " << row[0] <<" BOOKINGS MADE BY OUR BELOVED CUSTOMERS !" << endl << endl;
		}
	}
	timer(1);
	cout << " _____ Welcome to the Login Page ______" << endl;
	cout << " Please choose your identity: " << endl;
	cout << " 1. User " << endl;
	cout << " 2. Admin" << endl;
	cout << " 3. Register" << endl;
	cout << " 4. Forgot Password" << endl;
	cout << " 5. Exit" << endl << endl;
	cout << "   Enter your choice: ";
	cin >> option;

	switch (option)
	{
	case 1:
	{
		UserDetail user;
		user.loginUser();
		break;
	}
	case 2:
	{
		Admin ad;
		ad.loginAdmin();
		break;
	}
	case 3:
	{
		userRegister();
		break;
	}
	case 4:
	{
		forgotPassword();
		break;
	}
	case 5:
	ExitProgram:
		cout << "Program terminating. Are you sure to exit? (Y/N):";
		cin >> exitSecurity;
		if (exitSecurity == 'Y' || exitSecurity == 'y')
		{
			load_EXIT();
			return 0;
		}
		else if (exitSecurity == 'N' || exitSecurity == 'n')
		{
			system("cls");
			main();
		}
		else
		{
			cout << "Please choose after read the corresponding line." << endl;
			goto ExitProgram;
		}
	default:
		cout << "Please choose between option 1 - 5. Press Enter to continue..." << endl;
		system("cls");
		main();
		break;
	}
	return 0;
}

void userRegister()
{
	system("cls");

	string user_id, password, contact_num, address, email, name; 

	cout << " ***************************************" << endl << endl;
	cout << "       CAR RENTAL MANAGEMENT SYSTEM    " << endl << endl;
	cout << " ***************************************" << endl << endl << endl << endl;
	cout << "--- User Registration ---" << endl;
	cin.ignore(1, '\n');
	cout << "User ID: ";
	getline(cin, user_id);
	cout << "Name: ";
	getline(cin, name);
	cout << "Password: ";
	getline(cin, password);
	cout << "Contact number: ";
	getline(cin, contact_num);
	cout << "Address: ";
	getline(cin, address);
	cout << "Email: ";
	getline(cin, email);

	string checkUser_query = "select * from userdetail where user_id = '" + user_id+ "' limit 1";
	const char* cu = checkUser_query.c_str();
	qstate = mysql_query(conn, cu);

	if (!qstate)
	{
		res = mysql_store_result(conn);
		if (res->row_count == 1)
		{
			cout << "User ID is already exist. Press Enter to Try Again...";
			_getch();
			userRegister();
		}
		else
		{
			string insert_query = "insert into userdetail (user_id, name, password, contact_num, address, email) values ('" + user_id + "','" + name + "','" + password + "','" + contact_num + "','" + address + "','" + email + "') ";
			const char* q = insert_query.c_str();
			qstate = mysql_query(conn, q);

			if (!qstate)
			{
				cout << endl << "You have been registered. Press Enter to continue..." << endl;
			}
			else
			{
				cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
			}
			cout << "Press 'm' to Menu and any other key to Exit: ";
			cin >> choose;
			if (choose == 'M' || choose == 'm')
			{
				main();
			}
			else
			{
				exit(0);
			}
			system("cls");
		}
	}
}

void UserDetail::loginUser()
{
	system("cls");
	system("title Car Rental Management System");
	db_response::ConnectionFunction();
	bool loginuser = false;
	string user_id, password;
	string user[5000];
	char c{};
	bool HaveException = false;
	bool NotInDatabase = false;
	int indexForUserId = 0;
	cout << " ***************************************" << endl << endl;
	cout << "       CAR RENTAL MANAGEMENT SYSTEM    " << endl << endl;
	cout << " ***************************************" << endl << endl << endl << endl;
	cout << "--- Welcome to User Login Page ---" << endl;
	
	cout << "   User Id: ";
	cin >> user_id;
	cout << "   Password: ";
	while (c != '\r')
	{
		c = _getch();
		if (c == 0)
		{
			switch (_getch())
			{
			default:
				break;
			};
		}
		else if (c == '\b')  
		{
			if (password.size() != 0)  
			{
				cout << "\b \b";
				password.erase(password.size() - 1, 1);
			}
			continue;
		}
		else if (c <= '9' && c >= '0' || c >= 'a' && c <= 'z' || c >= 'A' && c <= 'Z')  
		{
			password += c;
			cout << "*";
		}
		else
			continue;
	}

	cout << endl;
	
	string findbyid_query = "select * from userdetail where user_id = '" + user_id + "' and password = '" + password + "'";
	const char* qi = findbyid_query.c_str();
	qstate = mysql_query(conn, qi);
	if (!qstate)
		{
			res = mysql_store_result(conn);
			if (res->row_count == 1)
			{
				while ((row = mysql_fetch_row(res)))
				{
					cout << row[1] << " " << "(" << user_id << ")" << " " << "login success!!!" << endl;
					timer(1);
					load_CHECK();
					UserDetail::user();
				}
			}
			else
			{
				char c;
				cout << " ***Invalid id or password. Want to try again? (y/n): ";
				cin >> c;
				if (c == 'y' || c == 'Y')
					loginUser();
				else
					main();
			}
		}
		else
		{
			cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
		}
			
}

void Admin::loginAdmin()
{
	system("cls");
	system("title Car Rental Management System");
	db_response::ConnectionFunction();
	bool loginadmin = false;
	string admin_id, password;
	string admin[5000];
	char c{};
	bool HaveException = false;
	bool NotInDatabase = false;
	int indexForAdminId = 0;
	cout << " ***************************************" << endl << endl;
	cout << "       CAR RENTAL MANAGEMENT SYSTEM    " << endl << endl;
	cout << " ***************************************" << endl << endl << endl << endl;
	cout << "--- Welcome to Admin Login Page ---" << endl;
	cout << "   Admin Id: ";
	cin >> admin_id;
	cout << "   Password: ";
	while (c != '\r')
	{
		c = _getch();
		if (c == 0)
		{
			switch (_getch())
			{
			default:
				break;
			};
		}
		else if (c == '\b')   
		{
			if (password.size() != 0) 
			{
				cout << "\b \b";
				password.erase(password.size() - 1, 1);
			}
			continue;
		}
		else if (c <= '9' && c >= '0' || c >= 'a' && c <= 'z' || c >= 'A' && c <= 'Z')  
		{
			password += c;
			cout << "*";
		}
		else
			continue;
	}

	cout << endl;
	
	string findbyid_query = "select * from admin where admin_id = '" + admin_id + "' and password= '" + password + "'";
	const char* qi = findbyid_query.c_str();
	qstate = mysql_query(conn, qi);
	if (!qstate)
	{
		res = mysql_store_result(conn);
		if (res->row_count == 1)
		{
			while ((row = mysql_fetch_row(res)))
			{
				cout << row[1] << " " << "(" << admin_id << ")" << " " << "login success" << endl;
				timer(1);
				load_CHECK();
				Admin::admin();
			}
		}
		else
		{
			char c;
			cout << " ***Invalid Admin Id or password. Want to try again? (y/n)" << endl;
			cin >> c;
			if (c == 'y' || c == 'Y')
				loginAdmin();
			else
				main();
		}
	}
	else
	{
		cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
	}
}

void forgotPassword()
{
	system("cls");
	string user_id, email;
	string user[5000];
	int indexForUserId = 0;
	bool HaveException = false;
	bool NotInDatabase = false;

	try
	{
		cout << "--- Welcome to Car Rental Management System ---" << endl;
		cout << "Forgot Password? " << endl;
		cout << "User Id: ";
		cin >> user_id;
		cout << "Email: ";
		cin >> email;
		cout << endl;
	}
	catch (exception e)
	{
		cout << "Please Enter a valid user id." << endl;
		HaveException = true;
		main();
	}
	if (HaveException == false)
	{
		string strem;
		stringstream streamid;
		stringstream streamem;
		streamid << user_id;
		streamid >> strid;
		streamem << email;
		streamem >> strem;

		for (int i = 0; i < indexForUserId; i++)
		{
			if (strid != user[i])
			{
				NotInDatabase = true;
			}
			else
			{
				NotInDatabase = false;
				break;
			}
		}
		if (NotInDatabase == false)
		{
			string findbyid_query = "select password from userdetail where user_id = '" + strid + "' and email = '" + strem + "'";
			const char* fp = findbyid_query.c_str();
			qstate = mysql_query(conn, fp);
			if (!qstate)
			{
				res = mysql_store_result(conn);
				while ((row = mysql_fetch_row(res)))
				{
					cout << "User Id: " << user_id << "\nPassword: " << row[0] << endl;
				}
			}
			else
			{
				cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
			}
		}
		cout << "Press 'm' to Menu, or any other key to Exit: ";
		cin >> choose;
		if (choose == 'M' || choose == 'm')
		{
			main();
		}
		else
		{
			exit(0);
		}
	}
	system("cls");
}

void UserDetail::user()
{
	system("cls");
	system("title Car Rental Management System");
	UserDetail::userOptions();
	cout << "   Enter your choice: ";
	int option;
	cin >> option;
	if (option == 1)
	{
		UserDetail::checkCarAvailability();
	}
	else if (option == 2)
	{
		UserDetail::carBooking();
	}
	else if (option == 3)
	{
		UserDetail::payment();
	}
	else if (option == 4)
	{
		UserDetail::feedback();
	}
	else if (option == 5)
	{
		UserDetail::bookingHistory();
	}
	else
	{
	ExitProgram:
		cout << "Logout. Are you sure? (Y/N): ";
		cin >> exitSecurity;
		if (exitSecurity == 'y' || exitSecurity == 'Y') {
			main();
		}
		else if (exitSecurity == 'n' || exitSecurity == 'N') {
			std::system("cls");
			UserDetail::user();
		}
		else {
			cout << "Next time choose after read the corresponding line." << endl;
			goto ExitProgram;
		}
	}
	std::system("pause");
	std::system("cls");
}

void Admin::admin()
{
	system("cls");
	system("title Car Rental Management System");
	Admin::adminOptions();
	cout << "   Enter your choice: ";
	int option;
	cin >> option;
	if (option == 1)
	{
		Admin::addNewCar();
	}
	else if (option == 2)
	{
		Admin::removeCar();
	}
	else if (option == 3)
	{
		Admin::addNewAdmin();
	}
	else if (option == 4)
	{
		Admin::addNewUser();
	}
	else if (option == 5)
	{
		Admin::showAllUser();
	}
	else if (option == 6)
	{
		Admin::editUserDetail();
	}
	else if (option == 7)
	{
		Admin::addNewBooking();
	}
	else if (option == 8)
	{
		Admin::removeBooking();
	}
	else if (option == 9)
	{
		Admin::findBooking();
	}
	else if (option == 10)
	{
		Admin::trackPayment();
	}
	else if (option == 11)
	{
		Admin::viewFeedback();
	}
	else if (option == 12)
	{
		Admin::generateStatistic();
	}
	else
	{
	ExitProgram:
		cout << "Logout. Are you sure? (Y/N): ";
		cin >> exitSecurity;
		if (exitSecurity == 'y' || exitSecurity == 'Y') {
			main();
		}
		else if (exitSecurity == 'n' || exitSecurity == 'N') {
			system("cls");
			Admin::admin();
		}
		else {
			cout << "Next time choose after read the corresponding line." << endl;
			goto ExitProgram;
		}
	}
	system("cls");
}

void UserDetail::checkCarAvailability()
{
	system("cls");
	system("title Car Rental Management System");
	cout << "--- Welcome to Car Rental Management System ---" << endl << endl;
	cout << " ___Show All Car for user___ " << endl << endl;
	qstate = mysql_query(conn, "select * from car");
	if (!qstate)
	{
		res = mysql_store_result(conn);
		cout << " |  Car Id\t\tBrand\t\t\tPlate Number\t\tNumber of Passengers\t\tPrice(RM per day)" << endl;
		cout << " |  ====================================================================================================================" << endl;
		while ((row = mysql_fetch_row(res)))
		{
			cout << " |  " << row[0] << "\t\t" << row[1] << "\t\t" << row[2] << "\t\t\t" << row[3] << "\t\t\t\t\t" << row[4] << endl;
		}
	}
	else
	{
		cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
	}
	cout << "Press 'm' to User Menu and any other key to Exit: ";
	cin >> choose;
	if (choose == 'm' || choose == 'M')
	{
		user();
	}
	else
	{
		exit(0);
	}
	system("pause");
	system("cls");
} 

void UserDetail::carBooking()
{
	system("cls");
	system("title Car Rental Management System");
	string booking_id, rental_date, return_date, car_id, user_id;

	cout << "--- Welcome to Car Rental Management System ---" << endl << endl;
	cout << " ___Make car booking___ " << endl;
	cin.ignore(1, '\n');
	cout << "Booking id: ";
	getline(cin, booking_id);
	cout << "Rental date: ";
	getline(cin, rental_date);
	cout << "Return date: ";
	getline(cin, return_date);
	cout << "Enter car id which want to book: ";
	getline(cin, car_id);
	cout << "Enter user id who want to book the car: ";
	getline(cin, user_id);

	string checkBooking_query = "select * from booking where booking_id ='" + booking_id + "' limit 1";
	const char* cb = checkBooking_query.c_str();
	qstate = mysql_query(conn, cb);

		if (!qstate)
		{
		res = mysql_store_result(conn);
			if (res->row_count == 1)
			{
				cout << "The booking Id is already exist. Please change your Id and Press Enter to Try Again...";
				_getch();
				carBooking();
			}
			else
			{
				string insert_query = "insert into booking (booking_id, rental_date, return_date, car_id, user_id) values ('" + booking_id + "',' " + rental_date + "','" + return_date + "','" + car_id + "',' " + user_id + "')";
				const char* q = insert_query.c_str();
				qstate = mysql_query(conn, q);

				if (!qstate)
				{
					cout << endl << "Your booking is successful." << endl;
				}
				else
				{
					cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
				}
				cout << "Press 'm' to User Menu Or Any Other key to exit: ";
				cin >> choose;
				if (choose == 'm' || choose == 'M')
				{
					user();
				}
				else
				{
					exit(0);
				}
				system("pause");
				system("cls");
			}
	}
}

void UserDetail::payment()
{
	system("cls");
	system("title Car Rental Management System");
	string payment_id, amount, accountNum, booking_id, user_id;

	cout << "--- Welcome to Car Rental Management System ---" << endl << endl;
	cout << " ___Make payment___ " << endl;
	cin.ignore(1, '\n');
	cout << "Payment Id: ";
	getline(cin, payment_id);
	cout << "Amount (RM): ";
	getline(cin, amount);
	cout << "Account Number: ";
	getline(cin, accountNum);
	cout << "Booking Id: ";
	getline(cin, booking_id);
	cout << "User Id: ";
	getline(cin, user_id);
	
	string insert_query = "insert into payment (payment_id, amount, accountNum, booking_id, user_id) values ('" + payment_id + "','" + amount + "','" + accountNum + "','" + booking_id + "','" + user_id + "')";
	const char* q = insert_query.c_str();
	qstate = mysql_query(conn, q);
	if (!qstate) {
		cout << endl << "Your payment is successfully being added. " << endl;
	}
	else
	{
		cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
	}
	cout << "Press 'm' to User Menu Or Any Other key to exit ";
	cin >> choose;
	if (choose == 'm' || choose == 'M')
	{
		user();
	}
	else
	{
		exit(0);
	}
	system("pause");
	system("cls");
}

void UserDetail::feedback()
{
	system("cls");
	system("title Car Rental Management System");
	string feedback_id, rating, opinion, booking_id, user_id;

	cout << "--- Welcome to Car Rental Management System ---" << endl << endl;
	cout << " ____Make feedback___ " << endl;
	cin.ignore(1, '\n');
	cout << "Feedback Id: ";
	getline(cin, feedback_id);
	cout << "Rating: ";
	getline(cin, rating);
	cout << "Opinion: ";
	getline(cin, opinion);
	cout << "Booking Id: ";
	getline(cin, booking_id);
	cout << "User Id: ";
	getline(cin, user_id);

	string insert_query = "insert into feedback (feedback_id, rating, opinion, booking_id, user_id) values ('" + booking_id + "','" + rating + "','" + opinion + "','" + booking_id + "','" + user_id + "')";
	const char* q = insert_query.c_str();
	qstate = mysql_query(conn, q);
	if (!qstate) {
		cout << endl << "Your feedback is successfully being added. " << endl;
	}
	else
	{
		cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
	}
	cout << "Press 'm' to User Menu Or Any Other key to exit: ";
	cin >> choose;
	if (choose == 'm' || choose == 'M')
	{
		user();
	}
	else
	{
		exit(0);
	}
	system("pause");
	system("cls");
}

 void UserDetail::bookingHistory()
{
	system("cls");
	system("title Car Rental Management System");
	string user_id;
	
	cout << "--- Welcome to Car Rental Management System ---" << endl << endl;
	cout << " ___Check booking history___ " << endl << endl;
	cout << "Enter your user id: " << endl;
	cin >> user_id;
	string findbyresult_query = "select * from booking where user_id = '" + user_id + "'";
	const char* qi = findbyresult_query.c_str();
	qstate = mysql_query(conn, qi);
	if (!qstate)
	{
		res = mysql_store_result(conn);
		if (res->row_count == 1)
		{
			cout << " |  Booking Id\t\tRental Date\tReturn Date\tCar Id\t\tUser Id" << endl;
			cout << " |  ===========================================================================" << endl;
			while ((row = mysql_fetch_row(res)))
			{
				cout << " |  " << row[0] << "\t\t" << row[1] << "\t" << row[2] << "\t" << row[3] << "\t\t" << row[4] << endl;
			}
		}
		else
		{
			char c;
			cout << "No booking found! Want to try again? (y/n)" << endl;
			cin >> c;
			if (c == 'y' || c == 'Y')
				bookingHistory();
			else
				main();
		}
	}
	else
	{
		cout << "Query Execution Problem! " << mysql_errno(conn) << endl;
		goto Menu;
	}
Menu:
	cout << "Press 'm' to User Menu and any other key to Exit: ";
	cin >> choose;
	if (choose == 'm' || choose == 'M')
	{
		user();
	}
	else
	{
		exit(0);
	}
	system("pause");
	system("cls");
}

void Admin::addNewCar()
{
	system("cls");
	system("title Car Rental Management System");
	string car_id, brand, plate_num;
	int numPassengers=0;
	double price = 0.00;

	cout << "--- Welcome to Car Rental Management System ---" << endl << endl;
	cout << " ___Add New Car for User___ " << endl;
	cin.ignore(1, '\n');
	cout << "Car_Id: ";
	getline(cin, car_id);
	cout << "Brand of car: ";
	getline(cin, brand);
	cout << "Plate number of car: ";
	getline(cin, plate_num);
	cout << "Number of passengers: ";
	cin >> numPassengers;
	cout << "Price of rental per day(RM): ";
	cin >> price;

	stringstream streamPassengers, streamPrice;
	string stpass, stprice;
	streamPassengers << numPassengers;
	streamPassengers >> stpass;
	streamPrice << price;
	streamPrice >> stprice;

	string insert_query = "insert into car (car_id, brand, plate_num, numPassengers, price) values ('" + car_id + "','" + brand + "','" + plate_num + "','" + stpass + "','" + stprice + "')";
	const char* q = insert_query.c_str();
	qstate = mysql_query(conn, q);
	if (!qstate)
	{
		cout << endl << "New car is added successfully." << endl;
	}
	else
	{
		cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
	}
	cout << "Press 'm' to Admin Menu Or Any Other key to menu: ";
	cin >> choose;
	if (choose == 'm' || choose == 'M')
	{
		admin();
	}
	else
	{
		addNewCar();
	}
	system("pause");
	system("cls");
}

void Admin::removeCar()
{
	system("cls");
	system("title Car Rental Management System");
	string car_id;
	string car[5000];
	int indexForCarId = 0;
	bool HaveException = false, NotInDatabase = false;

	cout << "--- Welcome to Car Rental Management System ---" << endl << endl;
	cout << "___Remove Car___" << endl << endl;
	qstate = mysql_query(conn, "select * from car");
	if (!qstate)
	{
		res = mysql_store_result(conn);
		cout << " |  Car Id\tBrand\t\t\tPlate Number\t\tNumber of Passengers\t\tPrice" << endl;
		cout << " |  =================================================================================================" << endl;
		while ((row = mysql_fetch_row(res)))
		{
			cout << " |  " << row[0] << "\t" << row[1] << "\t\t" << row[2] << "\t\t\t" << row[3] << "\t\t\t\t" << row[4] << endl;
			car[indexForCarId] = row[0];
			indexForCarId++;
		}
	}
	else
	{
		cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
	}
	try
	{
		cout << endl;
		cout << "Please enter your Car ID: ";
		cin >> car_id;
		cout << endl;
	}
	catch (exception e)
	{
		cout << "Please enter a valid Car ID." << endl;
		HaveException = true;
		goto ExitMenu;
	}

	if (HaveException == false)
	{
		stringstream streamcar;
		string strcar;
		streamcar << car_id;
		streamcar >> strcar;

		for (int i = 0; i < indexForCarId; i++)
		{
			if (strcar != car[i])
			{
				NotInDatabase = true;
			}
			else
			{
				NotInDatabase = false;
				break;
			}
		}
		if (NotInDatabase == false)
		{
			string delete_query = "delete from car where car_id = '" + strcar + "' ";
			const char* dq = delete_query.c_str();
			qstate = mysql_query(conn, dq);
			if (!qstate)
			{
				cout << "The car is successfully being deleted from the database." << endl;
			}
			else
			{
				cout << "Failed to delete!!!" << mysql_errno(conn) << endl;
			}
		}
		else
		{
			cout << "Car Id is not found in the database." << endl;
		}
	}
ExitMenu:
	cout << "Press 'm' to Admin Menu, 'd' to delete another item and any other key to Exit: ";
	cin >> choose;
	if (choose == 'm' || choose == 'M')
	{
		admin();
	}
	else if (choose == 'd' || choose == 'D')
	{
		removeCar();
		system("cls");
	}
	else
	{
		exit(0);
	}
	system("pause");
	system("cls");
}

void Admin::addNewAdmin()
{
	system("cls");

	string admin_id, name, password, contact_num, email;

	cout << "--- Welcome To Car Rental Management System ---" << endl << endl;
	cout << " ___Create account for admin___ " << endl;
	cin.ignore(1, '\n');
	cout << "Admin ID: ";
	getline(cin, admin_id);
	cout << "Name: ";
	getline(cin, name);
	cout << "Password: ";
	getline(cin, password);
	cout << "Contact number: ";
	getline(cin, contact_num);
	cout << "Email: ";
	getline(cin, email);

	string checkAdmin_query = "select * from admin where admin_id = '" + admin_id + "' limit 1";
	const char* ca = checkAdmin_query.c_str();
	qstate = mysql_query(conn, ca);

	if (!qstate)
	{
		res = mysql_store_result(conn);
		if (res->row_count == 1)
		{
			cout << "Admin ID is already exist. Press Enter to Try Again...";
			_getch();
			addNewAdmin();
		}
		else
		{
			string insert_query = "insert into admin (admin_id, name, password, contact_num, email) values ('" + admin_id + "','" + name + "','" + password + "','" + contact_num + "','" + email + "') ";
			const char* q = insert_query.c_str();
			qstate = mysql_query(conn, q);

			if (!qstate)
			{
				cout << endl << "New admin have been successfully added.  Press Enter to continue..." << endl;
			}
			else
			{
				cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
			}
			cout << "Press 'm' to Admin Menu and any other key to Exit: ";
			cin >> choose;
			if (choose == 'M' || choose == 'm')
			{
				admin();
			}
			else
			{
				exit(0);
			}
			system("cls");
		}
	}
}

void Admin::addNewUser()
{
	system("cls");
	system("title Car Rental Management System");
	string user_id, password, contact_num, address, email, name;

	cout << "--- Welcome To Car Rental Management System ---" << endl << endl;
	cout << " ____Add new user___ " << endl;
	cin.ignore(1, '\n');
	cout << "User ID: ";
	getline(cin, user_id);
	cout << "Name: ";
	getline(cin, name);
	cout << "Password: ";
	getline(cin, password);
	cout << "Contact number: ";
	getline(cin, contact_num);
	cout << "Address: ";
	getline(cin, address);
	cout << "Email: ";
	getline(cin, email);

	string checkUser_query = "select * from userdetail where user_id = '" + user_id + "' limit 1";
	const char* cu = checkUser_query.c_str();
	qstate = mysql_query(conn, cu);

	if (!qstate)
	{
		res = mysql_store_result(conn);
		if (res->row_count == 1)
		{
			cout << "User ID is already exist. Press Enter to Try Again...";
			_getch();
			Admin::addNewUser();
		}
		else
		{
			string insert_query = "insert into userdetail (user_id, name, password, contact_num, address, email) values ('" + user_id + "','" + name + "','" + password + "','" + contact_num + "','" + address + "','" + email + "') ";
			const char* q = insert_query.c_str();
			qstate = mysql_query(conn, q);

			if (!qstate)
			{
				cout << endl << "The account for new user is successfully created. Press Enter to continue..." << endl;
			}
			else
			{
				cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
			}
			cout << "Press 'm' to Admin Menu and any other key to Exit: ";
			cin >> choose;
			if (choose == 'M' || choose == 'm')
			{
				admin();
			}
			else
			{
				exit(0);
			}
			system("cls");
		}
	}
}

void Admin::addNewBooking()
{
	system("cls");
	system("title Car Rental Management System");
	string booking_id, rental_date, return_date, car_id, user_id;

	cout << "--- Welcome to Car Rental Management System ---" << endl << endl;
	cout << " ___Make car booking___ " << endl;
	cin.ignore(1, '\n');
	cout << "Booking id: ";
	getline(cin, booking_id);
	cout << "Rental date: ";
	getline(cin, rental_date);
	cout << "Return date: ";
	getline(cin, return_date);
	cout << "Enter car id which want to book: ";
	getline(cin, car_id);
	cout << "Enter user id who want to book the car: ";
	getline(cin, user_id);

	string checkBooking_query = "select * from booking where booking_id ='" + booking_id + "' limit 1";
	const char* cb = checkBooking_query.c_str();
	qstate = mysql_query(conn, cb);

	if (!qstate)
	{
		res = mysql_store_result(conn);
		if (res->row_count == 1)
		{
			cout << "The booking Id is already exist. Press Enter to Try Again...";
			_getch();
			addNewBooking();
		}
		else
		{
			string insert_query = "insert into booking (booking_id, rental_date, return_date, car_id, user_id) values ('" + booking_id + "',' " + rental_date + "','" + return_date + "','" + car_id + "',' " + user_id + "')";
			const char* q = insert_query.c_str();
			qstate = mysql_query(conn, q);

			if (!qstate)
			{
				cout << endl << "New booking is successfuly added." << endl;
			}
			else
			{
				cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
			}
			cout << "Press 'm' to Admin Menu Or Any Other key to exit: ";
			cin >> choose;
			if (choose == 'm' || choose == 'M')
			{
				admin();
			}
			else
			{
				main();
			}
			system("pause");
			system("cls");
		}
	}
}

void Admin::removeBooking()
{
	system("cls");
	system("title Car Rental Management System");
	string booking_id;
	string booking[5000];
	int indexForBookingId = 0;
	bool HaveException = false, NotInDatabase = false;

	cout << "--- Welcome to Car Rental Management System ---" << endl << endl;
	cout << " ___Remove Booking___ " << endl << endl;
	qstate = mysql_query(conn, "select * from booking");
	if (!qstate)
	{
		res = mysql_store_result(conn);
		cout << " |  Booking Id\t\tRental Date\t\tReturn Date\t\tCar Id\t\tUser Id" << endl;
		cout << " |  ================================================================================================" << endl;
		while ((row = mysql_fetch_row(res)))
		{
			cout << " |  " << row[0] << "\t\t" << row[1] << "\t\t"<<row[2]<<"\t\t"<<row[3]<<"\t\t"<< row[4] << endl;
			booking[indexForBookingId] = row[0];
			indexForBookingId++;
		}
	}
	else
	{
		cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
	}
	try
	{
		cout << endl;
		cout << "Please enter your Booking ID: ";
		cin >> booking_id;
		cout << endl;
	}
	catch (exception e)
	{
		cout << "Please enter a valid Booking ID." << endl;
		HaveException = true;
		goto ExitMenu;
	}

	if (HaveException == false)
	{
		stringstream streambook;
		string strbook;
		streambook << booking_id;
		streambook >> strbook;

		for (int i = 0; i < indexForBookingId; i++)
		{
			if (strbook != booking[i])
			{
				NotInDatabase = true;
			}
			else
			{
				NotInDatabase = false;
				break;
			}
		}
		if (NotInDatabase == false)
		{
			string delete_query = "delete from booking where booking_id = '" + strbook + "' ";
			const char* dq = delete_query.c_str();
			qstate = mysql_query(conn, dq);
			if (!qstate)
			{
				cout << "The booking is successfully being deleted from the database." << endl;
			}
			else
			{
				cout << "Failed to delete!" << mysql_errno(conn) << endl;
			}
		}
		else
		{
			cout << "Booking Id is not found in the database." << endl;
		}
	}
ExitMenu:
	cout << "Press 'm' to Admin Menu, 'd' to delete another item and any other key to Exit: ";
	cin >> choose;
	if (choose == 'm' || choose == 'M')
	{
		admin();
	}
	else if (choose == 'd' || choose == 'D')
	{
		removeBooking();
		system("cls");
	}
	else
	{
		exit(0);
	}
	system("pause");
	system("cls");
}

void Admin::showAllUser()
{
	system("cls");
	system("title Car Rental Management System");
	cout << "--- Welcome to Car Rental Management System ---" << endl << endl;
	cout << " ___Show All user___" << endl << endl;
	qstate = mysql_query(conn, "select * from userdetail");
	if (!qstate)
	{
		res = mysql_store_result(conn);
		cout << " |  User Id\t\tName\t\tContact Number\t\tAddress\t\t\t\tEmail" << endl;
		cout << " |  =========================================================================================================" << endl;
		while ((row = mysql_fetch_row(res)))
		{
			cout << " |  " << row[0] << "\t\t" << row[1] << "\t\t" << row[3] << "\t\t" << row[4] << "\t\t\t" << row[5] << endl;
		}
	}
	else
	{
		cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
	}
	cout << "Press 'm' to Admin Menu and any other key to Exit: ";
	cin >> choose;
	if (choose == 'm' || choose == 'M')
	{
		admin();
	}
	else
	{
		exit(0);
	}
	system("pause");
	system("cls");
}

void Admin::findBooking()
{
	system("cls");
	string input;
	system("title Car Rental Management System");
	cout << "--- Welcome to Car Rental Management System ---" << endl << endl;
	cout << " ___Finding booking___" << endl;
	cout << "Find by \n1. Booking Id\n2. User Id\nAny other number to Menu" << endl;
	cout << "Enter your option: ";
	cin >> choose;
	cin.ignore(1, '\n');
	if (choose == '1')
	{
		cout << "Enter booking id: ";
		getline(cin, input);
		string findbybookid_query = "select * from booking where booking_id like '" + input + "%'";
		const char* qb = findbybookid_query.c_str();
		qstate = mysql_query(conn, qb);
	}
	else if (choose == '2')
	{
		cout << "Enter User id: ";
		getline(cin, input);
		string findbyuserid_query = "select * from booking where user_id like '" + input + "%'";
		const char* qu = findbyuserid_query.c_str();
		qstate = mysql_query(conn, qu);
	}
	else
	{
		goto ExitMenu;
	}

	cout << endl;
	if (choose == '1' || choose == '2')
	{
		if (!qstate)
		{
			res = mysql_store_result(conn);
			cout << " |  Booking Id\t\tRental date\t\tReturn date\t\tCar id\t\tUser id" << endl;
			cout << " |  ==================================================================================================" << endl;
			while ((row = mysql_fetch_row(res)))
			{
				cout << " |  " << row[0] << "\t\t" << row[1] << "\t\t" << row[2] << "\t\t" << row[3] << "\t\t" << row[4] << endl;
			}
		}
		else
		{
			cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
		}
	}
		
ExitMenu:
	cout << "Press 'm' to Admin Menu, 'a' to Search again and any other key to Exit: ";
	cin >> choose;
	if (choose == 'm' || choose == 'M')
	{
		admin();
	}
	else if (choose == 'a' || choose == 'A')
	{
		findBooking();
	}
	else
	{
		exit(0);
	}
	system("pause");
	system("cls");
} 

void Admin::editUserDetail()
{
	system("cls");
	string user_id, name, password, contact_num, address, email;
	string userdetail[5000];
	bool HaveException = false;
	bool NotInDatabase = false;
	int indexForUserId = 0;

	string storeuserid, storename, storepassword, storecontactnum, storeaddress, storeemail;

	cout << "--- Welcome to Car Rental Management System ---" << endl << endl;
	cout << " ____Edit User Info___" << endl << endl;
	qstate = mysql_query(conn, "select user_id, name from userdetail");
	if (!qstate)
	{
		res = mysql_store_result(conn);
		cout << "UserId\tName" << endl;
		while ((row = mysql_fetch_row(res)))
		{
			cout << row[0] << "\t" << row[1] << endl;
			userdetail[indexForUserId] = row[0];
			indexForUserId++;
		}
	}
	else
	{
		cout << "Query Execution Problem! " << mysql_errno(conn) << endl;
	}
	try
	{
		cout << endl;
		cout << "Enter User Id: ";
		cin >> user_id;
		cout << endl;
	}
	catch (exception e)
	{
		cout << "Please enter a valid User Id." << endl;
		HaveException = true;
		goto adminMenu;
	}
	if (HaveException == false)
	{
		stringstream streamid;
		streamid << user_id;
		streamid >> strid;

		for (int i = 0; i < indexForUserId; i++)
		{
			if (strid != userdetail[i])
			{
				NotInDatabase = true;
			}
			else
			{
				NotInDatabase = false;
				break;
			}
		}

		if (NotInDatabase == false)
		{
			string findbyid_query = "select * from userdetail where user_id = '" + strid + "'";
			const char* qi = findbyid_query.c_str();
			qstate = mysql_query(conn, qi);
			if (!qstate)
			{
				res = mysql_store_result(conn);
				cout << endl;
				while ((row = mysql_fetch_row(res)))
				{
					cout << "User Id: " << row[0] << "\nName: " << row[1] << "\nPassword: " << row[2] << "\nContact Number: " << row[3] << "\nAddress: " << row[4] << "\nEmail: " <<row[5] << endl << endl;
					storeuserid = row[0];
					storename = row[1];
					storepassword = row[2];
					storecontactnum = row[3];
					storeaddress = row[4];
					storeemail = row[5];
				}
			}
			else
			{
				cout << "Query Execution Problem! " << mysql_errno(conn) << endl;
			}
			cin.ignore(1, '\n');
			cout << "Please insert new Name ('NO' to not change): ";
			getline(cin, name);
			if (name == "NO")
			{
				name = storename;
			}
			cout << "Please insert new Password ('NO' to not change): ";
			getline(cin, password);
			if (password == "NO")
			{
				password=storepassword;
			}
			cout << "Please insert new Contact Number ('NO' to not change): ";
			getline(cin, contact_num);
			if (contact_num == "NO")
			{
				contact_num=storecontactnum;
			}
			cout << "Please insert new Address ('NO' to not change): ";
			getline(cin, address);
			if (address == "NO")
			{
				address=storeaddress;
			}
			cout << "Please insert new Email ('NO' to not change): ";
			getline(cin, email);
			if (email == "NO")
			{
				email=storeemail;
			}
			string update_query = "update userdetail set name = '" + name + "', password = '" + password + "',contact_num='" + contact_num + "', address = '" + address + "', email = '" + email + "' where user_id = '" + strid + "'";
			const char* qu = update_query.c_str();
			qstate = mysql_query(conn, qu);
			if (!qstate)
			{
				cout << endl << "Successfully saved in database. " << endl;
			}
			else
			{
				cout << "Failed to update! " << mysql_errno(conn) << endl;
			}
		}
		else
		{
			cout << " User not found in database." << endl;
		}
	}
adminMenu:
	cout << "Press 'm' to Admin Menu, 'e' to edit another item and any other key to Exit: ";
	cin >> choose;
	if (choose == 'm' || choose == 'M')
	{
		admin();
	}
	else if (choose == 'e' || choose == 'E')
	{
		editUserDetail();
	}
	else
	{
		exit(0);
	}
	system("pause");
	system("cls");
}

void Admin::trackPayment()
{
	system("cls");
	string input;

	cout << "--- Welcome to Car Rental Management System ---" << endl << endl;
	cout << " ___Track payment___" << endl << endl;
	cout << "Find by \n1. Payment Id\n2. User Id\nAny other number to Menu" << endl;
	cout << "Choose one: ";
	cin >> choose;
	cin.ignore(1, '\n');
	if (choose == '1')
	{
		cout << "Enter payment Id: ";
		getline(cin, input);
		string findbypaymentid_query = "select * from payment where payment_id like '" + input + "%'";
		const char* qp = findbypaymentid_query.c_str();
		qstate = mysql_query(conn, qp);
	}
	else if (choose == '2')
	{
		cout << "Enter user Id: ";
		getline(cin, input);
		string findbyuserid_query = "select * from payment where user_id like '" + input + "%'";
		const char* qu = findbyuserid_query.c_str();
		qstate = mysql_query(conn, qu);
	}
	else
	{
		goto ExitMenu;
	}

	cout << endl;
	if (choose == '1' || choose == '2')
	{
		if (!qstate)
		{
			res = mysql_store_result(conn);
			cout << " |  PaymentId\t\tAmount\t\tAccount Number\t\tBookingId\t\tUserId" << endl;
			cout << " |  ===========================================================================================" << endl;
			while ((row = mysql_fetch_row(res)))
			{
				cout << " |  " << row[0] << "\t\t" << row[1] << "\t\t" << row[2] << "\t\t" << row[3] << "\t\t\t" << row[4] << endl;
			}
		}
		else
		{
			cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
		}
	}
ExitMenu:
	cout << "Press 'm' to Admin Menu, 'a' to Search again and any other key to Exit: ";
	cin >> choose;
	if (choose == 'm' || choose == 'M')
	{
		admin();
	}
	else if (choose == 'a' || choose == 'A')
	{
		trackPayment();
	}
	else
	{
		exit(0);
	}
	system("pause");
	system("cls");
}

void Admin::viewFeedback()
{
	system("cls");
	system("title Car Rental Management System");
	db_response::ConnectionFunction();
	cout << "--- Welcome to Car Rental Management System ---" << endl << endl;
	cout << " ___View the feedback___ " << endl << endl;
	qstate = mysql_query(conn, "select * from feedback");
	if (!qstate)
	{
		res = mysql_store_result(conn);
		cout << " |  Feedback Id\t\tRating\t\tOpinion\t\t\t\t\tUser Id" << endl;
		cout << " |  ====================================================================================" << endl;
		while ((row = mysql_fetch_row(res)))
		{
			cout << " |  " << row[0] << "\t\t" << row[1] << "\t\t" << row[2] << "\t\t\t\t" << row[3] << endl;
		}
	}
	else
	{
		cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
	}
	cout << "Press 'm' to Admin Menu and any other key to Exit: ";
	cin >> choose;
	if (choose == 'm' || choose == 'M')
	{
		admin();
	}
	else
	{
		exit(0);
	}
	system("pause");
	system("cls");
}

void Admin::generateStatistic()
{
	system("cls");
	system("title Car Rental Management System");
	int option;
	cout << " ___Statistic Report___ " << endl << endl;
	cout << "Please choose the option" << endl;
	cout << "1. Total booking" << endl;
	cout << "2. Total payment received" << endl;
	cout << "3. Back to Menu" << endl;
	cout << "   Enter your choice: ";
	cin >> option;
	if (option == 1)
	{
		system("cls");
		system("title Car Rental Management System");
		qstate = mysql_query(conn,"SELECT COUNT(booking_id) from booking");
		if (!qstate)
		{
			res = mysql_store_result(conn);
			cout << " ***************************************************" << endl << endl;
			while ((row = mysql_fetch_row(res)))
			{
				cout << "    TOTAL NUMBER OF BOOKINGS MADE CURRENTLY:  " << row[0] << endl << endl;
			}
			cout << " *************************************************** " << endl << endl;
		}
		else
		{
			cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
		}
		cout << "Press 'm' to continue, 'b' to Main Menu and any other key to Exit: ";
		cin >> choose;
		if (choose == 'm' || choose == 'M')
		{
			generateStatistic();
		}
		else if (choose == 'b' || choose == 'B')
		{
			admin();
		}
		else
		{
			exit(0);
		}
		system("pause");
		system("cls");
	}
	else if (option == 2)
	{
		system("cls");
		system("title Car Rental Management System");
		qstate = mysql_query(conn, "select SUM(amount) from payment");
		if (!qstate)
		{
			res = mysql_store_result(conn);
			cout << " ****************************************************************** " << endl << endl;
			while ((row = mysql_fetch_row(res)))
			{
				cout << "   TOTAL AMOUNT RECEIVED BY THE COMPANY CURRENTLY: " << row[0] << endl << endl;	
			}
			cout << " ****************************************************************** " << endl << endl;
		}
		else
		{
			cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
		}
		cout << "Press 'm' to Admin Menu, 'b' to Main Menu and any other key to Exit: ";
		cin >> choose;
		if (choose == 'm' || choose == 'M')
		{
			admin();
		}
		else if (choose == 'b' || choose == 'B')
		{
			admin();
		}
		else
		{
			exit(0);
		}
		system("pause");
		system("cls");
	}
	else
	{
		cout << "Press 'm' to Admin Menu, 'b' to Main Menu and any other key to Exit: ";
		cin >> choose;
		if (choose == 'm' || choose == 'M')
		{
			admin();
		}
		else if (choose == 'b' || choose == 'B')
		{
			main();
		}
		else
		{
			exit(0);
		}
		system("pause");
		system("cls");
	}
}