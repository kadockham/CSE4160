/*
 * Name:            Keneth Dockham
 * Filename:        filesys.cpp
 * Description:     This file implements the class described in filesys.h
 */

#include "filesys.h"

using namespace std;

Filesys::Filesys(string diskname, int numberofblocks, int blocksize) : Sdisk(diskname, numberofblocks, blocksize) {
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