#include "students.h"
#include "student.h"
#include <memory>
#include <string>
#include <cstring>

Students::Students():
    head(nullptr)
{}

void Students::addStudent(Student new_student){
    if (idExists(new_student.getId())){
        throw std::string("Error: Student with id ")
            + std::to_string(new_student.getId()) + " already exists";
    }
    if (head == nullptr){
        head = std::make_unique<StudentNode>(
            StudentNode(new_student)
        );
    }
    else {
        StudentNode* current = head.get();
        while (current->next != nullptr){
            current = current->next.get();
        }
        current->next = std::make_unique<StudentNode>(
            StudentNode(new_student)
        );
    }
    sort();
}

bool Students::idExists(long long id){
    try {
        getById(id);
        return true;
    }
    catch (std::string){
        return false;
    }
}

void Students::swap(StudentNode *a, StudentNode *b){
    Student temp = a->student;
    a->student = b->student;
    b->student = temp;
}

StudentNode* Students::oneSortStep(StudentNode *start, StudentNode *end){
    // When there is only one element on the container, return.
    if (start->next.get() == end){
        return start;
    }
    // Initialize the left and right pointer.
    Score mid = start->student.getInfo().total_score;
    StudentNode *left = start;
    StudentNode *right = start->next.get();
    while (right != end){
        // Make sure the element is not bigger than the mid.
        if (right->student.getInfo().total_score > mid){
            left = left->next.get();
            swap(left, right);
        }
        right = right->next.get();
    }
    swap(start, left);
    return left;
}
void Students::subSort(StudentNode *begin, StudentNode *end){
    if (begin != end){
        StudentNode *mid = oneSortStep(begin, end);
        subSort(begin, mid);
        subSort(mid->next.get(), end);
    }
}
void Students::sort(){
    // Sort the students.
    subSort(head.get(), nullptr);

    // Set the rank.
    int rank = 0;
    int total_score = 9999;
    int joint = 0;
    StudentNode *current = head.get();
    while (current != nullptr){
        if (current->student.getInfo().total_score < total_score){
            rank += joint;
            rank++;
            joint = 0;
            total_score = current->student.getInfo().total_score;
        }
        else{
            joint++;
        }
        current->student.setRank(rank);
        current = current->next.get();
    }
}

StudentNode* Students::getById(long long id){
    // if (head == nullptr){
    //     throw std::string("Error: Not found id: ")
    //         + std::to_string(id);
    // }
    StudentNode *current = head.get();
    while (current != nullptr){
        if (current->student.getId() == id){
            return current;
        }
        current = current->next.get();
    }
    throw std::string("Error: Not found id: ")
        + std::to_string(id);
}

Student Students::getStudentById(long long id){
    StudentNode *target = getById(id);
    return target->student;
}

Student Students::getStudentByName(const char *name){
    StudentNode *current = head.get();
    while (current != nullptr){
        if (!strcmp(current->student.getName(), name)){
            return current->student;
        }
        current = current->next.get();
    }
    throw std::string("Error: Not found name: ")
        + std::string(name);
}

void Students::setMathScore(long long id, Score new_score){
    StudentNode *target = getById(id);
    target->student.setMathScore(new_score);
    sort();
}
void Students::setEnglishScore(long long id, Score new_score){
    StudentNode *target = getById(id);
    target->student.setEnglishScore(new_score);
    sort();
}
void Students::setProgrammingScore(long long id, Score new_score){
    StudentNode *target = getById(id);
    target->student.setProgrammingScore(new_score);
    sort();
}
void Students::setDataStructureScore(long long id, Score new_score){
    StudentNode *target = getById(id);
    target->student.setDataStructureScore(new_score);
    sort();
}

const char* Students::getInfo(){
    std::string ans = "**The students list:**\n";
    if (head == nullptr) {
        ans += "{empty}\n";
        char *ans_str = new char[ans.size() + 1];
        strcpy(ans_str, ans.c_str());
        return ans_str;
    }
    StudentNode *current = head.get();
    while (1){
        Student student = current->student;
        StudentInfo info = student.getInfo();
        ans += "{\n    ID=" + std::to_string(student.getId()) + ",\n"
            + "    Name=\"" + student.getName() + "\",\n"
            + "    Math=" + std::to_string(info.math_score) + ",\n"
            + "    English=" + std::to_string(info.english_score)
            + ",\n" + "    Programming="
            + std::to_string(info.programming_score) + ",\n"
            + "    Data Structure="
            + std::to_string(info.data_structure_score) + ",\n"
            + "    Total=" + std::to_string(info.total_score) + "\n"
            + "    Rank=" + std::to_string(info.rank) + "\n},\n";
        // See if gets the end of the list.
        if (current->next == nullptr) break;
        current = current->next.get();
    }
    ans += "}\n";
    char *ans_str = new char[ans.size() + 1];
    strcpy(ans_str, ans.c_str());
    return ans_str;
}

const char* Students::getTable(){
    if (head == nullptr) return "";
    std::string ans = "";
    StudentNode *current = head.get();
    while (1){
        StudentInfo info = current->student.getInfo();
        // ID
        ans += std::to_string(current->student.getId()) + ',';
        // Name
        ans += current->student.getName();
        ans += ',';
        // Gender
        switch (info.gender){
        case Gender::Male:
            ans += "男,";
            break;
        case Gender::Female:
            ans += "女,";
            break;
        case Gender::NonBinary:
            ans += "非二元,";
            break;
        }
        // English
        ans += std::to_string(info.english_score) + ',';
        // Math
        ans += std::to_string(info.math_score) + ',';
        // Programming
        ans += std::to_string(info.programming_score) + ',';
        // Data Structure
        ans += std::to_string(info.data_structure_score) + ',';
        // Total
        ans += std::to_string(info.total_score) + ',';
        // Rank
        ans += std::to_string(info.rank);
        if (current->next == nullptr) break;
        ans += '\n';
        current = current->next.get();
    }
    char *ans_str = new char[ans.size() + 1];
    strcpy(ans_str, ans.c_str());
    return ans_str;
}