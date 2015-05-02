
// File - Display.cpp                                            //
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
* Public Interface:
* =================
* treeDisplay- This function displays xml tree
* childaddResult- This display the result of child added to node using id.
* childaddtagResult- This displays the result of child added to node using tag.
* childremoveidResult- This displays the result of child removal form node using id.
* elementfoundbyId- This displays the element found by id.
* elementfoundbyTag- This displays the element found by tag.
* printremoveattr- Prints removed attributes 
* printremoveelement- Prints element from which attributes are removed
* printattributes - Prints attributes
* printattributeEle - Prints element for specified attributes
* printChildren- Prints children of the element
* printChildElement- Prints element
* printElement - Prints Element
* retrieveAttributes- prints attributes 
* childremoveidResult- prints results of child removal
* 
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
#include "Display.h"

void Display::treeDisplay(sPtr pNode, size_t levelCount)
{
	std::string spacer(levelCount, ' ');
	levelCount += 2;
	std::cout << "\n  " << spacer <<pNode->value()<<" ";
	std::vector<std::pair<std::string, std::string>> vec = pNode->getAttributes();
	for (size_t i = 0; i < vec.size(); i++)
		std::cout << vec[i].first<<"="<<"\""<<vec[i].second<<"\"";
	for (auto pChild : *pNode)
		treeDisplay(pChild, levelCount);
	levelCount -= 2;
}
void Display::elementfoundbyId(sPtr element, std::string id)
{
	if (element == NULL || id.empty())
	{
		cout << "\nNo Element is found which has attributes \n";
	}
	else
	{
		for (size_t i = 0; i < element->getAttributes().size(); i++)
		{
			cout << "\n" << "Element found by Id:" << id << " is:" << element->value() << "\n";
		}
	}
}
void Display::elementfoundbyTag(std::vector<sPtr> elements, std::string tag)
{
	cout << "\n Number of Elements found with tag : " + tag + " are:" << elements.size() << "\n";
}

void Display::childaddResult(bool result)
{
	if (result == true)
		std::cout << " \n child <Project2> added successfully using id \n";
	else
		std::cout << "\n No id found for child addition \n";
}
void Display::childaddtagResult(bool result)
{
	if (result == true)
		std::cout << "\n child <Project1> added successfully using tag\n";
	else
		std::cout << "\n No Tag found for child addition \n";
}
void Display::childremoveidResult(sPtr result)
{
	if (result == NULL)
		std::cout << "\n No id found";
	else
		std::cout << "\n Element " << result->value() << " deleted using id:";
}
void Display::retrieveAttributes(std::vector<std::pair<std::string, std::string>> resultvec)
{
	for (size_t i = 0; i < resultvec.size(); i++)
	{
		cout << resultvec[i].first << "=\"" << resultvec[i].second << "\""<<"\n";
	}
}
void Display::printElement(sPtr element)
{
	if (element != NULL)
		cout << "\nAttributes of " << element->value() << "are :" << " \n";
	else
		cout << " \n No element with attribute \n";
}
void Display::printChildElement(sPtr element)
{
	cout << "\n Childern of " << element->value() << "are :" << "\n";
}
void Display::printChildren(vector<sPtr> resultvec)
{
	for (size_t i = 0; i < resultvec.size(); i++)
	{
		cout << resultvec[i]->value() << "\n";
	}
}
void Display::printattributeEle(sPtr element)
{
	cout << " added to " << element->value() <<"\n";
}
void Display::printattributes(std::pair<std::string, std::string> vec)
{
		cout << "\n Attributes: "<<vec.first << "=\"" << vec.second << "\"" << "\n";
}
void Display::printremoveelement(sPtr element)
{
	if (element != NULL)
		cout << "from element " << element->value() << "\n";
	else
		cout << "\n No element with attribute found \n";

}
void Display::printremoveattr(std::pair<std::string, std::string> vec)
{
	cout << " \n Attributes: " << vec.first << "=\"" << vec.second << "\"" <<" are deleted";
}

#ifdef DISPLAY
int main()
{
	std::string Prologue = "<?xml version=\"1.0\"?><!-- top level comment -->";
	std::string test1 = Prologue;
	test1 += "<parent att1='val1' att2='val2'><child1 /><child2>child2 body<child1 /></child2></parent>";
	std::string test2 = Prologue;
	test2 += "<Dir><path>/TestFile/Dir1</path><File date='notCurrent'><name type='file'>text1.txt</name><date>02/11/2012</date></File></Dir>";
	XmlDocument *xmldoc = new XmlDocument(filevalue);

	pNode=xmldoc->parseTree(filevalue);
	treeDisplay(pNode,0);

	std::string id=val1;
	elementfoundbyId(pNode,id);

	std::vector<sPtr> vec;
	vec.push(pNode)

	elementfoundbyTag(vec[0], parent);
	childaddResult(true);

	childaddtagResult(true);
	childremoveidResult(pNode);

	std::pair<std::string, std::string> attr;
	attr.first = "sneha";
	attr.second = "best";
	resultvec.push_back(attr);
	std::vector<std::pair<std::string, std::string>> resultvec;
	retrieveAttributes(resultvec);

	printElement(pNode);

	printChildElement(pNode);
	std::vector<sPtr> vec;
	vec.push_back(pNode);
	printChildren(vector<sPtr> vec);

	printattributeEle(pNode);
	printattributes(resultvec);

	printremoveelement(pNode);
	printremoveattr(resultvec);

	return 0;

}

#endif 


