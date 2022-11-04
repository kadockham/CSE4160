/*
 * Name:		Kenneth Dockham
 * Filename:	shell.h
 * Description:	This is the implimentation for the shell.h
 */

#include "shell.h"
#include "block.h"
#include <iostream>

using namespace std;

Shell::Shell(string filename, int numberofblocks, int blocksize) : Filesys(filename, numberofblocks, blocksize) {

}
int Shell::dir() {
    vector<string> flist = ls();
    for(int i = 0; i < flist.size(); i++) {
        cout << flist[i] << endl;
    }
}
int Shell::add(string file, string buffer) {
    int code = newfile(file);
    if(code == 1) {
        vector<string> blocks = block(buffer, getblocksize());
        for(int i = 0; i < blocks.size(); i++) {
            code = addblock(file, blocks[i]);
        }
        return 1;
    }
    return 0;
}
int Shell::del(string file) {
    int block = getfirstblock(file);
    while(getfirstblock(file) != 0) {
        int nblock = nextblock(file, block);
        delblock(file, block);
        block = nblock;
    }
    return 1;
}
int Shell::type(string file) {

}
int Shell::copy(string file1, string file2) {

};