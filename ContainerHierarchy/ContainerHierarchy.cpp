#include "ContainerHierarchy.h"

ContainerHierarchy::ContainerHierarchy()
{

}
Container<int>* ContainerHierarchy::pushElementsFromLine(const char& type, const std::string& line)
{
	std::string newLine(line.substr(1)); //Removes the first symbol which is the type of the container
	std::istringstream iss(newLine);

	Container<int>* container;

	if (type == 'D')
	{
		container = new LinkedList<int>();
	}
	else if (type == 'S')
	{
		container = new Stack<int>();
	}
	else
	{
		container = new Queue<int>();
	}
	int currentNumber;

	while (iss >> currentNumber)
	{
		container->push(currentNumber);
	}
	return container;
}
void ContainerHierarchy::parse(std::string fileName)
{
	std::ifstream readFile(fileName);
	std::string line;
	readFile >> this->numberOfContainers;

	int counter = -1; //because the first line shows the number of containers

	while (std::getline(readFile, line) && counter < this->numberOfContainers)
	{
		char type = line[0];

		if (type == 'D' || type == 'S' || type == 'Q')
		{
			this->list.push(pushElementsFromLine(type, line));
			counter++;
		}
	}
}
bool ContainerHierarchy::member(const int& x)
{
	for (Container<int>* container : this->list)
	{
		if (container->member(x))
		{
			return true;
		}
	}
	return false;
}
void ContainerHierarchy::addElement(const int& x) //load balancing
{
	if (this->numberOfContainers > 0)
	{
		int min = INT16_MAX;

		for (Container<int>* container : this->list)
		{
			if (container->numberOfElements() < min)
			{
				min = container->numberOfElements();
			}
		}
		for (Container<int>* container : this->list)
		{
			if (container->numberOfElements() == min)
			{
				container->push(x);
				break;
			}
		}
	}
}
bool ContainerHierarchy::meetsCondition(ContainerHierarchy::Condition condition)
{
	for (Container<int>* container : this->list)
	{
		for (Iterator<int> it = container->begin(); it != container->end(); ++it)
		{
			if (condition(*it))
			{
				return true;
			}
		}
	}
	return false;
}
void ContainerHierarchy::filterContainers(ContainerHierarchy::Condition condition)
{
	for (Container<int>* container : this->list)
	{
		int counter = 0;
		for (Iterator<int> it = container->begin(); it != container->end();)
		{
			if (condition(*it))
			{
				++it;
				container->remove(counter);
			}
			else
			{
				++it;
				counter++;
			}
		}
	}
}
void ContainerHierarchy::sortContainers()
{
	for (Container<int>* container : this->list)
	{
		container->sort();
	}
}
void ContainerHierarchy::print(std::ostream& os)
{
	os << this->numberOfContainers << '\n';

	for (Container<int>* container : this->list)
	{
		container->print(os);
	}
}
Iterator<int> ContainerHierarchy::getPositionOfElement(const int& x)
{
	for (Container<int>* container : this->list)
	{
		for (Iterator<int> it = container->begin(); it != container->end(); ++it)
		{
			if (*it == x)
			{
				return Iterator<int>(it);
			}
		}
	}
	std::cout << "Invalid iterator" << std::endl;
	return Iterator<int>(nullptr);
}
void ContainerHierarchy::write(std::string fileName)
{
	std::ofstream printFile;
	printFile.open(fileName);
	this->print(printFile);
}