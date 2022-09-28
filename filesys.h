/*
 *  Name:           Kenneth Dockham
 *  Filename:       filesys.h
 *  Description:    This file is the headerfile for the class Filesys
 */

#ifndef FILESYS_H
#define FILESYS_H

#include "sdisk.h"
#include <vector>

using namespace std;

class Filesys: public Sdisk {
    public:
        Filesys(string diskname, int numberofblocks, int blocksize);
        int fsclose();
        int newfile(string file);
        int rmfile(string file);
        int getfirstblock(string file);
        int addblock(string file, string block);
        int delblock(string file, int blocknumber);
        int readblock(string file, int blocknumber, string& buffer);
        int writeblock(string file, int blocknumber, string buffer);
        int nextblock(string file, int blocknumber);
    private:
        int rootsize;
        int fatsize;
        vector<string> filename;
        vector<int> firstblock;
        vector<int> fat;
        int buildfs();
        int readfs();
        int fssynch();
};

#endif