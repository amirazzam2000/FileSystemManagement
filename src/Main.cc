#include "FileReader.h"

using namespace std;


int main(){
    //FileReader f("../resources/Fat16_1024_Con-info.bin");
    FileReader f("../resources/Ext2");
    f.checkFATorEXT();
    f.fileClose();
}