#ifndef _FILE_READER_
#define _FILE_READER_
#include <stdio.h>
#include <iostream>
#include <string>
#include <fstream>
#include "FAT.h"
#include "Ext2.h"

using namespace std;

class FileReader {
    private:
        ifstream file;
        FAT fat;
        Ext2 ext;


    public:
        FileReader(string path);
        void checkFATorEXT();
        void fileClose();

        //fat data processing
        void parseFATData();
        void displayFatDetails();

        //ext data processing
        void parseExtData();
        void displayExtDetails();
};
#endif
