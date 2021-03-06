//Created by Philip newman and Brandon Chung

#ifndef ANIMAL_H
#define ANIMAL_H

#include "Client.h"
#include <string>
#include <fstream>
class Animal
{
public:
	Animal()
	{
		incrementCounter();
		this -> id = numberOfAnimals;
		this -> name = "N/A";
		this -> type = "N/A";
		this -> gender = "N/A";
		this -> breed = "N/A";
		this -> approxAge = 0;
		this -> adoptionCandidate = false;
		this -> owner = 0;
	}
	
	Animal(std::string name, std::string type, std::string gender, std::string breed, int approxAge, bool adoptionCandidate)
	{
		incrementCounter();
		this -> id = numberOfAnimals;
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
	int getId(){
		return id;
	}

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
	void setId(int id){
		this -> id = id;
	}

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

	static void setNumberOfAnimals(int numberOfAnimals){
		Animal::numberOfAnimals = numberOfAnimals;
	}

	bool euthanize(){
		this -> ~Animal();
	}

	void incrementCounter(){
		numberOfAnimals++;
	}

	void display(){
		std::cout << "ID\t" << id << std::endl << "Name:\t" << name << std::endl << "Type:\t" << type << std::endl << "Gender:\t" << gender << std::endl;
		std::cout << "Breed:\t" << breed << std::endl << "Approx Age:\t" << approxAge << std::endl << "Adoption Candidate:\t" << (adoptionCandidate ? "Yes" : "No") << std::endl;
		if(owner){
			std::cout << "Owner Name:\t" << (owner -> getFName()) << " " << (owner -> getLName()) << std::endl;
		}
	}

	void writeToFile(){
		std::ofstream animalWriter;
		try{
			animalWriter.open("newAnimals.txt", std::ios::app);
			animalWriter << id << '\t' << name << '\t' << type << '\t' << gender << '\t' << breed << '\t' << approxAge << '\t' << adoptionCandidate << '\t';// << (owner ? owner -> getEmail() : 0) << std::endl;
			if(!owner){
				animalWriter << 0 << '\n';
			} else {
				animalWriter << (owner -> getId()) << '\n';
			}
			animalWriter.close();
		} catch (std::exception& e){
			system("cls");
			std::cout << "Failure while storing animals" << std::endl;
			system("pause");
		}
	}

private:
	int id;
	std::string name;
	std::string type;
	std::string gender;
	std::string breed;
	int approxAge;
	bool adoptionCandidate;
	Client * owner;
	static int numberOfAnimals;
};

int Animal::numberOfAnimals = 0;

#endif