#pragma once
#include "Container.h"

template <typename T>
class Queue : public Container<T>
{
public:
	Queue();
	T pop();
	int front();
	char type();
};

template <typename T>
Queue<T>::Queue() : Container<T>()
{

}
template <typename T>
T Queue<T>::pop()
{
	if (this->size > 1)
	{
		Node<T>* toDelete = this->head;
		T front = this->front();
		this->head = this->head->next;
		delete toDelete;
		this->head->prev = nullptr;
		this->size--;
		return front;
	}
	else if (this->size == 1)
	{
		Node<T>* toDelete = this->head;
		T front = toDelete->value;
		delete toDelete;
		this->head = this->tail = nullptr;
		this->size--;
		return front;
	}
}
template <typename T>
int Queue<T>::front()
{
	if (this->head != nullptr)
	{
		return this->head->value;
	}
	return NULL;
}
template <typename T>
char Queue<T>::type()
{
	return 'Q';
}