//Created by Philip newman and Brandon Chung

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
		incrementNumberOfInterventions();
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
	
	//Getters
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

	std::string getCreationDateAndTime(){
		return creationDateAndTime;
	}


	//Setters
	void setInterventionNumber(int interventionNumber){
		this -> interventionNumber = interventionNumber;
	}

	void setReason(std::string reason){
		this -> reason = reason;
	}

	void setAbilityToPay(bool abilityToPay){
		this -> abilityToPay = abilityToPay;
	}

	void setPayInFull(bool payInFull){
		this -> payInFull = payInFull;
	}

	void setMakeContribution(bool makeContribution){
		this -> makeContribution = makeContribution;
	}

	void setAnimal(Animal * animal){
		this -> animal = animal;
	}

	void setClient(Client * client){
		this -> client = client;
	}

	void setIntendedDate(std::string intendedDate){
		this -> intendedDate = intendedDate;
	}

	void setCreationDateAndTime(std::string creationDateAndTime){
		this -> creationDateAndTime = creationDateAndTime;
	}

	virtual void display(){
		std::cout << "Intervention Number:\t" << interventionNumber << std::endl << "Reason:\t" << reason << std::endl << "Able to pay:\t" << (abilityToPay ? "Yes" : "No")  << std::endl;
		std::cout << "Paid in full:\t" << (payInFull ? "Yes" : "No") << std::endl << "Contribution made:\t" << (makeContribution ? "Yes" : "No") << std::endl;
		client -> display();
		animal -> display();
		std::cout << "Date of appointment:\t" << intendedDate << std::endl;
		std::cout << "Appointment creation date:\t" << creationDateAndTime << std::endl;
	}

	void incrementNumberOfInterventions(){
		numberOFInterventions++;
	}

	int getNumberOfInterventions(){
		return numberOFInterventions;
	}

	virtual bool writeToFile(int facilityNumber){
		std::ofstream interventionWriter;
		bool success = true;
		try{
			interventionWriter.open("newInterventions.txt", std::ios::app);
			interventionWriter << facilityNumber << '\t' << interventionNumber << '\t' << reason << '\t' << abilityToPay << '\t' << payInFull << '\t' << makeContribution << '\t' << (animal -> getId()) << '\t' << (client -> getId()) << '\t' << intendedDate << '\t' << creationDateAndTime << '\n';
			interventionWriter.close();
		} catch(std::exception& e){
			system("cls");
			success = false;
			std::cout << "Failure while storing intervention" << std::endl;
			system("pause");
		}
		return success;
	}

	virtual bool getKeptForAdoption(){
		
	}

	virtual void setKeptForAdoption(bool keptForAdoption){

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