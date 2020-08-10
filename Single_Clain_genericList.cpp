#include <iostream>
#include<ctime>
using namespace std;


template<typename T>
struct Node
{
	T  data;
	Node<T>* next;
};

template<typename T>
class operator_Clain
{
public:
	operator_Clain()
	{
		Head = nullptr;
	}
	const int amount = 10;
	Node<T>* Head = nullptr;
	bool CreateList();                           //创建链表无参数情况;
	bool CreateList(int index);   //创建链表有参数的情况,该函数的参数是链表节点的数量
	int Getelement(int index);   //获取链表中的第index个元素
	bool ListInsert(int index, T node_data);  //在链表中第index个位置插入元素
	bool ListDelete(int index);  //删除链表中第index个元素
	void ListShow();         //显示链表中的数据
	bool Clear(operator_Clain<T>* linklist);  //清除链表数据
};

template<typename T>
bool operator_Clain<T>::CreateList()    //创建链表无参数情况;
{
	Node<T>* first, * second;
	srand(time(0));
	Head = new Node<T>();
	second = Head;
	for (int i = 0; i < amount; i++)
	{
		first = new Node<T>();
		first->data = rand() % 100 + 1;
		second->next = first;
		second = first;
	}
	second->next = nullptr;
	return true;
}

template<typename T>
bool operator_Clain<T>::CreateList(int number)   //创建链表有参数的情况,该函数的参数是链表节点的数量
{
	Node<T>* first, * second;
	cout << "接下来输入这个链表的节点数据：\n";
	Head = new Node<T>();
	second = Head;
	for (int i = 0; i < number; i++)
	{
		first = new Node<T>();
		cout << "输入第" << i + 1 << "数据：";
		cin >> (first->data);
		second->next = first;
		second = first;
	}
	second->next = nullptr;
	return true;
}

template<typename T>
void operator_Clain<T>::ListShow()   //获取链表中的第index个元素
{
	Node<T>* point;
	point = Head->next;
	while (point != NULL)
	{
		cout << point->data << endl;
		point = point->next;
	}
}

template<typename T>
int operator_Clain<T>::Getelement(int index)   //在链表中第index个位置插入元素
{
	int counter = 1;
	Node<T>* point = nullptr;
	point = Head->next;
	while (point && counter < index)
	{
		point = point->next;
		++counter;
	}
	return (point->data);
}

template<typename T>
bool operator_Clain<T>::ListInsert(int index, T node_data)   //删除链表中第index个元素
{
	int counter = 1;
	Node<T>* Data1, * point = nullptr;
	point = Head->next;
	while (point && counter < (index - 1))
	{
		point = point->next;
		++counter;
	}
	if ((counter > (index - 1)) || !point)
		return false;
	Data1 = new Node<T>();
	Data1->data = node_data;
	Data1->next = point->next;
	point->next = Data1;
	return true;
}


template<typename T>
bool operator_Clain<T>::ListDelete(int index)  //显示链表中的数据
{
	int counter = 1;
	Node<T>* point1, * point0;
	point0 = Head->next;
	while (point0 && counter < (index - 1))
	{
		point0 = point0->next;
		++counter;
	}
	if ((counter > (index - 1)) || !point0)
		return false;
	point1 = point0->next;
	point0->next = point1->next;
	delete point1;
	return true;
}

template<typename T>
bool operator_Clain<T>::Clear(operator_Clain<T>* linklist)  //清除链表数据
{
	Node<T>* point1, * point2;
	point1 = linklist->Head->next;
	while (point1)
	{
		point2 = point1->next;
		delete point1;
		point1 = point2;
	}
	linklist->Head->next = nullptr;
	return true;
}

int main()
{
	operator_Clain<float>* clain1 = new operator_Clain<float>();
	clain1->CreateList(4);
	clain1->ListShow();
	cout << endl;
	clain1->ListDelete(9);
	clain1->ListShow();
	clain1->Clear(clain1);
	delete clain1;
	return 0;
}
