#include "FileReader.h"
#include <time.h>

using namespace std;

FileReader::FileReader(string path)
{
    this->file.open(path, ios::in | ios::binary);
    if (!this->file.good())
    {
        this->file.close();
        cout << "file doesn't exist" << endl;
    }
}

void FileReader::checkFATorEXT() // for thr ext2 check the magic paramater end of page 11
{ 

    this->file.seekg(FAT::BS_FilSysType, ios::beg);
    char aux[8];
    this->file.read(aux, sizeof(aux));

    bool isFAT = true;
    for (int i = 0; i < 8; i++)
    {
        if (aux[i] != FAT_STRING[i])
        {
            isFAT = false;
        }
    }


    if (isFAT)
    {
        this->parseFATData();
        this->displayFatDetails();
    }
    else
    {
        this->file.seekg(Ext2::S_MAGIC, ios::beg);
        int16_t aux2 = 0;
        this->file.read(reinterpret_cast<char*> (&aux2), sizeof(aux2));

        if (aux2 == (int16_t)Ext2::MAGIC_VALUE)
        {
            this->parseExtData();
            this->displayExtDetails();
        }
        else{
            cout << "File system is neither EXT2 nor FAT16." <<endl;
        }
    }

    //return aux;
}

void FileReader::parseFATData(){
    char aux_8b; //to read one bytes
    int16_t aux_16b; // to read two bytes
    char aux[8];
    char aux_11b[11];

    //System Name (BS_OEMName)
    this->file.seekg(FAT::BS_OEMName, ios::beg);
    this->file.read(aux, sizeof(aux));
    this->fat.setFatOEMName(aux);
    

    //Sectors Per Cluster (BPB_SecPerClus)
    this->file.seekg(FAT::BPB_SecPerClus, ios::beg);
    this->file.read(reinterpret_cast<char *>(&aux_8b), sizeof(aux_8b));
    this->fat.setFatSecPerClus(aux_8b);

    //Reserved Sectors (BPB_RsvdSecCnt)
    this->file.seekg(FAT::BPB_RsvdSecCnt, ios::beg);
    this->file.read(reinterpret_cast<char *>(&aux_16b), sizeof(aux_16b));
    this->fat.setFatRsvdSecCnt(aux_16b);

    //Number of FATs (BPB_NumFATs)
    this->file.seekg(FAT::BPB_NumFATs, ios::beg);
    this->file.read(reinterpret_cast<char *>(&aux_8b), sizeof(aux_8b));
    this->fat.setFatNumFATs(aux_8b);

    //MaxRootEntries (BPB_RootEntCnt)
    this->file.seekg(FAT::BPB_RootEntCnt, ios::beg);
    this->file.read(reinterpret_cast<char *>(&aux_16b), sizeof(aux_16b));
    this->fat.setFatRootEnteries(aux_16b);

    //Sectors per FAT (BPB_FATSz16)
    this->file.seekg(FAT::BPB_FATSz16, ios::beg);
    this->file.read(reinterpret_cast<char *>(&aux_16b), sizeof(aux_16b));
    this->fat.setFatSecPerFat(aux_16b);


    //Label (BS_VolLab)
    this->file.seekg(FAT::BS_VolLab, ios::beg);
    this->file.read(aux_11b, sizeof(aux_11b));
    this->fat.setFatLable(aux_11b);

    //Size (BPB_BytsPerSec)
    this->file.seekg(FAT::BPB_BytsPerSec, ios::beg);
    this->file.read(reinterpret_cast<char *>(&aux_16b), sizeof(aux_16b));
    this->fat.setFatSize(aux_16b);
}

void FileReader::displayFatDetails(){
    cout << "------ Filesystem Information ------" << endl << endl;
    cout << "Filesystem: FAT16" <<endl;
    cout << "System Name: " << this->fat.getFatOEMName() << endl;
    cout << "Size: " << this->fat.getFatSize() << endl;
    cout << "Sectors Per Cluster: " << (int)this->fat.getFatSecPerClus() << endl;
    cout << "Reserved Sectors: " << this->fat.getFatRsvdSecCnt() << endl;
    cout << "Number of FATs: " << (int)this->fat.getFatNumFATs() << endl;
    cout << "MaxRootEntries: " << this->fat.getFatRootEnteries() << endl;
    cout << "Sectors per FAT: " << this->fat.getFatSecPerFat() << endl;
    cout << "Label: " << this->fat.getFatLable() << endl;
}

void FileReader::parseExtData(){

    int16_t aux_16; // to read two bytes
    char aux_16B[16];
    int aux_4B;

    //the size of the file (I_SIZE)
    this->file.seekg(Ext2::S_INODE_SIZE, ios::beg);
    this->file.read(reinterpret_cast<char *>(&aux_4B), sizeof(aux_4B));
    this->ext.setSize(aux_4B);

    //the total count of inodes (S_INODE_COUNT)
    this->file.seekg(Ext2::S_INODE_COUNT, ios::beg);
    this->file.read(reinterpret_cast<char *>(&aux_4B), sizeof(aux_4B));
    this->ext.setInodeCount(aux_4B);

    //the id of the first inode (S_FIRST_INO)
    this->file.seekg(Ext2::S_FIRST_INO, ios::beg);
    this->file.read(reinterpret_cast<char *>(&aux_4B), sizeof(aux_4B));
    this->ext.setFirstIno(aux_4B);

    //the number of inodes per group (S_INODES_PER_GROUP)
    this->file.seekg(Ext2::S_INODES_PER_GROUP, ios::beg);
    this->file.read(reinterpret_cast<char *>(&aux_4B), sizeof(aux_4B));
    this->ext.setInodesPerGroup(aux_4B);

    //group size (S_LOG_BLOCK_SIZE) 
    this->file.seekg(Ext2::S_LOG_BLOCK_SIZE, ios::beg);
    this->file.read(reinterpret_cast<char *>(&aux_4B), sizeof(aux_4B));
    aux_4B = 1024 << aux_4B;
     this->ext.setLogBlockSize(aux_4B);

    //reserved blocks (S_R_BLOCKS_COUNT)
    this->file.seekg(Ext2::S_R_BLOCKS_COUNT, ios::beg);
    this->file.read(reinterpret_cast<char *>(&aux_4B), sizeof(aux_4B));
    this->ext.setReservedBlocksCount(aux_4B);

    //free blocks (S_FREE_BLOCKS_COUNT)
    this->file.seekg(Ext2::S_FREE_BLOCKS_COUNT, ios::beg);
    this->file.read(reinterpret_cast<char *>(&aux_4B), sizeof(aux_4B));
    this->ext.setFreeBlocksCount(aux_4B);

    //total number of blocks (S_BLOCKS_COUNT)
    this->file.seekg(Ext2::S_BLOCKS_COUNT, ios::beg);
    this->file.read(reinterpret_cast<char *>(&aux_4B), sizeof(aux_4B));
    this->ext.setBlocksCount(aux_4B);

    //the first block of data (S_FIRST_BLOCK)
    this->file.seekg(Ext2::S_FIRST_BLOCK, ios::beg);
    this->file.read(reinterpret_cast<char *>(&aux_4B), sizeof(aux_4B));
    this->ext.setFirstBlock(aux_4B);

    //group blocks (S_BLOCKS_PER_GROUP) ?????
    this->file.seekg(Ext2::S_BLOCKS_PER_GROUP, ios::beg);
    this->file.read(reinterpret_cast<char *>(&aux_4B), sizeof(aux_4B));
    this->ext.setBlockPerGroup(aux_4B);

    //frags blocks (S_FRAGS_PER_GROUP)
    this->file.seekg(Ext2::S_FRAGS_PER_GROUP, ios::beg);
    this->file.read(reinterpret_cast<char *>(&aux_4B), sizeof(aux_4B));
    this->ext.setFragsPerGroup(aux_4B);

    //frags blocks (S_VOLUME_NAME)
    this->file.seekg(Ext2::S_VOLUME_NAME, ios::beg);
    this->file.read(aux_16B, sizeof(aux_16B));
    this->ext.setVolumeName(aux_16B);

    //time last write (S_WTIME )
    this->file.seekg(Ext2::S_WTIME, ios::beg);
    this->file.read(reinterpret_cast<char *>(&aux_4B), sizeof(aux_4B));
    this->ext.setWtime(aux_4B);

    //time last mount (S_MTIME) 
    this->file.seekg(Ext2::S_MTIME, ios::beg);
    this->file.read(reinterpret_cast<char *>(&aux_4B), sizeof(aux_4B));
    this->ext.setMtime(aux_4B);

    //time last check(S_LASTCHECK)
    this->file.seekg(Ext2::S_LASTCHECK, ios::beg);
    this->file.read(reinterpret_cast<char *>(&aux_4B), sizeof(aux_4B));
    this->ext.setLastcheck(aux_4B);

    //the number of free inodes (BG_FREE_INODES_COUNT)
    this->file.seekg(Ext2::BG_FREE_INODES_COUNT, ios::beg);
    this->file.read(reinterpret_cast<char *>(&aux_16), sizeof(aux_16));
    this->ext.setFreeInodesCount(aux_16);
}

void FileReader::displayExtDetails(){
    cout << "------ Filesystem Information ------" << endl << endl;
    
    cout << "Filesystem: Ext2" << endl << endl;

    cout << "INFO INODE Inode" << endl;
    cout << "Size: " << this->ext.getSize() << endl;
    cout << "Num Inodes: " << this->ext.getInodeCount() << endl;
    cout << "First Inode: " << this->ext.getFirstIno() << endl;
    cout << "Inodes Group: " << this->ext.getInodesPerGroup() << endl;
    cout << "Inodes Free: " << this->ext.getFreeInodesCount() << endl;


    cout <<endl << "BLOCK INFO" << endl;
    cout << "Block Size: " << this->ext.getLogBlockSize() << endl;
    cout << "Reserved Blocks: " << this->ext.getReservedBlocksCount() << endl;
    cout << "Free Blocks: " << this->ext.getFreeBlocksCount() << endl;
    cout << "Total Blocks: " << this->ext.getBlocksCount() << endl;
    cout << "First Block: " << this->ext.getFirstBlock() << endl;
    cout << "Group Blocks: " << this->ext.getBlockPerGroup() << endl;
    cout << "Group Frags: " << this->ext.getFragsPerGroup() << endl;

    /*
    INFO VOLUME
    Volume name: ext2fs_prova1
    Last check: Tue Apr 24 18:41:24 2007edit
    Last: Tue Apr 24 19:33:11 2007
    Last write: Tue Apr 24 19:33:16 2007


    */
    cout << endl << "INFO VOLUME" << endl;
    cout << "Volume name: " << this->ext.getVolumeName() << endl;
    time_t aux_time = this->ext.getLastcheck();
    cout << "Last check: " << asctime(gmtime(&aux_time));
    aux_time = this->ext.getMtime();
    cout << "Last: " << asctime(gmtime(&aux_time));
    aux_time = this->ext.getWtime();
    cout << "Last write: " << asctime(gmtime(&aux_time));
}

void FileReader::fileClose()
{
    if (this->file.good())
        this->file.close();
}