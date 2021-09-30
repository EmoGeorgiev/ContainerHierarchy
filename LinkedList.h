#pragma once
#include "Container.h"

template <typename T>
class LinkedList : public Container<T>
{
public:
	LinkedList();
	char type();
};

template <typename T>
LinkedList<T>::LinkedList() : Container<T>()
{

}
template <typename T>
char LinkedList<T>::type()
{
	return 'D';
}