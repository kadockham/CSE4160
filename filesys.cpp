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
    fssynch();
}
int Filesys::newfile(string file) {
    for(int i = 0; i < filename.size(); i++) {
        if(filename[i] == file) {
            //file already exists
            //cout << "file already exists" << endl;
            return -1;
        }
    }
    for(int i = 0; i < filename.size(); i++) {
        if(filename[i] == "XXXXXX") {
            filename[i] = file;
            firstblock[i] = 0;
            fssynch();
            return 1;
        }
    }
    //file not found
    //cout << "file not found" << endl;
    return 0;
}
int Filesys::rmfile(string file) {
    for(int i = 0; i < filename.size(); i++) {
        if(filename[i] == file) {
            if(firstblock[i] == 0) {
                filename[i] = "XXXXXX";
                fssynch();
                return 1;
            }
            else {
                //file not empty
                //cout << "file not empty" << endl;
                return 0;
            }
        }
    }
    //file not found
    //cout << "file not found" << end;
    return -1;
}
int Filesys::getfirstblock(string file) {
    for(int i = 0; i < filename.size(); i++) {
        if(filename[i] == file) {
            return firstblock[i];
        }
    }
    //file not found
    //cout << "file not found" << endl;
    return -1;
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
    string buffer1, buffer2;

    getblock(1, buffer1);
    for(int i = 0; i < fatsize; i++) {
        string b;
        getblock(i+2, b);
        buffer2 += b;
    }
    istringstream instream1;
    istringstream instream2;

    instream1.str(buffer1);
    instream2.str(buffer2);

    for(int i = 0; i<rootsize; i++) {
        string f;
        int b;
        instream1 >> f >> b;
        filename.push_back(f);
        firstblock.push_back(b);
    }
    for(int i = 0; i < getnumberofblocks(); i++) {
        int k;
        instream2 >> k;
        fat.push_back(k);
    }

    return 1;
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
    cout << buffer1 << "buffer1";
    cout << buffer2 << "buffer2";
    vector<string> blocks1 = block(buffer1, getblocksize());
    vector<string> blocks2 = block(buffer2, getblocksize());
    putblock(1, blocks1[0]);
    for(int i = 0; i < blocks2.size(); i++) {
        putblock(i + 2 + fatsize, blocks2[i]);
    }
    return 1;
}