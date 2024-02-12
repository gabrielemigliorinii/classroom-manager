#include "../include/models/hash.h"
#include "../include/models/myfile.h"
#include "../include/models/indexfilerow.h"
#include "../include/models/student.h"

#include <cstring>

int Hash::function(char k[], int n)
{
    int s(0);
    for (int i=0; i<strlen(k); i++) s += int(k[i]) * (i+1);
    return s%n;
}
