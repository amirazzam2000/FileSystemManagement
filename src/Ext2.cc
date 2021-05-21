#include "Ext2.h"
#include <time.h>
#include "FileReader.h"
#include <string.h>

Ext2::~Ext2()
{
}

void Ext2::printFileSystemInfo(){
    cout << "------ Filesystem Information ------" << endl
         << endl;

    cout << "Filesystem: Ext2" << endl
         << endl;

    cout << "INFO INODE Inode" << endl;
    cout << "Size: " << this->getSize() << endl;
    cout << "Num Inodes: " << this->getInodeCount() << endl;
    cout << "First Inode: " << this->getFirstIno() << endl;
    cout << "Inodes Group: " << this->getInodesPerGroup() << endl;
    cout << "Inodes Free: " << this->getFreeInodesCount() << endl;

    cout << endl << "BLOCK INFO" << endl;
    cout << "Block Size: " << this->getLogBlockSize() << endl;
    cout << "Reserved Blocks: " << this->getReservedBlocksCount() << endl;
    cout << "Free Blocks: " << this->getFreeBlocksCount() << endl;
    cout << "Total Blocks: " << this->getBlocksCount() << endl;
    cout << "First Block: " << this->getFirstBlock() << endl;
    cout << "Group Blocks: " << this->getBlockPerGroup() << endl;
    cout << "Group Frags: " << this->getFragsPerGroup() << endl;

    cout << endl << "INFO VOLUME" << endl;
    cout << "Volume name: " << this->getVolumeName() << endl;
    time_t aux_time = this->getLastcheck();
    cout << "Last check: " << asctime(gmtime(&aux_time));
    aux_time = this->getMtime();
    cout << "Last: " << asctime(gmtime(&aux_time));
    aux_time = this->getWtime();
    cout << "Last write: " << asctime(gmtime(&aux_time));
}

void Ext2::parseData(FileReader * freader)
{

    char aux_16B[16];
    int aux_4B;

    //the size of the file (I_SIZE)
    freader->getFile().seekg(Ext2::S_INODE_SIZE, ios::beg);
    freader->getFile().read(reinterpret_cast<char *>(&aux_4B), sizeof(aux_4B));
    this->setSize(aux_4B);

    //the total count of inodes (S_INODE_COUNT)
    freader->getFile().seekg(Ext2::S_INODE_COUNT, ios::beg);
    freader->getFile().read(reinterpret_cast<char *>(&aux_4B), sizeof(aux_4B));
    this->setInodeCount(aux_4B);

    //the id of the first inode (S_FIRST_INO)
    freader->getFile().seekg(Ext2::S_FIRST_INO, ios::beg);
    freader->getFile().read(reinterpret_cast<char *>(&aux_4B), sizeof(aux_4B));
    this->setFirstIno(aux_4B);

    //the number of inodes per group (S_INODES_PER_GROUP)
    freader->getFile().seekg(Ext2::S_INODES_PER_GROUP, ios::beg);
    freader->getFile().read(reinterpret_cast<char *>(&aux_4B), sizeof(aux_4B));
    this->setInodesPerGroup(aux_4B);

    //group size (S_LOG_BLOCK_SIZE)
    freader->getFile().seekg(Ext2::S_LOG_BLOCK_SIZE, ios::beg);
    freader->getFile().read(reinterpret_cast<char *>(&aux_4B), sizeof(aux_4B));
    aux_4B = 1024 << aux_4B;
    this->setLogBlockSize(aux_4B);

    //reserved blocks (S_R_BLOCKS_COUNT)
    freader->getFile().seekg(Ext2::S_R_BLOCKS_COUNT, ios::beg);
    freader->getFile().read(reinterpret_cast<char *>(&aux_4B), sizeof(aux_4B));
    this->setReservedBlocksCount(aux_4B);

    //free blocks (S_FREE_BLOCKS_COUNT)
    freader->getFile().seekg(Ext2::S_FREE_BLOCKS_COUNT, ios::beg);
    freader->getFile().read(reinterpret_cast<char *>(&aux_4B), sizeof(aux_4B));
    this->setFreeBlocksCount(aux_4B);

    //total number of blocks (S_BLOCKS_COUNT)
    freader->getFile().seekg(Ext2::S_BLOCKS_COUNT, ios::beg);
    freader->getFile().read(reinterpret_cast<char *>(&aux_4B), sizeof(aux_4B));
    this->setBlocksCount(aux_4B);

    //the first block of data (S_FIRST_BLOCK)
    freader->getFile().seekg(Ext2::S_FIRST_BLOCK, ios::beg);
    freader->getFile().read(reinterpret_cast<char *>(&aux_4B), sizeof(aux_4B));
    this->setFirstBlock(aux_4B);

    //group blocks (S_BLOCKS_PER_GROUP) ?????
    freader->getFile().seekg(Ext2::S_BLOCKS_PER_GROUP, ios::beg);
    freader->getFile().read(reinterpret_cast<char *>(&aux_4B), sizeof(aux_4B));
    this->setBlockPerGroup(aux_4B);

    //frags blocks (S_FRAGS_PER_GROUP)
    freader->getFile().seekg(Ext2::S_FRAGS_PER_GROUP, ios::beg);
    freader->getFile().read(reinterpret_cast<char *>(&aux_4B), sizeof(aux_4B));
    this->setFragsPerGroup(aux_4B);

    //frags blocks (S_VOLUME_NAME)
    freader->getFile().seekg(Ext2::S_VOLUME_NAME, ios::beg);
    freader->getFile().read(aux_16B, sizeof(aux_16B));
    this->setVolumeName(aux_16B);

    //time last write (S_WTIME )
    freader->getFile().seekg(Ext2::S_WTIME, ios::beg);
    freader->getFile().read(reinterpret_cast<char *>(&aux_4B), sizeof(aux_4B));
    this->setWtime(aux_4B);

    //time last mount (S_MTIME)
    freader->getFile().seekg(Ext2::S_MTIME, ios::beg);
    freader->getFile().read(reinterpret_cast<char *>(&aux_4B), sizeof(aux_4B));
    this->setMtime(aux_4B);

    //time last check(S_LASTCHECK)
    freader->getFile().seekg(Ext2::S_LASTCHECK, ios::beg);
    freader->getFile().read(reinterpret_cast<char *>(&aux_4B), sizeof(aux_4B));
    this->setLastcheck(aux_4B);

    //the number of free inodes (BG_FREE_INODES_COUNT)
    freader->getFile().seekg(Ext2::S_Free_INODE_COUNT, ios::beg);
    freader->getFile().read(reinterpret_cast<char *>(&aux_4B), sizeof(aux_4B));
    this->setFreeInodesCount(aux_4B);

    freader->getFile().seekg(Ext2::BG_INODE_TABLE, ios::beg);
    freader->getFile().read(reinterpret_cast<char *>(&aux_4B), sizeof(aux_4B));
    this->setInodeTablePointer(aux_4B);
}

int Ext2::checkFileInRoot(FileReader *freader, std::string fileName)
{
    return this->checkFile(getInodeIndex(2), freader, fileName);
}


int Ext2::checkFile(int directory_index, FileReader *freader, std::string fileName)
{

    int size_of_blocks;
    int aux_size = 0;
    int inode_pointer;
    int data_entry = 0;

    int16_t record_len = 0;
    char name_len;
    char file_type;
    char *file_name = NULL;

    int aux_data_postion = 0;

    
    freader->getFile().seekg(directory_index + Ext2::I_BLOCKS, ios::beg);
    freader->getFile().read(reinterpret_cast<char *>(&size_of_blocks), sizeof(size_of_blocks));

    
    
    while (aux_size < size_of_blocks ) //&& data_entry < 13)
    {
        freader->getFile().seekg(directory_index + Ext2::I_BLOCK + (4 * data_entry++), ios::beg);
        freader->getFile().read(reinterpret_cast<char *>(&aux_data_postion), sizeof(aux_data_postion));

        aux_data_postion *= this->getLogBlockSize();

        freader->getFile().seekg(aux_data_postion, ios::beg);


        aux_size++;

        int amount_of_data_read = 0;

        while (amount_of_data_read < this->getLogBlockSize())
        {
            
            record_len = 0;
            freader->getFile().seekg(aux_data_postion, ios::beg);
            freader->getFile().read(reinterpret_cast<char *>(&inode_pointer), sizeof(int));

            freader->getFile().read(reinterpret_cast<char *>(&record_len), sizeof(int16_t));

            aux_data_postion += record_len;
            amount_of_data_read += record_len;


            freader->getFile().read(reinterpret_cast<char *>(&name_len), sizeof(char));

            file_name = (char *)calloc(sizeof(char), name_len + 1);

            freader->getFile().read(reinterpret_cast<char *>(&file_type), sizeof(char));
            freader->getFile().read(file_name, sizeof(char) * name_len);

            if (record_len == 0){
                free(file_name);
                break;
            }

            if (file_type == Ext2::EXT2_FT_DIR 
                    && strcmp(".", file_name) != 0 
                    && strcmp("..", file_name) != 0 
                    && strcmp("lost+found", file_name) != 0)
            {
                int aux = this->checkFile(getInodeIndex(inode_pointer), freader, fileName);
                if (aux != -1)
                {
                    free(file_name);
                    return aux;
                }
            }

            if (strcmp(file_name, fileName.c_str()) == 0 && file_type != Ext2::EXT2_FT_DIR)
            {
                free(file_name);
                return this->getFileSize(getInodeIndex(inode_pointer), freader);
            }
            free(file_name);
        }
    }

    return -1;
}


int Ext2::getFileSize(int Inode_index, FileReader *freader)
{
    int size;
    freader->getFile().seekg(Inode_index + Ext2::I_SIZE, ios::beg);
    freader->getFile().read(reinterpret_cast<char *>(&size), sizeof(size));
    
    return size;

}

int Ext2::getInodeIndex(int Inode_number){
    int block_group = (Inode_number - 1) / this->getInodesPerGroup();

    int local_index = (Inode_number - 1) % this->getInodesPerGroup();

    int group_offset = 1024 + this->getLogBlockSize() * this->getBlockPerGroup() * block_group;

    int block_offset = (this->getInodeTablePointer() - 1) * this->getLogBlockSize();

    return group_offset        // the group block offset
                       + block_offset      // the inode table block offset
                       + local_index * 128; // the inode offset relative to the table
}

bool Ext2::deleteFile(FileReader *freader, std::string fileName){
    return this->deleteFileInExt2(getInodeIndex(2), freader, fileName);
}

bool Ext2::deleteFileInExt2(int directory_index, FileReader *freader, std::string fileName){

    int size_of_blocks;
    int aux_size = 0;
    int data_entry = 0;

    int inode_pointer[2];
    int16_t record_len[2];
    record_len[0] = 0;
    record_len[1] = 0;
    char name_len[2];
    char file_type[2];
    char *file_name[2];
    file_name[0] = NULL;
    file_name[1] = NULL;

    int i = 0;


    int aux_data_postion[3];

    freader->getFile().seekg(directory_index + Ext2::I_BLOCKS, ios::beg);
    freader->getFile().read(reinterpret_cast<char *>(&size_of_blocks), sizeof(size_of_blocks));

    while (aux_size < size_of_blocks) //&& data_entry < 13)
    {

        freader->getFile().seekg(directory_index + Ext2::I_BLOCK + (4 * data_entry++), ios::beg);
        freader->getFile().read(reinterpret_cast<char *>(&aux_data_postion), sizeof(aux_data_postion));

        aux_data_postion[0] *= this->getLogBlockSize();

        freader->getFile().seekg(aux_data_postion[0], ios::beg);

        aux_size++;

        int amount_of_data_read = 0;
        i = 0;

        while (amount_of_data_read < this->getLogBlockSize())
        {
            int current_position = i % 2;
            record_len[current_position] = 0;
            freader->getFile().seekg(aux_data_postion[i % 3], ios::beg);
            freader->getFile().read(reinterpret_cast<char *>(&inode_pointer[current_position]), sizeof(int));
            freader->getFile().read(reinterpret_cast<char *>(&record_len[current_position]), sizeof(int16_t));

            aux_data_postion[(i + 1) % 3] = aux_data_postion[(i%3)] + record_len[current_position];
            amount_of_data_read += record_len[current_position];

            freader->getFile().read(reinterpret_cast<char *>(&name_len[current_position]), sizeof(char));

            file_name[current_position] = (char *)calloc(sizeof(char), name_len[current_position] + 1);

            freader->getFile().read(reinterpret_cast<char *>(&file_type), sizeof(char));
            freader->getFile().read(file_name[current_position], sizeof(char) * name_len[current_position]);

            if (record_len[current_position] == 0)
            {
                if (NULL != file_name[current_position])
                    free(file_name[current_position]);
                break;
            }

            if (file_type[current_position] == Ext2::EXT2_FT_DIR 
                    && strcmp(".", file_name[current_position]) != 0 
                    && strcmp("..", file_name[current_position]) != 0 
                    && strcmp("lost+found", file_name[current_position]) != 0)
            {
                bool aux = this->deleteFileInExt2(getInodeIndex(inode_pointer[current_position]), freader, fileName);
                if (aux)
                {
                    if (NULL != file_name[current_position])
                        free(file_name[current_position]);
                    return aux;
                }
            }

            if (strcmp(file_name[current_position], fileName.c_str()) == 0 
                    && file_type[current_position] != Ext2::EXT2_FT_DIR)
            {

                if(i != 0){
                    record_len[(i-1)%2] += record_len[i%2];
                    freader->getFile().seekp(aux_data_postion[(i - 1) % 3] + 4, ios::beg);
                    freader->getFile().clear();
                    freader->getFile().write(reinterpret_cast<char *>(&record_len[(i - 1) % 2]), sizeof(int16_t));
                }else{
                    i++;
                    int current_position = i % 2;
                    freader->getFile().seekg(aux_data_postion[i % 3], ios::beg);
                    freader->getFile().read(reinterpret_cast<char *>(&inode_pointer[current_position]), sizeof(int));
                    freader->getFile().read(reinterpret_cast<char *>(&record_len[current_position]), sizeof(int16_t));
                    freader->getFile().read(reinterpret_cast<char *>(&name_len[current_position]), sizeof(char));
                    file_name[current_position] = (char *)calloc(sizeof(char), name_len[current_position] + 1);
                    freader->getFile().read(reinterpret_cast<char *>(&file_type[current_position]), sizeof(char));
                    freader->getFile().read(file_name[current_position], sizeof(char) * name_len[current_position]);

                    freader->getFile().seekp(aux_data_postion[(i-1) % 3], ios::beg);
                    freader->getFile().clear();
                    freader->getFile().write(reinterpret_cast<char *>(&inode_pointer[current_position]), sizeof(int));
                    freader->getFile().clear();
                    record_len[current_position] += record_len[(i-1)%2];
                    freader->getFile().write(reinterpret_cast<char *>(&record_len[current_position]), sizeof(int16_t));
                    freader->getFile().clear();
                    freader->getFile().write(reinterpret_cast<char *>(&name_len[current_position]), sizeof(char));
                    freader->getFile().clear();
                    freader->getFile().write(reinterpret_cast<char *>(&file_type[current_position]), sizeof(char));
                    freader->getFile().clear();
                    freader->getFile().write(file_name[current_position], sizeof(char) * name_len[current_position]);
                }

                if (NULL != file_name[0]){
                    free(file_name[0]);
                }
                if (NULL != file_name[1])
                {
                    free(file_name[1]);
                }
                return true;
            }
            if (NULL != file_name[current_position])
            {
                free(file_name[current_position]);
                file_name[current_position] = NULL;
            }
            i++;
        }
    }
    return false;
}

/* SETTERS AND GETTERS */
void Ext2::setExt2Version(int16_t ext2_version)
{
    this->meta.ext2_version = ext2_version;
}
void Ext2::setSize(int i_size){
    this->meta.i_size = i_size;
}
void Ext2::setInodeCount(int s_inode_count){
    this->meta.s_inode_count = s_inode_count;
}
void Ext2::setFirstIno(int s_first_ino){
    this->meta.s_first_ino = s_first_ino;
}
void Ext2::setInodesPerGroup(int s_inodes_per_group){
    this->meta.s_inodes_per_group = s_inodes_per_group;
}
void Ext2::setLogBlockSize(int s_log_block_size){
    this->meta.s_log_block_size = s_log_block_size;
}
void Ext2::setReservedBlocksCount(int s_r_blocks_count)
{
    this->meta.s_r_blocks_count = s_r_blocks_count;
}
void Ext2::setFreeBlocksCount(int s_free_blocks_count){
    this->meta.s_free_blocks_count = s_free_blocks_count;
}
void Ext2::setBlocksCount(int s_blocks_count){
    this->meta.s_blocks_count = s_blocks_count;
}
void Ext2::setFirstBlock(int s_first_block){
    this->meta.s_first_block = s_first_block;
}
void Ext2::setBlockPerGroup(int s_blocks_per_group){
    this->meta.s_blocks_per_group = s_blocks_per_group;
}
void Ext2::setFragsPerGroup(int s_frags_per_group){
    this->meta.s_frags_per_group = s_frags_per_group;
}
void Ext2::setVolumeName(char s_volume_name[16]){
    for (int i = 0; i < 16; i++)
    {
        this->meta.s_volume_name[i] = s_volume_name[i];
    }
}
void Ext2::setWtime(int s_wtime){
    this->meta.s_wtime = s_wtime;
}
void Ext2::setMtime(int s_mtime){
    this->meta.s_mtime = s_mtime;
}
void Ext2::setLastcheck(int s_lastcheck){
    this->meta.s_lastcheck = s_lastcheck;
}
void Ext2::setFreeInodesCount(int bg_free_inodes_count)
{
    this->meta.s_free_inodes_count = bg_free_inodes_count;
}

void Ext2::setInodeTablePointer(int inode_table_pointer)
{
    this->meta.inode_table_pointer = inode_table_pointer;
}

int16_t Ext2::getExt2Version()
{
    return this->meta.ext2_version;
}
int Ext2::getSize(){
    return this->meta.i_size;
}
int Ext2::getInodeCount(){
    return this->meta.s_inode_count;
}
int Ext2::getFirstIno(){
    return this->meta.s_first_ino;
}
int Ext2::getInodesPerGroup(){
    return this->meta.s_inodes_per_group;
}
int Ext2::getLogBlockSize(){
    return this->meta.s_log_block_size;
}
int Ext2::getReservedBlocksCount(){
    return this->meta.s_r_blocks_count;
}
int Ext2::getFreeBlocksCount(){
    return this->meta.s_free_blocks_count;
}
int Ext2::getBlocksCount(){
    return this->meta.s_blocks_count;
}
int Ext2::getFirstBlock(){
    return this->meta.s_first_block;
}
int Ext2::getBlockPerGroup(){
    return this->meta.s_blocks_per_group;
}
int Ext2::getFragsPerGroup(){
    return this->meta.s_frags_per_group;
}
char *Ext2::getVolumeName(){
    return this->meta.s_volume_name;
}
int Ext2::getWtime(){
    return this->meta.s_wtime;
}
int Ext2::getMtime(){
    return this->meta.s_mtime;
}
int Ext2::getLastcheck(){
    return this->meta.s_lastcheck;
}
int Ext2::getFreeInodesCount()
{
    return this->meta.s_free_inodes_count;
}

int Ext2::getInodeTablePointer()
{
    return this->meta.inode_table_pointer;
}
