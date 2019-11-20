#pragma once

class ITimer {
public:
	virtual void start() = 0;
	virtual void stop() = 0;
	virtual long time() = 0;

};


class FakeTimer : public ITimer
{
private:

	long fakeTimes[60] =
	{	
		2137,  5165,  6435,  8309,  8589,  9368,  11211, 11381, 13134, 13973,
		15180, 16267, 16443, 17804, 18605, 21317, 22467, 24569, 26945, 30010,
		31711, 32055, 32337, 32594, 35489, 37386, 39209, 43415, 43709, 48153,
		50954, 51587, 52043, 54694, 56477, 60006, 61064, 62647, 64269, 64782,
		65691, 67056, 68528, 70960, 74878, 74190, 74658, 75431, 76352, 77135,
		77150, 77150, 77151, 77152, 77153, 77154, 77155, 77156, 77157, 77157
	};


	long counter;

public:

	FakeTimer() {};
	~FakeTimer() {};

	void start() { counter = 0; };
	void stop() { counter = 0; };
	long time() 
	{
		if (counter >= 50)
			return 86500;
		
		return fakeTimes[counter++];
	};

};