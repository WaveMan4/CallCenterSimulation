#pragma once
#include <list>
#include <stdlib.h>     
#include <time.h>     
#include <random>
#include "callqueue.h"
#include "customer.h"
#include "nonsubscriber.h"
#include "paidsubscriber.h"
#include "techsupportrep.h"

class CallCenterSimulation
{
	public:
		int numOfCustomers;
		int totalTimeForAllCustomers;
		int waitTimeForAllCustomers;
		CallCenterSimulation() { numOfCustomers = 0; totalTimeForAllCustomers = 0; waitTimeForAllCustomers = 0; }
		CallQueue simCallQueue;
		std::list<TechSupportRep> simRepresentatives;
		TechSupportRep currentRepresentative;
		bool techSupportRepisAvailable()
		{
			for (std::list<TechSupportRep>::iterator it = simRepresentatives.begin(); it != simRepresentatives.end(); ++it)
			{
				if (!(*it).isBusy)
				{
					currentRepresentative = *it;
					return true;
				}
			}
			return false;
		}
		void assignToRep(int minute)
		{
			//Retrieve customer at this minute
			Customer nextCustomer = simCallQueue.callQ.top();
			numOfCustomers++;
			simCallQueue.callQ.pop();
			nextCustomer.setQueue_Time(minute);
			nextCustomer.setWait_Time(minute - nextCustomer.getArrival_Time());
			waitTimeForAllCustomers += (minute - nextCustomer.getArrival_Time());
			currentRepresentative.registerStartTime(minute);
			currentRepresentative.isBusy = true;

			/*Average of 25 calls per hour (using exmponential distribution);
			mean:			6 minutes
			standard dev:	2 minutes*/
			std::default_random_engine e;
			std::normal_distribution<double> normalDistRandNums(6.0, 2.0);

			double number = normalDistRandNums(e);
			int serviceTime = (int)number;
			nextCustomer.setService_Time(serviceTime);
			currentRepresentative.registerEndTime(minute + serviceTime);
			totalTimeForAllCustomers += (nextCustomer.getWait_Time() + (currentRepresentative.endTime - currentRepresentative.startTime));
		}
		void checkOtherReps(int minute)
		{
			for (std::list<TechSupportRep>::iterator it = simRepresentatives.begin(); it != simRepresentatives.end(); ++it)
			{
				if ((*it).isBusy && (minute > (*it).endTime))
				{
					(*it).isBusy = false;
					(*it).startTime = 0;
					(*it).endTime = 0;
				}
			}
		}

};