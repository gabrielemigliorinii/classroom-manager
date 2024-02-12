#ifndef MYFILE_H
#define MYFILE_H

#include <string>
#include <fstream>

class MyFile 
{
	public:

		static void clear(const char[]);
		static bool exists(const char[]);
		static void create(const char[]);
		static void sortIndexFile(const char[], int, int);   // quick sort index file
		static int binarySearchIndexFile(const char[], std::string, int, int); // ricerca binaria in un file indice

        template <typename Record> 
        static bool write(const char filename[], int position, Record record)
        {
            if (position < 0) 
                return false;

            if (!exists(filename)) 
                create(filename);

            std::ofstream file;
            file.open(filename, std::ios::out|std::ios::in|std::ios::binary);
            file.seekp(position * sizeof(Record), std::ios::beg);
            file.write((char*) &record, sizeof(Record));
            file.close();

            return true;
        }

        template <typename Record> 
        static bool read(const char filename[], int position, Record &record)
        {
            if (!exists(filename) || position < 0) return false;

            std::ifstream file;
            file.open(filename, std::ios::in|std::ios::binary);
            file.seekg(position * sizeof(Record), std::ios::beg);
            file.read((char*) &record, sizeof(Record));
            file.close();

            return true;
        }

        template <typename Record> 
        static void append(const char filename[], Record record)
        {
            std::ofstream file;
            file.open(filename, std::ios::app|std::ios::binary);
            file.write((char*) &record, sizeof(Record));
            file.close();
        }



        template <typename Record> 
        static int countRecords(const char filename[])
        {
            std::ifstream file;
            file.open(filename, std::ios::in|std::ios::binary);
            file.seekg(0, std::ios::end);
            int N_RECORDS = file.tellg()/sizeof(Record);
            file.close();
            return N_RECORDS;
        }


        template <typename Record> 
        static void init(const char filename[], int N_RECORDS, bool override, char specialChar)
        {
            if (override) 
                MyFile::clear(filename);
            else if (exists(filename)) 
                return;

            std::ofstream file;
            file.open(filename, std::ios::app|std::ios::binary);

            for (int i=0; i<N_RECORDS*sizeof(Record); i++)
                file.write(&specialChar, sizeof(char));

            file.close();
        }


        template <typename Record> 
        static bool positionOK(const char filename[], int position, char spc)
        {
            char c;
            MyFile::read(filename, position*sizeof(Record), c);

            return c == spc;
        }

        template <typename Record> 
        static void swapRecords(const char filename[], int pos1, int pos2)
        {
            Record a, b;

            MyFile::read(filename, pos1, a);
            MyFile::read(filename, pos2, b);

            MyFile::write(filename, pos2, a);
            MyFile::write(filename, pos1, b);
        }
};

#endif 