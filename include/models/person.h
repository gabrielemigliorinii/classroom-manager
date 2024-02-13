#ifndef PERSON_H
#define PERSON_H

class Person 
{
	protected:

		char name[50];
		char surname[50];
        static char* DEFAULT_NAME;
        static char* DEFAULT_SURNAME;

	public:

		Person();
		Person(char*, char*);
		char* getName();
		char* getSurname();
		char* getNameSurname();
		bool setName(char*);
		bool setSurname(char*);
        friend bool operator== (Person, Person);
};

#endif 