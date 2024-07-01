#pragma once

#include "Node.hpp"
#include <vector>
/*
I don't need LinkedList at all, as it will double my space*/

template <class T>
class Fibonacci_Heap {
public:
	Node<T>* head;
	Node<T>* tail;

	Node<T>* minim;

	int size;
public:
	Fibonacci_Heap<T>();

	void Insert(Node<T>* node);
	void Insert(const T& elem);

	int get_size() const;
	Node<T>* operator[](const int i);
	
	void Merge(const Fibonacci_Heap<T>& heap);
	void extractMin();
	void consolidate();

	void decreaseOp(Node<T>* node);
	void decreaseKey(Node<T>* node, const T value);


	~Fibonacci_Heap<T>();
	void Clear();

	template <class T>
	friend std::ostream& operator<<(std::ostream& s, Fibonacci_Heap<T>& el);
};

template <class T>
Fibonacci_Heap<T>::Fibonacci_Heap<T>() {
	minim = head = tail = nullptr;
	size = 0;
	
}

template <class T>
inline void Fibonacci_Heap<T>::Insert(Node<T>* node) {
	if (!node)
		throw NullptrException("Fib_Heap Insert: nullptr node");
	
	node->right = nullptr;
	node->left = nullptr;
	
	++size;
	if (!head) {
		minim = head = tail = node;
		return;
	}

	tail->right = node;
	node->left = tail;
	tail = node;
	if (tail->info < minim->info)
		minim = tail;
}

template <class T>
inline void Fibonacci_Heap<T>::Insert(const T& elem) {
	Node<T>* node;
	if (!(node = new Node<T>(elem)))
		throw NotEnoughSpaceException("Fib_Heap Insert: not enough space");
	this->Insert(node);
}

template <class T>
int Fibonacci_Heap<T>::get_size() const {
	return size;
}

template <class T>
Node<T>* Fibonacci_Heap<T>::operator[](const int i) {
	Node<T>* current = this->head;
	for (int j = 0; j < i; ++j) {
		if (!current)
			throw InvalidLengthException("Fib_Heap operator[]: wrong index");
		current = current->right;
	}
	return current;
}

template <class T>
void Fibonacci_Heap<T>::Merge(const Fibonacci_Heap<T>& heap) {
	if (!heap.head)
		return;
	//size += heap.size; only if we call Merge from extractMin
	if (!head) {
		head = heap.head;
		tail = heap.tail;
		minim = heap.minim;
		return;
	}
	tail->right = heap.head;
	heap.head->left = tail;
	tail = heap.tail;
	if (!minim || heap.minim < minim)
		minim = heap.minim;
	//minim = minim.operator*(static_cast<bool>(minim->info <= heap.minim->info)) + heap.minim.operator*(static_cast<bool>(heap.minim->info < minim->info));
}

template <class T>
void Fibonacci_Heap<T>::extractMin() {

	Fibonacci_Heap<T>* new_heap = new Fibonacci_Heap<T>;//minim->first_child);

	Node<T>* cur = minim->last_child;
	if (minim == head)
		head = minim->right;
	else if (minim == tail)
		tail = minim->left;
	if (minim->left)
		minim->left->right = minim->right;
	if (minim->right)
		minim->right->left = minim->left;

	
	delete minim;
	minim = nullptr;
	Node<T>* left;// = cur->left;
	while (cur) {
		cur->parent = nullptr;
		left = cur->left;
		new_heap->Insert(cur);
		cur = left;
	}
	//cur = minim = head;
	/*
	while (cur) {
		if (cur->info < minim->info)
			minim = cur;
		cur = cur->right;
	}
	*/
	this->Merge(*new_heap);
	delete new_heap;
	this->consolidate();
	--size;
}

template <class T>
void Fibonacci_Heap<T>::consolidate() {
	Node<T>* current = head;
	//int* a = new int[std::log(this->size())];
	/*Node<int>** a = new Node<int>*[std::log2(size)+1];// this->get_size() implements o(n)
	for (int i = 0; i < std::log2(size) + 1; ++i) {
		a[i] = nullptr;
	}*/
	std::vector<Node<int>*> a(std::log2(size)+1, nullptr);
	minim = head;
	int r = 0;
	while (current) {
		if (current->info < minim->info)
			minim = current;

		if (a[current->rank]) {

			r = current->rank;
			if (a[current->rank]->info < minim->info)
				minim = a[current->rank];

			if (current->info > a[current->rank]->info) {
				std::swap(current, a[current->rank]);
				if (a[current->rank] == tail)
					tail = current;
				else if (a[current->rank] == head)
					head = current;
				current->push_child(a[current->rank]);
			}
			a[r] = nullptr;
			continue;
		}
		a[current->rank] = current;
		current = current->right;
	}
	//delete[] a;
}

template <class T>
void Fibonacci_Heap<T>::decreaseKey(Node<T>* node, const T value) {
	if (!node)
		throw NullptrException("decreaseKey: null ptr node");

	node->info -=value ;
	decreaseOp(node);

}

template <class T>
void Fibonacci_Heap<T>::decreaseOp(Node<T>* node) {

	if (node->parent && node->parent->mark) {
		decreaseOp(node->parent);
	}

	if (node->left)
		node->left->right = node->right;
	if (node->right)
		node->right->left = node->left;

	if (node->parent) {
		--node->parent->rank;

		if (node->parent->last_child == node) {
			node->parent->last_child = node->left;
		}
		if (node->parent->parent)//если корень, то mark = false
			node->parent->mark = true;
	}

	node->mark = false;
	node->parent = nullptr;
	this->Insert(node);
	
	
}

template <class T>
void Fibonacci_Heap<T>::Clear() {
	Node<T>* tmp;
	if (!head) return;
	for (Node<T>* current = head; current->right != nullptr;) {
		tmp = current->right;
		current->Clear();
		current = tmp;
		//delete current->left;
		//current->left = nullptr;
	}

	tail->Clear();
	//delete tail;
}


template <class T>
Fibonacci_Heap<T>::~Fibonacci_Heap<T>() {

}

template<class T>
std::ostream& operator<<(std::ostream& s, Fibonacci_Heap<T>& el)
{
	Node<T>* current = el.head;

	while (current) {
		s << current << " ";
		current = current->get_right();
	}
	std::cout << std::endl;
	std::cout << "head is " << el.head << " tail is " << el.tail << " min is " << el.minim;
	
	return s;
}
