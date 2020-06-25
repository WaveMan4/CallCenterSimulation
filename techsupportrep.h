#pragma once

#include "customer.h"

class TechSupportRep
{
	private: 
		unsigned int employeeSlotNumber;
	public:
		TechSupportRep() { isBusy = false; employeeSlotNumber = 0; startTime = 0; endTime = 0; }
		TechSupportRep(unsigned int esn, bool busy) 
		{ 
			employeeSlotNumber = esn; 
			isBusy = busy; 
			startTime = 0; 
			endTime = 0;
		}
		bool isBusy;
		int startTime;
		int endTime;
		unsigned int getEmployeeSlotNumber() { return employeeSlotNumber; }
		void setEmployeeSlotNumber(unsigned int esn) { employeeSlotNumber = esn; }
		void registerStartTime(int m) { startTime = m; }
		void registerEndTime(int m) { endTime = m; }
};