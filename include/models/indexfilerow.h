#ifndef INDEXFILEROW_H
#define INDEXFILEROW_H

class IndexFileRow 
{
    private:

		char key[20];
		int value;

	public:

		IndexFileRow(char[], int);
		IndexFileRow();
		char* getKey();
		int getVal();
};

#endif 