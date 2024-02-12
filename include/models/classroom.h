#ifndef CLASSROOM_H
#define CLASSROOM_H

#include "student.h"
#include <string>

class Classroom 
{
    private:

        int year;
        std::string address, section;
        int numberOfStudents;
        int MAX_STUDENTS;

        static char* INDEX_FILENAME;
        static char* STUDENTS_FILENAME;

    public:

        Classroom(int, std::string, std::string, int);
        int getMax();
        bool addStudent(Student);
        bool findStudent(Person, Student&);
        bool findStudentByTel(std::string, Student&);
        void menu();
        void showStudent(Student);
        bool showStudents();
};

#endif 