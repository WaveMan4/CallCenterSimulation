#pragma once

class Customer
{
	private:
		unsigned int arrival_time;
		unsigned int queue_time;
		unsigned int service_time;
		unsigned int total_time;
		unsigned int wait_time;
	public:
		Customer() 
		{ 
			arrival_time = 0; 
			queue_time = 0; 
			service_time = 0; 
			total_time = 0; 
			wait_time = 0; 
			priority = 2; 
		}
		Customer(unsigned short p) 
		{ 
			arrival_time = 0;
			queue_time = 0;
			service_time = 0;
			total_time = 0;
			wait_time = 0;
			priority = p;
		}
		unsigned short priority;
		unsigned int getArrival_Time() { return arrival_time; }
		unsigned int getQueue_Time() { return queue_time; }
		unsigned int getService_Time() { return service_time; }
		unsigned int getTotal_Time() { return total_time; }
		unsigned int getWait_Time() { return wait_time; }
		void setArrival_Time(unsigned int a) { arrival_time = a; }
		void setQueue_Time(unsigned int q) { queue_time = q;  }
		void setService_Time(unsigned int s) { service_time = s;  }
		void setTotal_Time(unsigned int t) { total_time = t; }
		void setWait_Time(unsigned int w) { wait_time = w; }
		void calculateTotalTime() {}
		void calculateWaitTime() {}
};