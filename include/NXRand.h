#pragma once

#include "../sys/incl.h"

namespace nx
{
	template<typename T, typename = void>
	class Rand 
	{ 
		static_assert(is_arithmetic<T>, "Must be an arithmetic type (integral/floating).");
		Rand() {} 
	};
}

namespace nx
{
	template<typename T>
	class Rand<T, is_int<T>>
	{
	public:
		Rand(T min, T max);
		Rand() {}

		// Reset the object's range to its default state 
		void ResetRange();
		void SetRange(T min, T max);

		// Resets the internal state of the distribution.
		// After a call to this function, the next call to operator() 
		// on the distribution object will not be dependent on previous calls to operator().
		void ResetState();

		void Seed(unsigned value);
		void Seed(std::seed_seq aSeedSequence);

		std::pair<T, T> GetRange() const;

		// Quickly fetch a random value unlocalized to an object
		// Its range goes from 0 to the given type's maximum capacity
		static T Next();
		// Quickly fetch a random value unlocalized to an object
		// Its range goes from 0 to 'max'
		static T Next(T max);
		// Quickly fetch a random value unlocalized to an object
		// Its range goes from 'min' to 'max'
		static T Next(T min, T max);

		T operator()(T min, T max, bool retain = true);
		T operator()();

	private:
		void CheckValidity(T min, T max);

	private:
		std::uniform_int_distribution<T> mDist;
		std::random_device mRand;
		Mersenne mGen;
	};
}

namespace nx
{
	template<typename T>
	class Rand<T, is_float<T>>
	{
	public:
		Rand(T min, T max);
		Rand() {}

		void ResetRange();
		void SetRange(T min, T max);

		// Resets the internal state of the distribution.
		// After a call to this function, the next call to operator() 
		// on the distribution object will not be dependent on previous calls to operator().
		void ResetState();

		void Seed(unsigned value);
		void Seed(std::seed_seq aSeedSequence);

		std::pair<T, T> GetRange() const;

		// Quickly fetch a random value unlocalized to an object
		// Its range goes from 0 to the given type's maximum capacity
		static T Next();
		// Quickly fetch a random value unlocalized to an object
		// Its range goes from 0 to 'max'
		static T Next(T max);
		// Quickly fetch a random value unlocalized to an object
		// Its range goes from 'min' to 'max'
		static T Next(T min, T max);

		T operator()(T min, T max, bool retain = true);
		T operator()();

	private:
		void CheckValidity(T min, T max);

	private:
		std::uniform_real_distribution<T> mDist;
		std::random_device mRand;
		Mersenne mGen;
	};
}

#include "../sys/RandInt.inl"
#include "../sys/RandFloat.inl"