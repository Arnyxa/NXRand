namespace nx
{
	template<typename T>
	Rand<T, if_int<T>>::Rand(T min, T max) : mGen(mRand())
	{
		CheckValidity(min, max);
	}

	template<typename T>
	void Rand<T, if_int<T>>::ResetRange()
	{
		mDist.param(param_int<T>(static_cast<T>(0), std::numeric_limits<T>::max()));
	}

	template<typename T>
	void Rand<T, if_int<T>>::SetRange(T min, T max)
	{
		CheckValidity(min, max);
	}

	template<typename T>
	void Rand<T, if_int<T>>::Seed(unsigned value)
	{
		mGen.seed(value);
	}

	template<typename T>
	void Rand<T, if_int<T>>::Seed(std::seed_seq aSeedSequence)
	{
		mGen.seed(aSeedSequence);
	}

	template<typename T>
	void Rand<T, if_int<T>>::ResetState()
	{
		mDist.reset();
	}

	template<typename T>
	std::pair<T, T> Rand<T, if_int<T>>::GetRange() const
	{
		return std::make_pair(mDist.min(), mDist.max());
	}

	template<typename T>
	T Rand<T, if_int<T>>::operator()(T min, T max, bool retain)
	{
		CheckValidity(min, max);

		auto myOldState = mDist.param();
		auto myNewState = param_int<T>(min, max);

		mDist.param(myNewState);

		T myReturn = mDist(mGen);

		if (retain)
			mDist.param(myOldState);

		return myReturn;
	}

	template<typename T>
	T Rand<T, if_int<T>>::operator()()
	{
		return mDist(mGen);
	}

	template<typename T>
	void Rand<T, if_int<T>>::CheckValidity(T min, T max)
	{
		if (min > max)
		{
			T temp = min;
			min = max;
			max = temp;
		}

		mDist.param(param_int<T>(min, max));
	}

	template<typename T>
	T Rand<T, if_int<T>>::Next()
	{
		static std::uniform_int_distribution<T> myDist;

		static std::random_device myRand;
		static Mersenne myGen(myRand());

		return myDist(myGen);
	}

	template<typename T>
	T Rand<T, if_int<T>>::Next(T max)
	{
		static std::uniform_int_distribution<T> myDist(static_cast<T>(0), max);

		static std::random_device myRand;
		static Mersenne myGen(myRand());

		return myDist(myGen);
	}

	template<typename T>
	T Rand<T, if_int<T>>::Next(T min, T max)
	{
		static std::uniform_int_distribution<T> myDist(min, max);

		if (min > max)
			myDist.param(param_int<T>(max, min));

		static std::random_device myRand;
		static Mersenne myGen(myRand());

		return myDist(myGen);
	}
}