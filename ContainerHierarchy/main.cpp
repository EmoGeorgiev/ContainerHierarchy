#include "ContainerHierarchy.h"

bool isEven(const int& x)
{
	return x % 2 == 0;
}
bool isOdd(const int& x)
{
	return x % 2 == 1;
}
int main()
{
	ContainerHierarchy ch;
	ch.parse("Input.txt");
	ch.print(std::cout);
	std::cout << "=============================" << std::endl;
	ch.addElement(6789);
	ch.print(std::cout);
	std::cout << "=============================" << std::endl;
	std::cout << "Member 50 : " << ch.member(50) << std::endl;
	std::cout << "Meets condition : " << ch.meetsCondition(isEven) << std::endl;
	std::cout << "=============================" << std::endl;
	ch.sortContainers();
	ch.print(std::cout);
	std::cout << "=============================" << std::endl;
	ch.filterContainers(isEven);
	ch.print(std::cout);
	ch.write("Output.txt");
	std::cout << "=============================" << std::endl;

	Iterator<int> it = ch.getPositionOfElement(47);

	while (it != nullptr)
	{
		std::cout << *it << " ";
		++it;
	}
	std::cout << std::endl;

	system("pause");
	return 0;
}