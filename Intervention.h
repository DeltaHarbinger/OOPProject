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
	
	Intervention(std::string reason, bool abilityToPay, bool payInFull, bool makeContribution, Animal * animal, std::string intendedDate, std::string creationDateAndTime){
		numberOFInterventions++;
		this -> interventionNumber = numberOFInterventions;
		this -> reason = reason;
		this -> abilityToPay = abilityToPay;
		this -> payInFull = payInFull;
		this -> makeContribution = makeContribution;
		this -> animal = animal;
		this -> client = animal -> getOwner();
		this -> intendedDate = intendedDate;
		this -> creationDateAndTime = creationDateAndTime;
	}

	~Intervention()
	{
	}
	
	int getInterventionNumber(){
		return interventionNumber;
	}

	std::string getReason(){
		return reason;
	}

	bool getAbilityToPay(){
		return abilityToPay;
	}

	bool getPayInFull(){
		return payInFull;
	}

	bool getMakeContribution(){
		return makeContribution;
	}

	Animal * getAnimal(){
		return animal;
	}

	Client * getClient(){
		return client;
	}

	std::string getIntendedDate(){
		return intendedDate;
	}

	std::string getcreationDateAndTime(){
		return creationDateAndTime;
	}

	void display(){
		std::cout << "Intervention Number:\t" << interventionNumber << std::endl << "Reason:\t" << reason << std::endl << "Able to pay:\t" << (abilityToPay ? "Yes" : "No") ;
		std::cout << "Paid in full:\t" << (payInFull ? "Yes" : "No") << std::endl << "Contribution made:\t" << (makeContribution ? "Yes" : "No") << std::endl;
		client -> display();
		animal -> display();
		std::cout << "Date of appointment:\t" << intendedDate << std::endl;
		std::cout << "Appointment creation date:\t" << creationDateAndTime << std::endl;
	}

private:
	int interventionNumber;
	std::string reason;
	bool abilityToPay;
	bool payInFull;
	bool makeContribution;
	Animal * animal;
	Client * client;
	std::string intendedDate;
	std::string creationDateAndTime;
	static int numberOFInterventions;

};
int Intervention::numberOFInterventions = 0;

#endif