#ifndef _FILE_READER_
#define _FILE_READER_
#include <stdio.h>
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

class FileReader {
    private:
        fstream file;


    public:
        FileReader(string path);
        void fileClose();
        fstream& getFile();


};
#endif
