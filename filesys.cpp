/*
 * Name:        Keneth Dockham
 * Filename:    filesys.cpp
 * Description: This file implements the class described in filesys.h
 */

#include "filesys.h"
#include "block.h"
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

Filesys::Filesys(string diskname, int numberofblocks, int blocksize) : Sdisk(diskname, numberofblocks, blocksize) {
    rootsize = getblocksize()/12;
    fatsize = ((getnumberofblocks()*5)/getblocksize()) + 1;

    string buffer;
    getblock(1, buffer);
    if(buffer[0] == '#') {
        buildfs();
        fssynch();
    }
    else {
        readfs();
    }
}
int Filesys::fsclose() {

}
int Filesys::newfile(string file) {
}
int Filesys::rmfile(string file) {
}
int Filesys::getfirstblock(string file) {
}
int Filesys::addblock(string file, string block) {
}
int Filesys::delblock(string file, int blocknumber) {
}
int Filesys::readblock(string files, int blocknumber, string& buffer) {
}
int Filesys::writeblock(string file, int blocknumber, string buffer) {
}
int Filesys::nextblock(string file, int blocknumber) {
}
int Filesys::buildfs() {
    for(int i = 0; i < rootsize; i++) {
        filename.push_back("XXXXXX");
        firstblock.push_back(0);
    }
    fat.push_back(2+fatsize);
    fat.push_back(-1);
    for(int i = 0; i < fatsize; i++) {
        fat.push_back(-1);
    }
    for(int i = 2+fatsize; i < getnumberofblocks(); i++) {
        fat.push_back(i+1);
    }
    fat[fatsize-1] = 0;
    return 1;
}
int Filesys::readfs() {
}
int Filesys::fssynch() {
    ostringstream outstream1;
    for(int i = 0; i < firstblock.size(); i++) {
        outstream1 << filename[i] << " " << firstblock[i] << " ";
    }
    ostringstream outstream2;
    for(int i = 0; i < fatsize; i++) {
        outstream2 << fat[i] << " ";
    }
    string buffer1 = outstream1.str();
    string buffer2 = outstream2.str();
    cout << buffer1;
    cout << buffer2;
    vector<string> blocks1 = block(buffer1, getblocksize());
    vector<string> blocks2 = block(buffer2, getblocksize());
    putblock(1, blocks1[0]);
    for(int i = 0; i < blocks2.size(); i++) {
        putblock(i + 2 + fatsize, blocks2[i]);
    }
    return 1;
}
