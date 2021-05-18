#ifndef _FILESYSTEM_
#define _FILESYSTEM_
#include <stdio.h>
#include <iostream>
#include <string>
#include "FileReader.h"

class FileSystem
{

public: 
    virtual ~FileSystem();
    virtual void parseData(FileReader * freader) = 0;
    virtual void printFileSystemInfo() = 0;
    virtual int checkFileInRoot(FileReader *freader, std::string fileName) = 0;
    virtual bool deleteFile(FileReader *freader, std::string fileName) = 0;
};

#endif