 /*
 * Project 3
 * Josef Ortiz-Feder
 */
package project3;

import java.util.Scanner;
import java.io.File;
import java.io.FileWriter;
import java.time.format.DateTimeFormatter;  
import java.time.LocalDateTime;

public class Project3 
{
	public static void main(String[] args) throws Exception
	{
		// Variables
		String menuInput, name, ID="", dept, rank, status;
		double gpa=0;
		int credits;
		boolean flag = true;
		int i = 0; 
		Scanner scnr = new Scanner(System.in);
		
		Person[] list = new Person[100];
		System.out.println("Welcome to my Personal Management Program\n\n");
		// Big while loop that loops until the user enters 7
		while(flag)
		{
			menuInput = printMenu();
			if(menuInput.equals("1"))
			{
				
				System.out.println("Enter faculty info:");
				System.out.print("\tName of the faculty: ");
				name = scnr.nextLine();
				System.out.print("\n\n\tID: ");
				ID = scnr.nextLine();
				while(!testID(ID))
				{
					try {
						if(!testID(ID))
						{
							throw new IdException("Invalid ID format. Must be LetterLetterDigitDigitDigitDigit");
						}
					}catch(IdException ex)
					{
						System.out.println(ex.getMessage());
					}
					System.out.print("\n\n\tID: ");
					ID = scnr.nextLine();
				}
				
				while(true)
				{
					System.out.print("\n\n\tRank: ");
					rank = scnr.nextLine();
					if(testRank(rank))
					{
						break;
					}
					System.out.println("\t" + rank + " is invalid");
				}
				while(true)
				{
					System.out.print("\n\n\tDepartment: ");
					dept = scnr.nextLine();
					if(testDepartment(dept))
					{
						break;
					}
					System.out.println("\t" + dept + " is invalid");
					
				}
				Faculty faculty = new Faculty(rank, dept, name, ID);
				list[i] = faculty;
				++i;
			}
			else if(menuInput.equals("2"))
			{
				System.out.println("Enter student 1 info:");
				System.out.print("\tName of Student: ");
				name = scnr.nextLine();
				System.out.print("\n\tID: ");
				ID = scnr.nextLine();
				while(!testID(ID))
				{
					try {
						if(!testID(ID))
						{
							throw new IdException("Invalid ID format. Must be LetterLetterDigitDigitDigitDigit");
						}
					}catch(IdException ex)
					{
						System.out.println(ex.getMessage());
					}
					System.out.print("\n\n\tID: ");
					ID = scnr.nextLine();
				}
				
				System.out.print("\n\tGpa: ");
				try {
					gpa  = Double.parseDouble(scnr.nextLine());

				}catch(Exception ex)
				{
					System.out.println("\tInvalid input: Numerical Values Only\n\n");
					continue;
				}
				System.out.print("\n\tCredit hours: ");
				try {
					credits = Integer.parseInt(scnr.nextLine());
				}catch(Exception ex)
				{
					System.out.println("\tInvalid input: Numerical Values Only\n\n");
					continue;
				}
				
				System.out.println("Thanks!");
				Student student = new Student(gpa, credits, name, ID);
				list[i] = student;
				++i;
			}
			else if(menuInput.equals("3"))
			{
				System.out.print("Enter the student's id: ");
				ID = scnr.nextLine();
				System.out.println();
				for(int j = 0 ; j < list.length; ++j)
				{
					if(j==i)
					{
						System.out.println("No student matched!");
						break;
					}
					if(list[j].getID().equals(ID))
					{
						System.out.println("Here is the tuition invoice for " + list[j].getFullName());
						list[j].print();
						break;
					}
				
				}
			}
			else if(menuInput.equals("4"))
			{
				System.out.print("Enter the Faculty's id: ");
				ID = scnr.nextLine();
				System.out.println();
				for(int j = 0 ; j < list.length; ++j)
				{
					if(j==i)
					{
						System.out.println("No student matched!");
						break;
					}
					if(list[j].getID().equals(ID))
					{
						System.out.println();
						list[j].print();
						break;
					}
				}
			}
			else if(menuInput.equals("5"))
			{
				System.out.println("Enter staff info: ");
				System.out.print("\tName of the staff member: ");
				name = scnr.nextLine();
				System.out.print("\n\tEnter the ID: ");
				ID = scnr.nextLine();
				while(!testID(ID))
				{
					try {
						if(!testID(ID))
						{
							throw new IdException("Invalid ID format. Must be LetterLetterDigitDigitDigitDigit");
						}
					}catch(IdException ex)
					{
						System.out.println(ex.getMessage());
					}
					System.out.print("\n\n\tID: ");
					ID = scnr.nextLine();
				}
				while(true)
				{
					System.out.print("\n\tDepartment: ");
					dept = scnr.nextLine();
					if(testDepartment(dept))
					{
						break;
					}
					System.out.println("\t" + dept + " is invalid");
				}
				while(true)
				{
					System.out.print("\tStatus, Enter P for part time or enter F for full time: ");
					status = scnr.nextLine();
					if(testStatus(status))
					{
						break;
					}
					System.out.println("\t" + status + " is invalid");

				}
				
				System.out.print("\n");
				Staff staff = new Staff(status, name, ID, dept);
				list[i] = staff;
				++i;
				System.out.println("Staff member added!");
			}
			else if(menuInput.equals("6"))
			{
				System.out.print("Enter the Staff's id: ");
				ID = scnr.nextLine();
				System.out.println();
				for(int j = 0 ; j < list.length; ++j)
				{
					if(j==i)
					{
						System.out.println("No student matched!");
						break;
					}
					if(list[j].getID().equals(ID))
					{
						System.out.println();
						list[j].print();
						break;
					}
				}
			}
			else if(menuInput.equals("7"))
			{
				System.out.print("Would you like to create the report? (Y/N): ");
				menuInput = scnr.nextLine();
				if(menuInput.equals("Y") || menuInput.equals("y"))
				{
					System.out.println("\nReport created!");
					File file = new File("C:\\Users\\josef\\eclipse-workspace\\Project3\\src\\project3\\report.dat");

					FileWriter writer = new FileWriter(file);
					DateTimeFormatter dtf = DateTimeFormatter.ofPattern("MM/dd/yyyy");  
					LocalDateTime now = LocalDateTime.now();    
					writer.write("\tReport created on " + dtf.format(now));
					writer.write("\n\t****************");
					int counter = 1; 
					writer.write("\nFaculty Members\n----------------------\n");
					for(int j = 0; j < list.length; ++j)
					{
						if(j == i)
						{
							break;
						}
						if(list[j].isWhat().equals("Faculty"))
						{
							writer.write(list[j].toString(counter));
							counter++;
						}
					}
					
					writer.write("\nStaff Members\n----------------------\n");
					counter = 1; 
					for(int j = 0; j < list.length; ++j)
					{
						if(j == i)
						{
							break;
						}
						if(list[j].isWhat().equals("Staff"))
						{
							writer.write(list[j].toString(counter));
							counter++;
						}
					}
					
					writer.write("\nStudents\n----------------------\n");
					counter = 1; 
					for(int j = 0; j < list.length; ++j)
					{
						if(j == i)
						{
							break;
						}
						if(list[j].isWhat().equals("Student"))
						{
							writer.write(list[j].toString(counter));
							counter++;
						}
					}
					writer.close();
					
				}
				
				flag = false;
			}
			else
			{
				System.out.println("\nInvalid entry- please try again\n");
			}
			scnr.reset();
		}
		System.out.println("Goodbye!");
		scnr.close();
		
	}
	public static boolean testID(String ID)
	{
		boolean flag = false, flag2 = false, flag3 = false, flag4 = false, flag5 = false, flag6 = false;
		char[] alphabet = {'a', 'b', 'c', 'd', 'e', 'f', 'g','h','i', 'j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};
		char[] digits = {'1','2','3','4','5','6','7','8','9','0'};
		if(ID.length() != 6)
		{
			return false;
		}
		for(int i=0; i<alphabet.length; ++i)
		{
			if(ID.charAt(0) == alphabet[i])
			{
				flag = true;
			}
			if(ID.charAt(1) == alphabet[i])
			{
				flag2 = true;
			}	
		}
		for(int i = 0; i < digits.length; ++i)
		{
			if(ID.charAt(2) == digits[i])
			{
				flag3 = true;
			}
			if(ID.charAt(3) == digits[i])
			{
				flag4 = true;
			}
			if(ID.charAt(4) == digits[i])
			{
				flag5 = true;
			}
			if(ID.charAt(5) == digits[i])
			{
				flag6 = true;
			}
		}
		if(flag && flag2 && flag3 && flag4 && flag5 && flag6)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	// Method that prints the menu
	public static String printMenu()
	{
		String menuInput;
		Scanner scnr = new Scanner(System.in);
		
		System.out.println("1- Enter the information of a faculty");
		System.out.println("2- Enter the information of a student");
		System.out.println("3- Print tuition invoice for a student");
		System.out.println("4- Print faculty information");
		System.out.println("5- Enter the information for a staff member");
		System.out.println("6- Print the information for a staff member");
		System.out.println("7- Exit Program");
		System.out.print("\n\tEnter your selection: ");
		
		menuInput = scnr.nextLine();
		
		
		return menuInput;
	}
	// Method that checks the rank and see if it is professor or adjunct
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
}
class IdException extends Exception
{
	public IdException(String x)
	{
		super(x);
	}

}
abstract class Person
{
	private String fullName;
	private String ID;
	public abstract void print();
	public abstract String isWhat();
	public abstract String toString(int x);
	
	public Person(String fullName2, String ID2)
	{
		fullName = fullName2;
		ID = ID2;
	}
	
	public String getFullName(){return fullName;}
	public void setFullName(String name) {fullName = name;}
	
	public String getID() {return ID;}
	public void setID(String newID) {ID = newID;}
}
class Faculty extends Employee
{
	
	private String rank;
	
	public void setRank(String rankInput){rank = rankInput;}
	public String getRank() {return rank;}
	public String isWhat()
	{
		return "Faculty";
	}
	public String toString(int x)
	{
		return x + ". " + this.getFullName() + "\nID: " + this.getID() + "\n" + this.getRank() + ", " + this.getDepartment();
	}
	public Faculty(String rankInput, String departmentInput, String fullName, String ID)
	{
		super(fullName, ID, departmentInput);
		rank = rankInput;
	}

	@Override 
	public void print()
	{
	
		this.setFullName(this.getFullName().toLowerCase());
		this.setFullName(this.getFullName().substring(0 , 1).toUpperCase() + this.getFullName().substring(1));
		this.setDepartment(this.getDepartment().toLowerCase());
		this.setDepartment(this.getDepartment().substring(0, 1).toUpperCase() + this.getDepartment().substring(1));
		this.setRank(this.getRank().toLowerCase());
		this.setRank(this.getRank().substring(0, 1).toUpperCase() + this.getRank().substring(1));
		
		System.out.println("----------------------------------");
		System.out.println("" + this.getFullName() + "\t" + this.getID());
		System.out.println("" + this.getDepartment() + " Department,  " + rank);
		System.out.println("----------------------------------");
	}
}
abstract class Employee extends Person
{
	private String department;
	@Override
	public abstract void print();
	@Override
	public abstract String isWhat();
	@Override
	public abstract String toString(int x);
	public Employee(String fullName, String ID, String department2)
	{
		super(fullName, ID);
		department = department2;
	}
	
	public String getDepartment() {return department;}
	public void setDepartment(String newDept) {department = newDept;}
	
}

class Student extends Person
{
	private double GPA;
	private int creditHours;
	@Override
	public void print()
	{
		double total = (this.getCH() * 236.45) + 52, discount = 0; 
		if(this.getGPA() >= 3.85)
		{
			discount = total*0.15;
			total -= discount;
		}
		
		String name = this.getFullName().substring(0 , 1).toUpperCase() + this.getFullName().substring(1);
		System.out.println("----------------------------------");
		System.out.println(name + "\t" + this.getID());
		System.out.println("Credit Hours: " + this.getCH() + " ($236.45/credit hour)");
		System.out.println("Fees: $52\n");
		System.out.println("Total payment (after discount): $" + String.format("%.2f", total) + "\t($" + String.format("%.2f", discount) + " discount applied)");
		System.out.println("----------------------------------");
	}
	public String toString(int x)
	{
		return x + ". " + this.getFullName() + "\nID: " + this.getID() + "\nGpa: " + this.getGPA() + "\nCredit Hours: " + this.getCH();
	}
	public String isWhat()
	{
		return "Student";
	}
	public Student(double GPA2, int credit2, String fullName, String ID)
	{
		super(fullName, ID);
		GPA = GPA2;
		creditHours = credit2;
	}
	
	public double getGPA() {return GPA;}
	public void setGPA(double GPA2) {GPA = GPA2;}
	
	public int getCH() {return creditHours;}
	public void setCH(int newCH) {creditHours = newCH;}
	
}



class Staff extends Employee
{
	private String status;
	
	@Override
	public void print()
	{
		this.setFullName(this.getFullName().toLowerCase());
		this.setFullName(this.getFullName().substring(0 , 1).toUpperCase() + this.getFullName().substring(1));
		this.setDepartment(this.getDepartment().toLowerCase());
		this.setDepartment(this.getDepartment().substring(0, 1).toUpperCase() + this.getDepartment().substring(1));
		this.setStatus(this.getStatus().toLowerCase());
		
		if(this.getStatus().equals("f"))
			status = "Full Time";
		else
			status = "Part Time";
		System.out.println("----------------------------------");
		System.out.println("" + this.getFullName() + "\t" + this.getID());
		System.out.println("" + this.getDepartment() + " Department, " + status);
		System.out.println("----------------------------------");
	}
	
	public String isWhat()
	{
		return "Staff";
	}
	public String toString(int x)
	{
		return x + ". " + this.getFullName() + "\nID: " + this.getID() + "\n" + this.getDepartment() + ", " + this.getStatus();
	}
	public Staff(String status2, String fullName, String ID, String departmentInput)
	{
		super(fullName, ID, departmentInput);
		status = status2;
	}
	public String getStatus() {return status;}
	public void setStatus(String status2) {status = status2;}
}

