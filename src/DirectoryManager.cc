#include "DirectoryManager.h"


DirectoryManager::DirectoryManager(string path)
{
    this->freader = new FileReader(path);

    //check if it's a FAT
    this->freader->getFile().seekg(FAT::BS_FilSysType, ios::beg);
    char aux[8];
    this->freader->getFile().read(aux, sizeof(aux));

    bool isFat = true;
    for (int i = 0; i < 8; i++)
    {
        if (aux[i] != FAT_STRING[i])
        {
            isFat = false;
        }
    }

    if (isFat)
    {
        //if FAT
        this->filesystem = new FAT();
    }
    else
    {
        //check if Ext2
        this->freader->getFile().seekg(Ext2::S_MAGIC, ios::beg);
        int16_t aux2 = 0;
        this->freader->getFile().read(reinterpret_cast<char *>(&aux2), sizeof(aux2));

        if (aux2 == (int16_t)Ext2::MAGIC_VALUE)
        {
            //If Ext2
            this->filesystem = new Ext2();
            
        }
        else
        {   
            //else
            cout << "File system is neither EXT2 nor FAT16." << endl;
            exit(0);
        }
    }

    //parse the data
    this->filesystem->parseData(this->freader);
}

FileSystem * DirectoryManager::getFileSystem(){
    return this->filesystem;
}

void DirectoryManager::close(){
    this->freader->fileClose();
    delete (this->filesystem);
    delete (this->freader);
}
