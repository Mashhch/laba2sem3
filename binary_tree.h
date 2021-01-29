#pragma once

#include <string>

using namespace std;



template <class T>
bool frstmin(T a, T b)
{
	return a < b;
}


template <class T>
class BinaryTree
{
private:
	struct node
	{
		node* parent = nullptr;
		node* left = nullptr;
		node* right = nullptr;
		T elem;
	};
	node* root = nullptr;
	int size = 0;
	bool (*cmp)(T, T) = frstmin;

private:
	void destructor(node* nodePtr)
	{
		if (nodePtr == nullptr) return;
		if (nodePtr->left != nullptr)
		{
			destructor(nodePtr->left);
			delete nodePtr->left;
		}
		if (nodePtr->right != nullptr)
		{
			destructor(nodePtr->right);
			delete nodePtr->right;
		}
	}
	void DeleteElem(node* DelNode)
	{
		node* delNode = DelNode;
		if (delNode == nullptr) return;
		if (delNode->right == nullptr && delNode->left == nullptr)
		{
			if (delNode == this->root)
			{
				delete delNode;
				this->root = nullptr;
			}
			else
			{
				if (delNode->parent->right == delNode) {
					delNode->parent->right = nullptr;
				}
				else {
					delNode->parent->left = nullptr;
				}
				delete delNode;
			}
		}
		else if (delNode->right != nullptr && delNode->left == nullptr)
		{
			if (delNode == this->root)
			{
				delNode->right->parent = nullptr;
				this->root = delNode->right;
			}
			else
			{
				if (delNode->parent->left == delNode) {
					delNode->parent->left = delNode->right;
				}
				else {
					delNode->parent->right = delNode->right;
				}
				delNode->right->parent = delNode->parent;
			}
			delete delNode;
		}
		else if (delNode->right == nullptr && delNode->left != nullptr)
		{
			if (delNode == this->root)
			{
				delNode->left->parent = nullptr;
				this->root = delNode->left;
			}
			else
			{
				if (delNode->parent->left == delNode) {
					delNode->parent->left = delNode->left;
				}
				else {
					delNode->parent->right = delNode->left;
				}
				delNode->left->parent = delNode->parent;
			}
			delete delNode;
		}
		else if (delNode->right != nullptr && delNode->left != nullptr)
		{
			node* DelNode_ = DelNode;
			DelNode_ = DelNode_->right;
			while (DelNode_->left != nullptr)
			{
				delNode = delNode->left;
			}
			T value = delNode->elem;
			delNode->elem = DelNode_->elem;
			this->DeleteElem(DelNode_);
		}
	}

	void printAll(node* nodePtr)
	{
		if (nodePtr == nullptr) return;
		if (nodePtr->left != nullptr)
		{
			printAll(nodePtr->left);
		}
		std::cout << nodePtr->elem;
		std::cout << endl;
		if (nodePtr->right != nullptr)
		{
			printAll(nodePtr->right);
		}
	}

public:

	BinaryTree() = default;

	BinaryTree(const T rootElem, bool (*cmp) (T, T))
	{
		this->root = new node;
		this->root->elem = rootElem;
		this->size = 1;
		this->cmp = cmp;
	}
	
	void add(const T elem)
	{
		node* nodePtr = this->root;
		this->size++;
		if (this->root == nullptr){
			this->root = new node;
			this->root->elem = elem;
			return;
		}
		while (nodePtr != nullptr)
		{
			if (this->cmp(nodePtr->elem, elem))
			{
				if (nodePtr->right != nullptr)
				{
					nodePtr = nodePtr->right;
				}
				else
				{
					nodePtr->right = new node;
					nodePtr->right->elem = elem;
					nodePtr->right->parent = nodePtr;
					break;
				}
			}
			else
			{
				if (nodePtr->left != nullptr)
				{
					nodePtr = nodePtr->left;
				}
				else
				{
					nodePtr->left = new node;
					nodePtr->left->elem = elem;
					nodePtr->left->parent = nodePtr;
					break;
				}
			}
		}
	}

	node* search(const T elem)
	{
		node* nodePtr = this->root;
		while (nodePtr != nullptr)
		{
			if (this->cmp(nodePtr->elem, elem))
			{
				nodePtr = nodePtr->right;
			}
			else if (this->cmp(elem, nodePtr->elem))
			{
				nodePtr = nodePtr->left;
			}
			else return nodePtr;
		}
		return nullptr;
	}
	
	T minimum()
	{
		if (this->root == nullptr) return T(0);
		node* nodePtr = this->root;
		while (nodePtr->left != nullptr)
		{
			nodePtr = nodePtr->left;
		}
		return nodePtr->elem;
	}
	T maximum()
	{
		node* nodePtr = this->root;
		if (this->root == nullptr)
		{
			return T(0);
		}
		while (nodePtr->right != nullptr)
		{
			nodePtr = nodePtr->right;
		}
		return nodePtr->elem;
	}
	bool exist(const T elem)
	{
		if (search(elem) != nullptr)
		{
			return true;
		}
		else return false;
	}


	int getSize() const
	{
		return this->size;
	}
	
	
	T getElem(node* cur)
	{
		return cur->elem;
	}

	void setElem(node* cur, T elem)
	{
		cur->elem = elem;
	}

	void erase(T elem)
	{
		node* delNode = search(elem);
		if (delNode == nullptr) return;

		DeleteElem(delNode);
		this->size--;
	}

	void printAll()
	{
		if (this->root == nullptr) return;
		printAll(this->root);
		std::cout << endl;
	}

	~BinaryTree()
	{
		destructor(this->root);
		size = 0;
		delete this->root;
	}
};