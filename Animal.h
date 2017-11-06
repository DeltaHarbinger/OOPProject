#ifndef ANIMAL_H
#define ANIMAL_H

#include "Client.h"
#include <string>
class Animal
{
public:
	Animal()
	{
		this -> name = "N/A";
		this -> type = "N/A";
		this -> gender = "N/A";
		this -> breed = "N/A";
		this -> approxAge = 0;
		this -> adoptionCandidate = false;
		this -> owner = 0;
	}
	
	Animal(std::string name, std::string type, std::string gender, std::string breed, int approxAge, bool adoptionCandidate){
		this -> name = name;
		this -> type = type;
		this -> gender = gender;
		this -> breed = breed;
		this -> approxAge = approxAge;
		this -> adoptionCandidate = adoptionCandidate;
	}
	
	Animal(std::string type, std::string breed) : Animal(){
		this -> type = type;
		this -> breed = breed;
	}

	~Animal()
	{
	}

	//Getters
	std::string getName(){
		return name;
	}

	std::string getType(){
		return type;
	}

	std::string getGender(){
		return gender;
	}

	std::string getBreed(){
		return breed;
	}

	int getApproxAge(){
		return approxAge;
	}

	bool getAdoptionCandidate(){
		return adoptionCandidate;
	}

	Client * getOwner(){
		return owner;
	}


	//Setters
	void setName(std::string name){
		this -> name = name;
	}

	void setType(std::string type){
		this -> type = type;
	}

	void setGender(std::string gender){
		this -> gender = gender;
	}

	void setBreed(std::string breed){
		this -> breed = breed;
	}

	void setApproxAge(int approxAge){
		this -> approxAge = approxAge;
	}

	void setAdoptionCandidate(bool adoptionCandidate){
		this -> adoptionCandidate = adoptionCandidate;
	}

	void setOwner(Client * owner){
		this -> owner = owner;
	}

	bool euthanize(){
		this -> ~Animal();
	}

	void display(){
		std::cout << "Name:\t" << name << std::endl << "Type:\t" << type << std::endl << "Gender:\t" << gender << std::endl;
		std::cout << "Breed:\t" << breed << std::endl << "Approx Age:\t" << approxAge << std::endl << "Adoption Candidate:\t" << (adoptionCandidate ? "Yes" : "No") << std::endl;
		if(owner){
			std::cout << "Owner Name:\t" << (owner -> getFName()) << " " << (owner -> getLName()) << std::endl;
		}
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

#endif