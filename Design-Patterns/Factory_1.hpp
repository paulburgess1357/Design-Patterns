#pragma once

// Concept From: Refactor Guru Design Patterns Book
// Example in C++ written by: Paul Burgess

// Abstract Factory
// Creation design pattern that lets you produce families of related objects
// without specifying their concrete classes

#include "Print.hpp"


// -------------- Product Interface 1 --------------
class Chair {
public:
	virtual ~Chair() = default;
	virtual void sit() const = 0;
};


// -------------- Concrete Products --------------
class VictorianChair : public Chair {
	void sit() const override {
		print("Sitting on a Victorian chair");
	}
};

class ModernChair : public Chair {
	void sit() const override {
		print("Sitting on a Modern chair");
	}
};


// ------------- Product Interface 2 ---------------
class CoffeeTable {
public:
	virtual ~CoffeeTable() = default;
	virtual void eat() const = 0;
};

class VictorianCoffeeTable : public CoffeeTable {
public:
	void eat() const override {
		print("Eating at Victorian coffee table");
	}
};

class ModernCoffeeTable : public CoffeeTable {
public:
	void eat() const override {
		print("Eating at Modern coffee table");
	}
};


// ------------- Abstract Factory -------------
class FurnitureFactory {
public:
	virtual ~FurnitureFactory() = default;
	virtual Chair* create_chair() const = 0;
	virtual CoffeeTable* create_coffee_table() const = 0;
};

// Concrete Factory 1
class VictorianFurnitureFactory : public FurnitureFactory {
public:
	Chair* create_chair() const override {
		return new VictorianChair;
	}
	CoffeeTable* create_coffee_table() const override {
		return new VictorianCoffeeTable;
	}
};

// Concrete Factory 2
class ModernFurnitureFactory : public FurnitureFactory {
public:
	Chair* create_chair() const override {
		return new ModernChair;
	}
	CoffeeTable* create_coffee_table() const override {
		return new ModernCoffeeTable;
	}
};


// ---------------- Example ----------------
void inline factory_1() {

	FurnitureFactory* furniture_factory = new VictorianFurnitureFactory;
	Chair* new_chair = furniture_factory->create_chair();
	CoffeeTable* new_coffee_table = furniture_factory->create_coffee_table();

	new_chair->sit();
	new_coffee_table->eat();

	delete furniture_factory;
	delete new_chair;
	delete new_coffee_table;

}