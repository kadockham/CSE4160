#include "table.h"
#include "block.h"
#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;

Table::Table(string diskname, int numberofblocks, int blocksize, string flatfile, string indexfile) : Filesys(diskname, numberofblocks, blocksize) {
    this -> flatfile = flatfile;
    this -> indexfile = indexfile;
}
int Table::buildTable(string inputfile) {
    if(newfile(flatfile) == -1 || newfile(indexfile) == -1) {
        cout << "Error: Database already exists on disk!" << endl;
        return 0;
    };
    ifstream infile;
    infile.open(inputfile.c_str());
    ostringstream outstream;
    string rec;
    getline(infile, rec);
    while(infile.good()) {
        string date = rec.substr(0,5);
        vector<string> blocks = block(rec, getblocksize());
        int b = addblock(flatfile, blocks[0]);
        outstream << date << " " << b << " ";
        getline(infile, rec);
    }
    outstream << "88888" << " " << 0;
    string buffer = outstream.str();
    vector<string> blocks = block(buffer, getblocksize());
    for(int i = 0; i < blocks.size(); i++) {
        addblock(indexfile, blocks[i]);
    }
    return 1;
}
int Table::search(string value) {
    //cout << "function called" << endl;
    int block = indexSearch(value);
    //cout << "block found" << endl;
    if(block == 0) {
        cout << "record not found" << endl;
        return 0;
    }
    else {
        string buffer;
        int error = readblock(flatfile, block, buffer);
        cout << buffer << endl;
        return 1;
    }
}
int Table::indexSearch(string value) {
    string buffer;
    int block = getfirstblock(indexfile);
    //cout << "frist block of index file" << block << endl;
    while(block != 0) {
        string b;
        int error = readblock(indexfile, block, b);
        buffer += b;
        block = nextblock(indexfile, block);
        //cout << block << " ";
    }
    //cout << "buffer full" << endl;
    istringstream instream;
    string s;
    int b;
    instream.str(buffer);
    instream >> s >> b;
    //cout << "I think we make it here" << endl;
    while(s != "88888") {
        if(s == value) {
            //cout << b << endl;
            return b;
        }
        //cout << s << " " << value;
        instream >> s >> b;
    }
    return 0;
}