#include "../../include/models/person.h"
#include "../../include/models/myregex.h"

#include <string.h>
#include <string>
#include <cstring>

char* Person::DEFAULT_NAME = "DEFAULT_NAME";
char* Person::DEFAULT_SURNAME = "DEFAULT_SURNAME";

Person::Person() : name(Person::DEFAULT_NAME), surname(Person::DEFAULT_SURNAME) {}

Person::Person(char name[], char surname[])
{
	setName(name);
	setSurname(surname);
}

char* Person::getName()
{
	return name;
}

char* Person::getSurname()
{
	return surname;
}

char* Person::getNameSurname()
{
    size_t name_len = std::strlen(name);
    size_t surname_len = std::strlen(surname);

    char* namesurname = new char[name_len + surname_len + 1];

    std::strcpy(namesurname, name);
    std::strcat(namesurname, surname);

	return namesurname;
}

bool Person::setName(char* name)
{
    if (MyRegex::name(name))
    {
        this->name = new char[strlen(name)+1];
        strcpy(this->name, name);
		return true;
	}
	return false;
}

bool Person::setSurname(char* surname)
{
	if (MyRegex::name(surname))
    {
        this->surname = new char[strlen(surname)+1];
        strcpy(this->surname, surname);
		return true;
	}
	return false;
}

bool operator== (Person p1, Person p2)
{
    std::string name_p1 = p1.getName();
    std::string surname_p1 = p1.getSurname();

    std::string name_p2 = p2.getName();
    std::string surname_p2 = p2.getSurname();

    return name_p1 == name_p2 && surname_p1 == surname_p2;
}