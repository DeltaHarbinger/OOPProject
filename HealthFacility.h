#ifndef HEALTHFACILITY_H
#define HEALTHFACILITY_H

#include <string>
#include <vector>
#include "Intervention.h"
#include "Veterinarian.h"
class HealthFacility
{
public:
	HealthFacility()
	{
	}
	
	HealthFacility(std::string address, int openingDays[], std::string typeOfFacility){
		this -> address = address;
		std::copy(openingDays, openingDays + 6, this -> openingDays);
		this -> typeOfFacility = typeOfFacility;
	}
	
	~HealthFacility()
	{
	}

	//Getters
	std::string getAddress(){
		return address;
	}

	int * getOpeningDays(){
		return openingDays;
	}

	std::vector<Veterinarian *> getVeterinarians(){
		return veterinarians;
	}

	std::vector<Intervention *> getStaffRecords(){
		return staffRecords;
	}

	void addVeterinarian(Veterinarian * veterinarian){
		veterinarians.push_back(veterinarian);
	}

	void addStaffRecord(Intervention * record){
		staffRecords.push_back(record);
	}

private:
	std::string address;
	//Days start on Sunday with is represented as 0
	int openingDays[7];
	std::string typeOfFacility;
	std::vector<Veterinarian *> veterinarians;
	std::vector<Intervention *> staffRecords;
};

#endif