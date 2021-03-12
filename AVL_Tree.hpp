#pragma once
#include "headfile.hpp"
//ƽ����������ñ���Ҫ�ο�����������԰�е����±�д��ƽ�����������Ҫ�Լ�дһ��

//����������л�������ü������ۣ��ر���ɾ�������Ǳߡ������ָ��ˣ�����������˵������bug�����Ҷ��ڲ���û��bug���Ǿ���û��bug�����������������һ��Ҫ��˺��
//���ò�˵���ֳ���˺���������ţ��


//��㹹��
template<typename T>
class AVLTreeNode
{
public:
	T key = {};
	AVLTreeNode* left, * right;
	int height;

	//��ʼ������
	AVLTreeNode(T value, AVLTreeNode* l=nullptr, AVLTreeNode* r=nullptr)
	{
		key = value;
		left = l;
		right = r;
		height = 0;
	}
};

template<typename T>
class AVLtree_first
{
private:
	AVLTreeNode<T>* HeadPoint;

public:
	AVLtree_first();
	~AVLtree_first();

	int height();              //��ȡ���ĸ߶�
	int max(int a, int b);     //��ȡ���ĸ߶�

	//�������еı���
	void PreOrder();
	void InOrder();
	void PostOrder();

	//����AVL���е�keyֵ�Ľڵ�
	AVLTreeNode<T>* search(T key);             //�ݹ�ʵ��
	AVLTreeNode<T>* iterativsSearch(T key);    //�ǵݹ�ʵ��

	//������С�ڵ㣺������С�ڵ��ֵ
	T minimum();
	//�������ڵ㣺�������ڵ��ֵ
	T maximum();

	//���ڵ㣬�ڵ�ֵΪkey����AVL����
	void insert(T key);

	//ɾ��ֵΪkey�Ľڵ�
	void remove(T key);

	//��ӡ��AVL��
	void print();

	//ɾ����
	void destory();

private:
	//��ȡ���ĸ߶�
	int height(AVLTreeNode<T>* tree);

	//����AVL��
	void PreOrder(AVLTreeNode<T>* tree) const;
	void PostOrder(AVLTreeNode<T>* tree) const;
	void InOrder(AVLTreeNode<T>* tree) const;

	//(�ݹ�ʵ��) ����AVL����ֵΪkey�Ľڵ�
	AVLTreeNode<T>* search(AVLTreeNode<T>* x, T key)const;
	//���ǵݹ�ʵ�֣�����AVL����ֵΪkey�Ľڵ�
	AVLTreeNode<T>* iterativsSearch(AVLTreeNode<T>* x, T key)const;

	//����������Сkeyֵ�Ľڵ�
	AVLTreeNode<T>* minium(AVLTreeNode<T>* tree);
	//�����������keyֵ�Ľڵ�
	AVLTreeNode<T>* maximum(AVLTreeNode<T>* tree);

	//LL:�����Ӧ�����
	AVLTreeNode<T>* leftleftRotation(AVLTreeNode <T>* k2);

	//RR:���Ҷ�Ӧ�����
	AVLTreeNode<T>* rightrightRotation(AVLTreeNode <T>* k1);

	//LR�����Ҷ�Ӧ�����
	AVLTreeNode<T>* leftrightRotation(AVLTreeNode<T>* k3);

	//RL:�����Ӧ�����
	AVLTreeNode<T>* rightleftRotation(AVLTreeNode<T>* k1);

	//���½ڵ㣨key������AVL����
	AVLTreeNode<T>* insert(AVLTreeNode<T>*& tree, T key);

	//ɾ��AVL���еĽڵ�Z�������ر�ɾ���Ľڵ�
	AVLTreeNode<T>* remove(AVLTreeNode<T>*& tree, AVLTreeNode<T>* z);

	//������
	void destory(AVLTreeNode<T>*& tree);

	//��ӡAVL��
	void print(AVLTreeNode<T>* tree, T key, int direction);
};


//���캯��
template<typename T>
AVLtree_first<T>::AVLtree_first() :HeadPoint(nullptr) {}

//��������
template<typename T>
AVLtree_first<T>::~AVLtree_first() { cout << "\n�ͷ��ڴ�\n"; destory(HeadPoint); }

//��ȡ���ĸ߶�
template<typename T>
int AVLtree_first<T>::height(AVLTreeNode<T>* tree)
{
	if (tree != nullptr)
		return tree->height;
	return 0;
}
template<typename T>
int AVLtree_first<T>::height()
{
	return height(HeadPoint);
}

//�Ƚ�����keyֵ�Ĵ�С
template<typename T>
int AVLtree_first<T>::max(int a, int b)
{
	return a > b ? a : b;
}

//����ƽ��������ĸ��ַ�����
//ǰ�����
template<typename T>
void AVLtree_first<T>::PreOrder(AVLTreeNode<T>* tree) const
{
	if (tree == nullptr)return;
	else
	{
		cout << tree->key << " ";
		PreOrder(tree->left);
		PreOrder(tree->right);
	}
}

template<typename T>
void AVLtree_first<T>::PreOrder()
{
	PreOrder(HeadPoint);
}

//�������
template<typename T>
void AVLtree_first<T>::InOrder(AVLTreeNode<T>* tree) const
{
	if (tree == nullptr)return;
	else
	{
		InOrder(tree->left);
		cout << tree->key << " ";
		InOrder(tree->right);
	}
}

template<typename T>
void AVLtree_first<T>::InOrder()
{
	InOrder(HeadPoint);
}

//�������
template<typename T>
void AVLtree_first<T>::PostOrder(AVLTreeNode<T>* tree)const
{
	if (tree == nullptr)return;
	else
	{
		PostOrder(tree->left);
		PostOrder(tree->right);
		cout << tree->key << " ";
	}
}

template<typename T>
void AVLtree_first<T>::PostOrder()
{
	PostOrder(HeadPoint);
}


//���ݹ�ʵ�֣�����x����Ϊkeyֵ�Ľڵ�
template<typename T>
AVLTreeNode<T>* AVLtree_first<T>::search(AVLTreeNode<T>* x, T key)const
{
	if (x == nullptr || x->key == key)return x;

	if (key < x->key)
		return search(x->left,key);
	else
		return search(x->right,key);
}

template<typename T>
AVLTreeNode<T>* AVLtree_first<T>::search(T key)
{
	return search(HeadPoint,key);
}

//���ǵݹ�ʵ�֣�����x����Ϊkeyֵ�Ľڵ�
template<typename T>
AVLTreeNode<T>* AVLtree_first<T>::iterativsSearch(AVLTreeNode<T>* x, T key) const
{
	while ((x != nullptr) && (x->key != key))
	{
		if (key < x->key)
			x = x->left;
		else
			x = x->right;
	}
	return x;
}

template<typename T>
AVLTreeNode<T>* AVLtree_first<T>::iterativsSearch(T key)
{
	return iterativsSearch(HeadPoint,key);
}


//������С�ڵ㣬����treeΪ���ڵ��AVL������С�ڵ�
template<typename T>
AVLTreeNode<T>* AVLtree_first<T>::minium(AVLTreeNode<T>* tree)
{
	if (tree == nullptr)return nullptr;
	while (tree->left != nullptr)
		tree = tree->left;
	return tree;
}

template<typename T>
T AVLtree_first<T>::minimum()
{
	AVLTreeNode<T>* p = minium(HeadPoint);
	if (p != nullptr)
		return p->key;
	return (T)NULL;
}

//�������ڵ㣬����treeΪ���ڵ��AVL�������ڵ�
template<typename T>
AVLTreeNode<T>* AVLtree_first<T>::maximum(AVLTreeNode<T>* tree)
{
	if (tree == nullptr)
		return nullptr;
	while (tree->right != nullptr)
		tree = tree->right;
	return tree;
}

template<typename T>
T AVLtree_first<T>::maximum()
{
	AVLTreeNode<T>* p = maximum(HeadPoint);
	if (p != nullptr)
		return p->key;
	return (T)NULL;
}


/*
	LL:�����Ӧ�����������ת��

	����ֵ:��ת��ĸ��ڵ�
*/
template<typename T>
AVLTreeNode<T>* AVLtree_first<T>::leftleftRotation(AVLTreeNode<T>* k2)
{
	AVLTreeNode<T>* k1;

	k1 = k2->left;
	k2->left = k1->right;
	k1->right = k2;

	k2->height = max(height(k2->left), height(k2->right)) + 1;
	k1->height = max(height(k1->left), k2->height) + 1;
	return k1;
}


/*
	RR:���Ҷ�Ӧ��������ҵ���ת��

	����ֵ:��ת��ĸ��ڵ�
*/
template<typename T>
AVLTreeNode<T>* AVLtree_first<T>::rightrightRotation(AVLTreeNode<T>* k1)
{
	AVLTreeNode<T>* k2;

	k2 = k1->right;
	k1->right = k2->left;
	k2->left = k1;

	k1->height = max(height(k1->right), height(k1->left)) + 1;
	k2->height = max(height(k2->right), k1->height) + 1;
	return k2;
}


/*
	RR:���Ҷ�Ӧ���������˫��ת��

	����ֵ:��ת��ĸ��ڵ�
*/
template<typename T>
AVLTreeNode<T>* AVLtree_first<T>::leftrightRotation(AVLTreeNode<T>* k3)
{
	k3->left = rightrightRotation(k3->left);
	return leftleftRotation(k3);
}

/*
	RR:�����Ӧ���������˫��ת��

	����ֵ:��ת��ĸ��ڵ�
*/
template<typename T>
AVLTreeNode<T>* AVLtree_first<T>::rightleftRotation(AVLTreeNode<T>* k1)
{
	k1->right = leftleftRotation(k1->right);
	return rightrightRotation(k1);
}



/*
	�������뵽AVL���У������ظ��ڵ�

	����˵����
		tree AVL���ĸ��ڵ�
		key ����Ľ��ļ�ֵ
	����ֵ��
		���ڵ�
*/
template<typename T>
AVLTreeNode<T>* AVLtree_first<T>::insert(AVLTreeNode<T>*& tree, T key)
{
	if (tree == nullptr)
	{
		//�½����
		tree = new AVLTreeNode<T>(key);
		if (tree == nullptr)
		{
			cout << "ERROR: create avltree node failed " << endl;
			return nullptr;
		}
	}
	else if (key < tree->key)
	{
		//�������������������
		tree->left = insert(tree->left, key);
		if (height(tree->left) - height(tree->right) == 2)
		{
			if (key < tree->left->key)
				tree = leftleftRotation(tree);
			else
				tree = leftrightRotation(tree);
		}
	}
	else if (key > tree->key)
	{
		//�������������������
		tree->right = insert(tree->right, key);
		if (height(tree->right) - height(tree->left) == 2)
		{
			if (key > tree->right->key)
				tree = rightrightRotation(tree);
			else
				tree = rightleftRotation(tree);
		}
	}
	else { cout << "���ʧ�ܣ������������ͬ�Ľ�㣡\n"; }
	tree->height = max(height(tree->left), height(tree->right)) + 1;
	return tree;
}

template<typename T>
void AVLtree_first<T>::insert(T key) { insert(HeadPoint, key); }

/*
	ɾ����㣨z�������ظ��ڵ�

	����˵����
		tree AVL���ĸ��ڵ�
		z ��ɾ���Ľ��
	����ֵ��
		�����
*/
template<typename T>
AVLTreeNode<T>* AVLtree_first<T>::remove(AVLTreeNode<T>*& tree, AVLTreeNode<T>* z)
{
	//��Ϊ��  ���� û��Ҫɾ���Ľ�㣬ֱ�ӷ���null
	if (tree == nullptr || z == nullptr)
		return nullptr;

	if (z->key < tree->key)    //��ɾ���������������
	{
		tree->left = remove(tree->left, z);
		//ɾ���������avl����ƽ��
		if (height(tree->right) - height(tree->left) == 2)
		{
			AVLTreeNode<T>* r = tree->right;
			if (height(r->right) > height(r->left))
				tree = rightleftRotation(tree);
			else
				tree = rightrightRotation(tree);
		}
	}
	else if (z->key > tree->key)  //��ɾ���������������
	{
		tree->right = remove(tree->right, z);
		//ɾ���������avl����ƽ��
		if (height(tree->left) - height(tree->right) == 2)
		{
			AVLTreeNode<T>* l = tree->left;
			if (height(l->right) > height(l->left))
				tree = leftrightRotation(tree);
			else
				tree = leftleftRotation(tree);
		}
	}
	else       //�ý������Ҫɾ���Ľ��
	{
		//����������Ӷ��ǿ�
		if ((tree->left!= nullptr) && (tree->right != nullptr))
		{
			if (height(tree->left) > height(tree->right))
			{
				AVLTreeNode<T>* max = maximum(tree->left);
				tree->key = max->key;
				tree->left = remove(tree->left, max);
			}
			else
			{
				AVLTreeNode<T>* min = minium(tree->right);
				tree->key = min->key;
				tree->right = remove(tree->right, min);
			}
		}
		else
		{
			AVLTreeNode<T>* tmp = tree;
			tree = (tree->left != nullptr)? tree->left:tree->right;
			delete tmp;
		}
	}
	
	return tree;
}

template<typename T>
void AVLtree_first<T>::remove(T key)
{
	AVLTreeNode<T>* z;
	if ((z = search(HeadPoint, key)) != nullptr)
		HeadPoint = remove(HeadPoint, z);
}

//����AVL��
template<typename T>
void AVLtree_first<T>::destory(AVLTreeNode<T>*& tree)
{
	if (tree == nullptr)
		return;
	else
	{
		destory(tree->left);
		destory(tree->right);
		delete tree;
	}
}

template<typename T>
void AVLtree_first<T>::destory() { destory(HeadPoint); }

//��ӡ���������
template<typename T>
void AVLtree_first<T>::print(AVLTreeNode<T>* tree, T key, int direction)
{
	if (tree != nullptr)
	{
		if (direction == 0)   //tree�Ǹ��ڵ�
			cout << setw(2) << tree->key << "  is root" << endl;
		else                //tree�Ƿ�֧���
			cout << setw(2) << tree->key << " is" << setw(2) << key << "'s" << setw(12) << (direction == 1 ? " right child " : " left child ") << endl;
		print(tree->left, tree->key, -1);
		print(tree->right, tree->key, 1);
	}
}

template<typename T>
void AVLtree_first<T>::print()
{
	if (HeadPoint != nullptr)
		print(HeadPoint, HeadPoint->key, 0);
}