#pragma once

// This file defines the container of the students.

#include <memory>
#include "student.h"

// A node of a student, which includes the pointer to the next node.
struct StudentNode{
    Student student;
    std::unique_ptr<StudentNode> next;

    StudentNode(Student student) : student(student), next(nullptr) {}
};

// The class which includes operations of the students.
class Students{
private:
    std::unique_ptr<StudentNode> head;

    // Get the pointer to the student by id.
    /**
     * @param id The id of the student.
     * @return The pointer to the student node.
     * @exception std::string When the id does not exist.
     */
    StudentNode* getById(long long id);

    // See if the id exists in the container.
    // TESTED.
    bool idExists(long long id);

    // Swap the value of two student nodes. Be cautious about abuse.
    // TESTED.
    void swap(StudentNode* a, StudentNode* b);

    // Sub functions of a quick sort.
    StudentNode* oneSortStep(StudentNode* begin, StudentNode* end);
    void subSort(StudentNode* begin, StudentNode* end);
    // Sort the students.
    // TESTED.
    void sort();

public:
    // It allows to initialize an empty container.
    Students();

    // Add a new student to the container.
    // Check if the id exists.
    // TESTED.
    void addStudent(Student student);

    // Get the information by the student ID.
    // TESTED.
    /**
     * @exception std::string When the id does not exist.
     */
    Student getStudentById(long long id);
    // Get the information by the student name.
    // TESTED.
    /**
     * @exception std::string When the name does not exist.
     */
    Student getStudentByName(const char *name);

    // Revise the score of the student by ID.
    /**
     * @exception std::string When the id does not exist.
     */
    void setMathScore(long long id, Score score);
    void setEnglishScore(long long id, Score score);
    void setProgrammingScore(long long id, Score score);
    void setDataStructureScore(long long id, Score score);

    // Get the info of the students via a string.
    // WARNING: This function allocs a new char array on the memory.
    // Remember to deal with its life period currectly.
    /**
     * @return const char* The info of the students.
     */
    // TESTED.
    const char* getInfo();

    // Get the info of the students via a string, used by the Qt function.
    const char* getTable();

    // The test case.
    friend void testStudents();
};