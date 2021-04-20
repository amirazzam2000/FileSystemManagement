#include "FAT.h"
#include "FileReader.h"

FAT::~FAT(){
        
}

void FAT::printFileSystemInfo(){
    cout << "------ Filesystem Information ------" << endl
         << endl;
    cout << "Filesystem: FAT16" << endl;
    cout << "System Name: " << this->getFatOEMName() << endl;
    cout << "Size: " << this->getFatSize() << endl;
    cout << "Sectors Per Cluster: " << (int)this->getFatSecPerClus() << endl;
    cout << "Reserved Sectors: " << this->getFatRsvdSecCnt() << endl;
    cout << "Number of FATs: " << (int)this->getFatNumFATs() << endl;
    cout << "MaxRootEntries: " << this->getFatRootEnteries() << endl;
    cout << "Sectors per FAT: " << this->getFatSecPerFat() << endl;
    cout << "Label: " ;
    for (int i = 0; i < 11 ; i++){
        cout << this->meta.lable[i];
    }
    cout << endl;
}

void FAT::parseData(FileReader * freader)
{
    char aux_8b;     //to read one bytes
    int16_t aux_16b; // to read two bytes
    char aux[8];
    char aux_11b[11];

    //System Name (BS_OEMName)
    freader->getFile().seekg(FAT::BS_OEMName, ios::beg);
    freader->getFile().read(aux, sizeof(aux));
    this->setFatOEMName(aux);

    //Sectors Per Cluster (BPB_SecPerClus)
    freader->getFile().seekg(FAT::BPB_SecPerClus, ios::beg);
    freader->getFile().read(reinterpret_cast<char *>(&aux_8b), sizeof(aux_8b));
    this->setFatSecPerClus(aux_8b);

    //Reserved Sectors (BPB_RsvdSecCnt)
    freader->getFile().seekg(FAT::BPB_RsvdSecCnt, ios::beg);
    freader->getFile().read(reinterpret_cast<char *>(&aux_16b), sizeof(aux_16b));
    this->setFatRsvdSecCnt(aux_16b);

    //Number of FATs (BPB_NumFATs)
    freader->getFile().seekg(FAT::BPB_NumFATs, ios::beg);
    freader->getFile().read(reinterpret_cast<char *>(&aux_8b), sizeof(aux_8b));
    this->setFatNumFATs(aux_8b);

    //MaxRootEntries (BPB_RootEntCnt)
    freader->getFile().seekg(FAT::BPB_RootEntCnt, ios::beg);
    freader->getFile().read(reinterpret_cast<char *>(&aux_16b), sizeof(aux_16b));
    this->setFatRootEnteries(aux_16b);

    //Sectors per FAT (BPB_FATSz16)
    freader->getFile().seekg(FAT::BPB_FATSz16, ios::beg);
    freader->getFile().read(reinterpret_cast<char *>(&aux_16b), sizeof(aux_16b));
    this->setFatSecPerFat(aux_16b);

    for (int i = 0; i < 11; i++)
        aux_11b[i] = '\0';

    //Label (BS_VolLab)
    freader->getFile().seekg(FAT::BS_VolLab, ios::beg);
    freader->getFile().read(aux_11b, sizeof(aux_11b));
    this->setFatLable(aux_11b);

    //Size (BPB_BytsPerSec)
    freader->getFile().seekg(FAT::BPB_BytsPerSec, ios::beg);
    freader->getFile().read(reinterpret_cast<char *>(&aux_16b), sizeof(aux_16b));
    this->setFatSize(aux_16b);

}

int FAT::getRootDirectory()
{
    return 0;
}

/* SETTERS AND GETTERS */
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
