#pragma once
#include "Client.h"
#include <string>
class Animal
{
public:
	Animal()
	{
	}
	
	Animal(std::string name, std::string type, std::string gender, std::string breed, int approxAge, bool adoptionCandidate){
		this -> name = name;
		this -> type = type;
		this -> gender = gender;
		this -> breed = breed;
		this -> approxAge = approxAge;
		this -> adoptionCandidate = adoptionCandidate;
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

