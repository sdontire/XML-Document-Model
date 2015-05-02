
/////////////////////////////////////////////////////////////////
// MNode.cpp - Node helper for M-ary Tree data structure         //
//                                                             //
// Application: Help for CSE687 Pr#2, Spring 2015              //
// Platform:    Dell XPS 2720, Win 8.1 Pro, Visual Studio 2013 //
// Author:      Jim Fawcett, CST 4-187, 443-3948               //
//              jfawcett@twcny.rr.com                          //
/////////////////////////////////////////////////////////////////
/*
* Package Operations:
* -------------------
* This package contains the class MNode<T>, a helper for MTree<T>
* in the MTree package.  MTree<T> is an M-ary tree, e.g., each
* MNode<T> has zero or more children.  Note that this is not a
* balanced binary tree.  No order is imposed on the children of
* any node.  They simply appear in the order they were added.
*
* M-ary trees are often used to represent parse trees where the
* ordering of nodes depends on the structure of the entity being
* represented, e.g., source code, XML, or HTML.
*
* Each MNode<T> holds a vector of std::shared_prt's to it's children,
* if any.  The value of the template parameter T represents what
* each node of the tree holds, e.g., a string representing a
* grammatical construct, or XML or HTML elements.
*
* Required Files:
* ---------------
*   - MNode.h and MNode.cpp, Utilities.h, Utilities.cpp
*
* Build Process:
* --------------
*   devenv MTree.sln /debug rebuild
*
* Maintenance History:
* --------------------
* This is a complete redesign of an earlier MNode class that uses
* C++11 constructs, most noteably std::shared_ptr.
*
* Ver 3.0 : 04 Feb 15
* - first release of new design
* ver 2.3 : 05 Jan 13
* - last version of the old branch
*/


#include "MNode.h"

#ifdef TEST_MNODE

using namespace MTreeLib;
using MNodeStr = MNode < std::string >;
using sPtr = std::shared_ptr < MNodeStr >;

//----< test makeNode >------------------------------------------------------

std::shared_ptr<MNode<std::string>> test_makeNode()
{
	title("creating std::shared_ptr<MNode<T>> to new node");
	sPtr pRoot = makeNode<std::string>("root");
	pRoot->value() = "root";
	pRoot->addChild(makeNode<std::string>("child"));
	show(*pRoot);
	std::cout << "\n";
	std::cout << "\n  " << pRoot->value() << " has " << pRoot->size() << " elements";
	std::cout << "\n  the first child of " << pRoot->value() << " is " << (*pRoot)[0]->value();
	std::cout << "\n  size of " << (*pRoot)[0]->value() << " is: " << (*pRoot)[0]->size();
	std::cout << "\n";
	return pRoot;
}
//----< test: add child node >-----------------------------------------------

void test_addChild(sPtr pNode)
{
	title("adding child nodes");
	mtLog.start();
	pNode->addChild("first child");
	pNode->addChild("second child");
	pNode->addChild("third child");

	MNodeStr& node = *pNode;
	node[1]->addChild("second child's child");
	MNodeStr& secondChild = *node[1];
	secondChild[0]->addChild("second child's grandchild");
	node[2]->addChild("third's child");

	// Note that reference qualifiers for node and secondChild are necessary.
	// We don't want to add children to copies of the nodes.

	///////////////////////////////////////////////////////////////////////////
	// if these renaming operations get tedious you can use
	// nested indirections like this:
	//
	// (*pNode)[1]->addChild("second child's child");
	// (*(*pNode)[1])[0]->addChild("second child's grandchild");
	// (*pNode)[2]->addChild("third's child");

	mtLog.show();
	show(*pNode);
	std::cout << "\n";
}
//----< test: find by value >------------------------------------------------

std::shared_ptr<MNode<std::string>> test_findByValue(std::shared_ptr<MNode<std::string>> pNode)
{
	title("finding \"third child\" in node");
	std::vector<sPtr> found = pNode->findByValue("third child");
	if (found.size() > 0)
	{
		std::cout << "\n  found:";
		for (auto item : found)
			std::cout << "\n    " << item->value();
	}
	else
		std::cout << "\n  not found";
	std::cout << "\n";

	title("finding \"second child\" in Augmented");
	sPtr pAugmented = pNode->clone();
	pAugmented->addChild("second child");
	found = pAugmented->findByValue("second child");
	if (found.size() > 0)
	{
		std::cout << "\n  found:";
		for (auto item : found)
			std::cout << "\n    " << item->value();
	}
	else
		std::cout << "\n  not found";
	std::cout << "\n";

	title("finding \"no_such_value\" in Augmented");
	found = pAugmented->findByValue("no_such_value");
	if (found.size() > 0)
	{
		std::cout << "\n  found:";
		for (auto item : found)
			std::cout << "\n    " << item->value();
	}
	else
		std::cout << "\n  not found";
	std::cout << "\n";
	return pAugmented;
}
//----< test: find by id >---------------------------------------------------

void test_findById(std::shared_ptr<MNode<std::string>> pAugmented)
{
	title("finding \"grandChildId\" in Augmented");
	MNode<std::string>& Augmented = *pAugmented;
	sPtr pSecondChild = Augmented[1];
	MNode<std::string>& SecondChild = *pSecondChild;
	sPtr pGrandChild = SecondChild[0];
	pGrandChild->id() = "grandChildId";
	sPtr pId = pAugmented->findById("grandChildId");
	if (pId != nullptr)
	{
		std::cout << "\n  found:";
		std::cout << "\n    id = " << pId->id();
		std::cout << "\n    value = " << pId->value();
	}
	else
		std::cout << "\n    not found";
	std::cout << "\n";

	title("finding \"no_such_id\" in Augmented");
	pId = pAugmented->findById("no_such_id");
	if (pId != nullptr)
	{
		std::cout << "\n  found:";
		std::cout << "\n    id = " << pId->id();
		std::cout << "\n    value = " << pId->value();
	}
	else
		std::cout << "\n    not found";
	std::cout << "\n";
}
//----< test: Depth First Search with functor >------------------------------

void test_DFS(std::shared_ptr<MNode<std::string>> pNode)
{
	title("testing DFS with functional");

	// making lambda that displays node values

	std::function<void(const MNodeStr&)> f =
		[](const MNodeStr& node){ std::cout << "\n  " << node.value(); };

	// using in depth first search to show the tree rooted at pNode

	DFS<std::string>(*pNode, f);
	std::cout << "\n";
}
//----< test: node clone >---------------------------------------------------

void test_clones(std::shared_ptr<MNode<std::string>> pNode)
{
	title("making clone of original node");

	sPtr pClone = pNode->clone();
	pClone->value() = std::string("clone of ") + pNode->value();
	std::cout << "\n  " << pClone->value() << " size = " << pClone->size();
	std::cout << "\n";

	title("show clone");
	show(*pClone);
	std::cout << "\n";
}
//----< test: copy construction >--------------------------------------------

MNode<std::string> test_copy(std::shared_ptr<MNode<std::string>> pNode)
{
	title("making copy of original node");
	MNodeStr copy = *pNode;
	copy.value() = std::string("copy of ") + pNode->value();
	show(copy);
	std::cout << "\n";

	title("changing first and third child values in copy");
	copy[0]->value() += " modified";
	copy[2]->value() += " modified";
	show(copy);
	std::cout << "\n";
	title("showing original did not change");
	show(*pNode);
	std::cout << "\n";
	return copy;
}
//----< test: move construction >--------------------------------------------

MNode<std::string> test_move(MNode<std::string>& node)
{
	title("testing move construction");
	MNode<std::string> moveTarget = std::move(node);
	moveTarget.value() = "moveTarget";
	show(moveTarget);
	std::cout << "\n";
	std::cout << "\n  value of move src = " << node.value();
	std::cout << "\n   size of move src = " << node.size();
	std::cout << "\n";
	return moveTarget;
}
//----< test: copy assignment >----------------------------------------------

void test_copyAssignment(MNode<std::string>& src)
{
	title("testing copy assignment");
	MNodeStr assignTarget;
	assignTarget = src;
	assignTarget.value() = "assignTarget";
	show(assignTarget);
	std::cout << "\n";
	show(src);
	std::cout << "\n";
}
//----< test: move assignment >----------------------------------------------

void test_moveAssignment(MNode<std::string>& src)
{
	title("testing move assignment");
	MNodeStr moveAssignTarget;
	moveAssignTarget = std::move(src);
	moveAssignTarget.value() = "moveAssignTarget";
	show(moveAssignTarget);
	std::cout << "\n";
	src.value() = "moveSource";
	show(src);
	std::cout << "\n";
}
//----< test: node constness >-----------------------------------------------

void test_constNode(std::shared_ptr<MNode<std::string>> pRoot)
{
	title("defining const node and attempting to change");
	const MNodeStr& rootRef = *pRoot;
	std::cout << "\n  value of const node is " << rootRef.value();
	std::cout << "\n  the first child of const rootRef is: " << rootRef[0]->value();
	std::cout << "\n  size of first child is: " << rootRef[0]->size();

	rootRef.value() += " - modified";  // this just writes to returned value - no effect on rootRef
	std::cout << "\n  const rootRef now is: " << rootRef.value();
	rootRef[0]->value() += " - modified"; // but this does modify child
	std::cout << "\n  the first child of const rootRef now is: " << rootRef[0]->value();
	std::cout << "\n";
}
//----< test driver >--------------------------------------------------------

int main()
{
	title("Testing class MNode<T>", '=');

	title("creating instance of node");
	sPtr pNode(new MNodeStr("original"));
	std::cout << "\n  " << pNode->value() << "\n";

	std::shared_ptr<MNode<std::string>> pRoot = test_makeNode();
	test_addChild(pNode);
	std::shared_ptr<MNode<std::string>> pAugmented = test_findByValue(pNode);
	test_findById(pAugmented);
	test_DFS(pNode);
	test_clones(pNode);
	MNode<std::string> copy = test_copy(pNode);
	MNode<std::string> moveTarget = test_move(copy);
	test_copyAssignment(moveTarget);
	test_moveAssignment(moveTarget);
	test_constNode(pRoot);

	title("showing log");
	mtLog.show();
	mtLog.clear();
	title("showing cleared log");
	mtLog.show();
	std::cout << "\n\n";
}

#endif
