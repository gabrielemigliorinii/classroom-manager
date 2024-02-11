#ifndef PERSON_H
#define PERSON_H

class Person 
{
	protected:

		char* name;
		char* surname;
        static const char* DEFAULT_NAME;
        static const char* DEFAULT_SURNAME;

	public:

		Person();
		Person(char[], char[]);
		char* getName();
		char* getSurname();
		char* getNameSurname();
		bool setName(char[]);
		bool setSurname(char[]);
        friend bool operator== (Person, Person);
};

#endif 