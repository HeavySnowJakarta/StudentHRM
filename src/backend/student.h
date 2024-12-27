#pragma once

#include <string>

typedef unsigned int Score;
typedef unsigned int Rank;

enum class Gender{
    Male,
    Female,
    NonBinary
};

// The information detail of a student.
// TESTED.
/**
 * @exception const char * When the score is higher than 100.
 */
struct StudentInfo{
    Gender gender;
    Score english_score;
    Score math_score;
    Score programming_score;
    Score data_structure_score;
    Score total_score;
    Rank rank;

    StudentInfo(
        Gender gender,
        Score english_score,
        Score math_score,
        Score programming_score,
        Score data_structure_score
    );

    void calcTotalScore();
};

// This file defines the structure of a student.
class Student{
private:
    long long id;
    std::string name;
    StudentInfo info;

public:
    // TESTED.
    Student(long long id, const char *name, StudentInfo info);

    // BOTH ARE TESTED.
    // Get the id of a student.
    long long getId();
    // Get the name of a student.
    const char *getName();

    // Revise the score of a student.
    void setMathScore(Score new_score);
    // TESTED.
    void setEnglishScore(Score new_score);
    void setProgrammingScore(Score new_score);
    void setDataStructureScore(Score new_score);

    void setRank(Rank new_rank);

    // Get the information of a student.
    // TESTED.
    StudentInfo getInfo();

    // See if a student's total score is higher than another student's.
    // TESTED.
    bool operator> (const Student &other) const;

    // See if a student's total score is smaller to another student's.
    bool operator< (const Student &other) const;
};