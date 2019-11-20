#include <memory>

#include "stdafx.h"
#include "CppUnitTest.h"

#include "../StationLog/Statistics.hpp"
#include "../StationLog/FakeStationData.hpp"
#include "../StationLog/FakeTimer.hpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1st
{		
	TEST_CLASS(UnitTest1st)
	{
	private:


	public:


		// Maximum Tests
		TEST_METHOD(MaxValueZero1st) {
			auto func = [] {
				std::shared_ptr<ITrainReader> mainDataReader(new FakeStationData());
				std::shared_ptr<ITimer> dataTimer(new FakeTimer());

				Statistics s(mainDataReader, dataTimer);
				s.readData();
				long max = s.maximumDuration(100, 2100);
			};

			Assert::ExpectException<std::invalid_argument>(func, L"averageDuration did not throw invalid_argument when no samples to average.");
		}
		TEST_METHOD(MaxValueMany1st) {
			std::shared_ptr<ITrainReader> mainDataReader(new FakeStationData());
			std::shared_ptr<ITimer> dataTimer(new FakeTimer());

			Statistics s(mainDataReader, dataTimer);
			long correctMax = 1605;

			for (int i = 0; i < 50; i++)
				s.readData();

			long max = s.maximumDuration(40000,66000);
			Assert::AreEqual(correctMax, max, L"averageDuration did not return the correct mean for trains before 30000 seconds");
		}
		TEST_METHOD(MaxValueOne1st) {
			std::shared_ptr<ITrainReader> mainDataReader(new FakeStationData());
			std::shared_ptr<ITimer> dataTimer(new FakeTimer());

			Statistics s(mainDataReader, dataTimer);
			long correctMax = 2137 - 787;

			s.readData();

			long max = s.maximumDuration(2130,2150);
			Assert::AreEqual(correctMax, max, L"averageDuration did not return the correct mean for the first item in the sample");
		}

		// Min Tests
		TEST_METHOD(MinValueZero1st) {
			auto func = [] {
				std::shared_ptr<ITrainReader> mainDataReader(new FakeStationData());
				std::shared_ptr<ITimer> dataTimer(new FakeTimer());

				Statistics s(mainDataReader, dataTimer);
				long min = s.minimumDuration(100, 2100);
			};

			Assert::ExpectException<std::invalid_argument>(func, L"averageDuration did not throw invalid_argument when no samples to average.");
		}
		TEST_METHOD(MinValueMany1st) {
			std::shared_ptr<ITrainReader> mainDataReader(new FakeStationData());
			std::shared_ptr<ITimer> dataTimer(new FakeTimer());

			Statistics s(mainDataReader, dataTimer);
			long correctMin = 495;

			for (int i = 0; i < 50; i++)
				s.readData();

			long min = s.minimumDuration(40000, 66000);
			Assert::AreEqual(correctMin, min, L"averageDuration did not return the correct mean for trains before 30000 seconds");
		}
		TEST_METHOD(MinValueOne1st) {
			std::shared_ptr<ITrainReader> mainDataReader(new FakeStationData());
			std::shared_ptr<ITimer> dataTimer(new FakeTimer());

			Statistics s(mainDataReader, dataTimer);
			long correctMin = 2137 - 787;

			s.readData();

			long min = s.minimumDuration(2130, 2150);
			Assert::AreEqual(correctMin, min, L"averageDuration did not return the correct mean for the first item in the sample");
		}


		// Mean Tests

		TEST_METHOD(MeanValueMany1st) {
			std::shared_ptr<ITrainReader> mainDataReader(new FakeStationData());
			std::shared_ptr<ITimer> dataTimer(new FakeTimer());

			Statistics s(mainDataReader, dataTimer);
			double correctMean = 1053.214286;
			long readTime = -1;

			for (int i = 0; i < 50; i++)
				readTime = s.readData();

			double mean = s.averageDuration(40000,66000);
			Assert::AreEqual(correctMean, mean, 0.0002, L"averageDuration did not return the correct mean for first 25 trains.");
		}
		TEST_METHOD(MeanValueOne1st) {
			std::shared_ptr<ITrainReader> mainDataReader(new FakeStationData());
			std::shared_ptr<ITimer> dataTimer(new FakeTimer());

			Statistics s(mainDataReader, dataTimer);
			double correctMean = 2137 - 787;

			s.readData();

			double mean = s.averageDuration(1000, 2137);
			Assert::AreEqual(correctMean, mean, 0.0002, L"averageDuration did not return the correct mean for the first item in the sample");
		}

	/*
	double averagePassengersTrain(std::string train) { return -1.0; }
	double averagePassengersPlatform(int platform) { return -1.0; }
	double averageDurationPlatform(int platform) { return -1.0; }
	*/

		TEST_METHOD(MeanPassengersTrain1st) {
			std::shared_ptr<ITrainReader> mainDataReader(new FakeStationData());
			std::shared_ptr<ITimer> dataTimer(new FakeTimer());

			Statistics s(mainDataReader, dataTimer);
			double correctMean = 41.0;
			long readTime = -1;

			for (int i = 0; i < 50; i++)
				readTime = s.readData();

			double mean = s.averagePassengersTrain("Train-05");
			Assert::AreEqual(correctMean, mean, 0.0002, L"averageDuration did not return the correct mean for Train-05");
		}

		TEST_METHOD(MeanPassengersPlatform1st) {
			std::shared_ptr<ITrainReader> mainDataReader(new FakeStationData());
			std::shared_ptr<ITimer> dataTimer(new FakeTimer());

			Statistics s(mainDataReader, dataTimer);
			double correctMean = 71;
			long readTime = -1;

			for (int i = 0; i < 50; i++)
				readTime = s.readData();

			double mean = s.averagePassengersPlatform(8);
			Assert::AreEqual(correctMean, mean, 0.0002, L"averageDuration did not return the correct mean for plaform 8.");
		}

		TEST_METHOD(MeanDurationPlatform1st) {
			std::shared_ptr<ITrainReader> mainDataReader(new FakeStationData());
			std::shared_ptr<ITimer> dataTimer(new FakeTimer());

			Statistics s(mainDataReader, dataTimer);
			double correctMean = 1365;
			long readTime = -1;

			for (int i = 0; i < 50; i++)
				readTime = s.readData();

			double mean = s.averageDurationPlatform(8);
			Assert::AreEqual(correctMean, mean, 0.0002, L"averageDuration did not return the correct mean for platform 8.");
		}

	};


}