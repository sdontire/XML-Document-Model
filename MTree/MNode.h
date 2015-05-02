#ifndef MNODE_H
#define MNODE_H
/////////////////////////////////////////////////////////////////
// MNode.h - Node helper for M-ary Tree data structure         //
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

#include <vector>
#include <memory>
#include <functional>
#include <string>
#include <iostream>
#include "../MTree/Utilities.h"  
//../Utilities/Utilities.h

namespace MTreeLib {

	/////////////////////////////////////////////////////////////////////////////
	// MNode<T> class

	template<typename T>
	class MNode {
	public:
		using sPtr = std::shared_ptr < MNode<T> >;
		using Children = std::vector < sPtr >;
		using iterator = typename Children::iterator;
		MNode(const T& t = T());       // can be used as default ctor
		MNode(const MNode<T>& node);
		MNode(MNode<T>&& node);
		MNode<T>& operator=(const MNode<T>& node);
		MNode<T>& operator=(MNode<T>&& node);
		sPtr clone() const;
		virtual ~MNode();

		T& value();
		T value() const;
		std::string& id();
		std::string id() const;
		bool addChild(sPtr pChild);  // fails if already has parent
		void addChild(const T& t);   // makes new node so has no parent
		std::vector<sPtr> nodeChildren();
		void setNodeChildren(std::vector<sPtr> childvec);
		size_t size() const;

		// note iterator points to std::shared_ptr<MNode<T>>, e.g., a pointer to a pointer
		iterator begin();
		iterator end();

		// note indexers return std::shared_ptr<MNode<T>>
		sPtr& operator[](size_t n);
		const sPtr& operator[](size_t n) const;

		sPtr findById(const std::string& id);
		std::vector<sPtr> findByValue(const T& t);

		std::vector<std::pair<std::string, std::string>> getAttributes();
		void setElement(std::string ele);
		std::string getElement();
		void setAttributes(std::vector<std::pair<std::string, std::string>> vec);

	private:
		void MNode<T>::cloneHelper(const MNode<T>& src, sPtr& dst) const;
		Children children_;
		std::string element;
		T value_;
		std::vector<std::pair<std::string, std::string>> attributes;
		std::string id_;         // MTree expects all its nodes to have unique ids or empty ids 
		bool hasParent = false;  // set to true when added to a node's children_ collection
	};
	
	template<typename T>
	void MNode<T>::setElement(std::string ele)
	{
		element = ele;
	}
	template<typename T>
	std::string MNode<T>::getElement()
	{
		return element;
	}
	template<typename T>
	void MNode<T>::setNodeChildren(std::vector<sPtr> childvec)
	{
		children_ = childvec;
	}

	template<typename T>
	std::vector<std::pair<std::string, std::string>> MNode<T>::getAttributes()
	{
		return attributes;
	}

	template<typename T>
	void MNode<T>::setAttributes(std::vector<std::pair<std::string, std::string>> vec)
	{
		attributes=vec;
	}

	
	//----< promotion constructor taking value >---------------------------------

	template<typename T>
	MNode<T>::MNode(const T& t) : value_(t), hasParent(false)
	{
		mtLog << std::string("\n  constructing MNode<T>(T)");
	}

	//----< copy constructor >---------------------------------------------------

	template<typename T>
	MNode<T>::MNode(const MNode<T>& node) : value_(node.value_), hasParent(false)
	{
		mtLog << std::string("copy construction from ") << node.value_;
		for (auto pChild : node.children_)
			children_.push_back(pChild->clone());
	}
	//----< move constructor >---------------------------------------------------

	template<typename T>
	MNode<T>::MNode(MNode<T>&& node) : value_(node.value_), hasParent(false)
	{
		mtLog << std::string("\n  move construction from ") << value_;
		children_ = std::move(node.children_); // causes children_.swap()
		node.value_ = T();
	}
	//----< destructor just used to enunciate >----------------------------------

	template<typename T>
	MNode<T>::~MNode()
	{
		mtLog << std::string("\n  deleting ") << value();
	}
	//----< private helper function for clone >----------------------------------

	template<typename T>
	void MNode<T>::cloneHelper(const MNode<T>& src, sPtr& dst) const
	{
		for (auto& pChild : src.children_)
		{
			sPtr pdstChild(new MNode<T>(pChild->value()));
			dst->addChild(pdstChild);
			cloneHelper(*pChild, pdstChild);
		}
	}
	//----< return clone of self >-----------------------------------------------

	template<typename T>
	std::shared_ptr<MNode<T>> MNode<T>::clone() const
	{
		mtLog << std::string("\n  cloning ") << value_;
		auto pReplica = sPtr(new MNode(this->value()));
		cloneHelper(*this, pReplica);
		return pReplica;
	}
	//----< access children collection >-----------------------------------------

	template<typename T>
	std::vector<std::shared_ptr<MNode<T>>> MNode<T>::nodeChildren() { return children_; }

	//----< copy assignment operator >-------------------------------------------

	template<typename T>
	MNode<T>& MNode<T>::operator=(const MNode<T>& node)
	{
		mtLog << std::string("\n  copy assignment from ") << node.value_;
		if (this == &node) return *this;
		// don't change hasParent
		value_ = node.value_;
		children_ = node.children_;
		return *this;
	}
	//----< move assignment operator >-------------------------------------------

	template<typename T>
	MNode<T>& MNode<T>::operator=(MNode<T>&& node)
	{
		mtLog << std::string("\n  move assignment from ") << node.value_;
		if (this == &node) return *this;
		// don't change hasParent
		value_ = node.value_;
		children_ = std::move(node.children_);
		return *this;
	}
	//----< get iterator pointing to std::shared_ptr to first child >------------

	template<typename T>
	typename MNode<T>::iterator MNode<T>::begin() { return children_.begin(); }

	//----< get iterator pointing to std::shared_ptr to one past last child >----

	template<typename T>
	typename MNode<T>::iterator MNode<T>::end() { return children_.end(); }

	//----< index through std::shared_ptrs to children >-------------------------

	template<typename T>
	std::shared_ptr<MNode<T>>& MNode<T>::operator[](size_t n)
	{
		if (size() <= n)
			throw(std::invalid_argument("index out of range"));
		return children_[n];
	}
	//----< index through std::shared_ptrs to children >-------------------------

	template<typename T>
	const std::shared_ptr<MNode<T>>& MNode<T>::operator[](size_t n) const
	{
		if (size() <= n)
			throw(std::invalid_argument("index out of range"));
		return children_[n];
	}
	//----< retrieve or set id >-------------------------------------------------

	template<typename T>
	std::string& MNode<T>::id() { return id_; }

	//----< retrieve id >--------------------------------------------------------

	template<typename T>
	std::string MNode<T>::id() const { return id_; }

	//----< retrieve or set value >----------------------------------------------

	template<typename T>
	T& MNode<T>::value() { return value_; }

	//----< retrieve value >-----------------------------------------------------

	template<typename T>
	T MNode<T>::value() const { return value_; }

	//----< add child std::shared_ptr to existing node >-------------------------
	/*
	*  Each node of tree must have only one parent (otherwise not a tree),
	*  so add child only if child has no other parent.
	*/
	template<typename T>
	bool MNode<T>::addChild(sPtr pChild)
	{
		mtLog << std::string("\n  adding existing child ") << pChild->value_
			<< std::string(" to ") << value_;
		if (!pChild->hasParent)
		{
			pChild->hasParent = true;
			children_.push_back(pChild);
			return true;
		}
		return false;
	}
	//----< add child std::shared_ptr to new node with specified value >---------

	template<typename T>
	void MNode<T>::addChild(const T& t)
	{
		mtLog << std::string("\n  adding new child ") << t << std::string(" to ") << value_;
		std::shared_ptr<MNode<T>> pToAdd(new MNode<T>(t));
		pToAdd->hasParent = true;
		children_.push_back(pToAdd);
	}
	//----< return number of children >------------------------------------------

	template<typename T>
	size_t MNode<T>::size() const { return children_.size(); }


	/////////////////////////////////////////////////////////////////////////////
	// valueSearch functor

	template<typename T>
	class valueSearch
	{
	public:
		valueSearch(const T& value);
		void add(std::shared_ptr<MNode<T>> pNode);
		void operator()(std::shared_ptr<MNode<T>> pNode);
		std::vector<std::shared_ptr<MNode<T>>> result();
	private:
		std::vector<std::shared_ptr<MNode<T>>> found_;
		T value_;
	};

	template<typename T>
	valueSearch<T>::valueSearch(const T& value) : value_(value) {}

	template<typename T>
	void valueSearch<T>::add(std::shared_ptr<MNode<T>> pNode)
	{
		found_.push_back(pNode);
	}

	template<typename T>
	void valueSearch<T>::operator()(std::shared_ptr<MNode<T>> pNode)
	{
		if (value_ == pNode->value())
			found_.push_back(pNode);
		for (auto pChild : pNode->nodeChildren())
			(*this)(pChild);
	}

	template <typename T>
	std::vector<std::shared_ptr<MNode<T>>> valueSearch<T>::result() { return found_; }

	///////////////////////////////////////////////////////////////////////////
	// idSearch functor

	template<typename T>
	class idSearch
	{
	public:
		idSearch(const std::string& id);
		void operator()(std::shared_ptr<MNode<T>> pNode);
		std::shared_ptr<MNode<T>> result();
	private:
		std::shared_ptr<MNode<T>> found_ = nullptr;
		std::string id_;
	};

	template<typename T>
	idSearch<T>::idSearch(const std::string& id) : id_(id) {}

	template<typename T>
	void idSearch<T>::operator()(std::shared_ptr<MNode<T>> pNode)
	{
		if (id_ == pNode->id())
			found_ = pNode;
		if (found_ != nullptr)
			return;
		for (auto pChild : pNode->nodeChildren())
			(*this)(pChild);
	}

	template <typename T>
	std::shared_ptr<MNode<T>> idSearch<T>::result() { return found_; }

	///////////////////////////////////////////////////////////////////////////

	//----< search decendents for value >--------------------------------------

	template<typename T>
	std::vector<std::shared_ptr<MNode<T>>> MNode<T>::findByValue(const T& value)
	{
		valueSearch<T> vs(value);
		for (auto pChild : children_)
			vs(pChild);
		return vs.result();
	}
	//----< search decendents for id >-----------------------------------------

	template<typename T>
	std::shared_ptr<MNode<T>> MNode<T>::findById(const std::string& id)
	{
		idSearch<T> is(id);
		for (auto pChild : children_)
		{
			if (is.result() != nullptr)
				break;
			is(pChild);
		}
		return is.result();
	}

	/////////////////////////////////////////////////////////////////////////////
	// global helper functions

	//----< make new MNode<T> with specified value >-----------------------------

	template<typename T>
	std::shared_ptr<MNode<T>> makeNode(const T& t)
	{
		return std::shared_ptr<MNode<T>>(new MNode<T>(t));
	}
	//----< global function to display contents of MNode<T> >--------------------
	template<typename T>
	void show(MNode<T>& node)
	{
		std::cout << "\n  " << node.value();
		for (auto& pChild : node)
			show(*pChild);
	}
	//----< Depth First Search with pluggable operation >------------------------
	/*
	* apply callable object f on every node of tree during depth first search
	*/
	template<typename T>
	void DFS(MNode<T>& node, std::function<void(const MNode<T>&)>& f)
	{
		f(node);
		for (auto& pChild : node)
			DFS(*pChild, f);
	}
}
#endif

