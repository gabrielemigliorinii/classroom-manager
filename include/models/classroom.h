#ifndef CLASSROOM_H
#define CLASSROOM_H

#include "student.h"
#include <string>

class Classroom 
{
    private:

        int year;
        std::string address; 
        std::string section;
        int numberOfStudents;
        int MAX_STUDENTS;

        const char* STUDENTS_FILENAME;
        const char* INDEX_FILENAME;

    public:

        Classroom(int, std::string, std::string, int, const char*, const char*);
        int getMax();
        bool addStudent(Student);
        bool findStudent(Person, Student&);
        bool findStudentByTel(std::string, Student&);
        void menu();
        void showStudent(Student);
        bool showStudents();
};

#endif 