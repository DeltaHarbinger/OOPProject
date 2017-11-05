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
std::vector<std::string> healthFacilityAddresses = {"10 Winchester Road", "Caymanas Track Limited"};
HealthFacility * facilities[2] = { new HealthFacility(healthFacilityAddresses[0], days, "Full"), new HealthFacility(healthFacilityAddresses[1], days2, "Mobile") };


std::vector<std::string> facilityAddresses = { facilities[0] -> getAddress(), facilities[1] -> getAddress() };

//Vectors for storing objects
std::vector<Client *> clients;
std::vector<Animal *> animals;


//Yes no option menu
std::vector<std::string> yesNoOptions = {"Yes", "No"};
//Menu options used in main menu
std::vector<std::string> menuOptions = {"Animals", "Clients", "Appointments", "Removal Requests", "Places for Inspection", "Veterinarians", "Exit"};



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
    std::cout << message << std::endl << "> ";
    std::cin.sync();
    getline(std::cin, message);
    return message;
}

int getNumber(std::string message){
    std::cout << message << std::endl << "# ";
    int number;
    std::cin >> number;
    return number;
}

bool getBoolean(std::string message){
    return displayArrowMenu(message, yesNoOptions);
}

int getMonth(std::string message){
    std::vector<std::string> months = {"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};
    return (displayArrowMenu(message, months) - 1);
}

bool validDay(int year, int month, int day){
    if(day < 1 || year < 1)
        return false;
    switch(month){
        case 1:
            if((year % 400 == 0) || (year % 100 != 0 && year % 4 == 0))
                return (day < 30) ? true : false;
            else
                return (day < 29) ? true : false;
            break;
        case 0:
        case 2:
        case 4:
        case 6:
        case 7:
        case 9:
        case 11:
            return (day < 32) ? true : false;
            break;
        default:
            return (day < 31) ? true : false;
    }
}

struct tm * getDate(){
    time_t source = time(NULL);
    struct tm * date = localtime(&source);
    date -> tm_year = getNumber("Enter the intended year for the appointment") - 1900;
    date -> tm_mon = getMonth("Select the intended month for the appointment");
    date -> tm_mday = getNumber("Enter the intended day for the appointment");
    while(!validDay(date -> tm_year, date -> tm_mon, date -> tm_mday)){
        std::cout << "Please enter a valid date";
        date -> tm_year = getNumber("Enter the intended year for the appointment") - 1900;
        date -> tm_mon = getMonth("Select the intended month for the appointment");
        date -> tm_mday = getNumber("Enter the intended day for the appointment");
    }
    return date;
}

bool animalsExist(){
    return animals.size() > 0;
}

bool clientsExist(){
    return clients.size() > 0;
}

bool interventionsExist(){
    return facilities[0] -> getStaffRecords().size() > 0 || facilities[1] -> getStaffRecords().size() > 0;
}



std::vector<std::string> getAllBasicAnimalInfo(){
    std::vector<std::string> animalInfo;
    for(int x = 0; x < animals.size(); x++){
        std::string animal = (animals[x] -> getName() + "\t" + animals[x] -> getType() + '\t' + animals[x] -> getBreed());
        animalInfo.push_back(animal);
    }
    return animalInfo;
}

std::vector<std::string> getAllClientNames(){
    std::vector<std::string> clientNames;
    for(int x = 0; x < clients.size(); x++){
        clientNames.push_back(clients[x] -> getFName() + " " + clients[x] -> getLName());
    }
    return clientNames;
}

HealthFacility * getHealthFacility(std::string message){
    return facilities[displayArrowMenu(message, healthFacilityAddresses) - 1];
}

Client * getClient(std::string message){
    return clients[displayArrowMenu(message, getAllClientNames()) - 1];
}

Animal * getAnimal(std::string message){
    return animals[displayArrowMenu(message, getAllBasicAnimalInfo()) - 1];
}

std::vector<Intervention *> getStaffRecords(HealthFacility * facility){
    return facility -> getStaffRecords();
}

std::vector<std::string> getAllBasicInterventionInfo(std::vector<Intervention *> interventions){
    std::vector<std::string> recordInfo;
    for(int x = 0; x < interventions.size(); x++){
        std::string info = (interventions[x] -> getInterventionNumber() + "\t" + interventions[x] -> getClient() -> getFName() + "\t" + interventions[x] -> getClient() -> getLName() + "\t" + interventions[x] -> getReason());
        recordInfo.push_back(info);
    }
    return recordInfo;
}

Intervention * getRecord(std::string message){
    HealthFacility * f = getHealthFacility("Select the health facility");
    std::vector<Intervention *> records = getStaffRecords(f);
    return records[displayArrowMenu(message, getAllBasicInterventionInfo(records)) - 1];
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
        Client * owner = getClient("Select the owner");
        std::cout << owner -> getFName() << " " << owner -> getLName();
        animals[animals.size() - 1] -> setOwner(owner); 
    }else{
        animals[animals.size() - 1] -> setOwner(0);
    }
}

void addClient(){
    std::string fName = getString("Enter the client's first name");
    std::string lName = getString("Enter the client's last name");
    std::string telephoneNo = getString("Enter the client's telephone number");
    std::string address = getString("Enter the client's address");
    std::string email = getString("Enter the client's email");
    Client * newClient = new Client(fName, lName, telephoneNo, address, email);
    clients.push_back(newClient);
}

void printInvalidDate(){
    system("cls");
    std::cout << "The date entered is not valid. Please enter a valid date" << std::endl;
    system("pause");
}

void addAppointment(){
    
    std::string reason = getString("State the reason for the appointment");
    bool abilityToPay = getBoolean("Does the client have the ability to pay?");
    bool payInFull = false;
    if(abilityToPay)
        payInFull = getBoolean("Will the client pay in full?");
    bool makeContribution = getBoolean("Does the client intend to make a contribution?");
    Animal * animal = getAnimal("Select the animal");

    struct tm * intendedDate = getDate();
    mktime(intendedDate);
    std::string intendedDateString = asctime(intendedDate);
    time_t currentTime = time(NULL);
    std::string currentTimeString = asctime(localtime(&currentTime));
    
    Intervention * newIntervention = new Intervention(reason, abilityToPay, payInFull, makeContribution, animal, intendedDateString, currentTimeString);
    getHealthFacility("Select the facility") -> addStaffRecord(newIntervention);
}

void addRemovalRequest(){

}

void addPlaceForInspection(){

}

void addVeterinarian(){

}

void createObject(int type){
    switch(type){
        case 1:
            addAnimal();
            break;
        case 2:
            addClient();
            break;
        case 3:
            if(animalsExist())
                addAppointment();
            else{
                std::cout << "There are currently no animals registered" << std::endl;
                system("pause");
            }
            break;
        case 4:
            addRemovalRequest();
            break;
        case 5:
            addPlaceForInspection();
            break;
        case 6:
            addVeterinarian();
            break;
    }
}

void updateObject(int option){

}

void displayAnimal(){
    system("cls");
    getAnimal("Select the animal to view") -> display();
    system("pause");
}

void displayClient(){
    system("cls");
    getClient("Select the client to view") -> display();
    system("pause");
}

void displayIntervention(){
    system("cls");
    getRecord("Select the record to be displayed") -> display();
    system("pause");
}

void displayObjectInfo(int type){
    switch(type){
        case 1:
            if(animalsExist())
                displayAnimal();
            else{
                system("cls");
                std::cout << "There are currently no animals registered." << std::endl;
                system("pause");
            }
            break;
        case 2:
            if(clientsExist())
                displayClient();
            else{
                system("cls");
                std::cout << "There are currently no clients registered." << std::endl;
                system("pause");
            }
            break;
        case 3:
            if(interventionsExist())
                displayIntervention();
            else{
                system("cls");
                std::cout << "There are currently no appointments recorded." << std::endl;
                system("pause");
            }
            
    }
}

void displayAllAnimals(){
    if(animalsExist())
        for(int x = 0; x < animals.size(); x++){
            system("cls");
            animals[x] -> display();
            system("pause");
        }
    else{
        std::cout << "There are currently no animals registered" << std::endl;
        system("pause");
    }
}

void displayAllClients(){
    if(clientsExist())
        for(int x = 0; x < clients.size(); x++){
            system("cls");
            clients[x] -> display();
            system("pause");
        }
    else{
        std::cout << "There are currently no clients registered" << std::endl;
        system("pause");
    }
}

void displayAllAppointments(){
    for(int x = 0; x < 2; x++){
        std::vector<Intervention *> staffRecords = facilities[x] -> getStaffRecords();
        if(staffRecords.size() > 0)
            for(int y = 0; y < staffRecords.size(); y++){
                if(staffRecords[y] -> getReason() != "Removal Requst"){
                    system("cls");
                    staffRecords[y] -> display();
                    system("pause");
                }
            }
        else{
            std::cout << "There are currently no records for the facility at " << facilities[x] -> getAddress() << std::endl;
            system("pause");
        }
    }
}

void displayAllObjectInfo(int option){
    switch(option){
        case 1:
            displayAllAnimals();
            break;
        case 2:
            displayAllClients();
            break;
        case 3:
            displayAllAppointments();
            break;
    }
}

void deleteAnimal(){
    if(animalsExist()){    
        int animalToBeDeleted = displayArrowMenu("Select the animal to be deleted", getAllBasicAnimalInfo()) - 1;
        animals[animalToBeDeleted] -> display();
        system("pause");
        if(displayArrowMenu("Delete the animal from the system?", yesNoOptions) == 1){
            system("cls");
            delete(animals[animalToBeDeleted]);
            std::cout << "The animal has been deleted from the system" << std::endl;
            animals.erase(animals.begin() + animalToBeDeleted);
            system("pause");
        } else {
            system("cls");
            std::cout << "The animal was not deleted" << std::endl;
        }
    } else {
        system("cls");
        std::cout << "There are currently no animals registered" << std::endl;
        system("pause");
    }
}

void deleteClient(){
    if(clientsExist()){
        int clientToBeDeleted = displayArrowMenu("Select the clien to be deleted", getAllClientNames()) - 1;
        clients[clientToBeDeleted] -> display();
        system("pause");
        if(displayArrowMenu("Delete the client? from the system?", yesNoOptions) == 1){
            system("cls");
            delete(clients[clientToBeDeleted]);
            std::cout << "The client has been deleted from the system" << std::endl;
            clients.erase(clients.begin() + clientToBeDeleted);
            system("pause");
        } else {
            system("cls");
            std::cout << "The client was not deleted" << std::endl;
            system("pause");
        }
    } else {
        system("cls");
        std::cout << "There are currently no clients registered" << std::endl;
        system("pause");
    }
}

void deleteAppointment(){
    int selectedFacility = displayArrowMenu("Select the facility tha the appointment was booked at", healthFacilityAddresses) - 1;
    std::vector<Intervention *> records = facilities[selectedFacility] -> getStaffRecords();
    if(records.size() > 0){
        std::vector<std::string> recordInfo;
        for(int x = 0; x < records.size(); x++){
            if(records[x] -> getReason() != "Removal Request")
                recordInfo.push_back((records[x] -> getInterventionNumber() + "\t" + records[x] -> getReason() + "\t" + records[x] -> getAnimal() -> getName()));
        }
        if(recordInfo.size() > 0){
            int recordToBeDeleted = displayArrowMenu("Select the record to be deleted", recordInfo) - 1;
            (facilities[selectedFacility] -> getStaffRecords())[recordToBeDeleted] -> display();
            system("pause");
            if(displayArrowMenu("Delete the selected appointment?", yesNoOptions) == 1){
                delete((facilities[selectedFacility] -> getStaffRecords())[recordToBeDeleted]);
                std::cout <<"The record has been deleted" << std::endl;
                system("pause");
            }
        } else {
            system("cls");
            std::cout << "There are currently no Appointments booked at this branch" << std::endl;
            system("pause");
        }
    } else {
        system("cls");
        std::cout << "There are currently no Appointments booked" << std::endl;
        system("pause");
    }
}

void deleteObject(int option){
    switch(option){
        case 1:
            deleteAnimal();
            break;
        case 2:
            deleteClient();
            break;
        case 3:
            deleteAppointment();
            break;

    }
}

void extraPlaceForInspectionOptions(){
    
}

void extraVeterinarionOptions(){

}

void displayPageTwo(int option){
    switch(option){
        case 5:
            extraPlaceForInspectionOptions();
            break;
        case 6:
            extraVeterinarionOptions();
            break;
    }
}

void executeMenuOption(int option){
    int selectedOption = option - 1;
    std::vector<std::string> functionOptions = {("Add " + menuOptions[selectedOption]), ("Update " + menuOptions[selectedOption]), ("View " + menuOptions[selectedOption]), ("View all " + menuOptions[selectedOption]), ("Delete " + menuOptions[selectedOption])};
    if(option == 5 || option == 6){
        functionOptions.push_back("Page 2");
    }
    functionOptions.push_back("Back");
    switch(displayArrowMenu("Choose an option", functionOptions)){
        case 1:
            createObject(option);
            break;
        case 2:
            updateObject(option);
            break;
        case 3:
            displayObjectInfo(option);
            break;
        case 4:
            displayAllObjectInfo(option);
            break;
        case 5:
            deleteObject(option);
            break;
        case 6:
            displayPageTwo(option);
            break;
    }
}


int main()
{
    


    int menuOption = 0;
    while((menuOption = menuOption = displayArrowMenu("Main Menu\n", menuOptions)) != 7)
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