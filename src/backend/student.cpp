#include "student.h"

// The constructor of `StudentInfo`.
StudentInfo::StudentInfo(
    Gender gender,
    Score english_score,
    Score math_score,
    Score programming_score,
    Score data_structure_score
):
    gender(gender),
    english_score(english_score),
    math_score(math_score),
    programming_score(programming_score),
    data_structure_score(data_structure_score),
    rank(0)
{
    if (
        english_score>100 ||
        math_score>100 ||
        programming_score>100 ||
        data_structure_score>100
    ){
        throw "Error: The score should be less than 100.";
    }
    calcTotalScore();
}

// The function to calculate the total score of the student.
void StudentInfo::calcTotalScore(){
    total_score = english_score + math_score + programming_score
        + data_structure_score;
}

// The constructor of `Student`.
Student::Student(
    long long id,
    const char *name,
    StudentInfo info
):
    id(id),
    name(name),
    info(info)
{}

long long Student::getId(){
    return id;
}
const char *Student::getName(){
    return name.c_str();
}

// Revise the score of a student.
void Student::setMathScore(Score new_score){
    info.math_score = new_score;
    info.calcTotalScore();
}
void Student::setEnglishScore(Score new_score){
    info.english_score = new_score;
    info.calcTotalScore();
}
void Student::setProgrammingScore(Score new_score){
    info.programming_score = new_score;
    info.calcTotalScore();
}
void Student::setDataStructureScore(Score new_score){
    info.data_structure_score = new_score;
    info.calcTotalScore();
}

void Student::setRank(Rank new_rank){
    info.rank = new_rank;
}

// Get the information of the student.
StudentInfo Student::getInfo(){
    return info;
}

bool Student::operator> (const Student &other) const{
    return this->info.total_score > other.info.total_score;
}

bool Student::operator< (const Student &other) const{
    return this->info.total_score < other.info.total_score;
}