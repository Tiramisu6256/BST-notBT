#include<iostream>
//#include<stdio.h>
#include"BST.cpp"
using namespace std;




namespace Rotate {
	class RoSearchTree : BST::BiSearchTree
	{
	public:
		RoSearchTree() { Root = nullptr; }
		~RoSearchTree() { Release(Root); }
		BST::BiNode* SearchBST(int val) { return BiSearch(Root, val); }
		void InsertBST(int val) { Root = BiInsert(Root, val); }
		void DeleteBST(int val) { Root = BiDelete(Root, val); }
		void rotateLeft(int val) { Root = rotateLeft(Root, val); }
		void rotateRight(int val) { Root = rotateRight(Root, val); }
		void test() { cout << "当前根节点值为：" << Root->Data << endl; }
	private:
		void Release(BST::BiNode* bt);
		BST::BiNode* Root;
		BST::BiNode* BiInsert(BST::BiNode* bt, int val);
		BST::BiNode* BiSearch(BST::BiNode* bt, int val);
		BST::BiNode* BiDelete(BST::BiNode* bt, int val);
		BST::BiNode* rotateLeft(BST::BiNode* bt, int val);
		BST::BiNode* rotateRight(BST::BiNode* bt, int val);
		BST::BiNode* FindMin(BST::BiNode* bt);
	};
	void test01() {
		cout << "以下是测试函数01，用于比较不同插入顺序下二叉树的构建以及对搜索性能的测试" << endl;
		RoSearchTree BST1;
		RoSearchTree BST2;
		int a1[7] = { 1,2,3,4,5,6,7 }, a2[7] = { 4,2,1,3,6,5,7 }, i;
		cout << "BST1已经插入节点：";
		for (i = 0; i < 7; i++) {
			BST1.InsertBST(a1[i]);
			cout << a1[i] << "\t";
		}
		cout << endl;
		cout << "BST2已经插入节点：";
		for (i = 0; i < 7; i++) {
			BST2.InsertBST(a2[i]);
			cout << a2[i] << "\t";
		}
		cout << endl;
		cout << "现在对BST1进行查找7操作" << endl;
		BST1.SearchBST(7);
		cout << "现在对BST2进行查找7操作" << endl;
		BST2.SearchBST(7);
		cout << "由此可以看出不同的插入顺序下查找性能是不同的。" << endl;
	}

	void test02() {
		cout << "以下是测试函数02，用于简单的节点旋转测试。" << endl;
		RoSearchTree BST;
		BST.InsertBST(1);
		cout << "已经插入节点：1" << endl;
		BST.InsertBST(3);
		cout << "已经插入节点：2" << endl;
		BST.InsertBST(2);
		cout << "已经插入节点：3" << endl;
		cout << "现在尝试查找节点：2" << endl;
		BST.SearchBST(2);
		BST.test();
		cout << "现在尝试对节点3进行右旋" << endl;
		BST.rotateRight(3);
		cout << "现在尝试对节点1进行左旋" << endl;
		BST.rotateLeft(1);
		cout << "现在再次尝试查找节点：2" << endl;
		BST.SearchBST(2);
		BST.test();
		cout << "以下是测试在旋转过程中对于异常情况的处理。" << endl;
		cout << "现在尝试对节点1进行左旋" << endl;
		BST.rotateLeft(1);
	}
	BST::BiNode* RoSearchTree::BiInsert(BST::BiNode* bt, int val)
	{
		if (bt == nullptr)
			return new BST::BiNode(val);
		if (val < bt->Data)
			bt->Left = BiInsert(bt->Left, val);
		if (val > bt->Data)
			bt->Right = BiInsert(bt->Right, val);
		return bt;
	}

	BST::BiNode* RoSearchTree::BiSearch(BST::BiNode* bt, int val)
	{
		cout << "目前访问节点值为：" << bt->Data << endl;
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

	void RoSearchTree::Release(BST::BiNode* bt)
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

	BST::BiNode* RoSearchTree::BiDelete(BST::BiNode* bt, int val)
	{
		if (bt == nullptr)
			return nullptr;
		if (val < bt->Data)
		{
			bt->Left = BiDelete(bt->Left, val);
		}
		else if (val > bt->Data)
		{
			bt->Right = BiDelete(bt->Right, val);
		}
		else
		{
			if (bt->Left == nullptr)
			{
				BST::BiNode* temp = bt->Right;
				delete bt;
				return temp;
			}

			else if (bt->Right == nullptr)
			{
				BST::BiNode* temp = bt->Left;
				delete bt;
				return temp;
			}

			BST::BiNode* temp = FindMin(bt->Right);//找出此时结点的右子树上最小的一个，用作替换
			bt->Data = temp->Data;
			bt->Right = BiDelete(bt->Right, temp->Data);
		}
		return bt;
	}

	BST::BiNode* RoSearchTree::FindMin(BST::BiNode* bt)
	{
		while (bt->Left != nullptr)
		{
			bt = bt->Left;
		}
		return bt;
	}

	BST::BiNode* RoSearchTree::rotateLeft(BST::BiNode* bt, int val) {
		if (bt->Data < val) {
			bt->Right = rotateLeft(bt->Right, val);
		}
		else if (bt->Data > val) {
			bt->Left = rotateLeft(bt->Left, val);
		}
		else {
			if (bt->Right == nullptr) {
				cout << "右旋失败，现保持原二叉搜索树不变。" << endl;
				return bt;
			}
			else {
				BST::BiNode* temp = bt->Right;
				bt->Right = temp->Left;
				temp->Left = bt;
				return temp;
			}
		}
		return bt;
	}

	BST::BiNode* RoSearchTree::rotateRight(BST::BiNode* bt, int val) {
		if (bt->Data < val) {
			bt->Right = rotateRight(bt->Right, val);
		}
		else if (bt->Data > val) {
			bt->Left = rotateRight(bt->Left, val);
		}
		else {
			if (bt->Left == nullptr) {
				cout << "左旋失败，现保持原二叉搜索树不变。" << endl;
				return bt;
			}
			else {
				BST::BiNode* temp = bt->Left;
				bt->Left = temp->Right;
				temp->Right = bt;
				return temp;
			}
		}
		return bt;
	}



}
























