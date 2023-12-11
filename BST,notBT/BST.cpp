#include<iostream>
//#include<stdio.h>
using namespace std;



namespace BST{
	enum COLOR { BLACK, RED };
	struct BiNode
	{
		int Data;
		BiNode* Left;
		BiNode* Right;
		COLOR Color;//此处规定颜色指的是该节点与其父节点的边颜色，其中1代表红色，0代表黑色。
		BiNode(int Value) :Data(Value), Left(nullptr), Right(nullptr), Color(RED) {}
	};

	class BiSearchTree
	{
	public:
		BiSearchTree() { Root = nullptr; }
		~BiSearchTree() { Release(Root); }
		void InsertBST(int val) { Root = BiInsert(Root, val); }
		BiNode* SearchBST(int val) { return BiSearch(Root, val); }
		void DeleteBST(int val) { Root = BiDelete(Root, val); }
	private:
		void Release(BiNode* bt);
		BiNode* Root;
		BiNode* BiInsert(BiNode* bt, int val);
		BiNode* BiSearch(BiNode* bt, int val);
		BiNode* BiDelete(BiNode* bt, int val);
		BiNode* FindMin(BiNode* bt);
	};
void test01()
{
	cout << "以下是测试函数01，用于测试构建二叉搜索树，以及测试查找，删除，插入节点各项功能";
	BiSearchTree BST;
	int num[10] = {63,55,42,45,58,90,70,25,85,65},i;
	for (i = 0; i < 10; i++) {
		BST.InsertBST(num[i]);
		cout << "已经插入节点：" << num[i] << endl;
	}
	cout << "现在尝试查找节点：65" << endl;
	if (BST.SearchBST(65))
		cout << "查找成功" << endl;
	else
		cout << "查找失败" << endl;
	BST.DeleteBST(65);
	cout << "已经删除节点：65" << endl;
	cout << "现在再次尝试查找节点：65" << endl;
	if (BST.SearchBST(65))
		cout << "查找成功" << endl;
	else
		cout << "查找失败" << endl;
}BiNode* BiSearchTree::BiInsert(BiNode* bt, int val)
{
	if (bt == nullptr)
		return new BiNode(val);
	if (val < bt->Data)
		bt->Left = BiInsert(bt->Left, val);
	if (val > bt->Data)
		bt->Right = BiInsert(bt->Right, val);
	return bt;
}

BiNode* BiSearchTree::BiSearch(BiNode* bt, int val)
{
	if (bt == nullptr)
		return nullptr;
	if (bt->Data == val)
		return bt;
	cout << "目前访问节点值为：" << bt->Data << endl;
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

BiNode* BiSearchTree::BiDelete(BiNode* bt, int val)
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
			BiNode* temp = bt->Right;
			delete bt;
			return temp;
		}

		else if (bt->Right == nullptr)
		{
			BiNode* temp = bt->Left;
			delete bt;
			return temp;
		}

		BiNode* temp = FindMin(bt->Right);//找出此时结点的右子树上最小的一个，用作替换
		bt->Data = temp->Data;
		bt->Right = BiDelete(bt->Right, temp->Data);
	}
	return bt;
}

BiNode* BiSearchTree::FindMin(BiNode* bt)
{
	while (bt->Left != nullptr)
	{
		bt = bt->Left;
	}
	return bt;
}

};
//int main()
//{
//	BST::test01();
//
//	system("pause");
//
//	return 0;
//}

