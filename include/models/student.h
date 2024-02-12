#ifndef STUDENT_H
#define STUDENT_H

#include "person.h"
#include <string>

class Student : public Person {

    private:

        char* tel;
        char* email;
        bool pc;
        bool stage;

        static char* DEFAULT_TEL;
        static char* DEFAULT_EMAIL;
        static char* DEFAULT_PC;
        static char* DEFAULT_STAGE;

    public:

        Student();
        Student(char[], char[], char[], char[], bool, bool);
        bool setTel(char[]);
        bool setEmail(char[]);
        void setPc(bool);
        void setStage(bool);
        char* getTel();
        char* getEmail();
        bool getPc();
        bool getStage();
        void show(int);
        void showAttribute(char[], std::string);
        void showAttribute(bool, std::string);
        bool input();
};

#endif 