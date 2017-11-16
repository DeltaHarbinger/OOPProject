#ifndef CLIENT_H
#define CLIENT_H

#include <string>

class Client
{
public:
	
	Client()
	{
		this -> fName = "";
		this -> lName = "";
		this -> telephoneNo = "";
		this -> address = "";
		this -> email = "";
	}
	
	Client(std::string fName, std::string lName, std::string telephoneNo, std::string address, std::string email)
	{
		incrementCounter();
		this -> id = id;
		this -> fName = fName;
		this -> lName = lName;
		this -> telephoneNo = telephoneNo;
		this -> address = address;
		this -> email = email;
	}
	
	~Client()
	{
	}

	//Getters
	int getId(){
		return id;
	}

	std::string getFName(){
		return fName;
	}

	std::string getLName(){
		return lName;
	}

	std::string getTelephoneNo(){
		return telephoneNo;
	}

	std::string getAddress(){
		return address;
	}

	std::string getEmail(){
		return email;
	}

	void setId(int id){
		this -> id = id;
	}

	void setFName(std::string fName){
		this -> fName = fName;
	}

	void setLName(std::string){
		this -> lName = lName;
	}

	void setTelephoneNo(std::string telephoneNo){
		this -> telephoneNo = telephoneNo;
	}

	void setAddress(std::string addess){
		this -> address = address;
	}

	void setEmail(std::string email){
		this -> email = email;
	}

	void incrementCounter(){
		numberOfClients++;
	}

	void display(){
		std::cout << "Name:\t" << fName << " " << lName << std::endl << "Telephone #:\t" << telephoneNo << std::endl << "Address:\t" << address << std::endl << "Email:\t" << email << std::endl;
	}

	void writeToFile(){
		std::ofstream clientWriter;
		try{
			clientWriter.open("newClients.txt", std::ios::app);
			clientWriter << fName << '\t' << lName << '\t' << telephoneNo << '\t' << address << '\t' << email << '\n';
		} catch(std::exception& e){
			system("cls");
			std::cout << "Failure while storing clients" << std::endl;
			system("pause");
		}
	}

private:
	int id;
	std::string fName;
	std::string lName;
	std::string telephoneNo;
	std::string address;
	std::string email;
	static int numberOfClients;
};
int Client::numberOfClients = 0;

#endif