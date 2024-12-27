#include <exception>
#include <iostream>
#include "test_student.h"

int main(int argc, char** argv) {
    // testStudent();
    try{
        testStudent();
        testStudents();
    }
    // Program custom exceptions.
    catch (const char *e){
        std::cout << e << std::endl;
    }
    catch (std::string &e){
        std::cout << e << std::endl;
    }
    // C++ standard exceptions.
    catch (const std::exception &e){
        std::cout << "Error: " << e.what() << std::endl;
    }
    catch(...){
        std::cout << "Unrecognized exception!" << std::endl;
    }
    return 0;
}
