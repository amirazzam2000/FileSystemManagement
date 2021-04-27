#ifndef _D_MANAGER_
#define _D_MANAGER_

#include <iostream>
#include <string>
#include "FileSystem.h"
#include "FileReader.h"
#include "FAT.h"
#include "Ext2.h"
#include <fstream>

using namespace std;

class DirectoryManager
{
    private: 
        FileSystem * filesystem;
        FileReader * freader;
        

    public:
        DirectoryManager(string path);
        FileSystem * getFileSystem();
        void close();
        int checkFileInRoot(string file);
};

#endif