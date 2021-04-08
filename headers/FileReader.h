#ifndef _FILE_READER_
#define _FILE_READER_
#include <stdio.h>
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

class FileReader {
    private:
        ifstream file;


    public:
        FileReader(string path)
        {
            this->file.open(path, ios::in);
            if(this->file.good()){
                cout << "file exist" << endl;
            }
            else{
                cout << "file doesn't exist" << endl;
            }

        }

        void fileClose(){
            this->file.close();
        }
};
#endif
