#include "CourseTree.h"
#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

// Default Constructor sets root to null
CourseTree::CourseTree() {
	_root = nullptr;
	_size = 0;
}

CourseTree::~CourseTree() {
	delete _root;
}

// Public insert definition. If the root is nullptr, create new node and set to root
// otherwise call private _insert function
void CourseTree::insert(Course course) {
	if (_root == nullptr) {
		Node* node = new Node();
		node->course = course;
		_root = node;
		++this->_size;
	}
	else {
		_insert(_root, course);
	}
}

// Inserts the course into the tree
void CourseTree::_insert(Node* node, Course course) {
	// Insert to the left if it is less than and left node is nullptr
	if (course.id < node->course.id) {
		if (node->left == nullptr) {
			Node* newNode = new Node();
			newNode->course = course;
			node->left = newNode;
			++this->_size;
		}
		// Otherwise keep going left
		else {
			_insert(node->left, course);
		}
	}
	// Greater than
	else {
		// Insert to right if it is greater than and right node is nullptr
		if (node->right == nullptr) {
			Node* newNode = new Node();
			newNode->course = course;
			node->right = newNode;
			++this->_size;
		}
		// Otherwise keep going right
		else {
			_insert(node->right, course);
		}
	}
}

// Public function to print the tree
void CourseTree::print() {
	_print(_root);
}

// Traverse tree using in-order traversal
void CourseTree::_print(Node* node) {
	if (node == nullptr) {
		return;
	}

	// Go left
	_print(node->left);

	// Once done going left, print the course information
	cout << left << setw(15) << "Course Title:" << node->course.title << endl;
	cout << left << setw(15) << "Course ID: " << node->course.id << endl;
	cout << left << setw(15) << "Prerequisites: ";
	// Check size of prerequisites vector and print if there are any
	if (node->course.prerequisites.size() > 0) {
		// The tiernary operation is strictly for formatting, outputting a comma and space if the prereq is not
		// the last prereq in the vector
		for (string prereq : node->course.prerequisites) {
			cout << prereq << ((prereq == node->course.prerequisites.at(node->course.prerequisites.size() - 1)) ? "" : ", ");
		}
	}
	// No Prerequisites
	else {
		cout << "NO PREREQUISITES";
	}
	cout << endl << endl;

	// Go right
	_print(node->right);
}

// Public search method
Course CourseTree::search(string courseId) {
	return _search(_root, courseId);
}

// Search for a course in the tree
Course CourseTree::_search(Node* node, string courseId) {
	// Initialize empty course. This will be returned empty to indicate
	// an unsuccessful search
	Course course;

	// Base case that node is nullptr (not found)
	if (node == nullptr) {
		return course;
	}
	
	// We found the courseId!!!!
	if (courseId == node->course.id) {
		return node->course;
	}
	
	// Not a match, if courseId is less than the current node's courseId, go left
	if (courseId < node->course.id) {
		return _search(node->left, courseId);
	}
	
	// Otherwise we are going right
	return _search(node->right, courseId);
}

// Public method to validate courses.
void CourseTree::validateCourses(){
	_validateCourses(_root);
}

// Validate that each course with prequisites contain valid prerequisites.
// This will be done by traversing the tree.
void CourseTree::_validateCourses(Node* node) {
	// Base case if our node is nullptr
	if (node == nullptr) {
		return;
	}

	// Iterate all prerequisites for a course. Because we're using
	// a range loop, it will not iterate if prerequisites is empty
	for (string prereq : node->course.prerequisites) {
		// If the search does not return a course for the prerequisite courseId, remove it.
		if (search(prereq).id.empty()) {
			cout << "Prerequisite not found for " << node->course.title << endl;
			_remove(_root, node->course.id);
			return;
		}
	}

	// Validate left then right. We are using pre-order traversal, just because.
	_validateCourses(node->left);
	_validateCourses(node->right);
}

// Public method to remove a course
void CourseTree::remove(string courseId){
	_remove(_root, courseId);
}

// Remove a node from the course, using courseId
Node* CourseTree::_remove(Node* node, string courseId){
	// Base case that the current node is null
	if (node == nullptr) {
		return node;
	}

	if (courseId < node->course.id) { // courseId is less than the current node, so go left
		node->left = _remove(node->left, courseId); // set left node after deletion
	}
	else if (courseId > node->course.id) { // courseId is greater than the current node, so go right
		node->right = _remove(node->right, courseId); // set right node after deletion
	}
	else { // This is the node we are looking to delete
		if (node->left == nullptr && node->right == nullptr) { // This is a leaf
			delete node;
			--this->_size;
			return nullptr;
		}
		else if (node->left == nullptr) { // There is only a right child tree, so delete the node and return the right subtree
			Node* tempNode = node->right;

			// Set left and right nodes to null, as to not destroy the subtrees when deleting the node due to chained deconstructors
			node->right = nullptr;
			node->left = nullptr;
			delete node;
			--this->_size;
			return tempNode;
		}
		else if (node->right == nullptr) { // There is only a left child tree, so delete the node and return the left subtree
			Node* tempNode = node->left;

			// Set left and right nodes to null, as to not destroy the subtrees when deleting the node due to chained deconstructors
			node->right = nullptr;
			node->left = nullptr;
			delete node;
			--this->_size;
			return tempNode;
		}

		// This is a fall-through condition indicating there are two child trees to the current node
		// Find the current nodes successor and set the successor's right node to the current node's right node
		Node* successorNode = _successor(node->right);
		successorNode->right = node->right;

		// Set left and right nodes to null, as to not destroy the subtrees when deleting the node due to chained deconstructors
		node->right = nullptr;
		node->left = nullptr;
		delete node;
		--this->_size;
		return successorNode;
	}

	// Return node to be assigned to left, right of parent appropriately.
	return node;
}

Node* CourseTree::_successor(Node* node) {
	// Finds the left most node in a subtree. 

	// If the left node is null, we have the left most node, return it
	if (node->left == nullptr) {
		return node;
	}

	// Keep looking.
	_successor(node->left);

}

int CourseTree::size() {
	return _size;
}