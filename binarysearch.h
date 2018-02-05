#include<iostream>
#include<queue>
#include<string>
using namespace std;

template<class K,class V>
class BinaraySearchNode
{
public:
	BinaraySearchNode<K,V>* _left;
	BinaraySearchNode<K,V>* _right;
	BinaraySearchNode<K,V>* _parent;
	K  _key;
	V _value;

	BinaraySearchNode(const K& key,const V& value)
		:_left(NULL)
		, _right(NULL)
		, _parent(NULL)
		, _key(key)
		, _value(value)
	{}
};

template<class K,class V>
class BinarySearchTree
{
	typedef BinaraySearchNode<K, V> Node;
public:
	BinarySearchTree()
		:_root(NULL)
	{}

	//��������
	BinarySearchTree(const BinarySearchTree<K, V>& bs)
		:_root(NULL)
	{
		if (bs._root == NULL)
		{
			return;
		}
		else
		{
			queue<Node*> q;
			q.push(bs._root);
			while (!q.empty())
			{
				Node* cur = q.front();
				InSert(cur->_key);
				q.pop();
				if (cur->_left)
					q.push(cur->_left);
				if (cur->_right)
					q.push(cur->_right);
			}
		}
	}

	//��ֵ�����
	BinarySearchTree<K, V>& operator = (const BinarySearchTree<K, V>& bs)
	{
		BinarySearchTree<K, V> tmp(bs);
		swap(_root, bs._root);
		return *this;
	}

	~BinarySearchTree()
	{
		_Destroy(_root);
	}

	void _Destroy(Node* root)
	{
		if (root == NULL)
			return;
		_Destroy(root->_left);
		_Destroy(root->_right);
		delete root;
	}

	//����
	bool InSert(const K& key,const V& value)
	{
		return _InSert(_root, key, value);
	}

	bool _InSert(Node*& root, const K&key, const V& value)
	{
		if (root == NULL)
		{
			root = new Node(key, value);
			return true;
		}
		Node* parent = NULL;
		Node* cur = _root;
		while (cur)
		{
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
				return false;
		}
		Node* tmp = new Node(key, value);
		if (parent->_key > key)
			parent->_left = tmp;
		else if (parent->_key < key)
			parent->_right = tmp;
		return true;
	}
	
	//����
	Node* Find(const K& key)
	{
		Node* cur = _root;
		while (cur)
		{
			if (cur->_key > key)
				cur = cur->_left;
			else if (cur->_key < key)
				cur = cur->_right;
			return cur;
		}
		return NULL;
	}

	//ɾ���ڵ�
	bool Remove(const K& key)
	{
		if (_root == NULL)
			return false;
		Node* parent = NULL;
		Node* cur = _root;
		while (cur)
		{
			if (key > cur->_key)
			{
				parent = cur;
				cur = cur->_right;
			}
			else if (key < cur->_key)
			{
				parent = cur;
				cur = cur->_left;
			}
			else//����
			{
				if (cur->_left == NULL)
				{
					parent = cur->_parent;
					if (parent == NULL)
					{
						_root = cur->_right;
						delete cur;
						cur = NULL;
						return true;
					}
					if (cur == parent->_left)
					{
						parent->_left = cur->_right;
					}
					else
					{
						parent->_right = cur->_right;
					}
					delete cur;
					cur = NULL;
				}
				if (cur->_right == NULL)
				{
					parent = cur->_parent;
					if (parent == NULL)
					{
						_root = cur->_left;
						delete cur;
						cur = NULL;
						return true;
					}
					if (cur == parent->_left)
					{
						parent->_left = cur->_left;
					}
					else
					{
						parent->_right = cur->_left;
					}
					delete cur;
					cur = NULL;
				}
				if (cur->_left != NULL && cur->_right != NULL)
				{
					//�滻��(ע����ڵ�Ϊ�յ������
					Node* subRight = cur->_right;
					Node* subParent = cur;
					while (subRight->_left)
					{
						subParent = subRight;
						subRight = subRight->_left;
					}

					cur->_key = subRight->_key;
					if (subParent->_right == subRight)
						subParent->_right = subRight->_right;
					else
						subParent->_left = subRight->_left;
					delete subRight;
					subRight = NULL;
				}
				return  true;
			}
		}
		return false;
	}

	//�ݹ����
	bool _InSertR(Node*& root, const K& key)//�ݹ����
	{
		if (root == NULL)
			return root = new Node(key);
		if (root->_key < key)
			return _InSertR(root->right, key);
		if (root->_key > key)
			return _InSertR(root->_left, key);
	}


	//�ݹ�ɾ��
	bool _RemoveR(Node*& root, const K& key)//ע�⣺����Ҫ������
	{
		if (root == NULL)
			return false;
		if (root->_left == NULL && root->_right == NULL)
		{
			if (root->_key == key)
			{
				delete root;
				return true;
			}
			else
				return false;
		}
		if (root->_key > key)
			RemoveR(root->_left, key);
		if (root->_key < key)
			RemoveR(root->_right, key);
		else
		{
			Node* cur = root;
			if (cur->_left == NULL)
			{
				parent = cur->_parent;
				if (parent == NULL)
				{
					root = root->_right;
					delete cur;
					cur = NULL;
				}
				if (cur == parent->_left)
				{
					parent->_left = cur->_right;
				}
				else
				{
					parent->_right = cur->_right;
				}
				delete cur;
				cur = NULL;
			}
			if (cur->_right == NULL)
			{
				parent = cur->_parent;
				if (parent == NULL)
				{
					_root = cur->_left;
					delete cur;
					cur = NULL;
					return true;
				}
				if (cur == parent->_left)
				{
					parent->_left = cur->_left;
				}
				else
				{
					parent->_right = cur->_left;
				}
				delete cur;
				cur = NULL;
			}
			if (cur->_left != NULL && cur->_right != NULL)
			{
				//�滻��
				Node* subRight = cur->_right;
				Node* subParent = cur;
				while (subRight->_left)
				{
					subParent = subRight;
					subRight = subRight->_left;
				}

				cur->_key = subRight->_key;
				if (subParent->_right == subRight)
					subParent->_right = subRight->_right;
				else
					subParent->_left = subRight->_left;
				delete subRight;
				subRight = NULL;
			}
			return  true;
		}
	}

	//�������
	void InOrder()
	{
		_InOrder(_root);
	}
protected:
	void _InOrder(Node* root)
	{
		if (root == NULL)
			return;
		else
		{
			_InOrder(root->_left);
			cout << root->_key << ":"<<root->_value<< " ";
			_InOrder(root->_right);
		}
	}
private:
	Node* _root;
};

void Test()
{
	BinarySearchTree<string, string> b;
	b.InSert("sort", "����");
	b.InSert("tree", "��");
	b.InSert("string", "�ַ���");
	b.InSert("search", "����");
	b.InOrder();
	//���ҵ���
	BinaraySearchNode<string, string> *ret = b.Find("sort");
	cout << ret->_value << endl;
	
	//int a[] = { 5, 3,1,0,4,7,6,8,9,2};
	/*for (size_t i = 0; i < (sizeof(a) / sizeof(a[0])); ++i)
	{
		bs.InSert(a[i],);
	}*/

	//ͳ�Ƶ��ʳ��ֵĴ���
	string arr[] = { "nihao", "hello", "good", "good", "good", "hello" };
	BinarySearchTree<string, int> CountTree;
	for (size_t i = 0; i < sizeof(arr) / sizeof(arr[0]); ++i)
	{
		BinaraySearchNode<string, int> *Node = CountTree.Find(arr[i]);
		if (Node)
		{
			Node->_value += 1;
		}
		else
		{
			CountTree.InSert(arr[i],1);
		}
	}

	//bs.InOrder();
	//cout << endl;
	//bs.Remove(5);
	//bs.InOrder();
};
