#pragma once
#include <iostream>

template <typename T>
struct  Node
{
	T value;
	Node<T>* next;
	Node<T>* prev;

	Node(const T& value = 0)
	{
		this->value = value;
		this->next = nullptr;
		this->prev = nullptr;
	}
};

template <typename T>
class Iterator;

template <typename T>
class Container
{
public:
	Container();
	Container(const Container<T>& other);
	Container<T>& operator=(const Container<T>& other);
	~Container();
	void push(const T& x);
	virtual T pop(); //pop function also returns the value of the element
	virtual void remove(const int& position);
	virtual void sort();
	bool member(const T& x);
	bool empty();
	virtual void print(std::ostream& os);
	int numberOfElements();
	virtual char type() = 0;
	friend class Iterator<T>;
	Iterator<T> begin();
	Iterator<T> end();
protected:
	int size;
	Node<T>* head;
	Node<T>* tail;
	void copy(const Container& other);
	void erase();
};

template <typename T>
class Iterator
{
public:
	Iterator(Node<T>* start);
	T& operator*();
	bool operator==(const Iterator& it);
	bool operator!=(const Iterator& it);
	Iterator<T>& operator++();
	friend class Container<T>;
private:
	char type;
	Iterator(Node<T>* start, char type);
	Node<T>* current;
};
template <typename T>
void Container<T>::copy(const Container<T>& other)
{
	Node<T>* current = other.head;

	while (current != nullptr)
	{
		this->push(current->value);
		current = current->next;
	}
}
template <typename T>
void Container<T>::erase()
{
	Node<T>* current = this->head;
	Node<T>* temp = current;

	while (current != nullptr)
	{
		delete current;
		temp = temp->next;
		current = temp;
	}
	this->head = this->tail = nullptr;
	this->size = 0;
}
template <typename T>
Container<T>::Container()
{
	this->head = nullptr;
	this->tail = nullptr;
	this->size = 0;
}
template <typename T>
Container<T>::Container(const Container<T>& other)
{
	this->copy(other);
}
template <typename T>
Container<T>& Container<T>::operator=(const Container<T>& other)
{
	if (this != &other)
	{
		this->erase();
		this->copy(other);
	}
	return *this;
}
template <typename T>
Container<T>::~Container()
{
	this->erase();
}
template <typename T>
void Container<T>::push(const T& x)
{
	Node<T>* newNode = new Node<T>(x);

	if (this->size == 0)
	{
		this->head = this->tail = newNode;
	}
	else
	{
		this->tail->next = newNode;
		newNode->prev = this->tail;
		this->tail = newNode;
	}
	this->size++;
}
template <typename T>
T Container<T>::pop()
{
	if (this->size > 1)
	{
		Node<T>* toDelete = this->tail;
		T last = toDelete->value;
		this->tail = this->tail->prev;
		delete toDelete;
		this->tail->next = nullptr;
		this->size--;
		return last;
	}
	else if (this->size == 1)
	{
		Node<T>* toDelete = this->head;
		T last = toDelete->value;
		delete toDelete;
		this->head = this->tail = nullptr;
		this->size--;
		return last;
	}
}
template <typename T>
void Container<T>::remove(const int& position)
{
	Node<T>* current = this->head;

	if (current == nullptr)
	{
		return;
	}
	else if (position == 0)
	{
		Node<T>* next = current->next;
		delete current;
		next->prev = nullptr;
		this->head = next;
	}
	else
	{
		int counter = 0;
		while (counter < position - 1 && current != nullptr)
		{
			current = current->next;
			counter++;
		}
		if (current == nullptr || current->next == nullptr)
		{
			return;
		}
		Node<T>* next = current->next->next;
		delete current->next;
		current->next = next;

		if (next != nullptr)
		{
			next->prev = current;
		}
		else
		{
			this->tail = current;
		}
	}
	this->size--;
}
template <typename T>
void Container<T>::sort()
{
	if (this->head == nullptr || this->head->next == nullptr)
	{
		return;
	}
	Node<T>* temp = this->head;
	while (temp != nullptr)
	{
		Node<T>* next = temp->next;
		while (next != nullptr)
		{
			if (temp->value > next->value)
			{
				T swap = temp->value;
				temp->value = next->value;
				next->value = swap;
			}
			next = next->next;
		}
		temp = temp->next;
	}
}
template <typename T>
bool Container<T>::member(const T& x)
{
	Node<T>* current = this->head;

	while (current != nullptr)
	{
		if (current->value == x)
		{
			return true;
		}
		current = current->next;
	}
	return false;
}
template <typename T>
bool Container<T>::empty()
{
	return this->size == 0;
}
template <typename T>
void Container<T>::print(std::ostream& os)
{
	Node<T>* current = this->head;

	os << this->type() << " ";
	while (current != nullptr)
	{
		os << current->value << " ";
		current = current->next;
	}
	os << '\n';
}
template <typename T>
int Container<T>::numberOfElements()
{
	return this->size;
}
template <typename T>
Iterator<T> Container<T>::begin()
{
	if (this->type() == 'S')
	{
		return Iterator<T>(this->tail, this->type());
	}
	else if (this->type() == 'D' || this->type() == 'Q')
	{
		return Iterator<T>(this->head, this->type());
	}
}
template <typename T>
Iterator<T> Container<T>::end()
{	
	return Iterator<T>(nullptr, this->type());
}
template <typename T>
T& Iterator<T>::operator*()
{
	return this->current->value;
}
template <typename T>
bool Iterator<T>::operator==(const Iterator& it)
{
	return this->current == it.current;
}
template <typename T>
bool Iterator<T>::operator!=(const Iterator& it)
{
	return this->current != it.current;
}
template <typename T>
Iterator<T>& Iterator<T>::operator++()
{
	if (this->type == 'S' && this->current != nullptr)
	{
		this->current = this->current->prev;
	}
	else if ((this->type == 'D' || this->type == 'Q') && this->current != nullptr)
	{
		this->current = this->current->next;
	}
	return *this;
}
template <typename T>
Iterator<T>::Iterator(Node<T>* start, char type)
{
	this->type = type;
	this->current = start;
}
template <typename T>
Iterator<T>::Iterator(Node<T>* start)
{
	this->current = start;
}