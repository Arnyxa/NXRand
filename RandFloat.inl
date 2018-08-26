// float
namespace nx
{
	Rand<float>::Rand(float aMin, float aMax) : mDist(aMin, aMax)
	{
		Check(aMin, aMax);
	}

	void Rand<float>::Reset()
	{
		auto myNew = mDist.param();
		myNew._Init(0, std::numeric_limits<float>::max());

		mDist.param(myNew);
	}

	void Rand<float>::Reset(float aMin, float aMax)
	{
		Check(aMin, aMax);

		auto myNew = mDist.param();
		myNew._Init(aMin, aMax);

		mDist.param(myNew);
	}

	void Rand<float>::ResetState()
	{
		mDist.reset();
	}

	std::pair<float, float> Rand<float>::GetRange() const
	{
		return std::make_pair(mDist.min(), mDist.max());
	}

	float Rand<float>::operator()(float aMin, float aMax, bool retain = true)
	{
		Check(aMin, aMax);

		auto myOldState = mDist.param();
		auto myNewState = mDist.param();

		myNewState._Init(aMin, aMax);
		mDist.param(myNewState);

		float myReturn = mDist(mGen);

		if (retain)
			mDist.param(myOldState);

		return myReturn;
	}

	float Rand<float>::operator()()
	{
		return mDist(mGen);
	}

	void Rand<float>::Check(float aMin, float aMax)
	{
		assert(aMin <= aMax && "Min value can not be greater than max value.");
	}
}