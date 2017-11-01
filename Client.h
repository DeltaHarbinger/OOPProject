#ifndef CLIENT_H
#define CLIENT_H

#include <string>

class Client
{
public:
	
	Client()
	{
	}
	
	Client(std::string fName, std::string lName, std::string telephoneNo, std::string address, std::string email)
	{
	}
	
	~Client()
	{
	}



private:
	std::string fName;
	std::string lName;
	std::string telephoneNo;
	std::string address;
	std::string email;
};

#endif