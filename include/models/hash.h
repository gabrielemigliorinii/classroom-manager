#ifndef HASH_H
#define HASH_H

#include "myfile.h"

class Hash 
{
    public:

        static int function(char*, int);

        template <typename T> 
        static int handleCollision(const char* filename, T t)
        {
            // append del record che ha avuto una collisione
            MyFile::append(filename, t);	 			
            
            // ritorno la posizione del record aggiunto
            return MyFile::countRecords<T>(filename) - 1; 
        }
};

#endif 