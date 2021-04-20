#include "DirectoryManager.h"
#include <stdio.h>
#include <string.h>

using namespace std;


int main(int argc, char * argv[]){
    //FileReader f("../resources/Fat16_1024_Con-info.bin");
    //"../resources/Ext2"

    if (argc >= 3 ){
        DirectoryManager d(argv[2]);

        if (strcmp(argv[1], "/info") == 0){    
            d.getFileSystem()->printFileSystemInfo();
        }else{
            cout << "unsupported operation"<<endl;
        }


        d.close();

    }else{
        cout << "error you must provide at least 3 parameters of the format : \"./shooter <operation> <volume_name> [<fileName>]\"" <<endl;
    }

}