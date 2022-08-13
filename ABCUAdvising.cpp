// ABCUAdvising.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <vector>
#include "Course.h"
#include "CourseTree.h"

using namespace std;

// Function declarations. This was mostly done so I didn't have to move
// function definitions when they were declared after they were accessed.
vector<string> splitString(string& text, char delim);
void printCourse(Course course);
void loadCourses(string fileName, CourseTree* courseTree);
void printMenu();
string centerText(string text, int colWidth);
void wait(string displayText);

int main()
{
	// Initialize application variables
	CourseTree* courseTree = new CourseTree();
	string fileName, courseId;
	Course course;
	int userInput = -99;
	
	// Main application loop
	while (userInput != 9) {
		// Print the menu
		printMenu();

		// Collect user imput.
		cout << "Please select an option: ";
		cin >> userInput;
		// Checking for cin.fail() ensures that cin parsed
		// the input to the proper data type. Clear cin error flag
		// and ignore all string input up to the newline character.
		if (cin.fail()) {
			cin.clear();
			cin.ignore(INT_MAX, '\n');
			continue;
		}

		// Application routing logic
		switch (userInput) {
		// Load course data
		case 1:
			// Collect file name from user and load the courses
			cout << "Enter course data file name: ";
			cin >> fileName;
			loadCourses(fileName, courseTree);
			// Validate the course
			courseTree->validateCourses();
			cout << courseTree->size() << " have been loaded." << endl;
			wait("Press <ENTER> to return to the menu.");
			break;
		// Print all courses, obviously
		case 2:
			if (courseTree->size() > 0) {
				courseTree->print();
			}
			else {
				cout << "Course data must be loaded before printing." << endl;
			}
			wait("Press <ENTER> to return to the menu.");
			break;
		// Search for a course and print its summary
		case 3:
			if (courseTree->size() > 0) {
				// Get courseId from user input for which to search
				cout << "Enter course id: ";
				cin >> courseId;
				course = courseTree->search(courseId);
				// Display the course summary
				if (!course.id.empty()) {
					printCourse(course);
				}
				// If the course was not found, tell the user such
				else {
					cout << "Course " << courseId << " was not found." << endl;
				}
			}
			else {
				cout << "Course data must be loaded before printing." << endl;
			}

			wait("Press <ENTER> to return to the menu.");
			break;
		
		// Remove a user specified course
		case 4:
			if (courseTree->size() > 0) {
				cout << "Enter course id: ";
				cin >> courseId;
				courseTree->remove(courseId);
			}
			else {
				cout << "There are no course available to be deleted." << endl;
			}
			wait("Press <ENTER> to return to the menu.");
			break;
		case 9:
			break;
		default:
			cout << "Invalid selection." << endl;
			wait("Press <ENTER> to return to the menu.");
		}
	}
	
	// Free memory upon program exit. Also verify deconstructor is working by checking output.
	delete courseTree;
}


void loadCourses(string fileName, CourseTree* courseTree) {
	// Initialize variables for course file and the CourseTree
	string textLine;

	// Initilize ifstream and open file
	ifstream file;
	file.open(fileName);

	// Continue while we are able to retrieve a line
	while (getline(file, textLine)) {

		// Initialize courseData with output from splitString
		vector<string> courseData = splitString(textLine, ',');

		// Course data must contain at least an Id and Title
		if (courseData.size() < 2) {
			cout << "Course not loaded: Course data must include at minimum an Id and Title" << endl;
			continue;
		}

		// Create the course from the course data
		Course course;
		course.id = courseData.at(0);
		course.title = courseData.at(1);

		// We have at the least the minimum number of entries, but are they populated?
		if (courseData.size() >= 2) {
			if (courseData.at(0).empty() || courseData.at(1).empty()) {
				cout << "Course not loaded: Course data must include at minimum an Id and Title" << endl;
				continue;
			}
			
			// If course data is greater than 2, we have prereqs!!! 
			if (courseData.size() > 2) {
				// Since c++ 11, we can use the vector constructor with a vector's begin and end iterators to return
				// a sub vector. We are utilizing this with a range-based loop, also c++ 11, to get the prereqs.
				for (string prereq : vector<string>(courseData.begin() + 2, courseData.end())) {
					// Make sure the prereq is not an empty string
					if (!prereq.empty()) {
						course.prerequisites.push_back(prereq);
					}
				}
			}
		}
		// insert the course
		courseTree->insert(course);
	}
	file.close();
}

// Helper function to split a string via delimiter
vector<string> splitString(string& text, char delim) {
	// vector<string> that function will return
	vector<string> returnVector;
	
	// Initialize the begining index for string.find and the ending index
	int beginIndex = 0;
	int endIndex = 0;
	
	// If there is no delimiter, use the entire string by setting endIndex to end of string
	endIndex = text.find(delim, beginIndex);
	if (endIndex < 0) {
		endIndex = text.length();
	}

	// Loop until the end of the string has been reached.
	while (beginIndex < text.length() - 1) {
		
		// Get the substring from the beginIndex to the endIndex, which is (endIndex - beginIndex) number of characters
		returnVector.push_back(text.substr(beginIndex, endIndex - beginIndex));
		// Set the beginIndex to the character position after the found delimiter
		beginIndex = endIndex + 1;
		
		// Find delimiter, and if it is not found, set endIndex to end of string
		endIndex = text.find(delim, beginIndex);
		if (endIndex < 0) {
			endIndex = text.length();
		}

		// The process will repeat itself. Easy Peasy!!!
	}

	return returnVector;
}

// Helper function to print a course. Same functionality as the print done
// in the CourseTree::print() method, without the traversal.
void printCourse(Course course) {
	cout << endl;
	cout << left << setw(15) << "Course Title:" << course.title << endl;
	cout << left << setw(15) << "Course ID: " << course.id << endl;
	cout << left << setw(15) << "Prerequisites: ";
	// Check size of prerequisites vector and print if there are any
	if (course.prerequisites.size() > 0) {
		// The tiernary operation is strictly for formatting, outputting a comma and space if the prereq is not
		// the last prereq in the vector
		for (string prereq : course.prerequisites) {
			cout << prereq << ((prereq == course.prerequisites.at(course.prerequisites.size() - 1)) ? "" : ", ");
		}
	}
	// No Prerequisites
	else {
		cout << "NO PREREQUISITES";
	}
	cout << endl << endl;
}

void printMenu() {
	// String that sets cursor to top left. Doesn't truly clear the screen,
	// but is a better visual experience than always seeing previous output.
	// Fater than system("CLS"), but can still scroll up to view previous output
	const string CLS = "\033[2J\033[1;1H";
	
	// Initialize variables for menu formatting.
	const int PADDING = 5;
	const int LINE_WIDTH = 101;
	const char PADDING_CHAR = ' ';
	const char BORDER_CHAR = '*';
	const string PAD_STRING = string(PADDING, PADDING_CHAR);
	
	// "CLEAR SCREEN" then print the menu
	cout << CLS;
	cout << string(LINE_WIDTH, BORDER_CHAR) << endl;
	cout << BORDER_CHAR << PAD_STRING << centerText("ABCU COURSE PLANNER", (LINE_WIDTH - (PADDING * 2) - 2)) << PAD_STRING << BORDER_CHAR << endl;
	cout << string(LINE_WIDTH, BORDER_CHAR) << endl;
	cout << PAD_STRING << "1. Load Course Material" << endl;
	cout << PAD_STRING << "2. Print Course List" << endl;
	cout << PAD_STRING << "3. Print Specific Course" << endl;
	cout << PAD_STRING << "4. Delete a Specific Course" << endl;
	cout << PAD_STRING << "9. Exit" << endl << endl;
}

// Help function to center text within a given column width.
string centerText(string text, int colWidth) {
	int paddingSize = 0;
	string fill;
	paddingSize = (colWidth - text.length()) / 2;
	fill = string(paddingSize, ' ');
	return fill + text + fill;
}

// Helper function to wait for user input before continuing.
void wait(string displayText) {
	// Display specified text.
	cin.ignore(INT_MAX, '\n');
	cout << displayText;
	// This loop is necessary to prevent screens from being skipped if user presses a key before <ENTER>.
	while (cin.peek() != '\n') {
		cin.ignore();
	}
	cin.get();
	cin.clear();
}