#ifndef _FAT_
#define _FAT_
#include <stdio.h>
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

#define FAT_STRING "FAT16   "

/*
    this struct will store the meta data needed to 
    work with the FAT file system.
*/
typedef struct 
{
    int16_t fat_version;

} MetaFat;

/**
 * this class stores all the data of the FAT file system,
 * and also provides methods to manage the system. 
 * 
*/
class FAT
{
    private:
        //attriputes
        MetaFat meta;

    public:
        //attriputes
        static int const BPB_FATSz16 = 22;
        static int const BS_FilSysType = 54;

        //methodes
        FAT();
        void setFatVersion(int16_t version);

};

#endif