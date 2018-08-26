#pragma once

#include "Incl.h"

namespace nx
{
	template<typename T, typename = void>
	class Rand 
	{ 
		static_assert(std::is_arithmetic_v<T>, "Must be an arithmetic type (integral/floating).");
		Rand() {} 
	};
}

namespace nx
{
	template<typename T>
	class Rand<T, std::enable_if_t<std::is_integral_v<T>>>
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

		void Seed(uint64_t value);
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
	class Rand<T, std::enable_if_t<std::is_floating_point_v<T>>>
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

		void Seed(uint64_t value);
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

namespace nx
{
	using iRand = Rand<int>;
	using fRand = Rand<float>;
	using dRand = Rand<double>;
}

#include "RandInt.inl"
#include "RandFloat.inl"