#include "FileReader.h"


using namespace std;

FileReader::FileReader(string path)
{
    this->file.open(path, ios::in | fstream::out | ios::binary);
    if (!this->file.good())
    {
        this->file.close();
        cout << "file doesn't exist" << endl;
    }
}
fstream& FileReader::getFile(){
    return this->file;
}

void FileReader::fileClose()
{
    if (this->file.good())
        this->file.close();
}