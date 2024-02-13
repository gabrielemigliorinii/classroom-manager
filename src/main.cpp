#include "../include/models/myfile.h"
#include "../include/models/student.h"
#include "../include/models/classroom.h"
#include "../include/models/person.h"

#include <iostream>

int main (int argc, char* argv[]) {

    const char* STUDENTS_FILENAME;
    const char* INDEX_FILENAME;
    unsigned int MAX_STUDENTS;

    if (argc == 4)
    {
        STUDENTS_FILENAME = argv[1];
        INDEX_FILENAME = argv[2];
        MAX_STUDENTS = std :: stoi (argv[3]);
    }
    else
    {
        STUDENTS_FILENAME = "../../data/STUDENTS.dat";
        INDEX_FILENAME = "../../data/INDEX.dat";
        MAX_STUDENTS = 31;
    }

	// Preparazione di un file con records di tipo 'Studente'
	MyFile::init<Student>(STUDENTS_FILENAME, MAX_STUDENTS, false, '$');

	Classroom classroom(5,"I","D", MAX_STUDENTS, STUDENTS_FILENAME, INDEX_FILENAME);

	int s;

    system("CLS");

	do 
    {
		s = -1;

		while (s < 0 || s > 4)
        {

			classroom.menu();
			std::cin >> s;
			system("CLS");
		}

		switch (s) 
        {

			case 2: {

				std::string re_run = "no";

				do 
                {

					if (re_run != "no") 
                        system("CLS");

					std::cout << "\n\n --- FUNZIONE AGGIUNGI NUOVO STUDENTE ---\n\n\n";

					bool input = false;
					Student student;

					do
                    {
						input = student.input();
						
                        if (!input)
							std::cout << "\n\n  [INSERITI VALORI NON VALIDI, PREMERE UN TASTO PER CONTINUARE...]\n\n ";

					} while (input == false);

					if (classroom.addStudent(student))
						std::cout << "\n\n  [STUDENTE AGGIUNTO CORRETTAMENTE ...] \n\n";
					else
						std::cout << "\n\n  [ERRORE, LIMITE MASSIMO DI STUDENTI RAGGIUNTO PER QUESTA CLASSE...] \n\n";

					std::cout << "\n - Vuoi inserire un altro studente? \n\n  (SI/NO) >: ";
					std::cin >> re_run;

				} while (re_run == "SI" || re_run == "si" || re_run == "Si" || re_run == "sI");

				break;
			}

			case 3: {

				std::cout << "\n\n --- FUNZIONE RICERCA STUDENTE TRAMITE NOME E COGNOME ---\n\n\n";

				char name[15], surname[15];

				std::cin.ignore();
				std::cout << " - Inserire nome: ";
				std::cin.getline(name, 15);
				std::cout << " - Inserire cognome: ";
				std::cin.getline(surname, 15);

				Person person(strlwr(name), strlwr(surname));
				Student student;

				if (classroom.findStudent(person, student))
					classroom.showStudent(student);
				else
					std::cout << "\n\n  [NESSUNO RISULTATO...] \n\n";

				break;
			}

			case 1: {

				std::cout << "\n\n --- FUNZIONE MOSTRA ELENCO STUDENTI ---\n\n";

				if(!classroom.showStudents())
					std::cout << "\n\n  [NESSUNO STUDENTE PER QUESTA CLASSE...] \n\n";
                
				break;
			}

			case 4: {

				std::cout << "\n\n --- FUNZIONE RICERCA STUDENTE TRAMITE NUMERO TELEFONICO ---\n\n\n";

				std::string tel;
				Student s;

				std::cin.ignore();
				std::cout << " - Inserire numero telefonico: [+39] ";

				getline(std::cin, tel); 
                tel = "+39" + tel;

				if (classroom.findStudentByTel(tel, s))
					classroom.showStudent(s);
				else
					std::cout << "\n\n  [NESSUN RISULTATO...] \n\n";

				break;
			}

			case 0: std::cout << "\n\n  [USCENDO...]\n\n";
		}

		if (s != 0)
        {
			std::cout << "\n\n ";
			system("PAUSE");
			system("CLS");
		}

	} while (s != 0);


	return 0;
}