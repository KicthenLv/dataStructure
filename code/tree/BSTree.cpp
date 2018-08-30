#include<iostream>
using namespace std;
 
//二叉搜索树结构
template<class K, class V>
struct BSTreeNode
{
	BSTreeNode* _left;
	BSTreeNode* _right;
	K _key;
	V _value;
 
	BSTreeNode(const K& key, const V& value)
		:_left(NULL)
		,_right(NULL)
		,_key(key)
		,_value(value)
	{}
 
};
 
template<class K,class V>
class BSTree
{
	typedef BSTreeNode<K, V> Node;
public:
	BSTree()
		:_root(NULL)
	{}
	
	//在二叉搜索树中插入节点
	bool Insert(const K& key, const V& value)
	{
		if (_root == NULL)
		{
			_root = new Node(key, value);
		}
 
		Node* cur=_root;
		Node* parent = NULL;
		//首先找到要插入的位置
		while (cur)
		{
			if (cur->_key > key)
			{
				parent = cur;
				cur = cur->_left;
			}
			else if(cur->_key<key)
			{
				parent = cur;
				cur = cur->_right;
			}
			else
			{
				return false;
			}
		}
		//在找到插入位置以后，判断插入父亲节点的左边还是右边
		if (parent->_key > key)
		{
			parent->_left = new Node(key, value);
		}
		else
		{
			parent->_right = new Node(key, value);
		}
 
		return true;
	}
 
 
	//在二叉搜索树中查找节点
	Node* Find(const K& key)
	{
		Node* cur=_root;
		//开始遍历查找
		while (cur)
		{
			if (cur->_key > key)
			{
				cur = cur->_left;
			}
			else if(cur->_key<key)
			{
				cur = cur->_right;
			}
			else
			{
				return cur;
			}
		}
		 
		return NULL;
	}
 
 
	//在二叉搜索树中删除节点
	bool Remove(const K& key)
	{
		//没有节点
		if (_root == NULL)
		{
			return false;
		}
		//只有一个节点
		if (_root->_left == NULL&&_root->_right == NULL)
		{
			if (_root->_key == key)
			{
				delete _root;
				_root = NULL;
				return true;
			}
 
			return false;
		}
 
		Node* parent = NULL;
		Node* cur = _root;
		//遍历查找要删除节点的位置
		while (cur)
		{
			Node* del = NULL;
			if (cur->_key > key)
			{
				parent = cur;
				cur = cur->_left;
			}
			else if (cur->_key < key)
			{
				parent = cur;
				cur = cur->_right;
			}
			else
			{
				//要删除节点的左子树为空，分3种情况
				if (cur->_left == NULL)
				{
					//注意判断父节点是否为空，若为空，则要删除的节点为根节点,如：只有根节点5和其右节点9
					if (parent == NULL)
					{
						_root = cur->_right;
						delete cur;
						cur = NULL;
						return true;
					}
					if (parent->_key > cur->_key)
					{
						del = cur;
						parent->_left = cur->_right;
						delete del;
						return true;
					}
					else if (parent->_key < key)
					{
						del = cur;
						parent->_right = cur->_right;
						delete del;
						return true;
					}
				}
				//要删除节点的右子树为空，同样分3种情况
				else if (cur->_right == NULL)
				{
					//注意判断父节点是否为空，若为空，则要删除的节点为根节点,如：只有根节点5和其左节点3
					if (parent == NULL)
					{
						_root = cur->_left;
						delete cur;
						cur = NULL;
						return true;
					}
					if (parent->_key > cur->_key)
					{
						del = cur;
						parent->_left = cur->_left;
						delete del;
						return true;
					}
					else if (parent->_key < cur->_key)
					{
						del = cur;
						parent->_right = cur->_left;
						delete del;
						return true;
					}
				}
				//左右子树都不为空
				else
				{
					Node* del = cur;
					Node* parent = NULL;
					Node* RightFirst = cur->_right;
					//右边第一个节点的左子树为空
					if (RightFirst->_left == NULL)
					{
						swap(RightFirst->_key, cur->_key);
						swap(RightFirst->_value, cur->_value);
						del = RightFirst;
						cur->_right = RightFirst->_right;
						delete del;
						return true;
					}
					//右边第一个节点的左子树不为空
					while (RightFirst->_left)
					{
						parent = RightFirst;
						RightFirst = RightFirst->_left;
					}
					   swap(RightFirst->_key, cur->_key);
					   swap(RightFirst->_value, cur->_value);
					   del = RightFirst;
					   parent->_left = RightFirst->_right;
					   delete del;
				       return true;
				}
			}
		}
		return false;
	}
 
	bool Insert_R(const K& key, const V& value)
	{
		return _Insert_R(_root, key, value);
	}
 
	Node* Find_R(const K& key)
	{
		return _Find_R(_root, key);
	}
 
	bool Remove_R(const K& key)
	{
		return _Remove_R(_root, key);
	}
 
	void InOrder()
	{
		_InOrder(_root);
		cout << endl;
	}
 
protected:
		
		bool _Remove_R(Node*& root, const K& key)
		{
			//没有节点
			if (root == NULL)
			{
				return false;
			}
			//只有一个节点
			if (root->_left == NULL&&root->_right == NULL)
			{
				if (root->_key == key)
				{
					delete root;
					root = NULL;
					return true;
				}
				else
				{
					return false;
				}
 
			}
 
			//删除二叉搜索树节点的递归写法
			if (root->_key > key)
			{
				_Remove_R(root->_left, key);
			}
			else if (root->_key < key)
			{
				_Remove_R(root->_right, key);
			}
			else
			{
				Node* del = NULL;
				
				if (root->_left == NULL)
				{
					del = root;
					root = root->_right;
					delete del;
					del = NULL;
					return true;
				}
				else if (root->_right == NULL)
				{
					del = root;
					root = root->_left;
					delete del;
					del = NULL;
					return true;
				}
				else
				{
					Node* RightFirst = root->_right;
 
					while (RightFirst->_left)
					{
						RightFirst = RightFirst->_left;
					}
 
					swap(root->_key, RightFirst->_key);
					swap(root->_value, RightFirst->_value);
 
					_Remove_R(root->_right, key);
					return true;
				}
			}
		}
 
		//递归查找法
		Node* _Find_R(Node* root, const K& key)
		{
			if (root == NULL)
			{
				return NULL;
			}
			if (root->_key > key)
			{
				return _Find_R(root->_left, key);
			}
			else if (root->_key < key)
			{
				return _Find_R(root->_right, key);
			}
			else
			{
				return root;
			}
		}
			
		//递归插入法
		bool _Insert_R(Node*& root, const K& key, const V& value)
		{
			if (root == NULL)
			{
				root = new Node(key, value);
				return true;
			}
			if (root->_key > key)
			{
				return _Insert_R(root->_left, key, value);
			}
			else if(root->_key < key)
			{
				return _Insert_R(root->_right, key, value);
			}
			else
			{
				return false;
			}
		}
 
		void _InOrder(Node* root)
		{
			if (root == NULL)
			{
				return;
			}
 
			_InOrder(root->_left);
			cout << root->_key << " ";
			_InOrder(root->_right);
		}
protected:
	Node* _root;
 
};
 
 
void Test()
{
	BSTree<int, int> s;
	
	//测试插入
	s.Insert_R(5, 1);
	s.Insert_R(4, 1);
	s.Insert_R(3, 1);
	s.Insert_R(6, 1);
	s.Insert_R(1, 1);
	s.Insert_R(2, 1);
	s.Insert_R(0, 1);
	s.Insert_R(9, 1);
	s.Insert_R(8, 1);
	s.Insert_R(7, 1);
 
	//二叉搜索树按中序输出是有序的
	s.InOrder();
 
	//测试查找
	cout << s.Find_R(6)->_key << endl;
 
	//测试删除
	s.Remove(5);

	
	//再次打印删除后的结果
	s.InOrder();
 
}
 
int main()
{
	Test();
	system("pause");
	return 0;
}
 
 
 
 
 
