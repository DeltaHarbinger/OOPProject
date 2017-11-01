#ifndef INTERVENTION_H
#define INTERVENTION_H

#include <string>
#include "Client.h"
#include "Animal.h"
#include <ctime>
class Intervention
{
public:
	Intervention()
	{
	}
	
	~Intervention()
	{
	}
	

private:
	int interventionNumber;
	std::string reason;
	bool abilityToPay;
	bool makeContribution;
	bool payInFull;
	Animal * animal;
	Client * client;
	struct tm * intendedDate;
	struct tm * creationDateAndTime;


};

#endif