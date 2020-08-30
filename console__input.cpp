#include<iostream>
#include<string>
#include<cstdlib>

using namespace std;

template<typename Item>
class Stack
{
private:
	struct stackNode
	{
		Item idata;
		stackNode* next = nullptr;
	};
	stackNode* Top=nullptr;
	int count;
public:
	Stack() { Top = nullptr; count = 0; }
	~Stack();
	Stack(int i);
	bool Push(Stack<Item>& s, Item number);
	bool Pop(Stack<Item>& s);
	bool ClearStack(Stack<Item>& s);
	int Stacklength(Stack<Item>& s) { return s.count; }
	bool StackEmpty(Stack<Item>& s) { return (Top == nullptr); }
	void Show();
};

template<typename Item>
Stack<Item>::Stack(int i)
{
	Item number;
	count = 0;
	if(i<=0)
	{
		cout << "这个栈的数量为0" << endl;
		Top = nullptr;
		count = 0;
	}
	for (int o = 0; o < i; o++)
	{
		stackNode *node = new stackNode();
		cout << "输入第" << o + 1 << "个数字：";
		cin >> number;
		node->idata = number;
		node->next = Top;
		Top = node;
		count++;
	}
}

template<typename Item>
bool Stack<Item>::Push(Stack<Item>& s, Item number)
{
	stackNode* mode = new stackNode();
	mode->idata = number;
	mode->next = s.Top;
	s.Top = mode;
	s.count++;
	return true;
}

template<typename Item>
bool Stack<Item>::Pop(Stack<Item>& s)
{
	stackNode* mode = new stackNode();
	if (StackEmpty(s))
	{
		cout << "pop失败，该栈是空的";
		return false;
	}
	mode = s.Top;
	s.Top = s.Top->next;
	delete mode;
	s.count--;
	return true;
}

template<typename Item>
bool Stack<Item>::ClearStack(Stack<Item>& s)
{
	if (StackEmpty(s))
	{
		cout << "pop失败，该栈是空的";
		return false;
	}
	stackNode* mode = new stackNode();
	while (s.Top)
	{
		mode = s.Top;
		s.Top = s.Top->next;
		delete mode;
		s.count--;
	}
	return true;
}

template<typename Item>
Stack<Item>::~Stack()
{
	stackNode* mode = new stackNode();
	while (Top)
	{
		mode = Top;
		Top = Top->next;
		delete mode;
	}
}

template <typename Item>
void Stack<Item>::Show()
{
	stackNode *mode=new stackNode();
	int nu;
	for (mode = Top, nu = 0; nu < count; nu++)
	{
		cout << mode->idata << "   ";
		mode = mode->next;
	}
}

int main()
{
	Stack<double> ou = Stack<double>(3);
	ou.Show();
	ou.ClearStack(ou);
	ou.Pop(ou);
	return 0;
}
