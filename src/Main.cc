#include "FileReader.h"
#include <stdio.h>
#include <string.h>

using namespace std;


int main(int argc, char * argv[]){
    //FileReader f("../resources/Fat16_1024_Con-info.bin");
    //"../resources/Ext2"
    if (argc == 3 ){
        if (strcmp(argv[1], "/info") == 0){
            FileReader f(argv[2]);
            f.checkFATorEXT();
            f.fileClose();
        }else{
            cout << "unsupported operation"<<endl;
        }

    }else{
        cout << "error you must provide 3 parameters of the format : \"./shooter <operation> <volume_name>\"" <<endl;
    }

}