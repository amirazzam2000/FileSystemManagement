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
        }
        else if (strcmp(argv[1], "/find") == 0){
            if (argc != 4 ){
                cout << "error you must provide at least 4 parameters of the format : \"./shooter /find <volume_name> <fileName>\"" << endl;
            }else{
                int found = d.checkFileInRoot(argv[3]);
                if(found != -1){
                    cout << "File found. It occupies " << found << " bytes." << endl;
                }else{
                    cout << "Error. Volume not found." << endl;
                }
            }
        }
        else if (strcmp(argv[1], "/delete") == 0)
        {
            if (argc != 4)
            {
                cout << "error you must provide at least 4 parameters of the format : \"./shooter /find <volume_name> <fileName>\"" << endl;
            }
            else
            {
                bool deleted = d.deleteFile(argv[3]);
                if (deleted)
                {
                    cout << "file deleted" << endl;
                }
                else
                {
                    cout << "Error. Volume not found." << endl;
                }
            }
        }
        else{
            cout << "unsupported operation"<<endl;
        }


        d.close();

    }else{
        cout << "error you must provide at least 3 parameters of the format : \"./shooter <operation> <volume_name> [<fileName>]\"" <<endl;
    }

}