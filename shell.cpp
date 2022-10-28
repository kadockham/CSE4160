/*
 * Name:		Kenneth Dockham
 * Filename:	shell.h
 * Description:	This is the implimentation for the shell.h
 */

#include "shell.h"
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

}
int Shell::del(string file) {

}
int Shell::type(string file) {

}
int Shell::copy(string file1, string file2) {

};