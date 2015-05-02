#ifndef EXECUTIVE_H
#define EXECUTIVE_H

// File- Executive.h                                                 //
// Ver 1.0                                                       //
// Application: CSE687 Pr#2, Spring 2015                         //
// Platform:    Dell XPS 2720, Win 8.1 Pro, Visual Studio 2013   //
// Author:      Dontireddy sneha reddy, computer engineering,    //
//              Syrracuse University, email-sdontire@syr.edu     //
///////////////////////////////////////////////////////////////////
/*
* Package Operations:
*----------------------
* Executive packages initiates all the packages in the project.
* Executive package recieves input from the commandline and parse the
* input. Executive package is responsible for demonstrating the requirements
* of the project.
*
* Public Interface:
* =================
* XmlWriterfile- Writes to the xml file given as input.
* openfile - Opens the file for reading and writing
* main- Recieves input from the commandline and parse the input
* and also reponsible for demonstrating the requirements of the project
*
*
* Required Files:
* ---------------
*   - Executive.h, Executive.cpp, FileSystem.h, FileSystem.cpp, Tokenizer.h, Tokenizer.cpp,
*     XmlReader.h, XmlReader.cpp,XmlWriter.h, XmlWriter.cpp
*     XmlDocument.h, XmlDocument.cpp, Display.h, Display.cpp, MNode.h, MNode.cpp,
*     MTree.h, MTree.cpp, Utilities.h, Utilities.cpp,XmlElement.h, XmlElement.cpp
*
* Build Process:
* --------------
*   devenv AST.sln /debug rebuild
*
* Maintenance History:
* --------------------
* ver 1.0
* - created executive file
*/
#pragma once
#include <string>
#include <iostream>
#include <string>
#include <fstream>
#include <stack>
#include <queue>
#include "../XmlTokenizer/Tokenizer.h"
#include "../Mtree/MTree.h"
#include "../XmlReader/XmlReader.h"
#include "../XmlWriter/XmlWriter.h"
#include "../XmlDocument/XmlDocument.h"
using namespace std;
using namespace MTreeLib;
using namespace XmlProcessing;

class Executive
{
public:
	Executive(){};
	~Executive(){};
	using MNodeStr = MNode < std::string >;
	using sPtr = std::shared_ptr < MNodeStr >;
	using Children = std::vector < sPtr >;
	
	string openFile(string filename);
	void XmlWriterfile(string filepath, sPtr pNode, bool empty);
	void demonstrateReqsThreetoNine(XmlDocument *xmldoc, string filevalue, sPtr pNode);
	void demonstrateReqsEighttoEnd(XmlDocument *xmldoc, string filevalue, sPtr pNode);
};
#endif
