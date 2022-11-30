/*
 * Name:		Kenneth Dockham
 * Filename:	shell.h
 * Description:	This is the implimentation for the shell.h
 */

#include "shell.h"
#include "block.h"
#include <iostream>

using namespace std;

Shell::Shell(string diskname, int numberofblocks, int blocksize) : Filesys(diskname, numberofblocks, blocksize) {

}
int Shell::dir() {
    vector<string> flist = ls();
    for(int i = 0; i < flist.size(); i++) {
        cout << flist[i] << endl;
    }
    return 1;
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
    while(block != 0) {
        int nblock = nextblock(file, block);
        delblock(file, block);
        block = nblock;
    }
    rmfile(file);
    return 1;
}
int Shell::type(string file) {
    string buffer;
    int block = getfirstblock(file);
    if (block == -1) 
    {
        cout << "Error" << endl;
        return 0;
    }
    while(block != 0) {
        string b;
        readblock(file, block, b);
        buffer += b;
        block = nextblock(file, block);
    }
    cout << buffer << endl;
    return 1;
}
int Shell::copy(string file1, string file2) {
    string buffer;
    newfile(file2);
    int block = getfirstblock(file1);
    while(block != 0) {
        string b;
        readblock(file1, block, b);
        addblock(file2, b);
        buffer += b;
        block = nextblock(file1, block);
    }
    return 1;
};