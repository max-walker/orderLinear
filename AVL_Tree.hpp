#pragma once
#include "headfile.hpp"
//平衡二叉树，该编主要参考（抄）博客园中的文章编写的平衡二叉树，还要自己写一颗

//这里是完结感谢：这树好几把难哇，特别是删除代码那边。改了又改了，不过看评论说还是有bug。在我短期测试没有bug，那就是没有bug（叉腰）。这棵树是一定要手撕的
//不得不说，现场手撕，那是真的牛逼


//结点构造
template<typename T>
class AVLTreeNode
{
public:
	T key = {};
	AVLTreeNode* left, * right;
	int height;

	//初始化函数
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

	int height();              //获取树的高度
	int max(int a, int b);     //获取树的高度

	//各种序列的遍历
	void PreOrder();
	void InOrder();
	void PostOrder();

	//查找AVL树中的key值的节点
	AVLTreeNode<T>* search(T key);             //递归实现
	AVLTreeNode<T>* iterativsSearch(T key);    //非递归实现

	//查找最小节点：返回最小节点的值
	T minimum();
	//查找最大节点：返回最大节点的值
	T maximum();

	//将节点，节点值为key插入AVL树中
	void insert(T key);

	//删除值为key的节点
	void remove(T key);

	//打印出AVL树
	void print();

	//删除树
	void destory();

private:
	//获取树的高度
	int height(AVLTreeNode<T>* tree);

	//遍历AVL树
	void PreOrder(AVLTreeNode<T>* tree) const;
	void PostOrder(AVLTreeNode<T>* tree) const;
	void InOrder(AVLTreeNode<T>* tree) const;

	//(递归实现) 查找AVL树中值为key的节点
	AVLTreeNode<T>* search(AVLTreeNode<T>* x, T key)const;
	//（非递归实现）查找AVL树中值为key的节点
	AVLTreeNode<T>* iterativsSearch(AVLTreeNode<T>* x, T key)const;

	//返回树中最小key值的节点
	AVLTreeNode<T>* minium(AVLTreeNode<T>* tree);
	//返回树中最大key值的节点
	AVLTreeNode<T>* maximum(AVLTreeNode<T>* tree);

	//LL:左左对应的情况
	AVLTreeNode<T>* leftleftRotation(AVLTreeNode <T>* k2);

	//RR:右右对应的情况
	AVLTreeNode<T>* rightrightRotation(AVLTreeNode <T>* k1);

	//LR：左右对应的情况
	AVLTreeNode<T>* leftrightRotation(AVLTreeNode<T>* k3);

	//RL:右左对应的情况
	AVLTreeNode<T>* rightleftRotation(AVLTreeNode<T>* k1);

	//将新节点（key）插入AVL树中
	AVLTreeNode<T>* insert(AVLTreeNode<T>*& tree, T key);

	//删除AVL树中的节点Z，并返回被删除的节点
	AVLTreeNode<T>* remove(AVLTreeNode<T>*& tree, AVLTreeNode<T>* z);

	//销毁树
	void destory(AVLTreeNode<T>*& tree);

	//打印AVL树
	void print(AVLTreeNode<T>* tree, T key, int direction);
};


//构造函数
template<typename T>
AVLtree_first<T>::AVLtree_first() :HeadPoint(nullptr) {}

//解析函数
template<typename T>
AVLtree_first<T>::~AVLtree_first() { cout << "\n释放内存\n"; destory(HeadPoint); }

//获取树的高度
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

//比较两个key值的大小
template<typename T>
int AVLtree_first<T>::max(int a, int b)
{
	return a > b ? a : b;
}

//遍历平衡二叉树的各种方法：
//前序遍历
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

//中序遍历
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

//后序遍历
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


//（递归实现）查找x树中为key值的节点
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

//（非递归实现）查找x树中为key值的节点
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


//查找最小节点，返回tree为根节点的AVL树的最小节点
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

//查找最大节点，返回tree为根节点的AVL树的最大节点
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
	LL:左左对应的情况（左单旋转）

	返回值:旋转后的根节点
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
	RR:右右对应的情况（右单旋转）

	返回值:旋转后的根节点
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
	RR:左右对应的情况（左双旋转）

	返回值:旋转后的根节点
*/
template<typename T>
AVLTreeNode<T>* AVLtree_first<T>::leftrightRotation(AVLTreeNode<T>* k3)
{
	k3->left = rightrightRotation(k3->left);
	return leftleftRotation(k3);
}

/*
	RR:右左对应的情况（右双旋转）

	返回值:旋转后的根节点
*/
template<typename T>
AVLTreeNode<T>* AVLtree_first<T>::rightleftRotation(AVLTreeNode<T>* k1)
{
	k1->right = leftleftRotation(k1->right);
	return rightrightRotation(k1);
}



/*
	将结点插入到AVL树中，并返回根节点

	参数说明：
		tree AVL树的根节点
		key 插入的结点的键值
	返回值：
		根节点
*/
template<typename T>
AVLTreeNode<T>* AVLtree_first<T>::insert(AVLTreeNode<T>*& tree, T key)
{
	if (tree == nullptr)
	{
		//新建结点
		tree = new AVLTreeNode<T>(key);
		if (tree == nullptr)
		{
			cout << "ERROR: create avltree node failed " << endl;
			return nullptr;
		}
	}
	else if (key < tree->key)
	{
		//插入树的左子树的情况
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
		//插入树的右子树的情况
		tree->right = insert(tree->right, key);
		if (height(tree->right) - height(tree->left) == 2)
		{
			if (key > tree->right->key)
				tree = rightrightRotation(tree);
			else
				tree = rightleftRotation(tree);
		}
	}
	else { cout << "添加失败，不允许添加相同的结点！\n"; }
	tree->height = max(height(tree->left), height(tree->right)) + 1;
	return tree;
}

template<typename T>
void AVLtree_first<T>::insert(T key) { insert(HeadPoint, key); }

/*
	删除结点（z），返回根节点

	参数说明：
		tree AVL树的根节点
		z 待删除的结点
	返回值：
		根结点
*/
template<typename T>
AVLTreeNode<T>* AVLtree_first<T>::remove(AVLTreeNode<T>*& tree, AVLTreeNode<T>* z)
{
	//根为空  或者 没有要删除的结点，直接返回null
	if (tree == nullptr || z == nullptr)
		return nullptr;

	if (z->key < tree->key)    //待删除结点在左子树中
	{
		tree->left = remove(tree->left, z);
		//删除结点后，如果avl树不平衡
		if (height(tree->right) - height(tree->left) == 2)
		{
			AVLTreeNode<T>* r = tree->right;
			if (height(r->right) > height(r->left))
				tree = rightleftRotation(tree);
			else
				tree = rightrightRotation(tree);
		}
	}
	else if (z->key > tree->key)  //待删除结点在右子树中
	{
		tree->right = remove(tree->right, z);
		//删除结点后，如果avl树不平衡
		if (height(tree->left) - height(tree->right) == 2)
		{
			AVLTreeNode<T>* l = tree->left;
			if (height(l->right) > height(l->left))
				tree = leftrightRotation(tree);
			else
				tree = leftleftRotation(tree);
		}
	}
	else       //该结点正是要删除的结点
	{
		//如果两个孩子都非空
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

//销毁AVL树
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

//打印二叉查找树
template<typename T>
void AVLtree_first<T>::print(AVLTreeNode<T>* tree, T key, int direction)
{
	if (tree != nullptr)
	{
		if (direction == 0)   //tree是根节点
			cout << setw(2) << tree->key << "  is root" << endl;
		else                //tree是分支结点
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