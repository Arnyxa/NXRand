#include "include/NXRand.h"
#include <iostream>

int main()
{
	using namespace nx;                   // for nx::Rand

	Rand<float> myfRand(2.f, 5.f);        // random object that stores floats, in the range 2 to 5
	Rand<double> mydRand;                 // random object that stores doubles, in the range 0.0 to 1.0 (default)
	Rand<int> myiRand(12, 54);            // random object that stores ints, range 12~54 (integral default range is 1~100)
	 
	Rand<unsigned> myUInt(67, 55);        // you can also use other types, as long as they're integral/floating
	Rand<long double> mySpicy;            // even the spicier types

	Rand<bool> myBools(0.7);              // booleans use a range of 0.0 to 1.0 to determine the probability of something being true
	Rand<bool> myBool;                    // the default probability is 0.5, so a roughly equal chance for either

	Rand<int>::Next();                    // if you don't want to make an object and just want quick rng, you use this
	Rand<long double>::Next();            // it works with any int/float type
	Rand<bool>::Next();                   // or bool

	Rand<int>::Next(18);                  // you can specify the max value (min will default to 0)
	Rand<double>::Next(14.2, 100.85);     // or you can specify a min and a max value

	Rand<bool>::Next(0.7);                // for booleans, you can specify the probability of the outcome being 'true' instead
	Rand<bool>::Next();                   // do keep in mind this probability stays the same for subsequent calls
                                          // you would have to manually set it back to the default 0.5

	mySpicy.Seed(52);                     // you can specify your own seeds
	myiRand.ResetRange();                 // resets range to default (1~100)
	myfRand.GetRange();                   // range is returned as a pair of values, accessed through pair.first/pair.second
	mydRand.ResetState();                 // can also reset the internal state of the distribution (it stops caring what number came last)
	myBools.SetProbability(25.7);         // boolean probabilities are modulated to between 0.0 and 1.0 for any value above 1

	Rand<int> myObject(100, 200);

	for (unsigned i = 0; i < 25; ++i)
		std::cout << myObject() << "\n";  // you can get a random value within your range like this

	unsigned count = 0;
	unsigned total = 100;
	for (unsigned i = 0; i < total; ++i)  // booleans work much the same
	{
		bool e = myBools();

		if (e)
			++count;

		std::cout << e << " ";
	}

	std::cout << "\n" << count << " True\n"
		<< total - count << " False";

}