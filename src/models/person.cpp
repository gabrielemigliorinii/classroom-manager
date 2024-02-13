#include "../../include/models/person.h"
#include "../../include/models/myregex.h"

#include <string.h>
#include <string>
#include <cstring>

Person::Person() : name("DEF_NAME"), surname("DEF_SURNAME") {}

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
    return (char*) ((std::string)getName() + (std::string)getSurname()).c_str();
}

bool Person::setName(char* name)
{
    if (MyRegex::name(name))
    {
        strcpy(this->name, name);
		return true;
	}
	return false;
}

bool Person::setSurname(char* surname)
{
	if (MyRegex::name(surname))
    {
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