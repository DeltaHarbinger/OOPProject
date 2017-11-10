#ifndef PLACEFORINSPECTION_H
#define PLACEFORINSPECTION_H

#include <string>
class PlaceForInspection
{
public:
	PlaceForInspection()
	{
	}
	
	PlaceForInspection(std::string name, std::string typeOfPlace){
		this -> name = name;
		this -> typeOfPlace = typeOfPlace;
		this -> passInspection = false;
	}

	~PlaceForInspection()
	{
	}
	
	bool inspect() 
	{
		//Temporary
		return true;
	}
	
	std::string getName(){
		return name;
	}

	std::string getTypeOfPlace(){
		return typeOfPlace;
	}

	bool getPassInspection(){
		return passInspection;
	}

	void display(){
		std::cout << "Name:\t" << name << std::endl << "Type of place:\t" << typeOfPlace << std::endl << "Passed last inspection:\t" << (passInspection ? "Yes" : "No") << std::endl;
	}

private:
	std::string name;
	std::string typeOfPlace;
	bool passInspection;
};

#endif