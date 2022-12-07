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
