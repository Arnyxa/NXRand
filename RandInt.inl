// int
namespace nx
{
	Rand<int>::Rand(int aMin, int aMax) : mDist(aMin, aMax)
	{
		Check(aMin, aMax);
	}

	void Rand<int>::Reset()
	{
		auto myNew = mDist.param();
		myNew._Init(0, std::numeric_limits<int>::max());

		mDist.param(myNew);
	}

	void Rand<int>::Reset(int aMin, int aMax)
	{
		Check(aMin, aMax);

		auto myNew = mDist.param();
		myNew._Init(aMin, aMax);

		mDist.param(myNew);
	}

	void Rand<int>::ResetState()
	{
		mDist.reset();
	}

	std::pair<int, int> Rand<int>::GetRange() const
	{
		return std::make_pair(mDist.min(), mDist.max());
	}

	int Rand<int>::operator()(int aMin, int aMax, bool retain = true)
	{
		Check(aMin, aMax);

		auto myOldState = mDist.param();
		auto myNewState = mDist.param();

		myNewState._Init(aMin, aMax);
		mDist.param(myNewState);

		int myReturn = mDist(mGen);

		if (retain)
			mDist.param(myOldState);

		return myReturn;
	}

	int Rand<int>::operator()()
	{
		return mDist(mGen);
	}

	void Rand<int>::Check(int aMin, int aMax)
	{
		assert(aMin <= aMax && "Min value can not be greater than max value.");
	}
}