#ifndef DISPLAY_H
#define DISPLAY_H

// File- Display.h                                               //
// Ver 1.0                                                       //
// Application: CSE687 Pr#2, Spring 2015                         //
// Platform:    Dell XPS 2720, Win 8.1 Pro, Visual Studio 2013   //
// Author:      Dontireddy sneha reddy, computer engineering,    //
//              Syrracuse University, email-sdontire@syr.edu     //
///////////////////////////////////////////////////////////////////
/*
* Package Operations:
*----------------------
* Display package is responsible for displaying outpt to the console.
* Requirements are displayed to console using display package.
*
* Public interface
*----------------------------
* treeDisplay- This function displays xml tree 
* childaddResult- This display the result of child added to node using id.
* childaddtagResult- This displays the result of child added to node using tag.
* childrenidResult- This displays the result of child removal form node using id.
* elementfoundbyId- This displays the element found by id.
* elementfoundbyTag- This displays the element found by tag.
*
*
* Required Files:
* ---------------
*   - Display.h, Display.cpp, MNode.h, MNode.cpp,
*     MTree.h, MTree.cpp, Utilities.h, Utilities.cpp.
*
* Build Process:
* --------------
*   devenv XmlDocument.sln /debug rebuild
*
* Maintenance History:
* --------------------
* ver 1.0
* - created Display file
*/
#pragma once
#include <iostream>
#include <string>
#include <stack>
#include "../Mtree/MTree.h"

using namespace MTreeLib;
using namespace std;

using MNodeStr = MNode < std::string >;
using sPtr = std::shared_ptr < MNodeStr >;
using Children = std::vector < sPtr >;


class Display
{
public:
	Display(){};
	~Display(){};
	void treeDisplay(sPtr pNode, size_t levelCount);
	void childaddResult(bool result);
	void childaddtagResult(bool result);
	void childremoveidResult(sPtr result);
	void elementfoundbyId(sPtr element, std::string id);
	void elementfoundbyTag(std::vector<sPtr> element, std::string tag);
	void retrieveAttributes(std::vector<std::pair<std::string, std::string>> resultvec);
	void printElement(sPtr element);
	void printChildren(vector<sPtr> resultvec);
	void printChildElement(sPtr element);
	void printattributeEle(sPtr element);
	void printattributes(std::pair<std::string, std::string> vec);
	void Display::printremoveelement(sPtr element);
	void Display::printremoveattr(std::pair<std::string, std::string> vec);
};

#endif