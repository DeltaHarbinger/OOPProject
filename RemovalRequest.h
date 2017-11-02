#ifndef REMOVALREQUEST_H
#define REMOVALREQUEST_H

#include <string>
#include "Intervention.h"
class RemovalRequest: public Intervention
{
public:
	RemovalRequest()
	{
	}
	
	
	~RemovalRequest()
	{
	}
	

private:
	std::string address;
	bool keptForAdoption;
};

#endif