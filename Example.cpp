#include "include/NXRand.h"
#include <iostream>

int main() 
{
	nx::Rand<float> myfRand(2.f, 5.f);    // random object that stores floats, in the range 2 to 5
	nx::Rand<double> mydRand;             // random object that stores doubles, in the range 0.0 to 1.0 (default)
	nx::Rand<int> myiRand(12, 54);        // random object that stores ints, range 12~54 (integral default range is 1~100)

	nx::Rand<unsigned> myUInt(67, 55);    // you can also use other types, as long as they're integral/floating
	nx::Rand<long double> mySpicy;        // even the spicier types

	nx::Rand<int>::Next();                // if you don't want to make an object and just want quick rng, you use this
	nx::Rand<long long int>::Next();      // it works with any int/float type

	mySpicy.Seed(52);                     // you can specify your own seeds
	myiRand.ResetRange();                 // resets range to default (1~100)
	myfRand.GetRange();                   // range is returned as a pair of values, accessed through pair.first/pair.second
	mydRand.ResetState();                 // can also reset the internal state of the distribution (it stops caring what number came last)

	nx::Rand<int> myObject(100, 200);

	for (int i = 0; i < 25; ++i)
		std::cout << myObject() << "\n";  // you can get a random value within your range like this

	std::cin.get();
}