#include <iostream>
using namespace std;

template<typename T>
struct Node
{
    T data;
    Node<T> *next = nullptr;
};

template<typename T>
class LinkQueue
{
private:
    Node<T>* front = nullptr;
    Node<T>* rear = nullptr;
public:
    LinkQueue();
    LinkQueue(int count);
    ~LinkQueue();
    void EnQueue(T element);
    T DeQueue();
    T GetHead();
    string Empty();
    void QueueShow();
};

template<typename T>
LinkQueue<T>::LinkQueue(int count)
{
    T number;
    Node<T>* newone = new Node<T>();
    Node<T>* newone1;
	cout << "请输入第" <<  1 << "个数字：";
	cin >> number;
    newone->data = number;
    front = newone;
    rear  = newone;
    for (int i = 1; i < count; ++i)
    {
        cout << "请输入第" << i + 1 << "个数字：";
        cin >> number;
        newone1 = new Node<T>();
        newone1->data = number;
        newone->next = newone1;
        newone = newone1;
    }
    newone->next = nullptr;
    rear = newone;
}

template<typename T>
LinkQueue<T>::LinkQueue()
{
    Node<T>* newone = nullptr;
    newone = new Node<T>();
    front = rear = newone;
}

template<typename T>
void LinkQueue<T>::EnQueue(T element)
{
    Node<T>* newone = new Node<T>();
    newone->data = element;
    rear->next = newone;
    rear = newone;
}

template<typename T>
T LinkQueue<T>::DeQueue()
{
    T element;
    if (rear == front)throw "溢出";
    Node<T>* newone = front;
    element = newone->data;
    front = newone->next;
    if (newone->next == nullptr) rear = front;
    delete newone;
    return element;
}

template<typename T>
T LinkQueue<T>::GetHead()
{
    if (front == nullptr)
        throw "这个队列没有元素";
    return front->data;
}

template<typename T>
string LinkQueue<T>::Empty()
{
    string conse = "";
    if (front == nullptr || rear == nullptr)
    {
        conse += "这个队列为空";
        return conse;
    }
    conse += "这个队列不是空";
    return conse;
}

template<typename T>
void LinkQueue<T>::QueueShow()
{
    Node<T>* newone = front;
    while (newone != nullptr)
    {
        cout << newone->data << endl;
        newone = newone->next;
    }
}

template<typename T>
LinkQueue<T>::~LinkQueue()
{
    Node<T>* newone = front;
    Node<T>* newone2;
    while (newone != nullptr)
    {
        newone2 = newone->next;
        delete newone;
        newone = newone2;
    }
}

int main()
{
    LinkQueue<int> qnide = LinkQueue<int>(4);
    qnide.QueueShow();
    cout<<qnide.Empty();
    return 0;
}
