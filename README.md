# OOP-SA02-StationLog
Template for the BSc. Computer Science Assignment

## Project setup process
1. Download this repository as a zip or clone into visual studio.
1. Unzip the repository on your machine before completing the next step.
1. Open the solution file, there will be a program solution and two test projects.
1. Right click on the StationLog project and select Properties.
   * Select C/C++
   * Precompiled Headers
   * Precompiled Header
   * Select the Not Using Precompiled Headers option
1. Select the Test menu from visual studio
   * Test Settings
   * Default Processor Architecture
   * X64
   
To compile and test your solution will require you to write all the method signatures for the class, if a method returns a long add { return -1; } to the end of the signature, if it returns a double add { return -1.0; }, once this is completed all the tests will fail apart from readdata.  Read data will not store any readings until you add a data structure to your class such as a vector or an array and write code in read data to store the readings.

Sample of getting start and end times based on a duration

``` C++
long Statistics::sampleCount(long duration) 
{ 
	long endTime = _timer->time();
	long startTime = endTime - duration;

	return -1; 

}
```
