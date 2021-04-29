#ifndef _EXT_
#define _EXT_
#include <stdio.h>
#include <iostream>
#include <string>
#include "FileSystem.h"

using namespace std;



/*
    this struct will store the meta data needed to 
    work with the Ext2 file system.
*/
typedef struct
{
    int16_t ext2_version;
    int i_size;
    int s_inode_count;
    int s_first_ino;
    int s_inodes_per_group;
    int s_log_block_size;
    int s_r_blocks_count;
    int s_free_blocks_count;
    int s_blocks_count;
    int s_first_block;
    int s_blocks_per_group;
    int s_frags_per_group;
    char s_volume_name[16];
    int s_wtime;
    int s_mtime;
    int s_lastcheck;
    int s_free_inodes_count;
    int inode_table_pointer;

} MetaExt;

/**
 * this class stores all the data of the FAT file system,
 * and also provides methods to manage the system. 
 * 
*/
class Ext2 : public FileSystem
{
private:
    //attriputes
    MetaExt meta;

public:
    //attriputes
    static int32_t const MAGIC_VALUE = 0xEF53; // the magic value to compare with
    static int const S_MAGIC = 1080; //to check the filesystem

    //inode block (shifted 5 bytes)
    static int const S_INODE_SIZE = 1024 + 88; // the size of the file (4 bytes)

    //suppur block (shifted 1024)
    static int const S_INODE_COUNT = 1024 + 0; // the total count of inodes (4 bytes)
    static int const S_FIRST_INO = 1024 + 84; // the id of the first inode (4 bytes)
    static int const S_INODES_PER_GROUP = 1024 + 40; // the number of inodes per group (4 bytes)
    static int const S_LOG_BLOCK_SIZE = 1024 + 24;   // group size (4 bytes) block size = 1024 << s_log_block_size;
    static int const S_R_BLOCKS_COUNT = 1024 + 8;    // reserved blocks (4 bytes)
    static int const S_FREE_BLOCKS_COUNT = 1024 + 12;    // free blocks (4 bytes)
    static int const S_BLOCKS_COUNT = 1024 + 4;          // total number of blocks (4 bytes)
    static int const S_FIRST_BLOCK = 1024 + 20;          // the first block of data (4 bytes)
    static int const S_BLOCKS_PER_GROUP = 1024 + 32;     // group blocks (4 bytes) 
    static int const S_FRAGS_PER_GROUP = 1024 + 36;      // frags blocks (4 bytes)
    static int const S_VOLUME_NAME = 1024 + 120;         // volume name (16 bytes)
    static int const S_WTIME = 1024 + 48 ;               // time last write (4 bytes)
    static int const S_MTIME = 1024 + 44;               //  time last mount (4 bytes) 
    static int const S_LASTCHECK = 1024 + 64 ;           //  time last check(4 bytes)
    static int const S_Free_INODE_COUNT = 1024 + 16;    // the number of free inodes (4 bytes)

    // group block (shifted 1024 * 2)
    static int const BG_INODE_TABLE = 1024 * 2 + 8; // the pointer to the first entery of the inode table (4 bytes)

    //Inode table
    static int const I_BLOCKS = 28; //  the number of blocks stored in the inode (4 bytes) (relative to the inode table)
    static int const I_BLOCK = 40;  //  pointer to data blocks  (4 bytes * 15)

    //methodes
    virtual ~Ext2();
    virtual void parseData(FileReader * freader);
    virtual void printFileSystemInfo();
    virtual int checkFileInRoot(FileReader *freader, std::string fileName);
    int getInodeIndex(int Inode_number);

    //setters
    void setExt2Version(int16_t ext2_version);
    void setSize(int i_size);
    void setInodeCount(int s_inode_count);
    void setFirstIno(int s_first_ino);
    void setInodesPerGroup(int s_inodes_per_group);
    void setLogBlockSize(int s_log_block_size);
    void setReservedBlocksCount(int s_r_blocks_count);
    void setFreeBlocksCount(int s_free_blocks_count);
    void setBlocksCount(int s_blocks_count);
    void setFirstBlock(int s_first_block);
    void setBlockPerGroup(int s_blocks_per_group);
    void setFragsPerGroup(int s_frags_per_group);
    void setVolumeName(char s_volume_name[16]);
    void setWtime(int s_wtime);
    void setMtime(int s_mtime);
    void setLastcheck(int s_lastcheck);
    void setFreeInodesCount(int s_free_inodes_count);
    void setInodeTablePointer(int inode_table_pointer);

    //getters
    int16_t
    getExt2Version();
    int  getSize();
    int  getInodeCount();
    int  getFirstIno();
    int  getInodesPerGroup();
    int  getLogBlockSize();
    int  getReservedBlocksCount();
    int  getFreeBlocksCount();
    int  getBlocksCount();
    int  getFirstBlock();
    int  getBlockPerGroup();
    int  getFragsPerGroup();
    char* getVolumeName();
    int  getWtime();
    int  getMtime();
    int  getLastcheck();
    int  getFreeInodesCount();
    int getInodeTablePointer();

    //other methods 
};

#endif