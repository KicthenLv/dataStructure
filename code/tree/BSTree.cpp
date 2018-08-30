#include<iostream>
using namespace std;
 
//�����������ṹ
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
	
	//�ڶ����������в���ڵ�
	bool Insert(const K& key, const V& value)
	{
		if (_root == NULL)
		{
			_root = new Node(key, value);
		}
 
		Node* cur=_root;
		Node* parent = NULL;
		//�����ҵ�Ҫ�����λ��
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
		//���ҵ�����λ���Ժ��жϲ��븸�׽ڵ����߻����ұ�
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
 
 
	//�ڶ����������в��ҽڵ�
	Node* Find(const K& key)
	{
		Node* cur=_root;
		//��ʼ��������
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
 
 
	//�ڶ�����������ɾ���ڵ�
	bool Remove(const K& key)
	{
		//û�нڵ�
		if (_root == NULL)
		{
			return false;
		}
		//ֻ��һ���ڵ�
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
		//��������Ҫɾ���ڵ��λ��
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
				//Ҫɾ���ڵ��������Ϊ�գ���3�����
				if (cur->_left == NULL)
				{
					//ע���жϸ��ڵ��Ƿ�Ϊ�գ���Ϊ�գ���Ҫɾ���Ľڵ�Ϊ���ڵ�,�磺ֻ�и��ڵ�5�����ҽڵ�9
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
				//Ҫɾ���ڵ��������Ϊ�գ�ͬ����3�����
				else if (cur->_right == NULL)
				{
					//ע���жϸ��ڵ��Ƿ�Ϊ�գ���Ϊ�գ���Ҫɾ���Ľڵ�Ϊ���ڵ�,�磺ֻ�и��ڵ�5������ڵ�3
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
				//������������Ϊ��
				else
				{
					Node* del = cur;
					Node* parent = NULL;
					Node* RightFirst = cur->_right;
					//�ұߵ�һ���ڵ��������Ϊ��
					if (RightFirst->_left == NULL)
					{
						swap(RightFirst->_key, cur->_key);
						swap(RightFirst->_value, cur->_value);
						del = RightFirst;
						cur->_right = RightFirst->_right;
						delete del;
						return true;
					}
					//�ұߵ�һ���ڵ����������Ϊ��
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
			//û�нڵ�
			if (root == NULL)
			{
				return false;
			}
			//ֻ��һ���ڵ�
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
 
			//ɾ�������������ڵ�ĵݹ�д��
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
 
		//�ݹ���ҷ�
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
			
		//�ݹ���뷨
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
	
	//���Բ���
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
 
	//��������������������������
	s.InOrder();
 
	//���Բ���
	cout << s.Find_R(6)->_key << endl;
 
	//����ɾ��
	s.Remove(5);

	
	//�ٴδ�ӡɾ����Ľ��
	s.InOrder();
 
}
 
int main()
{
	Test();
	system("pause");
	return 0;
}
 
 
 
 
 
