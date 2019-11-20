#include <memory>

#include "stdafx.h"
#include "CppUnitTest.h"

#include "../StationLog/Statistics.hpp"
#include "../StationLog/FakeStationData.hpp"
#include "../StationLog/FakeTimer.hpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTesting
{		
	TEST_CLASS(UnitTest3rd)
	{
	private:

		 
	public:
	
		TEST_METHOD(ReadData)
		{
			std::shared_ptr<ITrainReader> mainDataReader(new FakeStationData());
			std::shared_ptr<ITimer> dataTimer(new FakeTimer());

			Statistics s(mainDataReader, dataTimer);

			long result;
			long counter = 0;
			do 
			{
				result = s.readData();
				counter++;
			} while (result != 18605 && counter < 50);

			Assert::AreEqual(18605l, result, L"readData did not report back the correct time for the read.");	
		}
		TEST_METHOD(ReadDataMoreThan24)
		{
			auto func = [] {
				std::shared_ptr<ITrainReader> mainDataReader(new FakeStationData());
				std::shared_ptr<ITimer> dataTimer(new FakeTimer());

				Statistics s(mainDataReader, dataTimer);

				for (int i = 0; i < 60; i++)
					s.readData();

				s.readData();
			};
	
			Assert::ExpectException<std::out_of_range>(func, L"readData() did not throw out_of_range when reading beyond 24H.");
			
		}
		// Clear Samples Tests
		TEST_METHOD(ClearSamplesZero)
		{
			std::shared_ptr<ITrainReader> mainDataReader(new FakeStationData());
			std::shared_ptr<ITimer> dataTimer(new FakeTimer());

			Statistics s(mainDataReader, dataTimer);
			long beforeClear = 0;
			long afterClear = -1;

			s.clearSamples();
			afterClear = s.sampleCount(1000);

			Assert::AreEqual(beforeClear, afterClear, L"Sample count is not 0 after .clearSamples()");
		}
		TEST_METHOD(ClearSamplesOne)
		{
			std::shared_ptr<ITrainReader> mainDataReader(new FakeStationData());
			std::shared_ptr<ITimer> dataTimer(new FakeTimer());

			Statistics s(mainDataReader, dataTimer);

			long beforeClear = 1;
			long afterClear = -1;

			long sampleTime = s.readData();
			s.clearSamples();

			afterClear = s.sampleCount(sampleTime);
			Assert::AreNotEqual(beforeClear, afterClear, L"No change in the item count after calling .clearSamples()");
			Assert::AreEqual(0l, afterClear, L"Sample count is not 0 after .clearSamples()");
		}
		TEST_METHOD(ClearSamplesMany)
		{
			std::shared_ptr<ITrainReader> mainDataReader(new FakeStationData());
			std::shared_ptr<ITimer> dataTimer(new FakeTimer());

			Statistics s(mainDataReader, dataTimer);
			long beforeClear = 0;

			long afterClear = -1;
			
			s.readData();
			s.readData();
			long sampleTime = s.readData();
			
			beforeClear = s.sampleCount(sampleTime);

			s.clearSamples();
		
			afterClear = s.sampleCount(sampleTime);
			Assert::AreNotEqual(beforeClear, afterClear, L"No change in the item count after calling .clearSamples()");
			Assert::AreEqual(0l, afterClear,L"Sample count is not 0 after .clearSamples()");
		}

		// Total Tests
		TEST_METHOD(TotalEmpty) {
			std::shared_ptr<ITrainReader> mainDataReader(new FakeStationData());
			std::shared_ptr<ITimer> dataTimer(new FakeTimer());

			Statistics s(mainDataReader, dataTimer);
			long totalSamples = -1;
			totalSamples = s.sampleTotal();

			Assert::AreEqual(0l, totalSamples, L"sampleTotal has not returned 0 when there are no samples.");
		}
		TEST_METHOD(TotalOne) {
			std::shared_ptr<ITrainReader> mainDataReader(new FakeStationData());
			std::shared_ptr<ITimer> dataTimer(new FakeTimer());

			Statistics s(mainDataReader, dataTimer);
			long totalSamples = -1;
			s.readData();
			totalSamples = s.sampleTotal();

			Assert::AreEqual(1l, totalSamples, L"sampleTotal has not returned 1 when there is 1 sample.");
		}
		TEST_METHOD(TotalMany) {
			std::shared_ptr<ITrainReader> mainDataReader(new FakeStationData());
			std::shared_ptr<ITimer> dataTimer(new FakeTimer());

			Statistics s(mainDataReader, dataTimer);
			long totalSamples = -1;
			s.readData();
			s.readData();
			s.readData();
			s.readData();
			s.readData();
			totalSamples = s.sampleTotal();

			Assert::AreEqual(5l, totalSamples, L"sampleTotal has not returned 5 when there are 5 samples.");
		}

		// Maximum Tests
		TEST_METHOD(MaxValueZero) {
			auto func = [] {
				std::shared_ptr<ITrainReader> mainDataReader(new FakeStationData());
				std::shared_ptr<ITimer> dataTimer(new FakeTimer());

				Statistics s(mainDataReader, dataTimer);
				s.readData();
				long max = s.maximumDuration(2100);
			};

			Assert::ExpectException<std::invalid_argument>(func, L"averageDuration did not throw invalid_argument when no samples to average.");
		}
		TEST_METHOD(MaxValueMany) {
			std::shared_ptr<ITrainReader> mainDataReader(new FakeStationData());
			std::shared_ptr<ITimer> dataTimer(new FakeTimer());

			Statistics s(mainDataReader, dataTimer);
			long correctMax = 1770;

			for (int i = 0; i < 25; i++)
				s.readData();

			long max = s.maximumDuration(35500);
			Assert::AreEqual(correctMax, max, L"averageDuration did not return the correct mean for trains before 30000 seconds");
		}
		TEST_METHOD(MaxValueOne) {
			std::shared_ptr<ITrainReader> mainDataReader(new FakeStationData());
			std::shared_ptr<ITimer> dataTimer(new FakeTimer());

			Statistics s(mainDataReader, dataTimer);
			long correctMax = 2137 - 787;

			s.readData();

			long max = s.maximumDuration(30000);
			Assert::AreEqual(correctMax, max, L"averageDuration did not return the correct mean for the first item in the sample");
		}

		// Mean Tests
		TEST_METHOD(MeanValueZero) {
			auto func = [] {
				std::shared_ptr<ITrainReader> mainDataReader(new FakeStationData());
				std::shared_ptr<ITimer> dataTimer(new FakeTimer());

				Statistics s(mainDataReader, dataTimer);
				double mean = s.averageDuration(30000);
			};

			Assert::ExpectException<std::invalid_argument>(func, L"averageDuration did not throw invalid_argument when no samples to average.");
		}
		TEST_METHOD(MeanValueMany) {
			std::shared_ptr<ITrainReader> mainDataReader(new FakeStationData());
			std::shared_ptr<ITimer> dataTimer(new FakeTimer());

			Statistics s(mainDataReader, dataTimer);
			double correctMean = 968.8235;
			long readTime = -1;

			for (int i = 0; i < 17; i++)
				readTime = s.readData();

			double mean = s.averageDuration(22500);
			Assert::AreEqual(correctMean, mean, 0.0002, L"averageDuration did not return the correct mean for first 25 trains.");
		}
		TEST_METHOD(MeanValueOne) {
			std::shared_ptr<ITrainReader> mainDataReader(new FakeStationData());
			std::shared_ptr<ITimer> dataTimer(new FakeTimer());

			Statistics s(mainDataReader, dataTimer);
			double correctMean =  2137 - 787;

			s.readData();

			double mean = s.averageDuration(30000);
			Assert::AreEqual(correctMean, mean, 0.0002, L"averageDuration did not return the correct mean for the first item in the sample");
		}

		// Sample Count Tests
		TEST_METHOD(CorrectSampleCountZero) {
			std::shared_ptr<ITrainReader> mainDataReader(new FakeStationData());
			std::shared_ptr<ITimer> dataTimer(new FakeTimer());

			Statistics s(mainDataReader, dataTimer);

			long sampleCount = s.sampleCount(1000);
			Assert::AreEqual(0l, sampleCount, L"sampleCount did not return the correct count of the number of items stored (0)");
		}
		TEST_METHOD(CorrectSampleCountOne) {
			std::shared_ptr<ITrainReader> mainDataReader(new FakeStationData());
			std::shared_ptr<ITimer> dataTimer(new FakeTimer());

			Statistics s(mainDataReader, dataTimer);

		    long sampleTime = s.readData();

			long sampleCount = s.sampleCount(6000);
			Assert::AreEqual(1l, sampleCount, L"sampleCount did not return the correct count of the number of items stored (1)");
		}
		TEST_METHOD(CorrectSampleCountMany) {
			std::shared_ptr<ITrainReader> mainDataReader(new FakeStationData());
			std::shared_ptr<ITimer> dataTimer(new FakeTimer());

			Statistics s(mainDataReader, dataTimer);
			long sampleTime = -1;

			for (int i = 0; i < 25; i++)
				sampleTime = s.readData();

			long sampleCount = s.sampleCount(sampleTime);
			Assert::AreEqual(25l, sampleCount, L"sampleCount did not return the correct count of the number of items stored (25)");
		}

		// Duration Tests
		TEST_METHOD(CorrectGetDurationValidRequest) {
			std::shared_ptr<ITrainReader> mainDataReader(new FakeStationData());
			std::shared_ptr<ITimer> dataTimer(new FakeTimer());

			Statistics s(mainDataReader, dataTimer);

			for (int i = 0; i < 50; i++)
				s.readData();

			long beforeClear = s.getDuration(32337);
			Assert::AreEqual(32337l - 31692l, beforeClear, L"getDuration did not calculate the correct duration from the arrival and departure times.");
		}
		TEST_METHOD(CorrectGetDurationEmpty) {

			auto func = [] {
				std::shared_ptr<ITrainReader> mainDataReader(new FakeStationData());
				std::shared_ptr<ITimer> dataTimer(new FakeTimer());

				Statistics s(mainDataReader, dataTimer);
				long beforeClear = s.getDuration(48154);
			};

			Assert::ExpectException<std::invalid_argument>(func, L"getDuration did not throw invalid_argument when empty.");
		}
		TEST_METHOD(CorrectGetDurationOutOfRange) {
			auto func = [] {
				std::shared_ptr<ITrainReader> mainDataReader(new FakeStationData());
				std::shared_ptr<ITimer> dataTimer(new FakeTimer());

				Statistics s(mainDataReader, dataTimer);

				for (int i = 0; i < 50; i++)
					s.readData();

				long beforeClear = s.getDuration(24 * 3600 + 1);
			};

			Assert::ExpectException<std::out_of_range>(func, L"getDuration did not throw out_of_range when sent a time greater than 24 hours.");
		}
		TEST_METHOD(CorrectGetDurationInvalidRequest) {

			auto func = [] {  
			std::shared_ptr<ITrainReader> mainDataReader(new FakeStationData());
			std::shared_ptr<ITimer> dataTimer(new FakeTimer());

			Statistics s(mainDataReader, dataTimer);
			long beforeClear = s.getDuration(48154);
			};

			Assert::ExpectException<std::invalid_argument>(func,L"getDuration did not throw invalid_argument when sent an incorrect log time.");	
		}

	};
}