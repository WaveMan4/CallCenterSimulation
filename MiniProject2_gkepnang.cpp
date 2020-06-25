// MiniProject2_gkepnang.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <random>
#include <list>
#include "callcentersimulation.h"
#include "callqueue.h"
#include "customer.h"
#include "techsupportrep.h"

using namespace std; 

list<double> callTimes;

int main()
{
	//Create exponential distribution
	default_random_engine e;
	exponential_distribution<> expoRandNums(25.0);

	/*Average of 25 calls per hour (using exmponential distribution);
		mean:			6 minutes
		standard dev:	2 minutes*/
	normal_distribution<double> normalDistRandNums(6.0, 2.0);

	CallCenterSimulation ccs;
	////Create counter
	int minutes = 0;

	////Create 3 technical support representatives
	TechSupportRep rep1(1, false);
	TechSupportRep rep2(2, false);
	TechSupportRep rep3(3, false);
	ccs.simRepresentatives.push_back(rep1);
	ccs.simRepresentatives.push_back(rep2);
	ccs.simRepresentatives.push_back(rep3);

	////RNG for customer calls
	srand(time(NULL)); // initialize random seed:

	unsigned short subscriber_or_not = 0;

	//Sequence for Simulation:
	//	1. Receive call
		// a) Assign arrival time to Customer
		// b) Queue the customer
		// c) Measure queue time
	//	2. Give to tech support rep
		// a) Find available tech support rep
		// b) Assign start time to Customer
	//  3. Handle Call
		// a) Service customer 
		// b) Assign service time to Customer
	//	4. Repeat again
	
	double v = 0;
	double interArrivalTime = 0;
	double arrivalTime = 0;
	
	int nextCall = 0;
	
	Customer currentCustomer;
	   
	//Start counter
	for (int hour=0; hour < 24; hour++)
	{

		for (int i = 0; i < 25; i++)
		{
			v = expoRandNums(e);
			arrivalTime += (v * 40);
			callTimes.push_back(arrivalTime);
			cout << "InterArrival = " << v << "\tArrivalTime = " << arrivalTime << endl;
		}

		for (int minute = 0; minute < 60; minute++)
		{
			//read front element of minute
			if (callTimes.size() > 0)
				nextCall = (int)callTimes.front();
			else
				break;

			//Check <current minute interval> compared to <time interval for phonecall> 
			if (minute == nextCall)
			{
				//If minute is equal to time for expected or slightly after...
				//	then create customer calls 
				subscriber_or_not = rand() % 2 + 1;
				if (subscriber_or_not == 1 || subscriber_or_not == 2)
				{
					//Queuing the customer
					currentCustomer = Customer(subscriber_or_not);
					currentCustomer.setArrival_Time((hour * 60) + minute);
					ccs.simCallQueue.addCustomer(currentCustomer);

					//Handling customer request
					if (ccs.techSupportRepisAvailable())
					{
						ccs.assignToRep((hour * 60) + minute);
					}
				}

				callTimes.pop_front();
			}
			
			//Checking status of other reps
			ccs.checkOtherReps((hour * 60) + minute);
		}

		callTimes.clear();
		
		arrivalTime = 0; 
	}

	//After simulation, then tally the following: 
	// 1) Number of customers serviced by the help center
	// 2) Average total time for each customer (queue time + wait time)
	// 3) Average wait time for each customer in the queue
	cout << "\n Mini Project 2 Output \n======================================================================================================" << endl;
	cout << "The number of customers serviced by the help center: " << ccs.numOfCustomers << endl;
	cout << "The average total time in the system for a customer (queue time + service time): " << (double) ((ccs.totalTimeForAllCustomers)/(ccs.numOfCustomers)) << endl;
	cout << "The average wait time in the caller queue for a customer: " << (double) ((ccs.waitTimeForAllCustomers) / (ccs.numOfCustomers)) << endl;
		
	return 0;
}

int nextCall(list<double> const& list, int minute)
{
	int currMinute = 0;
	for (auto it = list.cbegin(); it != list.cend(); it++)
	{
		currMinute = (int)* it;
		if (currMinute > minute) return currMinute;
	}
}