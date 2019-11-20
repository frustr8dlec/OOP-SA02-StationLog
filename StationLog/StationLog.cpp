// StationLog.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <iostream>
#include "Statistics.hpp"
#include "FakeStationData.hpp"
#include "FakeTimer.hpp"


int main()
{
	
	std::shared_ptr<ITrainReader> dataReader(new FakeStationData());
	std::shared_ptr<ITimer> dataTimer(new FakeTimer());

	Statistics s(dataReader, dataTimer);

	std::cout << s.readData() << std::endl;
	


	return 0;
}

