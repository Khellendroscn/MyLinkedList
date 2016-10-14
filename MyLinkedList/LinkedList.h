#pragma once
/*
Class : template LinkedList
Created by : Khellendros
Date : 2016 10 12
Version : v2.2
*/
#include<iostream>
namespace Khellendros {
	template<typename T>
	class LinkedListIterator;
	template<typename T>
	class LinkedList
	{
	public:
		template<typename T>
		class ListNode
		{
			//Ƕ���࣬����ڵ�
		public:
			typedef T ValueType;
		private:
			ValueType* valuePtr;
			ListNode* previousPtr;
			ListNode* nextPtr;
		public:
			ListNode()
			{
				valuePtr = nullptr;
				previousPtr = nullptr;
				nextPtr = nullptr;
			}

			ListNode(const ValueType& value, ListNode* const previous = nullptr, ListNode* const next = nullptr)
			{
				previousPtr = previous;
				nextPtr = next;
				valuePtr = new ValueType;
				*valuePtr = value;
			}
			ListNode(ValueType* const value, ListNode* const previous = nullptr, ListNode* const next = nullptr)
			{
				valuePtr = value;
				previousPtr = previous;
				nextPtr = next;
			}
			~ListNode()
			{
				//��������
				if (valuePtr != nullptr)
				{
					delete valuePtr;
					valuePtr = nullptr;
				}
				previousPtr = nullptr;
				nextPtr = nullptr;
			}

			void setValue(const ValueType& value)
			{
				*valuePtr = value;
			}

			void setNext(ListNode* const next)
			{
				nextPtr = next;
			}

			void setPrevious(ListNode* const previous)
			{
				previousPtr = previous;
			}

			ListNode* getNext()const
			{
				return nextPtr;
			}

			ListNode* getPrevious()const
			{
				return previousPtr;
			}

			ValueType& getValue()const
			{
				return ValueType(*valuePtr);
			}

			ValueType& getValue()
			{
				return *valuePtr;
			}
			ValueType* getValuePtr()
			{
				return valuePtr;
			}
			static void link(ListNode* node1, ListNode* node2)
			{
				//��node2���ӵ�node1֮��
				node1->setNext(node2);
				node2->setPrevious(node1);
			}
			void swapPtr()
			{
				ListNode* temp = nextPtr;
				setNext(previousPtr);
				setPrevious(nextPtr);
			}
			bool operator==(const ListNode& node)const
			{
				return valuePtr == node.valuePtr;
			}
			bool operator!=(const ListNode& node)const
			{
				return valuePtr != node.valuePtr;
			}
			//bool hasNext()const
			//{
			//	return nextPtr != nullptr;
			//}
			//bool hasPrevious()const
			//{
			//	return previousPtr != nullptr;
			//}
		};
		typedef typename T ValueType;
		typedef typename LinkedListIterator<ValueType> IterType;
		typedef typename ListNode<T> NodeType;
		//friend class iterType;

	private:
		NodeType* rootNode;//���ڵ�
		int length;//����
		bool isSimpleCopy;//�Ƿ���ǳ����
		void deepCopy()
		{
			//���
			NodeType* temp = rootNode->getNext();
			NodeType* tempRoot = rootNode;
			rootNode = new NodeType();
			rootNode->setNext(rootNode);
			rootNode->setPrevious(rootNode);
			length = 0;
			isSimpleCopy = false;
			while (temp!= tempRoot)
			{
				pushBack(temp->getValue());
				temp = temp->getNext();
			}
		}
	public:
		//���캯����
		LinkedList()//Ĭ�Ϲ��캯��
		{
			rootNode = new NodeType();//Ϊ�ڵ�����ڴ�
			rootNode->setNext(rootNode);
			rootNode->setPrevious(rootNode);
			length = 0;
			isSimpleCopy = false;
		}
		LinkedList(const LinkedList& list)//���ƹ���
		{
			rootNode = list.rootNode;
			length = list.length;
			isSimpleCopy = true;
		}
		LinkedList(LinkedList&& list)//��ֵ����
		{
			rootNode = list.rootNode;
			length = list.length;
			isSimpleCopy = false;
			list.isSimpleCopy = true;
		}
		LinkedList(const std::initializer_list<ValueType>& init)//�б��ʼ��
		{
			rootNode = new NodeType();//Ϊ�ڵ�����ڴ�
			rootNode->setNext(rootNode);
			rootNode->setPrevious(rootNode);
			length = 0;
			isSimpleCopy = false;
			for (auto item : init)
			{
				pushBack(item);
			}
		}
		//����������
		~LinkedList()
		{
			if (!isSimpleCopy)
			{
				//�����ͷ����нڵ�
				while (length>0)
				{
					popBack();
				}
				delete rootNode;
			}
		}
		//��飺
		int size()const
		{
			return length;
		}

		bool isEmpty()const
		{
			return length == 0;
		}
		//������
		ValueType& get(IterType& iter)
		{
			if (isSimpleCopy)
			{
				deepCopy();
			}
			return iter.node->getValue();
		}
		ValueType& get(IterType& iter)const
		{
			return iter.node->getValue();
		}
		void pushBack(const ValueType& value)
		{
			if (isSimpleCopy)
			{
				//����Ƿ���ǳ����
				deepCopy();
			}
			//���뵽��β
			NodeType* tailNode = rootNode->getPrevious();//��ȡβ�ڵ�
			NodeType* newNode = new NodeType(value, tailNode, rootNode);//�����½ڵ�
			tailNode->setNext(newNode);//���ӵ�β��
			rootNode->setPrevious(newNode);
			++length;
		}

		ValueType popBack()
		{
			//������βԪ��
			if (isEmpty())
			{
				return ValueType();
			}
			if (isSimpleCopy)
			{
				deepCopy();
			}
			NodeType* tailNode = rootNode->getPrevious();
			tailNode->getPrevious()->setNext(rootNode);
			rootNode->setPrevious(tailNode->getPrevious());
			ValueType value = tailNode->getValue();
			delete tailNode;
			tailNode = nullptr;
			--length;
			return value;
		}

		void pushFront(const ValueType& value)
		{
			//���뵽��ͷ
			if (isSimpleCopy)
			{
				deepCopy();
			}
			NodeType* frontNode = rootNode->getNext();
			NodeType* newNode = new NodeType(value, rootNode, frontNode);
			frontNode->setPrevious(newNode);
			rootNode->setNext(newNode);
			++length;
		}

		ValueType popFront()
		{
			//������ͷ
			if (isEmpty())
			{
				return ValueType();
			}
			if (isSimpleCopy)
			{
				deepCopy();
			}
			NodeType* frontNode = rootNode->getNext();
			frontNode->getNext()->setPrevious(rootNode);
			rootNode->setNext(frontNode->getNext());
			ValueType value = frontNode->getValue();
			delete frontNode;
			frontNode = nullptr;
			--length;
			return value;
		}
		ValueType getBack()
		{
			return rootNode->getPrevious()->getValue();
		}
		ValueType getFront()
		{
			return rootNode->getNext()->getValue();
		}
		IterType& insert(IterType& iter, const ValueType& value)
		{
			if (isSimpleCopy) deepCopy();
			NodeType* target = iter.node;
			NodeType* previous = target->getPrevious();
			NodeType* newNode = new NodeType(value, previous, target);
			target->setPrevious(newNode);
			previous->setNext(newNode);
			++length;
			return --iter;
		}
		IterType& remove(IterType& iter)
		{
			if (iter == end()) return end();
			if (isSimpleCopy) deepCopy();
			NodeType* target = iter.node;
			target->getPrevious()->setNext(target->getNext());
			target->getNext()->setPrevious(target->getPrevious());
			++iter;
			delete(target);
			--length;
			return iter;
		}
		void reverse()
		{
			NodeType* nextNode = rootNode->getNext();
			while (nextNode != rootNode)
			{
				NodeType* temp = nextNode;
				nextNode = temp->getNext();
				temp->swapPtr();
			}
			rootNode->swapPtr();
		}
		IterType begin()
		{
			return IterType(this,rootNode->getNext());
		}
		IterType end()
		{
			return IterType(this,rootNode);
		}

		//�����������
		LinkedList& operator<<(const ValueType& value)
		{
			pushBack(value);
			return *this;
		}
		LinkedList& operator >> (ValueType& value)
		{
			value = popBack();
			return *this;
		}
		LinkedList& operator+=(const LinkedList& list)
		{
			if (isSimpleCopy)
			{
				deepCopy();
			}
			LinkedList temp(list);
			temp.deepCopy();
			temp.isSimpleCopy = true;//��ֹtemp�����������ͷ�
			NodeType* newTail = temp.rootNode->getPrevious();
			temp.rootNode->getNext()->setPrevious(rootNode->getPrevious());//��list2��ͷ���ӵ�list1��β��
			rootNode->getPrevious()->setNext(temp.rootNode->getNext());//��list1��β���ӵ�list2��ͷ��
			newTail->setNext(rootNode);//��list2��β���ӵ�list1�ĸ��ڵ�
			rootNode->setPrevious(newTail);//��list2��β����Ϊβ�ڵ�
			length += list.size();//���ӳ���
			return *this;
		}
		LinkedList operator+(const LinkedList& list)const
		{
			LinkedList temp(*this);
			temp.deepCopy();
			temp += list;
			return temp;
		}
		bool operator==(LinkedList& list)
		{
			if (length != list.size()) return false;
			for (auto iter1 = begin(), iter2 = list.begin(); iter1 != end()&&iter2!=list.end(); ++iter1, ++iter2)
			{
				if (*iter1 != *iter2) return false;
			}
			return true;
		}
		bool operator!=(LinkedList& list)
		{
			return !operator==(list);
		}
		T& operator[](int index)const
		{
			IterType iter = begin();
			for (int i = 0; i < index; ++i, ++iter);
			return *iter;
		}
		T& operator[](int index)
		{
			IterType iter = begin();
			for (int i = 0; i < index; ++i, ++iter);
			return *iter;
		}
		template<typename T>
		friend std::ostream& operator<<(std::ostream& os, const LinkedList& list);
	};
	template<typename T>
	std::ostream& operator<<(std::ostream& os, LinkedList<T>& list)
	{
		os << "[ ";
		for (auto item : list)
		{
			os << item << " , ";
		}
		os << "\b\b]";
		return os;
	}
}