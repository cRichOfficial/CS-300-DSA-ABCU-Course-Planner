//============================================================================
// Name        : Course.cpp
// Author      : Christopher Richards
// Email	   : christopher.richards4@snhu.edu
// Version     : 1.0
// Copyright   : Copyright © 2022 Chris Richards
//============================================================================

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

