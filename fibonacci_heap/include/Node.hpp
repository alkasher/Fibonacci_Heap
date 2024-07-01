#pragma once
//#include "EfficientList/Include/LinkedList.hpp"
#include "Exception.hpp"

template <class T>
class Node {
protected:
	int rank;
	bool mark;

	T info;
	Node<T>* parent;
	Node<T>* left;
	Node<T>* right;
	Node<T>* last_child;

public:
	Node<T>(const T& elem) : info(elem), rank(0), mark(false), parent(nullptr),
	left(nullptr), right(nullptr), last_child(nullptr) {}

	Node<T>() : rank(0), mark(false), parent(nullptr),
		left(nullptr), right(nullptr), last_child(nullptr) {}

	Node<T>(const Node<T>& elem) 
		: info(elem.info), parent(elem.parent), left(elem.left), right(elem.right),
		last_child(elem.last_child), mark(elem.mark), rank(elem.rank) {}

	void push_child(Node<T>* node);

	Node<T>* get_right() const;

	~Node<T>() {}

	void Clear();

	template <class T>
	friend std::ostream& operator<<(std::ostream& s, Node<T>* el);

	template <class T>
	friend class Fibonacci_Heap;
};

template <class T>
Node<T>* Node<T>::get_right() const {
	return this->right;
}

template <class T>
void Node<T>::push_child(Node<T>* node) {
	++rank;
	if (node->right)
		node->right->left = node->left;
	if (node->left)
		node->left->right = node->right;
	node->parent = this;
	node->right = nullptr;
	node->left = nullptr;
	if (!last_child)
		last_child = node;
	else {
		last_child->right = node;
		node->left = last_child;
		last_child = node;
	}
}

template <class T>
void Node<T>::Clear() {
	if (this->right) {
		right->left = nullptr;
	}
	if (this->last_child) {
		//delete last_child;
		last_child->Clear();
		last_child = nullptr;
	}
	if (this->left) {
		left->Clear();
		//delete left;
		left = nullptr;
	}
	if (this) {
		if (this->parent)
		{
			Node<T>* cur = this->parent->last_child;
			while (cur && cur != this) {
				cur = cur->left;
			}
			cur = nullptr;
		}
		
		//..tmp->right = this;
		delete this;
		//this = NULL;
	}
}

template <class T>
Node<T>* XOR(const Node<T>* a, const Node<T>* b)
{
	return reinterpret_cast<Node<T>*>(
		reinterpret_cast<uintptr_t>(a) ^
		reinterpret_cast<uintptr_t>(b));
}

template<class T>
std::ostream& operator<<(std::ostream& s, Node<T>* el)
{
	s << el->info;
	return s;
}