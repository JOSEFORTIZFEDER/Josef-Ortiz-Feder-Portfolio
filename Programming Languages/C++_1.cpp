// C_Assignment1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <string>
using namespace std;

// ==========Problem #1==================
class Student {
public:
	void Takedata(int admno, string sname, float end, float math, float science);
	void Showdata();
private:
	int admno;
	string sname;
	float eng;
	float math;
	float science;
	float total;
	float ctotal();
};
void Student::Takedata(int admno, string sname, float eng, float math, float science)
{
	this->admno = admno;
	this->sname.assign(sname);
	this->eng = eng;
	this->math = math;
	this->science = science;
	this->total = ctotal();
}

void Student::Showdata()
{
	cout << "admno - " << admno << endl;
	cout << "sname - " << sname << endl;
	cout << "eng - " << eng << endl;
	cout << "math - " << math << endl;
	cout << "science - " << science << endl;
	cout << "total - " << total << endl;
}

float Student::ctotal()
{
	return math + science + eng;
}

// ==========Problem #2==================
class batsman {
public: 
	void readdata(int bcode, string bname, float innings, float notout, float runs);
	void displaydata();
private:
	int bcode;
	string bname;
	float innings;
	float notout;
	float runs;
	float batavg;
	float calcavg();
};

void batsman::readdata(int bcode, string bname, float innings, float notout, float runs)
{
	this->bcode = bcode;
	this->bname.assign(bname);
	this->innings = innings;
	this->notout = notout;
	this->runs = runs;
	this->batavg = calcavg();
}
void batsman::displaydata()
{
	cout << "bcode - " << bcode << endl;
	cout << "bname - " << bname << endl;
	cout << "innings - " << innings << endl;
	cout << "notout - " << notout << endl;
	cout << "runs - " << runs << endl;
	cout << "batavg - " << batavg << endl;
}
float batsman::calcavg()
{
	return runs / (innings - notout);
}

// ==========Problem #3==================
class Test {
public:
	void SCHEDULE();
	void DISPTEST();
private: 
	int TestCode;
	string Description;
	int NoCandidate;
	int CenterReqd;
	int CALCNTR();
};
void Test::SCHEDULE()
{
	cout << "Enter the TestCode: ";
	cin >> TestCode;

	cout << "Enter the Description: ";
	cin.ignore();
	getline(cin, Description);

	cout << "Enter the NoCandidate: ";
	cin >> NoCandidate;
	CenterReqd = CALCNTR();
}
void Test::DISPTEST()
{
	cout << "TestCode - " << TestCode << endl;
	cout << "Description - " << Description << endl;
	cout << "NoCandidate - " << NoCandidate << endl;
	cout << "CenterReqd - " << CenterReqd << endl;
}
int Test::CALCNTR()
{
	return NoCandidate / 100 + 1;
}

// ==========Problem #4==================
class Flight {
public:
	void FEEDINFO();
	void SHOWINFO();
private:
	int flightNum;
	string destination;
	float distance;
	float fuel;
	float CALFUEL();
};

void Flight::FEEDINFO()
{
	cout << "Flight Number: ";
	cin >> flightNum;
	cout << "Destination: ";
	cin.ignore();

	getline(cin, destination);
	cout << "Distance: ";
	cin >> distance;
	fuel = CALFUEL();
}
void Flight::SHOWINFO()
{
	cout << "Flight Number - " << flightNum << endl;
	cout << "Destination - " << destination << endl;
	cout << "Distance - " << distance << endl;
	cout << "Fuel - " << fuel << endl;
}
float Flight::CALFUEL()
{
	if (distance <= 1000)
	{
		return 500;
	}
	else if (distance > 1000 && distance <= 2000)
	{
		return 1100;
	}
	else
	{
		return 2200;
	}
	
}

// ==========Problem #5==================
class BOOK {
public:
	void INPUT();
	void PURCHASE();

private:
	int bookNo;
	string bookTitle;
	float price;
	float TOTAL_COST(int N);
};

void BOOK::INPUT()
{
	cout << "Book No.: ";
	cin >> bookNo;
	cout << "Book Title: ";
	cin.ignore();

	getline(cin, bookTitle);
	cout << "Price: ";
	cin >> price;
}

void BOOK::PURCHASE()
{
	cout << "How many copies would you like to purchase? ";
	int num;
	cin >> num;
	cout << "The total cost is: " << TOTAL_COST(num);
}
float BOOK::TOTAL_COST(int N)
{
	return N * price;
}

// ==========Problem #6==================
class REPORT {
private:
	int adno;
	string name;
	float marks[5];
	float average;
	float GETAVG();
public:
	void READINFO();
	void DISPLAYINFO();
};

float REPORT::GETAVG()
{
	return (marks[0] + marks[1] + marks[2] + marks[3] + marks[4]) / 5;
}

void REPORT::READINFO()
{
	cout << "adno: ";
	cin >> adno;
	cout << "Name: ";
	cin.ignore();
	getline(cin, name);
	for (int i = 0; i < 5; ++i)
	{
		cout << "Mark " << i << " : ";
		cin >> marks[i];
	}
	average = GETAVG();
}
void REPORT::DISPLAYINFO()
{
	cout << "adno - " << adno << endl;
	cout << "Name - " << name << endl;
	for (int i = 0; i < 5; ++i)
	{
		cout << "Mark " << i << " - " << marks[i] << endl;
	}
	cout << "Average - " << average << endl;
}

// ==========Problem #7==================
class Rectangle {
private:
	float length;
	float width;
public:
	void setlength(float length);
	void setwidth(float width);
	float perimeter();
	float area();
	void show();
	int sameArea(Rectangle rect);
};
void Rectangle::setlength(float length)
{
	this->length = length;
}
void Rectangle::setwidth(float width)
{
	this->width = width;
}
float Rectangle::perimeter()
{
	return (width * 2) + (length*2);
}
float Rectangle::area()
{
	return width * length;
}
void Rectangle::show()
{
	cout << "Length: " << length << endl;
	cout << "Width: " << width << endl;
}
int Rectangle::sameArea(Rectangle rect)
{
	if (this->area() == rect.area())
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

// ==========Problem #8==================
class complex {
public:
	void set(float real, float imaginary);
	void disp();
	complex sum(complex x);
private:
	float real;
	float imaginary;
};
void complex::set(float real, float imaginary)
{
	this->real = real;
	this->imaginary = imaginary;
}
void complex::disp()
{
	cout << "Real: " << real << " Imaginary: " << imaginary << endl;
}
complex complex::sum(complex x)
{
	complex newComplex;
	newComplex.set(real + x.real, imaginary + x.imaginary);
	return newComplex;
}

// ==========Problem #9==================
class Distance {
private:
	int feet;
	float inches;
public:
	void set(int feet, float inches);
	void disp();
	Distance add(Distance x);
};
void Distance::set(int feet, float inches)
{
	this->feet = feet;
	this->inches = inches;
}
void Distance::disp()
{
	cout << "Feet: " << feet << " Inches: " << inches << endl;
}
Distance Distance::add(Distance x)
{
	Distance newDistance;
	newDistance.set(feet + x.feet, inches + x.inches);
	if (newDistance.inches >= 12)
	{
		newDistance.inches -= 12;
		newDistance.feet += 1;
	}
	return newDistance;
}

// ==========Problem #10==================
class Time {
private:
	int hours;
	int minutes;
public:
	void settime(int hours, int minutes);
	void showtime();
	Time sum(Time x);
};
void Time::settime(int hours, int minutes)
{
	this->hours = hours;
	this->minutes = minutes;
}
void Time::showtime()
{
	cout << "Hours: " << hours << " Minutes: " << minutes << endl;
}

Time Time::sum(Time x)
{
	Time newTime;
	newTime.settime(hours + x.hours, minutes + x.minutes);
	if (newTime.minutes >= 60)
	{
		newTime.hours += 1;
		newTime.minutes -= 60;
	}
	if (newTime.hours >= 13)
	{
		newTime.hours -= 12;
	}
	return newTime;
}


// ==========Main==================

int main()
{
	cout << "Problem 1:" << endl;
	Student myStudent;
	myStudent.Takedata(15, "Brad", 3, 4, 5);
	myStudent.Showdata();
	
	cout << endl << "Problem 2:" << endl;
	batsman myBatsman;
	myBatsman.readdata(15, "Brad", 5, 3, 5);
	myBatsman.displaydata();

	cout << endl << "Problem 3:" << endl;
	Test myTest;
	myTest.SCHEDULE();
	myTest.DISPTEST();

	cout << endl << "Problem 4:" << endl;
	Flight myFlight;
	cout << "Showing FEEDINFO() function" << endl;
	myFlight.FEEDINFO();
	cout << "Showing SHOWINFO() function" << endl;
	myFlight.SHOWINFO();

	cout << endl << "Problem 5:" << endl;
	BOOK myBook;
	cout << "Showing INPUT() function" << endl;
	myBook.INPUT();
	cout << "Showing PURCHASE() function" << endl;
	myBook.PURCHASE();

	cout << endl << "Problem 6:" << endl;
	REPORT myReport;
	cout << "Showing READINFO() function" << endl;
	myReport.READINFO();
	cout << "Showing DISPLAYINFO() function" << endl;
	myReport.DISPLAYINFO();

	cout << endl << "Problem 7:" << endl;
	Rectangle rect1, rect2;
	rect1.setlength(5);
	rect1.setwidth(2.5);
	rect2.setlength(5);
	rect2.setwidth(18.9);
	cout << "First Rectangle: ";
	rect1.show();
	cout << "First Rectangle Perimeter: " << rect1.perimeter() << endl;
	cout << "First Rectangle Area: " << rect1.area() << endl;
	cout << "Second Rectangle: ";
	rect2.show();
	cout << "Second Rectangle Perimeter: " << rect2.perimeter() << endl;
	cout << "Second Rectangle Area: " << rect2.area() << endl;

	cout << "Do the Rectangles have the same area? (0 - no, 1 - yes): " << rect1.sameArea(rect2) << endl;

	rect1.setlength(15);
	rect1.setwidth(6.3);

	rect1.show();
	cout << "First Rectangle Perimeter: " << rect1.perimeter() << endl;
	cout << "First Rectangle Area: " << rect1.area() << endl;
	cout << "Second Rectangle: ";
	rect2.show();
	cout << "Second Rectangle Perimeter: " << rect2.perimeter() << endl;
	cout << "Second Rectangle Area: " << rect2.area() << endl;

	cout << "Do the Rectangles have the same area? (0 - no, 1 - yes): " << rect1.sameArea(rect2) << endl;

	cout << endl << "Problem 8:" << endl;
	complex complex1, complex2, complex3;
	complex1.set(2, 3);
	complex2.set(3, 4);
	complex3 = complex1.sum(complex2);
	cout << "First Complex Num" << endl;
	complex1.disp();
	cout << "Second Complex Num" << endl;
	complex2.disp();
	cout << "Third Complex Num" << endl;
	complex3.disp();

	cout << endl << "Problem 9:" << endl;
	Distance dist1, dist2, dist3;
	dist1.set(3, 11);
	dist2.set(3, 3);
	dist3 = dist1.add(dist2);
	cout << "First Distance" << endl;
	dist1.disp();
	cout << "Second Distance" << endl;
	dist2.disp();
	cout << "Third Distance" << endl;
	dist3.disp();

	cout << endl << "Problem 10:" << endl;
	Time time1, time2, time3;
	time1.settime(6, 50);
	time2.settime(2, 20);
	time3 = time1.sum(time2);
	cout << "First Time" << endl;
	time1.showtime();
	cout << "Second Time" << endl;
	time2.showtime();
	cout << "Third Time" << endl;
	time3.showtime();
}
