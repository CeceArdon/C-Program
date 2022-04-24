//==========================================================
// Name         : ABCUAdvising.cpp
// Author       : Concepcion Ardon
// Version      : 1.0
// Description  : Project 2 Course/BinaryTreeSearch
//==========================================================

#include <iostream>
#include <time.h>

#include "CSVparser.hpp"

using namespace std;

//============================================================================
// Global definitions visible to all methods and classes
//============================================================================

// forward declarations
double strToDouble(string str, char ch);

// define a structure to hold course information
struct Course {
    string courseNumber; // unique identifier
    string courseTitle;
    string prerequisites1;
    string prerequisites2;

};

// Internal structure for tree node
struct Node {
    Course course;
    Node* left;
    Node* right;

    // create the key for the given course
    unsigned int key = hash(atoi(course.courseNumber.c_str()));
    Node* node = &(nodes.at(key));

    // if entry found for the key
    if (node != nullptr && node->key != UINT_MAX
        && node->course.courseNumber.compare(courseNumber) == 0) {
        return node->course;
    }

    // if no entry found for the key
    if (node == nullptr || node->key == UINT_MAX) {
        return course;
    }

    while (node != nullptr) {
        // if the current node matches, return it
        if (node->key != UINT_MAX && node->course.courseNumber.compare(courseNumber) == 0) {
            return node->course;
        }
        node = node->next;
    }

    return course;

};

//============================================================================
// Binary Search Tree class definition
//============================================================================

/**
 * Defines a class containing data members and methods to
 * implement a binary search tree
 */
class BinarySearchTree {

private:
    Node* root;

    void inOrder(Node* node);

    void postOrder(Node* node);

    void preOrder(Node* node);

public:
    BinarySearchTree();
    virtual ~BinarySearchTree();
    void InOrder();
    void PostOrder();
    void PreOrder();
    Course Search(string courseNumber);
};

/**
 * Default constructor
 */
BinarySearchTree::BinarySearchTree() {
    // initialize housekeeping variables
    //root is equal to nullptr
    root = nullptr;

}

/**
 * Destructor
 */
BinarySearchTree::~BinarySearchTree() {
    // recurse from root deleting every node
}

/**
 * Traverse the tree in order
 */
void BinarySearchTree::InOrder() {
    // In order root
    // call inOrder fuction and pass root 
    this->inOrder(root);
}

/**
 * Traverse the tree in post-order
 */
void BinarySearchTree::PostOrder() {
    // Post order root
    // postOrder root
    this->postOrder(root);

}

/**
 * Traverse the tree in pre-order
 */
void BinarySearchTree::PreOrder() {
    // Pre order root
    // preOrder root
    this->preOrder(root);
}


/**
 * Search for a course
 */
Course BinarySearchTree::Search(string courseNumber) {
    // Implement searching the tree for a course

    Node* cur = root; // set current node equal to root
     // keep looping downwards until bottom reached or matching courseNumber found
    while (cur != nullptr) {
        if (cur->course.courseNumber.compare(courseNumber) == 0) { // if match found, return current course
            return cur->course;
        }
        if (courseNumber.compare(cur->course.courseNumber) < 0) {  // if course is smaller than current node then traverse left
            cur = cur->left;
        }
        else {   // else larger so traverse right
            cur = cur->right;
        }
    }
    Course course;
    return course;
}

void BinarySearchTree::inOrder(Node* node) {
    // Inorder root

    if (node != nullptr) {  //if node is not equal to null ptr
        inOrder(node->left); //InOrder not left
        cout << node->course.courseNumber << ": " << node->course.courseTitle << " , " << node->course.prerequisites1 << " , " << node->course.prerequisites2 << endl;  //output bidID, title, amount, fund
        inOrder(node->right); //InOder right
    }
}
void BinarySearchTree::postOrder(Node* node) {
    // Post order root

    if (node != nullptr) { //if node is not equal to null ptr
        postOrder(node->left); //postOrder left
        postOrder(node->right); //postOrder right
        cout << node->course.courseNumber << ": " << node->course.courseTitle << ", " << node->course.prerequisites1 << ", " << node->course.prerequisites2 << endl; //output bidID, title, amount, fund
    }

}

void BinarySearchTree::preOrder(Node* node) {
    // Pre order root       
    if (node != nullptr) {  //if node is not equal to null ptr
        cout << node->course.courseNumber << ": " << node->course.courseTitle << ", " << node->course.prerequisites1 << ", " << node->course.prerequisites2 << endl; //output bidID, title, amount, fund
        postOrder(node->left);   //postOrder left
        postOrder(node->right);   //postOrder right
    }
}

//============================================================================
// Static methods used for testing
//============================================================================

/**
 * Display the course information to the console (std::out)
 *
 * @param course struct containing the course info
 */
void displayCourse(Course course) {
    cout << course.courseNumber << ": " << course.courseTitle << ", " << course.prerequisites1 << ", "
        << course.prerequisites2 << endl;
    return;
}

/**
 * Load a CSV file containing courses into a container
 *
 * @param csvPath the path to the CSV file to load
 * @return a container holding all the courses read
 */
void loadCourses(string csvPath, BinarySearchTree* bst) {
    cout << "Loading CSV file " << csvPath << endl;

    // initialize the CSV Parser using the given path
    csv::Parser file = csv::Parser(csvPath);

    // read and display header row - optional
    vector<string> header = file.getHeader();
    for (auto const& c : header) {
        cout << c << " , ";
    }
    cout << "" << endl;

    try {
        // loop to read rows of a CSV file
        for (unsigned int i = 0; i < file.rowCount(); i++) {

            // Create a data structure and add to the collection of courses
            Course course;
            course.courseNumber = file[i][1];
            course.courseTitle = file[i][0];
            course.prerequisites1 = file[i][8];
            course.prerequisites2 = file[i][4];
        }
    }
    catch (csv::Error& e) {
        std::cerr << e.what() << std::endl;
    }
}

/**
 * Simple C function to convert a string to a double
 * after stripping out unwanted char
 *
 * credit: http://stackoverflow.com/a/24875936
 *
 * @param ch The character to strip out
 */
double strToDouble(string str, char ch) {
    str.erase(remove(str.begin(), str.end(), ch), str.end());
    return atof(str.c_str());
}

/**
 * The one and only main() method
 */
int main(int argc, char* argv[]) {

    // process command line arguments
    string csvPath, courseKey;
    switch (argc) {
    case 2:
        csvPath = argv[1];
        courseKey = "csci400";
        break;
    case 3:
        csvPath = argv[1];
        courseKey = argv[2];
        break;
    default:
        csvPath = "ABCUAdvising.csv";
        courseKey = "csci400";
    }

    // Define a binary search tree to hold all course
    BinarySearchTree* bst;

    Course course;

    int choice = 0;
    while (choice != 9) {
        cout << "Menu:" << endl;
        cout << "  1. Load Bids" << endl;
        cout << "  2. Display All Bids" << endl;
        cout << "  3. Find Bid" << endl;
        cout << "  9. Exit" << endl;
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {

        case 1:
            bst = new BinarySearchTree();

            // Complete the method call to load the courses
            loadCourses(csvPath, bst);

            //cout << bst->Size() << " course read" << endl;
            break;

        case 2:
            bst->InOrder();
            break;

        case 3:
            ticks = clock();

            course = bst->Search(courseKey);


            if (!course.courseNumber.empty()) {
                displayCourse(course);
            }
            else {
                cout << "Course number " << courseKey << " not found." << endl;
            }


            break;
        }
    }

    cout << "Good bye." << endl;

    return 0;
}
