#pragma once
#include "Container.h"
#include "LinkedList.h"
#include "Stack.h"
#include "Queue.h"
#include <fstream>
#include <sstream>
#include <string>

class ContainerHierarchy
{
	using Condition = bool(*)(const int&);
public:
	ContainerHierarchy();
	void parse(std::string fileName);
	bool member(const int& x);
	void addElement(const int& x);
	bool meetsCondition(Condition condition);
	void filterContainers(Condition condition);
	void sortContainers();
	void print(std::ostream& os);
	Iterator<int> getPositionOfElement(const int& x);
	void write(std::string fileName);
private:
	LinkedList<Container<int>*> list;
	int numberOfContainers;
	Container<int>* pushElementsFromLine(const char& type, const std::string& line);
};