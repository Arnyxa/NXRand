#pragma once

#include <random>
#include <cassert>
#include <limits>

namespace nx
{
	template<typename T>
	class Rand 
	{ Rand() {} };

}

namespace nx
{
	template<>
	class Rand<int>
	{
	public:
		Rand(int aMin, int aMax) : mDist(aMin, aMax)
		{
			Check(aMin, aMax);
		}

		Rand()
		{}

		void Reset();
		void Reset(int aMin, int aMax);
		void ResetState();

		std::pair<int, int> GetRange() const;

		int operator()(int aMin, int aMax, bool retain = true);
		int operator()();

	private:
		void Check(int aMin, int aMax);

	private:
		std::uniform_int_distribution<int> mDist;
		std::default_random_engine mGen;
	};
}

#include "RandInt.inl"

namespace nx
{
	template<>
	class Rand<double>
	{
	public:
		Rand(double aMin, double aMax) : mDist(aMin, aMax)
		{
			Check(aMin, aMax);
		}

		Rand()
		{}

		void Reset();
		void Reset(double aMin, double aMax);
		void ResetState();

		std::pair<double, double> GetRange() const;

		double operator()(double aMin, double aMax, bool retain = true);
		double operator()();

	private:
		void Check(double aMin, double aMax);

	private:
		std::uniform_real_distribution<double> mDist;
		std::default_random_engine mGen;
	};
}

#include "RandDouble.inl"

namespace nx
{
	template<>
	class Rand<float>
	{
	public:
		Rand(float aMin, float aMax) : mDist(aMin, aMax)
		{
			Check(aMin, aMax);
		}

		Rand()
		{}

		void Reset();
		void Reset(float aMin, float aMax);
		void ResetState();

		std::pair<float, float> GetRange() const;

		float operator()(float aMin, float aMax, bool retain = true);
		float operator()();

	private:
		void Check(float aMin, float aMax);

	private:
		std::uniform_real_distribution<float> mDist;
		std::default_random_engine mGen;
	};
}

#include "RandFloat.inl"