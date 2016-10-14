#pragma once
#include<iterator>
namespace Khellendros {
#include"LinkedList.h"
	template<typename T>
	class LinkedListIterator :public std::iterator<std::bidirectional_iterator_tag, T>
	{
	public:
		typedef typename T ValueType;
		typedef typename LinkedList<T> List;
		typedef typename List::NodeType Node;
		friend class List;
	private:
		Node* node;
		List* list;
	public:
		LinkedListIterator(List* listPtr,Node*  listNode) :list(listPtr),node(listNode) {}
		LinkedListIterator(const LinkedListIterator& iter) :list(iter.list),node(iter.node) {}

		//²Ù×÷£º
		ValueType& operator*()const
		{
			return list->get(*this);
		}
		ValueType& operator*()
		{
			return list->get(*this);
		}
		ValueType* operator->()
		{
			return node->getValuePtr();
		}
		LinkedListIterator& operator++()
		{
			node = node->getNext();
			return *this;
		}
		LinkedListIterator operator++(int)
		{
			LinkedListIterator temp(*this);
			this->operator++();
			return temp;
		}
		LinkedListIterator& operator--()
		{
			node = node->getPrevious();
			return *this;
		}
		LinkedListIterator operator--(int)
		{
			LinkedListIterator temp(*this);
			this->operator--();
			return temp;
		}
		bool operator==(const LinkedListIterator& iter)const
		{
			return node == iter.node;
		}
		bool operator!=(const LinkedListIterator& iter)const
		{
			return node != iter.node;
		}

	};
}
