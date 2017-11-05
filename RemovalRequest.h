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
	
	RemovalRequest(bool abilityToPay, bool payInFull, bool makeContribution, Animal * animal, Client * client, std::string intendedDate, std::string creationDateAndTime, std::string address){
		this -> setReason("Removal Request");
		this -> setAbilityToPay(abilityToPay);
		this -> setPayInFull(payInFull);
		this -> setMakeContribution(makeContribution);
		this -> setAnimal(animal);
		this -> setClient(client);
		this -> setIntendedDate(intendedDate);
		this -> setCreationDateAndTime(creationDateAndTime);
		this -> address = address;
		//Remember to change outcome
	}
	
	~RemovalRequest()
	{

	}
	

private:
	std::string address;
	bool keptForAdoption;
};

#endif