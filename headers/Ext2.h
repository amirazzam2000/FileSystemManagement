#ifndef _EXT_
#define _EXT_
#include <stdio.h>
#include <iostream>
#include <string>

using namespace std;



/*
    this struct will store the meta data needed to 
    work with the Ext2 file system.
*/
typedef struct
{
    int16_t ext2_version;

} MetaExt;

/**
 * this class stores all the data of the FAT file system,
 * and also provides methods to manage the system. 
 * 
*/
class Ext2
{
private:
    //attriputes
    MetaExt meta;

public:
    //attriputes
    static int const S_MAGIC = 1080;
    static int32_t const MAGIC_VALUE = 0xEF53;

    //methodes
    Ext2();

};

#endif