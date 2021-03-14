#pragma once
#include "headfile.hpp"

enum RBTColor { Red, BLACK };

template<typename T>
class RBTnode
{
public:
	RBTColor color;   //��ɫ
	T keyval = {};         //�ؼ�ֵ
	RBTnode<T>* parent;   //�������Ҫ��˫��ָ��
	RBTnode<T>* left;
	RBTnode<T>* right;
	
	RBTnode(T value,RBTColor c, RBTnode* p, RBTnode* l, RBTnode* r) :keyval(value), parent(p), right(r), left(l),color(c) {}
};

template<typename T>
class RBTree
{
private:
	RBTnode<T>* mRoot; //���ڵ�

public:
	RBTree();
	RBTree(const vector<int>& s);
	~RBTree();
	//���ı���
	void PreOrder();
	void InOrder();
	void PortOrder();

	//���ݹ�ʵ�֣����Һ�����м�ֵΪkey�Ľڵ�
	RBTnode<T>* search(T key);
	//���ǵݹ�ʵ�֣����Һ�����м�ֵΪkey�Ľڵ�
	RBTnode<T>* iterativesearch(T key);

	//������С�ڵ㣬������С�ڵ�ļ�ֵ
	T minimum();
	//�������ڵ㣬�������ڵ�ļ�ֵ
	T maximum();

	//����㣨��ֵΪkey������������
	void insert(T key);

	//ɾ������йؼ�ֵΪkey��
	void remove(T key);

	//���ٺ����
	void destory();

	//��ӡ�����
	void print();

	//�ҵ���㣨x���ĺ�̽�㣬�������ҡ�����������ݴ��ڸý�㡱�ġ���С�ڵ㡱
	RBTnode<T>* successor(RBTnode<T>* x);

	//�ҵ���㣨x����ǰ����㣬�������ҡ������������С�ڸý�㡱�ġ����ڵ㡱
	RBTnode<T>* predecessor(RBTnode<T>* x);

private:
	//����
	void PreOrder(RBTnode<T>* tree) const;
	void PortOrder(RBTnode<T>* tree)const;
	void InOrder(RBTnode<T>* tree)const;

	//���ݹ�ʵ�֣����Һ�����м�ֵΪkey�Ľڵ�
	RBTnode<T>* search(RBTnode<T>* tree, T key)const;
	//���ǵݹ�ʵ�֣����Һ�����м�ֵΪkey�Ľڵ�
	RBTnode<T>* iterativesearch(RBTnode<T>* tree, T key)const;

	//�������ڵ㣬�������ڵ�
	RBTnode<T>* maximum(RBTnode<T>* tree);

	//������С��㣬������С���
	RBTnode<T>* minimum(RBTnode<T>* tree);

	//����
	void leftRotate(RBTnode<T>*& root, RBTnode<T>* x);
	//����
	void rightRotate(RBTnode<T>*& root, RBTnode<T>* y);
	//���뺯��
	void insert(RBTnode<T>*& root, RBTnode<T>* node);
	//������������
	void insertFixUp(RBTnode<T>*& root, RBTnode<T>* node);
	//ɾ������
	void remove(RBTnode<T>*& root, RBTnode<T>* node);
	//ɾ����������
	void removeFixUp(RBTnode<T>*& root, RBTnode<T>* node, RBTnode<T>* parent);

	//���ٺ����
	void destory(RBTnode<T>*& tree);

	//��ӡ�����
	void print(RBTnode<T>* tree, T key, int direction);
};

template<typename T>
RBTree<T>::RBTree()
{
	mRoot = nullptr;
}

template<typename T>
RBTree<T>::RBTree(const vector<int>& s)
{
	if (!s.empty())
	{
		for (auto t : s)
			this->insert(t);
	}
}

template<typename T>
RBTree<T>::~RBTree()
{
	destory();
}

//ǰ����������
template<typename T>
void RBTree<T>::PreOrder(RBTnode<T>* tree)const
{
	if (tree == nullptr)return;
	else
	{
		cout << tree->keyval << " ";
		PreOrder(tree->left);
		PortOrder(tree->right);
	}
}

template<typename T>
void RBTree<T>::PreOrder()
{
	PreOrder(mRoot);
}

//������������
template<typename T>
void RBTree<T>::InOrder(RBTnode<T>* tree)const
{
	if (tree != nullptr)
	{
		InOrder(tree->left);
		cout << tree->keyval << " ";
		InOrder(tree->right);
	}
}

template<typename T>
void RBTree<T>::InOrder()
{
	InOrder(mRoot);
}

//������������
template<typename T>
void RBTree<T>::PortOrder(RBTnode<T>* tree) const
{
	if (tree != nullptr)
	{
		PortOrder(tree->left);
		PortOrder(tree->right);
		cout << tree->keyval << " ";
	}
}

template<typename T>
void RBTree<T>::PortOrder()
{
	PortOrder(mRoot);
}

//���ݹ�ʵ�֣����Һ�����м�ֵΪkey�Ľڵ�
template<typename T>
RBTnode<T>* RBTree<T>::search(RBTnode<T>* tree, T key)const
{
	if (tree == nullptr || tree->keyval == key)return tree;

	if (key < tree->keyval)
		return search(tree->left, key);
	else
		return search(tree->right, key);
}

template<typename T>
RBTnode<T>* RBTree<T>::search(T key)
{
	return search(mRoot, key);
}

//���ǵݹ�ʵ�֣����Һ�����м�ֵΪkey�Ľڵ�
template<typename T>
RBTnode<T>* RBTree<T>::iterativesearch(RBTnode<T>* tree, T key)const
{
	while ((tree!=nullptr)&&(tree->keyval!=key))
	{
		if (tree->keyval < key)
			tree = tree->right;
		else
			tree = tree->left;
	}
	return tree;
}

template<typename T>
RBTnode<T>* RBTree<T>::iterativesearch(T key)
{
	return iterativesearch(mRoot,key);
}

//������С��㣬����treeΪ���ڵ�ĺ��������С���
template<typename T>
RBTnode<T>* RBTree<T>::minimum(RBTnode<T>* tree)
{
	if (tree == nullptr)return nullptr;

	while (tree->left!=nullptr)
	{
		tree = tree->left;
	}
	return tree;
}

template<typename T>
T RBTree<T>::minimum()
{
	RBTnode<T>* p = minimum(mRoot);
	if (p != nullptr)
		return p->keyval;
	return T(NULL);
}

//�������ڵ㣬����treeΪ���ڵ����С���
template<typename T>
RBTnode<T>* RBTree<T>::maximum(RBTnode<T>* tree)
{
	if (tree == nullptr)return nullptr;

	while (tree->right != nullptr)
		tree = tree->right;
	return tree;
}

template<typename T>
T RBTree<T>::maximum()
{
	RBTnode<T>* p = maximum(mRoot);
	if (p != nullptr)
		return p->keyval;
	return T(NULL);
}


//�ҵ���㣨x���ĺ�̽�㣬�������ҡ�����������ݴ��ڸý�㡱�ġ���С�ڵ㡱
template<typename T>
RBTnode<T>* RBTree<T>::successor(RBTnode<T>* x)
{
	//���x�����Һ��ӣ���x�ĺ�̽�㡱Ϊ�������Һ���Ϊ������������С��㡱
	if (x->right != nullptr)
		return minimum(x->right);

	//���xû���Һ��ӣ������������ֿ���
	//xΪһ���������ӣ���ô���ĺ�̾�����˫��
	//x��һ���Һ���,����ҡ�x����͵ĸ��ڵ㣬���Ҹø��ڵ�Ҫ�������ӡ����ҵ����������͵ĸ��ڵ㡱���ǡ�x�ĺ�̽�㡱
	RBTnode<T>* y = x->parent;
	while (y!=nullptr&&(x==y->right))
	{
		x = y;
		y = y->parent;
	}
	return y;
}

//�ҵ���㣨x����ǰ����㣬�������ҡ������������С�ڸý�㡱�ġ����ڵ㡱
template<typename  T>
RBTnode<T>* RBTree<T>::predecessor(RBTnode<T>* x)
{
	//���x�������ӣ���x�ĺ�̽�㡱Ϊ����������Ϊ��������������㡱
	if (x->left != nullptr)
		return maximum(x->left);
	//���xû�����ӣ������������ֿ���
	//xΪһ�������Һ��ӣ���ô���ĺ�̾�����˫��
	//x��һ������,����ҡ�x����͵ĸ��ڵ㣬���Ҹø��ڵ�Ҫ�����Һ��ӡ����ҵ����������͵ĸ��ڵ㡱���ǡ�x�ĺ�̽�㡱
	RBTnode<T>* y = x->parent;
	while ((y!=nullptr)&&(y->left==x))
	{
		x = y;
		y = y->parent;
	}
	return y;
}

/*

* �Ժ�����Ľڵ�(x)��������ת
 *
 * ����ʾ��ͼ(�Խڵ�x��������)��
 *      px                              px
 *     /                               /
 *    x                               y
 *   /  \      --(����)-->           / \                
 *  lx   y                          x  ry
 *     /   \                       /  \
 *    ly   ry                     lx  ly
*/
//����
template<typename T>
void RBTree<T>::leftRotate(RBTnode<T>*& root, RBTnode<T>* x)
{
	//����x���Һ���Ϊy
	RBTnode<T>* y = x->right;

	//�� �� y������ �� ��Ϊ ��x���Һ��ӡ�
	//���y�����ӷǿգ�����x����Ϊ��y�����ӵĸ��ס�
	x->right = y->left;
	if (x->left != nullptr)
		y->left->parent = x;

	y->parent = x->parent;
	if (x->parent == nullptr)
		root = y;   //���x�ĸ���Ϊ�գ���y��Ϊ���ڵ�
	else
	{
		if (x->parent->left == x)
			x->parent->left = y;      //��� x�������׽ڵ����ӣ���y��Ϊ��x�ĸ��׽ڵ�����ӡ�
		else
			x->parent->right = y;	  //��� x�������׽ڵ��Һ��ӣ���y��Ϊ��x�ĸ��׽ڵ���Һ��ӡ�
	}
	y->left = x;
	x->parent = y;
}

/*
* �Ժ�����Ľڵ�(y)��������ת
*
* ����ʾ��ͼ(�Խڵ�y��������)��
*            py                               py
*           /                                /
*          y                                x
*         /  \      --(����)-->            /  \                     
*        x   ry                           lx   y
*       / \                                   / \                   
*      lx  rx                                rx  ry
*/
//����
template<typename T>
void RBTree<T>::rightRotate(RBTnode<T>*& root, RBTnode<T>* y)
{
	//����x�ǵ�ǰ�ڵ������
	RBTnode<T>* x = y->left;

	//�� ��x���Һ��ӡ� ��Ϊ ��y�����ӡ�
	//���x���Һ��Ӳ�Ϊ�յĻ����� y ��Ϊ x ���Һ��ӵĸ���
	y->left = x->right;
	if (x->right != nullptr)
		x->right->parent = y;

	x->parent = y->parent;
	if (y->parent == nullptr)
	{
		root = x;     //���x�ĸ���Ϊ�գ���y��Ϊ���ڵ�
	}
	else
	{
		if (y == y->parent->right)
			y->parent->right = x;    //��� y�������׽ڵ��Һ��ӣ���x��Ϊ��y�ĸ��׽ڵ���Һ��ӡ�
		else
			y->parent->left = x;     //��� y�������׽ڵ����ӣ���x��Ϊ��y�ĸ��׽ڵ�����ӡ�
	}
	x->right = y;
	y->parent = x;
}

/*
	�����������������

	������������ڵ�֮��ʧȥƽ�⣩���ٵ��øú���
	Ŀ�Ľ������������һ�ź����

	����˵����
		root ������ĸ�
		node ����Ľڵ�
*/
//������������
template<typename T>
void RBTree<T>::insertFixUp(RBTnode<T>*& root, RBTnode<T>* node)
{
	RBTnode<T>* parent, * gparent;

	//�������ڵ���ڣ����Ҹ��ڵ����ɫΪ��ɫ��
	while ((parent = node->parent) && parent->color == Red)
	{
		gparent = parent->parent;

		//�������ڵ㡱�ǡ��游�ڵ�����ӡ�
		if (parent == gparent->left)
		{
			//case 1����������ڵ����ɫ�Ǻ�ɫ
			{
				RBTnode<T>* uncle = gparent->right;
				if (uncle && uncle->color == Red)
				{
					uncle->color = BLACK;
					parent->color = BLACK;
					gparent->color = Red;
					node = gparent;
					continue;
				}
			}

			//case 2����������ڵ����ɫ��ɫ�����ҵ�ǰ�ڵ����Һ���
			if (parent->right == node)
			{
				RBTnode<T>* tmp;
				leftRotate(root, parent);
				tmp = parent;
				parent = node;
				node = tmp;
			}
			
			//case 3�����������Ǻ�ɫ�����ҵ�ǰ�ڵ�������
			parent->color = BLACK;
			gparent->color = Red;
			rightRotate(root, gparent);
		}
		else //����z�ĸ��ڵ㡱�ǡ�z���游�ڵ���Һ��ӡ�
		{
			// case 1����:����ڵ��Ǻ�ɫ
			{
				RBTnode<T>* uncle = gparent->left;
				if (uncle && uncle->color == Red)
				{
					uncle->color = BLACK;
					parent->color = BLACK;
					gparent->color = Red;
					node = gparent;
					continue;
				}
			}
			//case 2�����������Ǻ�ɫ�����ҵ�ǰ�ڵ�������
			if (parent->left == node)
			{
				RBTnode<T>* tmp;
				rightRotate(root, parent);
				tmp = parent;
				parent = node;
				node = tmp;
			}

			//case 3����:�����Ǻ�ɫ�����ҵ�ǰ�ڵ����Һ���
			parent->color = BLACK;
			gparent->color = Red;
			leftRotate(root, gparent);
		}
	}
	//�����ڵ���ɫ����Ϊ��ɫ
	root->color = BLACK;
}

/*
	�������뵽�������
	����˵����
		root ������ĸ��ڵ�
		node ����Ľ��
*/
template<typename T>
void RBTree<T>::insert(RBTnode<T>*& root, RBTnode<T>* node)
{
	RBTnode<T>* y = nullptr;
	RBTnode<T>* x = root;

	//1. �����������һ�Ŷ�����������������ӵ������������
	while (x != nullptr)
	{
		y = x;
		if (node->keyval < x->keyval)
			x = x->left;
		else
			x = x->right;
	}

	node->parent = y;
	if (y != nullptr)
	{
		if (node->keyval < y->keyval)
			y->left = node;
		else
			y->right = node;
	}
	else
		root = node;

	// 2.���ý�����ɫΪ��ɫ
	node->color = Red;
	// 3.������������Ϊһ�ź����
	insertFixUp(root, node);
}

template<typename T>
void RBTree<T>::insert(T key)
{
	RBTnode<T>* z = nullptr;
	
	//����½����ʧ�ܣ��򷵻�
	if ((z = new RBTnode<T>(key, BLACK, nullptr, nullptr, nullptr)) == nullptr)
	{
		cout << "�½����ʧ��";
		return;
	}
	insert(mRoot, z);
}

/*
	�����ɾ����������

	�ڴӺ������ɾ������ڵ�֮�󣨺����ʧȥƽ�⣩���ٵ��ú�����
	Ŀ�����������³�Ϊһ�ź����

	����˵����
		root ������ĸ�
		node �������Ľڵ�
*/
//�����ɾ����������
template<typename T>
void RBTree<T>::removeFixUp(RBTnode<T>*& root, RBTnode<T>* node, RBTnode<T>* parent)
{
	RBTnode<T>* other;
	while ((!node || node->color == BLACK) && node != root)
	{
		if (parent->left == node)
		{
			other = parent->right;
			if (other->color == Red)
			{
				//case 1: x���ֵ�w�Ǻ�ɫ��
				other->color = BLACK;
				parent->color = Red;
				leftRotate(root, parent);
				other = parent->right;
			}
			if ((!other->left || other->left->color == BLACK) && (!other->right || other->right->color == BLACK))
			{
				//case 2: x���ֵ�w�Ǻ�ɫ������w���������Ӷ��Ǻ�ɫ��
				other->color = Red;
				node = parent;
				parent = node->parent;
			}
			else
			{
				if (!other->right || other->color == BLACK)
				{
					//case 3:x���ֵ�w�Ǻ�ɫ�ģ�����w�������Ǻ�ɫ�ģ��Һ�����Ϊ��ɫ
					other->left->color = BLACK;
					other->color = Red;
					rightRotate(root, other);
					other = parent->right;
				}
				//case 4: x���ֵ�w�Ǻ�ɫ�ģ�����w���Һ����Ǻ�ɫ�ģ�����������ɫ
				other->color = parent->color;
				parent->color = BLACK;
				other->right->color = BLACK;
				leftRotate(root, parent);
				node = root;
				break;
			}
		}
		else
		{
			other = parent->left;
			if (other->color == Red)
			{
				//case 1:x���ֵ�w�Ǻ�ɫ��
				other->color = BLACK;
				parent->color = Red;
				rightRotate(root, parent);
				other = parent->left;
			}
			if ((!other->left || other->left->color == BLACK) && (!other->right || other->right->color == BLACK))
			{
				//case 2��x���ֵ�w�Ǻ�ɫ����w����������Ҳ���Ǻ�ɫ��
				other->color = Red;
				node = parent;
				parent = node->parent;
			}
			else
			{
				if (!other->left || other->left->color == BLACK)
				{
					// case 3: x���ֵ�w�Ǻ�ɫ������w�������Ǻ�ɫ���Һ����Ǻ�ɫ
					other->right->color = BLACK;
					other->color = Red;
					leftRotate(root, other);
					other = parent->left;
				}
				//case 4: x���ֵ�w�Ǻ�ɫ�ģ�����w���Һ����Ǻ�ɫ�ģ�����������ɫ
				other->color = parent->color;
				parent->color = BLACK;
				other->left->color = BLACK;
				rightRotate(root, parent);
				node = root;
				break;
			}
		}
	}
	if (node)
		node->color = BLACK;
}

/*
	ɾ�����ĺ����������ر�ɾ���Ľڵ�

	����˵����
		root ������ĸ��ڵ�
		node ɾ���Ľڵ�
*/
template<typename T>
void RBTree<T>::remove(RBTnode<T>*& root, RBTnode<T>* node)
{
	RBTnode<T>* child, * parent;
	RBTColor color;

	//��ɾ�����ġ����Һ��Ӷ���Ϊ�ա����
	if ((node->left != nullptr) && (node->right != nullptr))
	{
		//��ɾ�����ĺ�̽�㣨����Ϊ��ȡ����㡱��
		//������ȡ������ɾ��㡱��λ�ã�Ȼ���ٽ�����ɾ��㡱ȥ��
		RBTnode<T>* replaces = node;

		//��ȡ��̽��
		replaces = replaces->right;
		while (replaces->left != nullptr)
			replaces = replaces->left;

		//"node���"���Ǹ��ڵ㣨ֻ�и��ڵ㲻���ڸ��ڵ㣩
		if (node->parent)
		{
			if (node->parent->left == node)
				node->parent->left = replaces;
			else
				node->parent->right = replaces;
		}
		else  //��node����Ǹ��ڵ㡱 �����ڵ�
			root = replaces;

		//child��"ȡ�����"���Һ��ӣ�Ҳ��Ҫ�������Ľڵ㡱
		//��ȡ����㡱�϶����������ӣ���Ϊ����һ����̽��
		child = replaces->right;
		parent = replaces->parent;
		//���桰ȡ����㡱����ɫ
		color = replaces->color;

		//����ɾ����㡱�ǡ����ĺ�̽��ĸ��ڵ㡱
		if (parent == node)
			parent = replaces;
		else
		{
			//child��Ϊ��
			if (child)
				child->parent = parent;
			parent->left = child;

			replaces->right = node->right;
			node->right->parent = replaces;
		}

		replaces->parent = node->parent;
		replaces->color = node->color;
		replaces->left = node->left;
		node->left->parent = replaces;

		if (color == BLACK)
			removeFixUp(root, child, parent);

		delete node;
		return;
	}
	if (node->left != nullptr)
		child = node->left;
	else
		child = node->right;
	
	parent = node->parent;
	//���桰ȡ��������ɫ��
	color = node->color;

	if (child)
		child->parent = parent;
	//��node��㡱���Ǹ��ڵ�
	if (parent)
	{
		if (parent->left == node)
			parent->left = child;
		else
			parent->right = child;
	}
	else
		root = child;

	if (color == BLACK)
		removeFixUp(root, child, parent);
	delete node;
}

/*
	ɾ��������м�ֵΪkey�Ľڵ�
	����˵����
		tree ������ĸ��ڵ�
*/
template<typename T>
void RBTree<T>::remove(T key)
{
	RBTnode<T>* node;

	//����key��Ӧ�Ľڵ㣬�ҵ���ɾ�����
	if ((node = search(mRoot, key)) != nullptr)
		remove(mRoot, node);
}


//���ٺ����
template<typename T>
void RBTree<T>::destory(RBTnode<T>*& tree)
{
	if (tree == nullptr)
		return;

	if (tree->left != nullptr)
		return destory(tree->left);
	if (tree->right != nullptr)
		return destory(tree->right);
	delete tree;
	tree = nullptr;
}

template<typename T>
void RBTree<T>::destory()
{
	destory(mRoot);
}

/*
	��ӡ���������
		key --����ֵ
		direction  0 ��ʾ�ýڵ�Ϊ���ڵ�
				  -1 ��ʾ�ýڵ������ĸ��ڵ������
				   1 ��ʾ�ýڵ������ĸ��ڵ���Һ���
*/
template<typename T>
void RBTree<T>::print(RBTnode<T>* tree, T key, int direction)
{
	if (tree != nullptr)
	{
		if (direction == 0)	//tree�Ǹ��ڵ�
			cout << setw(2) << tree->keyval << " (B) is root " << endl;
		else
			cout << setw(2) << tree->keyval << ((tree->color == Red) ? "(R)" : "(B)") << " is " << setw(2) << key << "'s " << setw(12) << ((direction == 1) ? " right child " : " left child ") << endl;
		print(tree->left, tree->keyval, -1);
		print(tree->right, tree->keyval, 1);
	}
}

template<typename T>
void RBTree<T>::print()
{
	if (mRoot != nullptr)
		print(mRoot, mRoot->keyval, 0);
}