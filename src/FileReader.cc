#include "../headers/FileReader.h"

using namespace std;

FileReader::FileReader(string path)
{
    this->file.open(path, ios::in);
    if (this->file.good())
    {
        cout << "file exist" << endl;
    }
    else
    {
        cout << "file doesn't exist" << endl;
    }
}

void FileReader::fileClose()
{
    this->file.close();
}