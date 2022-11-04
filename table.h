/*
 * Name:		Kenneth Dockham
 * Filename:	shell.h
 * Description:	This is the header file for the shell
 */
#ifndef TABLE_H
#define TABLE_H

#include "filesys.h"

using namespace std;

class Table : public Filesys
{
    public:
        Table(string diskname, int blocksize, int numberofblocks, string flatfile, string indexfile);
        int buildTable(string input_file);
        int search(string value);
    private:
        string flatfile;
        string indexfile;
        int indexSearch(string value);

};
#endif
