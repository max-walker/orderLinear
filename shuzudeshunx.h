#pragma once
#include<iostream>
using namespace std;
const int maxinum = 20;
template<typename T>
struct shuzu
{
	int length;
	T shuzu_shuzu[maxinum];
	shuzu();
	shuzu(T l[],int i);
	void Show();
};


template<typename T>
bool ClearList(T *l);     //清除线性表的数据

template<typename T>
int GetElem(T * l, int i);//获取某个元素

template<typename T>
bool ListDelete(T* l, int i);//删除第某个元素并返回

template<typename T>
bool ListInsert(T* l, int i, int e);//在线性表的第i的元素插入一个元素

template<typename T>
shuzu<T>::shuzu()
{
	for (int i = 0; i < maxinum; i++)
		shuzu_shuzu[i] = 0;
	length = 0;
}

template<typename T>
shuzu<T>::shuzu(T l[], int i)
{
	for (int ou = 0; ou < i; ou++)
		shuzu_shuzu[ou] = l[ou];
	length = i;
}

template<typename T>
void shuzu<T>::Show()
{
	for (int i = 0; i < length; i++)
		std::cout << shuzu_shuzu[i] << std::endl;
}

template<typename T>
int GetElem(T* l, int i)
{
	if ((i > l->length) || (i < 0) || (l->length == 0))
	{
		std::cout << "此查询的数字无效";
		return 0;
	}
	return l->shuzu_shuzu[i - 1];
}

template<typename T>
bool ListDelete(T* l, int i)
{
	int k;
	if ((i > l->length) || (i < 0) || (l->length == 0))
	{
		std::cout << "此删除的数字无效";
		return false;
	}
	if (i < l->length)
	{
		for (k = i; k < l->length; k++)
		{
			l->shuzu_shuzu[k - 1] = l->shuzu_shuzu[k];
		}
	}
	l->length--;
	return true;
}

template<typename T>
bool ListInsert(T* l, int i, int e)
{
	int k;
	if ((i > l->length) || (i < 0) || (l->length == 0))
	{
		std::cout << "此插入的数字无效";
		return false;
	}
	if (l->length >= i)
	{
		for (k = l->length - 1; k >= i - 1; k--)
			l->shuzu_shuzu[k + 1] = l->shuzu_shuzu[k];
	}
	l->shuzu_shuzu[i - 1] = e;
	l->length++;
	return true;
}

template<typename T>
bool ClearList(T* l)
{
	for (int i = 0; i < l->length; i++)
		l->shuzu_shuzu[i] = 0;
	l->length = 0;
	return true;
}