#include "FileReader.h"
#include "FAT.h"
#include "Ext2.h"

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

    bool isFAT = false;
    for (int i = 0; i < 8; i++)
    {
        cout << aux[i];
        if (aux[i] != FAT_STRING[i])
        {
            isFAT = false;
        }
    }
    if (isFAT)
    {
        cout<< "this is a FAT file!"<< endl;
    }
    else
    {
        this->file.seekg(Ext2::S_MAGIC, ios::beg);
        int16_t aux2 = 0;
        this->file.read(reinterpret_cast<char*> (&aux2), sizeof(aux2));

        if (aux2 == (int16_t)Ext2::MAGIC_VALUE)
        {
            cout<< "this is an Ext2 file system"<< endl;
        }
    }

    //return aux;
}

void FileReader::fileClose()
{
    if (this->file.good())
         this->file.close();
}