#include "../../include/models/classroom.h"
#include "../../include/models/hash.h"
#include "../../include/models/indexfilerow.h"
#include "../../include/models/myfile.h"
#include "../../include/models/student.h"
#include "../../include/models/person.h"

#include <iostream>
#include <string>

Classroom::Classroom(int year, std::string address, std::string section, int MAX_STUDENTS)
{
	this->year = year;
	this->address = address;
	this->section = section;
	this->numberOfStudents = MyFile::exists("INDEXF") ? MyFile::countRecords<IndexFileRow>("INDEXF") : 0;
	this->MAX_STUDENTS = MAX_STUDENTS;
}

bool Classroom::addStudent(Student student){

	Person person(student.getName(), student.getSurname());

	int position = Hash::function(person.getNameSurname(), MAX_STUDENTS);

	const bool empty = MyFile::positionOK<Student>("STUDS", position, '$');

	if (empty == false)  // collisione
		position = Hash::handleCollision("STUDS", student); // appende studente e ritorna posizione
	else
		MyFile::write("STUDS", position, student);

	numberOfStudents++;

	IndexFileRow keyvalue(student.getTel(), position);
	MyFile::append("INDEXF", keyvalue);
	MyFile::sortIndexFile("INDEXF", 0, MyFile::countRecords<IndexFileRow>("INDEXF")-1);

	return true;
}

int Classroom::getMax(){
	return this->MAX_STUDENTS;
}

void Classroom::menu(){

	std::string s = numberOfStudents == 1 ? "STUDENTE" : "STUDENTI";

	std::cout << "\n\n\t\t STATISTICHE CLASSE "<<year<<address<<section<<"  -  "
	<< numberOfStudents <<" "<<s<<" ";
	std::cout << "\n\n   ____________________________________________________________________\n\n\n";
	std::cout << "     Selezionare un'opzione:\n\n";
	std::cout << "         (1) Mostra studenti\n";
	std::cout << "         (2) Aggiungi studente\n";
	std::cout << "         (3) Ricerca studente tramite nome e cognome\n";
	std::cout << "         (4) Ricerca studente tramite numero telefonico\n";
	std::cout << "         (0) ESCI";
	std::cout << "\n\n       >: ";
}

bool Classroom::findStudent(Person person, Student &student)
{

	bool found = false;
	int position = Hash::function(person.getNameSurname(), MAX_STUDENTS);

	if (!MyFile::positionOK<Student>("STUDS", position, '$')){
	// se il record alla posizione 'position' inizia con un carattere diverso da '$' (char speciale) =>

		Person p;
		MyFile::read("STUDS", position, student);

		p.setName(student.getName()); p.setSurname(student.getSurname());

		found = (person == p);

		if (!found){  // in caso di collisione

			position = MAX_STUDENTS;
			const int N_RECORDS = MyFile::countRecords<Student>("STUDS");

			// ricerca sequenzionale tra le collisioni il cui numero è: (N_RECORDS - position)
			while (!found && position < N_RECORDS)
            {
				MyFile::read("STUDS", position, student);
				p.setName(student.getName()); p.setSurname(student.getSurname());
				found = (person == p);

				position++;
			}
		}
	}

	return found;
}

bool Classroom::findStudentByTel(std::string tel, Student &s){

	int pos = -1;
	bool found = false;

	if (this->numberOfStudents > 0){

		pos = MyFile::binarySearchIndexFile("INDEXF", tel, 0, this->numberOfStudents-1);

		if (pos > -1){

			IndexFileRow ir;
			MyFile::read("INDEXF", pos, ir);
			pos = ir.getVal();
			MyFile::read("STUDS", pos, s);
			found = true;
		}
	}

	return found;
}

void Classroom::showStudent(Student s)
{
	s.show(1);
}

bool Classroom::showStudents()
{
	Student s;
	IndexFileRow ir;
	int position(-1);

	for (int i = 0; i<this->numberOfStudents; i++){

		MyFile::read("INDEXF", i, ir);
		position = ir.getVal();
		if (position < 0) continue;
		MyFile::read("STUDS", position, s);
		s.show(i+1);
	}

	return position > 0;
}