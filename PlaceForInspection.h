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

	void writeToFile()
	{
		std::ofstream streamy;
		try{
			streamy.open("newPlacesForInspection.txt", std::ios::app);
			streamy << name << "\t" << typeOfPlace << "\t" << passInspection << "\n";
			streamy.close();
		}catch(std::exception& error)
		{
			system("cls");
			std::cout << "Error writing PlacesForInspection to the file!" << std::endl;
			system("pause");
		}
		try{
			if(streamy.is_open())
				streamy.close();
		}catch(std::exception& error)
		{ }
	}

private:
	std::string name;//write these 
	std::string typeOfPlace;//write
	bool passInspection;
};

#endif