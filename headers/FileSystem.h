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
    virtual int getRootDirectory() = 0;

};

#endif