#pragma once

#include <string>
#include <exception>


struct Train
{
	long arrive;
	long depart;
	int passengers;
	std::string name;
	int platform;
};

enum TrainError
{
	NoData = 1,
	Unknown = 2
};

class TrainException : public std::exception
{
public:
	TrainException(const char* errMessage, TrainError errorType) :m_ErrMessage(errMessage),
		m_ErrorType(errorType) {}

	// overriden what() method from exception class
	const char* what() const noexcept { return m_ErrMessage; }
	TrainError GetError() { return m_ErrorType; }
private:
	const char* m_ErrMessage;
	TrainError m_ErrorType;
};

class ITrainReader
{
public:
	virtual Train readData(long timeSeconds) = 0;
};