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
	
	
	~HealthFacility()
	{
	}


private:
	std::string address;
	std::string openingDays[7];
	std::vector<Intervention *> staffRecords;
	std::string typeOfFacility;
	std::vector<Veterinarian *> veterinarians;
};

#endif