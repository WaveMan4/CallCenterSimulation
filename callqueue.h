#pragma once

#include "customer.h"
#include <queue>
#include <vector>

class CallerCompare
{
public:
	bool operator()(Customer& x, Customer& y) 
	{ 
		bool priorityfirst = (x.priority > y.priority);
		bool timenext = (x.getArrival_Time() < y.getArrival_Time());
		//priority-check
		//	then arrival time
		if (!priorityfirst)
		{
			return priorityfirst;
		}
		else timenext;
	}
};

class CallQueue
{
	public:
		CallQueue() {}
		std::priority_queue<Customer, std::vector<Customer>, CallerCompare> callQ;	//initialize priority queue
		void addCustomer(Customer cust)
		{
			callQ.push(cust);
		}
};