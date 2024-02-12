#include "../../include/models/myfile.h";
#include "../../include/models/indexfilerow.h";
#include "../../include/models/student.h";
#include "../../include/models/person.h";

#include <fstream>
#include <string>

void MyFile::clear(const char filename[])
{
	std::fstream file;
	file.open(filename, std::ios::out|std::ios::trunc|std::ios::binary);
	file.close();
}


bool MyFile::exists(const char filename[])
{
    std::ifstream file(filename);
    bool state = file.good();
    file.close();
    return state;
}

void MyFile::create(const char filename[])
{
	std::ofstream file(filename); 
    file.close();
}

void MyFile::sortIndexFile(const char filename[], int indexP, int indexU)
{
	std::string pivot, s1, s2;

	if (indexP < indexU){

		IndexFileRow ir;
		MyFile::read(filename, indexP, ir);
		std::string pivot((std::string)ir.getKey());

		int i = indexP-1;
		int j = indexU+1;

		while (i < j) {

			do {

				j--;
				IndexFileRow rx;
				MyFile::read(filename, j, rx);
				s1 = (std::string)rx.getKey();

			} while (s1 > pivot);

			do {

				i++;
				IndexFileRow ry;
				MyFile::read(filename, i, ry);
			 	s2 = (std::string)ry.getKey();

			} while (s2 < pivot);

			if (i < j) swapRecords<IndexFileRow>(filename, i, j);
		}

		MyFile::sortIndexFile(filename, indexP, j);
		MyFile::sortIndexFile(filename, j+1, indexU);
	}
}



int MyFile::binarySearchIndexFile(const char filename[], std::string target, int imin, int imax)
{
	IndexFileRow ir;
	std::string s;

	if (imax >= imin) {

        int imid = imin + (imax - imin) / 2;

  		MyFile::read(filename, imid, ir);
  		s = (std::string)ir.getKey();

        if (s == target) return imid;

  		MyFile::read(filename, imid, ir);
  		s = (std::string)ir.getKey();

        if (s > target)
            return binarySearchIndexFile(filename, target, imin, imid - 1);

        return binarySearchIndexFile(filename, target, imid + 1, imax);
	}

	return -1;
}