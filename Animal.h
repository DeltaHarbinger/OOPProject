#pragma once
#include "Client.h"
#include <string>
class Animal
{
public:
	Animal()
	{
	}
	
	
	~Animal()
	{
	}

private:
	std::string name;
	std::string type;
	std::string gender;
	std::string breed;
	int approxAge;
	bool adoptionCandidate;
	Client * owner;

};

