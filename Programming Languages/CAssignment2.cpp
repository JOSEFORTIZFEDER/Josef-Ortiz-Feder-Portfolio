// CAssignment2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string.h>
#include <iomanip>
using namespace std;

void copyupper()
{
    ifstream ReadFile("FIRST.TXT");
    ofstream WriteFile("SECOND.TXT");
    char temp;
    while (!ReadFile.eof())
    {
        ReadFile.get(temp);
        temp = toupper(temp);
        WriteFile << temp;
    }
    ReadFile.close();
    WriteFile.close();
}

void vowelwords()
{
    ifstream ReadFile("FIRST.TXT");
    ofstream WriteFile("SECOND.TXT");
    char temp[30];

    while (!ReadFile.eof())
    {
        // ReadFile3.get(temp2);
        ReadFile >> temp;
        if (temp[0] == 'a' || temp[0] == 'e' || temp[0] == 'i' || temp[0] == 'o' || temp[0] == 'u')
        {
            WriteFile << temp << " ";
        }
    }
    ReadFile.close();
    WriteFile.close();
}

// Question 10:
class EMPLOYEE
{
    int ENO;
    char ENAME[10];
public:
    void GETIT()
    {
        //cin.ignore();
        cin >> ENO;
        cin.ignore();
        cin.getline(ENAME, sizeof ENAME);
    }
    void SHOWIT()
    {
        cout << ENO << ENAME << endl;
    }
};
void WriteToBinary()
{
    ofstream WriteFile("employee.dat", ios::binary);
    EMPLOYEE e;
    e.GETIT();
    WriteFile.write((char*)&e, sizeof(e));
    WriteFile.close();
}
void ReadToBinary()
{
    ifstream ReadFile("employee.dat", ios::binary);
    EMPLOYEE e;
    while (ReadFile.read((char*)&e, sizeof(e)))
    {
        e.SHOWIT();
    }
    ReadFile.close();
}

// Question 12:
class computer
{
    char chiptype[10];
    int speed;
public:
    void getdetails()
    {
        //cin.ignore();
        cin.getline(chiptype, sizeof chiptype);
        cin.ignore();
        cin >> speed;
        cin.ignore();
    }
    void showdetails()
    {
        cout << "Chip" << chiptype <<  "Speed = " << speed;
    }
};

void readfile()
{
    ifstream ReadFile("SHIP.DAT", ios::binary);
    computer c;
    int count = 0;
    while (ReadFile.read((char*)&c, sizeof(c)))
    {
        c.showdetails();
        cout << endl;
        count += 1;
    }
    cout << "Count = " << count << endl;
    ReadFile.close();
}

// Question 13:
class Student
{
    char S_Admno[10];    //Admission number of student
    char S_Name[30];       //Name of student
    int Percentage;            //Marks Percentage of student
public:
    void EnterData()
    {
        cin.getline(S_Admno, sizeof S_Admno);
        cin.ignore();
        cin.getline(S_Name, sizeof(S_Name));
        cin.ignore();
        cin >> Percentage;
        cin.ignore();
    }
    void DisplayData()
    {
        cout << setw(12) << S_Admno;
        cout << setw(32) << S_Name;
        cout << setw(3) << Percentage << endl;
    }
    int ReturnPercentage()
    {
        return Percentage;
    }
};
void ShowStudentsOver75()
{
    Student s; 
    ifstream ReadFile("STUDENT.DAT", ios::binary); 

    while (ReadFile.read((char*)&s, sizeof(s)))
    {
        cout << s.ReturnPercentage() << endl;
        if (s.ReturnPercentage() > 75)
        {
            s.DisplayData();
        }
    }

    ReadFile.close();

}

// Question 14:

class Employee
{
    int Eno;
    char Ename[20];
public:
    //Function to count the total number of records
    int Countrec();
};

int Employee::Countrec()
{
    fstream File;
    File.open("EMP.DAT", ios::binary | ios::in);
    File.seekg(0, ios::end); //Statement 1
    int Bytes = File.tellg(); //Statement 2
    int Count = Bytes / sizeof(Employee);
    File.close();
    return Count;
}

// Question 15:
class STUD {
    int Rno;
    char Name[20];
public:
    void Enter() {
        cin >> Rno;
        cin.ignore(); 
        cin.getline(Name, 20);
    }
    void Display() {
        cout << Rno << " " << Name << endl;
    }
};

void AddNewStudent() {
    fstream WriteFile;
    WriteFile.open("STUDENT.DAT", ios::binary | ios::in | ios::out | ios::app);

 
    STUD s;
    s.Enter();

    WriteFile.write((char*)&s, sizeof(STUD));

    WriteFile.close();
}

// Question 16:
class Item
{
    int Ino;
    char Item[20];
public:
    //Function to search and display the content from a particular record number
    void Search(int);
    //Function to modify the content of a particular record number
    void Modify(int);
};

void Item::Search(int RecNo)
{
    fstream File;
    File.open("STOCK.DAT", ios::binary | ios::in);

    File.seekg((RecNo - 1) * sizeof(Item)); //Statement 1

    File.read((char*)this, sizeof(Item));
    cout << Ino << " ==> " << Item << endl;
    File.close();
}

void Item::Modify(int RecNo)
{
    fstream File;
    File.open("STOCK.DAT", ios::binary | ios::in | ios::out);
    cin >> Ino;
    cin.getline(Item, 20);
    File.seekp((RecNo - 1) * sizeof(Item)); //Statement 2
        File.write((char*)this, sizeof(Item));
    File.close();
}
int main()
{

    // Question 1:
    ofstream MyFile("NOTES.TXT");
    for (int i = 1; i <= 100; ++i)
    {
        MyFile << i << " ";
    }
    MyFile.close();

    // Question 2:
    string content = "Time is a great teacher but unfortunately it kills all its pupils. Berlioz";
    ofstream MyFile2("OUT.TXT");
    MyFile2 << content;
    MyFile2.close();

    // Question 3:
    ifstream ReadFile("OUT.TXT");
    char temp;
    int count = 0;
    while (!ReadFile.eof())
    {
        ReadFile.get(temp);
        if (isalpha(temp))
        {
            count += 1;
        }
    }
    cout << "Question 3: " << endl;
    cout << "Number of Characters in OUT.TXT = " << count << endl;
    ReadFile.close();

    // Question 4:
    ifstream ReadFile2("OUT.TXT");
    temp = NULL;
    count = 0;
    while (!ReadFile2.eof())
    {
        ReadFile2.get(temp);
        if (temp == ' ')
        {
            count += 1;
        }
    }
    cout << "Question 4: " << endl;
    cout << "Number of White Spaces in OUT.TXT = " << count << endl;
    ReadFile2.close();

    // Question 5:
    ifstream ReadFile3("OUT.TXT");
    count = 0;
    char temp2[30];
    bool inWord = false;
    while (!ReadFile3.eof())
    {
       // ReadFile3.get(temp2);
        ReadFile3 >> temp2;
        count += 1;

    }
    cout << "Question 5: " << endl;
    cout << "Number of Words in OUT.TXT = " << count << endl;
    ReadFile3.close();

    // Question 6:
    ifstream ReadFile4("STORY.TXT");
    char temp3[30];
    count = 0;
    while (!ReadFile4.eof())
    {
        ReadFile4 >> temp3;
        for (int i = 0; i < 30; ++i)
        {
            temp3[i] = tolower(temp3[i]);
        }
        if (!strcmp(temp3, "the"))
        {
            count += 1;
        }
    }
    cout << "Question 6: " << endl;
    cout << "Number of Instances of (the) in STORY.TXT = " << count << endl;
    ReadFile4.close();

    // Question 7:
    ifstream ReadFile5("STORY.TXT");
    char temp4[100];
    count = 0;
    while (!ReadFile5.eof())
    {
        ReadFile5.getline(temp4, 100);
        if (temp4[0] != 'A')
        {
            count += 1;
        }
    }
    cout << "Question 7: " << endl;
    cout << "Number of Lines that do not start with A in STORY.TXT = " << count << endl;
    ReadFile5.close();

    // Question 8:
    copyupper();

    // Question 9:
    vowelwords();

    // Question 10:
    EMPLOYEE newemp;
    cout << "Question 10: " << endl;
    cout << "Input the ENO and ENAME for the employee: " << endl;
    WriteToBinary();
    cout << "Reading from the .dat file: " << endl;
    ReadToBinary();

    // Question 12:
    cout << "Question 12: Records from SHIP.dat" << endl;
    
    readfile();

    // Question 13:
    cout << "Question 13: Students with Percentages > 75: " << endl;
    ShowStudentsOver75();

    // Question 15:
    cout << "Rno and Name for the new Student Object: " << endl;
    AddNewStudent();


}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
