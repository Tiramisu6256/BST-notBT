#include<iostream>
#include<stdio.h>
using namespace std;

struct BiNode
{
	int Data;
	BiNode* Left;
	BiNode* Right;
	bool Color;//此处规定颜色指的是该节点与其父节点的边颜色，其中1代表红色，0代表黑色。
	BiNode(int Value) :Data(Value), Left(nullptr), Right(nullptr),Color(1) {}
};

class BiSearchTree
{
public:
	BiSearchTree() { Root = nullptr; }
	~BiSearchTree() { Release(Root); }
	BiNode* SearchBST(int val) { return BiSearch(Root, val); }
	void InsertBST(int val) { 
		Root = BiInsert(Root, val);
		Root->Color=0;
	}
	void DeleteBST(int val) { Root = BiDelete(Root, val); }
	void RotateLeft(int val){ Root = RotateLeft(Root, val); }
	void RotateRight(int val){ Root = RotateRight(Root, val); }
	void test(){cout<<"当前根节点值为："<<Root->Data<<endl;}
private:
	void Release(BiNode* bt);
	BiNode* Root;
	BiNode* BiInsert(BiNode* bt,int val);
	BiNode* BiSearch(BiNode* bt,int val);
	BiNode* BiDelete(BiNode* bt,int val);
	BiNode* RotateLeft(BiNode* bt,int val);
	BiNode* RotateRight(BiNode* bt,int val);
	BiNode* FlipColors(BiNode* bt);
	BiNode* FindMin(BiNode* bt);
	bool IsRed(BiNode* bt);
};

void test01(){
	cout<<"以下是测试函数01，用于比较不同插入顺序下二叉树的构建以及对搜索性能的测试"<<endl;
	BiSearchTree BST2;
	int a2[7]={4,2,1,3,6,5,7},i;
	for(i=0;i<7;i++){
		cout<<"BST2正在尝试插入节点："<<a2[i]<<endl;
		BST2.InsertBST(a2[i]);
	}
	cout<<endl;
	cout<<"现在对BST2进行查找7操作"<<endl;
	BST2.SearchBST(7);
	cout<<endl;
}

void test02(){
	cout<<"以下是测试函数02，用于简单的节点旋转测试。"<<endl;
	BiSearchTree BST;
	BST.InsertBST(1);
	cout<<"已经插入节点：1"<<endl;
	BST.InsertBST(3);
	cout<<"已经插入节点：2"<<endl;
	BST.InsertBST(2);
	cout<<"已经插入节点：3"<<endl;
	cout<<"现在尝试查找节点：2"<<endl;
	BST.SearchBST(2);
	BST.test();
	cout<<"现在尝试对节点3进行右旋"<<endl;
	BST.RotateRight(3);
	cout<<"现在尝试对节点1进行左旋"<<endl;
	BST.RotateLeft(1);
	cout<<"现在再次尝试查找节点：2"<<endl;
	BST.SearchBST(2);
	BST.test();
	cout<<"以下是测试在旋转过程中对于异常情况的处理。"<<endl;
	cout<<"现在尝试对节点1进行左旋"<<endl;
	BST.RotateLeft(1);
}

int main()
{
	test01();

	system("pause");
	
	//system("cls");
	
	//test02();

	//system("pause");
		
	return 0;
}

BiNode* BiSearchTree::BiInsert(BiNode* bt,int val)
{
	if (bt == nullptr)
		return new BiNode(val);
	if (val < bt->Data)
		bt->Left = BiInsert(bt->Left, val);
	if (val > bt->Data)
		bt->Right = BiInsert(bt->Right, val);
	if(IsRed(bt->Right)&&!IsRed(bt->Left)){
		cout<<"现在对节点"<<bt->Data<<"进行左旋处理"<<endl;
		bt=RotateLeft(bt,bt->Data);
	}
	if(IsRed(bt->Left)&&IsRed(bt->Left->Left)){
		cout<<"现在对节点"<<bt->Data<<"进行右旋处理"<<endl;
		bt=RotateRight(bt,bt->Data);
	}
	if(IsRed(bt->Right)&&IsRed(bt->Left)){
		cout<<"现在对节点"<<bt->Data<<"进行颜色翻转处理"<<endl;
		bt=FlipColors(bt);
	}
	return bt;
}

bool BiSearchTree::IsRed(BiNode* bt)
{
	if(bt==nullptr) return false;
	return bt->Color;
}

BiNode* BiSearchTree::BiSearch(BiNode* bt,int val)
{
	cout<<"目前访问节点值为："<<bt->Data<<endl;
	if (bt == nullptr)
		return nullptr;
	if (bt->Data == val)
		return bt;
	if (val < bt->Data)
		return BiSearch(bt->Left, val);
	if (val > bt->Data)
		return BiSearch(bt->Right, val);
	return nullptr;
}

void BiSearchTree::Release(BiNode* bt)
{
	if (bt == nullptr)
		return;
	else
	{
		Release(bt->Left);
		Release(bt->Right);
		delete bt;
	}
}

BiNode* BiSearchTree::RotateLeft(BiNode* bt,int val){
	if(bt->Data<val){
		bt->Right=RotateLeft(bt->Right,val);
	}
	else if(bt->Data>val){
		bt->Left=RotateLeft(bt->Left,val);
	}
	else{
		if(bt->Right==nullptr){
			cout<<"左旋失败，现保持原二叉搜索树不变。"<<endl;
			return bt;
		}
		else{
		BiNode* temp = bt->Right;
		bt->Right=temp->Left;
		temp->Left=bt;
		temp->Color=bt->Color;
		bt->Color=1;
		return temp;
		}
	}
	return bt;
}

BiNode* BiSearchTree::RotateRight(BiNode* bt,int val){
	if(bt->Data<val){
		bt->Right=RotateRight(bt->Right,val);
	}
	else if(bt->Data>val){
		bt->Left=RotateRight(bt->Left,val);
	}
	else{
		if(bt->Left==nullptr){
			cout<<"右旋失败，现保持原二叉搜索树不变。"<<endl;
			return bt;
		}
		else{
		BiNode* temp = bt->Left;
		bt->Left=temp->Right;
		temp->Right=bt;
		temp->Color=bt->Color;
		bt->Color=1;
		return temp;
		}
	}
	return bt;
}

BiNode* BiSearchTree::FlipColors(BiNode *bt){
	bt->Left->Color=0;
	bt->Right->Color=0;
	bt->Color=1;
	return bt;
}

