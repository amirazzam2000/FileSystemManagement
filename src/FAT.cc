#include "FAT.h"


FAT::FAT(){
        
}

void FAT::setFatVersion(int16_t version){
    this->meta.fat_version = version;
}

void FAT::setFatSecPerClus(char sec_per_clus)
{
    this->meta.sec_per_clus = sec_per_clus;
}

void FAT::setFatRsvdSecCnt(int16_t rsvd_sec_cnt){
    this->meta.rsvd_sec_cnt = rsvd_sec_cnt;
}

void FAT::setFatNumFATs(char num_fats){
    this->meta.num_fats = num_fats;
}

void FAT::setFatOEMName(char * fat_name){
    for(int i = 0 ; i < 8 ; i++){
        this->meta.fat_name[i] = fat_name[i];
    }
}

void FAT::setFatRootEnteries(int16_t root_enteries){
    this->meta.root_enteries = root_enteries;
}

void FAT::setFatSecPerFat(int16_t sec_per_fat){
    this->meta.sec_per_fat = sec_per_fat;
}

void FAT::setFatLable(char lable[11])
{
    for (int i = 0; i < 11; i++)
    {
        this->meta.lable[i] = lable[i];
    }
}

void FAT::setFatSize(int16_t size){
    this->meta.size = size;
}


int16_t FAT::getFatVersion(){
    return this->meta.fat_version;
}

char FAT::getFatSecPerClus()
{
    return this->meta.sec_per_clus;
}

int16_t FAT::getFatRsvdSecCnt(){
    return this->meta.rsvd_sec_cnt;
}

char FAT::getFatNumFATs()
{
    return (char)this->meta.num_fats;
}

char *FAT::getFatOEMName(){
    return this->meta.fat_name;
}

int16_t FAT::getFatRootEnteries(){
    return this->meta.root_enteries;
}
int16_t FAT::getFatSecPerFat(){
    return this->meta.sec_per_fat;
}
char *FAT::getFatLable()
{
    return this->meta.lable;
}

int16_t FAT::getFatSize()
{
    return this->meta.size;
}
