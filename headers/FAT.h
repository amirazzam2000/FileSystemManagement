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
    char sec_per_clus;
    int16_t rsvd_sec_cnt;
    char num_fats;
    char fat_name[8];
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
class FAT
{
    private:
        //attriputes
        MetaFat meta;

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

        //methodes
        FAT();
        void setFatVersion(int16_t version);
        void setFatSecPerClus(char sec_per_clus);
        void setFatRsvdSecCnt(int16_t rsvd_sec_cnt);
        void setFatNumFATs(char num_fats);
        void setFatOEMName(char fat_name[8]);
        void setFatRootEnteries(int16_t root_enteries);
        void setFatSecPerFat(int16_t sec_per_fat);
        void setFatLable(char lable[11]);
        void setFatSize(int16_t size);

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