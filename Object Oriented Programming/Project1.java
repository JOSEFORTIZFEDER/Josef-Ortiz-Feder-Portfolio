/*
 * Project 1
 * Josef Ortiz-Feder
 */
package project;

import java.util.Scanner;

public class Project1 {

	public static void main(String[] args) {
		Scanner scnr = new Scanner(System.in);
		boolean flag = true, studentFlag = false, staffFlag = false, facultyFlag = false;
		String menuInput, facultyName = "", facultyID = "", facultyRank = "", facultyDepartment = "";
		String studentName1="", studentID1="";
		String studentName2="", studentID2="";
		String staffName = "", staffID = "", staffDepartment = "", staffStatus="";
		String overrideInput="";
		int studentCH1=0, studentCH2=0, studentInput;
		double studentGPA1=0, studentGPA2=0;
		System.out.println("Choose one of the options:\n");
		// Big while loop that loops until the user enters 7
		while(flag)
		{
			
			menuInput = printMenu();
			if(menuInput.equals("1"))
			{
				if(facultyFlag)
				{
					while(true)
					{
						System.out.println("You already have a faculty member filled in. Do you want to update their information?");
						System.out.print("Yes or No: ");
						overrideInput = scnr.nextLine();
						if(testOverride(overrideInput))
						{
							break;
						}
						System.out.println("\t" + overrideInput + " is invalid");
					}
					overrideInput = overrideInput.toLowerCase();
					if(overrideInput.equals("no"))
						continue;
					
				}
				System.out.println("Enter faculty info:");
				System.out.print("\tName of the faculty: ");
				facultyName = scnr.nextLine();
				System.out.print("\n\n\tID: ");
				facultyID = scnr.nextLine();
				while(true)
				{
					System.out.print("\n\n\tRank: ");
					facultyRank = scnr.nextLine();
					if(testRank(facultyRank))
					{
						break;
					}
					System.out.println("\t" + facultyRank + " is invalid");
				}
				while(true)
				{
					System.out.print("\n\n\tDepartment: ");
					facultyDepartment = scnr.nextLine();
					if(testDepartment(facultyDepartment))
					{
						break;
					}
					System.out.println("\t" + facultyDepartment + " is invalid");
					
				}
				System.out.println("\nFaculty successfully added!");
				facultyFlag = true;
				
			}
			else if(menuInput.equals("2"))	
			{
				if(studentFlag)
				{
					while(true)
					{
						System.out.println("You already have students filled in. Do you want to update their information?");
						System.out.print("Yes or No: ");
						overrideInput = scnr.nextLine();
						if(testOverride(overrideInput))
						{
							break;
						}
						System.out.println("\t" + overrideInput + " is invalid");
					}
					overrideInput = overrideInput.toLowerCase();
					if(overrideInput.equals("no"))
						continue;
					
				}
				System.out.println("Enter student 1 info:");
				System.out.print("\tName of Student: ");
				studentName1 = scnr.nextLine();
				System.out.print("\n\tID: ");
				studentID1 = scnr.nextLine();
				System.out.print("\n\tGpa: ");
				studentGPA1  = Double.parseDouble(scnr.nextLine());
				System.out.print("\n\tCredit hours: ");
				studentCH1 = Integer.parseInt(scnr.nextLine());
				
				System.out.println("Thanks!");
				
				System.out.println("Enter student 2 info:");
				System.out.print("\tName of Student: ");
				studentName2 = scnr.nextLine();
				System.out.print("\n\tID: ");
				studentID2 = scnr.nextLine();
				System.out.print("\n\tGpa: ");
				studentGPA2  = Double.parseDouble(scnr.nextLine());
				System.out.print("\n\tCredit hours: ");
				studentCH2 = Integer.parseInt(scnr.nextLine());
				
				System.out.println("Thanks!");
				
				studentFlag = true;
			}
			else if(menuInput.equals("3"))
			{
				if(!studentFlag)
				{
					System.out.println("Sorry! No students have been added");
				}
				else
				{
					System.out.print("Which student? Enter 1 for " + studentName1 + " or Enter 2 for " + studentName2 + "? ");
					studentInput = Integer.parseInt(scnr.nextLine());
					if(studentInput == 1)
						printInvoice(studentName1, studentID1, studentGPA1, studentCH1);
					else if(studentInput == 2)
						printInvoice(studentName2, studentID2, studentGPA2, studentCH2);

				}
			}
			else if(menuInput.equals("4"))
			{
				if(facultyFlag)
				{
					printFaculty(facultyName, facultyID, facultyDepartment, facultyRank);
				}
				else
					System.out.println("Sorry! No faculty member entered yet\n\n");
			}
			else if(menuInput.equals("5"))
			{
				if(staffFlag)
				{
					
					while(true)
					{
						System.out.println("You already have a staff member filled in. Do you want to update their information?");
						System.out.print("Yes or No: ");
						overrideInput = scnr.nextLine();
						if(testOverride(overrideInput))
						{
							break;
						}
						System.out.println("\t" + overrideInput + " is invalid");
					}
					overrideInput = overrideInput.toLowerCase();
					if(overrideInput.equals("no"))
						continue;
				}
				
				System.out.println("Enter staff info: ");
				System.out.print("\tName of the staff member: ");
				staffName = scnr.nextLine();
				System.out.print("\n\tEnter the ID: ");
				staffID = scnr.nextLine();
				while(true)
				{
					System.out.print("\n\tDepartment: ");
					staffDepartment = scnr.nextLine();
					if(testDepartment(staffDepartment))
					{
						break;
					}
					System.out.println("\t" + staffDepartment + " is invalid");
				}
				while(true)
				{
					System.out.print("\tStatus, Enter P for part time or enter F for full time: ");
					staffStatus = scnr.nextLine();
					if(testStatus(staffStatus))
					{
						break;
					}
					System.out.println("\t" + staffStatus + " is invalid");

				}
				
				System.out.print("\n");
				
				System.out.println("Staff member added!");
				staffFlag = true;
			}
			else if(menuInput.equals("6"))
			{
				if(staffFlag)
					printStaff(staffName, staffID, staffDepartment, staffStatus);
				else
					System.out.println("Sorry! No staff member has been added\n\n");
			}
			else if(menuInput.equals("7"))
			{
				flag = false;
			}
			else
			{
				System.out.println("\nInvalid entry- please try again\n");
			}
			System.out.println("\n");
			scnr.reset();
			
		}
		System.out.println("\n\n\nGoodbye!");
		
	}
	
	// This method outputs the menu and prompts the user to enter a value. 
	public static String printMenu()
	{
		String menuInput;
		Scanner scnr = new Scanner(System.in);
		
		System.out.println("1- Enter the information of the faculty");
		System.out.println("2- Enter the information of the two students");
		System.out.println("3- Print tuition invoice");
		System.out.println("4- Print faculty information");
		System.out.println("5- Enter the information of the staff member");
		System.out.println("6- Print the information of the staff member");
		System.out.println("7- Exit Program");
		System.out.print("\n\tEnter your selection: ");
		
		menuInput = scnr.nextLine();
		
		
		return menuInput;
	}
	// This method outputs the faculty information by taking in parameters, setting them to lower case, and then setting the first letter to uppercase
	public static void printFaculty(String name, String ID, String department, String rank)
	{
		name = name.toLowerCase();
		name = name.substring(0 , 1).toUpperCase() + name.substring(1);
		department = department.toLowerCase();
		department = department.substring(0, 1).toUpperCase() + department.substring(1);
		rank = rank.toLowerCase();
		rank = rank.substring(0, 1).toUpperCase() + rank.substring(1);
		
		System.out.println("----------------------------------");
		System.out.println("" + name + "\t" + ID);
		System.out.println("" + department + " Department,  " + rank);
		System.out.println("----------------------------------");
	}
	// This method outputs the staff information by taking in parameters, setting them to lower case, and then setting the first letter to uppercase
	public static void printStaff(String name, String ID, String department, String status)
	{
		name = name.toLowerCase();
		name = name.substring(0 , 1).toUpperCase() + name.substring(1);
		department = department.toLowerCase();
		department = department.substring(0, 1).toUpperCase() + department.substring(1);
		status = status.toLowerCase();
		if(status.equals("f"))
			status = "Full Time";
		else
			status = "Part Time";
		System.out.println("----------------------------------");
		System.out.println("" + name + "\t" + ID);
		System.out.println("" + department + " Department, " + status);
		System.out.println("----------------------------------");

	}
	// This method outputs the student invoice by calculating the total cost and then outputting the information
	public static void printInvoice(String name, String ID, double gpa, int credits)
	{
		double total = (credits * 236.45) + 52, discount = 0; 
		if(gpa >= 3.85)
		{
			discount = total*0.15;
			total -= discount;
		}
		name = name.substring(0 , 1).toUpperCase() + name.substring(1);
		System.out.println("Here is the tuition invoice for " + name + " :\n");
		System.out.println("--------------------------------------------------------------------");
		System.out.println(name + "\t" + ID);
		System.out.println("Credit Hours: " + credits + " ($236.45/credit hour)");
		System.out.println("Fees: $52\n");
		System.out.println("Total payment (after discount): $" + String.format("%.2f", total) + "\t($" + String.format("%.2f", discount) + " discount applied)");
		System.out.println("--------------------------------------------------------------------");

	}
	// This method tests the input done by the user to make sure the user inputs a correct value
	public static boolean testRank(String rankTest)
	{
		String[] possibleRanks = {"professor", "adjunct"};
		rankTest = rankTest.toLowerCase();
		for(int i = 0; i < possibleRanks.length; ++i)
		{
			if(rankTest.equals(possibleRanks[i]))
			{
				return true;
			}
		}
		return false;
	}
	// This method tests the input done by the user to make sure the user inputs a correct value
	public static boolean testDepartment(String departmentTest)
	{
		String[] possibleDepartments = {"mathematics", "engineering", "english"};
		departmentTest = departmentTest.toLowerCase();
		for(int i = 0; i < possibleDepartments.length; ++i)
		{
			if(departmentTest.equals(possibleDepartments[i]))
				return true;
		}
		return false;
	}
	// This method tests the input done by the user to make sure the user inputs a correct value
	public static boolean testStatus(String statusTest)
	{
		String[] possibleRanks = {"f", "p"};
		statusTest = statusTest.toLowerCase();
		for(int i = 0; i < possibleRanks.length; ++i)
		{
			if(statusTest.equals(possibleRanks[i]))
			{
				return true;
			}
		}
		return false;
	}
	// This method tests the input done by the user to make sure the user inputs a correct value. (I use this in my logic pertaining to faculty, staff, and students)
	public static boolean testOverride(String overrideTest)
	{
		String[] possibleValues = {"yes", "no"};
		overrideTest = overrideTest.toLowerCase();
		for(int i = 0; i < possibleValues.length; ++i)
		{
			if(overrideTest.equals(possibleValues[i]))
			{
				return true;
			}
		}
		return false;
	}
}
