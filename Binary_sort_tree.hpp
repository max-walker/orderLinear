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
	//��������������
	B_S_Tree(vector<int> newone,char n=' ') {
		if (n == ' ')
			HeadPoint = createBST(newone);
		else
		{
			sort(begin(newone), end(newone));
			HeadPoint = createBST(newone);
		}
	} 
	B_S_Tree() { }                                               //����
	~B_S_Tree() { Release(HeadPoint); cout << "\n�Ѿ��ͷ��ڴ�\n"; }                          //�������õ�
	void InOrder() { inorder(HeadPoint); }                        //�������
	void ProOrder() { ProOrder(HeadPoint); }                     //ǰ�����
	void PortOrder() { PortOrder(HeadPoint); }                   //�������
	//�๹�캯������Ĺ��캯��
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
	bool search_date(int targe);                                //Ѱ�������ǲ����ڶ�������
	void insert_TD(int theint);                                 //��������
	void delete_TD(const int& theint);                                 //ɾ������

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
		else return true;   //�������������û�������ʹ�����ֵ���
	}
	return false;           //û�ҵ���ƥ�����ֵ
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
		else return;      //�����Ѿ�����������
	}
	

	//������û�������ݣ��ڶ�����������������
	BTreeNode* newnode = new BTreeNode(theint);
	if (newnode != nullptr && HeadPoint != nullptr)
	{
		if (theint > pp->date)
			pp->Tright = newnode;
		else
			pp->Tleft = newnode;
	}
	else HeadPoint = newnode;    //�������
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
	if (point == nullptr) return;         //û�ҵ����ݣ������˳�

	//������֯���Ľṹ
	//������ɾ���������Ӧ�÷ֱ��Ӧ����

	if (point->Tleft != nullptr && point->Tright != nullptr)
	{
		//��Ҫɾ���Ľڵ���������Ӷ���Ϊ�յ�ʱ��
		srand(time(0));
		BTreeNode* s = nullptr, * ps = point;
		if (rand() % 2)
		{
			//�ƶ�������������СԪ����
			s = point->Tright;
			while (s->Tleft != nullptr)
			{
				ps = s;
				s = s->Tleft;
			}
		}
		else
		{
			//�Ƶ�Ŀ�����������Ԫ����
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

	//P �����һ������
	//�Ѻ���ָ�����C
	BTreeNode* c;
	if (point->Tleft != nullptr)
		c = point->Tleft;
	else
		c = point->Tright;

	//ɾ��Point
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