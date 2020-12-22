#pragma once

// Concept From: Refactor Guru Design Patterns Book
// Example in C++ written by: Paul Burgess

// Factory Method
// Creational pattern that provides an interface for creating objects in the
// superclass, but allows subclasses to alter the type of objects that will
// be created


#include "Print.hpp"


// -------------- Product Interface --------------
class Transport {

public:
	virtual ~Transport() = default;
	virtual void deliver() const = 0;

};


// -------------- Concrete Products --------------
class Truck : public Transport {

public:
	void deliver() const override {
		print("Delivering by truck");
	}
};

// Concrete Product 2
class Boat : public Transport {

public:
	void deliver() const override {
		print("Delivering by boat");
	}
};


// --------- Creator Interface (Factory) ----------
class TransportCreator {

public:
	virtual ~TransportCreator() = default;

	Transport* create_and_test_transportation() {

		Transport* transport_type = create_transportation();
		
		transport_type->deliver();

		return transport_type;
	}

protected:
	virtual Transport* create_transportation() = 0;

};


// --------- Concrete Creator Classes ------------
class TruckCreator : public TransportCreator {
public:
	Transport* create_transportation() override {
		return new Truck;
	}
};

class BoatCreator : public TransportCreator {
public:
	Transport* create_transportation() override {
		return new Boat;
	}
};


// ----------------- Example --------------------
int main() {
	TransportCreator* truck_creator = new TruckCreator;
	Transport* truck = truck_creator->create_and_test_transportation();

	TransportCreator* boat_creator = new BoatCreator;
	Transport* boat = boat_creator->create_and_test_transportation();

	delete truck_creator;
	delete truck;

	delete boat_creator;
	delete boat;
}
