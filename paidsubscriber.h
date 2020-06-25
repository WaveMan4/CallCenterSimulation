#pragma once

#include "customer.h"

class PaidSubscriber : public Customer
{
	public: 
		PaidSubscriber() {}
		const unsigned short priority = 1;
};