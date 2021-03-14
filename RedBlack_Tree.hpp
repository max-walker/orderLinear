#pragma once
#include "headfile.hpp"

enum RBTColor { Red, BLACK };

template<typename T>
class RBTnode
{
public:
	RBTColor color;   //颜色
	T keyval = {};         //关键值
	RBTnode<T>* parent;   //红黑树需要有双亲指针
	RBTnode<T>* left;
	RBTnode<T>* right;
	
	RBTnode(T value,RBTColor c, RBTnode* p, RBTnode* l, RBTnode* r) :keyval(value), parent(p), right(r), left(l),color(c) {}
};

template<typename T>
class RBTree
{
private:
	RBTnode<T>* mRoot; //根节点

public:
	RBTree();
	RBTree(const vector<int>& s);
	~RBTree();
	//树的遍历
	void PreOrder();
	void InOrder();
	void PortOrder();

	//（递归实现）查找红黑树中键值为key的节点
	RBTnode<T>* search(T key);
	//（非递归实现）查找红黑树中键值为key的节点
	RBTnode<T>* iterativesearch(T key);

	//查找最小节点，返回最小节点的键值
	T minimum();
	//查找最大节点，返回最大节点的键值
	T maximum();

	//将结点（键值为key）插入红黑树中
	void insert(T key);

	//删除结点中关键值为key的
	void remove(T key);

	//销毁红黑树
	void destory();

	//打印红黑树
	void print();

	//找到结点（x）的后继结点，即，查找“红黑树中数据大于该结点”的“最小节点”
	RBTnode<T>* successor(RBTnode<T>* x);

	//找到结点（x）的前驱结点，即，查找“红黑树中数据小于该结点”的“最大节点”
	RBTnode<T>* predecessor(RBTnode<T>* x);

private:
	//遍历
	void PreOrder(RBTnode<T>* tree) const;
	void PortOrder(RBTnode<T>* tree)const;
	void InOrder(RBTnode<T>* tree)const;

	//（递归实现）查找红黑树中键值为key的节点
	RBTnode<T>* search(RBTnode<T>* tree, T key)const;
	//（非递归实现）查找红黑树中键值为key的节点
	RBTnode<T>* iterativesearch(RBTnode<T>* tree, T key)const;

	//查找最大节点，返回最大节点
	RBTnode<T>* maximum(RBTnode<T>* tree);

	//查找最小结点，返回最小结点
	RBTnode<T>* minimum(RBTnode<T>* tree);

	//左旋
	void leftRotate(RBTnode<T>*& root, RBTnode<T>* x);
	//右旋
	void rightRotate(RBTnode<T>*& root, RBTnode<T>* y);
	//插入函数
	void insert(RBTnode<T>*& root, RBTnode<T>* node);
	//插入修正函数
	void insertFixUp(RBTnode<T>*& root, RBTnode<T>* node);
	//删除函数
	void remove(RBTnode<T>*& root, RBTnode<T>* node);
	//删除修正函数
	void removeFixUp(RBTnode<T>*& root, RBTnode<T>* node, RBTnode<T>* parent);

	//销毁红黑树
	void destory(RBTnode<T>*& tree);

	//打印红黑树
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

//前序遍历红黑树
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

//中序遍历红黑树
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

//后序遍历红黑树
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

//（递归实现）查找红黑树中键值为key的节点
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

//（非递归实现）查找红黑树中键值为key的节点
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

//查找最小结点，返回tree为根节点的红黑树的最小结点
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

//查找最大节点，返回tree为根节点的最小结点
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


//找到结点（x）的后继结点，即，查找“红黑树中数据大于该结点”的“最小节点”
template<typename T>
RBTnode<T>* RBTree<T>::successor(RBTnode<T>* x)
{
	//如果x存在右孩子，则“x的后继结点”为“以其右孩子为根的子树的量小结点”
	if (x->right != nullptr)
		return minimum(x->right);

	//如果x没有右孩子，则有下面两种可能
	//x为一个结点的左孩子，那么它的后继就是它双亲
	//x是一个右孩子,则查找“x的最低的父节点，并且该父节点要具有左孩子”，找到的这个“最低的父节点”就是“x的后继结点”
	RBTnode<T>* y = x->parent;
	while (y!=nullptr&&(x==y->right))
	{
		x = y;
		y = y->parent;
	}
	return y;
}

//找到结点（x）的前驱结点，即，查找“红黑树中数据小于该结点”的“最大节点”
template<typename  T>
RBTnode<T>* RBTree<T>::predecessor(RBTnode<T>* x)
{
	//如果x存在左孩子，则“x的后继结点”为“以其左孩子为根的子树的最大结点”
	if (x->left != nullptr)
		return maximum(x->left);
	//如果x没有左孩子，则有下面两种可能
	//x为一个结点的右孩子，那么它的后继就是它双亲
	//x是一个左孩子,则查找“x的最低的父节点，并且该父节点要具有右孩子”，找到的这个“最低的父节点”就是“x的后继结点”
	RBTnode<T>* y = x->parent;
	while ((y!=nullptr)&&(y->left==x))
	{
		x = y;
		y = y->parent;
	}
	return y;
}

/*

* 对红黑树的节点(x)进行左旋转
 *
 * 左旋示意图(对节点x进行左旋)：
 *      px                              px
 *     /                               /
 *    x                               y
 *   /  \      --(左旋)-->           / \                
 *  lx   y                          x  ry
 *     /   \                       /  \
 *    ly   ry                     lx  ly
*/
//左旋
template<typename T>
void RBTree<T>::leftRotate(RBTnode<T>*& root, RBTnode<T>* x)
{
	//设置x的右孩子为y
	RBTnode<T>* y = x->right;

	//将 “ y的左孩子 ” 设为 “x的右孩子”
	//如果y的左孩子非空，将“x”设为“y的左孩子的父亲”
	x->right = y->left;
	if (x->left != nullptr)
		y->left->parent = x;

	y->parent = x->parent;
	if (x->parent == nullptr)
		root = y;   //如果x的父亲为空，则将y设为根节点
	else
	{
		if (x->parent->left == x)
			x->parent->left = y;      //如果 x是它父亲节的左孩子，则将y设为“x的父亲节点的左孩子”
		else
			x->parent->right = y;	  //如果 x是它父亲节的右孩子，则将y设为“x的父亲节点的右孩子”
	}
	y->left = x;
	x->parent = y;
}

/*
* 对红黑树的节点(y)进行右旋转
*
* 右旋示意图(对节点y进行左旋)：
*            py                               py
*           /                                /
*          y                                x
*         /  \      --(右旋)-->            /  \                     
*        x   ry                           lx   y
*       / \                                   / \                   
*      lx  rx                                rx  ry
*/
//右旋
template<typename T>
void RBTree<T>::rightRotate(RBTnode<T>*& root, RBTnode<T>* y)
{
	//设置x是当前节点的左孩子
	RBTnode<T>* x = y->left;

	//将 “x的右孩子” 设为 “y的左孩子”
	//如果x的右孩子不为空的话，将 y 设为 x 的右孩子的父亲
	y->left = x->right;
	if (x->right != nullptr)
		x->right->parent = y;

	x->parent = y->parent;
	if (y->parent == nullptr)
	{
		root = x;     //如果x的父亲为空，则将y设为根节点
	}
	else
	{
		if (y == y->parent->right)
			y->parent->right = x;    //如果 y是它父亲节的右孩子，则将x设为“y的父亲节点的右孩子”
		else
			y->parent->left = x;     //如果 y是它父亲节的左孩子，则将x设为“y的父亲节点的左孩子”
	}
	x->right = y;
	y->parent = x;
}

/*
	红黑树插入修正函数

	在向红黑树插入节点之后（失去平衡），再调用该函数
	目的将它重新塑造成一颗红黑树

	参数说明：
		root 红黑树的根
		node 插入的节点
*/
//插入修正函数
template<typename T>
void RBTree<T>::insertFixUp(RBTnode<T>*& root, RBTnode<T>* node)
{
	RBTnode<T>* parent, * gparent;

	//若“父节点存在，并且父节点的颜色为红色”
	while ((parent = node->parent) && parent->color == Red)
	{
		gparent = parent->parent;

		//若“父节点”是“祖父节点的左孩子”
		if (parent == gparent->left)
		{
			//case 1条件：叔叔节点的颜色是红色
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

			//case 2条件：叔叔节点的颜色黑色，并且当前节点是右孩子
			if (parent->right == node)
			{
				RBTnode<T>* tmp;
				leftRotate(root, parent);
				tmp = parent;
				parent = node;
				node = tmp;
			}
			
			//case 3条件：叔叔是黑色，并且当前节点是左孩子
			parent->color = BLACK;
			gparent->color = Red;
			rightRotate(root, gparent);
		}
		else //若“z的父节点”是“z的祖父节点的右孩子”
		{
			// case 1条件:叔叔节点是红色
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
			//case 2条件：叔叔是黑色，并且当前节点是左孩子
			if (parent->left == node)
			{
				RBTnode<T>* tmp;
				rightRotate(root, parent);
				tmp = parent;
				parent = node;
				node = tmp;
			}

			//case 3条件:叔叔是黑色，并且当前节点是右孩子
			parent->color = BLACK;
			gparent->color = Red;
			leftRotate(root, gparent);
		}
	}
	//将根节点颜色设置为黑色
	root->color = BLACK;
}

/*
	将结点插入到红黑树中
	参数说明：
		root 红黑树的根节点
		node 插入的结点
*/
template<typename T>
void RBTree<T>::insert(RBTnode<T>*& root, RBTnode<T>* node)
{
	RBTnode<T>* y = nullptr;
	RBTnode<T>* x = root;

	//1. 将红黑树当做一颗二叉查找树，将结点添加到二叉查找树中
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

	// 2.设置结点的颜色为红色
	node->color = Red;
	// 3.将它重新修正为一颗红黑树
	insertFixUp(root, node);
}

template<typename T>
void RBTree<T>::insert(T key)
{
	RBTnode<T>* z = nullptr;
	
	//如果新建结点失败，则返回
	if ((z = new RBTnode<T>(key, BLACK, nullptr, nullptr, nullptr)) == nullptr)
	{
		cout << "新建结点失败";
		return;
	}
	insert(mRoot, z);
}

/*
	红黑树删除修正函数

	在从红黑树中删除插入节点之后（红黑树失去平衡），再调用函数；
	目的是让其重新成为一颗红黑树

	参数说明：
		root 红黑树的根
		node 待修正的节点
*/
//红黑树删除修正函数
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
				//case 1: x的兄弟w是红色的
				other->color = BLACK;
				parent->color = Red;
				leftRotate(root, parent);
				other = parent->right;
			}
			if ((!other->left || other->left->color == BLACK) && (!other->right || other->right->color == BLACK))
			{
				//case 2: x的兄弟w是黑色，并且w的两个孩子都是黑色的
				other->color = Red;
				node = parent;
				parent = node->parent;
			}
			else
			{
				if (!other->right || other->color == BLACK)
				{
					//case 3:x的兄弟w是黑色的，并且w的左孩子是红色的，右孩子是为黑色
					other->left->color = BLACK;
					other->color = Red;
					rightRotate(root, other);
					other = parent->right;
				}
				//case 4: x的兄弟w是黑色的，并且w的右孩子是红色的，左孩子任意颜色
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
				//case 1:x的兄弟w是红色的
				other->color = BLACK;
				parent->color = Red;
				rightRotate(root, parent);
				other = parent->left;
			}
			if ((!other->left || other->left->color == BLACK) && (!other->right || other->right->color == BLACK))
			{
				//case 2：x的兄弟w是黑色，且w的两个孩子也都是黑色的
				other->color = Red;
				node = parent;
				parent = node->parent;
			}
			else
			{
				if (!other->left || other->left->color == BLACK)
				{
					// case 3: x的兄弟w是黑色，并且w的左孩子是红色，右孩子是黑色
					other->right->color = BLACK;
					other->color = Red;
					leftRotate(root, other);
					other = parent->left;
				}
				//case 4: x的兄弟w是黑色的，并且w的右孩子是红色的，左孩子任意颜色
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
	删除结点的函数，并返回被删除的节点

	参数说明：
		root 红黑树的根节点
		node 删除的节点
*/
template<typename T>
void RBTree<T>::remove(RBTnode<T>*& root, RBTnode<T>* node)
{
	RBTnode<T>* child, * parent;
	RBTColor color;

	//被删除结点的“左右孩子都不为空”情况
	if ((node->left != nullptr) && (node->right != nullptr))
	{
		//被删除结点的后继结点（被称为“取代结点”）
		//用它来取代“被删结点”的位置，然后再将“被删结点”去掉
		RBTnode<T>* replaces = node;

		//获取后继结点
		replaces = replaces->right;
		while (replaces->left != nullptr)
			replaces = replaces->left;

		//"node结点"不是根节点（只有根节点不存在父节点）
		if (node->parent)
		{
			if (node->parent->left == node)
				node->parent->left = replaces;
			else
				node->parent->right = replaces;
		}
		else  //“node结点是根节点” 更根节点
			root = replaces;

		//child是"取代结点"的右孩子，也需要“调整的节点”
		//“取代结点”肯定不存在左孩子！因为它是一个后继结点
		child = replaces->right;
		parent = replaces->parent;
		//保存“取代结点”的颜色
		color = replaces->color;

		//“被删除结点”是“它的后继结点的父节点”
		if (parent == node)
			parent = replaces;
		else
		{
			//child不为空
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
	//保存“取代结点的颜色”
	color = node->color;

	if (child)
		child->parent = parent;
	//“node结点”不是根节点
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
	删除红黑树中键值为key的节点
	参数说明：
		tree 红黑树的根节点
*/
template<typename T>
void RBTree<T>::remove(T key)
{
	RBTnode<T>* node;

	//查找key对应的节点，找到就删除结点
	if ((node = search(mRoot, key)) != nullptr)
		remove(mRoot, node);
}


//销毁红黑树
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
	打印“红黑树”
		key --结点的值
		direction  0 表示该节点为根节点
				  -1 表示该节点是它的父节点的左孩子
				   1 表示该节点是它的父节点的右孩子
*/
template<typename T>
void RBTree<T>::print(RBTnode<T>* tree, T key, int direction)
{
	if (tree != nullptr)
	{
		if (direction == 0)	//tree是根节点
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