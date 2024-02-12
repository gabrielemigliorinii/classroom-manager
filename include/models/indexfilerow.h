#ifndef INDEXFILEROW_H
#define INDEXFILEROW_H

class IndexFileRow 
{
    private:

		char* key;
		int value;

	public:

		IndexFileRow(char[], int);
		IndexFileRow();
        void setKey(char[]);
        void setVal(int);
		char* getKey();
		int getVal();
};

#endif 