#include "../include/models/indexfilerow.h"

#include <cstring>

IndexFileRow::IndexFileRow(char key[], int value)
{
    setKey(key);
    strcpy(this->key,key);
    this->value = value;
}

IndexFileRow::IndexFileRow() : key("DEFAULT_KEY"), value(-1) {}

void IndexFileRow::setKey(char* key)
{
    this->key = new char[strlen(key)+1];
    strcpy(this->key, key);
}

char* IndexFileRow::getKey()
{ 
    return key; 
}

void IndexFileRow::setVal(int value)
{
    this->value = value;
}

int IndexFileRow::getVal()
{ 
    return value; 
}


