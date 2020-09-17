#include <iostream>
#include<memory>
using namespace std;
static int i = 0;

template<typename Tpte>
class BinaryTree
{
public:
	class BiNode
	{
	public:
		Tpte data;
		BiNode* righttree, * lefttree;
		BiNode() : righttree(nullptr), lefttree(nullptr) {}
	};
	BinaryTree() { createTermination(); root = Create(); }         //构造函数，调用创建二叉树的函数.
	virtual ~BinaryTree() { Release(root); }  //删除解析函数调用删除动态内存的函数。
	void PreOrder() { Preorder(root); }       //前序遍历
	void InOrder() { Inorder(root); }		  //中序遍历
	void PortOrder() { Portorder(root); }	  //后序遍历
	Tpte Termination;
private:
	void createTermination()
	{
		cout << "输入你的终止条件:";
		cin >> Termination;
		cout << endl;
	}
	void Portorder(BiNode* bt);
	void Inorder(BiNode* bt);
	void Preorder(BiNode* bt);
	void Release(BiNode *bt);
	BiNode* Create()
	{
		BiNode* btree;
		Tpte number;
		cout << "输入节点的数据(" << Termination << "终止条件)：";
		cin >> number;
		if (number == Termination)
		{
			btree = nullptr;
		}
		else
		{
			btree = new BiNode();
			btree->data = number;
			btree->lefttree = Create();
			btree->righttree = Create();
		}
		return btree;
	}
	BiNode* root = nullptr;            //头节点
};

template<typename Tpte>
void BinaryTree<Tpte>::Release(BiNode*bt)   //释放内存的方法
{
	if (bt==nullptr)return;
	else
	{
		Release(bt->lefttree);
		Release(bt->righttree);
		delete bt;
	}
}

template<typename Tpte>
void BinaryTree<Tpte>::Preorder(BiNode* bt)   //前序遍历
{
	if (bt == nullptr) return;
	else
	{
		cout << bt->data << "  ";
		Preorder(bt->lefttree);
		Preorder(bt->righttree);
	}
}

template<typename Tpte>
void BinaryTree<Tpte>::Inorder(BiNode* bt)   //中序遍历
{
	if (bt == nullptr)return;
	else
	{
		Inorder(bt->lefttree);
		cout << bt->data << "  ";
		Inorder(bt->righttree);
	}
}

template<typename Tpte>
void BinaryTree<Tpte>::Portorder(BiNode* bt) //后序遍历
{
	if (bt == nullptr)return;
	else
	{
		Portorder(bt->lefttree);
		Portorder(bt->righttree);
		cout << bt->data << "  ";
	}
}


int main()
{
	BinaryTree<int> inopen = BinaryTree<int>();
	inopen.PreOrder();
	return 0;
}
