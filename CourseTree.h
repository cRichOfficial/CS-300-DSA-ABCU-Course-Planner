//============================================================================
// Name        : CourseTree.h
// Author      : Christopher Richards
// Email	   : christopher.richards4@snhu.edu
// Version     : 1.0
// Copyright   : Copyright © 2022 Chris Richards
//============================================================================

#pragma once
#include <iostream>
#include "Course.h"

using namespace std;

struct Node;
class CourseTree;

class CourseTree
{
	
public:
	CourseTree();
	~CourseTree();
	void insert(Course course);
	void print();
	Course search(string courseId);
	void validateCourses();
	void remove(string courseId);
	int size();

private:
	void _insert(Node* node, Course course);
	void _print(Node* node);
	Course _search(Node* node, string courseId);
	void _validateCourses(Node* node);
	Node* _remove(Node* node, string courseId);
	Node* _successor(Node* node);

	int _size;
	Node* _root;
};

// Node stuct to conatain course information
struct Node
{
	// Constructor
	Node() {
		left = nullptr;
		right = nullptr;
	}

	// Destructor. This will recursively delete all child nodes.
	~Node() {
		cout << "Deleting " << course.id << endl;
		delete left;
		delete right;
	}

	// Properties of Node
	Course course;
	Node* left;
	Node* right;
};

