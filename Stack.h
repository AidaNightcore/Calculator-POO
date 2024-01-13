#pragma once
#ifndef STACK_H
#define STACK_H
#include <stdexcept>
#include <iostream>
template <typename T>
class SStack {
private:
	T* elements;
	size_t capacity;
	size_t size;

public:
	SStack(size_t initialCapacity = 1);
	~SStack();
	void push(const T& value);
	void pop();
	T& top();
	bool empty() const;
	size_t getSize() const; 
	SStack(const SStack<T>& other);  // Copy constructor
	SStack<T>& operator=(const SStack<T>& other);  // Copy assignment operator
	void print() const;

private:
	void resize();
};



template <typename T>
SStack<T>::SStack(size_t initialCapacity) : elements(new T[initialCapacity]), capacity(initialCapacity), size(0) {}

template <typename T>
SStack<T>::~SStack() {
	if (elements != nullptr) {
		delete[] elements;
	}
}
template <typename T>
SStack<T>::SStack(const SStack<T>& other) : elements(new T[other.capacity]), capacity(other.capacity), size(other.size) {
	for (size_t i = 0; i < size; ++i) {
		elements[i] = other.elements[i];
	}
}

template <typename T>
SStack<T>& SStack<T>::operator=(const SStack<T>& other) {
	if (this != &other) {
		delete[] elements;
		elements = new T[other.capacity];
		capacity = other.capacity;
		size = other.size;

		for (size_t i = 0; i < size; ++i) {
			elements[i] = other.elements[i];
		}
	}
	return *this;
}
template <typename T> void SStack<T>::push(const T& value) {
	if (size == capacity) {
		resize();
	}
	elements[size++] = value;
}

template <typename T> void SStack<T>::pop() {
	if (!empty()) {
		--size;
	}
}

template <typename T> T& SStack<T>::top() {
	if (!empty()) {
		return elements[size - 1];
	}
	throw std::out_of_range("Stack is empty");
}

template <typename T> bool SStack<T>::empty() const {
	return size == 0;
}

template <typename T> size_t SStack<T>::getSize() const {
	return size;
}

template <typename T>
void SStack<T>::resize() {
	size_t newCapacity;
	if (capacity == 0)
		newCapacity = 1;
	else
		newCapacity = capacity * 2;

	T* newElements = new T[newCapacity];

	// Copy existing elements
	for (size_t i = 0; i < size; ++i) {
		newElements[i] = elements[i];
	}

	// Initialize the remaining elements in the new array
	for (size_t i = size; i < newCapacity; ++i) {
		newElements[i] = T();  // Default initialization
	}

	delete[] elements;
	elements = newElements;
	capacity = newCapacity;
}

template <typename T>
void SStack<T>::print() const {
	std::cout << "SStack Contents: ";
	for (size_t i = 0; i < size; ++i) {
		std::cout << elements[i] << " ";
	}
	std::cout << std::endl;
}




#endif // STACK_H