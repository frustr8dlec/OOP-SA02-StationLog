#pragma once

#include <memory>
#include "ITrainReader.h"
#include "FakeStationData.hpp"
#include "FakeTimer.hpp"

class Statistics
{
private:
	std::shared_ptr<ITrainReader> _stationData;
	std::shared_ptr<ITimer> _timer;

public:
	Statistics(const std::shared_ptr<ITrainReader>& reader, const std::shared_ptr<ITimer>& timer);
	~Statistics();

	// 3rd
	long readData();
	long sampleCount(long duration) { return -1; };

	// 1st
	double averageDuration(long startTime, long endTime) { return -1.0; }


};


Statistics::Statistics(const std::shared_ptr<ITrainReader>& reader, const std::shared_ptr<ITimer>& timer)
{
	_stationData = reader;
	_timer = timer;
	_timer->start();
}


Statistics::~Statistics()
{
}

long Statistics::readData() 
{
	Train trainSample;

	long timeOfSample = _timer->time(); 
	
	try {
		trainSample = this->_stationData->readData(timeOfSample);
	}
	catch (TrainException& e) {
		if (e.GetError() == TrainError::NoData)
		{
			throw std::runtime_error("No train data at this time!");
		}
		else if (e.GetError() == TrainError::Unknown)
		{
			throw std::runtime_error("Unknown error occurred when reading train data!");
		}
			
	}
	catch (...)
	{
		throw std::runtime_error("Things went really bad when reading train data!");
	}

	// TODO: Code to store the data in the data structure

	return trainSample.depart; // Return the second that the sample was taken at.
};
