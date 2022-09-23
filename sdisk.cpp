/*
 * Name:	Kenneth Dockham
 * Filename:	sdisk.cpp
 * Description: This file implements the class described in sdisk.h 
 */

#include "sdisk.h"
#include <fstream>
#include <iostream>

using namespace std;

Sdisk::Sdisk(string diskname, int numberofblocks, int blocksize) {
	this -> diskname = diskname;
	this -> numberofblocks = numberofblocks;
	this -> blocksize = blocksize;
	//check if diskname exists
	ifstream indisk;
	indisk.open(diskname.c_str());
	if(indisk.fail()) {
		indisk.close();
		ofstream outdisk;
		outdisk.open(diskname.c_str());
		for(int i = 0; i < (numberofblocks * blocksize); i++) {
			outdisk.put('#');
		}
	}
	else
	{
		//count the number of characters and compare to blocksize * of # of blocks
		int count = 0;
		char c;
		indisk.get(c);
		while(indisk.good()) {
			count++;
			indisk.get(c);
		}
		if(count == (numberofblocks * blocksize)) {
			cout << "File already exists" << endl;
		}
		else {
			cout << "Warning: file exists with different number of characters" << endl;
		}
	}
}
int Sdisk::getblock(int blocknumber, string &buffer) {
	//This puts takes a block from memeory and puts it into buffer
	fstream iofile;
	iofile.open(diskname.c_str(), ios::in | ios::out);
	if(blocknumber < 0 || blocknumber >= numberofblocks) {
		cout << "Error: block dosen't exist" << endl;
		return -1;
	}
	iofile.seekg(blocksize * blocknumber);
	buffer.clear();
	char c;
	for(int i = 0; i < blocksize; i++) {
		iofile.get(c);
		buffer.push_back(c);
	}
	return 1;
}
int Sdisk::putblock(int blocknumber, string buffer) {
	//This puts the buffer into the given blocknumber
	fstream iofile;
        iofile.open(diskname.c_str(), ios::in | ios::out);
        if(blocknumber < 0 || blocknumber >= numberofblocks) {
                cout << "Error: block dosen't exist" << endl;
		return -1;
        }
        iofile.seekp(blocksize * blocknumber);
        for(int i=0; i < blocksize; i++) {
                iofile.put(buffer[i]);
        }
	return 1;
}
int Sdisk::getnumberofblocks() {
	//return the number of blocks
	return numberofblocks;
}
int Sdisk::getblocksize() {
	//return the block size
	return blocksize;
}

