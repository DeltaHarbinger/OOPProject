#include <iostream>
#include <string>
#include <fstream>
#include <conio.h>
#include <cstdio>
#include <windows.h>
#include "HealthFacility.h"
#include "PlaceForInspection.h"
#include "RemovalRequest.h"

//Health Facility Data is defined here. The data is hard coded as there is no indication of a need to change the data later on
int days[] = {1, 2, 3, 4, 5, 6};
int days2[] = {0, 6};
std::vector<std::string> healthFacilityAddresses = {"10 Winchester Road", "Caymanas Track Limited"};
HealthFacility * facilities[2] = { new HealthFacility(healthFacilityAddresses[0], days, "Full"), new HealthFacility(healthFacilityAddresses[1], days2, "Mobile") };


//Vectors for storing objects
std::vector<Client *> clients;
std::vector<Animal *> animals;
std::vector<PlaceForInspection *> placesForInspection;


//Yes no option menu
std::vector<std::string> yesNoOptions = {"Yes", "No"};
//Menu options used in main menu
std::vector<std::string> menuOptions = {"Animals", "Clients", "Appointments", "Removal Requests", "Places for Inspection", "Veterinarians", "Exit"};


//Function used to generate an arrow menu
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




//Function used to get different types of variables in a generic way
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
    return displayArrowMenu(message, yesNoOptions) == 1;
}

int getMonth(std::string message){
    std::vector<std::string> months = {"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};
    return (displayArrowMenu(message, months) - 1);
}

//validates a given date
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

struct tm * getDate(std::string dateReason){
    time_t source = time(NULL);
    struct tm * date = localtime(&source);
    date -> tm_year = getNumber("Enter the intended year for the " + dateReason) - 1900;
    date -> tm_mon = getMonth("Select the intended month for the " + dateReason);
    date -> tm_mday = getNumber("Enter the intended day for the " + dateReason);
    while(!validDay(date -> tm_year, date -> tm_mon, date -> tm_mday)){
        std::cout << "Please enter a valid date";
        date -> tm_year = getNumber("Enter the intended year for the " + dateReason) - 1900;
        date -> tm_mon = getMonth("Select the intended month for the " + dateReason);
        date -> tm_mday = getNumber("Enter the intended day for the " + dateReason);
    }
    return date;
}




//Checks if objects exist in a vector and returns true/false appropriately
bool animalsExist(){
    return animals.size() > 0;
}

bool clientsExist(){
    return clients.size() > 0;
}

bool interventionsExist(){
    return facilities[0] -> getStaffRecords().size() > 0 || facilities[1] -> getStaffRecords().size() > 0;
}

bool placesForInspectionExist(){
    return placesForInspection.size() > 0;
}

bool veterinariansExist(){
    return (facilities[0] -> getVeterinarians()).size() > 0 || (facilities[1] -> getVeterinarians()).size() > 0;
}


//Returns a vector of strings composed of the names, types and preeds of animals
std::vector<std::string> getAllBasicAnimalInfo(){
    std::vector<std::string> animalInfo;
    for(int x = 0; x < animals.size(); x++){
        std::string animal = (animals[x] -> getName() + "\t" + animals[x] -> getType() + '\t' + animals[x] -> getBreed());
        animalInfo.push_back(animal);
    }
    return animalInfo;
}
//Returns a vector of strings composed of the names, of clients
std::vector<std::string> getAllClientNames(){
    std::vector<std::string> clientNames;
    for(int x = 0; x < clients.size(); x++){
        clientNames.push_back(clients[x] -> getFName() + " " + clients[x] -> getLName());
    }
    return clientNames;
}

//Get the names of all places of inspection
std::vector<std::string> getAllBasicPlaceOfInspectionInfo(){
    std::vector<std::string> placesInfo;
    for(int x = 0; x < placesForInspection.size(); x++){
        placesInfo.push_back(placesForInspection[x] -> getName() + " " + placesForInspection[x] -> getTypeOfPlace());
    }
    return placesInfo;
}

//Returns a health facility chosen from a menu
HealthFacility * getHealthFacility(std::string message){
    return facilities[displayArrowMenu(message, healthFacilityAddresses) - 1];
}
//Returns a client selected from a menu
Client * getClient(std::string message){
    return clients[displayArrowMenu(message, getAllClientNames()) - 1];
}
//Returns an animal selected from a menu
Animal * getAnimal(std::string message){
    return animals[displayArrowMenu(message, getAllBasicAnimalInfo()) - 1];
}
//Returns the staff records of a given health facility
std::vector<Intervention *> getStaffRecords(HealthFacility * facility){
    return facility -> getStaffRecords();
}
//Returns a vector of strings filled with basic info on given interventions including the intervention number, client name and reason
std::vector<std::string> getAllBasicInterventionInfo(std::vector<Intervention *> interventions){
    std::vector<std::string> recordInfo;
    for(int x = 0; x < interventions.size(); x++){
        std::string info = (interventions[x] -> getInterventionNumber() + "\t" + interventions[x] -> getClient() -> getFName() + "\t" + interventions[x] -> getClient() -> getLName() + "\t" + interventions[x] -> getReason());
        recordInfo.push_back(info);
    }
    return recordInfo;
}
//Returns an intervention from a health facility after giving a 
Intervention * getRecord(std::string message){
    HealthFacility * f = getHealthFacility("Select the health facility");
    std::vector<Intervention *> records = getStaffRecords(f);
    return records[displayArrowMenu(message, getAllBasicInterventionInfo(records)) - 1];
}

Intervention * getAppointment(std::string message){
    HealthFacility * f = getHealthFacility("Select the health facility");
    std::vector<Intervention *> records = getStaffRecords(f);
    for(int x = 0; x < records.size(); x++)
        if(!(records[x] -> getReason()).compare("Removal Request"))
            records.erase(records.begin() + x);
    //return records[displayArrowMenu(message, getAllBasicInterventionInfo(records)) - 1];
    if(records.size() > 0)
        return records[displayArrowMenu(message, getAllBasicInterventionInfo(records)) - 1];
    else
        return 0;
}

Intervention * getRemovalRequest(std::string message){
    HealthFacility * f = getHealthFacility("Select the health facility");
    std::vector<Intervention *> records = getStaffRecords(f);
    for(int x = 0; x < records.size(); x++)
        if((records[x] -> getReason()) != "Removal Request")
            records.erase(records.begin() + x);
    if(records.size() > 0)
        return records[displayArrowMenu(message, getAllBasicInterventionInfo(records)) - 1];
    else
        return 0;
}

PlaceForInspection * getPlaceForInspection(std::string message){
    std::vector<std::string> places;
    for(int x = 0; x < placesForInspection.size(); x++){
        places.push_back(((placesForInspection[x] -> getName()) + "\t" + (placesForInspection[x] -> getTypeOfPlace())));
    }
    return placesForInspection[displayArrowMenu(message, places) - 1];
}


//Adds an animal to the global animal vector after taking all of the information needed to create it
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



////////////////////////////////////    Add Object  ////////////////////////////////
void addAnimal(Client * client){
    std::string type = getString("Enter the type of animal");
    std::string breed = getString("Enter the animal's breed");
    animals.push_back(new Animal(type, breed));
    system("cls");
    std::cout << "The data for the animal that " << (client -> getFName()) << " has requested to be removed has been stored" << std::endl;
    system("pause");
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

void addAppointment(){
    
    std::string reason = getString("State the reason for the appointment");
    bool abilityToPay = getBoolean("Does the client have the ability to pay?");
    bool payInFull = false;
    if(abilityToPay)
        payInFull = getBoolean("Will the client pay in full?");
    bool makeContribution = getBoolean("Does the client intend to make a contribution?");
    Animal * animal = getAnimal("Select the animal");

    struct tm * intendedDate = getDate("appointment");
    mktime(intendedDate);
    std::string intendedDateString = asctime(intendedDate);
    time_t currentTime = time(NULL);
    std::string currentTimeString = asctime(localtime(&currentTime));
    
    Intervention * newIntervention = new Intervention(reason, abilityToPay, payInFull, makeContribution, animal, intendedDateString, currentTimeString);
    getHealthFacility("Select the facility") -> addStaffRecord(newIntervention);
}
//Adds removal request to 
void addRemovalRequest(){
    Client * client = getClient("Choose the client responsible for making the request");
    addAnimal(client);
    Animal * animal = animals[animals.size() - 1];
    bool abilityToPay = getBoolean("Does the client have the ability to pay?");
    bool payInFull = false;
    if(abilityToPay)
        payInFull = getBoolean("Will the client pay in full?");
    bool makeContribution = getBoolean("Does the client intend to make a contribution?");
    struct tm * intendedDate = getDate("removal");
    mktime(intendedDate);
    std::string intendedDateString = asctime(intendedDate);
    time_t currentTime = time(NULL);
    std::string currentTimeString = asctime(localtime(&currentTime));
    std::string address = getString("Enter the address that the animal is currently located at");
    RemovalRequest * newRemovalRequest = new RemovalRequest(abilityToPay, payInFull, makeContribution, animal, client, intendedDateString, currentTimeString, address);
    getHealthFacility("Select the facility") -> addStaffRecord(newRemovalRequest);
}

void addPlaceForInspection(){
    std::string name = getString("Enter the name of the Facility");
    std::string typeOfPlace = getString("Enter the type of facility");
    placesForInspection.push_back(new PlaceForInspection(name, typeOfPlace));
}

void addVeterinarian(){
    std::string name = getString("Enter the name of the Veterinarian");
    HealthFacility * employedFacility = getHealthFacility("Select the facility that th veterinarian is employed at");
    employedFacility -> addVeterinarian(new Veterinarian(name));
}

//Calls the paaropriate function used to create an object depending on the parameter
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
            if(clientsExist())
                addRemovalRequest();
            else{
                std::cout << "There are currently no clients registered" << std::endl;
            }
            break;
        case 5:
            addPlaceForInspection();
            break;
        case 6:
            addVeterinarian();
            break;
    }
}

void updateAnimalName(Animal * targetAnimal){
    std::string name = getString("Enter the animal's new name");
    targetAnimal -> setName(name);
}

void updateAnimalType(Animal * targetAnimal){
    std::string type = getString("Enter the animal's type");
    targetAnimal -> setType(type);
}

void updateAnimalGender(Animal * targetAnimal){
    std::string gender = getString("Enter the animal's gender");
    targetAnimal -> setGender(gender);
}

void updateAnimalBreed(Animal * targetAnimal){
    std::string breed = getString("Enter the animal's breed");
    targetAnimal -> setBreed(breed);
}

void updateAnimalAge(Animal * targetAnimal){
    int age = getNumber("Enter the animal's age");
    targetAnimal -> setApproxAge(age);
}

void updateAnimalAdoptionCandidateStatus(Animal * targetAnimal){
    bool adoptionCandidateStatus = getBoolean("Is the animal a candidate for adoption?");
    targetAnimal -> setAdoptionCandidate(adoptionCandidateStatus);
}

void updateAnimalOwner(Animal * targetAnimal){
    std::vector<std::string> clientInfo = getAllClientNames();
    clientInfo.push_back("None");
    int newClient = displayArrowMenu("Selet the animal's owner", clientInfo) - 1;
    newClient == clients.size() ? targetAnimal -> setOwner(0) : targetAnimal -> setOwner(clients[newClient]);
}

void updateAnimalInfo(int option){
    Animal * targetAnimal = getAnimal("Select the animal to be updated");
    switch(option){
        case 1:
            updateAnimalName(targetAnimal);
            break;
        case 2:
            updateAnimalType(targetAnimal);
            break;
        case 3:
            updateAnimalGender(targetAnimal);
            break;
        case 4:
            updateAnimalBreed(targetAnimal);
            break;
        case 5:
            updateAnimalAge(targetAnimal);
            break;
        case 6:
            updateAnimalAdoptionCandidateStatus(targetAnimal);
            break;
        case 7:
            updateAnimalOwner(targetAnimal);
            break;
        
    }
}

void updateAnimal(){
    std::vector<std::string> updateOptions = {"Name", "Type", "Gender", "Breed", "Age", "Update Adoption Candidate Status", "Change owner", "Cancel"};
    updateAnimalInfo(displayArrowMenu("Select the field to be updated", updateOptions));
}

void updateClientFirstName(Client * targetClient){
    std::string fName = getString("Enter the client's first name");
    targetClient -> setFName(fName);
}

void updateClientLastNAme(Client * targetClient){
    std::string lName = getString("Enter the client's last name");
    targetClient -> setLName(lName);
}

void updateClientTelephoneNumber(Client * targetClient){
    std::string telephoneNo = getString("Enter the client's telephone number");
    targetClient -> setTelephoneNo(telephoneNo);
}

void updateClientAddress(Client * targetClient){
    std::string address = getString("Enter the client's address");
    targetClient -> setAddress(address);
}

void updateClientEmail(Client * targetClient){
    std::string email = getString("Enter the client's email");
    targetClient -> setEmail(email);
}

void updateClientInfo(int option){
    Client * targetClient = getClient("Select the client to be updated");
    switch(option){
        case 1:

            break;
        case 2:

            break;
        case 3:

            break;
        case 4:

            break;
        case 5:

            break;
    }
}

void updateClient(){
    std::vector<std::string> updateOptions = {"First Name", "Last Name", "Telephone number", "Address", "Email", "Cancel"};
    updateClientInfo(displayArrowMenu("Select the field to be updated", updateOptions));
}

void updateAppointmentReason(Intervention * targetAppointment){

}



void updateAppointmentInfo(int option){
    Intervention * targetAppointment = getAppointment("Select the appointment to be updated");
    switch(option){
        case 1:
            updateAppointmentReason(targetAppointment);
            break;
        case 2:

            break;
    }
}

void updateAppiontment(){
    std::vector<std::string> updateOptions = {"Reason", "Ability To Pay", "Ability to Pay in Full", "Ability to Make Contribution", "Animal Scheduled", "Client Scheduled", "Intended Date", "Cancel"};
    updateAppointmentInfo(displayArrowMenu("Select the field to be updated", updateOptions));
}










void updateObject(int option){
    switch(option){
        case 1:
            updateAnimal();
            break;
        case 2: 
            updateClient();
            break;
        case 3:
            break;
    }
}

///////////////////////////////////////     Display     //////////////////////////////

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
    Intervention * temp = getAppointment("Select the record to be displayed");
    if(temp){
        system("cls");
        temp -> display();
    }
    else{
        std::cout << "There are no appointments to be displayed" << std::endl;
    }
    system("pause");
}

void displayRemovalRequest(){
    system("cls");
    Intervention * temp = getRemovalRequest("Select the record to be displayed");
    if(temp){
        system("cls");
        temp -> display();
    }
    else{
        std::cout << "There are no appointments to be displayed" << std::endl;
    }
    system("pause");
}

void displayPlaceForInspection(){
    system("cls");
    PlaceForInspection * place = getPlaceForInspection("Select the Location to be displayed");
    place -> display();
    system("pause");
}

void displayVeterinarian(){

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
            break;
        case 4:
            if(interventionsExist())
                displayRemovalRequest();
            else{
                system("cls");
                std::cout << "There are currently no removal requests recorded." << std::endl;
                system("pause");
            }
            break;
        case 5:
            if(placesForInspectionExist())
                displayPlaceForInspection();
            else{
                system("cls");
                std::cout << "There are currently no places to be inspected recorded" << std::endl;
                system("pause");
            }
        case 6:
            if(veterinariansExist())
                displayVeterinarian();
            else {
                system("cls");
                std::cout << "There are currently no veterinarians recorded" << std::endl;
                system("pause");
            }
    }
}

////////////////////////////////    Display ALL     /////////////////////////////////////////////
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
        bool displayed = false;
        std::vector<Intervention *> staffRecords = facilities[x] -> getStaffRecords();
        if(staffRecords.size() > 0)
            for(int y = 0; y < staffRecords.size(); y++){
                if((staffRecords[y] -> getReason()).compare("Removal Request")){
                    system("cls");
                    staffRecords[y] -> display();
                    displayed = true;
                    system("pause");
                }
            }
        if(!displayed){
            std::cout << "There are currently no records for the facility at " << facilities[x] -> getAddress() << std::endl;
            system("pause");
        }
    }
}

void displayAllRemovalRequests(){
    for(int x = 0; x < 2; x++){
        bool displayed = false;
        std::vector<Intervention *> staffRecords = facilities[x] -> getStaffRecords();
        if(staffRecords.size() > 0){
            for(int y = 0; y < staffRecords.size(); y++){
                if(!(staffRecords[y] -> getReason()).compare("Removal Request")){
                    system("cls");
                    staffRecords[y] -> display();
                    system("pause");
                    displayed = true;
                }
            }
        }
        if(!displayed){
            std::cout << "There are currently no records for the facility at " << facilities[x] -> getAddress() << std::endl;
            system("pause");
        }
    }
}

void displayAllPlacesForInspection(){
    if(placesForInspectionExist())
        for(int x = 0; x < placesForInspection.size(); x++){
            system("cls");
            placesForInspection[x] -> display();
            system("pause");
        }
    else{
        std::cout << "There are currently no places for inspection registered" << std::endl;
        system("pause");
    }
}

void displayAllVeterinarians(){
    if(veterinariansExist()){
        for(int x = 0; x < 2; x++){
            bool displayed = false;
            std::vector<Veterinarian *> veterinarians = facilities[x] -> getVeterinarians();
            if(veterinarians.size() > 0){
                for(int y = 0; y < veterinarians.size(); y++){
                    system("cls");
                    veterinarians[y] -> display();
                    system("pause");
                    displayed = true;
                }
            }
            if(!displayed){
                std::cout << "There are currently no veterinarians registered for the facility at " << facilities[x] -> getAddress() << std::endl;
                system("pause");
            }
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
        case 4:
            displayAllRemovalRequests();
            break;
        case 5:
            displayAllPlacesForInspection();
            break;
        case 6:
            displayAllVeterinarians();
    }
}

////////////////////////////////    Delete      //////////////////////////////
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
        std::vector<int> recordNumber;
        for(int x = 0; x < records.size(); x++){
            if(records[x] -> getReason() != "Removal Request")
                recordInfo.push_back((records[x] -> getInterventionNumber() + "\t" + records[x] -> getReason() + "\t" + records[x] -> getAnimal() -> getName()));
                recordNumber.push_back(x);
        }
        if(recordInfo.size() > 0){
            int recordToBeDeleted = displayArrowMenu("Select the record to be deleted", recordInfo) - 1;
            recordToBeDeleted = recordNumber[recordToBeDeleted];
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

void deleteRemovalRequest(){
    int selectedFacility = displayArrowMenu("Select the facility tha the request was booked at", healthFacilityAddresses) - 1;
    std::vector<Intervention *> records = facilities[selectedFacility] -> getStaffRecords();
    if(records.size() > 0){
        std::vector<std::string> recordInfo;
        std::vector<int> recordNumber;
        for(int x = 0; x < records.size(); x++){
            if(!(records[x] -> getReason()).compare("Removal Request"))
                recordInfo.push_back((records[x] -> getInterventionNumber() + "\t" + records[x] -> getReason() + "\t" + records[x] -> getClient() -> getFName()));
                recordNumber.push_back(x);
        }
        if(recordInfo.size() > 0){
            int recordToBeDeleted = displayArrowMenu("Select the record to be deleted", recordInfo) - 1;
            recordToBeDeleted = recordNumber[recordToBeDeleted];
            (facilities[selectedFacility] -> getStaffRecords())[recordToBeDeleted] -> display();
            system("pause");
            if(displayArrowMenu("Delete the selected rwquest?", yesNoOptions) == 1){
                delete((facilities[selectedFacility] -> getStaffRecords())[recordToBeDeleted]);
                std::cout <<"The request has been deleted" << std::endl;
                system("pause");
            }
        } else {
            system("cls");
            std::cout << "There are currently no requests booked at this branch" << std::endl;
            system("pause");
        }
    } else {
        system("cls");
        std::cout << "There are currently no requests booked" << std::endl;
        system("pause");
    }
}

void deletePlaceForInspection(){
    if(placesForInspectionExist()){
        int placeToBeDeleted = displayArrowMenu("Select the place to be deleted", getAllBasicPlaceOfInspectionInfo()) - 1;
        placesForInspection[placeToBeDeleted] -> display();
        system("pause");
        if(displayArrowMenu("Delete the place from the system?", yesNoOptions) == 1){
            system("cls");
            delete(placesForInspection[placeToBeDeleted]);
            std::cout << "The place has been deleted from the system" << std::endl;
            placesForInspection.erase(placesForInspection.begin() + placeToBeDeleted);
            system("pause");
        } else {
            system("cls");
            std::cout << "The place was not deleted" << std::endl;
            system("pause");
        }
    } else {
        system("cls");
        std::cout << "There are currently no places registered" << std::endl;
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
        case 4:
            deleteRemovalRequest();
            break;
        case 5:
            deletePlaceForInspection();
            break;
    }
}

////////////////////////////////    Extra Options   //////////////////////////////
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

void commitNewAnimals(){
    try{
        std::remove("animals.txt");
        std::rename("newAnimals.txt", "animals.txt");
        std::remove("owners.txt");
        std::rename("newOwners.txt", "owners.txt");
    } catch(std::exception& e){
        system("cls");
        std::cout << "Error commiting changes to animals, all changes have been reverted" << std::endl;
    }
}

void writeAnimals(){
    for(int x = 0; x < animals.size(); x++){
        animals[x] -> writeToFile();
        if(x == animals.size() - 1)
            commitNewAnimals();
    }

}

void commitNewClients(){
    try{
        std::remove("clients.txt");
        std::rename("newClients.txt", "clients.txt");
    } catch(std::exception& e){
        system("cls");
        std::cout << "Error commiting changes to clients, all changes have been reverted" << std::endl;
    }
}

void writeClients(){
    for(int x = 0; x < clients.size(); x++){
        clients[x] -> writeToFile();
        if(x == clients.size() - 1){
            commitNewClients();
        }
    }
}

void writeInterventions(){
    for(int x = 0; x < 2; x++){
        std::vector<Intervention *> records = facilities[x] -> getStaffRecords();
        for(int y = 0; y < records.size(); y++){

        }
    }
}

void writeObjects(){
    writeAnimals();
    writeClients();
}

int main()
{
    int menuOption = 0;
    while((menuOption = menuOption = displayArrowMenu("Main Menu\n", menuOptions)) != 7)
    {
        executeMenuOption(menuOption);
    }
    writeObjects();
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