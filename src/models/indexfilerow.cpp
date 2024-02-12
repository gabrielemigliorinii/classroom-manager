#include "../include/models/indexfilerow.h"

#include <cstring>

IndexFileRow::IndexFileRow(char key[], int value)
{
    strcpy(this->key,key);
    this->value = value;
}

IndexFileRow::IndexFileRow()
{
    strcpy(key, "DEFAULT_KEY");
    value = -1;
}

char* IndexFileRow::getKey()
{ 
    return key; 
}

int IndexFileRow::getVal()
{ 
    return value; 
}