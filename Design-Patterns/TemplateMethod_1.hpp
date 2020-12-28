#pragma once
#include "Print.hpp"

// Concept From: Head First Design Patterns
// Example in C++ written by: Paul Burgess

// The template method pattern defines the steps of an algorithm and allows the
// subclasses to provide the implementation for one or more steps.


// -------------- Class with Algorithm Outline  --------------
class CaffeineDrink{	
public:
	virtual ~CaffeineDrink() = default;
	void prepare_recipe() const{
		boil_water();
		brew();
		pour_in_cup();

		if(customer_wants_condiments()){
			add_condiments();
		}
	}
private:
	void boil_water() const{
		print("Boiling water");
	}		

	void pour_in_cup() const {
		print("Pouring into cup");
	}

	// hook
	virtual bool customer_wants_condiments() const {
		return true;
	}

	virtual void brew() const = 0;
	virtual void add_condiments() const = 0;	
};


// ----- Subclass that overrides steps in the algorithm ------
class Tea : public CaffeineDrink{
public:
	void brew() const override{
		print("Brewing the tea");
	}
	void add_condiments() const override{
		print("Adding lemon to tea");
	}

	// Decided not to implement the hook (so condiments are always added)
};


// ----- Subclass that overrides steps in the algorithm ------
class Coffee : public CaffeineDrink{
public:
	void brew() const override{
		print("Dripping coffee through filter");
	}
	void add_condiments() const override{
		print("Adding sugar and cream");
	}
	
private:
	// hook in overridden here (so customer does not add condiments):
	bool customer_wants_condiments() const override{
		return false;
	}
};


// ----------------- Example --------------------
inline void template_method_1(){

	CaffeineDrink* tea = new Tea;
	tea->prepare_recipe();
	delete tea;

	print("\n");
	
	CaffeineDrink* coffee = new Coffee;
	coffee->prepare_recipe();
	delete coffee;	
}