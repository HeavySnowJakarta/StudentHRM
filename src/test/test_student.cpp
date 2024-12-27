#include "test_student.h"
#include "student.h"
#include "students.h"

#include <iostream>
#include <memory>

void testStudent(){
    std::cout << "Now testing `Student`." << std::endl;
    StudentInfo infoA = StudentInfo(
        Gender::Male,
        80,
        70,
        90,
        85
    );

    Student studentA = Student(
        3,
        "John",
        infoA
    );

    StudentInfo infoB = StudentInfo(
        Gender::Female,
        10,
        20,
        30,
        40
    );

    Student studentB = Student(
        6,
        "Mary",
        infoB
    );

    std::cout << studentA.getInfo().math_score << std::endl;
    std::cout << studentA.getInfo().total_score << std::endl;
    studentA.setEnglishScore(75);
    std::cout << studentA.getInfo().total_score << std::endl;

    std::cout << "StudentA's name is " << studentA.getName() << std::endl;
    std::cout << "StudentB's id is " << studentB.getId() << std::endl;

    std::cout << "studentA>studentB == " << (studentA > studentB) << std::endl;
}

void testStudents(){
    std::cout << "Now testing `Students`." << std::endl;
    Students students;

    StudentInfo infoA = StudentInfo(
        Gender::Male,
        80,
        70,
        90,
        85
    );
    Student studentA = Student(
        3,
        "John",
        infoA
    );
    StudentInfo infoB = StudentInfo(
        Gender::Female,
        10,
        20,
        30,
        40
    );
    Student studentB = Student(
        6,
        "Mary",
        infoB
    );
    StudentInfo infoC = StudentInfo(
        Gender::Female,
        80,
        70,
        90,
        85
    );
    Student studentC = Student(
        7,
        "Alice",
        infoC
    );
    StudentInfo infoD = StudentInfo(
        Gender::Male,
        60,
        50,
        60,
        60
    );
    Student studentD = Student(
        8,
        "Bob",
        infoD
    );

    // Add the students.
    students.addStudent(studentA);
    students.addStudent(studentB);
    students.addStudent(studentC);
    students.addStudent(studentD);
    students.sort();
    std::cout << "Now the students are added." << std::endl;
    const char *info = students.getInfo();
    std::cout << info << std::endl;
    delete info;

    Student stuA = students.getStudentById(3);
    std::cout << "Student A's total score is " << stuA.getInfo().total_score
        << std::endl;

    Student stuB = students.getStudentByName("Mary");
    std::cout << "Student B's total score is " << stuB.getInfo().total_score
        << std::endl;

    if (students.idExists(3)){
        std::cout << "The id 3 exists." << std::endl;
    }
    else{
        std::cout << "The id 3 does not exist." << std::endl;
    }

    if (students.idExists(5)){
        std::cout << "The id 5 exists." << std::endl;
    }
    else{
        std::cout << "The id 5 does not exist." << std::endl;
    }

    StudentNode *nodeA = students.head.get();
    StudentNode *nodeB = students.head.get()->next.get();
    // students.swap(nodeA, nodeB);

    std::unique_ptr<const char> str (students.getInfo());
    std::cout << str.get() << std::endl;
    std::cout << "Now the info of the students are printed out." << std::endl;

    // students.addStudent(studentA);

    std::cout << "学号,姓名,性别,英语,数学,编程,数据结构,总分" << std::endl;
    const char *table = students.getTable();
    std::cout << table << std::endl;
    delete table;
}