//Created by Philip newman and Brandon Chung

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
		incrementNumberOfInterventions();
		this -> setInterventionNumber(getNumberOfInterventions());
		this -> setReason("Removal Request");
		this -> setAbilityToPay(abilityToPay);
		this -> setPayInFull(payInFull);
		this -> setMakeContribution(makeContribution);
		this -> setAnimal(animal);
		this -> setClient(client);
		this -> setIntendedDate(intendedDate);
		this -> setCreationDateAndTime(creationDateAndTime);
		this -> address = address;
		this -> keptForAdoption = 2;
		//Remember to change outcome
	}
	
	~RemovalRequest()
	{

	}
	
	bool getKeptForAdoption() override{
		return keptForAdoption;
	}

	void setKeptForAdoption(bool keptForAdoption) override{
		this -> keptForAdoption = keptForAdoption;
	}

	void display() override {
		std::cout << "Intervention Number:\t" << getInterventionNumber() << std::endl << "Reason:\t" << getReason() << std::endl << "Able to pay:\t" << (getAbilityToPay() ? "Yes" : "No")  << std::endl;
		std::cout << "Paid in full:\t" << (getPayInFull() ? "Yes" : "No") << std::endl << "Contribution made:\t" << (getMakeContribution() ? "Yes" : "No") << std::endl;
		getClient() -> display();
		getAnimal() -> display();
		std::cout << "Date of appointment:\t" << getIntendedDate() << std::endl;
		std::cout << "Appointment creation date:\t" << getCreationDateAndTime() << std::endl << "Result:\t" << (!keptForAdoption ? "Euthanized" : (keptForAdoption == 2 ? "Not Concluded" : "Kept") ) ; 
	}

	bool writeToFile(int facilityNumber) override {
		std::ofstream interventionWriter;
		bool success = true;
		system("cls");
		try{
			interventionWriter.open("newInterventions.txt", std::ios::app);
			interventionWriter << facilityNumber << '\t' << getInterventionNumber() << '\t' << getReason() << '\t' << getAbilityToPay() << '\t' << getPayInFull() << '\t' << getMakeContribution() << '\t' << (getAnimal() -> getId()) << '\t' << (getClient() -> getId()) << '\t' << getIntendedDate() << '\t' << getCreationDateAndTime() << '\t' << address << '\t' << keptForAdoption << '\n';
			interventionWriter.close();
		} catch(std::exception& e){
			system("cls");
			success = false;
			std::cout << "Failure while storing request" << std::endl;
			system("pause");
		}
		return success;
	}

private:
	std::string address;
	bool keptForAdoption;
};

#endif