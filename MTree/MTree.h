#pragma once
#ifndef MTREE_H
#define MTREE_H
/////////////////////////////////////////////////////////////////
// MTree.h - M-ary Tree data structure                         //
//                                                             //
// Application: Help for CSE687 Pr#2, Spring 2015              //
// Platform:    Dell XPS 2720, Win 8.1 Pro, Visual Studio 2013 //
// Author:      Jim Fawcett, CST 4-187, 443-3948               //
//              jfawcett@twcny.rr.com                          //
/////////////////////////////////////////////////////////////////
/*
* Package Operations:
* -------------------
* This package contains the class MTree<T>.  MTree<T> is an
* M-ary tree, e.g., each MNode<T> has zero or more children.
* Note that this is not a balanced binary tree.  No order is
* imposed on the children of any node.  They simply appear
* in the order they were added.
*
* M-ary trees are often used to represent parse trees where
* ordering of nodes depends on the structure of the entity
* being represented, e.g., source code, XML, or HTML.
*
* MTree<T>'s nodes are members of class MNode<T>.  each MNode<T>
* holds a vector of std::shared_prt's to it's children, if any.
* the value of the template parameter T represents what each node
* of the tree holds, e.g., a string representing a grammatical
* constructor, or XML or HTML element.
*
* Required Files:
* ---------------
*   - MTree.h, MTree.cpp, MNode.h, MNode.cpp,
*     Utilities.h, Utilities.cpp
*
* Build Process:
* --------------
*   devenv MTree.sln /debug rebuild
*
* Maintenance History:
* --------------------
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
//#include "../Utilities/Utilities.h"

namespace MTreeLib {

	/////////////////////////////////////////////////////////////////////////////
	// MTree<T> class

	template<typename T>
	class MTree
	{
	public:
		using sPtr = std::shared_ptr < MNode<T> >;

		MTree(sPtr& pRoot);
		MTree(const T& t = T());
		MTree(const MTree<T>& tree);
		MTree(MTree<T>&& tree);
		~MTree();

		MTree<T>& operator=(const MTree<T>& tree);
		MTree<T>& operator=(MTree<T>&& tree);

		sPtr root();
		sPtr findById(const std::string& id);
		std::vector<sPtr> findByValue(const T& value);
		std::vector<sPtr> children(const T& value, size_t count = 1);
		std::vector<sPtr> descendents(const T& value, size_t count = 1);

	private:
		void decendentsHelper(sPtr ptr);
		sPtr pRoot_ = nullptr;
		std::vector<sPtr> collection_;
	};
	//----< construct tree from root node >--------------------------------------

	template<typename T>
	MTree<T>::MTree(sPtr& pRoot) : pRoot_(pRoot) {}

	//----< construct tree from value for new root node >------------------------

	template<typename T>
	MTree<T>::MTree(const T& t) : pRoot_(sPtr(new MNode<T>(t))) {}

	//----< destructor >---------------------------------------------------------

	template<typename T>
	MTree<T>::~MTree() {}

	//----< copy constructor >---------------------------------------------------

	template<typename T>
	MTree<T>::MTree(const MTree<T>& tree)
	{
		pRoot_ = tree.pRoot_->clone();
	}
	//----< move constructor >---------------------------------------------------

	template<typename T>
	MTree<T>::MTree(MTree<T>&& tree)
	{
		pRoot_ = tree.pRoot_;
		tree.pRoot_ = nullptr;
	}
	//----< copy assignment >----------------------------------------------------

	template<typename T>
	MTree<T>& MTree<T>::operator=(const MTree<T>& tree)
	{
		if (this == &tree) return *this;
		pRoot_ = tree.pRoot_->clone();
		return *this;
	}
	//----< move assignment >----------------------------------------------------

	template<typename T>
	MTree<T>& MTree<T>::operator=(MTree<T>&& tree)
	{
		if (this == &tree) return *this;
		pRoot_ = tree.pRoot_;
		tree.pRoot_ = nullptr;
		return *this;
	}
	//----< return tree root node >----------------------------------------------

	template<typename T>
	std::shared_ptr<MNode<T>> MTree<T>::root() { return pRoot_; }

	//----< find tree node by id >-----------------------------------------------

	template<typename T>
	std::shared_ptr<MNode<T>> MTree<T>::findById(const std::string& id)
	{
		if (pRoot_->id() == id)
			return pRoot_;
		return pRoot_->findById(id);
	}
	//----< find tree nodes by value >-------------------------------------------

	template<typename T>
	std::vector<std::shared_ptr<MNode<T>>> MTree<T>::findByValue(const T& value)
	{
		std::vector<sPtr> temp = pRoot_->findByValue(value);
		if (pRoot_->value() == value)
			temp.insert(begin(temp), pRoot_);
		return temp;
	}
	//----< find children of node with specified value >-------------------------

	template<typename T>
	std::vector<std::shared_ptr<MNode<T>>> MTree<T>::children(const T& value, size_t count = 1)
	{
		std::vector<std::shared_ptr<MNode<T>>> temp = findByValue(value);
		if (temp.size() < count)
		{
			temp.clear();
			return temp;
		}
		for (auto pChild : temp[count - 1]->nodeChildren())
			collection_.push_back(pChild);
		return std::move(collection_);
	}
	//----< find descendents of node with specified value >----------------------

	template<typename T>
	void MTree<T>::decendentsHelper(std::shared_ptr<MNode<T>> ptr)
	{
		collection_.push_back(ptr);
		for (auto pChild : ptr->nodeChildren())
			decendentsHelper(pChild);
	}

	template<typename T>
	std::vector<std::shared_ptr<MNode<T>>> MTree<T>::descendents(const T& value, size_t count = 1)
	{
		std::vector<std::shared_ptr<MNode<T>>> temp = findByValue(value);
		if (temp.size() < count)
		{
			temp.clear();
			return temp;
		}
		for (auto pChild : temp[count - 1]->nodeChildren())
			decendentsHelper(pChild);
		return std::move(collection_);
	}
	//----< show tree node structure >-------------------------------------------

	template<typename T>
	void showHelper(std::shared_ptr<MNode<T>> pNode, size_t levelCount)
	{
		std::string spacer(levelCount, ' ');
		levelCount += 2;
		std::cout << "\n  " << spacer << pNode->value();
		for (auto pChild : *pNode)
			showHelper(pChild, levelCount);
		levelCount -= 2;
	}

	template <typename T>
	void show(MTree<T>& tree)
	{
		if (tree.root() != nullptr)
			
			
			
			
			
			Helper(tree.root(), 0);
	}
}
#endif

class MTree
{
public:
	MTree();
	~MTree();
};
