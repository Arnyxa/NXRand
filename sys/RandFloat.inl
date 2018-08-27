namespace nx
{
	template<typename T>
	Rand<T, is_float<T>>::Rand(T min, T max) : mGen(mRand())
	{
		CheckValidity(min, max);
	}

	template<typename T>
	void Rand<T, is_float<T>>::ResetRange()
	{
		mDist.param(std::uniform_real<T>(static_cast<T>(0), std::numeric_limits<T>::max()).param());
	}

	template<typename T>
	void Rand<T, is_float<T>>::SetRange(T min, T max)
	{
		CheckValidity(min, max);
	}

	template<typename T>
	void Rand<T, is_float<T>>::Seed(unsigned value)
	{
		mGen.seed(value);
	}

	template<typename T>
	void Rand<T, is_float<T>>::Seed(std::seed_seq aSeedSequence)
	{
		mGen.seed(aSeedSequence);
	}

	template<typename T>
	void Rand<T, is_float<T>>::ResetState()
	{
		mDist.reset();
	}

	template<typename T>
	std::pair<T, T> Rand<T, is_float<T>>::GetRange() const
	{
		return std::make_pair(mDist.min(), mDist.max());
	}

	template<typename T>
	T Rand<T, is_float<T>>::operator()(T min, T max, bool retain)
	{
		CheckValidity(min, max);

		auto myOldState = mDist.param();
		auto myNewState = mDist.param();

		myNewState._Init(min, max);
		mDist.param(myNewState);

		T myReturn = mDist(mGen);

		if (retain)
			mDist.param(myOldState);

		return myReturn;
	}

	template<typename T>
	T Rand<T, is_float<T>>::operator()()
	{
		return mDist(mGen);
	}

	template<typename T>
	void Rand<T, is_float<T>>::CheckValidity(T min, T max)
	{
		if (min > max)
		{
			T temp = min;
			min = max;
			max = temp;
		}

		mDist.param(std::uniform_real<T>(min, max).param());
	}

	template<typename T>
	T Rand<T, is_float<T>>::Next()
	{
		static std::uniform_real_distribution<T> myDist;

		static std::random_device myRand;
		static Mersenne myGen(myRand());

		return myDist(myGen);
	}

	template<typename T>
	T Rand<T, is_float<T>>::Next(T max)
	{
		static std::uniform_real_distribution<T> myDist(static_cast<T>(0), max);

		static std::random_device myRand;
		static Mersenne myGen(myRand());

		return myDist(myGen);
	}

	template<typename T>
	T Rand<T, is_float<T>>::Next(T min, T max)
	{
		static std::uniform_real_distribution<T> myDist(min, max);

		if (min > max)
			myDist.param(std::uniform_real<T>(max, min).param());

		static std::random_device myRand;
		static Mersenne myGen(myRand());

		return myDist(myGen);
	}
}