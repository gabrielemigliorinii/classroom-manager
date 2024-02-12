#include "../../include/models/student.h"
#include "../../include/models/person.h"
#include "../../include/models/myregex.h"

#include <iostream>
#include <cstring>

Student::Student(char name[], char surname[],  char tel[], char email[], bool pc, bool stage) : Person(name, surname) 
{
	setTel(tel);
	setEmail(email);
	setPc(pc);
	setStage(stage);
}

Student::Student() : Person()
{
    setTel("DEFAULT_TEL");
    setEmail("DEFAULT_EMAIL");
    setPc(NULL);
    setStage(NULL);
}

bool Student::setTel(char tel[]) 
{
	if (MyRegex::tel(tel) == true)
    {
		strcpy(this->tel, tel);
		return true;
	}else
		return false;
}

bool Student::setEmail(char email[])
{
	if (MyRegex::email(email) == true)
    {
		strcpy(this->email,email);
		return true;
	}
    else
		return false;
}

void Student::setPc(bool pc)
{
	this->pc = pc;
}

void Student::setStage(bool stage)
{
	this->stage = stage;
}

void Student::show(int pos)
{
	std::cout<<"\n\n";
	std::cout<<"  [STUDENTE "<<pos<<"]\n\n";
	std::cout<<" ------------------------------------\n\n";
    showAttribute(getName(), "Nome"); std::cout<<std::endl;
    showAttribute(getSurname(), "Cognome"); std::cout<<std::endl;
    showAttribute(getTel(), "Telefono"); std::cout<<std::endl;
    showAttribute(getEmail(), "Email"); std::cout<<std::endl;
    showAttribute(getPc(), "Portatile"); std::cout<<std::endl;
    showAttribute(getStage(), "Stage"); std::cout<<std::endl;
    std::cout<<"\n\n";
}

void Student::showAttribute(char value[], std::string fieldName)
{
	std::cout << "  -> "<<fieldName<<":\t";
	for (int i=0; i<strlen(value); i++) std::cout << value[i];
}

void Student::showAttribute(bool value, std::string fieldName)
{
	std::string s;
	std::cout << "  -> "<<fieldName<<":\t";
	s = value? "SI" : "NO";
	std::cout << s;
}

char* Student::getTel()
{
	return tel;
}

char* Student::getEmail()
{
	return email;
}

bool Student::getPc()
{
	return pc;
}

bool Student::getStage()
{
	return stage;
}

bool Student::input()
{

	std::string s1, s2, s3, s4, s5, s6;

	std::cin.ignore();

	std::cout << " - Inserire nome: ";
	std::getline(std::cin, s1);
	
    std::cout << " - Inserire cognome: ";
	std::getline(std::cin, s2);
	
    std::cout << " - Inserire telefono: [+39] ";
	std::getline(std::cin, s3); s3 = "+39"+s3;
	
    std::cout << " - Inserire email: ";
	std::getline(std::cin, s4);
	
    std::cout << " - Pc portatile ? (SI/NO): ";
	std::getline(std::cin, s5);
	
    std::cout << " - Stage ? (SI/NO): ";
	std::getline(std::cin, s6);

	s5 = (std::string)strupr((char*)s5.c_str());
	s6 = (std::string)strupr((char*)s6.c_str());

	setPc((s5 == "SI" || s5 == "S") ? 1 : 0);
	setStage((s6 == "SI" || s6 == "S") ? 1 : 0);

	bool input_valid[] = 
    {

	   setName((char*)s1.c_str()),
	   setSurname((char*)s2.c_str()),
	   setTel((char*)s3.c_str()),
	   setEmail((char*)s4.c_str())
	};

	return input_valid[0] && input_valid[1] && input_valid[2] && input_valid[3];
}