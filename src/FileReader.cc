#include "FileReader.h"


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
ifstream& FileReader::getFile(){
    return this->file;
}

void FileReader::fileClose()
{
    if (this->file.good())
        this->file.close();
}