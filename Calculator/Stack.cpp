#include "Stack.h"
template <typename T>
stack<T>::stack(size_t initialCapacity) : elements(new T[initialCapacity]), capacity(initialCapacity), size(0) {}

template <typename T> stack<T>::~stack() {
	delete[] elements;
}

template <typename T> void stack<T>::push(const T& value) {
	if (size == capacity) {
		resize();
	}
	elements[size++] = value;
}

template <typename T> void stack<T>::pop() {
	if (!empty()) {
		--size;
	}
}

template <typename T> T& stack<T>::top() {
	if (!empty()) {
		return elements[size - 1];
	}
	/*throw out_of_range("Stack is empty");*/
	/*cout << "Stack is empty"; */
}

template <typename T> bool stack<T>::empty() const {
	return size == 0;
}

template <typename T> size_t stack<T>::getSize() const {
	return size;
}

template <typename T> void stack<T>::resize() {
	size_t newCapacity; 
	if (capacity == 0)
		newCapacity = 1;
	else
		newCapacity = capacity * 2;


	T* newElements = new T[newCapacity];

	for (size_t i = 0; i < size; ++i) {
		newElements[i] = elements[i];
	}

	delete[] elements;
	elements = newElements;
	capacity = newCapacity;
}

