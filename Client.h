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
	std::string getFName(){
		return fName;
	}

	std::string getLName(){
		return lName;
	}

private:
	std::string fName;
	std::string lName;
	std::string telephoneNo;
	std::string address;
	std::string email;
};

#endif