#include <iostream>
#include <fstream>
#include <string.h>
#include <regex>

using namespace std;

const char STUDENTS_FILENAME[] = "ELENCO_CLASSE.dat";
const char INDEX_FILENAME[] = "FILE_INDICE.dat";

class Person {

	protected:

		char name[15];
		char surname[15];

	public:

		Person();
		Person(char[], char[]);
		char* getN();
		char* getS();
		char* getNS();
		bool setN(char[]);
		bool setS(char[]);

		friend bool operator== (Person p1, Person p2){
			return (string)p1.getN() == (string)p2.getN() && (string)p1.getS() == (string)p2.getS();
		}
};

namespace school {

	class Student : public Person {

		private:

			char tel[16];
			char email[25];
			bool pcp;
			bool stage;

		public:

			Student();
			Student(char[], char[], char[], char[], bool, bool);
			bool setT(char[]);
			bool setE(char[]);
			void setP(bool);
			void setA(bool);
			char* getT();
			char* getE();
			bool getP();
			bool getA();
			void show(int);
			void showAttribute(char[], string);
			void showAttribute(bool, string);
			bool input();
	};

	class Class {

		private:

			int year;
			string address, section;
			int numberOfStudents;
		    int MAX_STUDENTS;

		public:

			Class(int, string, string, int);
			int getMax();
			bool addStudent(Student);
			bool findStudent(Person, Student&);
			bool findStudentByTel(string, Student&);
			void menu();
			void showStudent(Student);
			bool showStudents();
	};
}

class MYFILE {

	public:

		template <typename Record> static bool write(const char[], int, Record);
		template <typename Record> static bool read(const char[], int, Record&);
		template <typename Record> static void append(const char[], Record);
		template <typename Record> static int countRecords(const char[]);
		template <typename Record> static void setUp(const char[], int, bool, char='$');
		template <typename Record> static void swapRecords(const char[], int, int);
		template <typename Record> static bool positionOK(const char[], int, char='$');
		static void clear(const char[]);
		static bool exist(const char[]);
		static void create(const char[]);
		static void sortIndexFile(const char[], int, int);   // quick sort index file
		static int binarySearchIndexFile(const char[], string, int, int); // ricerca binaria in un file indice
};

class HASH {

	public:

		static int function(char k[], int n){

			int s(0);
			for (int i=0; i<strlen(k); i++) s += int(k[i]) * (i+1);
			return s%n;
		}

		template <typename T> static int handleCollision(const char filename[], T t){

			MYFILE::append(filename, t);	 			// append del record che ha avuto una collisione
			return MYFILE::countRecords<T>(filename)-1; // ritorno la posizione del record aggiunto
		}

};

// Oggetto RigaFileIndice(chiave, valore).
// Utile per scrittura/lettura di coppie chiave-valore nel file indice.
class IndexFileRow {

	private:

		char key[20];
		int value;

	public:

		IndexFileRow(char key[], int value){
			strcpy(this->key,key);
			this->value = value;
		}

		IndexFileRow(){
			strcpy(key, "DEFAULT_KEY");
			value = -1;
		}

		char* getKey(){ return key; }
		int getVal(){ return value; }
};

class REGEX {

	public:

		static bool email(char email[]){
			regex pattern("(\\w+)(\\.|_)?(\\w*)@(\\w+)(\\.(\\w+))+");
			return regex_match(email, pattern);
		}

		static bool telnum(char tel[]){
			regex pattern("^[0-9\\-\\+]{9,15}$");
			return regex_match(tel, pattern);
		}

		static bool name(char name[]){
			regex pattern("[_|A-Z|a-z]+[_|A-Z|a-z|0-9]+");
			return regex_match(name, pattern);
		}
};

using namespace school;

int main (void) {

	const unsigned int MAX_STUDENTS = 31;

	// Preparazione di un file con records di tipo 'Studente'
	MYFILE::setUp<Student>(STUDENTS_FILENAME, MAX_STUDENTS, false, '$');

	Class sclass(5,"I","D", MAX_STUDENTS);

	int s;

	do {
		s = -1;

		while (s < 0 || s > 4){

			sclass.menu();
			cin >> s;
			system("CLS");
		}

		switch (s) {

			case 2: {

				string re_run("no");

				do {

					if (re_run != "no") system("CLS");
					cout << "\n\n --- FUNZIONE AGGIUNGI NUOVO STUDENTE ---\n\n\n";

					bool input = false;
					Student student;

					while (!input){
						input = student.input();
						if (!input)
							cout << "\n\n  [INSERITI VALORI NON VALIDI, PREMERE UN TASTO PER CONTINUARE...]\n\n ";
					}

					if (sclass.addStudent(student))
						cout << "\n\n  [STUDENTE AGGIUNTO CORRETTAMENTE ...] \n\n";
					else
						cout << "\n\n  [ERRORE, LIMITE MASSIMO DI STUDENTI RAGGIUNTO PER QUESTA CLASSE...] \n\n";
					cout << "\n - Vuoi inserire un altro studente? \n\n  (SI/NO) >: ";
					cin >> re_run;

				} while (re_run=="SI" || re_run=="si" || re_run=="Si" || re_run=="sI");

				break;
			}

			case 3: {

				cout << "\n\n --- FUNZIONE RICERCA STUDENTE TRAMITE NOME E COGNOME ---\n\n\n";

				char name[15], surname[15];

				cin.ignore();
				cout << " - Inserire nome: ";
				cin.getline(name, 15);
				cout << " - Inserire cognome: ";
				cin.getline(surname, 15);

				Person person(name, surname);
				Student student;

				if (sclass.findStudent(person, student))
					sclass.showStudent(student);
				else
					cout << "\n\n  [NESSUNO RISULTATO...] \n\n";

				break;
			}

			case 1: {

				cout << "\n\n --- FUNZIONE MOSTRA ELENCO STUDENTI ---\n\n";
				if(!sclass.showStudents())
					cout << "\n\n  [NESSUNO STUDENTE PER QUESTA CLASSE...] \n\n";

				break;
			}

			case 4: {

				cout << "\n\n --- FUNZIONE RICERCA STUDENTE TRAMITE NUMERO TELEFONICO ---\n\n\n";

				string tel;
				Student s;

				cin.ignore();
				cout << " - Inserire numero telefonico: [+39] ";
				getline(cin, tel); tel = "+39"+tel;

				if (sclass.findStudentByTel(tel, s))
					sclass.showStudent(s);
				else
					cout << "\n\n  [NESSUN RISULTATO...] \n\n";

				break;
			}

			case 0: cout << "\n\n  [USCENDO...]\n\n";
		}

		if (s != 0){
			cout << "\n\n ";
			system("PAUSE");
			system("CLS");
		}

	} while (s != 0);

	return 0;
}


// ------------------- START CLASS MYFILE ---------------------------------------------------------

template <typename Record> bool MYFILE::write(const char filename[], int position, Record record){

	if (position < 0) return false;
	if (!exist(filename)) create(filename);

	ofstream file;
	file.open(filename, ios::out|ios::in|ios::binary);
	file.seekp(position * sizeof(Record), ios::beg);
	file.write((char*) &record, sizeof(Record));
	file.close();

	return true;
}

template <typename Record> bool MYFILE::read(const char filename[], int position, Record &record){

	if (!exist(filename) || position < 0) return false;

	ifstream file;
	file.open(filename, ios::in|ios::binary);
	file.seekg(position * sizeof(Record), ios::beg);
	file.read((char*) &record, sizeof(Record));
	file.close();

	return true;
}

template <typename Record> void MYFILE::append(const char filename[], Record record){

	ofstream file;
	file.open(filename, ios::app|ios::binary);
	file.write((char*) &record, sizeof(Record));
	file.close();
}

void MYFILE::create(const char filename[]){

	ofstream file(filename); file.close();
}

template <typename Record> int MYFILE::countRecords(const char filename[]){

	ifstream file;
	file.open(filename, ios::in|ios::binary);
	file.seekg(0, ios::end);
	int N_RECORDS = file.tellg()/sizeof(Record);
	file.close();
	return N_RECORDS;
}

void MYFILE::clear(const char filename[]){

	fstream file;
	file.open(filename, ios::out|ios::trunc|ios::binary);
	file.close();
}

template <typename Record> void MYFILE::setUp(const char filename[],int N_RECORDS,bool override,char specialChar){

	if (override) MYFILE::clear(filename);
	else if (exist(filename)) return;

	ofstream file;
	file.open(filename, ios::app|ios::binary);

	for (int i=0; i<N_RECORDS*sizeof(Record); i++)
		file.write(&specialChar, sizeof(char));

	file.close();
}

bool MYFILE::exist(const char filename[]){

    ifstream file(filename);
    bool state = file.good();
    file.close();
    return state;
}

template <typename Record> bool MYFILE::positionOK(const char filename[], int position, char spc){

	char c;
	MYFILE::read(filename, position*sizeof(Record), c);

	return c == spc;
}

void MYFILE::sortIndexFile(const char filename[], int indexP, int indexU){

	string pivot, s1, s2;

	if (indexP < indexU){

		IndexFileRow ir;
		MYFILE::read(filename, indexP, ir);
		string pivot((string)ir.getKey());

		int i = indexP-1;
		int j = indexU+1;

		while (i < j) {

			do {

				j--;
				IndexFileRow rx;
				MYFILE::read(filename, j, rx);
				s1 = (string)rx.getKey();

			} while (s1 > pivot);

			do {

				i++;
				IndexFileRow ry;
				MYFILE::read(filename, i, ry);
			 	s2 = (string)ry.getKey();

			} while (s2 < pivot);

			if (i < j) swapRecords<IndexFileRow>(filename, i, j);
		}

		sortIndexFile(filename, indexP, j);
		sortIndexFile(filename, j+1, indexU);
	}
}

template <typename Record> void MYFILE::swapRecords(const char filename[], int pos1, int pos2){

	Record a, b;

	MYFILE::read(filename, pos1, a);
	MYFILE::read(filename, pos2, b);

	MYFILE::write(filename, pos2, a);
	MYFILE::write(filename, pos1, b);
}

int MYFILE::binarySearchIndexFile(const char filename[], string target, int imin, int imax){

	IndexFileRow ir;
	string s;

	if (imax >= imin) {

        int imid = imin + (imax - imin) / 2;

  		MYFILE::read(filename, imid, ir);
  		s = (string)ir.getKey();

        if (s == target) return imid;

  		MYFILE::read(filename, imid, ir);
  		s = (string)ir.getKey();

        if (s > target)
            return binarySearchIndexFile(filename, target, imin, imid - 1);

        return binarySearchIndexFile(filename, target, imid + 1, imax);
	}

	return -1;
}

// ------------------- END CLASS MYFILE ---------------------------------------------------------




// ------------------- START CLASS PERSON -------------------------------------------------------

Person::Person(){
	strcpy(name,"DEFAULT_NAME");
	strcpy(surname,"DEFAULT_SURNAME");
}

Person::Person(char name[], char surname[]){
	setN(name);
	setS(surname);
}

char* Person::getN(){
	return name;
}

char* Person::getS(){
	return surname;
}

char* Person::getNS(){
	return (char*) ((string)name + (string)surname).c_str();
}

bool Person::setN(char name[]){
	strupr(name);
	if (REGEX::name(name)){
		strcpy(this->name, name);
		return true;
	}
	return false;
}

bool Person::setS(char surname[]){
	strupr(surname);
	if (REGEX::name(surname)){
		strcpy(this->surname, surname);
		return true;
	}
	return false;
}


// ------------------- END CLASS PERSON ----------------------------------------------------------



// ------------------- START CLASS SCHOOL::STUDENT -------------------------------------------------------

Student::Student(char name[], char surname[],  char tel[], char email[], bool pcp, bool stage) : Person(name, surname) {
	setT(tel);
	setE(email);
	setP(pcp);
	setA(stage);
}

Student::Student() : Person() {
	strcpy(tel,"DEFAULT_TEL");
	strcpy(email,"DEFAULT_EMAIL");
	this->pcp = NULL;
	this->stage = NULL;
}

bool Student::setT(char tel[]) {
	strupr(tel);
	if (REGEX::telnum(tel)==true){
		strcpy(this->tel,tel);
		return true;
	}else
		return false;
}

bool Student::setE(char email[]) {
	strupr(email);
	if (REGEX::email(email)==true){
		strcpy(this->email,email);
		return true;
	}else
		return false;
}

void Student::setP(bool pcp){
	this->pcp = pcp;
}

void Student::setA(bool stage){
	this->stage = stage;
}

void Student::show(int pos){

	cout<<"\n\n";
	cout<<"  [STUDENTE "<<pos<<"]\n\n";
	cout<<" ------------------------------------\n\n";
    showAttribute(getN(), "Nome"); cout<<endl;
    showAttribute(getS(), "Cognome"); cout<<endl;
    showAttribute(getT(), "Telefono"); cout<<endl;
    showAttribute(getE(), "Email"); cout<<endl;
    showAttribute(getP(), "Portatile"); cout<<endl;
    showAttribute(getA(), "Stage"); cout<<endl;
    cout<<"\n\n";
}

void Student::showAttribute(char value[], string fieldName){

	cout << "  -> "<<fieldName<<":\t";
	for (int i=0; i<strlen(value); i++) cout << value[i];
}

void Student::showAttribute(bool value, string fieldName){

	string s;
	cout << "  -> "<<fieldName<<":\t";
	s = value?"SI":"NO";
	cout << s;
}

char* Student::getT(){
	return tel;
}

char* Student::getE(){
	return email;
}

bool Student::getP(){
	return pcp;
}

bool Student::getA(){
	return stage;
}

bool Student::input(){

	string s1, s2, s3, s4, s5, s6;

	cin.ignore();
	cout << " - Inserire nome: ";
	getline(cin, s1);
	cout << " - Inserire cognome: ";
	getline(cin, s2);
	cout << " - Inserire telefono: [+39] ";
	getline(cin, s3); s3 = "+39"+s3;
	cout << " - Inserire email: ";
	getline(cin, s4);
	cout << " - Pc portatile ? (SI/NO): ";
	getline(cin, s5);
	cout << " - Stage ? (SI/NO): ";
	getline(cin, s6);

	s5 = (string)strupr((char*)s5.c_str());
	s6 = (string)strupr((char*)s6.c_str());

	setP((s5 == "SI" || s5 == "S") ? 1 : 0);
	setA((s6 == "SI" || s6 == "S") ? 1 : 0);

	bool input_valid[] = {

	   setN((char*)s1.c_str()),
	   setS((char*)s2.c_str()),
	   setT((char*)s3.c_str()),
	   setE((char*)s4.c_str())
	};

	return input_valid[0] && input_valid[1] && input_valid[2] && input_valid[3];
}

// ------------------- END CLASS SCHOOL::STUDENT -------------------------------------------------------




// ------------------- START CLASS SCHOOL::CLASS ------------------------------------------------------

Class::Class(int year, string address, string section, int MAX_STUDENTS){

	this->year = year;
	this->address = address;
	this->section = section;
	this->numberOfStudents = MYFILE::exist(INDEX_FILENAME) ? MYFILE::countRecords<IndexFileRow>(INDEX_FILENAME) : 0;
	this->MAX_STUDENTS = MAX_STUDENTS;
}

bool Class::addStudent(Student student){

	Person person(student.getN(), student.getS());

	int position = HASH::function(person.getNS(), MAX_STUDENTS);

	const bool empty = MYFILE::positionOK<Student>(STUDENTS_FILENAME, position, '$');

	if (empty == false)  // collisione
		position = HASH::handleCollision(STUDENTS_FILENAME, student); // appende studente e ritorna posizione
	else
		MYFILE::write(STUDENTS_FILENAME, position, student);

	numberOfStudents++;

	IndexFileRow keyvalue(student.getT(), position);
	MYFILE::append(INDEX_FILENAME, keyvalue);
	MYFILE::sortIndexFile(INDEX_FILENAME, 0, MYFILE::countRecords<IndexFileRow>(INDEX_FILENAME)-1);

	return true;
}

int Class::getMax(){
	return this->MAX_STUDENTS;
}

void Class::menu(){

	string s = numberOfStudents == 1 ? "STUDENTE" : "STUDENTI";

	cout << "\n\n\t\t STATISTICHE CLASSE "<<year<<address<<section<<"  -  "
	<< numberOfStudents <<" "<<s<<" ";
	cout << "\n\n   ____________________________________________________________________\n\n\n";
	cout << "     Selezionare un'opzione:\n\n";
	cout << "         (1) Mostra studenti\n";
	cout << "         (2) Aggiungi studente\n";
	cout << "         (3) Ricerca studente tramite nome e cognome\n";
	cout << "         (4) Ricerca studente tramite numero telefonico\n";
	cout << "         (0) ESCI";
	cout << "\n\n       >: ";
}

bool Class::findStudent(Person person, Student &student){

	bool found = false;
	int position = HASH::function(person.getNS(), MAX_STUDENTS);

	if (!MYFILE::positionOK<Student>(STUDENTS_FILENAME, position, '$')){
	// se il record alla posizione 'position' inizia con un carattere diverso da '$' (char speciale) =>

		Person p;
		MYFILE::read(STUDENTS_FILENAME, position, student);

		p.setN(student.getN()); p.setS(student.getS());

		found = (person == p);

		if (!found){  // in caso di collisione

			position = MAX_STUDENTS;
			const int N_RECORDS = MYFILE::countRecords<Student>(STUDENTS_FILENAME);

			// ricerca sequenzionale tra le collisioni il cui numero è: (N_RECORDS - position)
			while (!found && position < N_RECORDS){

				MYFILE::read(STUDENTS_FILENAME, position, student);
				p.setN(student.getN()); p.setS(student.getS());
				found = (person == p);

				position++;
			}
		}
	}

	return found;
}

bool Class::findStudentByTel(string tel, Student &s){

	int pos = -1;
	bool found = false;

	if (this->numberOfStudents > 0){

		pos = MYFILE::binarySearchIndexFile(INDEX_FILENAME, tel, 0, this->numberOfStudents-1);

		if (pos > -1){

			IndexFileRow ir;
			MYFILE::read(INDEX_FILENAME, pos, ir);
			pos = ir.getVal();
			MYFILE::read(STUDENTS_FILENAME, pos, s);
			found = true;
		}
	}

	return found;
}

void Class::showStudent(Student s){
	s.show(1);
}

bool Class::showStudents(){

	Student s;
	IndexFileRow ir;
	int position(-1);

	for (int i = 0; i<this->numberOfStudents; i++){

		MYFILE::read(INDEX_FILENAME, i, ir);
		position = ir.getVal();
		if (position < 0) continue;
		MYFILE::read(STUDENTS_FILENAME, position, s);
		s.show(i+1);
	}

	return position > 0;
}

// ------------------- END CLASS SCHOOL::CLASS ------------------------------------------------------
