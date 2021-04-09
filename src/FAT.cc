#include "FAT.h"


FAT::FAT(){
        
}

void FAT::setFatVersion(int16_t version){
    this->meta.fat_version = version;
}