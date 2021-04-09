#ifndef _FILE_READER_
#define _FILE_READER_
#include <stdio.h>
#include <iostream>
#include <string>
#include <fstream>
#include "FAT.h"

using namespace std;

class FileReader {
    private:
        ifstream file;
        FAT fat;


    public:
        FileReader(string path);
        void checkFATorEXT();
        void fileClose();
};
#endif
