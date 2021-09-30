#pragma once
#include "Container.h"

template <typename T>
class Stack : public Container<T>
{
public:
	Stack();
	void remove(const int& position);
	void sort();
    void print(std::ostream& os);
	int top();
	char type();
};

template <typename T>
Stack<T>::Stack() : Container<T>()
{

}
template <typename T>
void Stack<T>::remove(const int& position)
{
	Node<T>* current = this->tail;

	if (current == nullptr)
	{
		return;
	}
	if (position == 0)
	{
		Node<T>* next = current->prev;
		delete current;
		next->next = nullptr;
		this->tail = next;
	}
	else
	{
		int counter = 0;
		while (counter < position - 1 && current != nullptr)
		{
			current = current->prev;
			counter++;
		}
		if (current == nullptr || current->prev == nullptr)
		{
			return;
		}
		Node<T>* prev = current->prev->prev;
		delete current->prev;
		current->prev = prev;

		if (prev != nullptr)
		{
			prev->next = current;
		}
		else
		{
			this->head = current;
		}
	}
	this->size--;
}
template <typename T>
void Stack<T>::sort()
{
	if (this->head == nullptr || this->head->next == nullptr)
	{
		return;
	}
	Node<T>* temp = this->tail;
	while (temp != nullptr)
	{
		Node<T>* next = temp->prev;
		while (next != nullptr)
		{
			if (temp->value > next->value)
			{
				T swap = temp->value;
				temp->value = next->value;
				next->value = swap;
			}
			next = next->prev;
		}
		temp = temp->prev;
	}
}
template <typename T>
void Stack<T>::print(std::ostream& os)
{
	Node<T>* current = this->tail;

	os << this->type() << " ";
	while (current != nullptr)
	{
		os << current->value << " ";
		current = current->prev;
	}
	os << '\n';
}
template <typename T>
int Stack<T>::top()
{
	if (this->tail != nullptr)
	{
		return this->tail->value;
	}
	return NULL;
}
template <typename T>
char Stack<T>::type()
{
	return 'S';
}