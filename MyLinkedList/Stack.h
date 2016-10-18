#pragma once
#include<iostream>
namespace Khellendros {
#include"LinkedList.h"
	//栈适配器，将链表包装成栈
	template<typename T>
	class Stack {
	public:
		typedef typename T ValueType;
		typedef typename LinkedList<T> ListType;
	private:
		ListType list;
	public:
		Stack() = default;
		Stack(const ListType& linkedList) :list(linkedList) {}
		Stack(const Stack& stack) :list(stack.list) {}
		void push(const ValueType& item) { list.pushFront(item); }
		ValueType pop() { return list.popFront(); }
		ValueType top() { return list.getFront(); }
		int size() { return list.size(); }
		bool isEmpty() { return list.isEmpty(); }
		void clear() { list.clear(); }
		Stack& operator<<(const ValueType& item) { push(item); return *this; }
		Stack& operator >> (ValueType& item) { item = pop(); return *this; }
		template<typename T>
		friend std::ostream& operator<<(std::ostream& os, Stack<T>& stack);
	};
	template<typename T>
	std::ostream& operator<<(std::ostream& os, Stack<T>& stack)
	{
		os << stack.list;
		return os;
	}
}