/*
 * Name:		Kenneth Dockham
 * Filename:	shell.h
 * Description:	This is the header file for the shell
 */
#ifndef SHELL_H
#define SHELL_H

#include "filesys.h"

using namespace std;

class Shell: public Filesys {
    public:
        Shell(string filename, int numberofblocks, int blocksize);
        int dir();
        int add(string file, string buffer);
        int del(string file);
        int type(string file);
        int copy(string file1, string file2);
};

#endif