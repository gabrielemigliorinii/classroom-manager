#ifndef INDEXFILEROW_H
#define INDEXFILEROW_H

class IndexFileRow 
{
    private:

		char key[20];
		int value;

	public:

		IndexFileRow(char*, int);
		IndexFileRow();
        void setKey(char*);
		char* getKey();
        void setValue(int);
		int getValue();
};

#endif 