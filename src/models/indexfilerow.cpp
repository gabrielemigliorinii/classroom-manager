#include "../include/models/indexfilerow.h"

#include <cstring>

IndexFileRow::IndexFileRow(char* key, int value)
{
    setKey(key);
    setValue(value);
}

IndexFileRow::IndexFileRow() : key("DEFAULT_KEY"), value(-1) {}

void IndexFileRow::setKey(char* key)
{
    this->key = new char[strlen(key)+1];
    strcpy(this->key, key);
}

char* IndexFileRow::getKey()
{ 
    return this->key; 
}

void IndexFileRow::setValue(int value)
{
    this->value = value;
}

int IndexFileRow::getValue()
{ 
    return this->value; 
}


