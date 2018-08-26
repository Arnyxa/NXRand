#include <iostream>
#include "NXRand.h"

class A {};

int main(void)
{
	nx::Rand<int> myInt(1, 100);
	nx::Rand<double> myDouble(0.0, 2.0);
	nx::Rand<float> myFloat(100.f, 103.f);
	nx::Rand<unsigned> myPoggers(50, 60);

	nx::Rand<A> myTest; // doesn't compile

	std::cout << myInt() << "\n";
	std::cout << myDouble() << "\n";
	std::cout << myFloat() << "\n";
	std::cout << myPoggers() << "\n";

	std::cin.get();
	return 0;
}