#include <iostream>
#include <string>
#include <conio.h>
#include <windows.h>
#include "HealthFacility.h"
#include "PlaceForInspection.h"
#include "RemovalRequest.h"

//Health Facility Data is defined here. The data is hard coded as there is no indication of a need to change the data later on
int days[] = {1, 2, 3, 4, 5, 6};
int days2[] = {0, 6};
HealthFacility * facilities[2] = { new HealthFacility("10 Winchester Road", days, "Full"), new HealthFacility("Caymanas Track Limited", days2, "Mobile") };


std::vector<std::string> facilityAddresses = { facilities[0] -> getAddress(), facilities[1] -> getAddress() };

//Vectors for storing objects
std::vector<Client *> clients;
std::vector<Animal *> animals;

//Yes no option menu
std::vector<std::string> yesNoOptions = {"Yes", "No"};

int displayArrowMenu(std::string message, std::vector<std::string> menuItems)
{
    unsigned int position = 0, character = 0;
    while (character != 13)
    {
        system("cls");
        std::cout << message << std::endl;
        for(unsigned int x = 0; x < menuItems.size(); x++) std::cout << (x == position ? "-->" : "  ") << menuItems[x] << (x == position ? "<--" : "  ") << std::endl;
        character = (character = getch()) == 224 ? getch() : character;
        (character == 72 && position != 0) ? position-- : (character == 80 && position != menuItems.size() - 1) ? position++ : false;
    }
    return position + 1;
}



std::string getString(std::string message){
    std::cout << message << std::endl << ">";
    std::cin.sync();
    getline(std::cin, message);
    return message;
}

int getNumber(std::string message){
    std::cout << message << std::endl << "#";
    int number;
    std::cin >> number;
    return number;
}

bool getBoolean(std::string message){
    return displayArrowMenu(message, yesNoOptions);
}

std::vector<std::string> getAllClientNames(){
    std::vector<std::string> clientNames;
    for(int x = 0; x < clients.size(); x++){
        clientNames.push_back(clients[x] -> getFName() + " " + clients[x] -> getLName());
    }
    return clientNames;
}

Client * getClient(std::string message){
    return clients[displayArrowMenu(message , getAllClientNames())];
}

std::vector<std::string> getAllBasicAnimalInfo(){
    std::vector<std::string> animalInfo;
    for(int x = 0; x < animals.size(); x++){
        std::string animal = (animals[x] -> getName() + "\t" + animals[x] -> getType() + '\t' + animals[x] -> getBreed());
        animalInfo.push_back(animal);
    }
    return animalInfo;
}

void displayAnimal(){
    animals[displayArrowMenu("Select the animal to view", getAllBasicAnimalInfo()) - 1] -> display();
    system("pause");
}

void addAnimal(){
    std::string name = getString("Enter the animal's name");
    std::string type = getString("Enter the type of animal");
    std::string gender = getString("Enter the animal's gender");//Change Genders to list
    std::string breed = getString("Enter the animal's breed");
    int approxAge = getNumber("Enter the age");
    bool adoptionCandidate = getBoolean("Is this animal a candidate for adoption?");
    Animal * newAnimal = new Animal(name, type, gender, breed, approxAge, adoptionCandidate);
    animals.push_back(newAnimal);
    bool owned = false;
    if(clients.size() > 0){
        owned = getBoolean("Does the animal have an owner?");
    }
    if(owned){
        animals[animals.size()] -> setOwner(getClient("Select the owner")); 
    }
}

void executeAnimalFunction(int functionNumber){
    switch(functionNumber){
        case 1:
            displayAnimal();
            break;
        case 2:
            addAnimal();
            break;
    }
}

void animalMenu(){
    std::vector<std::string> animalOptions = {"Display All Animals", "Add Animal", "Euthanize Animal"};
    executeAnimalFunction(displayArrowMenu("Choose an option", animalOptions));
}


void execuseClientFunction(int functionNumber){
    
}

void clientMenu(){
    std::vector<std::string> clientOptions = {"Display all Clients", "Add a Client", "Remove a Client"};

}


void executeMenuOption(int option){
    switch(option){
        case 1:
            animalMenu();
            break;
        case 2:
            clientMenu();

        
    }
}

int main()
{
    std::vector<std::string> menuOptions = {"Animals", "Clients", "Event Records", "Places for Inspection", "Veterinarians", "Exit"};


    int menuOption = 0;
    while((menuOption = menuOption = displayArrowMenu("Main Menu\n", menuOptions)) != 6)
    {
        
        executeMenuOption(menuOption);
    }

    return 0;
}

// Time Stuff
// struct tm * test;
// time_t dummy;

// time(&dummy);
// test = localtime(&dummy);

// test -> tm_mday = 27;
// test -> tm_mon = 2;
// test -> tm_year = 0;
// test -> tm_hour = 15;
// test -> tm_min = 30;
// test -> tm_sec = 45;



// mktime(test);

// std::cout << asctime(test);
// std::cin.get();