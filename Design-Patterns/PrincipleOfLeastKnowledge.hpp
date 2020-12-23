#pragma once
#include "Print.hpp"

// Concept From: Head First Design Patterns
// Example in C++ written by: Paul Burgess

// The principle of least knowledge limits the function calls from objects
// within a class.  The goal is to create designs that are not tightly
// coupled.  This is also known as the Law of Demeter.


class Engine{
public:
	void start() const{
		print("Starting car");
	}
};

class Doors{
public:
	void lock() const{
		print("Locking doors");
	}
};

class Key{
public:
	bool key_turned_to_on() const{
		print("Turning key");
		return true;
	}
};


// ------------------------- Example -------------------------
class Car{

public:
	Car() = default;
	void start_car(Key key) const{

		Doors doors; // The methods from this object are legal to call since we are creating it.
		bool key_is_on =  key.key_turned_to_on(); // This method is legal since its an object passed in as a parameter
		if(key_is_on){
			m_engine.start(); // This method is legal since its a method called from a component of the class
			turn_dashboard_on(); // This method is legal since its a local method defined within the object itself.
			doors.lock(); // This method is legal because it is a method called on an object that we instantiated
		}		
	}
	
private:
	Engine m_engine;
	void turn_dashboard_on() const{
		print("Turning dashboard on");
	}		
};

inline void principle_of_least_knowledge_1(){
	Car car;
	Key key;
	car.start_car(key);
}