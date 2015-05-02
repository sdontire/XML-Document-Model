// XmlDocument.cpp- Ver 1.2                                      //
// Application: CSE687 Pr#2, Spring 2015                         //
// Platform:    Dell XPS 2720, Win 8.1 Pro, Visual Studio 2013   //
// Author:      Dontireddy sneha reddy, computer engineering,    //
//              Syrracuse University, email-sdontire@syr.edu     //
///////////////////////////////////////////////////////////////////
/*
* Package Operations:
* -------------------
* This package uses C++11 constructs, most noteably std::shared_ptr. 
* The XML Document Model is essentially
* a program-friendly wrapper around an Abstract Syntax Tree (AST) used to
* contain the results of parsing XML markup.
* 
* This package also contains code to demonstrate the requirements of the project.
* Requirements demonstrated are: Adding child using Id and Adding child using tag.
* Removing child using Id and Tag. Finding element using id and tag.  Returning 
* attribute name-value pair of given element. Returning children for specified 
* element. Writing root to a empty file. Add and remove attribute for specified 
* element.
*PUBLIC INTERFACE
* ---------------------------
* recurFunc- function for searching a node in tree
* findElementById- function to find element by id
* findElementByTag- function for deleting a node in tree using tag
* deleteNode- function for deleting a node in tree using tag
* findAttributes- return attributes of a particular node
* TestfindByTag- for demonstarting element found by id
* updateElements- For updating changes in the file
* Testaddchild- Demonstarting child addition
* removeChildUsingId - remove child using id
* retrieveChildren- for retrieving children
* parseTree- For constructing parse tree
* deleteNode- for deleting Node form tree
* addChilds -  for parsing tree  
* deleteNodeUsingId- Delete node using Id
* findChildren- For finding children of a node
* removeAttribute- For removing attribute
* fetchElementForId- For fetching element using id
* fetchAttributeElement- For fetching attribute using tag
* fetchElementForIdUsingTag- For fetching attribute using tag
* TestaddchildUsingTag- For adding children using id
* removeChildUsingId-  for removing children using id
*
*
*
*
* Abstract Syntax Trees, defined in this package, are unordered trees with
* two types of nodes:
*   Terminal nodes     - nodes with no children
*   Non-Terminal nodes - nodes which may have a finite number of children
* They are often used to contain the results of parsing some language.
*
* The elements defined in the companion package, XmlElement, will be used in
* the AST defined in this package.  They are:
*   AbstractXmlElement - base for all the XML Element types
*   DocElement         - XML element with children designed to hold prologue, Xml root, and epilogue
*   TaggedElement      - XML element with tag, attributes, child elements
*   TextElement        - XML element with only text, no markup
*   CommentElement     - XML element with comment markup and text
*   ProcInstrElement   - XML element with markup and attributes but no children
*   XmlDeclarElement   - XML declaration element with attributes
* 
*
* Required Files:
* ---------------
*   - XmlDocument.h, XmlDocument.cpp, Display.h, Display.cpp, MNode.h, MNode.cpp,
*     MTree.h, MTree.cpp, Utilities.h, Utilities.cpp,XmlElement.h, XmlElement.cpp
*
* Build Process:
* --------------
*   devenv XmlDocument.sln /debug rebuild
*
* Maintenance History:
* --------------------
* ver 1.3 : 24 March 15
* -added functionalities
* ver 1.2 : 21 Feb 15
* - modified these comments
* ver 1.1 : 14 Feb 15
* - minor changes to comments, method arguments
* Ver 1.0 : 11 Feb 15
* - first release
*/

#include <iostream>
#include <string>
#include <stack>
#include "../XmlReader/XmlReader.h"
#include "../Mtree/MTree.h"
#include "../Display/Display.h"
#include "XmlDocument.h"
using namespace MTreeLib;
using namespace std;
using namespace XmlProcessing;

// function for searching a node in tree
sPtr XmlDocument::recurFunc(sPtr root, std::string target)
{
	stack<sPtr> stk1;
	stk1.push(root);
	while (!stk1.empty()) {
		sPtr top = stk1.top();
		stk1.pop();
		for (sPtr child : top->nodeChildren()) {
			stk1.push(child);
		}
		if (top->value() == target)
			return top;
	}

	return NULL;
}
XmlProcessing::XmlDocument::XmlDocument(std::string filevalue1)
{
	
}

//function to find element by id
sPtr XmlDocument::findElementById(std::string id, sPtr pNode)
{
	stack<sPtr> stk1;
	stk1.push(pNode);

	while (!stk1.empty()) {
		sPtr top = stk1.top();
		stk1.pop();
		for (sPtr child : top->nodeChildren()) {
			stk1.push(child);
		}
		for (std::pair<std::string, std::string> att : top->getAttributes())
		{
			if (att.second == id)
				return top;
		}


	}
	return NULL;
}

//function for finding tag
std::vector<sPtr> XmlDocument::findElementByTag(std::string tag, sPtr pNode)
{
	stack<sPtr> stk1;
	stk1.push(pNode);
	std::vector<sPtr> tagvec;

	while (!stk1.empty()) {
		sPtr top = stk1.top();
		stk1.pop();
		for (sPtr child : top->nodeChildren()) {
			stk1.push(child);
		}
		if (top->value() == tag)
			tagvec.push_back(top);
	}
	return tagvec;
}
// function for deleting a node in tree using tag
bool XmlDocument::deleteNode(sPtr &root, std::string node)
{
	stack<sPtr> stk1;
	stk1.push(root);

	while (!stk1.empty()) {
		sPtr &top = stk1.top();

		for (size_t i = 0; i < top->nodeChildren().size(); i++)
		{
			if (node == top->nodeChildren().at(i)->value())
			{

				std::vector<sPtr> myvector1;
				myvector1 = top->nodeChildren();
				myvector1.erase(myvector1.begin() + i);
				top->nodeChildren() = myvector1;
				top->setNodeChildren(myvector1);
				return true;
			}
		}
		stk1.pop();
		for (sPtr child : top->nodeChildren()) {
			stk1.push(child);
		}

	}
	return false;
}

//function to delete a node using id
bool XmlDocument::deleteNodeUsingId(sPtr &root, std::string node)
{
	stack<sPtr> stk1;
	stk1.push(root);

	while (!stk1.empty()) {
		sPtr &top = stk1.top();
		for (size_t i = 0; i < top->nodeChildren().size(); i++)
		{
			for (size_t j = 0; j < top->nodeChildren().at(i)->getAttributes().size(); j++)
			{
				if (node == top->nodeChildren().at(i)->getAttributes().at(j).second)
				{

					std::vector<sPtr> myvector1;
					myvector1 = top->nodeChildren();
					myvector1.erase(myvector1.begin() + i);
					top->nodeChildren() = myvector1;
					top->setNodeChildren(myvector1);
					return true;
				}
			}

		}

		stk1.pop();
		for (sPtr child : top->nodeChildren()) {
			stk1.push(child);
		}

	}
	return false;
}


//return attributes of a particular node
std::vector<std::pair<std::string, std::string>> XmlDocument::findAttributes(sPtr root, sPtr target)
{
	stack<sPtr> stk1;
	stk1.push(root);

	while (!stk1.empty()) {
		sPtr top = stk1.top();
		stk1.pop();
		for (sPtr child : top->nodeChildren()) {
			stk1.push(child);
		}
		if (top == target)
			return top->getAttributes();
	}
	std::vector<std::pair<std::string, std::string>> vec;
	return vec;
}

//return children of a particular node
std::vector<sPtr> XmlDocument::findChildren(sPtr root, sPtr target)
{
	stack<sPtr> stk1;
	stk1.push(root);

	while (!stk1.empty()) {
		sPtr top = stk1.top();
		stk1.pop();
		for (sPtr child : top->nodeChildren()) {
			stk1.push(child);
		}
		if (top == target)
			return top->nodeChildren();
	}
	std::vector<sPtr> vec;
	return vec;
}

//remove attribute from a node
bool XmlDocument::removeAttribute(sPtr root, sPtr target)
{
	stack<sPtr> stk1;
	stk1.push(root);

	while (!stk1.empty()) {
		sPtr &top = stk1.top();
		stk1.pop();
		if (top == target)
		{
			std::vector<std::pair<std::string, std::string>> vec = top->getAttributes();
			Display *disp = new Display();
			disp->printremoveattr(vec[0]);
			vec.erase(vec.begin() + 0);
			top->setAttributes(vec);
			return true;
		}
		for (sPtr child : top->nodeChildren()) {
			stk1.push(child);
		}

	}
	return false;
}



//To fetch element which has id attribute for using in other functions
sPtr XmlDocument::fetchElementForId(sPtr root)
{
	stack<sPtr> stk1;
	stk1.push(root);

	while (!stk1.empty()) {
		sPtr top = stk1.top();
		stk1.pop();
		std::vector<std::pair<std::string, std::string>> vec = top->getAttributes();
		if (vec.size()>0)
		{
			return top;
		}

		for (sPtr child : top->nodeChildren()) {
			stk1.push(child);
		}

	}
	return NULL;
}


//To fetch element for using in other functions
sPtr XmlDocument::fetchAttributeElement(sPtr root)
{
	stack<sPtr> stk1;
	stk1.push(root);

	while (!stk1.empty()) {
		sPtr top = stk1.top();
		stk1.pop();
		if (top->getAttributes().size() >= 1 && top->value() != "document" && top->value() != "Comment" && top->value() != "Declaration")
		{
			return top;
		}
		for (sPtr child : top->nodeChildren()) {
			stk1.push(child);
		}

	}
	return NULL;
}

//To fetch an attribute for using in addAttribute func
std::pair<std::string, std::string> XmlDocument::fetchAttribute(sPtr root)
{
	stack<sPtr> stk1;
	stk1.push(root);

	while (!stk1.empty()) {
		sPtr top = stk1.top();
		stk1.pop();
		if (top->getAttributes().size() >= 1)
		{
			return top->getAttributes().at(0);
		}
		for (sPtr child : top->nodeChildren()) {
			stk1.push(child);
		}

	}
	std::pair<std::string, std::string> vec;
	return vec;
}

//add attribute to a node
bool XmlDocument::addAttribute(sPtr root, sPtr target, std::pair<std::string, std::string> attr)
{
	stack<sPtr> stk1;
	stk1.push(root);

	while (!stk1.empty()) {
		sPtr &top = stk1.top();
		stk1.pop();
		if (top == target)
		{
			std::vector<std::pair<std::string, std::string>> vec = top->getAttributes();
			vec.push_back(attr);
			top->setAttributes(vec);
			Display *disp = new Display();
			disp->printattributes(attr);
			disp->printattributeEle(top);
			return true;
		}
		for (sPtr child : top->nodeChildren()) {
			stk1.push(child);
		}

	}
	return false;
}


//function for opening given file

void XmlDocument::Testfindbyid(sPtr pNode)
{
	// Demonstrating finding element by id
	sPtr target = fetchElementForId(pNode);
	std::string id;
	sPtr element;
	if (target != NULL)
	{
		id= target->getAttributes().at(0).second; //finding random id
		element = findElementById(id, pNode); // finding element with specified id
	}
	Display *disp = new Display();
	disp->elementfoundbyId(element, id);
}
// for demonstarting element found by id
void XmlDocument::TestfindByTag(sPtr pNode)
{
	std::vector<sPtr> taggedElements;
	std::string tag;
	//Demonstrating finding element by tag
	vector<sPtr> vecchild = pNode->nodeChildren();

	tag = vecchild[vecchild.size() - 1]->value();


	taggedElements = findElementByTag(tag, pNode);
	Display *disp = new Display();
	disp->elementfoundbyTag(taggedElements, tag);


}

stack<sPtr> XmlDocument::returnStack(sPtr root)
{
	stack<sPtr> stk1, stk2;
	stk1.push(root);
	stk2.push(root);
	while (!stk1.empty()) {
		sPtr &top = stk1.top();
		stk1.pop();
		for (sPtr child : top->nodeChildren()) {
			stk1.push(child);
			stk2.push(child);
		}

		
	}
	return stk2;
}
// for updating the changes in the file
sPtr XmlDocument::updateElements(sPtr &root, sPtr target)
{
	stack<sPtr> stk2 = returnStack(root);
	while (stk2.size() != 0)
	{
		sPtr &top1 = stk2.top();
		stk2.pop();
		vector<sPtr>vecchidren1 = root->nodeChildren();
		vector<sPtr> vecchildren = top1->nodeChildren();
		std::string ele = "";
		if (vecchildren.size() >= 1)
		{
			if (top1->value() != "document" && top1->value() != "Comment" && top1->value() != "Declaration" &&  top1->value()!=vecchidren1[vecchidren1.size()-1]->value())
				ele += "<" + top1->value();
			std::vector<std::pair<std::string, std::string>> attvec = top1->getAttributes();
			if (attvec.size() > 0)
			{
				for each(std::pair<std::string, std::string> att in attvec)
					ele += " " + att.first + "=\"" + att.second + "\"";
			}
			if (top1->value() != "document" && top1->value() != "Comment" && top1->value() != "Declaration" &&  top1->value() != vecchidren1[vecchidren1.size() - 1]->value())
				ele += ">";
			for (size_t i = 0; i < vecchildren.size(); i++)
			{
				ele += vecchildren.at(i)->getElement();
			}
			if (top1->value() != "document" && top1->value() != "Comment" && top1->value() != "Declaration" && top1->value() != vecchidren1[vecchidren1.size() - 1]->value())
				ele += "</" + top1->value() + ">";
			top1->setElement(ele);
		}

	}
	return root;
}
// Demonstarting child addition
bool XmlDocument::Testaddchild(sPtr pNode)
{
	sPtr element;
	std::vector<sPtr> tagvec;
	sPtr ele=fetchElementForId(pNode);
	if (ele != NULL)
	{
		std::string id1 = fetchElementForId(pNode)->getAttributes().at(0).second;
		std::string addc = "<Project2>XmlDocument</Project2>";
		XmlReader *xmlrd1 = new XmlReader(addc);
		element = findElementById(id1, pNode);
		element->addChild(xmlrd1->tag());

		int lastnode = element->nodeChildren().size() - 1;
		sPtr childnode = element->nodeChildren().at(lastnode);
		XmlReader::attribElems attribs = xmlrd1->attributes();
		childnode->setAttributes(attribs);
		childnode->setElement(xmlrd1->element());
		sPtr rtroot = updateElements(pNode, element);
		return true;
	}
	else
	{
		return false;
	}

}


sPtr XmlDocument::fetchElementForIdUsingTag(sPtr root)
{
	return root->nodeChildren().at(root->nodeChildren().size() - 1);

}

//Function to add a child to the specified tag
bool XmlDocument::TestaddchildUsingTag(sPtr pNode)
{
	std::vector<sPtr> tagvec;
	sPtr target = fetchElementForIdUsingTag(pNode);

	std::string addc = "<Project1>FileCataloger</Project1>";
	XmlReader *xmlrd1 = new XmlReader(addc);

	if (target != NULL)
	{
		target->addChild(xmlrd1->tag());

		int lastnode = target->nodeChildren().size() - 1;
		sPtr childnode = target->nodeChildren().at(lastnode);
		cout << xmlrd1->element();
		XmlReader::attribElems attribs = xmlrd1->attributes();
		childnode->setAttributes(attribs);
		childnode->setElement(xmlrd1->element());
		sPtr rtroot = updateElements(pNode, target);
		return true;
	}
	else
		return false;
}

//remove child using id

sPtr XmlDocument::removeChildUsingId(sPtr pNode)
{
	sPtr target = fetchElementForId(pNode);

	//Tree deletion
	if (target != NULL)
	{
		//string childrtag = "author";
		sPtr rttarget = target;
		deleteNodeUsingId(pNode, target->getAttributes().at(0).second);
		updateElements(pNode, target);
		return rttarget;
	}
	else
		return NULL;
}
sPtr XmlDocument::removeChildUsingTag(sPtr pNode)
{
	sPtr target = fetchElementForId(pNode);

	//Tree deletion
	if (target != NULL)
	{
		//string childrtag = "author";
		sPtr rttarget = target;
		deleteNode(pNode, target->value());
		updateElements(pNode, target);
		return rttarget;
	}
	else
		return NULL;
}
// for retrieving attributes
std::vector<std::pair<std::string,std::string>> XmlDocument::retrieveAttributes(sPtr pNode)
{
	sPtr attrnode = fetchAttributeElement(pNode);
	std::vector<std::pair<std::string, std::string>> attsvec;
	if (attrnode != NULL)
	{
		attsvec = findAttributes(pNode, attrnode);
	}
	Display *disp = new Display();
	disp->printElement(attrnode);
	return attsvec;
}
// for retreiving children
std::vector<sPtr> XmlDocument::retrieveChildren(sPtr pNode)
{
	sPtr attrnode1 = pNode->nodeChildren().at(pNode->nodeChildren().size() - 1);//findElementByTag("book", pNode).at(0);
	std::vector<sPtr> childvec = findChildren(pNode, attrnode1);
	Display *disp = new Display();
	disp->printChildElement(attrnode1);
	return childvec;
}
// for adding attributes
void XmlDocument::addAttribute1(sPtr pNode)
{
	sPtr attrnode = fetchElementForIdUsingTag(pNode);
	std::pair<std::string, std::string> attr;
	attr.first = "sneha";
	attr.second = "best";
	addAttribute(pNode, attrnode, attr);
	updateElements(pNode,pNode);
	Display *disp = new Display();
	disp->printattributeEle(attrnode);
	cout << "\n Tree Structure\n";
	cout << "----------------------------------\n";
	disp->treeDisplay(pNode, 0);
}

// for removing attribute
void XmlDocument::removeAttribute1(sPtr pNode)
{
	sPtr element=fetchAttributeElement(pNode);
	if (element != NULL)
	{
		removeAttribute(pNode, element);
		updateElements(pNode, pNode);
	}
	Display *disp = new Display();
	disp->printremoveelement(element);
	cout << "\n Tree Structure\n";
	cout << "----------------------------------\n";
	disp->treeDisplay(pNode, 0);
}

// for adding children
void XmlDocument::addChilds(XmlReader *xmlrd, sPtr &pNode, bool &firstnode, std::stack<std::string> &stk, std::vector<std::string> &vec)
{
	for (int i = vec.size() - 1; i >= 0; i--)
	{
		if (vec[vec.size() - 1].find(xmlrd->tag()) != string::npos)
		{
			if (vec[vec.size() - 1].find(xmlrd->body()) != string::npos)
			{
				sPtr targetptr = recurFunc(pNode, stk.top());
				if (stk.size() >= 1)
				{
					targetptr->addChild(xmlrd->tag());
					int lastnode = targetptr->nodeChildren().size() - 1;
					sPtr childnode = targetptr->nodeChildren().at(lastnode);
					childnode->setAttributes(xmlrd->attributes());
					childnode->setElement(xmlrd->element());
				}

				stk.push(xmlrd->tag());
				break;
			}
			else
			{
				stk.pop();
				vec.pop_back();
			}
		}
		else
		{
			stk.pop();
			vec.pop_back();
		}
	}
	if (xmlrd->tag() != "" && firstnode == false && xmlrd->tag() != "!--" && xmlrd->tag() != "?xml")
	{
		firstnode = true;
		pNode->addChild(xmlrd->tag());
		std::string value = xmlrd->element();
		int lastnode = pNode->nodeChildren().size() - 1;
		sPtr childnode = pNode->nodeChildren().at(lastnode);
		XmlReader::attribElems attribs = xmlrd->attributes();
		childnode->setAttributes(attribs);
		childnode->setElement(xmlrd->element());
		//childnode->setParent(pNode);
		stk.push(xmlrd->tag());
	}
}
//Parse tree construction
sPtr XmlDocument::parseTree(std::string filevalue1)
{
	std::string filevalue;
	filevalue = filevalue1;
	std::stack<std::string> stk;
	std::string ident;
	std::vector<std::string> vec;
	size_t position = 1;
	XmlReader *xmlrd = new XmlReader(filevalue);
	std::cout << "\n  testing next(), tag(), element(), body(), and attributes()";
	std::cout << "\n -----------------------------------------------------------";
	sPtr pNode(new MNodeStr("document"));
	bool firstnode = false;
	bool firstxml = false;
	while (xmlrd->next())
	{
		std::cout << "\n  tag:     " << xmlrd->tag().c_str();
		if (xmlrd->tag() == "?xml")
		{
			pNode->addChild("Declaration");
			continue;
		}
		if (xmlrd->tag().find("?xml") != string::npos)
		{
			continue;
		}
		if (xmlrd->tag().find("?") != string::npos)
		{
			continue;
		}

		std::cout << "\n  element: " << xmlrd->element().c_str();
		pNode->setAttributes(xmlrd->attributes());
		if (xmlrd->tag() == "!--")
		{
			pNode->addChild("Comment");
		}
		addChilds(xmlrd, pNode, firstnode, stk, vec);
		std::cout << "\n  body:    " << xmlrd->body().c_str();
		if (stk.size() != 0)
		{
			vec.push_back(xmlrd->body());
		}
		XmlReader::attribElems attribs = xmlrd->attributes();
		for (size_t i = 0; i < attribs.size(); ++i)
			std::cout << "\n  attributes: " << attribs[i].first.c_str() << ", " << attribs[i].second.c_str();
	}
	std::cout << "\n\n";
	Display *disp = new Display();
	cout << "\n Tree Structure\n";
	cout << "----------------------------------\n";
	disp->treeDisplay(pNode, 0);
	return pNode;
}

#ifdef XMLDOCUMENT
int main()
{
  //title("Testing XmlDocument class");
	sPtr pNode;
	std::string Prologue = "<?xml version=\"1.0\"?><!-- top level comment -->";
	std::string test1 = Prologue;
	test1 += "<parent att1='val1' att2='val2'><child1 /><child2>child2 body<child1 /></child2></parent>";
	std::string test2 = Prologue;
	test2 += "<Dir><path>/TestFile/Dir1</path><File date='notCurrent'><name type='file'>text1.txt</name><date>02/11/2012</date></File></Dir>";
	
	pNode=parseTree(test1);
	std::pair<std::string, std::string> testAttribute = fetchAttribute(pNode);
	Testfindbyid(pNode); 
	TestfindByTag(pNode);
	bool childadded = Testaddchild(pNode);
	bool childaddedbytag = TestaddchildUsingTag(pNode);
	sPtr Child = removeChildUsingId(pNode);

	removeChildUsingTag(pNode);
	retrieveAttributes(pNode);
	retrieveChildren(pNode);

	addAttribute1(pNode);
	removeAttribute1(sPtr pNode);
	XmlReader *xmlrd=new XmlReader;
	bool firstnode=true;
	std::stack<std::string> stk;
	std::vector<std::string> vec;
	addChilds(xmlrd, pNode,firstnode, stk,vec);


  std::cout << "\n\n";
}
#endif 