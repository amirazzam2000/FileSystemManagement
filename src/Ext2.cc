#include "Ext2.h"

Ext2::Ext2()
{
}

void Ext2::setExt2Version(int16_t ext2_version){
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
void Ext2::setFreeInodesCount(int16_t bg_free_inodes_count)
{
    this->meta.bg_free_inodes_count = bg_free_inodes_count;
}

int16_t Ext2::getExt2Version(){
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
int16_t Ext2::getFreeInodesCount(){
    return this->meta.bg_free_inodes_count;
}