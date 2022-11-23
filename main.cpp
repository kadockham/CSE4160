/*
 * Name:        Kenneth Dockham
 * Filename:    main.cpp
 * Description: This file is the file used to test the classes of the project and demonstrait that they function.
 */

#include "sdisk.h"
#include "filesys.h"
#include "shell.h"
#include "table.h"
#include "block.h"
#include <iostream>

using namespace std;

int main()
{
  Shell s1("disk1", 256, 128);
  string s;
  string command="go";
  string op1,op2;

  while (command != "quit")
      {
        command.clear();
        op1.clear();
        op2.clear();
        cout << "$";
        getline(cin,s);
        int firstblank=s.find(' ');
        if (firstblank < s.length()) s[firstblank]='#';
        int secondblank=s.find(' ');
        command=s.substr(0,firstblank);
        if (firstblank < s.length())
          op1=s.substr(firstblank+1,secondblank-firstblank-1);
        if (secondblank < s.length())
          op2=s.substr(secondblank+1);
        if (command=="dir")
          {
            s1.dir();
          }
        if (command=="add")
          {
            s1.add(op1, op2);
          }
        if (command=="del")
          {
            s1.del(op1);
          }
        if (command=="type")
          {
            s1.type(op1);
          }
        if (command=="copy")
          {
            s1.copy(op1,op2);
          }
      }

  return 0;
};
  /*
  Sdisk disk1("disk1",256,128);
  Filesys fsys("disk1",256,128);
  fsys.newfile("file1");
  fsys.newfile("file2");

  string bfile1;
  string bfile2;

  for (int i=1; i<=1000; i++)
      {
        bfile1+="1";
      }
  vector<string> blocks=block(bfile1,128); 

  int blocknumber=0;

  for (int i=0; i< blocks.size(); i++)
      {
        blocknumber=fsys.addblock("file1",blocks[i]);
      }

  fsys.delblock("file1",fsys.getfirstblock("file1"));

  for (int i=1; i<=2048; i++)
      {
        bfile2+="2";
      }

  blocks=block(bfile2,128); 

  for (int i=0; i< blocks.size(); i++)
      {
        blocknumber=fsys.addblock("file2",blocks[i]);
      }

  fsys.delblock("file2",blocknumber); 
  */
 //
 //This main program inputs commands to the shell.
 //It inputs commands as : command op1 op2
 //You should modify it to work for your implementation.
 //
