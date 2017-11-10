#ifndef VETERINARIAN_H
#define VETERINARIAN_H

class Veterinarian
{
public:
	Veterinarian()
	{
	}
	
	Veterinarian(std::string name){
		this -> name = name;
	}
	
	~Veterinarian()
	{
	}
	
	
	void euthanasia() {
		
	}
	
	bool attemptToCare() {
		//Temporary
		return true;
	}

	std::string getName(){
		return name;
	}
private:
	std::string name;

};

#endif