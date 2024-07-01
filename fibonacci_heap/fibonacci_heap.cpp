#include <iostream>
#include <list>

#include "include/fibonacci_heap.hpp"

int main() {



	
	Fibonacci_Heap<int>* heap = new Fibonacci_Heap<int>;
	for (int i = -1; i < 8; ++i) {
		heap->Insert(i);
	}
	Node<int>* node1 = heap->operator[](7);
	Node<int>* node2 = heap->operator[](6);
	heap->extractMin();
	heap->decreaseKey(node1, 1);
	heap->decreaseKey(node2, 1);

	/*
	for (int i = 0; i < std::pow(10,6); ++i) {
		heap->Insert(i);
	}
	try{
		for (int i = 0; i < std::pow(10,6); ++i) {
			heap->extractMin();			
		}
		std::cout << "o";
		heap->Clear();
		delete heap;
	}
	catch (Exception& e) {
		e.print();
	}
	*/
}