#ifndef _FAT_
#define _FAT_
#include <stdio.h>
#include <iostream>
#include <string>
#include <fstream>
#include "FileSystem.h"

using namespace std;

#define FAT_STRING "FAT16   "

/*
    this struct will store the meta data needed to 
    work with the FAT file system.
*/
typedef struct 
{
    int16_t fat_version;
    char sec_per_clus;
    int16_t rsvd_sec_cnt;
    char num_fats;
    char fat_name[9];
    int16_t root_enteries;
    int16_t sec_per_fat;
    int16_t size;
    char lable[11];

} MetaFat;

/**
 * this class stores all the data of the FAT file system,
 * and also provides methods to manage the system. 
 * 
*/
class FAT : public FileSystem
{
    private:
        //attriputes
        MetaFat meta;

        //methods
        int checkFile(int offset, FileReader *freader, std::string fileName);

    public:
        //attriputes
        static int const BPB_FATSz16 = 22;
        static int const BS_FilSysType = 54; // check if the file system is FAT 16
        static int const BS_VolLab = 43; //volume lable
        static int const BPB_RsvdSecCnt = 14 ; // number of reserved sectors
        static int const BPB_SecPerClus = 13 ; // number of sectors per cluster
        static int const BPB_NumFATs = 16; // number of fats
        static int const BS_OEMName = 3;  // name of file system
        static int const BPB_RootEntCnt = 17; // max root enteries
        static int const BPB_BytsPerSec = 11; // sector size

        static int const DIR_Attr = 11;  // a flag storing meta data about the file entry (like if it is a directory or if it has a long name etc.)
        static int const DIR_FstClusLO = 26; // next file
        static int const DIR_FileSize = 28; // file size


        //methodes
        virtual ~FAT();
        virtual void parseData(FileReader * freader);
        virtual void printFileSystemInfo();
        virtual int checkFileInRoot(FileReader *freader, std::string fileName);
        

        //setter
        void setFatVersion(int16_t version);
        void setFatSecPerClus(char sec_per_clus);
        void setFatRsvdSecCnt(int16_t rsvd_sec_cnt);
        void setFatNumFATs(char num_fats);
        void setFatOEMName(char fat_name[8]);
        void setFatRootEnteries(int16_t root_enteries);
        void setFatSecPerFat(int16_t sec_per_fat);
        void setFatLable(char lable[11]);
        void setFatSize(int16_t size);

        //getters
        int16_t getFatVersion();
        char getFatSecPerClus();
        int16_t getFatRsvdSecCnt();
        char getFatNumFATs();
        char* getFatOEMName();
        int16_t getFatRootEnteries();
        int16_t getFatSecPerFat();
        char *getFatLable();
        int16_t getFatSize();


};

#endif