#include "FAT.h"
#include "FileReader.h"
//#include <math.h>
#include<cmath>
#include <string.h>
#include <algorithm>

using namespace std;

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

int FAT::checkFileInRoot(FileReader *freader, std::string fileName)
{
    return checkFile(0, freader, fileName);
}

int FAT::checkFile(int offset, FileReader *freader, std::string fileName)
{
    char name[11];
    int size;
    int16_t nextFile;
    //int shift;

    //RootDirSectors = ((BPB_RootEntCnt * 32) + (BPB_BytsPerSec – 1)) / BPB_BytsPerSec;
    //int root_dir = (int)ceil(((this->getFatRootEnteries() * 32) + (this->getFatSize() - 1)) / this->getFatSize());
    // Fat size = bytes per Sector
    
    int sector_pointer = this->getFatRsvdSecCnt() * this->getFatSize() + this->getFatNumFATs() * this->getFatSecPerFat() * this->getFatSize();

    
    if (offset != 0){
        //(number of root entries * 32) / (bytes per sector)
        offset = (offset - 2) * this->getFatSecPerClus() * this->getFatSize();
        sector_pointer += offset;
        sector_pointer += this->getFatRootEnteries() * 32;   
    }

    cout << "\t\toffset " << sector_pointer << endl;
    
    name[0] = 1;
    int i = 0;
    int8_t isDirectory;
    string full_name;

    while (name[0] != (char)0 && name[0] != (char)229)
    {
        
        freader->getFile().seekg(sector_pointer + (i * 32), ios::beg);
        freader->getFile().read(name, sizeof(name));

        freader->getFile().seekg(sector_pointer + (i * 32) + 28, ios::beg);
        freader->getFile().read(reinterpret_cast<char *>(&size), sizeof(int));

        freader->getFile().seekg(sector_pointer + (i * 32) + 26, ios::beg);
        freader->getFile().read(reinterpret_cast<char *>(&nextFile), sizeof(int16_t));

        freader->getFile().seekg(sector_pointer + (i * 32) + 11, ios::beg);
        freader->getFile().read(reinterpret_cast<char *>(&isDirectory), sizeof(int8_t));
        i++;

        if (size != -1)
        {
            for (int j = 0; j < 8; j++)
            {
                if (name[j] == ' ')
                {
                    break;
                }
                full_name += ::tolower(name[j]);
            }
            if (size != 0)
            {
                full_name += ".";
            }
            for (int j = 8; j < 11; j++)
            {
                if (name[j] == ' ')
                {
                    break;
                }
                full_name += ::tolower(name[j]);
            }
            if (isDirectory != 16)
                cout << "|" << full_name << "|" << strlen(full_name.c_str()) << endl;

            std::for_each(fileName.begin(), fileName.end(), [](char &c) {
                c = ::tolower(c);
            });


            if (isDirectory == 16)
            {
                cout << "\t\tnext file: " << nextFile << endl;
                int aux = -1;
                cout << "\t\t|" << full_name << "|" << strlen(full_name.c_str()) << endl;
                if (strcmp(".", full_name.c_str()) != 0 && strcmp("..", full_name.c_str()) != 0)
                    aux = checkFile(nextFile, freader, fileName);

                if (aux != -1)
                {
                    return aux;
                }

                cout << "\t\t--end Dir " << full_name << " --" << endl;
            }
            else if (strcmp(fileName.c_str(), full_name.c_str()) == 0)
            {
                return size;
            }

            full_name = "";
        }

        
    }
    return -1;
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
    this->meta.fat_name[8] = 0;
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
