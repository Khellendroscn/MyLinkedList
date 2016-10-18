#include"LinkedList.h"
#include"LinkedListIterator.h"
#include"Stack.h"
#include<algorithm>
using namespace std;
using namespace Khellendros;
void testInit() {
	cout << "Test LinkedList(initialize)" << endl;
	cout << "默认构造：" << endl;
	LinkedList<int> list1;
	cout << "pushBack():" << endl;
	list1 << 1 << 2 << 3;
	cout << list1 << endl;
	cout << "列表构造" << endl;
	LinkedList<int> list2 = { 1,3,5,7,9 };
	cout << list2 << endl;
	cout << "list1+list2:\n" << list1+list2 << endl;
	cout << "下标[0],[1],[2]：" << endl;
	cout << list1[0]<<" , "<<list1[1]<<" , "<<list1[2] << endl;
}
void testOtherFunc()
{
	cout << "====================" << endl;
	cout << "Test Other Functions" << endl;
	LinkedList<int> list = { 1,2,3,4,5,6,7 };
	cout << list << endl;
	cout << "pushFront():" << endl;
	list.pushFront(0);
	cout << list << endl;
	int n1,n2;
	list >> n1;
	n2=list.popFront();
	cout << "pop():" << endl;
	cout << "n1,n2: " << n1<<" , "<<n2 << endl;
	cout << list << endl;
	auto iter = list.begin();
	++iter;
	iter = list.insert(iter, 999);
	iter = list.insert(iter, 888);
	cout << "insert():" << endl;
	cout << list << endl;
	iter = list.remove(iter);
	cout << "remove():" << endl;
	cout << list << endl;
	cout << "std::find():" << endl;
	auto iter1 = find(list.begin(), list.end(), 999);
	auto list2 = list;
	cout << "operator==" << endl;
	cout << (list == list2 ? "true" : "false") << endl;
	cout << "list<<123  list2<<456 ; operator== :" << endl;
	list << 123;
	list2 << 456;
	cout << (list == list2 ? "true" : "false") << endl;
	cout << "revers():" << endl;
	list.reverse();
	cout << list << endl;
	if (iter1 != list.end())
	{
		cout << *iter1 << " found!" << endl;
	}
	else
	{
		cout << "not found..." << endl;
	}
}
void testStack()
{
	cout << "====================" << endl;
	cout << "Test Stack" << endl;
	LinkedList<char> chars = {'a','b','c'};
	Stack<char> charStack(chars);
	char c1, c2;
	charStack >> c1 >> c2;
	cout << "c1: " << c1 << " c2: " << c2 << endl;
	cout << "charStack: " << charStack << endl;
	cout << "chars: " << chars << endl;
	charStack << c1 << c2;
	cout << "top: " << charStack.top() << endl;
	cout << "charStack: " << charStack << endl;
}
int main()
{
	testInit();
	testOtherFunc();
	testStack();
	system("pause");
	return 0;
}