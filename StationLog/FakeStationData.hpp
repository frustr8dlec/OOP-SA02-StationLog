#pragma once

#include <string>
#include <vector>
#include <memory>
#include "ITrainReader.h"

#include "pch.h"

class FakeStationData : public ITrainReader
{


private:

	Train trains[50] =
	{
	{ 787, 2137, 70, "Train-01", 8 },
	{ 3455,5165,94,"Train-02",10 },
	{ 6105,6435,2,"Train-03",1 },
	{ 7724,8309,19,"Train-04",3 },
	{ 7869,8589,28,"Train-05",4 },
	{ 8513,9368,37,"Train-06",5 },
	{ 10731,11211,12,"Train-07",2 },
	{ 10781,11381,20,"Train-08",3 },
	{ 11664,13134,78,"Train-01",9 },
	{ 12908,13973,51,"Train-02",6 },
	{ 14340,15180,36,"Train-03",5 },
	{ 14617,16267,90,"Train-04",10 },
	{ 15903,16443,16,"Train-05",3 },
	{ 17279,17804,15,"Train-06",3 },
	{ 18185,18605,8,"Train-07",2 },
	{ 19757,21317,84,"Train-08",9 },
	{ 20697,22467,98,"Train-01",11 },
	{ 23954,24569,21,"Train-02",3 },
	{ 25520,26945,75,"Train-03",9 },
	{ 28945,30010,51,"Train-04",6 },
	{ 30361,31711,70,"Train-05",8 },
	{ 31365,32055,26,"Train-06",4 },
	{ 31692,32337,23,"Train-07",3 },
	{ 30839,32594,97,"Train-08",11 },
	{ 33749,35489,96,"Train-01",11 },
	{ 35736,37386,90,"Train-02",10 },
	{ 38834,39209,5,"Train-03",1 },
	{ 42065,43415,70,"Train-04",8 },
	{ 43184,43709,15,"Train-05",3 },
	{ 46548,48153,87,"Train-06",10 },
	{ 49724,50954,62,"Train-07",7 },
	{ 49982,51587,87,"Train-08",10 },
	{ 50663,52043,72,"Train-01",8 },
	{ 54154,54694,16,"Train-02",3 },
	{ 55637,56477,36,"Train-03",5 },
	{ 58491,60006,81,"Train-04",9 },
	{ 59879,61064,59,"Train-05",7 },
	{ 61792,62647,37,"Train-06",5 },
	{ 63684,64269,19,"Train-07",3 },
	{ 64287,64782,13,"Train-08",2 },
	{ 64656,65691,49,"Train-01",6 },
	{ 66006,67056,50,"Train-02",6 },
	{ 67463,68528,51,"Train-03",6 },
	{ 70135,70960,35,"Train-04",4 },
	{ 73708,74878,58,"Train-05",7 },
	{ 74109,74190,8,"Train-06",2 },
	{ 74208,74658,10,"Train-07",2 },
	{ 75101,75431,2,"Train-08",1 },
	{ 75272,76352,52,"Train-01",6 },
	{ 75740,77135,73,"Train-02",8 }
	};

public:
	FakeStationData() {};
	~FakeStationData() {};

	Train readData(long timeSeconds)
	{
		for (long index = 0; index < 50; index++)
			if (this->trains[index].depart == timeSeconds)
			{
				return this->trains[index];
			}

		throw TrainException("No Train Data Available", NoData);

	};
};



