#ifndef XMLDOCUMENT_H
#define XMLDOCUMENT_H
// XmlDocument.h- Ver 1.2                                      //
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
* PUBLIC INTERFACE
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

#include <memory>
#include <string>
#include "../XmlElement/XmlElement.h"
#include <string>
#include <stack>
#include "../XmlReader/XmlReader.h"
#include "../Mtree/MTree.h"
#include "../Display/Display.h"
using namespace MTreeLib;
using namespace std;

//using sPtr1 = std::shared_ptr < AbstractXmlElement >;
namespace XmlProcessing
{
  class XmlDocument
  {
  public:
  
	  using MNodeStr = MNode < std::string >;
	  using sPtr = std::shared_ptr < MNodeStr >;
	  using Children = std::vector < sPtr >;
    enum sourceType { string, filename };

    XmlDocument(std::string src);
	void addChilds(XmlReader *xmlrd, sPtr &pNode, bool &firstnode, std::stack<std::string> &stk, std::vector<std::string> &vec);
	sPtr recurFunc(sPtr root, std::string target);   
	sPtr parseTree(std::string filevalue1);
	sPtr findElementById(std::string id, sPtr pNode);
	std::vector<sPtr> findElementByTag(std::string tag, sPtr pNode);
	bool deleteNodeUsingId(sPtr &root, std::string node);
	std::vector<std::pair<std::string, std::string>> findAttributes(sPtr root, sPtr target);
	std::vector<sPtr> findChildren(sPtr root, sPtr target);
	bool removeAttribute(sPtr root, sPtr target);
	sPtr fetchElementForId(sPtr root);
	sPtr fetchAttributeElement(sPtr root);
	std::pair<std::string, std::string> fetchAttribute(sPtr root);
	bool addAttribute(sPtr root, sPtr target, std::pair<std::string, std::string> attr);
	void Testfindbyid(sPtr pNode);
	void TestfindByTag(sPtr pNode);
	sPtr updateElements(sPtr &root, sPtr target);
	bool Testaddchild(sPtr pNode);
	sPtr fetchElementForIdUsingTag(sPtr root);
	bool TestaddchildUsingTag(sPtr pNode);
	sPtr removeChildUsingId(sPtr pNode);
	sPtr removeChildUsingTag(sPtr pNode);
	std::vector<std::pair<std::string, std::string>> retrieveAttributes(sPtr pNode);
	std::vector<sPtr> retrieveChildren(sPtr pNode);
	void addAttribute1(sPtr pNode);
	void removeAttribute1(sPtr pNode);
	bool deleteNode(sPtr &root, std::string node);
	stack<sPtr> returnStack(sPtr root);
	// queries return XmlDocument references so they can be chained, e.g., doc.element("foobar").descendents();
    XmlDocument& element(const std::string& tag);           // found_[0] contains first element (DFS order) with tag
    XmlDocument& elements(const std::string& tag);          // found_ contains all elements with tag
    XmlDocument& children(const std::string& tag = "");     // found_ contains sPtrs to children of prior found_[0] 
    XmlDocument& descendents(const std::string& tag = "");  // found_ contains sPtrs to descendents of prior found_[0]
    std::vector<sPtr>& select();                            // return reference to found_.  Use std::move(found_) to clear found_

  private:
    //sPtr1 pDocElement_;         // AST that holds procInstr, comments, XML root, and more comments
    std::vector<sPtr> found_;  // query results
  };
}
#endif
