#pragma once

#include "customer.h"

class NonSubscriber : public Customer
{
	public:
		NonSubscriber() {}
		const unsigned short priority = 2;
};