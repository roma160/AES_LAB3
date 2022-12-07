#pragma once
#include <vector>

using namespace std;

template<typename T>
class mod_stack: vector<T>
{
private:
	size_t size, head;

public:
	mod_stack(size_t size);

	void push(T el);
	T pop();

	T& top();

	void swap();
	void duplicate();

	size_t get_head() const;

	const vector<T>* get_vector() const;
};

template <typename T>
mod_stack<T>::mod_stack(size_t size) : vector<T>(size)
{
	this->size = size;
	this->head = size - 1;
}

template <typename T>
void mod_stack<T>::push(T el)
{
	head = (head + 1) % size;
	(*this)[head] = el;
}

template <typename T>
T mod_stack<T>::pop()
{
	size_t buff_head = head;
	head = (head - 1) % size;
	return (*this)[buff_head];
}

template <typename T>
T& mod_stack<T>::top()
{
	return (*this)[head];
}

template <typename T>
void mod_stack<T>::swap()
{
	std::swap((*this)[head], (*this)[(head - 1) % size]);
}

template <typename T>
void mod_stack<T>::duplicate()
{
	push(top());
}

template <typename T>
size_t mod_stack<T>::get_head() const
{
	return head;
}

template <typename T>
const vector<T>* mod_stack<T>::get_vector() const
{
	return this;
}

