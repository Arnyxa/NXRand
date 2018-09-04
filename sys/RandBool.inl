namespace nx
{
	// Will always modulate the given input to be between 0.f and 1.f
	Rand<bool>::Rand(double aProbability) 
		: mGen(mRand())
		, mDist(std::fmod(aProbability, 1.0))
	{}

	void Rand<bool>::ResetProbability()
	{
		mDist.param(param_bool());
	}

	void Rand<bool>::SetProbability(double aProbability)
	{
		mDist.param(param_bool(std::fmod(aProbability, 1.0)));
	}

	void Rand<bool>::Seed(std::seed_seq aSeedSequence)
	{
		mGen.seed(aSeedSequence);
	}

	void Rand<bool>::ResetState()
	{
		mDist.reset();
	}
	
	double Rand<bool>::GetProbability() const
	{
		return mDist.p();
	}
	
	bool Rand<bool>::operator()(double aProbability, bool retain)
	{
		auto myOldState = mDist.param();
		auto myNewState = param_bool(std::fmod(aProbability, 1.0));

		mDist.param(myNewState);

		bool myReturn = mDist(mGen);

		if (retain)
			mDist.param(myOldState);

		return myReturn;
	}
	
	bool Rand<bool>::operator()()
	{
		return mDist(mGen);
	}
	
	bool Rand<bool>::Next(double aProbability)
	{
		static std::bernoulli_distribution myDist;

		static std::random_device myRand;
		static Mersenne myGen(myRand());

		double myCurrentProb = fmod(aProbability, 1);

		static double myLastProb = myCurrentProb;

		if (myLastProb != myCurrentProb)
			myDist.param(param_bool(myCurrentProb));

		return myDist(myGen);
	}
}