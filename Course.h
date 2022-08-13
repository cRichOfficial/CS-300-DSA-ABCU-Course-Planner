#pragma once

#include <string>
#include <vector>

using namespace std;

struct Course
{
	// Default constructor to allow for creating an empty Course
	Course(){

	}

	// Constructor
	Course(string courseId, string courseTitle) {
		id = courseId;
		title = courseTitle;
	}

	// Properties
	string id;
	string title;
	vector<string> prerequisites;
};

