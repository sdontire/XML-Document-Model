// File- Executive.cpp                                                 //
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
* PUBLIC INTERFACE
* -----------------------
* XmlWriterfile- Writes to the xml file given as input.
* openfile - Opens the file for reading and writing
* main- Recieves input from the commandline and parse the input
* and also reponsible for demonstrating the requirements of the project
*
*
* Files required:
* =================
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

#include "Executive.h"
#include "../FileSystem/FileSystem.h"
#include "../XmlWriter/XmlWriter.h"
#include <Exception>

using namespace FileSystem;
void XmlWriterfile(string filepath, sPtr pNode, bool empty)
{
	//XML writer
	if (empty == true)
	{
		XmlWriter *xmlwr = new XmlWriter();
		std::ifstream myfile(filepath);
		std::ofstream ofs;
		ofs.open(filepath, std::ofstream::out | std::ofstream::trunc);
		std::vector<sPtr> elements = pNode->nodeChildren();
		xmlwr->addDeclaration();
		xmlwr->addComment("xml");
		vector<sPtr> vec = pNode->nodeChildren();
		xmlwr->element(vec[vec.size()-1]->value(), elements[elements.size()-1]->getElement()).xml();
		ofs << xmlwr->xml();
		ofs.close();
	}
}

string Executive::openFile(string filename)
{
	bool mvalue = false;
	std::ifstream myfile(filename);

	string filevalue = "";

	if (myfile.is_open())
	{
		std::string line;

		while (myfile.good())
		{
			while (!myfile.eof())
			{
				std::getline(myfile, line);
				filevalue += line;
			}
		}
	}
	else cout << "Unable to open file";
	return filevalue;
}

void demonstrateReqsThreetoNine(XmlDocument *xmldoc, string filevalue, sPtr pNode)
{
	try{
		cout << " \n REQUIREMENT 5 DEMONSTRATION\n ";
		cout << "*********************************************************************";
		//// Demonstrating finding element by id
		xmldoc->Testfindbyid(pNode);

		cout << " \n REQUIREMENT 6 DEMONSTRATION\n ";
		cout << "*********************************************************************";


		////Demonstrating finding element by tag
		xmldoc->TestfindByTag(pNode);
		//taggedElements=findElementByTag("book", pNode);

		cout << " \n REQUIREMENT 7a DEMONSTRATION\n ";
		cout << "*********************************************************************";
		//Demonstarting adding child to element found by id or tag
		Display *disp = new Display();
		bool childadded = xmldoc->Testaddchild(pNode);
		disp->childaddResult(childadded);
		cout << "\n Tree Structure\n";
		cout << "----------------------------------\n";
		disp->treeDisplay(pNode, 0);
		bool childaddedbytag = xmldoc->TestaddchildUsingTag(pNode);
		disp->childaddtagResult(childaddedbytag);
		cout << "\n Tree Structure\n";
		cout << "----------------------------------\n";
		disp->treeDisplay(pNode, 0);
		//Tree deletion
		cout << " \n REQUIREMENT 7b DEMONSTRATION\n ";
		cout << "*********************************************************************";
		sPtr removeChild = xmldoc->removeChildUsingId(pNode);
		disp->childremoveidResult(removeChild);
		cout << "\n Tree Structure\n";
		cout << "----------------------------------\n";
		disp->treeDisplay(pNode, 0);
	}
	catch (exception e)
	{
		cout << "error occured";
	}
}

void demonstrateReqsEighttoEnd(XmlDocument *xmldoc, string filevalue, sPtr pNode)
{
	try{
		Display *disp = new Display();
		xmldoc->removeChildUsingTag(pNode);
		cout << " \n REQUIREMENT 8a DEMONSTRATION\n ";
		cout << "*********************************************************************";
		//testing 8.a requirement to retrieve attributes of a node
		std::vector<std::pair<std::string, std::string>> resultvec;
		resultvec = xmldoc->retrieveAttributes(pNode);
		disp->retrieveAttributes(resultvec);

		cout << " \n REQUIREMENT 8b DEMONSTRATION\n ";
		cout << "*********************************************************************";
		//Testing 8.b to retrieve children of a node
		std::vector<sPtr> childresultvec = xmldoc->retrieveChildren(pNode);
		disp->printChildren(childresultvec);
		cout << " \n REQUIREMENT 9a DEMONSTRATION\n ";
		cout << "*********************************************************************";
		//Testing 9.a to add attribute for a node
		xmldoc->addAttribute1(pNode);
		cout << " \n REQUIREMENT 9b DEMONSTRATION\n ";
		cout << "*********************************************************************";
		//Testing 9.b to remove attribute for a node
		xmldoc->removeAttribute1(pNode);


		cout << " \nEND WITH DEMONSTRATION\n ";
		cout << "*********************************************************************";
	}
	catch (exception e)
	{
		cout << "error occured";
	}
}
	int main(int argc, char *argv[])
	{
		try{ string filepath, filename; // input file
			ifstream inputfile;
			sPtr element;
			string filevalue;
			if (argc > 1)
			{filepath = string(argv[1]);
				Executive *ex = new Executive();
				sPtr pNode;
				string tag;
				bool empty = true;
				//To read input file
				if (filepath.find("<") != std::string::npos)
				{filevalue = filepath; }
				else
				{ filepath = Path::getFullFileSpec(argv[1]);
					filevalue = ex->openFile(filepath);
					if (filevalue.empty())
					{ empty = false;
						XmlWriter *xmlwr1 = new XmlWriter();
						std::ifstream myfile(filepath);
						std::ofstream ofs;
						ofs.open(filepath, std::ofstream::out | std::ofstream::trunc);
						xmlwr1->addDeclaration();
						xmlwr1->addComment("Xml Test Case");
						xmlwr1->element("Catalog", "").xml();
						ofs << xmlwr1->xml();
						ofs.close();
						filevalue = ex->openFile(filepath);
	                 }
				}
				XmlDocument *xmldoc = new XmlDocument(filevalue);
				Display *disp = new Display();
				cout << " \n REQUIREMENT 3 DEMONSTRATION\n ";
				cout << "*********************************************************************";
				pNode = xmldoc->parseTree(filevalue);
				demonstrateReqsThreetoNine(xmldoc, filevalue, pNode);
				demonstrateReqsEighttoEnd(xmldoc, filevalue, pNode);
				XmlWriterfile(filepath, pNode, empty);
				getchar();
				return 0;
			}	else
				cout << "Please provide xml input";
			getchar();
			return 0;
		}catch (exception e){ cout << "\nError ocurred\n";  getchar(); }
	}
	