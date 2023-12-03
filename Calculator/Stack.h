#pragma once
#include <stdexcept>

template <typename T>
class stack {
private:
	T* elements;
	size_t capacity;
	size_t size;

public:
	stack(size_t initialCapacity = 1);
	~stack();

	void push(const T& value);
	void pop();
	T& top();
	bool empty() const;
	size_t getSize() const;

private:
	void resize();
};
#include "Stack.cpp"; 