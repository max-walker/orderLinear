#pragma once
#include "headfile.hpp"
using namespace std;

struct BTreeNode
{
	int date;
	BTreeNode* Tright, * Tleft;
	BTreeNode() { this->date = {}; Tright = Tleft = nullptr; }
	BTreeNode(int newone) :date(newone) { Tright = Tleft = nullptr; }
	BTreeNode(int newone, BTreeNode* l, BTreeNode* r) :date(newone), Tright(r), Tleft(l) {}
};

class B_S_Tree
{
public:
	//构建二叉排序树
	B_S_Tree(vector<int> newone,char n=' ') {
		if (n == ' ')
			HeadPoint = createBST(newone);
		else
		{
			sort(begin(newone), end(newone));
			HeadPoint = createBST(newone);
		}
	} 
	B_S_Tree() { }                                               //空树
	~B_S_Tree() { Release(HeadPoint); cout << "\n已经释放内存\n"; }                          //销毁树用的
	void InOrder() { inorder(HeadPoint); }                        //中序遍历
	void ProOrder() { ProOrder(HeadPoint); }                     //前序遍历
	void PortOrder() { PortOrder(HeadPoint); }                   //后序遍历
	//类构造函数以外的构造函数
	void building(vector<int> newone,char n=' ')
	{ 
		if (n == ' ') {
			HeadPoint = createBST(newone);
		}
		else
		{
			sort(begin(newone), end(newone));
			HeadPoint = createBST(newone);
		}
	}   
	bool search_date(int targe);                                //寻找数据是不是在二叉树中
	void insert_TD(int theint);                                 //插入数据
	void delete_TD(const int& theint);                                 //删除数据

private:
	BTreeNode* HeadPoint = nullptr;
	void inorder(BTreeNode* bt);
	void ProOrder(BTreeNode* bt);
	void PortOrder(BTreeNode* bt);
	void Release(BTreeNode* bt);
	BTreeNode* createBST(const vector<int>& newone);
};
void B_S_Tree::ProOrder(BTreeNode* bt)
{
	if (bt == nullptr)return;
	cout << bt->date << " ";
	ProOrder(bt->Tleft);
	ProOrder(bt->Tright);
}

void B_S_Tree::inorder(BTreeNode* bt)
{
	if (bt == nullptr)return;
	inorder(bt->Tleft);
	cout << bt->date<<" ";
	inorder(bt->Tright);
}

void B_S_Tree::PortOrder(BTreeNode* bt)
{
	if (bt == nullptr)return;
	PortOrder(bt->Tleft);
	PortOrder(bt->Tright);
	cout << bt->date << " ";
}

BTreeNode* B_S_Tree::createBST(const vector<int>& newone)
{
	if (newone.size() == 0)return nullptr;
	if (newone.size() == 1)return new BTreeNode(newone[0]);
	int middle = newone.size() / 2;

	BTreeNode* root = new BTreeNode(newone[middle]);
	vector<int> nums_left(newone.begin(), newone.begin() + middle);
	vector<int> nums_right((newone.begin() + middle + 1), newone.end());
	root->Tleft = createBST(nums_left);
	root->Tright = createBST(nums_right);
	return root;
}

void B_S_Tree::Release(BTreeNode* bt)
{
	if (bt == nullptr)return;
	else
	{
		Release(bt->Tleft);
		Release(bt->Tright);
		delete bt;
	}
}

bool B_S_Tree::search_date(int targe)
{
	BTreeNode* temp = HeadPoint;
	while (temp!=nullptr)
	{
		if (targe > HeadPoint->date)
			HeadPoint = HeadPoint->Tright;
		else if (targe < HeadPoint->date)
			HeadPoint = HeadPoint->Tleft;
		else return true;   //上述两种情况都没遇到，就代表与值相等
	}
	return false;           //没找到相匹配的数值
}

void B_S_Tree::insert_TD(int theint)
{
	BTreeNode* p = HeadPoint,*pp=nullptr;
	while (p!=nullptr)
	{
		pp = p;
		if (theint > p->date)
			p = p->Tright;
		else if (theint < p->date)
			p = p->Tleft;
		else return;      //发现已经存在数据了
	}
	

	//以下是没发现数据，在二叉线索树插入数据
	BTreeNode* newnode = new BTreeNode(theint);
	if (newnode != nullptr && HeadPoint != nullptr)
	{
		if (theint > pp->date)
			pp->Tright = newnode;
		else
			pp->Tleft = newnode;
	}
	else HeadPoint = newnode;    //插入空树
}

void B_S_Tree::delete_TD(const int& theint)
{
	BTreeNode* point = HeadPoint, * pp = nullptr;
	while (point!=nullptr&&point->date!=theint)
	{
		pp = point;
		if (theint > point->date)
			point = point->Tright;
		else
			point = point->Tleft;
	}
	if (point == nullptr) return;         //没找到数据，所以退出

	//重新组织树的结构
	//有三种删除的情况，应该分别对应处理

	if (point->Tleft != nullptr && point->Tright != nullptr)
	{
		//当要删除的节点的两个孩子都不为空的时候
		srand(time(0));
		BTreeNode* s = nullptr, * ps = point;
		if (rand() % 2)
		{
			//移动到右子树的最小元素中
			s = point->Tright;
			while (s->Tleft != nullptr)
			{
				ps = s;
				s = s->Tleft;
			}
		}
		else
		{
			//移到目标左子树最大元素中
			s = point->Tleft;
			while (s->Tright!=nullptr)
			{
				ps = s;
				s = s->Tright;
			}
		}


		BTreeNode* q = new BTreeNode(s->date, point->Tleft, point->Tright);
		if (pp == nullptr)HeadPoint = q;
		else if (point == HeadPoint->Tleft) pp->Tleft = q;
		else pp->Tright = q;

		if (ps == point) pp = q;
		else pp = ps;
		delete point;
		point = s;
	}

	//P 最多有一个孩子
	//把孩子指针放在C
	BTreeNode* c;
	if (point->Tleft != nullptr)
		c = point->Tleft;
	else
		c = point->Tright;

	//删除Point
	if (point == HeadPoint)
		HeadPoint = c;
	else
	{
		if (point == pp->Tleft)
			pp->Tleft = c;
		else
			pp->Tright = c;
	}
	delete point;
}