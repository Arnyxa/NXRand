# NXRand

Small library that abstracts away C++'s random classes and makes them somewhat easier to use.

The primary purpose of NXRand is to have a simple, yet effective way of utilizing the STL's PRNG, without having to go through all the hassle of creating random devices, rng engines, and distribution objects.

This would make it effective for things such as game programming, or smaller objects where simple RNG is all that is required.

The engine used is the Mersenne Twister, which will be the 32-bit or 64-bit version depending on what architecture you're targeting.

The distributions are uniform. Support for additional distributions/random engines may be added in the future,
if it somehow ends up being requested, though this is pretty unlikely.

## Requirements
A compiler that supports C++14 is required in order to use this library.

## Installation
NXRand is header-only, so all you need to do is add it to your include files. Make sure to preserve the folder structure (or you'll have to manually path to /sys/). 

If you're using Visual Studio, under your Project Properties go to Configuration Properties -> C/C++ -> General, and add the path to the folder containing /include/ and /sys/ (both folders must be present) to "Additional Include Directories".

If you're using gcc, simply add the NXRand folder path to your list of includes or paste it into your folder structure. Both /include/ and /sys/ must be in the same folder.

## Usage
```cpp
#include "include/NXRand.h"
#include <iostream>

int main() 
{
	nx::Rand<float> myfRand(2.f, 5.f);    // random object that stores floats, in the range 2 to 5
	nx::Rand<double> mydRand;             // random object that stores doubles, in the range 0.0 to 1.0 (default)
	nx::Rand<int> myiRand(12, 54);        // random object that stores ints, range 12~54 (integral default range is 1~100)

	nx::Rand<unsigned> myUInt(67, 55);    // you can also use other types, as long as they're integral/floating
	nx::Rand<long double> mySpicy;        // even the spicier types

	nx::Rand<bool> myBools(0.7);          // booleans use a range of 0.0 to 1.0 to determine the probability of something being true
	nx::Rand<bool> myBool;                // the default probability is 0.5, so a roughly equal chance for either

	nx::Rand<int>::Next();                // if you don't want to make an object and just want quick rng, you use this
	nx::Rand<long double>::Next();        // it works with any int/float type
	nx::Rand<bool>::Next();               // or bool

	nx::Rand<int>::Next(18);              // you can specify the max value (min will default to 0)
	nx::Rand<double>::Next(14.2, 100.85); // or you can specify a min and a max value

	nx::Rand<bool>::Next(0.7);            // for booleans, you can specify the probability of the outcome being 'true' instead
	nx::Rand<bool>::Next();               // do keep in mind this probability stays the same for subsequent calls
					      // you would have to manually set it back to the default 0.5

	mySpicy.Seed(52);                     // you can specify your own seeds
	myiRand.ResetRange();                 // resets range to default (1~100)
	myfRand.GetRange();                   // range is returned as a pair of values, accessed through pair.first/pair.second
	mydRand.ResetState();                 // can also reset the internal state of the distribution 
					      // (it stops caring what number came last)
	myBools.SetProbability(25.7);         // boolean probabilities are modulated to between 0.0 and 1.0 for any value above 1

	nx::Rand<int> myObject(100, 200);

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
```
